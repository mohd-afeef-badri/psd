//*-------------------------------------------------------------------------------------*/
// Drucker-Prager Constitutive Model (linear elasticity, no strain hardening)
// Author: Evelyne FOERSTER
// Initial Version: July 2020
//*-------------------------------------------------------------------------------------*/

#include "stdafx.h"

using namespace std;
const int   NHISTDRUCKP = 1, // nb of internal variables (history)
            NPROPDRUCKP = 7; // nb of const properties (user data)
//////////////////////////////////////////////////////////////////////////////////////
// class DruckerPragerLaw
//

////////////////////////////////////
// ***** CONSTRUCTORS & DESTRUCTOR
DruckerPragerLaw::DruckerPragerLaw()
{
    initConst();
}
//=================================================================================================================//
/**/


//=================================================================================================================//
//=================================================================================================================//
DruckerPragerLaw::DruckerPragerLaw(const DruckerPragerLaw& h)
{
    init(h.m_param);
}
//=================================================================================================================//
/**/

//=================================================================================================================//
// Initialization performed when reading user parameters at the beginning of each step for a given integration point
//=================================================================================================================//
void DruckerPragerLaw::initConst()
{
    incmax = 30;
    indaux = 0;
    cohes = 0.;

    // local variables used during iterations
    m_mu = 0.;
    m_lamda = 0.;
    sinphi = 0.;
    cosphi = 0.;
    sinpsi = 0.;
    is_associe = true;
    is_plastic = false;
}
//=================================================================================================================//
/**/


//=================================================================================================================//
// Initializing when reading user parameters at the beginning of each step for a given integration point
//=================================================================================================================//
void DruckerPragerLaw::init(const dvector& param)
{
    m_param.assign(param.begin(),param.end()); // tab of size NPROPDRUCKP

    m_mu = m_param[1];
    m_lamda = m_param[0] - 2 * m_mu / 3.;
    auto	phi = m_param[2]; // already in radians (converted when reading data)
    auto	psi = m_param[3]; // already in radians
    cohes = m_param[4];
    incmax = (int)m_param[5];
    indaux = (int)m_param[6];

    sinphi = sin(phi);
    cosphi = cos(phi);
    sinpsi = sin(psi);
    is_associe = (phi == psi);
    sef = sqrt(3.) * (3. - sinphi);//compressive meridian
    alfa = 2. * sinphi / sef;
    xk = 6. * cohes * cosphi / sef;
    alfpsi = 2. * sinpsi / sqrt(3.) / (3. - sinpsi);
    m_elast_tensor = ElastTensor(m_lamda, m_mu);
}
//=================================================================================================================//
/**/

//=================================================================================================================//
// Just put for compatibility with the template writing of laws but not needed for this law
// sig = stress tensor at the end of previous converged time step
// histab : tab containing internal variables(=hardening parameters) stored on each integration point(size = NHISTHUJ)
//
//=================================================================================================================//
bool DruckerPragerLaw::initState(const Tensor2& /*sign*/, dvector* histab)
{
    if (histab == nullptr) return true;
    is_plastic = histab->front();
    return false;
}
//=================================================================================================================//
/**/

//=================================================================================================================//
// reading the 24 Hujeux Law parameters from a given .input file
//=================================================================================================================//
bool DruckerPragerLaw::readParameters(const string& name)
{
#ifdef DEBUG
    cout << "\n Entering class HujeuxLaw::readParameters  from hujeux.cpp\n"
       << " Input parameters :\n                  name = "  << name <<"\n"<< endl;
#endif

#ifdef _DEBUG
    if (name.empty())
	{
		cout << "\n Error filename for materials not found "
		        "--> Process stopped in HujeuxLaw::readParameters\n";
		return false;
	}
#endif

    filebuf MonFichier;
    bool ok = MonFichier.open(name, ios::in);

#ifdef _DEBUG
    if (!ok) return false;
#endif

    istream		JeLis(&MonFichier);
    char		c[MAXCAR];

    // =================================================================================
    // Drucker-Prager model parameters :
    // 0-Ki  1-Gi 2-phi(°)  3-psi(°)  4-cohesion (Pa) 5-incmax   6-indaux
    // =================================================================================
    dvector param(NPROPDRUCKP, 0.);
    for (int i = 0; i < NPROPDRUCKP; i++)
        JeLis >> param[i];
    JeLis.getline(c, MAXCAR); // "\n"

    MonFichier.close();

#ifdef _DEBUG
    if (param[2] < 0.) param[2] *= -1;// phi is positive in Drucker-Prager
	if (param[3] < 0.) param[3] *= -1;// psi also
	if (fabs(param[2]) < fabs(param[3])) param[3] = param[2];// psi <= phi
	if (int(param[6]) < 0 || int(param[6]) > 1) param[6] = 0;
#endif

    param[2] *= RAD;
    param[3] *= RAD;

    init(param);

#ifdef DEBUG
    cout << "// ================================================================================= //"
       << "\n  0  Ki      = "<< param[0]
       << "\n  1  Gi      = "<< param[1]
       << "\n  2  ne      = "<< param[2]
       << "\n  3  phi(°)  = "<< param[3]
       << "\n  4  psi(°)  = "<< param[4]
       << "\n  5  beta    = "<< param[5]
       << "\n  6  pci     = "<< param[6]
       << "\n  7  amon    = "<< param[7]
       << "\n  8  b       = "<< param[8]
       << "\n  9  acyc    = "<< param[9]
       << "\n  10 alfa    = "<< param[10]
       << "\n  11 rayela  = "<< param[11]
       << "\n  12 rayhys  = "<< param[12]
       << "\n  13 raymbl  = "<< param[13]
       << "\n  14 cmon    = "<< param[14]
       << "\n  15 d       = "<< param[15]
       << "\n  16 ccyc    = "<< param[16]
       << "\n  17 dltela  = "<< param[17]
       << "\n  18 xkimin  = "<< param[18]
       << "\n  19 m       = "<< param[19]
       << "\n  20 facinc  = "<< param[20]
       << "\n  21 iecoul  = "<< param[21]
       << "\n  22 incmax  = "<< param[22]
       << "\n  23 Kaux    = "<< param[23]
       << "\n  24 Gaux    = "<< param[24]
       << "\n// ================================================================================= //"
       << endl;
#endif
    return true;
}
//=================================================================================================================//
/**/


//=================================================================================================================//
// Computing tangent constitutive (4th order) tensor
//=================================================================================================================//
void DruckerPragerLaw::computeTangentTensor(const Tensor2& sig,const Tensor2& deps)
{
    // Initializing tangent stiffness tensor with the elastic one
    int i,j;

    for (i = 0; i < 6; i++)
        for (j = 0; j < 6; j++)
            m_tangent_tensor[i][j] = m_elast_tensor(i,j);

    auto K = m_lamda + 2. * m_mu / 3.;
    auto depsv = trace(deps);
    Real lambdap = 0.; // plastic multiplier

    // 1st stress invariant
    Real I1 = trace(sig);

    // Stress deviator
    Real3	sd = sig.get_diagonal(),// sii
            ss = sig.get_outdiagonal();//sij, j!=i

    sd += (-I1/3.);

    // 2nd deviatoric stress invariant
    Real	J2 = norm_sqr(ss) + 0.5*norm_sqr(sd),
            RJ2 = sqrt(J2);


    // Computing plastic multiplier:
    // lamdap = phiK*depsv + phiG*sij*depsij
    // with phiK = [3*K*alfa]/RH and phiG = G/RJ2/RH
    // In case of non associated law:
    // plastic potential: g = RJ2 + alfpsi*I1

    Real	H = m_mu + 9. * K * alfa * alfpsi, RH = sqrt(H),
            phiG = m_mu / RJ2 / RH,
            phiK = 3. * K * alfa / RH,
            psiK = 3. * K * alfpsi / RH;

    lambdap = phiK * depsv;
    lambdap += phiG * (dot(sd, deps.get_diagonal()) + dot(ss, deps.get_outdiagonal()));

    // if lambdap <= 0, nothing to do (remaining elastic): tangent_tensor = elast_tensor
    if (lambdap > 0.)
    {
        // Plastic yielding
        Real3	fh = phiG * sd + phiK,
                hs = phiG * ss,
                gh = phiG * sd + psiK;

        // m_tangent_tensor = constitutive 4th order tensor (as m_elast_tensor)
        // => symmetric if is_associe = true ou indaux = 0 (Sup = Slow)
        //     _          _
        //     |  D     Sup |
        // C = |            |
        //     |            |
        //     |  Slow   S  |
        //     |_          _|
        //
        // 3D tensorial products => matrix 3x3
        Real3x3	mat1 = tensor_prod(gh, fh), // D
                mat2 = tensor_prod(hs, hs), // S
                mat3 = tensor_prod(gh, hs), // Sup
                mat4 = tensor_prod(fh, hs); // Slow

        for (i = 0; i < 3; i++)
            for (j = 0; j < 3; j++)
                m_tangent_tensor[i][j] -= mat1[i][j]; //D

        for (i = 3; i < 6; i++)
            for (j = 3; j < 6; j++)
                m_tangent_tensor[i][j] -= mat2[i-3][j-3]; // S

        for (i = 0; i < 3; i++)
            for (j = 3; j < 6; j++)
                m_tangent_tensor[i][j] -= mat3[i][j-3]; // Sup

        // if non associated law => indaux (user choice) to keep the tangent stiffness tensor symmetric or not
        // if yes, we assume Slow = Sup (so keeping upper part values only)
        if (is_associe || indaux == 0)
            mat4 = mat3;

        for (i = 3; i < 6; i++)
            for (j = 0; j < 3; j++)
                m_tangent_tensor[i][j] -= mat4[i-3][j]; //Slow

        is_plastic = true;
    }
    else
        is_plastic = false;
}
//=================================================================================================================//
/**/


//=================================================================================================================//
// Computing stresses at step n+1 (small strain formulation)
// Deviatoric plane mechanisms : mec1=YZ    mec2=ZX    mec3=XY
//=================================================================================================================//
void DruckerPragerLaw::ComputeStress(dvector* histab,Tensor2& sig, Tensor2& eps, Tensor2& epsp, Tensor2& dsig,
                              const Tensor2& deps,bool is_converge)
{
    Tensor2 sign(sig);
    dsig = m_elast_tensor*deps;

    // stress estimation
    sig = sign + dsig;

    // 1st stress invariant
    double	I1 = trace(sig);

    // stress deviator
    Real3	sd = sig.get_diagonal(),// sii
            ss = sig.get_outdiagonal();//sij, j!=i

    sd += (-I1/3.);

    // 2nd deviatoric stress invariant
    auto	J2 = 0.5 * norm_sqr(sd) + norm_sqr(ss);
    auto    RJ2 = sqrt(J2);// square root of J2

    // Computing yield surface
    auto    fseuil = RJ2 + alfa*I1 - xk;

    if (fseuil > 0.)
    {
        // Plastic yielding
        is_plastic = true;

        // Evaluation of elastic & plastic parts for deformations:
        // dsig = dsigel + dsigp
        // dsigel = ratio*deps => sigel = sign + dsigel
        // dsigp = (1-ratio)*deps

        auto	I1n = trace(sign),dI1 = trace(dsig);
        Real3	dsd = dsig.get_diagonal(),
                dss = dsig.get_outdiagonal(),
                sdn = sign.get_diagonal(),
                ssn = sign.get_outdiagonal();
        auto	dJ2 = norm_sqr(dss),
                sds = dot(ssn,dss),
                J2n = norm_sqr(ssn);

        dsd += (-dI1/3.);
        sdn += (-I1n/3.);

        dJ2 += 0.5*norm_sqr(dsd);
        sds += 0.5*dot(sdn,dsd);
        J2n += 0.5*norm_sqr(sdn);

        // Computing ratio by solving: A*ratio*ratio + 2*B*ratio + E = 0
        Real	ratio = 0.,
                xkai = xk - alfa*I1n,
                A = dJ2 - pow(alfa*dI1,2),
                B = sds + alfa*dI1*xkai,
                E = J2n - xkai*xkai,
                Discrim = B*B - A*E;

        if (Discrim >= 0.)
        {
            if (fabs(A) <= EPS && fabs(B) > EPS)
            {
                ratio = -E/2./B;
            }
            else if (fabs(A) > EPS)
                ratio = (-B + sqrt(Discrim))/A;
        }

        // Elastic part
        Tensor2 rdsig(ratio*dsig);

        sig = sign + rdsig;

        // Plastic part: sub-increments are used to project back on the yield surface
        auto ninc = incmax;// default nb max of sub-increments

        if (xk)
        {
            ninc = int(20.*sqrt(2.*fseuil/xk)) + 1;
            ninc = min(incmax,ninc);
        }
        Real dratio = (1. - ratio)/ninc;

        Tensor2 deps1(dratio*deps);

        if (norm(deps1.m_vec) > EPS)
        {
            // Loop on sub-increments
            for (int i = 0; i < ninc; i++)
            {
                computeTangentTensor(sig,deps1);

                for (int j = 0; j < 6; j++)
                {
                    Real vi = 0.;
                    for (int k = 0; k < 6; k++) vi += m_tangent_tensor[j][k]*deps1.m_vec[k];
                    sig.m_vec[j] += vi;
                }

                if (is_plastic)
                {
                    I1 = trace(sig);
                    sd = sig.get_diagonal() - I1 / 3.;
                    ss = sig.get_outdiagonal();
                    J2 = 0.5*norm_sqr(sd) + norm_sqr(ss);
                    RJ2 = sqrt(J2);

                    fseuil = RJ2 + alfa*I1 - xk;

                    Real ft = fabs(fseuil),tol = 1.e-5;
                    if (fabs(xk) > EPS)
                    {
                        ft /= xk;
                        tol = 0.005;
                    }

                    // Checking that we are on yield surface
                    if (ft > tol)// Correcting as we are not yet
                    {
                        // Stress increment to project back on surface (f = fseuil):
                        // dsigc = -f/(df/dsig)^2*(df/dsig)
                        // Corrected stress: sig = sig - dsigc
                        // if a = 0.5/RJ2:
                        // (df/dsig) = alfa*I + a*sij (I = identite)
                        // (df/dsig)^2 = 3*alfa^2 + 2*J2*a^2
                        Real	alfa2 = alfa*alfa,
                                dfdsig2 = 3.*alfa2 + 0.5,
                                a = 0.5/RJ2;

                        E = fseuil/dfdsig2;

                        Tensor2 dsigc(E * (a * sd + alfa), E * a * ss);
                        sig -= dsigc;
                    }
                    epsp += deps1;
                }
            }
        }
    }
    histab->front() = is_plastic;
}
//=================================================================================================================//
/**/


