/**************************************************************************************
*                                                                                     *
* Author : Mohd Afeef BADRI                                                           *
* Email  : mohd-afeef.badri@cea.fr                                                    *
* Date   : 20/04/2020                                                                 *
* Type   : Support file                                                               *
*                                                                                     *
* Comment: This support  file is  responsible for generating  ControlParameters.edp   *
*          which contain main solver control parameters of PSD.                       *
*                                                                                     *
**************************************************************************************/

cout << " building ControlParameters.edp";

{ofstream  write("ControlParameters.edp");

if(Prblm=="linear_elasticity")
{
#include "./ControlParameters/LinearElasticity.hpp"
}

if(Prblm=="elasto_plastic")
{
#include "./ControlParameters/ElastoPlastic.hpp"
}

if(Prblm=="damage")
{
#include "./ControlParameters/DamageMechanics.hpp"
}

if(Prblm=="elastodynamics")
{
#include "./ControlParameters/ElastoDynamics.hpp"
}

if(Prblm=="soildynamics")
{
#include "./ControlParameters/SoilDynamics.hpp"
}


if(Prblm=="poisson")
{
#include "./ControlParameters/poisson.hpp"
}

} //-- [ostream terminator]  ControlParameters.edp closed --//

cout << " ............... Done \n";

