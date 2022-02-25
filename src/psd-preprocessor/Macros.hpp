/**************************************************************************************
*                                                                                     *
* Author : Mohd Afeef BADRI                                                           *
* Email  : mohd-afeef.badri@cea.fr                                                    *
* Date   : 20/04/2020                                                                 *
* Type   : Support file                                                               *
*                                                                                     *
* Comment: This support  file is  responsible for generating  Macros.edp   *
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

#include "./Macros/common.hpp"
} //-- [ostream terminator]  Macros.edp closed --//

cout << " ............... Done \n";

