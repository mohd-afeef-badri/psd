/*****************************************************************************

         This file is a part of PSD (Parallel Structural Dynamics)

     -------------------------------------------------------------------

     Author(s): Mohd Afeef Badri, Evelyne Foerster
     Email    : mohd-afeef.badri@hotmail.com
     Date     : 2018‑05‑29

     -------------------------------------------------------------------

     PSD a parallel  finite  element framework  provides tools to  solve 
     multiple  solid-dynamic  problems; PSD is distributed  in  the hope 
     that it will be useful, but WITHOUT ANY WARRANTY; or  without  even  
     the implied warranty of  FITNESS  FOR  A  PARTICULAR  PURPOSE.

*******************************************************************************/


#include "ff++.hpp"

using namespace Fem2D;
using namespace std;

//=============================================================================
// --- HujeuxLaw --
//=============================================================================

double HujeuxLaw(KN<double> *const & f, KN<double> *const & f1)   
{
  cout << "  HELLO HELLO FROM hujeuxLaw fuction  " << endl;
  return 0.0;
}



//=============================================================================
// --- Update HujeuxSoilLaw --
//=============================================================================

template<class K>
class HujeuxSoilLaw_Op : public E_F0mps {
    public:
        Expression du					  ;

              
        static const int n_name_param = 0		;
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
basicAC_F0::name_and_type HujeuxSoilLaw_Op<K>::name_param[] = { };

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
    KN<K>* vec1 = GetAny<KN<K>*>((*du)(stack))		;
    					                        ;
    cout << " HELLO HELLO FROM hujeuxLaw CLass " << endl;    
    
    return 0L;
}


 
static void InitFF()
{
  Global.Add("HujeuxSoilLaw", "(", new HujeuxSoilLaw<double>);
  Global.Add("HujeuxLaw","(",new OneOperator2_<double,KN<double>*, KN<double>*>(HujeuxLaw));
}
LOADFUNC(InitFF)   
