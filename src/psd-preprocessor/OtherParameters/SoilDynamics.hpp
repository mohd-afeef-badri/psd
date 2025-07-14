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
* Comment: This support file is  responsible for generating OtherParameters.edp which *
*          is responsible for defining some parameters needed in PSD.                 *
*                                                                                     *
**************************************************************************************/

writeHeader;

 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- Variational formulation constant parameters -------                  \n"
 "//==============================================================================\n"
 "                                                                                \n"
 "  real[int] c(10);                                                              \n"
 "                                                                                \n";

 if(TimeDiscretization=="generalized_alpha")
  writeIt
  "  c[0] =   rho*(1.-alpm)/(beta*dt*dt)                                          ;\n"
  "  c[1] =   lambda*(1.-alpf)                                                    ;\n"
  "  c[2] =   2.*mu*(1.-alpf)                                                     ;\n"
  "  c[3] =   rho*(1.-alpm)/(beta*dt)                                             ;\n"
  "  c[4] =   rho*((1.-alpm)/2./beta -1.)                                         ;\n"
  "  c[5] =   lambda*alpf                                                         ;\n"
  "  c[6] =   2*mu*alpf                                                           ;\n"
  "  c[7] =   rho*(1.-alpf)*gamma/beta/dt                                         ;\n"
  "  c[8] =   rho*(1.-gamma*(1-alpf)/beta)                                        ;\n"
  "  c[9] =   rho*(1.-alpf)*dt*(1.-gamma/(2.*beta))                               ;\n"
  "                                                                                \n";

 if(TimeDiscretization=="newmark_beta")
  writeIt
  "  c[0] =   rho/(beta*dt*dt)                                                    ;\n"
  "  c[1] =   lambda                                                              ;\n"
  "  c[2] =   2.*mu                                                               ;\n"
  "  c[3] =   rho/(beta*dt)                                                       ;\n"
  "  c[4] =   rho*(1./2./beta -1.)                                                ;\n"
  "  c[5] =   0.                                                                  ;\n"
  "  c[6] =   0.                                                                  ;\n"
  "  c[7] =   rho*gamma/beta/dt                                                   ;\n"
  "  c[8] =   rho*(1.-gamma/beta)                                                 ;\n"
  "  c[9] =   rho*dt*(1.-gamma/(2.*beta))                                         ;\n"
  "                                                                                \n";

 if(TimeDiscretization=="central_difference")
  writeIt
  "  c[0] =   rho/(dt*dt)                                                         ;\n"
  "  c[1] =   lambda                                                              ;\n"
  "  c[2] =   2.*mu                                                               ;\n"
  "  c[3] =   rho/(dt)                                                            ;\n"
  "  c[4] =   rho*(1./2. -1.)                                                     ;\n"
  "  c[5] =   0.                                                                  ;\n"
  "  c[6] =   0.                                                                  ;\n"
  "  c[7] =   rho*gamma/dt                                                        ;\n"
  "  c[8] =   rho*(1.-gamma)                                                      ;\n"
  "  c[9] =   rho*dt*(1.-gamma/2.)                                                ;\n"
  "                                                                                \n";

 if(TimeDiscretization=="hht_alpha")
  writeIt
  "  c[0] =   rho/(beta*dt*dt)                                                    ;\n"
  "  c[1] =   lambda*(1.-alpf)                                                    ;\n"
  "  c[2] =   2.*mu*(1.-alpf)                                                     ;\n"
  "  c[3] =   rho/(beta*dt)                                                       ;\n"
  "  c[4] =   rho*(1./2./beta -1.)                                                ;\n"
  "  c[5] =   lambda*alpf                                                         ;\n"
  "  c[6] =   2*mu*alpf                                                           ;\n"
  "  c[7] =   rho*(1.-alpf)*gamma/beta/dt                                         ;\n"
  "  c[8] =   rho*(1.-gamma*(1-alpf)/beta)                                        ;\n"
  "  c[9] =   rho*(1.-alpf)*dt*(1.-gamma/(2.*beta))                               ;\n"
  "                                                                                \n";

 if(ParaViewPostProcess){
  writeIt
  "                                                                                \n"
  "//==============================================================================\n"
  "//  ------- Paraview plotting parameters -------                                \n"
  "//==============================================================================\n"
  "                                                                                \n";
 if(Sequential)
  writeIt
  "  int      iterout  = 0                ;  // Loop counter                       \n";

 if(PostProcess=="u" || PostProcess=="v" || PostProcess=="a")
  writeIt
  "  int[int] vtuorder = [1]                ;  // Solution export order           \n";

 if(   PostProcess=="uv" || PostProcess=="vu" || PostProcess=="au" || PostProcess=="ua"
    || PostProcess=="av" || PostProcess=="va" )
  writeIt
  "  int[int] vtuorder = [1,1]              ;  // Solution export order           \n";

if(   PostProcess=="uva" || PostProcess=="uav" || PostProcess=="vau"
   || PostProcess=="vua" || PostProcess=="auv" || PostProcess=="ava" )
  writeIt
  "  int[int] vtuorder = [1,1,1]            ;  // Solution export order           \n";
  }

 if(getenergies){
  writeIt
  "                                                                               \n"
  "//=============================================================================\n"
  "// ------- Gnuplot pipeing parameters  -------                                 \n"
  "//=============================================================================\n"
  "                                                                               \n"
  <<(Sequential ? "  real Ek,El,Ec;" : "  real[int] E(3),EG(3);"                  )<<
  "  // To store damping energy                                                   \n"
  "                                                                               \n"
  <<(Sequential ? "" : "  if(mpirank==0)\n"                                       )<<
  "  system(\"rm -rf energies.data\");                                            \n";

 if(plotreaction)
  writeIt
  "                                                                               \n"
  "  pstream pgnuplot(\"gnuplot -p\");                                            \n"
  <<(Sequential ? "" : "  if(mpirank==0)\n"                                       )<<
  "  pgnuplot                                                                     \n"
  "  <<\" set title\\\"E-Energy\t E-Elastic\tT-Total\tK-Kinetic\\\";        \\n\" \n"
  "  <<\" set termoption font \\\"Arial-Bold,20\\\";                \t\t\\n\"     \n"
  "  <<\" set format x \\\"%.1t\\\";                                    \t\t\\n\" \n"
  "  <<\" set xlabel \\\" Time     \\\";                            \t\t\\n\"     \n"
  "  <<\" set ylabel \\\" Energies \\\";                            \t\t\\n\"     \n"
  "  <<\" set grid x y; set key left;                                       \\n\";\n"
  "                                                                               \n";
 }

 if(doublecouple=="force_based" || doublecouple=="displacement_based")
  writeIt
  "                                                                               \n"
  "//=============================================================================\n"
  "//                  ------- double couple  parameters  -------                 \n"
  "// --------------------------------------------------------------------------- \n"
  "// iNorth : is the integer index of the northern degree of freedom             \n"
  "//          as it is assembled in the linear system. This is  used             \n"
  "//          to force boundary coditions of double-couple whcih can             \n"
  "//          be a point load or a force. Same is true for iSouth,..             \n"
  "//  Nrank  : is rank of the MPI process that holds the finite element          \n"
  "//           degree of freedom of the  Northern  double couple point.          \n"
  "//           Same is true for Srank, Erank, Wrank.                             \n"
  "// --------------------------------------------------------------------------- \n"
  "//  values of  iNorth,....,iWest and Nrank,...,Wrank are set to -1 as          \n"
  "//  this will sereve as error indicator should anything go wrong.              \n"
  "//=============================================================================\n"
  "                                                                               \n"
  "  int iNorth=-1, iSouth=-1, iEast=-1, iWest=-1;                                \n"
  "  int Nrank=-1, Srank=-1, Erank=-1, Wrank=-1;                                  \n";
