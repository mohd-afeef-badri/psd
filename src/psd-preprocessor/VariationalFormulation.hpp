//=================================================================================================
// ------ Building the VariationalFormulations.edp file ------ 
//=================================================================================================

cout << " building VariationalFormulations.edp"; 

{ofstream  write("VariationalFormulations.edp");

writeHeader;

if(Prblm=="linear-elasticity")
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
