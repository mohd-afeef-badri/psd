/**************************************************************************************
*                                                                                     *
* Author:  Mohd Afeef BADRI, Rania SAADI                                              *
* Date:    15/10/2024                                                                 *
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

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "HeaderMacro.hpp"

#define writeIt  write<<
#define codeSnippet  write<<

#define IsArgumentValueTrue   if(argvalue=="yes"||argvalue=="on"||argvalue=="true"||argvalue=="1")
#define IsArgumentValueFalse  if(argvalue=="no"||argvalue=="off"||argvalue=="false"||argvalue=="0")


using namespace std;


int main(int argc, char *argv[]){

  int dirichletpointconditions = 0;
  int bodyforceconditions      = 0;
  int dirichletconditions      = 1;
  int tractionconditions       = 0;
  int adaptmeshiteration       = 5;
  int spc                      = 2;
  int lag                      = 1;

  bool RCM          		= true ;
  bool help         		= false;
  bool debug        		= false;
  bool useGFP       		= false;
  bool timelog      		= false;
  bool top2vol      		= false;
  bool pipegnu      		= false;
  bool testflags    		= false;
  bool adaptmesh    		= false;
  bool vectorial    		= false;
  bool useMfront    		= false;
  bool fastmethod   		= true ;
  bool Sequential   		= false;
  bool pointprobe   		= false;
  bool dirichletbc  		= false;
  bool energydecomp 		= false;
  bool versionpsd   		= false;
  bool plotreaction 		= false;
  bool constrainHPF 		= false;
  bool precracked   		= false;
  bool getenergies  		= false;
  bool reactionforce		= false;
  bool adaptmeshisotropy 	= true;

  bool   errorArgument         = false  ;
  bool   wrongArgument         = false  ;
  string wrongArgumentWarning  = ""     ;

  string Validation              = "NULL";
  string Model                   = "hybrid_phase_field";
  string Solver                  = "cg";
  string PostProcess             = "null";
  string Prblm                   = "linear_elasticity";
  string Partitioner             = "parmetis";
  string doublecouple            = "unused";
  string Preconditioner          = "jacobi";
  string NonLinearMethod         = "Picard";
  string reactionforcemethod     = "stress_based";
  string SubPreconditioner       = "ilu";
  string TimeDiscretization      = "generalized_alpha";
  string AdaptmeshBackend        = "freefem";
  string AdaptmeshMetricBackend  = "freefem";
  string ParmmgMethod            = "NULL";
  string AdaptmeshType		       = "";

//=====================================================================================
//---- Comandline Parameters -----
//=====================================================================================

  argv[argc] = argv[argc-1];       // Hacky way to avoid C++ warning, ignore this line

  for(int i=0; i<argc; i++){

    string argvdummy  = argv[i]   ;
    string argvalue   = argv[i+1] ;

    #include "DetectWrongArgument.hpp"

    if( argvdummy == "-dirichletpointconditions") dirichletpointconditions = stoi(argv[i+1]);
    if( argvdummy == "-dirichletconditions"     ) dirichletconditions      = stoi(argv[i+1]);
    if( argvdummy == "-bodyforceconditions"     ) bodyforceconditions      = stoi(argv[i+1]);
    if( argvdummy == "-tractionconditions"      ) tractionconditions       = stoi(argv[i+1]);
    if( argvdummy == "-adaptmesh_iter"          ) adaptmeshiteration       = stoi(argv[i+1]);
    if( argvdummy == "-dimension"               ) spc                      = stoi(argv[i+1]);
    if( argvdummy == "-lagrange"                ) lag                      = stoi(argv[i+1]);

    if( argvdummy == "-useRCM"                  ) {                     RCM          = true;
                                                   IsArgumentValueTrue  RCM          = true;
                                                   IsArgumentValueFalse RCM          = false;
                                                  }

    if( argvdummy == "-useGFP"                  ) {                     useGFP       = true;
                                                   IsArgumentValueTrue  useGFP       = true;
                                                   IsArgumentValueFalse useGFP       = false;
                                                  }

    if( argvdummy == "-useMfront"               ) {                     useMfront    = true;
                                                   IsArgumentValueTrue  useMfront    = true;
                                                   IsArgumentValueFalse useMfront    = false;
                                                  }

    if( argvdummy == "-activeplot"              ) {                     pipegnu      = true;
                                                   IsArgumentValueTrue  pipegnu      = true;
                                                   IsArgumentValueFalse pipegnu      = false;
                                                  }

    if( argvdummy == "-timelog"                 ) {                     timelog      = true;
                                                   IsArgumentValueTrue  timelog      = true;
                                                   IsArgumentValueFalse timelog      = false;
                                                  }

    if( argvdummy == "-vectorial"               ) {                    vectorial     = true;
    if( argvdummy == "-vectorial"               ) IsArgumentValueTrue  vectorial     = true;
    if( argvdummy == "-vectorial"               ) IsArgumentValueFalse vectorial     = false;
                                                  }

    if( argvdummy == "-sequential"              ) {                     Sequential   = true;
                                                   IsArgumentValueTrue  Sequential   = true;
                                                   IsArgumentValueFalse Sequential   = false;
                                                  }

    if( argvdummy == "-dirichletbc"             ) {                     dirichletbc  = true;
                                                   IsArgumentValueTrue  dirichletbc  = true;
                                                   IsArgumentValueFalse dirichletbc  = false;
                                                  }

    if( argvdummy == "-energydecomp"            ) {                     energydecomp = true;
                                                   IsArgumentValueTrue  energydecomp = true;
                                                   IsArgumentValueFalse energydecomp = false;
                                                  }

    if( argvdummy == "-pointprobe"              ) {                     pointprobe   = true;
                                                   IsArgumentValueTrue  pointprobe   = true;
                                                   IsArgumentValueFalse pointprobe   = false;
                                                  }

    if( argvdummy == "-top2vol-meshing"         ) {                     top2vol      = true;
                                                   IsArgumentValueTrue  top2vol      = true;
                                                   IsArgumentValueFalse top2vol      = false;
                                                  }

    if( argvdummy == "-getenergies"             ) {                     getenergies = true;
                                                   IsArgumentValueTrue  getenergies = true;
                                                   IsArgumentValueFalse getenergies = false;
                                                  }

    if( argvdummy == "-getreactionforce"        ) {                     reactionforce = true;
                                                   IsArgumentValueTrue  reactionforce = true;
                                                   IsArgumentValueFalse reactionforce = false;
                                                  }

    if( argvdummy == "-plotreactionforce"       ) {                     plotreaction = true;
                                                   IsArgumentValueTrue  plotreaction = true;
                                                   IsArgumentValueFalse plotreaction = false;
                                                  }

    if( argvdummy == "-constrainHPF"            ) {                     constrainHPF = true;
                                                   IsArgumentValueTrue  constrainHPF = true;
                                                   IsArgumentValueFalse constrainHPF = false;
                                                  }


    if( argvdummy == "-adaptmesh"               ) {                     adaptmesh    = true;
                                                   IsArgumentValueTrue  adaptmesh    = true;
                                                   IsArgumentValueFalse adaptmesh    = false;
                                                  }

    if( argvdummy == "-crackdirichletcondition" ) {                     precracked   = true;
                                                   IsArgumentValueTrue  precracked   = true;
                                                   IsArgumentValueFalse precracked   = false;
                                                  }

    if( argvdummy == "-withmaterialtensor"      ) {                     fastmethod   = false;
                                                   IsArgumentValueTrue  fastmethod   = false;
                                                   IsArgumentValueFalse fastmethod   = true;
                                                  }


    if( argvdummy == "-testflags"               ) testflags  = true;
    if( argvdummy == "-debug"                   ) debug      = true;
    if( argvdummy == "-help"                    ) help       = true;
    if( argvdummy == "-version"                 ) versionpsd = true;
    if( argvdummy == "--version"                ) versionpsd = true;
    if( argvdummy == "-h"                       ) help       = true;


    if( argvdummy == "-model"                   ) Model                    = argv[i+1];
    if( argvdummy == "-solver"                  ) Solver                   = argv[i+1];
    if( argvdummy == "-problem"                 ) Prblm                    = argv[i+1];
    if( argvdummy == "-partitioner"             ) Partitioner              = argv[i+1];
    if( argvdummy == "-postprocess"             ) PostProcess              = argv[i+1];
    if( argvdummy == "-doublecouple"            ) doublecouple             = argv[i+1];
    if( argvdummy == "-preconditioner"          ) Preconditioner           = argv[i+1];
    if( argvdummy == "-nonlinearmethod"         ) NonLinearMethod          = argv[i+1];
    if( argvdummy == "-reactionforce"           ) reactionforcemethod      = argv[i+1];
    if( argvdummy == "-validation"              ) Validation               = argv[i+1];
    if( argvdummy == "-subpreconditioner"       ) SubPreconditioner        = argv[i+1];
    if( argvdummy == "-timediscretization"      ) TimeDiscretization       = argv[i+1];
    if( argvdummy == "-adaptmesh_backend"       ) AdaptmeshBackend         = argv[i+1];
    if( argvdummy == "-adaptmesh_metric_backend") AdaptmeshMetricBackend   = argv[i+1];
    if( argvdummy == "-adaptmesh_parmmg_method" ) ParmmgMethod             = argv[i+1];

    if( argvdummy == "-adaptmesh_type"		) {
	    					  AdaptmeshType		   = argv[i+1];
						  adaptmeshisotropy  	   = (AdaptmeshType == "isotropic") ? true : (AdaptmeshType == "anisotropic") ? false : adaptmeshisotropy;
    						  }
  }

 #include "ErrorWrongArgument.hpp"

 if(wrongArgument)
   cout << wrongArgumentWarning << endl;

  int labelBodyForce=1;
  int labelDirichlet=2;
  int labelDirichletTraction=2;
  if(Prblm=="damage" && Model=="hybrid_phase_field")labelDirichlet=1;
  if(Prblm=="damage" && Model=="hybrid_phase_field")dirichletbc=true;
  if(Prblm=="damage" && Model=="Mazar")dirichletbc=true;
  if(Prblm=="soildynamics")dirichletconditions      = 0;
  if(useMfront)fastmethod = false;
  int labLface=2;if(spc==3)labLface=1;
  int labRface=4;if(spc==3)labRface=2;
  if(spc==3)labelBodyForce=6;

  if(plotreaction)
    pipegnu = true;

  bool ParaViewPostProcess = false;

  int Fdofs = spc;
  if(vectorial)
      Fdofs = spc+1;

if(   PostProcess=="u"   || PostProcess=="v"   || PostProcess=="a"   || PostProcess=="d"
   || PostProcess=="uv"  || PostProcess=="vu"  || PostProcess=="au"  || PostProcess=="ua"
   || PostProcess=="av"  || PostProcess=="va"  || PostProcess=="ud"  || PostProcess=="du"
   || PostProcess=="uva" || PostProcess=="uav" || PostProcess=="vau" || PostProcess=="vua"
   || PostProcess=="auv" || PostProcess=="avu" )  ParaViewPostProcess = true;

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
  cout << " adaptmeshiterations are ------------> "<<  adaptmeshiteration       << endl;
  cout << " problem dimension is ---------------> "<<  spc                      << endl;
  cout << " lagrange order is ------------------> "<<  lag                      << endl;

  cout << "===================================================================" << endl;
  cout << "                        STRING ARGUMENTS                           " << endl;
  cout << "===================================================================" << endl;

  cout << " solver is---------------------------> "<<  Solver                   << endl;
  cout << " partitioner is----------------------> "<<  Partitioner              << endl;
  cout << " postProcess is----------------------> "<<  PostProcess              << endl;
  cout << " doublecouple is---------------------> "<<  doublecouple             << endl;
  cout << " reactionforce is--------------------> "<<  reactionforcemethod      << endl;
  cout << " preconditioner is-------------------> "<<  Preconditioner           << endl;
  cout << " subPreconditioner is----------------> "<<  SubPreconditioner        << endl;
  cout << " timeDiscretization is---------------> "<<  TimeDiscretization       << endl;
  cout << " adaptmesh_backend is----------------> "<<  AdaptmeshBackend 	      << endl;
  cout << " adaptmesh_metric_backend is---------> "<<  AdaptmeshMetricBackend 	<< endl;
  cout << " adaptmesh_type is-------------------> "<<  AdaptmeshType 		        << endl;
  cout << " adaptmesh_isotropy is --------------> "<<  adaptmeshisotropy	      << endl;
  cout << " adaptmesh_parmmg_method is ---------> "<<  ParmmgMethod      	      << endl;

  cout << "===================================================================" << endl;
  cout << "                        BOOL ARGUMENTS                             " << endl;
  cout << "===================================================================" << endl;

  cout << " help is ----------------------------> " << help                     << endl;
  cout << " debug is ---------------------------> " << debug                    << endl;
  cout << " useGFP is --------------------------> " << useGFP                   << endl;
  cout << " useRCM is --------------------------> " << RCM                      << endl;
  cout << " timelog is -------------------------> " << timelog                  << endl;
  cout << " vectorial is -----------------------> " << vectorial                << endl;
  cout << " useMfront is -----------------------> " << useMfront                << endl;
  cout << " testflags is -----------------------> " << testflags                << endl;
  cout << " sequential is ----------------------> " << Sequential               << endl;

  cout << " adaptmesh is -----------------------> " << adaptmesh                << endl;
  cout << " pointprobe is ----------------------> " << pointprobe               << endl;
  cout << " activeplot is ----------------------> " << pipegnu                  << endl;
  cout << " dirichletbc is ---------------------> " << dirichletbc              << endl;
  cout << " getenergies is ---------------------> " << getenergies              << endl;
  cout << " energydecomp is --------------------> " << energydecomp             << endl;
  cout << " constrainedHPF is ------------------> " << constrainHPF             << endl;
  cout << " getreactionforce is ----------------> " << reactionforce            << endl;
  cout << " plotreactionforce is ---------------> " << pipegnu                  << endl;
  cout << " withmaterialtensor is --------------> " << fastmethod               << endl;
  cout << " crackdirichletcondition is ---------> " << precracked               << endl;
  }


  cout << "                                                                   " << endl;

if(versionpsd){
  cout << "  PSD Version 2.6 " << endl;
  cout << "    Copyright (C) CEA 2019 - 2025 "<< endl;
  cout << "                                                                   " << endl;
  cout << "    This is free software; see the source for copying conditions.  " << endl;
  cout << "    There is NO warranty; not even for MERCHANTABILITY or FITNESS  " << endl;
  cout << "    FOR A PARTICULAR PURPOSE.                                      " << endl;
  cout << "                                                                   " << endl;
  cout << "    Report bugs/issues ::    mohd-afeef.badri@cea.fr               " << endl;
  cout << "                                                                   " << endl;
  cout << "===================================================================" << endl;
  exit(0);
}

if(help)
{
 #include "Help.hpp"
 exit(0);
}

if(Validation == "Iwan"){
 #include "Validation/Iwan.hpp"

 cout << "                                                                   " << endl;
 cout << " PSD solver is now ready to run the  validation case               " << endl;
 cout << "                                                                   " << endl;
 cout << " For a simulation with N number of processes run your solver with  " << endl;
 cout << "                                                                   " << endl;
 cout << "     PSD_Solve -np N PSD-validation**.edp                          " << endl;
 cout << "                                                                   " << endl;
 cout << " For a sequential simulation run your solver with                  " << endl;
 cout << "                                                                   " << endl;
 cout << "     PSD_Solve_Seq PSD-validation**.edp                            " << endl;
 cout << "                                                                   " << endl;
 cout << "===================================================================" << endl;

 exit(0);
}


 #include "Main.hpp"
 #include "MeshAndFeSpace.hpp"
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
  cout << " For a simulation with N number of processes run your solver with  " << endl;
  cout << "                                                                   " << endl;
  cout << "     PSD_Solve -np N Main.edp                                      " << endl;
  cout << "                                                                   " << endl;
  cout << " For a sequential simulation run your solver with                  " << endl;
  cout << "                                                                   " << endl;
  cout << "     PSD_Solve_Seq Main.edp                                        " << endl;
  cout << "                                                                   " << endl;
  cout << "===================================================================" << endl;

return 0;
}
