/**************************************************************************************
*                                                                                     *
* Author : Mohd Afeef BADRI, Rania SAADI                                              *
* Email  : mohd-afeef.badri@cea.fr, rania.saadi@cea.fr                                *
* Date   : 15/10/2024                                                                 *
* Type   : Support file                                                               *
*                                                                                     *
* Comment: This support  file is  responsible for generating  OtherParameters.edp     *
*          which contain main solver control parameters of PSD.                       *
*                                                                                     *
**************************************************************************************/

cout << " building OtherParameters.edp";

{ofstream  write("OtherParameters.edp");

if(Prblm=="linear_elasticity")
{
#include "./OtherParameters/LinearElasticity.hpp"
}

if(Prblm=="elasto_plastic")
{
#include "./OtherParameters/ElastoPlastic.hpp"
}

if(Prblm=="damage")
{
#include "./OtherParameters/DamageMechanics.hpp"
}

if(Prblm=="elastodynamics")
{
#include "./OtherParameters/ElastoDynamics.hpp"
}

if(Prblm=="soildynamics")
{
#include "./OtherParameters/SoilDynamics.hpp"
}

if(Prblm=="poisson")
{
#include "./OtherParameters/poisson.hpp"
}


#include "./OtherParameters/common.hpp"

} //-- [ostream terminator]  OtherParameters.edp closed --//

cout << " ............... Done \n";

