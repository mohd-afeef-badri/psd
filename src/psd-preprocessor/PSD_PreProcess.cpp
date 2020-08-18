/**************************************************************************************
*                                                                                     *
* Author:  Mohd Afeef BADRI                                                           *
* Date:    20/04/2020                                                                 *
* Type:    Execution file                                                             *
*                                                                                     *
* Comment: Once executed this file generates following edp files: Main, Macros, Mesh, *
*          MeshPartitioning,   VariationalFormulations,   BoundaryAndSourceConditions *
*          Parameters,  LinearFormBuilderAndSolver, and PostProcessor. All these .edp *
*          files combine  together to form  a fully tailored  solid mechanics solver. *
*          Commandline flags  are  used to controls the nature of the generated file. *
*          One   is    advised     to   carefully   go   through   these   arguments. *
*                                                                                     *
* Compile: Use a g++/icpc compiler C++ compiler                                       *
*                                                                                     *
**************************************************************************************/

/**************************************************************************************
*                              ___               __                                   *
*                            / __ \   _____   __/  /                                  *
*                           / /_/ /  / ___/ / __  /                                   *
*                          / ___ /  (__  ) / /_/ /                                    *
*                         /_/      /____/  \___ /                                     *
*                                                                                     *
**************************************************************************************/

//=====================================================================================
// ------ All command line argument descriptions [ARGUMENTS] ------
//=====================================================================================
/*

  -------------------------------------------------------------------------------------

  -dirichletpointconditions [int]  # of Dirchlet points.  Default 0.

  -bodyforceconditions      [int]  # of regions in which body force is define.  Default 0.
  
  -dirichletconditions      [int]  # of Dirchlet boundaries.  Default 1.

  -tractionconditions       [int]  # of Neumann/traction boundaries.  Default 0.

  -parmetis_worker          [int]  Active when mesh partitioner is parmetis.

  -dimension                [int]  Dimension of problem. 2 for 2D 3 for 3D. Default 2.

  -lagrange                 [int]  Lagrange order used for building FE space. Options
                                   are  1 for P1 or 2 for P2. Default is P1.

  -------------------------------------------------------------------------------------

  -doublecouple    [string] Soil dynamics double couple. Use force-based|displacement-based.

  -nonlinearmethod [string] Nonlinear method type. Use Picard|Newton-Raphsons.

  -partitioner     [string] Mesh partitioner. Use metis|scotch|parmetis.

  -postprocess     [string] Indicate postprocessing quantity. Use u|v|a|phi|uphi|uva.

  -problem         [string] Interested problem. Use linear-elasticity|damage|elastodynamics.

  -model           [string] Interested model. Use hybrid-phase-field|Mazar.

  -------------------------------------------------------------------------------------

  -help         [bool]     To activate helping message on the terminal.

  -plot         [bool]     To activate plotting routine.

  -debug        [bool]     To activate debug openGL plotting routine.

  -useGFP       [bool]     To activate use of GoFastPlugins. A suite of c++ plugins.

  -timelog      [bool]     To setup time logging for various phases of the solver.

  -useRCM       [bool]     To activate mesh level renumbering via Reverse Cuthill Mckee.

  -pipegnu      [bool]     To activate realtime pipe plotting using GnuPlot.

  -vectorial    [bool]     To generate vectorial space solver for non-linear.

  -supercomp    [bool]     To be used when using a cluster/supercomputer.

  -fastmethod   [bool]     Fast method for linear elasticity (expanded material tensor).

  -energydecomp [bool]     To activate hybrid phase field energy decomposition.

  -sequential   [bool]     To generate a sequential ff++ solver.

  -top2vol-meshing [bool]  To activate top-ii-vol point source meshing for soil-dynamics.

*/

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "HeaderMacro.hpp"

#define writeIt  write<<


using namespace std;


int main(int argc, char *argv[]){

  int dirichletpointconditions = 0;
  int bodyforceconditions      = 0;  
  int dirichletconditions      = 1;
  int tractionconditions       = 0;
  int spc                      = 2;
  int lag                      = 1;

  bool RCM          = true;  
  bool help         = false;
  bool debug        = false;
  bool useGFP       = false;
  bool timelog      = false;
  bool top2vol      = false;
  bool pipegnu      = false;
  bool testflags    = false;
  bool vectorial    = false;
  bool supercomp    = false;
  bool fastmethod   = true;
  bool Sequential   = false;
  bool dirichletbc  = false;
  bool energydecomp = false;


  string Model                   = "hybrid-phase-field";
  string Solver                  = "cg";
  string PostProcess             = "u";
  string Prblm                   = "linear-elasticity";
  string Partitioner             = "parmetis";
  string doublecouple            = "unused";
  string Preconditioner          = "jacobi";
  string NonLinearMethod         = "Picard";
  string SubPreconditioner       = "ilu";
  string TimeDiscretization      = "generalized-alpha";

//=====================================================================================
//---- Comandline Parameters -----
//=====================================================================================

  for(int i=0; i<argc; i++){

    string argvdummy  = argv[i]   ;

    if( argvdummy == "-dirichletpointconditions") dirichletpointconditions = stoi(argv[i+1]);
    if( argvdummy == "-dirichletconditions"     ) dirichletconditions      = stoi(argv[i+1]);
    if( argvdummy == "-bodyforceconditions"     ) bodyforceconditions      = stoi(argv[i+1]);        
    if( argvdummy == "-tractionconditions"      ) tractionconditions       = stoi(argv[i+1]);
    if( argvdummy == "-dimension"               ) spc                      = stoi(argv[i+1]);
    if( argvdummy == "-lagrange"                ) lag                      = stoi(argv[i+1]);

    if( argvdummy == "-useRCM"          ) RCM                              = true;
    if( argvdummy == "-help"            ) help                             = true;
    if( argvdummy == "-debug"           ) debug                            = true;
    if( argvdummy == "-useGFP"          ) useGFP                           = true;
    if( argvdummy == "-pipegnu"         ) pipegnu                          = true;
    if( argvdummy == "-testflags"       ) testflags                        = true;
    if( argvdummy == "-timelog"         ) timelog                          = true;
    if( argvdummy == "-vectorial"       ) vectorial                        = true;
    if( argvdummy == "-supercomp"       ) supercomp                        = true;
    if( argvdummy == "-fastmethod"      ) fastmethod                       = true;
    if( argvdummy == "-sequential"      ) Sequential                       = true;
    if( argvdummy == "-dirichletbc"     ) dirichletbc                      = true;
    if( argvdummy == "-energydecomp"    ) energydecomp                     = true;
    if( argvdummy == "-top2vol-meshing" ) top2vol                          = true;        

    if( argvdummy == "-model"              ) Model                         = argv[i+1];
    if( argvdummy == "-solver"             ) Solver                        = argv[i+1];
    if( argvdummy == "-problem"            ) Prblm                         = argv[i+1];
    if( argvdummy == "-partitioner"        ) Partitioner                   = argv[i+1];
    if( argvdummy == "-postprocess"        ) PostProcess                   = argv[i+1];
    if( argvdummy == "-doublecouple"       ) doublecouple                  = argv[i+1];
    if( argvdummy == "-preconditioner"     ) Preconditioner                = argv[i+1];
    if( argvdummy == "-nonlinearmethod"    ) NonLinearMethod               = argv[i+1];
    if( argvdummy == "-subpreconditioner"  ) SubPreconditioner             = argv[i+1];
    if( argvdummy == "-timediscretization" ) TimeDiscretization            = argv[i+1];


  }

  int labelBodyForce=1;
  int labelDirichlet=2;
  int labelDirichletTraction=2;  
  if(Prblm=="damage" && Model=="hybrid-phase-field")labelDirichlet=1;
  if(Prblm=="damage" && Model=="hybrid-phase-field")dirichletbc=true;
  if(Prblm=="damage" && Model=="Mazar")dirichletbc=true;
  if(Prblm=="soildynamics")dirichletconditions      = 0;
  int labLface=2;if(spc==3)labLface=1;
  int labRface=4;if(spc==3)labRface=2;  
  if(spc==3)labelBodyForce=6;
  
  bool ParaViewPostProcess = false; 
  
if(   PostProcess=="u"   || PostProcess=="v"   || PostProcess=="a"   || PostProcess=="d"
   || PostProcess=="uv"  || PostProcess=="vu"  || PostProcess=="au"  || PostProcess=="ua"
   || PostProcess=="av"  || PostProcess=="va"  || PostProcess=="ud"  || PostProcess=="du"
   || PostProcess=="uva" || PostProcess=="uav" || PostProcess=="vau" || PostProcess=="vua"
   || PostProcess=="auv" || PostProcess=="ava" )  ParaViewPostProcess = true;

//=====================================================================================
//---- PSD Logo on commandline -----
//=====================================================================================

  cout << "===================================================================" << endl;
  cout << "                        ___               __                       " << endl;
  cout << "                      / __ \\   _____   __/  /                     " << endl;
  cout << "                     / /_/ /  / ___/ / __  /                       " << endl;
  cout << "                    / ___ /  (__  ) / /_/ /                        " << endl;
  cout << "                   /_/      /____/  \\___ /                        " << endl;
  cout << "                                                                   " << endl;
  cout << "===================================================================" << endl;

  if(testflags){

  cout << "===================================================================" << endl;
  cout << "                        INT ARGUMENTS                              " << endl;
  cout << "===================================================================" << endl;

  cout << " dirichletpointconditions are -------> "<<  dirichletpointconditions << endl;
  cout << " dirichletconditions are ------------> "<<  dirichletconditions      << endl;
  cout << " bodyforceconditions are ------------> "<<  bodyforceconditions      << endl;  
  cout << " tractionconditions are -------------> "<<  tractionconditions       << endl;
  cout << " lagrange order is ------------------> "<<  lag                      << endl;
  cout << " problem dimension is ---------------> "<<  spc                      << endl;

  cout << "===================================================================" << endl;
  cout << "                        STRING ARGUMENTS                           " << endl;
  cout << "===================================================================" << endl;

  cout << " partitioner is----------------------> "<<  Partitioner              << endl;
  cout << " solver is---------------------------> "<<  Solver                   << endl;
  cout << " postProcess is----------------------> "<<  PostProcess              << endl;
  cout << " doublecouple is---------------------> "<<  doublecouple             << endl;
  cout << " preconditioner is-------------------> "<<  Preconditioner           << endl;
  cout << " subPreconditioner is----------------> "<<  SubPreconditioner        << endl;
  cout << " timeDiscretization is---------------> "<<  TimeDiscretization       << endl;

  cout << "===================================================================" << endl;
  cout << "                        BOOL ARGUMENTS                             " << endl;
  cout << "===================================================================" << endl;

  cout << " useRCM is --------------------------> " << RCM                      << endl;
  cout << " help is ----------------------------> " << help                     << endl;
  cout << " debug is ---------------------------> " << debug                    << endl;
  cout << " useGFP is --------------------------> " << useGFP                   << endl;
  cout << " pipegnu is -------------------------> " << pipegnu                  << endl;
  cout << " testflags is -----------------------> " << testflags                << endl;
  cout << " timelog is -------------------------> " << timelog                  << endl;
  cout << " vectorial is -----------------------> " << vectorial                << endl;
  cout << " supercomp is -----------------------> " << supercomp                << endl;
  cout << " fastmethod is ----------------------> " << fastmethod               << endl;
  cout << " sequential is ----------------------> " << Sequential               << endl;
  cout << " dirichletbc is ---------------------> " << dirichletbc              << endl;
  cout << " energydecomp is --------------------> " << energydecomp             << endl;
  }


  cout << "                                                                   " << endl;

if(Sequential){
	system("sed -i 's/^ffmpi=FreeFem++-mpi$/ffmpi=FreeFem++/g' PSD_Solve;");
	system("sed -i 's/^j=1;$/j=1;mpi_run_option=;a[0]=;/g' PSD_Solve;"); 
}

if(!Sequential){
	system("sed -i 's/^ffmpi=FreeFem++$/ffmpi=FreeFem++-mpi/g' PSD_Solve;");
	system("sed -i 's#^j=1;mpi_run_option=;a\\[0\\]=;$#j=1;#g' PSD_Solve;"); 
}			 

 #include "Help.hpp"

if(!help){
 #include "Main.hpp"
 #include "Mesh.hpp"
 #include "Macros.hpp"
 #include "FemParameters.hpp"
 #include "OtherParameters.hpp"
 #include "ControlParameters.hpp"
 #include "VariationalFormulation.hpp"
 #include "LinearFormBuilderAndSolver.hpp"
 #include "PostProcessor.hpp"

  cout << "                                                                   " << endl;
  cout << "===================================================================" << endl;

 if(ParaViewPostProcess)
  system("mkdir -p VTUs");

  cout << "                                                                   " << endl;
  cout << " PSD solver is now ready to run.                                   " << endl;
  cout << "                                                                   " << endl;
  cout << " For a simulation with $ number of processes run your solver with  " << endl;
  cout << "                                                                   " << endl;
  cout << "     ff-mpirun -np $ Main.edp                                      " << endl;
  cout << "                                                                   " << endl;
  cout << " For a sequential simulation run your solver with                  " << endl;
  cout << "                                                                   " << endl;
  cout << "     FreeFem++ Main.edp                                            " << endl;
  cout << "                                                                   " << endl;
  cout << "===================================================================" << endl;
}
return 0;
}
