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

#include <cmath>
#include <iostream>
#include <math.h>
#include "ff++.hpp"
#include "RNM.hpp"
#include "AFunction.hpp"
#include "AFunction_ext.hpp"

#include "MGIS/Behaviour/State.hxx"
#include "MGIS/Behaviour/Behaviour.hxx"
#include "MGIS/Behaviour/BehaviourData.hxx"
#include "MGIS/Behaviour/MaterialDataManager.hxx"
#include "MGIS/Behaviour/Integrate.hxx"

using namespace std;
using namespace Fem2D;
using namespace mgis;
using namespace mgis::behaviour;


#include "typedefinitions.hxx"
#include "PsdMfrontPrintBehaviourStats.hpp"
#include "PsdMfrontHandler.hpp"
#include "PsdMfrontHandlerDm.hpp"


static void InitFF()
{
  Global.Add("PsdMfrontHandler", "(", new PsdMfrontHandler<double>);
  Global.Add("PsdMfrontHandlerDm", "(", new PsdMfrontHandlerDm<double>);
  Global.Add("PsdMfrontPrintBehaviourStats", "(", new PsdMfrontStats<double>);  
}
LOADFUNC(InitFF)
