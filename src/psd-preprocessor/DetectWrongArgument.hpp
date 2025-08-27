/**************************************************************************************
*                                                                                     *
*           This file is a part of PSD project                                        *
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
* Comment: This support file is  responsible for detecting wrong commandline flag     *
*          provided  by  the  user. Depending on the processed info an error or a     *
*          warning will be displayed on the terminal.                                 *
*                                                                                     *
**************************************************************************************/

    if (argvdummy.find("-") != string::npos )
      if (
           argvdummy != "-dirichletpointconditions" &&
           argvdummy != "-dirichletconditions"      &&
           argvdummy != "-bodyforceconditions"      &&
           argvdummy != "-tractionconditions"       &&
           argvdummy != "-adaptmesh_backend"        &&
           argvdummy != "-adaptmesh_metric_backend" &&
           argvdummy != "-dimension"                &&
           argvdummy != "-lagrange"                 &&
	   argvdummy != "-adaptmesh_type"           &&
	   argvdummy != "-adaptmesh_parmmg_method"  &&
           argvdummy != "-h"                        &&
           argvdummy != "-useRCM"                   &&
           argvdummy != "-useMfront"                &&
           argvdummy != "-help"                     &&
           argvdummy != "-debug"                    &&
           argvdummy != "-useGFP"                   &&
           argvdummy != "-activeplot"               &&
           argvdummy != "-testflags"                &&
           argvdummy != "-adaptmesh"                &&
           argvdummy != "-timelog"                  &&
           argvdummy != "-vectorial"                &&
           argvdummy != "--version"                 &&
           argvdummy != "-version"                  &&
           argvdummy != "-sequential"               &&
           argvdummy != "-dirichletbc"              &&
           argvdummy != "-energydecomp"             &&
           argvdummy != "-pointprobe"               &&
           argvdummy != "-top2vol-meshing"          &&
           argvdummy != "-getreactionforce"         &&
           argvdummy != "-plotreactionforce"        &&
           argvdummy != "-constrainHPF"             &&
           argvdummy != "-getenergies"              &&
           argvdummy != "-adaptmesh_iter"           &&
           argvdummy != "-crackdirichletcondition"  &&
           argvdummy != "-withmaterialtensor"       &&
           argvdummy != "-model"                    &&
           argvdummy != "-solver"                   &&
           argvdummy != "-problem"                  &&
           argvdummy != "-partitioner"              &&
           argvdummy != "-validation"               &&           
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
