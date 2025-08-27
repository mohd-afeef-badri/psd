/**************************************************************************************
*                                                                                     *
*           This file is a part of PSD project                                        *
*                                                                                     *
*       -------------------------------------------------------------------           *
*                                                                                     *
*       Copyright 2019-2025 CEA/DES                                                   *
*                                                                                     *
*       Licensed under the Apache License, Version 2.0  (the "License");              *
*       you may not use this file except in compliance with the License.              *
*       You may obtain a copy of the License at                                       *
*                                                                                     *
*           http://www.apache.org/licenses/LICENSE-2.0                                *
*                                                                                     *
*       Unless required by applicable law or agreed to in writing, software           *
*       distributed under the License is distributed on an  "AS IS"  BASIS,           *
*       WITHOUT  WARRANTIES  OR  CONDITIONS  OF  ANY  KIND,  either express           *
*       or implied. See  the License  for  the  specific language governing           *
*       permissions and limitations under the License.                                *
*                                                                                     *
*       -------------------------------------------------------------------           *
*                                                                                     *
**************************************************************************************/

#include <cmath>
#include <iostream>
#include <math.h>
//#include <omp.h>
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
