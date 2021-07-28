/*****************************************************************************

         This file is a part of PSD (Parallel Structural Dynamics)

     -------------------------------------------------------------------

     Author(s): Mohd Afeef Badri
     Email    : mohd-afeef.badri@cea.com
     Date     : 2021‑07‑29

     -------------------------------------------------------------------

     PSD a parallel  finite  element framework  provides tools to  solve 
     multiple  solid-dynamic  problems; PSD is distributed  in  the hope 
     that it will be useful, but WITHOUT ANY WARRANTY; or  without  even  
     the implied warranty of  FITNESS  FOR  A  PARTICULAR  PURPOSE.

*******************************************************************************/


#include <iostream>
#include <math.h>
#include "ff++.hpp"
#include "RNM.hpp"
#include "AFunction.hpp"
#include "AFunction_ext.hpp"

#include <iostream>
#include "MGIS/Behaviour/Behaviour.hxx"

using namespace Fem2D;
using namespace std;
using namespace mgis::behaviour;


template<class K>
class MFrontParameter_Op : public E_F0mps {
    public:
        Expression mu					;  
              
        static const int n_name_param = 0		;
        static basicAC_F0::name_and_type name_param[]	;
        Expression nargs[n_name_param]			;
        
        MFrontParameter_Op(const basicAC_F0& args		, 
        		Expression param1				
        		) : 
        		mu     (param1)			
        		{
            		args.SetNameParam(n_name_param	, 
            				  name_param	, 
            				  nargs
            				  )		;
        		}
        		
        AnyType operator()(Stack stack) const		;
};

template<class K>
basicAC_F0::name_and_type MFrontParameter_Op<K>::name_param[] = { };

template<class K>
class MFrontParameter : public OneOperator {
    public:
        MFrontParameter() : OneOperator(atype<long>()	,         			     
        			     atype<double>()  
        			     ) {}

        E_F0* code(const basicAC_F0& args) const {
            return new MFrontParameter_Op<K>(args, 
            				  t[0]->CastTo(args[0])           				              				  
            				  );
        }
};


template<class K>
AnyType MFrontParameter_Op<K>::operator()(Stack stack) const {

    const auto muMfront = mgis::real{GetAny<double>((*mu)(stack))};
    
    cout
             << " Print of MFront Parameter "
             <<  muMfront 
             <<
    endl;
        
    return 0L;
}

static void InitFF()
{
  Global.Add("MFrontParameter", "(", new MFrontParameter<double>);
}
LOADFUNC(InitFF)   
