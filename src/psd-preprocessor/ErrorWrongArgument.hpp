/**************************************************************************************
*                                                                                     *
* Author : Mohd Afeef BADRI                                                           *
* Email  : mohd-afeef.badri@cea.fr                                                    *
* Date   : 20/05/2021                                                                 *
* Type   : Support file                                                               *
*                                                                                     *
* Comment: This support file is  responsible for detecting wrong commandline flag     *
*          provided  by  the  user. Depending on the processed info an error or a     *
*          warning will be displayed on the terminal.                                 *
*                                                                                     *
**************************************************************************************/


//----------------------------------------------------------
// Wrong Integer Argument
//---------------------------------------------------------
  for(int i=0; i<argc; i++){

    string argvdummy  = argv[i]   ;
    string argvalue;

    #include "DetectWrongArgument.hpp"

    if( argvdummy == "-dirichletpointconditions")
    { 
      argvalue = argv[i+1];
      if (argvalue.find(".") != string::npos){
      cout << 
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"          
          "The flag \033[1;31m-dirichletpointconditions\033[0m only accepts \033[1;34mInteger\033[0m values\n"
          "  \033[1;31m-dirichletpointconditions "<< argvalue << "\033[0m is not acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
      }   
    }
                     
    if( argvdummy == "-dirichletconditions"     )
    { 
      argvalue = argv[i+1];
      if (argvalue.find(".") != string::npos){
      cout << 
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"          
          "The flag \033[1;31m-dirichletconditions\033[0m only accepts \033[1;34mInteger\033[0m values\n"
          "  \033[1;31m-dirichletconditions "<< argvalue << "\033[0m is not acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
      }   
    }

    if( argvdummy == "-bodyforceconditions"     )
    { 
      argvalue = argv[i+1];
      if (argvalue.find(".") != string::npos){
      cout << 
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"          
          "The flag \033[1;31m-bodyforceconditions\033[0m only accepts \033[1;34mInteger\033[0m values\n"
          "  \033[1;31m-bodyforceconditions "<< argvalue << "\033[0m is not acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
      }   
    }        

    if( argvdummy == "-tractionconditions"      )
    { 
      argvalue = argv[i+1];
      if (argvalue.find(".") != string::npos){
      cout << 
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"          
          "The flag \033[1;31m-tractionconditions\033[0m only accepts \033[1;34mInteger\033[0m values\n"
          "  \033[1;31m-tractionconditions "<< argvalue << "\033[0m is not acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
      }   
    }

    if( argvdummy == "-dimension"               )
    { 
      argvalue = argv[i+1];
      if (argvalue.find(".") != string::npos){
      cout << 
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"          
          "The flag \033[1;31m-dimension\033[0m only accepts \033[1;34mInteger\033[0m values\n"
          "  \033[1;31m-dimension "<< argvalue << "\033[0m is not acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
      }   
    }
    if( argvdummy == "-lagrange"                )
    { 
      argvalue = argv[i+1];
      if (argvalue.find(".") != string::npos){
      cout << 
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"          
          "The flag \033[1;31m-lagrange\033[0m only accepts \033[1;34mInteger\033[0m values\n"
          "  \033[1;31m-lagrange "<< argvalue << "\033[0m is not acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
      }   
    }

  }

  if(errorArgument) 
   exit(1111);

  if ( spc != 2 && spc != 3){
      cout << 
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"          
          "The flag \033[1;31m-dimension\033[0m only accepts \033[1;34m2|3\033[0m\n"
          "  \033[1;31m-dimension "<< spc << "\033[0m is not acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
     }

  if ( lag != 1){
      cout << 
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"          
          "The flag \033[1;31m-lagrange\033[0m only accepts \033[1;34m1\033[0m\n"
          "  \033[1;31m-lagrange "<< lag << "\033[0m is not acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
     }

  if ( dirichletpointconditions <= -1){
      cout << 
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"          
          "The flag \033[1;31m-dirichletpointconditions\033[0m only accepts positive integers \033[1;34m0|1|2|3|4|...\033[0m\n"
          "  \033[1;31m-dirichletpointconditions "<< dirichletpointconditions << "\033[0m is not acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
     }

  if ( dirichletconditions <= -1){
      cout << 
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"          
          "The flag \033[1;31m-dirichletconditions\033[0m only accepts positive integers \033[1;34m0|1|2|3|4|...\033[0m\n"
          "  \033[1;31m-dirichletconditions "<< dirichletconditions << "\033[0m is not acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
     }

  if ( bodyforceconditions <= -1){
      cout << 
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"          
          "The flag \033[1;31m-bodyforceconditions\033[0m only accepts positive integers \033[1;34m0|1|2|3|4|...\033[0m\n"
          "  \033[1;31m-bodyforceconditions "<< bodyforceconditions << "\033[0m is not acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
     }

  if ( tractionconditions <= -1){
      cout << 
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"          
          "The flag \033[1;31m-tractionconditions\033[0m only accepts positive integers \033[1;34m0|1|2|3|4|...\033[0m\n"
          "  \033[1;31m-tractionconditions "<< tractionconditions << "\033[0m is not acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
     }


  if ( Model != "hybrid-phase-field" && Model != "Mazar" && Model != "pseudo-nonlinear" 
     ){
      cout << 
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"          
          "The flag \033[1;31m-model\033[0m only accepts \033[1;34mhybrid-phase-field|Mazar|pseudo-nonlinear\033[0m\n"
          "\033[1;31m-model "<< Model << "\033[0m is not an acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
     }

  if ( Prblm != "linear-elasticity" && Prblm != "damage" && Prblm != "elastodynamics" && Prblm != "soildynamics" 
     ){
      cout << 
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"          
          "The flag \033[1;31m-problem\033[0m only accepts \033[1;34mlinear-elasticity|damage|elastodynamics|soildynamics\033[0m\n"
          "\033[1;31m-problem "<< Prblm << "\033[0m is not an acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
     }

  if ( Partitioner != "metis" && Partitioner != "scotch" && Partitioner != "parmetis"  
     ){
      cout << 
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"          
          "The flag \033[1;31m-partitioner\033[0m only accepts \033[1;34mmetis|scotch|parmetis\033[0m\n"
          "\033[1;31m-partitioner "<< Partitioner << "\033[0m is not an acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
     }

  if (PostProcess!="u"   && PostProcess!="v"   && PostProcess!="a"   && PostProcess!="d"
   && PostProcess!="uv"  && PostProcess!="vu"  && PostProcess!="au"  && PostProcess!="ua"
   && PostProcess!="av"  && PostProcess!="va"  && PostProcess!="ud"  && PostProcess!="du"
   && PostProcess!="uva" && PostProcess!="uav" && PostProcess!="vau" && PostProcess!="vua"
   && PostProcess!="auv" && PostProcess!="avu" && PostProcess!="null"  
     ){
      cout << 
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"          
          "The flag \033[1;31m-postprocess\033[0m only accepts \033[1;34mu|v|a|d|ud|uv|vu|au|ua|av|va|du|uav|vau|vua|auv|avu|uva\033[0m\n"
          "\033[1;31m-postprocess "<< PostProcess << "\033[0m is not an acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
     }

  if ( doublecouple != "force-based" && doublecouple != "displacement-based" && doublecouple != "unused"  
     ){
      cout << 
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"          
          "The flag \033[1;31m-doublecouple\033[0m only accepts \033[1;34mforce-based|displacement-based\033[0m\n"
          "\033[1;31m-doublecouple "<< doublecouple << "\033[0m is not an acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
     }

  if ( NonLinearMethod != "Picard" && NonLinearMethod != "Newton-Raphsons"  
     ){
      cout << 
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"          
          "The flag \033[1;31m-nonlinearmethod\033[0m only accepts \033[1;34mPicard|Newton-Raphsons\033[0m\n"
          "\033[1;31m-nonlinearmethod "<< NonLinearMethod << "\033[0m is not an acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
     }

  if ( reactionforcemethod != "stress-based" && reactionforcemethod != "variational-based"  
     ){
      cout << 
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"          
          "The flag \033[1;31m-reactionforce\033[0m only accepts \033[1;34mstress-based|variational-based\033[0m\n"
          "\033[1;31m-reactionforce "<< reactionforcemethod << "\033[0m is not an acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
     }


  if ( TimeDiscretization != "generalized-alpha" && TimeDiscretization != "newmark-beta"   && TimeDiscretization != "hht-alpha"   && TimeDiscretization != "central-difference"  
     ){
      cout << 
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"          
          "The flag \033[1;31m-timediscretization\033[0m only accepts \033[1;34mgeneralized-alpha|newmark-beta|hht-alpha|central-difference\033[0m\n"
          "\033[1;31m-timediscretization "<< TimeDiscretization << "\033[0m is not an acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
     }

  if(errorArgument) 
   exit(1111);