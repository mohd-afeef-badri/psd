//*-------------------------------------------------------------------------------------*/
// Drucker-Prager Constitutive Model (linear elasticity, no strain hardening)
// Author: Evelyne FOERSTER
// Initial Version: July 2020
//*-------------------------------------------------------------------------------------*/

#ifndef DRUCKERPRAGER_H
#define DRUCKERPRAGER_H

#pragma once
///////////////////////////////////////////////////////////////////////////////
// External Classes used in this file

class Real2;
class Real3;
class Real3x3;
class Tensor2;
// see utils.h for definition

/////////////////////////////////////////////////////////////////////////////////////////
// class DruckerPragerLaw: standard constitutive model (linear elasticity+isotropy, no hardening)
//
class DruckerPragerLaw
{
    // Member Variables
public:
    dvector m_param{}; // tab with 7 constant law parameters (user data) which will be read on the fly:
    // 0-Ki  1-Gi 2-phi(°)  3-psi(°)  4-cohesion (Pa) 5-incmax 6-indaux
//  Internal variables for this law:
//  0-is_plastic : boolean to know whether the point was previously in the plastic domain

    int		incmax{}, // nb max of sub-increments for law integration (user data)
            indaux{};//indicator for auxiliary (tangent) constitutive operator type:
            // 0 = elastic operator (default, symmetric),1 = plastic (unsymmetric)


    // Constant Lame coefficients
    Real    m_lamda{},m_mu{}, cohes{};

    // Local variables
    Real    sinphi{},cosphi{}, sinpsi{},
            alfa{}, alfpsi{}, xk{}, sef{};

    ElastTensor m_elast_tensor{}; // elastic constitutive tensor
    Real        m_tangent_tensor[6][6]{}; // tangent constitutive tensor used for LHS contribution (implicit solver)
    bool        is_plastic, is_associe;

public:

    // Construction/Destruction
public:
    DruckerPragerLaw();
    DruckerPragerLaw(const DruckerPragerLaw&);
    ~DruckerPragerLaw() = default;

    // Attributs

    // Methodes
//	DruckerPragerLaw& operator=(const DruckerPragerLaw&);

//    static Real get_dev(const Tensor2&, bool /*is_sig*/ = true);
    void init(const dvector& /*param*/);
    void initConst();
    void computeTangentTensor(const Tensor2& /*sig*/,const Tensor2& /*deps*/);
    bool initState(const Tensor2& /*sign*/ = Tensor2::zero(), dvector* /*histab*/ = nullptr);

    void ComputeStress(dvector* /*histab*/, Tensor2& /*sig*/, Tensor2& /*eps*/, Tensor2& /*epsp*/, Tensor2& /*dsig*/,
                       const Tensor2& /*deps*/,bool /*is_converge*/ = false);

    bool readParameters(const string&);
};

#endif //DRUCKERPRAGER_H
