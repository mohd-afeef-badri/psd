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
* Comment: This support file is responsible for generating VariationalFormulations.edp*
*          the file which contains FEM variational  formulation  for  PSD. Infact this*
*          variational formulations for specific applications ( damage, elastodynamics*
*          linear elasticity, soildynamics ) are written in other files and  this file*
*          helps choose the correct one                                               *
*                                                                                     *
**************************************************************************************/

cout << " building VariationalFormulations.edp";

{ofstream  write("VariationalFormulations.edp");

writeHeader;

if(Prblm=="linear_elasticity")
{
#include "./VariationalFormulation/LinearElasticity.hpp"
}

if(Prblm=="elasto_plastic")
{
#include "./VariationalFormulation/ElastoPlastic.hpp"
}

if(Prblm=="damage")
{
#include "./VariationalFormulation/DamageMechanics.hpp"
}

if(Prblm=="elastodynamics")
{
#include "./VariationalFormulation/ElastoDynamics.hpp"
}

if(Prblm=="soildynamics")
{
#include "./VariationalFormulation/SoilDynamics.hpp"
}

if(Prblm=="poisson")
{
#include "./VariationalFormulation/poisson.hpp"
}

} //-- [ostream terminator]  VariationalFormulations.edp closed --//

cout << " .................. Done \n";
