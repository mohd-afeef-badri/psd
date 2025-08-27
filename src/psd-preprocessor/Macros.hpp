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
*                                                                                     *
* Comment: This support  file is  responsible for generating  Macros.edp              *
*          which contain main solver control parameters of PSD.                       *
*                                                                                     *
**************************************************************************************/

cout << " building Macros.edp";

{ofstream  write("Macros.edp");

if(Prblm=="linear_elasticity")
{
#include "./Macros/LinearElasticity.hpp"
}

if(Prblm=="elasto_plastic")
{
#include "./Macros/ElastoPlastic.hpp"
}


if(Prblm=="damage")
{
#include "./Macros/DamageMechanics.hpp"
}

if(Prblm=="elastodynamics")
{
#include "./Macros/ElastoDynamics.hpp"
}

if(Prblm=="soildynamics")
{
#include "./Macros/SoilDynamics.hpp"
}


if(Prblm=="poisson")
{
#include "./Macros/poisson.hpp"
}
#include "./Macros/common.hpp"
} //-- [ostream terminator]  Macros.edp closed --//

cout << " ............... Done \n";

