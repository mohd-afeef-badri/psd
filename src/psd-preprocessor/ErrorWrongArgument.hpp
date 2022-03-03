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

  if ( !fastmethod && Prblm != "linear_elasticity"){
      cout <<
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"
          "The flag \033[1;31m-withmaterialtensor\033[0m only works for \033[1;34m -problem linear_elasticity\033[0m\n"
          "  It has not been implemented for other models yet. You have used  \n"
          "  \033[1;31m-problem "<< Prblm << "\033[0m which is not acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
     }


  if ( Model == "Hujeux" && Prblm != "soildynamics"){
      cout <<
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"
          "The flag \033[1;31m-model Hujeux\033[0m only works for \033[1;34m -problem soildynamics\033[0m\n"
          "  As it is a soil nonlinear law it does not work for  \n"
          "  \033[1;31m-model "<< Model << "\033[0m, please correct \n"
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

  if ( Validation != "Iwan" && Validation != "NULL" ){
      cout <<
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"
          "The flag \033[1;31m-validation\033[0m only accepts \033[1;34miwan\033[0m\n"
          "\033[1;31m-validation "<< Validation << "\033[0m is not an acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
     }


  if ( Model != "hybrid_phase_field" && Model != "Mazar" && Model != "pseudo_nonlinear"  &&  Model != "Hujeux" &&  Model != "von_mises"
     ){
      cout <<
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"
          "The flag \033[1;31m-model\033[0m only accepts \033[1;34mhybrid_phase_field|Mazar|pseudo_nonlinear|Hujeux|von_mises\033[0m\n"
          "\033[1;31m-model "<< Model << "\033[0m is not an acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
     }

  if ( Model == "pseudo_nonlinear"  &&   Prblm == "damage" ){
      cout <<
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"
          "The flag \033[1;31m-model pseudo_nonlinear\033[0m only works with \033[1;34m-problem linear_elasticity|elastodynamics|soildynamics\033[0m\n"
          "\033[1;31m-problem "<< Prblm << "\033[0m is not an acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
     }

  if ( Prblm != "linear_elasticity" && Prblm != "damage" && Prblm != "elastodynamics" && Prblm != "soildynamics" && Prblm != "elasto_plastic"
     ){
      cout <<
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"
          "The flag \033[1;31m-problem\033[0m only accepts \033[1;34mlinear_elasticity|damage|elastodynamics|soildynamics|elasto_plastic\033[0m\n"
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

  if ( doublecouple != "force_based" && doublecouple != "displacement_based" && doublecouple != "unused"
     ){
      cout <<
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"
          "The flag \033[1;31m-doublecouple\033[0m only accepts \033[1;34mforce_based|displacement_based\033[0m\n"
          "\033[1;31m-doublecouple "<< doublecouple << "\033[0m is not an acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
     }

  if ( NonLinearMethod != "Picard" && NonLinearMethod != "Newton_Raphsons"
     ){
      cout <<
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"
          "The flag \033[1;31m-nonlinearmethod\033[0m only accepts \033[1;34mPicard|Newton_Raphsons\033[0m\n"
          "\033[1;31m-nonlinearmethod "<< NonLinearMethod << "\033[0m is not an acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
     }

  if ( reactionforcemethod != "stress_based" && reactionforcemethod != "variational_based"
     ){
      cout <<
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"
          "The flag \033[1;31m-reactionforce\033[0m only accepts \033[1;34mstress_based|variational_based\033[0m\n"
          "\033[1;31m-reactionforce "<< reactionforcemethod << "\033[0m is not an acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
     }


  if ( TimeDiscretization != "generalized_alpha" && TimeDiscretization != "newmark_beta"   && TimeDiscretization != "hht_alpha"   && TimeDiscretization != "central_difference"
     ){
      cout <<
          "===================================================================\n"
          " ** ERROR **\n"
          "===================================================================\n"
          "\n"
          "The flag \033[1;31m-timediscretization\033[0m only accepts \033[1;34mgeneralized_alpha|newmark_beta|hht_alpha|central_difference\033[0m\n"
          "\033[1;31m-timediscretization "<< TimeDiscretization << "\033[0m is not an acceptable, please correct \n"
          "\n"
          "===================================================================\n";
      errorArgument = true;
     }

  if(errorArgument)
   exit(1111);
