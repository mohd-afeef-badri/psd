// LAWDRIVER: constitutive model driver
// OS : Linux - Windows
// Auteur : Evelyne FOERSTER
// Version initiale (1.0) : mai 2020

#if !defined(__HUJEUX_H__)
#define __HUJEUX_H__

#pragma once

extern const int NHISTHUJ, NPROPHUJ;

///////////////////////////////////////////////////////////////////////////////
// External Classes used in this file

class Real3;
class Real3x3;
// see utils.h for definition

//////////////////////////////////////////////////////////////////////////////////////
// class ElastTensor: 4th-order elastic tensor
//
//      _          _
//     |  D      0  |
// C = |            |
//     |            |
//     |  0      S  |
//     |_          _|
//
//      _                                      _
//     | lambda + 2mu   lambda           lambda |  (Real3x3)
// D = |                                        |
//     | lambda       lambda + 2mu       lambda |
//     |                                        |
//     | lambda         lambda     lambda + 2mu |
//     |_                                      _|
//      _           _
//     | mu   0    0 | (Real3x3)
// S = |             |
//     | 0    mu   0 |
//     |             |
//     | 0    0   mu |
//     |_           _|


class ElastTensor
{
	// ***** ATTRIBUTES
public:
	Real3x3	m_D, m_S;

	// ***** CONSTRUCTORS & DESTRUCTOR
public:
	ElastTensor() = default;
	ElastTensor(const Real3x3& /*D*/, const Real3x3& /*S*/);
	ElastTensor(const ElastTensor&);
	ElastTensor(const double&/*lambda*/, const double&/*mu*/);
	~ElastTensor() = default;

	// ***** ACCESS TO ATTRIBUTES

	// ***** IMPLEMENTATION METHODS
public:
	ElastTensor& operator=(const ElastTensor&);
	ElastTensor& operator*=(const double&);
	ElastTensor& operator+=(const ElastTensor&);
	ElastTensor& operator-=(const ElastTensor&);
	ElastTensor operator-() const;

	double		operator()(const int&, const int&) const;
	void		set(const int&, const int&, const double&);
};
/*---------------------------------------------------------------------------*/
extern ElastTensor operator+(const ElastTensor&, const ElastTensor&);
/*---------------------------------------------------------------------------*/
extern ElastTensor operator-(const ElastTensor&, const ElastTensor&);
/*---------------------------------------------------------------------------*/
extern ElastTensor operator*(double, const ElastTensor&);
/*---------------------------------------------------------------------------*/
extern ElastTensor operator*(const ElastTensor&, double);
/*---------------------------------------------------------------------------*/
extern Tensor2 operator*(const ElastTensor&, Tensor2);
/*---------------------------------------------------------------------------*/
extern double trace(const ElastTensor&);
/*---------------------------------------------------------------------------*/
extern ElastTensor transpose(const ElastTensor&);

/////////////////////////////////////////////////////////////////////////////////////////
// class HujeuxLaw: Hujeux 3D constitutive model with 3 deviatoric + 1 isotropic mechanisms
//
class HujeuxLaw
{
	// Member Variables
public:
   dvector m_param{}; // tab with 26 constant law parameters (user data) which will be read on the fly:
                    // 0-Ki  1-Gi     2-ne      3-phi(°)  4-psi(°)  5-beta    6-pci    7-amon
                    // 8-b   9-acyc  10-alfa   11-rayela 12-rayhys 13-raymbl 14-cmon  15-d
                    // 16-ccyc  17-dltela   18-xkimin   19-m   20-facinc   21-iecoul  22-incmax
                    // 23-Kaux  24-Gaux

	Real2   ray[4], sigb[3], vn[3];

	int		nmecdev{},// nb of deviatoric mechanisms
			nmeciso{},// = 1 if isotropic mechanism is active, else 0
			incmax{}, // nb max of sub-increments for law integration (user data)
			indaux,//indicator for auxiliary (tangent) constitutive operator type:
			       // 0 = elastic operator (defaut, symmetric),1 = plastic (unsymmetric)

	//  inipl[4]: tab to intialize plastic yield surfaces (resp. 0-yz 1-zx 2-xy planes & 3-isotropic)
	//  values: 1 = plastic (default value recommended for Hujeux model), -1 = elastic
			inipl[4]{},
		
	//  ipl[4]: tab to indicate local behaviour during iterations (resp. 0-yz 1-zx 2-xy planes & 3-isotropic)
	//  values: 1 = plastic, -1 = elastic
			ipl[4]{},
			iipl{},// global indicator to encapsulate ipl tab values for the 4 mechanisms:
				// = (ipl[0] + 2) + 5*(ipl[1] + 2) + 25*(ipl[2] + 2) + 125*(ipl[3] + 2)
			im{}, jm{}, km{}, lm{}, iecoul{};// local indices for deviatoric mechanisms

	double	Phi[4][6]{}, Psi[4][6]{}, CPsi[4][6]{},

	// Lame coef. depending on mean effective stress p' (=I1/3)
	// computed from a nonlinear function of user data Ki, Gi and exponant ne (nonlinear elasticity)
	        m_lamda{},m_mu{},

			ppp{}, // local effective mean stress (during iterations) used in function F= 1-b*log(ppp/pc):
				// = pk if _ptot=false (contrainte eff. moy. 2D => plan du mecanisme dev. k)
				// = p si _ptot=true (contrainte eff. moy. 3D)
			facinc{}, // factor applied to sub-increment size reduction (default = 0.2)
			inc{},// sub-increment variable size during iterations (fraction of strain increment deps)
			incmin{},// minimum sub-increment size
			sinphi{}, sinpsi{}, pc{}, pref{}, ptrac{}, evp{},// local variables
			pldiso{}, sgncyc{},
			lambdap[4]{};
	
	ElastTensor m_elast_tensor; // elastic constitutive tensor
	double m_tangent_tensor[6][6]; // tangent constitutive tensor used for LHS contribution (implicit solver)

public:

	// Construction/Destruction
public:
	HujeuxLaw();
	HujeuxLaw(const HujeuxLaw&);
	~HujeuxLaw() = default;

	// Attributs

	// Methodes
//	HujeuxLaw& operator=(const HujeuxLaw&);
	
	static double get_dev(const Tensor2&, bool /*is_sig*/ = true);
	void init(const dvector& /*param*/);         
	void initConst();
	void set_ipl(const int& /*iiplval*/);
	void computeElastTensor(const double& /*p*/);
	void computeTangentTensor(const Tensor2& /*sign*/);
	bool initState(const Tensor2& /*sign*/ = Tensor2::zero(), dvector* /*histab*/ = nullptr);
	void initHistory(dvector* /*histab*/);

	void ComputeStress(dvector* /*histab*/, Tensor2& /*sig*/, Tensor2& /*eps*/, Tensor2& /*epsp*/, Tensor2& /*dsig*/, 
		              const Tensor2& /*deps*/,bool /*is_converge*/ = false);

	bool initMecdev(const Tensor2& /*sig*/, int& /*iniplkm*/, int& /*iplk*/, Real2& /*vnk*/, Real2& /*sigbk*/, Real2& /*rayk*/),
		 initMeciso(const Tensor2& /*sig*/, int& /*inipl3*/, int& /*ipl3*/, Real2& /*ray3*/);

	void ComputeMecdev(const Tensor2& /*sig*/, const Tensor2& /*dsig*/, double* /*Phik*/, double* /*Psik*/, double* /*CPsik*/, double& /*seuilk*/,
		double& /*fidsig*/, double& /*hray*/, double& /*xlray*/, int& /*iplk*/, int& /*jplk*/,
		Real2& /*vnk*/, Real2& /*sigbk*/, Real2& /*rayk*/);
	
	void ComputeMeciso(const Tensor2& /*sig*/, const Tensor2& /*dsig*/, double* /*Phic*/, double* /*Psic*/, double* /*CPsic*/, double& /*seuilc*/,
		double& /*fidsig*/, double& /*hray*/, double& /*xldelta*/, int& /*ipl3*/, int& /*jpl3*/, Real2& /*delta*/);

	bool readParameters(const string&);
  int TestClass();	       
};
///////////////////////////////////////////////////////////////////////////////
#endif // __HUJEUX_H__
