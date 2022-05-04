/*!
 * \file   hujeux.h
 * \brief  Header for Hujeux Constitutive Model (ECP family models)
 * \author Evelyne Foerster
 * \date   26/11/2021
 */

#ifndef __HUJEUX_H__
#define __HUJEUX_H__

//#include "nlsoils_utils.hxx"

namespace nlsoils {

    constexpr auto MAXCAR = 500; // Nb max de caracteres sur une ligne;
    constexpr auto MAXBUFFER = 257;

using namespace std;
    class Real2;
    class Real3;
    class Real3x3;

/********************************/
/** Structure for Hujeux3D law **/
/********************************/
    struct Hujeux3D {
        // Variables membres
    public:
        dvector m_param{}; // tab with 26 constant law parameters (user data) which will be read on the fly:
        // 0-Ki  1-Gi     2-ne      3-phi(°)  4-psi(°)  5-beta    6-pci    7-amon
        // 8-b   9-acyc  10-alfa   11-rayela 12-rayhys 13-raymbl 14-cmon  15-d
        // 16-ccyc  17-dltela   18-xkimin   19-m   20-facinc   21-iecoul  22-incmax
        // 23-Kaux  24-Gaux

        Real2 ray[4], sigb[3], vn[3];

        int nmecdev{},// nb of deviatoric mechanisms
        nmeciso{},// = 1 if isotropic mechanism is active, else 0
        incmax{}, // nb max of sub-increments for law integration (user data)
        indaux{},//indicator for auxiliary (tangent) constitutive operator type:
        // 0 = elastic operator (defaut, symmetric),1 = plastic (unsymmetric)
        iipl{},// global indicator to encapsulate ipl tab values for the 4 mechanisms:
        // = (ipl[0] + 2) + 5*(ipl[1] + 2) + 25*(ipl[2] + 2) + 125*(ipl[3] + 2)
        im{}, jm{}, km{}, lm{}, iecoul{};// local indices for deviatoric mechanisms

        //  inipl[4]: tab to intialize plastic yield surfaces (resp. 0-yz 1-zx 2-xy planes & 3-isotropic)
        //  values: 1 = plastic (default value recommended for Hujeux model), -1 = elastic
        iarray4 inipl{},

        //  ipl[4]: tab to indicate local behaviour during iterations (resp. 0-yz 1-zx 2-xy planes & 3-isotropic)
        //  values: 1 = plastic, -1 = elastic
        ipl{};

        Real Phi[4][6]{}, Psi[4][6]{}, CPsi[4][6]{},
        // Lame coef. depending on mean effective stress p' (=I1/3)
        // computed from a nonlinear function of user data Ki, Gi and exponant ne (nonlinear elasticity)
        m_lamda{}, m_mu{},

                ppp{}, // local effective mean stress (during iterations) used in function F= 1-b*log(ppp/pc):
        // = pk if _ptot=false (contrainte eff. moy. 2D => plan du mecanisme dev. k)
        // = p si _ptot=true (contrainte eff. moy. 3D)
        facinc{}, // factor applied to sub-increment size reduction (default = 0.2)
        inc{},// sub-increment variable size during iterations (fraction of strain increment deps)
        incmin{},// minimum sub-increment size
        sinphi{}, sinpsi{}, pc{}, pref{}, ptrac{}, evp{},// local variables
        pldiso{}, sgncyc{};
        darray4 lambdap{};

        ElastTensor m_elast_tensor{}; // elastic constitutive tensor
        Real m_tangent_tensor[6][6]{}; // tangent constitutive tensor used for LHS contribution (implicit solver)

    public:

        // Construction/Destruction
    public:
        Hujeux3D();

        explicit Hujeux3D(const dvector &Param, bool isdrained = true);

        Hujeux3D(const Hujeux3D &);

        ~Hujeux3D() = default;

        // Implementation
//	static Real get_dev(const Tensor2&, bool /*is_sig*/ = true);
        void init(const dvector & /*param*/);

        void initConst();

        void set_ipl(const int & /*iiplval*/);

        void computeElastTensor(const Real & /*p*/);

        void computeTangentTensor(const Tensor2 & /*sign*/);

        bool initState(const Tensor2 & /*sign*/ = Tensor2::zero(), dvector * /*histab*/ = nullptr);

        void initHistory(dvector * /*histab*/);

        void ComputeStress(dvector * /*histab*/, Tensor2 & /*sig*/, Tensor2 & /*eps*/, Tensor2 & /*epsp*/,
                           Tensor2 & /*dsig*/,
                           const Tensor2 & /*deps*/, bool /*is_converge*/ = false);

        bool initMecdev(const Tensor2 & /*sig*/, int & /*iniplkm*/, int & /*iplk*/, Real2 & /*vnk*/, Real2 & /*sigbk*/,
                        Real2 & /*rayk*/),
                initMeciso(const Tensor2 & /*sig*/, int & /*inipl3*/, int & /*ipl3*/, Real2 & /*ray3*/);

        void ComputeMecdev(const Tensor2 & /*sig*/, const Tensor2 & /*dsig*/, Real * /*Phik*/, Real * /*Psik*/,
                           Real * /*CPsik*/, Real & /*seuilk*/,
                           Real & /*fidsig*/, Real & /*hray*/, Real & /*xlray*/, int & /*iplk*/, int & /*jplk*/,
                           Real2 & /*vnk*/, Real2 & /*sigbk*/, Real2 & /*rayk*/);

        void ComputeMeciso(const Tensor2 & /*sig*/, const Tensor2 & /*dsig*/, Real * /*Phic*/, Real * /*Psic*/,
                           Real * /*CPsic*/, Real & /*seuilc*/,
                           Real & /*fidsig*/, Real & /*hray*/, Real & /*xldelta*/, int & /*ipl3*/, int & /*jpl3*/,
                           Real2 & /*delta*/);

        bool readParameters(const string &);

        int TestClass();
    };

} // end namespace nlsoils

///////////////////////////////////////////////////////////////////////////////
#endif // __HUJEUX_H__
