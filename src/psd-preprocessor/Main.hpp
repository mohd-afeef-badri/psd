/**************************************************************************************
*                                                                                     *
*           This file is a part of PSD (Parallel Structural Dynamics)                 *
*                                                                                     *
*       -------------------------------------------------------------------           *
*                                                                                     *
*       Copyright 2019-2025 CEA/DES                                                   *
*                                                                                     *
*       Licensed under the Apache License, Version 2.0  (the "License");              *
*       you may not use this file except in compliance with the License.              *
*       You may obtain a copy of the License at                                       *
*                                                                                     *
*           http://www.apache.org/licenses/LICENSE-2.0                                *
*                                                                                     *
*       Unless required by applicable law or agreed to in writing, software           *
*       distributed under the License is distributed on an  "AS IS"  BASIS,           *
*       WITHOUT  WARRANTIES  OR  CONDITIONS  OF  ANY  KIND,  either express           *
*       or implied. See  the License  for  the  specific language governing           *
*       permissions and limitations under the License.                                *
*                                                                                     *
*       -------------------------------------------------------------------           *
*                                                                                     *
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

if (((AdaptmeshBackend=="mmg" || AdaptmeshBackend=="parmmg") && spc==3) || AdaptmeshMetricBackend=="mshmet")
 writeIt
 "  load    \"mshmet\"                               // metric interface active \n";

if (AdaptmeshBackend=="parmmg" && spc==3)
 writeIt
 "  load    \"mmg\"                                  // mmg interface active \n"
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

if(debug || ParaViewPostProcess)if(!Sequential && !top2vol)if(!(!Sequential && spc == 3 && adaptmesh))
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

 if(!top2vol && !(AdaptmeshBackend=="parmmg" && spc==3))
  writeIt
  "  include \"DDmacro.edp\"                          // Domain decomp macros  \n";
 if(top2vol || (AdaptmeshBackend=="parmmg" && spc==3))
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
