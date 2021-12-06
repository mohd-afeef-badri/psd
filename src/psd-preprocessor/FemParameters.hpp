/**************************************************************************************
*                                                                                     *
* Author : Mohd Afeef BADRI                                                           *
* Email  : mohd-afeef.badri@cea.fr                                                    *
* Date   : 20/04/2020                                                                 *
* Type   : Support file                                                               *
*                                                                                     *
* Comment: This support  file is  responsible for generating  FemParameters.edp   *
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

} //-- [ostream terminator]  FemParameters.edp closed --//

cout << " ............... Done \n";

