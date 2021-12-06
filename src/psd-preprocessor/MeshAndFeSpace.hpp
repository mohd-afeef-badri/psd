/**************************************************************************************
*                                                                                     *
* Author : Mohd Afeef BADRI                                                           *
* Email  : mohd-afeef.badri@cea.fr                                                    *
* Date   : 20/04/2020                                                                 *
* Type   : Support file                                                               *
*                                                                                     *
* Comment: This support  file is  responsible for generating  MeshAndFeSpace.edp   *
*          which contain main solver control parameters of PSD.                       *
*                                                                                     *
**************************************************************************************/

cout << " building MeshAndFeSpace.edp";

{ofstream  write("MeshAndFeSpace.edp");

if(Prblm=="linear_elasticity")
{
#include "./MeshAndFeSpace/LinearElasticity.hpp"
}

if(Prblm=="elasto_plastic")
{
#include "./MeshAndFeSpace/ElastoPlastic.hpp"
}

if(Prblm=="damage")
{
#include "./MeshAndFeSpace/DamageMechanics.hpp"
}

if(Prblm=="elastodynamics")
{
#include "./MeshAndFeSpace/ElastoDynamics.hpp"
}

if(Prblm=="soildynamics")
{
#include "./MeshAndFeSpace/SoilDynamics.hpp"
}

} //-- [ostream terminator]  MeshAndFeSpace.edp closed --//

cout << " ............... Done \n";

