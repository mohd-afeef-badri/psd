/*****************************************************************************

         This file is a part of PSD (Parallel Structural Dynamics)

     -------------------------------------------------------------------

     Author(s): Mohd Afeef Badri, Evelyne Foerster
     Email    : mohd-afeef.badri@cea.fr, evelyne.foerster@cea.fr 
     Date     : 2018‑05‑29

     -------------------------------------------------------------------

     PSD a parallel  finite  element framework  provides tools to  solve 
     multiple  solid-dynamic  problems; PSD is distributed  in  the hope 
     that it will be useful, but WITHOUT ANY WARRANTY; or  without  even  
     the implied warranty of  FITNESS  FOR  A  PARTICULAR  PURPOSE.

*******************************************************************************/


#include "ff++.hpp"
#include "./../hujeux-law-lib/utils.h"
#include "./../hujeux-law-lib/hujeux.h"

using namespace Fem2D;
using namespace std;


//=============================================================================
// --- HujeuxSoilLaw class interface for PSD--
//=============================================================================

template<class K>
class HujeuxSoilLaw_Op : public E_F0mps {
    public:
        Expression du					  ;
            
        static const int n_name_param = 3		;
        static basicAC_F0::name_and_type name_param[]	;
        Expression nargs[n_name_param]			;
        
        HujeuxSoilLaw_Op(const basicAC_F0& args		, 
        		Expression param1		
        		) : 
        		du     (param1)					
        		{
            		args.SetNameParam(n_name_param	, 
            				  name_param	, 
            				  nargs
            				  )		;
        		}
        		
        AnyType operator()(Stack stack) const		;
};

template<class K>
basicAC_F0::name_and_type HujeuxSoilLaw_Op<K>::name_param[] = { 
    {"ParamaterFile", &typeid(std::string*)},
    {"stressVector" , &typeid(KN<K>*)},    
    {"InternalVariables", &typeid(KN<K>*)}        
};

template<class K>
class HujeuxSoilLaw : public OneOperator {
    public:
        HujeuxSoilLaw() : OneOperator(atype<long>()	, 
        			     atype<KN<K>*>()	 
        			     ) {}

        E_F0* code(const basicAC_F0& args) const {
            return new HujeuxSoilLaw_Op<K>(args, 
            				  t[0]->CastTo(args[0])       				              				  
            				  );
        }
};


template<class K>
AnyType HujeuxSoilLaw_Op<K>::operator()(Stack stack) const {

  string* paramFileName = nargs[0] ? GetAny<std::string*>((*nargs[0])(stack)) : NULL;
  
  KN<K>* epsPSD    = GetAny<KN<K>*>((*du)(stack));                            // PSD starin vector for all gauss points
  KN<K>* sigPSD    = nargs[1] ? GetAny<KN<K>*>((*nargs[1])(stack))  : NULL	; // PSD history variable vector for all gauss points   
  KN<K>* hisVarPSD = nargs[2] ? GetAny<KN<K>*>((*nargs[2])(stack))  : NULL	; // PSD stress vector for all gauss points 


#ifdef DEBUG
  cout << "\n Entering class HujeuxSoilLaw  soil-laws.cpp\n"
          " Input parameters :\n"
          "            paramFileName = "  << *paramFileName 
       << endl;
       
  if(paramFileName == NULL) 
     cout << "******Error in class HujeuxSoilLaw_Op*******"
             "                                            "
             "      ParamaterFile cannot be empty         " 
             "********************************************"
          << endl;       
#endif

//vec2->operator[](0)=vec2->operator[](0)+99.;

//----------------------------------------------------------
//  HujeuxLaw class tests : simple shear on one material point 
//---------------------------------------------------------- 
    
  HujeuxLaw PSDobject;                      // Creating PSDobject    
  PSDobject.readParameters(*paramFileName); // Read paramerts for HujeuxLaw    

  auto   PI     = acos(-1.),
         t      = 0.;  
  double freq   = 5., 
         dt     = 0.001,
         xmax   = 0.001,                     //0.1% strains max
         dx     = 0., 
         x      = 0.,
         tpeak  = asin(1) / (2 * PI * freq),
         fact   = tpeak/dt,
         faceps = 100.,
         facsig = 1.e-3;
  int	   npi    = (int)(fact),              // number of steps per 1/4 cycle
         ncyc   = 1,                        // only one loading cycle for this 1st test (to be increased later if everything works fine)
         npas   = 4 * ncyc * npi;

  Tensor2 sig(Real3(sigPSD->operator[](0), sigPSD->operator[](1),sigPSD->operator[](2)), 
              Real3::zero()                                                     ),  // effective stress tensor for current step
          eps,	                                    // strain tensor for current step
          epsp,                                     // plastic strain tensor for current step
          deps,                                     // strain tensor increment
          dsig;                                     // effective stress tensor increment
          
          
  dvector *histab = new dvector(NHISTHUJ);
  for(int i = 0; i < NHISTHUJ; i++) (*histab)[i] = hisVarPSD->operator[](i);
     
  filebuf fichout;
  fichout.open("Hujeuxresults.output", ios::out);
  ostream os(&fichout);
  os.setf(std::ios::left);
  os.precision(8);
  os << "#Simple shear test on a material point";
  os << string("\n#gamxy[%]\tgampxy[%]\tsigxy[kPa]\tpmean[kPa]\tepsv[%]\tepsvp[%]") << endl;
  os << setw(15) << "0." << setw(15) << "0." << setw(15) << "0.";
  os << setw(15) << -sigPSD->operator[](0) * facsig << setw(15) << "0." << setw(15) << "0." << endl;

  PSDobject.initState(sig, histab);

  bool is_converge = true;

  for (int i = 0; i < npas; i++)
   {
    auto x0  = xmax * sin(2 * PI * freq * t);
    t += dt;
    auto x   = xmax * sin(2 * PI * freq * t);
    if (fabs(x0) < EPS) x0 = 0.;
    if (fabs(x) < EPS)  x  = 0.;
    dx = x - x0;

    eps.m_vec[3]  = 2 * x;                        //epsxy = 2*gamxy
    deps.m_vec[3] = 2 * dx;

    PSDobject.ComputeStress(histab,sig, eps, epsp, dsig, deps, is_converge);

    auto gamxy  =  eps.m_vec[3]  * faceps / 2.;   // [%]
    auto gampxy =  epsp.m_vec[3] * faceps / 2.;   // [%]
    auto sigxy  =  sig.m_vec[3]  * facsig     ;   // [kPa]
    auto pmean  = -trace(sig)    * facsig / 3.;   // [kPa]
    auto epsv   =  trace(eps)    * faceps;        // [%]
    auto epsvp  =  trace(epsp)   * faceps;        // [%]

    if(i==0)cout << "\nprinting step results in Hujeuxresults.ouput...";
    os << setw(15) << gamxy << setw(15) << gampxy << setw(15) << sigxy;
    os << setw(15) << pmean << setw(15) << epsv << setw(15) << epsvp << endl;
   }
     fichout.close();
    
  return 0L;
}


 
static void InitFF()
{
  Global.Add("PSDHujeuxSoilLaw", "(", new HujeuxSoilLaw<double>);
}
LOADFUNC(InitFF)   
