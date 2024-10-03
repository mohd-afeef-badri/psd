//=====================================================================================
// ------ Building the LinearFormBuilderAndSolver.edp file ------
//=====================================================================================

cout << " building LinearFormBuilderAndSolver.edp";

{ofstream  write("LinearFormBuilderAndSolver.edp");

writeHeader;

if(Prblm=="linear_elasticity")
{
#include "./LinearFormBuilderAndSolver/LinearElasticity.hpp"
}

if(Prblm=="elasto_plastic")
{
#include "./LinearFormBuilderAndSolver/ElastoPlastic.hpp"
}

if(Prblm=="damage")
{
#include "./LinearFormBuilderAndSolver/DamageMechanics.hpp"
}

if(Prblm=="elastodynamics")
{
#include "./LinearFormBuilderAndSolver/ElastoDynamics.hpp"
}

if(Prblm=="soildynamics")
{
#include "./LinearFormBuilderAndSolver/SoilDynamics.hpp"
}

if(Prblm=="poisson")
{
#include "./LinearFormBuilderAndSolver/poisson.hpp"
}

} //-- [ostream terminator]  LinearFormBuilderAndSolver.edp closed --//

cout << " ............... Done \n";

