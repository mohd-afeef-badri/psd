/**************************************************************************************
*                                                                                     *
*           This file is a part of PSD (Parallel Structural Dynamics)                 *
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
*                                                                                     *
* Comment: This support  file is  responsible for generating  FemParameters.edp       *
*          which contain main solver control parameters of PSD.                       *
*                                                                                     *
**************************************************************************************/

cout << " building FemParameters.edp";

{ofstream  write("FemParameters.edp");

writeHeader;

if(Prblm=="linear_elasticity")
{
#include "./FemParameters/LinearElasticity.hpp"
}

if(Prblm=="elasto_plastic")
{
#include "./FemParameters/ElastoPlastic.hpp"
}

if(Prblm=="damage")
{
#include "./FemParameters/DamageMechanics.hpp"
}

if(Prblm=="elastodynamics")
{
#include "./FemParameters/ElastoDynamics.hpp"
}

if(Prblm=="soildynamics")
{
#include "./FemParameters/SoilDynamics.hpp"
}

if(Prblm=="poisson")
{
#include "./FemParameters/poisson.hpp"
}

} //-- [ostream terminator]  FemParameters.edp closed --//

cout << " ............... Done \n";

