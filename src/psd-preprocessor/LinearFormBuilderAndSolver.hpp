//=====================================================================================
// ------ Building the LinearFormBuilderAndSolver.edp file ------ 
//=====================================================================================

cout << " building LinearFormBuilderAndSolver.edp";

{ofstream  writesolver("LinearFormBuilderAndSolver.edp");

writesolver<<
"/************************ LinearFormBuilderAndSolver **************************\n"
"*                                                                             *\n"
"* Note!!! This file is  generated  by  running  PSD PreProcessor. Do not edit *\n"
"*         in order to  control this file please change flag arguments of  the *\n"
"*         PSD_PreProcess. To know the available flags run PSD_PreProcess with *\n"
"*         -help or read the PSD manual.                                       *\n"
"*                                                                             *\n"
"******************************************************************************/\n"
"										\n";

if(Prblm=="damage")
{
#include "LinearFormBuilderAndSolver_DamageMechanics.hpp"
}

if(Prblm=="linear-elasticity")
{
#include "LinearFormBuilderAndSolver_LinearElasticity.hpp"
}

if(Prblm=="elastodynamics" || Prblm=="soildynamics")
{
#include "LinearFormBuilderAndSolver_Dynamics.hpp"
}

} //-- [ostream terminator]  LinearFormBuilderAndSolver.edp closed --//

cout << " ............... Done \n";

