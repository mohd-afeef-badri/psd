//=====================================================================================
// ------ Building the LinearFormBuilderAndSolver.edp file ------
//=====================================================================================

cout << " building LinearFormBuilderAndSolver.edp";

{ofstream  write("LinearFormBuilderAndSolver.edp");

writeHeader;

if(Prblm=="linear-elasticity")
{
#include "LinearFormBuilderAndSolver_LinearElasticity.hpp"
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

