//=====================================================================================
// ------ Building the LinearFormBuilderAndSolver.edp file ------
//=====================================================================================

cout << " building LinearFormBuilderAndSolver.edp";

{ofstream  write("LinearFormBuilderAndSolver.edp");

writeHeader;

if(Prblm=="linear_elasticity")
{
#include "LinearFormBuilderAndSolver_LinearElasticity.hpp"
}

if(Prblm=="elasto_plastic")
{
#include "LinearFormBuilderAndSolver_ElastoPlastic.hpp"
}

if(Prblm=="damage")
{
#include "LinearFormBuilderAndSolver_DamageMechanics.hpp"
}

if(Prblm=="elastodynamics")
{
#include "LinearFormBuilderAndSolver_ElastoDynamics.hpp"
}

if(Prblm=="soildynamics")
{
#include "LinearFormBuilderAndSolver_SoilDynamics.hpp"
}

} //-- [ostream terminator]  LinearFormBuilderAndSolver.edp closed --//

cout << " ............... Done \n";

