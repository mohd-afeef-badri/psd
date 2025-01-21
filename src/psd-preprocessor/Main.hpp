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
"// ------ load libraries ------                                                \n"
"//=============================================================================\n"
"                                                                               \n"
"                                                                               \n";

if (AdaptmeshBackend=="mmg")
 writeIt
 "  load    \"mmg\"                                  // mmg interface active \n";

if ((AdaptmeshBackend=="mmg" || AdaptmeshBackend=="parmmg") && spc==3)
 writeIt
 "  load    \"mshmet\"                               // metric interface active \n";

if (AdaptmeshBackend=="parmmmg" && spc==3)
 writeIt
 "  load    \"parmmg\"                               // parmmg interface active \n";

if(!Sequential)
 writeIt
 "  load    \"PETSc\"                                // PETSc plugin activated  \n";

if(useMfront)
 writeIt
 "  load    \"mfront\"                               // MFront interface active \n";

if(Sequential)if(ParaViewPostProcess)
 writeIt
 "  load    \"iovtk\"                                // Paraview support files \n";

if(useGFP)if(!energydecomp)
 writeIt
 "  load    \"gofastplugins\"                        // GoFastPlugins Library  \n";

if(Prblm=="damage" && Model=="hybrid_phase_field" && energydecomp)
 writeIt
 "  load    \"gofastplugins\"                       // GoFastPlugins Library  \n";

if(pipegnu)
 writeIt
 "  load    \"pipe\"                                 // Piping activated       \n";

if( (Prblm=="linear_elasticity" || Prblm=="elasto_plastic") && !fastmethod)
 writeIt
 "  load    \"Element_QF\"                           // Quadrature elements     \n";

if(Prblm=="soildynamics" && Model=="Hujeux")
 writeIt
 "  load    \"Element_QF\"                           // Quadrature elements     \n"
 "  load    \"soil-laws\"                            // Soil law PSD library    \n";

if(!Sequential&& Prblm=="soildynamics" && top2vol)
 writeIt
 "  load    \"msh3\"                                 // to get cube function   \n"
 "  load    \"top-ii-vol\"                           // top-ii-vol meshing     \n";

writeIt
"                                                                               \n"
"func int compute(){                                                            \n";

if(debug || ParaViewPostProcess)if(!Sequential && !top2vol)
 writeIt
 "  include \"DDplotMacro.edp\"                     // Domain decomp plotting \n";

if(Sequential)
 writeIt
 "  include \"getARGV.idp\"                          // Commandline arguments  \n"
 "  include \"ControlParameters.edp\"                // Parameters & properties\n"
 "  include \"Macros.edp\"                           // User-defined macros    \n"
 "  include \"OtherParameters.edp\"                  // Other Parameters       \n"
 "  include \"MeshAndFeSpace.edp\"                   // Mesh and FE space      \n"
 "  include \"FemParameters.edp\"                    // Fem Parameters         \n"
 "  include \"VariationalFormulations.edp\"          // Variational formulation\n"
 "  include \"LinearFormBuilderAndSolver.edp\"       // Build and solve Ax=b   \n";

if(!Sequential)
 {
 writeIt
 "  include \"getARGV.idp\"                          // Commandline arguments  \n"
 "  include \"ControlParameters.edp\"                // Parameters & properties\n"
 "  include \"OtherParameters.edp\"                  // Other Parameters       \n"
 "  include \"Macros.edp\"                           // User-defined macros    \n";

 if(!top2vol)
  writeIt
  "  include \"DDmacro.edp\"                          // Domain decomp macros  \n";
 if(top2vol || (AdaptmeshBackend=="parmmmg" && spc==3))
  writeIt
  "  include \"macro_ddm.idp\"                        // Domain decomp macros  \n";

 writeIt
 "  include \"MeshAndFeSpace.edp\"                   // Mesh and FE space      \n"
 "  include \"FemParameters.edp\"                    // Fem Parameters         \n"
 "  include \"VariationalFormulations.edp\"          // Variational formulation\n"
 "  include \"LinearFormBuilderAndSolver.edp\"       // Build and solve Ax=b   \n";
 }


writeIt
"  include \"PostProcessor.edp\"                    // Post Processing        \n"
"}                                                                            \n";


if(timelog)
writeIt
"                                                                             \n"
<<(Sequential ? "real tc = clock(); \n" : "real tc = mpiWtime(); \n"          )<<
"compute();                                                                   \n"
"                                                                             \n"
"                                                                             \n"
"                                                                             \n"
<<(Sequential ? "" : "mpiBarrier(mpiCommWorld);\n"                            )
<<(Sequential ? "tc = clock()-tc; \n" : "tc = mpiWtime()-tc; if(mpirank==0)\n")<<
"cout.scientific << \"----------------------------------------------\\n\"     \n"
"                << \"  PSD total run time [ \" << tc <<\" ] s      \\n\"     \n"
"                << \"----------------------------------------------\\n\";    \n"
"                                                                             \n";

if(!timelog)
writeIt
"                                                                             \n"
"compute();                                                                   \n";

} //-- [ostream terminator]  main.edp closed --//

cout << " ..................................... Done \n";
