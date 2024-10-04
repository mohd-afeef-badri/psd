/**************************************************************************************
*                                                                                     *
* Author : Mohd Afeef BADRI                                                           *
* Email  : mohd-afeef.badri@cea.fr                                                    *
* Date   : 30/11/2021                                                                 *
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
