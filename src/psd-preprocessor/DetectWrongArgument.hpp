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

    if (argvdummy.find("-") != string::npos)
      if ( 
           argvdummy != "-dirichletpointconditions" &&
           argvdummy != "-dirichletconditions"      &&
           argvdummy != "-bodyforceconditions"      &&        
           argvdummy != "-tractionconditions"       &&
           argvdummy != "-dimension"                &&
           argvdummy != "-lagrange"                 &&

           argvdummy != "-useRCM"                   &&
           argvdummy != "-help"                     &&
           argvdummy != "-debug"                    &&
           argvdummy != "-useGFP"                   &&
           argvdummy != "-pipegnu"                  &&
           argvdummy != "-testflags"                &&
           argvdummy != "-timelog"                  &&
           argvdummy != "-vectorial"                &&
           argvdummy != "--version"                 &&        
           argvdummy != "-version"                  &&    
           argvdummy != "-supercomp"                &&
           argvdummy != "-sequential"               &&
           argvdummy != "-dirichletbc"              &&
           argvdummy != "-energydecomp"             &&
           argvdummy != "-pointprobe"               &&    
           argvdummy != "-top2vol-meshing"          &&
           argvdummy != "-getreactionforce"         &&
           argvdummy != "-plotreactionforce"        &&
           argvdummy != "-constrainHPF"             &&
           argvdummy != "-crackdirichletcondition"  &&
           argvdummy != "-withmaterialtensor"       && 

           argvdummy != "-model"                    &&
           argvdummy != "-solver"                   &&
           argvdummy != "-problem"                  &&
           argvdummy != "-partitioner"              &&
           argvdummy != "-postprocess"              &&
           argvdummy != "-doublecouple"             &&
           argvdummy != "-preconditioner"           &&
           argvdummy != "-nonlinearmethod"          &&
           argvdummy != "-reactionforce"            &&       
           argvdummy != "-subpreconditioner"        &&
           argvdummy != "-timediscretization"                      
         ){
         wrongArgument = true;
         wrongArgumentWarning +=
          "===================================================================\n"
          " ** WARNING **\n"
          "===================================================================\n"
          "\n"
          " The commmandline argument\n"
          "    \033[1;31m"+ argvdummy + "\033[0m\n"
          " not recognized, it is suggested to take appropriate action\n"
          " to eliminate this warning before running the simulation\n"
          "\n"
          "===================================================================\n";
        }