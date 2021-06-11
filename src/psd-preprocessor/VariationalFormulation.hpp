/**************************************************************************************
*                                                                                     *
* Author : Mohd Afeef BADRI                                                           *
* Email  : mohd-afeef.badri@cea.fr                                                    *
* Date   : 20/04/2020                                                                 *
* Type   : Support file                                                               *
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
#include "VariationalFormulation_LinearElasticity.hpp"
}

if(Prblm=="damage")
{
#include "VariationalFormulation_DamageMechanics.hpp"
}

if(Prblm=="elastodynamics")
{
#include "VariationalFormulation_ElastoDynamics.hpp"
}

if(Prblm=="soildynamics")
{
#include "VariationalFormulation_SoilDynamics.hpp"
}

} //-- [ostream terminator]  VariationalFormulations.edp closed --//

cout << " .................. Done \n";
