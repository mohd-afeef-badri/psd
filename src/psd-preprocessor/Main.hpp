//=====================================================================================
// ------ Building the main.edp file ------ 
//=====================================================================================

{ofstream  writemain("Main.edp");

writemain
<<"										   \n"
<<"/**********************************Main file************************************\n"
<<"*                                                                              *\n"
<<"* Note!!! This file is  generated  by running SolverGenerator.edp. Do not edit *\n"
<<"*         in order to  control this  file please change flag arguments of  the *\n"
<<"*         SolverGenerator, details of which are present in SolverGenerator.edp *\n"
<<"*         or in the README.MD file.                                            *\n"
<<"*                                                                              *\n"
<<"*******************************************************************************/\n"
<<"										   \n"
<<"										   \n"
<<"//==============================================================================\n"
<<"// ------ Module files load and include ------ 				   \n"
<<"//==============================================================================\n"
<<"										   \n"
<<"										   \n";

if(!Sequential)writemain
<<"  load    \"PETSc\"                                  // PETSc plugin activated  \n";

if(Sequential)if(plotAll || plotTime)writemain
<<"  load    \"../Plugins/iovtk\"                       // Paraview support files  \n";


if(useGFP)if(!energydecomp)writemain
<<"  load    \"../Plugins/gofastplugins\"               // GoFastPlugins Library   \n";

if(nonlinear)if(energydecomp)writemain
<<"  load    \"../Plugins/gofastplugins\"               // GoFastPlugins Library   \n";

if(pipegnu)if(!supercomp)writemain
<<"  load    \"pipe\"                                   // Piping activated	   \n";

if(debug || plotAll || plotTime)if(!Sequential)writemain
<<"  include \"../Plugins/DDplotMacro.edp\"             // Domain decomp plotting  \n";

if(Sequential)writemain
<<"  include \"getARGV.idp\"                            // Commandline arguments ON\n"
<<"  include \"ControlParameters.edp\"                  // Parameters & propeties  \n"
<<"  include \"Macros.edp\"                             // User-defined macros	   \n"
<<"  include \"OtherParameters.edp\"                    // Other Parameters        \n"
<<"  include \"MeshAndFeSpace.edp\"                     // Define Mesh and FE space\n"
<<"  include \"FemParameters.edp\"                      // Fem Parameters          \n"
<<"  include \"VariationalFormulations.edp\"            // Variational formulations\n"
<<"  include \"LinearFormBuilderAndSolver.edp\"         // Build and solve Ax=b	   \n";

if(!Sequential){writemain
<<"  include \"getARGV.idp\"                            // Commandline arguments ON\n"
<<"  include \"ControlParameters.edp\"                  // Parameters & propeties  \n"
<<"  include \"OtherParameters.edp\"                    // Other Parameters        \n"
<<"  include \"Macros.edp\"                             // User-defined macros	   \n"
<<"  include \"../Plugins/DDmacro.edp\"                 // Domain decomp macros    \n";

writemain
<<"  include \"MeshAndFeSpace.edp\"                     // Define Mesh and FE space\n"
<<"  include \"FemParameters.edp\"                      // Fem Parameters          \n"
<<"  include \"VariationalFormulations.edp\"            // Variational formulations\n"
<<"  include \"LinearFormBuilderAndSolver.edp\"         // Build and solve Ax=b	   \n";
}

if(plotAll)writemain
<<"  include \"PostProcessor.edp\"                      // Post Processing   	   \n";        

} //-- [ostream terminator]  main.edp closed --//

