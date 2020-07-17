/**************************************************************************************
*                                                                                     *
* Author : Mohd Afeef BADRI                                                           *
* Email  : mohd-afeef.badri@cea.fr                                                    *
* Date   : 20/04/2020                                                                 *
* Type   : Support file                                                               *
*                                                                                     *
* Comment: This support file is  responsible for generating Main.edp which  contain   *
*          the main solver finite element files of PSD.                               *
*                                                                                     *
**************************************************************************************/

cout << " building Main.edp";

{ofstream  write("Main.edp");

writeHeader;

writeIt
"                                                                               \n"
"//=============================================================================\n"
"// ------ Module files load and include ------                                 \n"
"//=============================================================================\n"
"                                                                               \n"
"                                                                               \n";

if(!Sequential)
 writeIt
 "  load    \"PETSc\"                                // PETSc plugin activated  \n";

if(Sequential)if(plotAll || plotTime)
 writeIt
 "  load    \"../Plugins/iovtk\"                     // Paraview support files \n";

if(useGFP)if(!energydecomp)
 writeIt
 "  load    \"../Plugins/gofastplugins\"             // GoFastPlugins Library  \n";

if(Prblm=="damage" && Model=="hybrid-phase-field" && energydecomp)
 writeIt
 "  load    \"../Plugins/gofastplugins\"             // GoFastPlugins Library  \n";

if(pipegnu)if(!supercomp)
 writeIt
 "  load    \"pipe\"                                 // Piping activated       \n";
 
if(Prblm=="soildynamics" && Model=="Hujeux")
 writeIt
 "  load    \"Element_QF\"                           // Quadrature elements     \n" 
 "  load    \"../Plugins/soil-laws\"                 // Soil law PSD library    \n";
 

if(debug || plotAll || plotTime)if(!Sequential)
 writeIt
 "  include \"../Plugins/DDplotMacro.edp\"           // Domain decomp plotting \n";

if(Sequential)
 writeIt
 "  include \"getARGV.idp\"                          // Commandline arguments  \n"
 "  include \"ControlParameters.edp\"                // Parameters & propeties \n"
 "  include \"Macros.edp\"                           // User-defined macros    \n"
 "  include \"OtherParameters.edp\"                  // Other Parameters       \n"
 "  include \"MeshAndFeSpace.edp\"                   // Mesh and FE space      \n"
 "  include \"FemParameters.edp\"                    // Fem Parameters         \n"
 "  include \"VariationalFormulations.edp\"          // Variational formulation\n"
 "  include \"LinearFormBuilderAndSolver.edp\"       // Build and solve Ax=b   \n";

if(!Sequential)
 writeIt
 "  include \"getARGV.idp\"                          // Commandline arguments  \n"
 "  include \"ControlParameters.edp\"                // Parameters & propeties \n"
 "  include \"OtherParameters.edp\"                  // Other Parameters       \n"
 "  include \"Macros.edp\"                           // User-defined macros    \n"
 "  include \"../Plugins/DDmacro.edp\"               // Domain decomp macros   \n"
 "  include \"MeshAndFeSpace.edp\"                   // Mesh and FE space      \n"
 "  include \"FemParameters.edp\"                    // Fem Parameters         \n"
 "  include \"VariationalFormulations.edp\"          // Variational formulation\n"
 "  include \"LinearFormBuilderAndSolver.edp\"       // Build and solve Ax=b   \n";


if(plotAll)
 writeIt
 "  include \"PostProcessor.edp\"                    // Post Processing        \n";        

} //-- [ostream terminator]  main.edp closed --//

cout << " ..................................... Done \n";
