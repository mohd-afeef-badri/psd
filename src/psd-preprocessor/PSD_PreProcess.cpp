/**************************************************************************************
*                                                                                     *
* Author:  Mohd Afeef BADRI                                                           *
* Date:	   20/04/2020                                                                 *
* Type:    Execution file                                                             *
* Comment: Once executed this file generates following edp files: Main, Macros, Mesh, *
*          MeshPartitioning,   VariationalFormulations,   BoundaryAndSourceConditions *
*          Parameters,  LinearFormBuilderAndSolver, and PostProcessor. All these .edp * 
*          files combine  together to form  a fully tailored  solid mechanics solver. *
*	   Commandline flags  are  used to controls the nature of the generated file.     *
*          One   is    advised     to   carefully   go   through   these   arguments. *
* Compile: Use a g++/icpc compiler C++ compiler                                       *
*                                                                                     *
**************************************************************************************/

//=====================================================================================
// ------ All command line argument descriptions [ARGUMENTS] ------
//=====================================================================================
/*

  -------------------------------------------------------------------------------------

  -dirichletpointconditions [int]  Number of Dirchlet points.  Default 1.

  -dirichletconditions      [int]  Number of Dirchlet boundries.  Default 1.

  -tractionconditions       [int]  Number of Neumann/traction boundrie.  Default 1.

  -dimension                [int]  Dimension of proble. 2 for 2D 3 for 3D. Default 2.
  
  -lagrange                 [int]  Lagrange order used for building FE space. Options 
  			                       are  1 for P1 or 2 for P2. Defaut is P1.
  
  -------------------------------------------------------------------------------------

  -partitioner    [sting] Mesh partitioner to be used. Options are "metis"
  			  "parmetis" "scotch" or "ptstoch".
  			
  -partitioner parmetis   Mesh partitioner is parmetis. Additional option is 
  			  active '-parmetis_worker [int]'.			
 
  -------------------------------------------------------------------------------------
 			  
  -help        [bool]     To activate helping message on the terminal. Default OFF. 
  			  
  -plot        [bool]     To activate plotting routine. Default OFF.

  -debug       [bool]     To activate debug openGL plotting routine. Default OFF.

  -dynamic     [bool]	  To activate dynamic solver. Default OFF.
  
  -useGFP      [bool]	  To activate use of GoFastPlugins. A suite of c++ plugins.
  
  -timelog     [bool]	  To setup time logging for various phases of the solver.  

  -useRCM      [bool]	  To activate mesh level renumbering via Reverse Cuthill Mckee.   
  
  -pipegnu     [bool]	  To activate realtime pipe plotting using GnuPlot. Default OFF.

  -pointbc     [bool]     To activate Dirichlet boundary condition on point. Default OFF.
  
  -nonlinear   [bool]     To activate non-linear mechanics (Crack). Default OFF.
  
  -bodyforce   [bool]     To activate volumetric source term (body force). Default OFF.

  -vectorial   [bool]	  To generate vectorial space solver for non-linear. Default OFF.  
    
  -supercomp   [bool]	  To be used when using a cluster/supercomputer. Default OFF.   
    
  -dirichletbc [bool]     To activate Dirichlet boundary condition. Default ON.
  
  -tractionbc  [bool]     To activate traction boundary condition (Neumann).Default OFF.
  
  -quasistatic [bool]     To activate quasi-static damage mechanics module.Default OFF.  

  -energydecomp[bool]     To activate hybrid phase field energy decomposition.  
  
  -sequential  [bool]	  To generate a sequential ff++ solver. Default OFF.

*/


#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std;


int main(int argc, char *argv[]){

  int dirichletpointconditions = 0;
  int dirichletconditions      = 1;
  int tractionconditions       = 0;
  int spc                      = 2;
  int lag                      = 1;

  bool RCM          = true;
  bool help         = false;
  bool debug        = false;
  bool useGFP       = false;
  bool pointbc      = false;
  bool timelog      = false;
  bool plotAll      = false;
  bool dynamic      = false;    
  bool pipegnu      = false;
  bool plotTime     = false;
  bool testflags    = false; 
  bool vectorial    = false;
  bool bodyforce    = false;
  bool nonlinear    = false;
  bool supercomp    = false;
  bool elasticity   = false;    
  bool tractionbc   = false; 
  bool fastmethod   = false;       
  bool Sequential   = false;
  bool quasistatic  = false;
  bool dirichletbc  = false;
  bool energydecomp = false;  
  bool soildynamics = false;  

  string Solver                  = "cg"; 
  string PostProcess             = "u"; 
  string Partitioner             = "parmetis";
  string Preconditioner          = "jacobi";
  string SubPreconditioner       = "ilu";
  string TimeDiscretization      = "generalized-alpha";


/*

  string Solver=getARGV("-solver", "cg"); 
  string PostProcess=getARGV("-postprocess", "u"); 
  string Partitioner=getARGV("-partitioner", "parmetis");
  string Preconditioner=getARGV("-preconditioner", "jacobi");
  string SubPreconditioner=getARGV("-subpreconditioner", "ilu");
  string TimeDiscretization=getARGV("-timediscretization", "generalized-alpha");
  
  
  bool RCM          =  usedARGV("-useRCM"       ) !=  1;
  bool help         =  usedARGV("-help"         ) != -1;
  bool debug        =  usedARGV("-debug"        ) != -1;
  bool useGFP       =  usedARGV("-useGFP"       ) != -1;  
  bool plotAll      =  usedARGV("-plot"         ) != -1;
  bool dynamic      =  usedARGV("-dynamic"      ) != -1;    
  bool pipegnu      =  usedARGV("-pipegnu"      ) != -1;
  bool plotTime     =  usedARGV("-timepvd"      ) != -1;
  bool pointbc      =  usedARGV("-pointbc"      ) != -1;
  bool timelog      =  usedARGV("-timelog"      ) != -1;
  bool vectorial    =  usedARGV("-vectorial"    ) != -1;  
  bool bodyforce    =  usedARGV("-bodyforce"    ) != -1;
  bool nonlinear    =  usedARGV("-nonlinear"    ) != -1; 
  bool elasticity   =  usedARGV("-Lelasticty"   ) != -1;            
  bool supercomp    =  usedARGV("-supercomp"    ) != -1;       
  bool tractionbc   =  usedARGV("-tractionbc"   ) != -1; 
  bool fastmethod   =  usedARGV("-fastmethod"   ) != -1;       
  bool Sequential   =  usedARGV("-sequential"   ) != -1;
  bool quasistatic  =  usedARGV("-quasistatic"  ) != -1;
  bool dirichletbc  =  usedARGV("-dirichletbc"  ) !=  1;
  bool energydecomp =  usedARGV("-energydecomp" ) != -1;  
  bool soildynamics =  usedARGV("-soildynamics" ) != -1;


  int dirichletpointconditions = getARGV("-dirichletpointconditions", 0);
  int dirichletconditions      = getARGV("-dirichletconditions", 1);
  int tractionconditions       = getARGV("-tractionconditions" , 0);
  int spc                      = getARGV("-dimension", 2);
  int lag                      = getARGV("-lagrange" , 1);
*/

//=====================================================================================
//---- Comandline Parameters -----
//=====================================================================================

  for(int i=0; i<argc; i++){
  
    string argvdummy  = argv[i]   ;

    if( argvdummy == "-dirichletpointconditions") dirichletpointconditions = stoi(argv[i+1]);
    if( argvdummy == "-dirichletconditions"     ) dirichletconditions      = stoi(argv[i+1]);
    if( argvdummy == "-tractionconditions"      ) tractionconditions       = stoi(argv[i+1]);
    if( argvdummy == "-dimension"               ) spc                      = stoi(argv[i+1]);
    if( argvdummy == "-lagrange"                ) lag                      = stoi(argv[i+1]);

    if( argvdummy == "-useRCM"       ) RCM            = true;      
    if( argvdummy == "-help"         ) help           = true;              
    if( argvdummy == "-debug"        ) debug          = true;
    if( argvdummy == "-useGFP"       ) useGFP         = true;  
    if( argvdummy == "-plot"         ) plotAll        = true;
    if( argvdummy == "-dynamic"      ) dynamic        = true;    
    if( argvdummy == "-pipegnu"      ) pipegnu        = true;
    if( argvdummy == "-timepvd"      ) plotTime       = true;
    if( argvdummy == "-testflags"    ) testflags      = true;
    if( argvdummy == "-pointbc"      ) pointbc        = true;
    if( argvdummy == "-timelog"      ) timelog        = true;
    if( argvdummy == "-vectorial"    ) vectorial      = true;  
    if( argvdummy == "-bodyforce"    ) bodyforce      = true;
    if( argvdummy == "-nonlinear"    ) nonlinear      = true; 
    if( argvdummy == "-Lelasticty"   ) elasticity     = true;            
    if( argvdummy == "-supercomp"    ) supercomp      = true;       
    if( argvdummy == "-tractionbc"   ) tractionbc     = true; 
    if( argvdummy == "-fastmethod"   ) fastmethod     = true;       
    if( argvdummy == "-sequential"   ) Sequential     = true;
    if( argvdummy == "-quasistatic"  ) quasistatic    = true;
    if( argvdummy == "-dirichletbc"  ) dirichletbc    = true;
    if( argvdummy == "-energydecomp" ) energydecomp   = true;  
    if( argvdummy == "-soildynamics" ) soildynamics   = true;
  
    if( argvdummy == "-solver"             ) Solver               = argv[i+1];
    if( argvdummy == "-partitioner"        ) Partitioner          = argv[i+1];     
    if( argvdummy == "-postprocess"        ) PostProcess          = argv[i+1];     
    if( argvdummy == "-preconditioner"     ) Preconditioner       = argv[i+1];     
    if( argvdummy == "-subpreconditioner"  ) SubPreconditioner    = argv[i+1];   
    if( argvdummy == "-timediscretization" ) TimeDiscretization   = argv[i+1];         

    
  }
  
  int labelDirichlet=2; 
  if(nonlinear)labelDirichlet=1;

  int labLface=2;if(spc==3)labLface=1;  
  int labRface=4;if(spc==3)labRface=2;  

//=====================================================================================
//---- PSD Logo on commandline -----
//=====================================================================================

  cout << "===================================================================" << endl;
  cout << "                        ___               __                       " << endl;
  cout << "                      / __ \\   _____   __/  /                      " << endl;
  cout << "                     / /_/ /  / ___/ / __  /                       " << endl;
  cout << "                    / ___ /  (__  ) / /_/ /                        " << endl;
  cout << "                   /_/      /____/  \\___ /                         " << endl;
  cout << "                                                                   " << endl;
  cout << "===================================================================" << endl;

  if(testflags){

  cout << "===================================================================" << endl;
  cout << "                        INT ARGUMENTS                              " << endl;
  cout << "===================================================================" << endl;

  cout << " dirichletpointconditions are -------> "<<  dirichletpointconditions << endl;
  cout << " dirichletconditions are ------------> "<<  dirichletconditions      << endl;
  cout << " tractionconditions are -------------> "<<  tractionconditions       << endl;
  cout << " lagrange order is ------------------> "<<  lag                      << endl;
  cout << " problem dimension is ---------------> "<<  spc                      << endl;

  cout << "===================================================================" << endl;
  cout << "                        STRING ARGUMENTS                           " << endl;
  cout << "===================================================================" << endl;

  cout << " partitioner is----------------------> "<<  Partitioner              << endl;
  cout << " solver is---------------------------> "<<  Solver                   << endl;
  cout << " postProcess is----------------------> "<<  PostProcess              << endl;
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
  cout << " plot is ----------------------------> " << plotAll                  << endl;
  cout << " dynamic is -------------------------> " << dynamic                  << endl;    
  cout << " pipegnu is -------------------------> " << pipegnu                  << endl;
  cout << " timepvd is -------------------------> " << plotTime                 << endl;
  cout << " testflags is -----------------------> " << testflags                << endl;
  cout << " pointbc is -------------------------> " << pointbc                  << endl;
  cout << " timelog is -------------------------> " << timelog                  << endl;
  cout << " vectorial is -----------------------> " << vectorial                << endl;  
  cout << " bodyforce is -----------------------> " << bodyforce                << endl;
  cout << " nonlinear is -----------------------> " << nonlinear                << endl; 
  cout << " Lelasticty is ----------------------> " << elasticity               << endl;            
  cout << " supercomp is -----------------------> " << supercomp                << endl;       
  cout << " tractionbc is ----------------------> " << tractionbc               << endl; 
  cout << " fastmethod is ----------------------> " << fastmethod               << endl;       
  cout << " sequential is ----------------------> " << Sequential               << endl;
  cout << " quasistatic is ---------------------> " << quasistatic              << endl;
  cout << " dirichletbc is ---------------------> " << dirichletbc              << endl;
  cout << " energydecomp is --------------------> " << energydecomp             << endl;  
  cout << " soildynamics is --------------------> " << soildynamics             << endl;
  }

  cout << "                                                                   " << endl;

#include "Help.hpp"
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

if(plotAll)
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

return 0;
}
