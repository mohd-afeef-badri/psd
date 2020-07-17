//*-------------------------------------------------------------------------------------*/
// Hujeux Constitutive Model (ECP family models): 4 yielding bounding surfaces
//                         (3 deviatoric + 1 isotropic), strain hardening
// Author: Evelyne FOERSTER
// Initial Version: May 2020
//*-------------------------------------------------------------------------------------*/

#include "stdafx.h"

using namespace std;

//extern void		gauss(double**, double*, double*, const int&);
extern void		gauss(Real**, Real*, Real*, const int&);
const Real	EPS  = 1.e-15;
const Real  FTOL = 1.e-8;
const Real  Pa   = -1.e6;                      // Reference stress (in Pa)
const Real  RAD = acos(-1.) / 180.;
string 	    ferrlog("error.log");
char	    szout[MAXBUFFER];
//////////////////////////////////////////////////////////////////////////////////////
// class ElastTensor: 4th-order elastic tensor
//

////////////////////////////////////
// ***** CONSTRUCTORS & DESTRUCTOR

ElastTensor::ElastTensor(const Real3x3& D, const Real3x3& S) { m_D = D; m_S = S; }

ElastTensor::ElastTensor(const ElastTensor& tens)
{
	m_D = tens.m_D;
	m_S = tens.m_S;
}

ElastTensor::ElastTensor(const Real& lambda, const Real& mu)
{

	m_D = lambda;
	for (int i = 0; i < 3; i++) m_D[i][i] += 2 * mu;
	m_S = mu * Real3x3::identity();
}

////////////////////////////////////
// ***** IMPLEMENTATION METHODS

ElastTensor& ElastTensor::operator=(const ElastTensor& tens)
{
	m_D = tens.m_D;
	m_S = tens.m_S;
	return (*this);
}

ElastTensor& ElastTensor::operator*=(const Real& x)
{
	m_D *= x;
	m_S *= x;
	return (*this);
}

ElastTensor& ElastTensor::operator+=(const ElastTensor& tens)
{
	m_D += tens.m_D;
	m_S += tens.m_S;
	return (*this);
}

ElastTensor& ElastTensor::operator-=(const ElastTensor& tens)
{
	m_D -= tens.m_D;
	m_S -= tens.m_S;
	return (*this);
}

ElastTensor ElastTensor::operator-() const
{
	return ElastTensor(-m_D,-m_S);
}

Real ElastTensor::operator()(const int& i, const int& j) const
{
	if (i < 0 || i >= 6 && j < 0 || j >= 6) throw std::out_of_range("Matrix indices are out of range");

	if (i < 3)
	{
		if (j < 3) return m_D[i][j];
		return 0.;
	}

	if (j < 3) return 0.;
	return m_S[i-3][j-3];
}

void ElastTensor::set(const int& i, const int& j, const Real& x)
{
	if (i < 0 || i >= 6 && j < 0 || j >= 6) throw std::out_of_range("Matrix indices are out of range");

	if (i < 3 && j < 3)//DD(i,j) = x;
		m_D[i][j] = x;

	else if (i > 3 && j > 3)//S(i-3,j-3) = x
		m_S[i-3][j-3] = x;
}

/*---------------------------------------------------------------------------*/
ElastTensor operator+(const ElastTensor& m1, const ElastTensor& m2)
{
    return ElastTensor(m1.m_D + m2.m_D, m1.m_S + m2.m_S);
}

/*---------------------------------------------------------------------------*/
ElastTensor operator-(const ElastTensor& m1, const ElastTensor& m2)
{
    return ElastTensor(m1.m_D - m2.m_D, m1.m_S - m2.m_S);
}

/*---------------------------------------------------------------------------*/
ElastTensor operator*(Real x, const ElastTensor& m)
{
    return ElastTensor(x * m.m_D, x * m.m_S);
}

/*---------------------------------------------------------------------------*/
ElastTensor operator*(const ElastTensor& m, Real x)
{
    return ElastTensor(x * m.m_D, x * m.m_S);
}

/*---------------------------------------------------------------------------*/
Tensor2 operator*(const ElastTensor& m1, Tensor2 m2)
{
    Tensor2 m;
    for (int i = 0; i < 6; i++)
    {
        Real vi = 0.;
        for (int j = 0; j < 6; j++) vi += m1(i,j) * m2.m_vec[j];
        m.m_vec[i] = vi;
    }
    return m;
}

/*---------------------------------------------------------------------------*/
Real trace(const ElastTensor& m)
{
    return trace(m.m_D) + trace(m.m_S);
}

/*---------------------------------------------------------------------------*/
ElastTensor transpose(const ElastTensor& m)
{
    return ElastTensor(matrix3x3Transpose(m.m_D), matrix3x3Transpose(m.m_S));
}

/*---------------------------------------------------------------------------*/
const int ipermu[3][3] = { {1,2,5},{2,0,4},{0,1,3} };
const int   NHISTHUJ = 24, // nb of internal variables (history) for Hujeux
	        NPROPHUJ = 25; // nb of const properties (user data) for Hujeux

//=================================================================================================================//
//=================================================================================================================//
HujeuxLaw::HujeuxLaw() 
{
    initConst();
}
//=================================================================================================================//
/**/


//=================================================================================================================//
//=================================================================================================================//
HujeuxLaw::HujeuxLaw(const HujeuxLaw& h)
{
	init(h.m_param);
}
//=================================================================================================================//
/**/

//=================================================================================================================//
// Initialization performed when reading user parameters at the beginning of each step for a given integration point
//=================================================================================================================//
void HujeuxLaw::initConst()
{
    nmecdev = 3;
    nmeciso = 1;
    inc = 0.;
    im = jm = km = lm = 0;
    facinc = 0.2;
    iecoul = 1;
    incmax = 20;
    incmin = 1. / incmax;
    indaux = 0;

	// local variables used during iterations
	m_mu = 0.;
	m_lamda = 0.;
    pref = Pa;
    ptrac = pref * 1.e-12;
    sgncyc = 0.;
    evp = 0.;
	ppp = 0.;
	pc = 0.;
	sinphi = 0.;
	sinpsi = 0.;

    // initializing values of inipl/ipl tabs (-1=elastic, 1=plastic)
    // default = on yield surface
    for (int i = 0; i < 4; i++)
    {
        inipl[i] = 1;
        ipl[i] = 1;
        lambdap[i] = 0.;
    }
    iipl = 0;

    for (int i = 0; i < 3; i++)
    {
        vn[i] = Real2::zero();
        sigb[i] = Real2::zero();
    }

    for (int i = 0; i < 4; i++)
    {
        ray[i] = Real2::zero();
        for (int j = 0; j < 6; j++)
        {
            Phi[i][j] = 0.;
            Psi[i][j] = 0.;
            CPsi[i][j] = 0.;
        }
    }
}
//=================================================================================================================//
/**/


//=================================================================================================================//
// Initializing when reading user parameters at the beginning of each step for a given integration point
//=================================================================================================================//
void HujeuxLaw::init(const dvector& param)
{
    m_param.assign(param.begin(),param.end()); // tab of size NPROPHUJ
    nmecdev = 3;
    nmeciso = 1;
    inc = 0.;
    im = jm = km = lm = 0;
    facinc = m_param[20];
    iecoul = (int)m_param[21];
    incmax = (int)m_param[22];
    incmin = 1. / incmax;

	// local variables used during iterations
	m_mu = m_param[1];
	m_lamda = m_param[0] - 2 * m_mu / 3.;
    pref = Pa;
    ptrac = pref * 1.e-12;
    sgncyc = 0.;
	ppp = 0.;
	pc = m_param[6];
	auto	phi = m_param[3]; // already in radians (converted when reading data)
	auto	psi = m_param[4]; // already in radians
	sinphi = sin(phi);
	sinpsi = sin(psi);

    // initializing values of inipl/ipl tabs (-1=elastic, 1=plastic)
    // default = on yield surface
    for (int i = 0; i < 4; i++)
    {
        inipl[i] = 1;
        ipl[i] = 1;
        lambdap[i] = 0.;
    }
    iipl = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            Phi[i][j] = 0.;
            Psi[i][j] = 0.;
            CPsi[i][j] = 0.;
        }
    }

	for (int i = 0; i < 3; i++)
	{
	    vn[i] = Real2::zero();
    	sigb[i] = Real2::zero();
	}
	evp = 0.;
}
//=================================================================================================================//
/**/

	
//=================================================================================================================//
// reading the 24 Hujeux Law parameters from a given .input file 
//=================================================================================================================//	        
bool HujeuxLaw::readParameters(const string& name)
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
	// Hujeux 3D model parameters :
    // 0-Ki  1-Gi     2-ne      3-phi(°)  4-psi(°)  5-beta    6-pci    7-amon
    // 8-b   9-acyc  10-alfa   11-rayela 12-rayhys 13-raymbl 14-cmon  15-d
    // 16-ccyc  17-dltela   18-xkimin   19-m   20-facinc   21-iecoul  22-incmax
    // 23-Kaux  24-Gaux
	// =================================================================================
	dvector param(NPROPHUJ, 0.);
	for (int i = 0; i < NPROPHUJ; i++)
		JeLis >> param[i];
	JeLis.getline(c, MAXCAR); // "\n"

	MonFichier.close();

#ifdef _DEBUG
	if (param[3] > 0.) param[3] *= -1;// phi is negative in Hujeux 3D
	if (param[4] > 0.) param[4] *= -1;// psi also
	if (fabs(param[3]) < fabs(param[4])) param[4] = param[3];
	if (param[2] > 1.) param[2] = 1.; // ne
	if (param[5] > 0.) param[5] *= -1; // beta is negative in Hujeux 3D
	if (param[8] > 1.) param[8] = 1.; // b
#endif

	param[3] *= RAD;
	param[4] *= RAD;

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
//=================================================================================================================//
void HujeuxLaw::set_ipl(const int& iiplval)
{
	iipl = iiplval;
	ipl[3] = iipl / 125;
	ipl[2] = (iipl - 125 * ipl[3]) / 25;
	ipl[1] = (iipl - 25 * ipl[2] - 125 * ipl[3]) / 5;
	ipl[0] = (iipl - 5 * ipl[1] - 25 * ipl[2] - 125 * ipl[3]);
	ipl[0] -= 2;
	ipl[1] -= 2;
	ipl[2] -= 2;
	ipl[3] -= 2;
}
//=================================================================================================================//
/**/


//=================================================================================================================//
// Computing elastic constitutive (4th order) tensor considering nonlinear elasticity p = current effective
// mean stress at integration point (=I1/3 with I1, 1st stress invariant)
//=================================================================================================================//
void HujeuxLaw::computeElastTensor(const Real& p)
{
	auto K = m_param[0];
	m_mu = m_param[1];
	auto ne = m_param[2];
    Real	fac = 1.;

	if (p < 0.) fac = pow(p / pref, ne);
	K *= fac;
	m_mu *= fac;
	if (K < 0.) K *= -1.;
	if (m_mu < 0.) m_mu *= -1.;
	m_lamda = K - 2 * m_mu / 3.;
	m_elast_tensor = ElastTensor(m_lamda, m_mu);
}
//=================================================================================================================//
/**/


//=================================================================================================================//
// Computing tangent constitutive (4th order) tensor considering nonlinear elasticity
//=================================================================================================================//
void HujeuxLaw::computeTangentTensor(const Tensor2& sig)
{
    auto p = trace(sig)/3.;
    
	auto ne = m_param[2];
    Real	fac = 1.;
    auto Kaux = m_param[23];
    auto Gaux = m_param[24];

	if (p < 0.) fac = pow(p / pref, ne);
	Kaux *= fac;
	Gaux *= fac;
	if (Kaux < 0.) Kaux *= -1.;
	if (Gaux < 0.) Gaux *= -1.;
	auto lamda = Kaux - 2 * Gaux / 3.;

	ElastTensor t(lamda, Gaux);

	for (int i = 0; i < 6; i++)
	    for (int j = 0; j < 6; j++)
	        m_tangent_tensor[i][j] = t(i,j);        
}
//=================================================================================================================//
/**/


//=================================================================================================================//
//=================================================================================================================//
void HujeuxLaw::initHistory(dvector* histab)
{
    evp = histab->front();

	int ii = 1, jj = 15;
    for (auto & r : ray)
    {
        for (int j = 0; j < 2; j++)
        {
            r[j] = (*histab)[ii + j];
        }
        ii += 2;
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            vn[i][j] = (*histab)[ii + j];
            sigb[i][j] = (*histab)[jj + j];
        }
        ii += 2;
        jj += 2;
    }
    pldiso = (*histab)[jj++];
    set_ipl(histab->back());
}
//=================================================================================================================//
/**/




//=================================================================================================================//
// sig = stress tensor at the end of previous converged time step
// histab : tab containing internal variables(=hardening parameters) stored on each integration point(size = NHISTHUJ)
// 
//=================================================================================================================//
bool HujeuxLaw::initState(const Tensor2& sig, dvector* histab)
{
  if (sig == Tensor2::zero() || histab == nullptr) return true;
	auto beta = m_param[5];
	pc = m_param[6] * exp(beta * evp);
	initHistory(histab);

	// initialisation des mecanismes
	// mecanismes deviatoires
	bool stop = false;
	
	for (int k = 0; k < nmecdev && !stop; k++)
	{
		im = ipermu[k][0];
		jm = ipermu[k][1];
		lm = ipermu[k][2];
		km = k;
		stop = initMecdev(sig,inipl[km], ipl[k], vn[k], sigb[k], ray[k]);
	}

	// mecanisme isotrope
	if (!stop) stop = initMeciso(sig, inipl[3], ipl[3], ray[3]);

	if (stop)
	{
		filebuf ficherr;
		ficherr.open(ferrlog.c_str(), ios::out | ios::app);
		ostream oserr(&ficherr);
		oserr << "Warning : error while initializing mechanisms - Stop!" << endl;
		ficherr.close();
		return true;
	}

	iipl = (ipl[0] + 2) + 5 * (ipl[1] + 2) + 25 * (ipl[2] + 2) + 125 * (ipl[3] + 2);
	histab->back() = iipl;
	histab->front() = evp;

	int ii = 1;
	int jj = 15;
	for (auto & r : ray)
	{
		for (int j = 0; j < 2; j++)
		{
			(*histab)[ii + j] = r[j];
		}
		ii += 2;
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			(*histab)[ii + j] = vn[i][j];
			(*histab)[jj + j] = sigb[i][j];
		}
		ii += 2;
		jj += 2;
	}
	(*histab)[jj++] = pldiso;
	
	return stop;
}
//=================================================================================================================//
/**/


//=================================================================================================================//
//=================================================================================================================//
bool HujeuxLaw::initMecdev(const Tensor2& sig, int& iniplk, int& iplk, Real2& vnk, Real2& sbk, Real2& rayk)
{
	auto	pk = 0.5 * (sig.m_vec[im] + sig.m_vec[jm]);
    auto    s1 = 0.5 * (sig.m_vec[im] - sig.m_vec[jm]);
    auto    s2 = sig.m_vec[lm];
    auto    qk = sqrt(s1 * s1 + s2 * s2);
    auto    rayela = m_param[11];
    auto    b = m_param[8];
    bool	stop = false;

	ppp = pk;
	if (iecoul < 0) ppp = trace(sig) / 3.;

	auto  facpk = sinphi * (1. - b * log(ppp / pc));
    auto  fmk = facpk * pk;
    auto  raykk = qk / fmk;

    if (abs(iniplk) == 2)
	{
		// cannot start as cyclic
		iniplk = 1;
	}

	if (iniplk == 1)
	{
		if (raykk > 1.)
		{
			filebuf ficherr;
			ficherr.open(ferrlog.c_str(), ios::out | ios::app);
			ostream oserr(&ficherr);
            snprintf(szout, MAXBUFFER, "Starting out of dev yield surface %d!", km + 1);             ///////// CHECK CHECK
			oserr << szout << endl;
			ficherr.close();
			raykk = 1.;
//			stop = true;
		}

		if (raykk < rayela)
		{
			rayk[0] = rayela;
			iplk = -1;
		}
		else
		{
			rayk[0] = raykk;
			iplk = iniplk;
		}
	}
	else if (raykk <= 1.05 * rayela)
	{
		rayk[0] = rayela;
		iplk = iniplk;
	}
	else
	{
		filebuf ficherr;
		ficherr.open(ferrlog.c_str(), ios::out | ios::app);
		ostream oserr(&ficherr);
        snprintf(szout, MAXBUFFER, "Starting as elastic impossible when dev mob degree %d > rayela!", km + 1);
		oserr << szout << endl;
		ficherr.close();
		stop = true;
	}

	return stop;
}
//=================================================================================================================//
/**/


//=================================================================================================================//
//=================================================================================================================//
bool HujeuxLaw::initMeciso(const Tensor2& sig, int& inipl4, int& ipl4, Real2& delta)
{
	auto dltela = m_param[17];
	auto d = m_param[15];
    auto p = trace(sig) / 3.;
    auto faciso = -d * pc;
    auto rayiso = -p / faciso;
    bool stop = false;

	pldiso = p / pc;

	if (abs(inipl4) == 2)
	{
		// cannot start as cyclic
		inipl4 = 1;
	}

	if (inipl4 == 1)
	{
		if (rayiso > 1.)
		{
			filebuf ficherr;
			ficherr.open(ferrlog.c_str(), ios::out | ios::app);
			ostream oserr(&ficherr);
			oserr << "Starting out of isotropic yield surface!" << endl;
			ficherr.close();
//			stop = true;
		}

		if (rayiso < dltela)
		{
			delta[0] = dltela;
			ipl4 = -1;
		}
		else
		{
			delta[0] = rayiso;
			ipl4 = inipl4;
		}
	}
	else if (rayiso <= 1.05 * dltela)
	{
		delta[0] = dltela;
		ipl4 = inipl4;
	}
	else
	{
		filebuf ficherr;
		ficherr.open(ferrlog.c_str(), ios::out | ios::app);
		ostream oserr(&ficherr);
		oserr << "Starting as elastic impossible when isotropic mob degree > rayela!" << endl;
		ficherr.close();
		stop = true;
	}
	return stop;
}
//=================================================================================================================//
/**/



//=================================================================================================================//
//=================================================================================================================//
void HujeuxLaw::ComputeMecdev(const Tensor2& sig, const Tensor2& dsig, Real* Phik, Real* Psik, Real* CPsik, Real& seuilk,
                              Real& fidsig, Real& hray, Real& xlray, int& iplk, int& jplk, Real2& vnk, Real2& sbk, Real2& rayk)
{
	Real2	c, cred, s, si;
	auto	pci = m_param[6];
    auto    b = m_param[8];
    auto    beta = m_param[5];
    auto    alfa = m_param[10];
    auto    m = m_param[19];
    auto    rayela = m_param[11];
    auto    rayhys = m_param[12];
    auto    raymbl = m_param[13];
    auto    amon = m_param[7];
    auto    acyc = m_param[9];
    auto    da = amon - acyc;
    auto    pk = 0.5 * (sig.m_vec[im] + sig.m_vec[jm]);
    auto    tracesig = trace(sig);
    auto    p = tracesig / 3.;

    s[0] = 0.5 * (sig.m_vec[im] - sig.m_vec[jm]);
	s[1] = sig.m_vec[lm];
	si = s;

	ppp = pk;
	if (iecoul < 0) ppp = p;

	if (ppp >= 0.)
	{
		// traction issue but not treated yet (additional iterative problem to consider here)...
		ppp = ptrac;
	}
	// Accuracy issue
	else if (ppp >= -1.e-7) ppp = -1.e-7;

	auto	qk = s.norm();
    auto    qkc = qk;
    auto    facpk = sinphi * (1. - b * (log(-ppp) - log(-pci) - beta * evp));
    auto    fmk = facpk * pk;
    auto    raym = rayk[0];
    auto    rayc = rayk[1];
    auto    raykk = raym;
    auto    fmkray = fmk * raykk;
    Real    cmod = 0.,
            fachray = 1.,
            raydum = 0.;

    // former cyclic yield surface active: testing if monotonous surface is reached
	seuilk = qk - fmkray;

	// Accuracy issue
	if (fabs(1. - qk / fmkray) < EPS) seuilk = 0.;

	if (jplk != 1)
	{
		if (seuilk < 0.)
		{
			// remaining cyclic: test if intersecting with monotonous surface
			// cred: reduced coordinates of the circle center
			fmkray = fmk * rayc;
			
			for (int i = 0; i < 2; i++) cred[i] = sbk[i] - vnk[i] * rayc;
			cmod = cred.norm();

			if ((cmod + rayc - raym) / raym >= 1.e-4)
			{
				// crossing the yield surface => computing:
				// sb = intersecting monotonous and cyclic surfaces (fixed point)
				// vn = extern normal to both surfaces at sb
				// new circle ray for the monotonous surface (tangent)
				if (rayc < raym)
				{
					raydum = rayc + cmod;
					raym = min_(Real(1.), raydum);
					rayk[0] = raym;
					raykk = raym;
				}
				for (int i = 0; i < 2; i++)
				{
					vnk[i] = cred[i] / cmod;
					sbk[i] = vnk[i] * raym;
				}
			}

			// computing cyclic yield surface seuilk
      c = cred * fmk;
			s -= c;
			qkc = s.norm();
			seuilk = qkc - fmkray;

			// Accuracy issue
			if (fabs(1. - qkc / fmkray) < EPS) seuilk = 0.;

		}
		else
		{
			// historical monotonous yield surface is reached (active) => switching between cyclic - monotonous
			iplk = 1;
			jplk = 1;
		}
	}

	// computing df/ds (cyclic or monotonous loading case)
	Real2	dfds;
	double	dfdsmod = 0.;

	if (qkc > fmkray * 0.01)
	{
		// standard case: df/ds = direction of qkc gradient
		dfds = s / qkc;
	}
	else
	{
		// special case: we are close to the circle center
		// df/ds = unit vector parallel to dsig (deviator s)
		dfds[0] = 0.5 * (dsig.m_vec[im] - dsig.m_vec[jm]);
		dfds[1] = dsig.m_vec[lm];
		dfdsmod = dfds.norm();

		// if increment of stress is too small, mechanism is not active
		if (dfdsmod < 1.e-4 * fmk)
		{
			// remaining elastic w/o changing loading sign
			iplk = -jplk;
			return;
		}
		dfds /= dfdsmod;
	}

	if (jplk != 1)
	{
		// cyclic loading case only
		raykk = rayc + dfds[0] * cred[0] + dfds[1] * cred[1];
		//		double un = 1. + 1.e-12;
		//		fachray = 1./(un - (dfds[0]*vn[0] + dfds[1]*vn[1]));

		double	prod = 1.0 - (dfds[0] * vnk[0] + dfds[1] * vnk[1]),
				zero = 1.e-12;

		//		if (fabs(prod) < zero) prod = 1.;
		if (fabs(prod) < zero) prod = zero;
		fachray = 1. / prod;
	}

	// monotonous or cyclic case: computing Phik = (dfk/dsig, -dfk/devp)
	double phiv2 = 0., phid2 = 0.;
	if (iecoul < 0)
	{
		double dfdevp = b * pk * raykk * sinphi;
		Phik[km] = dfdevp / tracesig;
		Phik[3] = dfdevp * beta;
		phiv2 = -0.5 * facpk * raykk + Phik[km];
	}
	else
	{
		Phik[km] = 0.;
		double temp = sinphi * b * raykk;
		phiv2 = 0.5 * (temp - facpk * raykk);
		Phik[3] = temp * pk * beta;
	}
	
	phid2 = 0.5 * dfds[0];
	Phik[im] = phid2 + phiv2;
	Phik[jm] = -phid2 + phiv2;
	Phik[4] = dfds[1];

	// Computing RHS of the system to be solve for plastic multipliers derivation (lambda)
	// fidsig = (dfdsig)T . dsig
	fidsig = Phik[im] * dsig.m_vec[im] + Phik[jm] * dsig.m_vec[jm] + Phik[km] * dsig.m_vec[km] + Phik[4] * dsig.m_vec[lm];

	double	prkinc = fmk / (fabs(fidsig) + 1.e-12) * facinc;

	if (prkinc < incmin) prkinc = incmin;
	if (prkinc < inc) inc = prkinc;

	double actif = seuilk + fidsig * inc;

	// test on unloading/elasticity/loading:
	// actif < 0 and fidsig < 0 et ipl > 0 : unloading
	// actif < 0 and fidsig > 0 : elastic case w/o changing loading direction
	// actif < 0 and ipl < 0 : elastic case with changing loading direction at previous sub-increment
	// actif > 0 : plastic yielding

// Accuracy issue
//	if (fidsig*inc != 0. && fabs(1. + seuilk/(fidsig*inc)) < EPS) actif = 0.;

	if (actif > 0.)
	{
		// plastic yield surface possibly active: computing direction of the plastic strain increment
		// and contributions to the hardening parameters
		iplk = jplk;

		double	alfak = 1., psiv = 0., psiv2 = 0.;
		int		jecoul = abs(iecoul),
				kecoul = jecoul / 10;

		switch (jecoul)
		{
			default:
			case 1: psiv = (sinpsi - (dfds[0] * si[0] + dfds[1] * si[1]) / pk);
				break;

			case 2: psiv = (sinpsi - qkc / pk);
				break;

			case 3: psiv = -sinpsi;
				break;
		}

		if (!(kecoul == 1 && jplk == 1))
		{
			if (rayk[jplk - 1] <= rayhys) alfak = 0.;
			else if (rayk[jplk - 1] > rayhys)
			{
				if (rayk[jplk - 1] < raymbl) alfak = pow((rayk[jplk - 1] - rayhys) / (raymbl - rayhys), m);
			}
		}

		psiv *= alfa * alfak;
		psiv2 = 0.5 * psiv;
		Psik[im] = phid2 + psiv2;
		Psik[jm] = -phid2 + psiv2;
		Psik[lm] = 0.5 * Phik[4];

		double	G2 = 2. * m_mu, lambda2G = m_lamda + G2;

		CPsik[km] = m_lamda * (Psik[im] + Psik[jm]);
		CPsik[im] = lambda2G * Psik[im] + m_lamda * Psik[jm];
		CPsik[jm] = m_lamda * Psik[im] + lambda2G * Psik[jm];
		CPsik[4] = G2 * Psik[lm];
		CPsik[3] = psiv;

		double ak = acyc + da * alfak;
		hray = pow(1. - rayk[jplk - 1], 2) / ak;
		xlray = hray * fachray;
		hray *= fmk;
	}
	else if (!(iplk < 0 || fidsig >= 0.))
	{
		// Unloading (direction changed):
		// => possibly putting back the monotonous yield surface as tangent to this one
		// => initializing the new cyclic yield surface
		// (vn(1), vn(2)) : unit extern normal to the yield surface previously active
		// (sb(1), sb(2)) : reduced coord. at fixed point on the cyclic yield surface
		// rayela = ray of the elastic cyclic domain (disk)
		if (iplk == 1)
		{
			double dum = max_(rayk[0], qk / fmk);
			rayk[0] = min_(dum, 1.);
		}
		iplk = -2;
		jplk = 2;

		for (int ii = 0; ii < 2; ii++)
		{
			vnk[ii] = dfds[ii];
			sbk[ii] = si[ii] / fmk;
		}
		rayk[1] = rayela;
		//		fmkray = fmk*rayela;

		prkinc = fmk / fabs(fidsig) * facinc;
		if (prkinc < incmin) prkinc = incmin;
		if (prkinc < inc) inc = prkinc;
	}	
}
//=================================================================================================================//
/**/


//=================================================================================================================//
//=================================================================================================================//
void HujeuxLaw::ComputeMeciso(const Tensor2& sig, const Tensor2& dsig, Real* Phic, Real* Psic, Real* CPsic, Real& seuilc, Real& fidsig,
                              Real& hray, Real& xldelta, int& ipl4, int& jpl4, Real2& delta)
{
	double	d = m_param[15],
			beta = m_param[5],
			dltela = m_param[17],
			cmon = m_param[14],
			ccyc = m_param[16],
			xkimin = m_param[18],
			cc = cmon - ccyc,
			p = trace(sig) / 3.,
			dm = delta[0],
			dc = delta[1],
			faciso = -d * pc,
			facdlt = faciso * dm,
			sgnnew = -1., pcyc = 0.;

	// former cyclic yield surface active: testing if monotonous surface is reached
	seuilc = -p - facdlt;

	if (fabs(1. + p / facdlt) < EPS) seuilc = 0.;

	if (jpl4 != 1)
	{
		if (seuilc < 0.)
		{
			// remaining cyclic
			facdlt = faciso * dc;
			sgnnew = 1.;
			pcyc = p - pldiso * pc;
			if (pcyc < 0.)
			{
				pcyc *= -1.;
				sgnnew = -1.;
			}
			seuilc = pcyc - facdlt;
		}
		else
		{
			// historical monotonous yield surface is reached (active) => switching between cyclic - monotonous
			ipl4 = 1;
			jpl4 = 1;
		}
	}
	Phic[0] = sgnnew / 3.;
	Phic[1] = Phic[0];
	Phic[2] = Phic[0];

	// trick: if jpl = 1, monotonous formulation; if jpl = 2, cyclic
	// Phik[3] = -df/devp
	int jpl1 = 1 - jpl4;
	Phic[3] = -pc * beta * (d * delta[jpl4 - 1] + jpl1 * sgnnew * pldiso);

	fidsig = sgnnew * trace(dsig) / 3.;

	double	prkinc = facdlt / (fabs(fidsig) + 1.e-12) * facinc;

	if (prkinc < incmin) prkinc = incmin;
	if (prkinc < inc) inc = prkinc;

	double actif = seuilc + fidsig * inc;

	// test on unloading/elasticity/loading:
	// actif < 0 and fidsig < 0 et ipl > 0 : unloading
	// actif < 0 and fidsig > 0 : elastic case w/o changing loading direction
	// actif < 0 and ipl < 0 : elastic case with changing loading direction at previous sub-increment
	// actif > 0 : plastic yielding
	if ((actif - 0.001 * p) > 0.)
	{
		// plastic yield surface possibly active: computing direction of the plastic strain increment
		// and contributions to the hardening parameters
		ipl4 = jpl4;
		Psic[0] = sgnnew / 3.;
		Psic[1] = Psic[0];
		Psic[2] = Psic[0];

		CPsic[0] = 2. * (m_lamda + m_mu) * Psic[0];
		CPsic[1] = CPsic[0];
		CPsic[2] = CPsic[0];
		CPsic[3] = sgnnew;

		xldelta = pow(1. - delta[jpl4 - 1], 2);
		if (xldelta < xkimin) xldelta = xkimin;

		xldelta *= pref / pc / cmon;
		if (jpl4 == 2) xldelta *= cmon / ccyc;
		hray = -xldelta * pc * d;
	}
	else if (ipl4 < 0)
	{
		// remaining elastic w/o changing loading direction
		ipl4 = -jpl4;
	}
	else
	{
		// Unloading (direction changed):
		// => possibly putting back the monotonous yield surface as tangent to this one
		// => initializing the new cyclic yield surface: pldiso = p/pc at changing direction point
		// dltela = ray of the elastic cyclic domain (disk)
		// need to verify that the point where changing direction occurs remains inside the monotonous yield surface
		ipl4 = -2;
		jpl4 = 2;
		pldiso = p / pc;
		delta[1] = dltela;
		dc = delta[1];
		facdlt = faciso * dc;
		prkinc = facdlt / (fabs(fidsig) + 1.e-12) * facinc;

		if (prkinc < incmin) prkinc = incmin;
		if (prkinc < inc) inc = prkinc;
	}
}
//=================================================================================================================//







//=================================================================================================================//
// Computing stresses at step n+1 (small strain formulation)
// Deviatoric plane mechanisms : mec1=YZ    mec2=ZX    mec3=XY
//=================================================================================================================//
void HujeuxLaw::ComputeStress(dvector* histab,Tensor2& sig, Tensor2& eps, Tensor2& epsp, Tensor2& dsig,
        const Tensor2& deps,bool is_converge)
{
	Real	resinc = 1., // portion d'increment restant a calculer
			beta = m_param[5],
			pci = m_param[6],
			n = m_param[2],
			b = m_param[8],
			p = 0.,
			factmp = 0., fac = 0., actif = 0.,
			seuil[4], fidsig[4], hray[4], xlray[4],
			daux[6][6];
	auto hh1 = new Real*[4];
	auto hb = new Real[4];


	initHistory(histab);
	auto evp0 = evp;

	int	incfai = 0,// nb of sub-icrements done during iterative main loop
		i = 0, j = 0, k = 0, ii = 0, jj = 0, lmec = 0, kmec = 0, l = 0,
		nmec = 0, jpl[4], imec[4], jmec[4], iv = 0;
	
	Tensor2 sign(sig), epspn(epsp), depsp;

	inc = 0.;
	incmin = 1./incmax;
	for (i = 0; i < 4; i++)
	{
		hh1[i] = new Real[4];
		hray[i] = 0.;
		seuil[i] = 0.;
		fidsig[i] = 0.;
		xlray[i] = 0.;
	}

	Real depsv = trace(deps);
	
	computeTangentTensor(sig);
	
	// subincrements loop start
	do
	{
		ii = 0;

		inc = resinc;
		incfai++;
		if (incmin > resinc) incmin = resinc;

		// if no yield surface (=mechanism) is active, restarting the loop with a bigger increment
		if (incfai == 1 || (incfai > 1 && nmec > 0))
		{
			pc = pci * exp(beta * evp);
			p = trace(sig) / 3.;
			factmp = 50. * p / pc;
			fac = factmp;
			if (factmp < 0.1) fac = 0.1;
			if (fac < 1.) inc *= fac;
			if (inc < incmin) inc = incmin;
		}
		
		if (p >= 0.) p = ptrac;
		else if (p >= -1.e-7) p = -1.e-7;

		computeElastTensor(p);

		auto K = m_lamda + 2. * m_mu / 3.;
		dsig = m_elast_tensor * deps;

		// treating possible traction or liquefaction (not done yet)

		// determining active yield surfaces and terms depending on stresses and hardening

		// Computing vectors Phi, Psi, CPsi and yield surface for each plane mechanism
		// Phi = (df/dsig, -df/devp)
		// Psi = dgk/dsig
		// CPsi = C(K,G) * Psi

		// Deviatoric mechanisms
		for (k = 0; k < nmecdev; k++)
		{
			im = ipermu[k][0];
			jm = ipermu[k][1];
			lm = ipermu[k][2];
			km = k;
			jpl[k] = abs(ipl[k]);
			for (i = 0; i < 6; i++)
			{
				Phi[k][i] = 0.;
				Psi[k][i] = 0.;
				CPsi[k][i] = 0.;
			}

			ComputeMecdev(sig,dsig,Phi[k], Psi[k], CPsi[k], seuil[k], fidsig[k], hray[k], xlray[k], ipl[k],
				jpl[k], vn[k], sigb[k], ray[k]);
		}

		// Isotropic mechanism
		for (i = 0; i < 6; i++)
		{
			Phi[3][i] = 0.;
			Psi[3][i] = 0.;
			CPsi[3][i] = 0.;
		}
		jpl[3] = abs(ipl[3]);

		ComputeMeciso(sig,dsig,Phi[3], Psi[3], CPsi[3], seuil[3], fidsig[3], hray[3], xlray[3], ipl[3],
			jpl[3], ray[3]);

		// dividing into sub-increments for elasticity
		factmp = depsv;

		auto dum = fabs(factmp * inc * K * n / p / facinc);

		if (dum > 1.) inc /= dum;
		if (inc < incmin) inc = incmin;

		// checking if dev. mechanisms are active for this sub-increment
		nmec = 0;

		for (i = 0; i < 4; i++)
		{
			imec[i] = 0;
			jmec[i] = 0;// used to compute tangent operator
			hb[i] = 0.;
			for (j = 0; j < 4; j++)
			{
				hh1[i][j] = 0.;
			}
		}

		for (k = 0; k < nmecdev + nmeciso; k++)
		{
			if (ipl[k] > 0.)
			{
				actif = seuil[k] + fidsig[k] * inc;

				// Accuracy issue
				//	if (fidsig[k]*inc != 0. && fabs(1. + seuil[k]/(fidsig[k]*inc)) < EPS) actif = 0.; 

				if (k < nmecdev && actif <= 0.)
					ipl[k] = -jpl[k];

				else
				{
					// isotropic yield surface always assumed active (original hujeux model...)
					// computig RHS
					hb[nmec] = actif;
					imec[nmec] = k;
					jmec[k] = nmec++;
				}
			}
		}

		// building the system to be inverted
		if (nmec > 0)
		{
		
		
			int kk = 0;
			for (i = 0; i < nmec; i++)
			{
				k = imec[i];
				hh1[i][i] = hray[k] + Phi[k][4] * CPsi[k][4];

				for (j = 0; j < nmec; j++)
				{
					kk = imec[j];
					for (int iii = 0; iii < 4; iii++)
					{
						hh1[i][j] += Phi[k][ii] * CPsi[kk][ii];
					}
				}
			}

			// solving for lambdap by gauss elimination
			Real lpi = 0.;
			bool stop = false;
			int niter = 0, maxit = incmax / 2;
			
			do
			{
				niter++;
	
				for (i = 0; i < 4; i++) lambdap[i] = 0.;
			    ///////////////////////////////////////// CHANGE WITH LAPACK ////////////////////////////////////				
				gauss(hh1, hb, lambdap, nmec);
			    ///////////////////////////////////////// CHANGE WITH LAPACK ////////////////////////////////////				

				// test on lambdap (> 0)
				j = 0;
				for (i = 0; i < nmec; i++)
				{
					lpi = lambdap[i];

					// Accuracy issue
					// if (fabs(lpi) < EPS) lpi = 0.; 

					if (lpi >= 0.) j++;
					else
					{
						if (niter < maxit && lpi < -1.e-7)
						{
							j--;
							hh1[i][i] = 1.e20;
							hb[i] = 0.;
						}
						else
						{
							lambdap[i] = 0.;
							j++;
						}
					}
				}
				stop = (j == nmec);
			} while (!stop || niter == maxit / 2);
				
			// computing plastic strain rates and hardening
			dvector dep(6,0.);
			int kpl = 0;
			for (i = 0; i < nmec; i++)
			{
				k = imec[i];
				kpl = ipl[k] - 1;
				lpi = lambdap[i];
				//	if (lpi < -EPS) lpi = 0.;
				evp += lpi * CPsi[k][3];
				ray[k][kpl] += lpi * xlray[k];
				ray[k][kpl] = min_(ray[k][kpl], Real(1.));

				for (j = 0; j < 6; j++)
					dep[j] += lpi * Psi[k][j];
			}

			// Accuracy issue
			if (fabs(evp) < EPS) evp = 0.;
			else
			{
				evp = max_(evp, Real(-1.));
				evp = min_(evp, Real(1.));
			}

			if (indaux == 1 && is_converge)
			{
			    // replace double** with matrix type from existing lib
			    // use inversion fct from existing lib (not implemented here)
			    
			    ///////////////////////////////////////// CHANGE WITH LAPACK ////////////////////////////////////
				auto	hhi = new Real*[4];
				for (i = 0; i <4; i++) 
				{
					hhi[i] = new Real[4];
					for (j = 0; j < 4; j++) hhi[i][j] = hh1[i][j];
				}
				gauss(hhi,hb,hb,nmec);              
			    ///////////////////////////////////////// CHANGE WITH LAPACK ////////////////////////////////////
				
				auto	G2 = 2.*m_mu;

				for (i = 0; i < 6; i++)
				    for (j = 0; j < 6; j++)
				        daux[i][j] = 0.;

				for (ii = 0; ii < nmecdev; ii++)
				{
					for (jj = 0; jj < nmecdev; jj++)
					{
						for (kmec = 0; kmec < nmec; kmec++)
						{
							k = imec[kmec];
							if (k != 3)
							{
								for (lmec = 0; lmec < nmec; lmec++)
								{
									l = imec[lmec];
									if (l != 3)
									{
										daux[ii][jj] += (m_lamda*(Psi[k][0] + Psi[k][1] + Psi[k][2])
														+ G2*Psi[k][ii])*hhi[kmec][lmec]*(m_lamda*(Phi[l][0]
														+ Phi[l][1] + Phi[l][2]) + G2*Phi[l][jj]);
									}
								}
							}
						}
					}
				}

				for (ii = 0; ii < nmecdev; ii++)
				{
					for (jj = nmecdev; jj < 6; jj++)
					{
						for (kmec = 0; kmec < nmec; kmec++)
						{
							k = imec[kmec];
							if (k != 3)
							{
								if ((l = jmec[6 - jj]) != 0)
								{
									daux[ii][jj] += (m_lamda*(Psi[k][0] + Psi[k][1] + Psi[k][2])
													+ G2*Psi[k][ii])*hhi[kmec][l]*G2*Phi[l][4];
								}
							}
						}
					}
				}

				for (ii = nmecdev; ii < 6; ii++)
				{
					for (jj = 0; jj < nmecdev; jj++)
					{
						for (kmec = 0; kmec < nmec; kmec++)
						{
							k = imec[kmec];
							if (k != 3)
							{
								if ((l = jmec[6 - ii]) != 0)
								{
									daux[ii][jj] += (m_lamda*(Phi[k][0] + Phi[k][1] + Phi[k][2])
													+ G2*Phi[k][jj])*hhi[l][kmec]*G2*Psi[l][4];
								}
							}
						}
					}
				}

				if ((l = jmec[1]) != 0)
				{
					daux[3][3] += G2*Phi[2][4]*hhi[l][l]*G2*Psi[2][3];
				}
				if ((l = jmec[2]) != 0)
				{
					daux[4][4] += G2*Phi[1][4]*hhi[l][l]*G2*Psi[1][4];
				}
				if ((l = jmec[0]) != 0)
				{
					daux[5][5] += G2*Phi[0][4]*hhi[l][l]*G2*Psi[0][5];
				}
			}
			

			// computing elastoplastic stresses
			depsp = dep;
			sig -= m_elast_tensor * depsp;
			epsp += depsp;
	
		}
		
		sig += dsig * inc;
		resinc -= inc;
   
	} while (resinc > FTOL);

 
	bool is_plastic = (fabs(evp) >= EPS || norm(epsp.m_vec) >= EPS);	
	 
	if (!is_plastic)
	{

		epsp = epspn;
		evp = evp0;
		sig = sign;
	  p = trace(sig) / 3.;
		if (p >= 0.) p = ptrac;
		else if (p >= -1.e-7) p = -1.e-7;

		computeElastTensor(p);

		dsig = m_elast_tensor * deps;
		sig += dsig;

	}

	if (is_converge)
	{
		computeTangentTensor(sig);

	    // computing tangent elastoplastic stiffness operator
		if (indaux == 1)
		{
			for (i = 0; i < 6; i++)
			{
			    for (j = 0; j < 6; j++)
			    {
			        m_tangent_tensor[i][j] -= daux[i][j];
			    }
			}
		}

		// updating internal variables in histab
		histab->front() = evp;

		ii = 1;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 2; j++)
			{
				(*histab)[ii + j] = ray[i][j];
			}
			ii += 2;
		}

		jj = 15;
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 2; j++)
			{
				(*histab)[ii + j] = vn[i][j];
				(*histab)[jj + j] = sigb[i][j];
			}
			ii += 2;
			jj += 2;
		}
		(*histab)[jj++] = pldiso;

    	iipl = (ipl[0] + 2) + 5 * (ipl[1] + 2) + 25 * (ipl[2] + 2) + 125 * (ipl[3] + 2);
		histab->back() = iipl;
	}	
}
//=================================================================================================================//
/**/

//=================================================================================================================//
// Test class to get number
//=================================================================================================================//
int HujeuxLaw::TestClass() 
{ 

#ifdef DEBUG
  cout << "\n Entering class HujeuxLaw::getNum  from hujeux.cpp "<<endl;
#endif 

    Tensor2 Newobject, Newobject2(Real3(1,1,1),Real3(1,1,1));
    //Tensor2 Newobject3 = Newobject2 + Newobject;
    cout << Newobject2.m_vec[0] << endl;
    cout << Newobject.m_vec[0] << endl;

    Newobject = Newobject2;
    //if (Newobject == Newobject2)
    //cout << Newobject.m_vec[0] << endl;
 return 9999999; 
}
//=================================================================================================================//	        

