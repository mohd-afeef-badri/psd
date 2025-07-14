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
 "                                                                               \n"
 "//=============================================================================\n"
 "// ------- Elasto-dynamic constant parameters -------                          \n"
 "//=============================================================================\n"
 "                                                                               \n"
 "  real[int] c(11);                                                             \n"
 "                                                                               \n";

 if(TimeDiscretization=="generalized_alpha")
  writeIt
  "  c[0] =   rho*(1.-alpm)/(beta*dt*dt) + etam*rho*gamma*(1-alpf)/beta/dt       ;\n"
  "  c[1] =   lambda*(1.-alpf) + lambda*etak*gamma*(1-alpf)/beta/dt              ;\n"
  "  c[2] =   2.*mu*(1.-alpf) + 2.*mu*etak*gamma*(1-alpf)/beta/dt                ;\n"
  "  c[3] =   rho*(1.-alpm)/beta/dt - etam*rho*(1-gamma*(1-alpf)/beta)           ;\n"
  "  c[4] =   rho*( (1.-alpm)*(1.-2.*beta)/2./beta - alpm - etam*dt*(1.-alpf)*(1.-gamma/2/beta))   ;\n"
  "  c[5] =   lambda*alpf -    lambda*etak*gamma*(1.-alpf)/beta/dt               ;\n"
  "  c[6] =   2*mu*alpf   -    2.*mu*etak*gamma*(1.-alpf)/beta/dt                ;\n"
  "  c[7] =   etak*lambda*(gamma*(1.-alpf)/beta - 1)                             ;\n"
  "  c[8] =   etak*lambda*dt*(1.-alpf)*((1.-2*beta)/2./beta - (1.-gamma))        ;\n"
  "  c[9] =   etak*2*mu*(gamma*(1.-alpf)/beta -1)                                ;\n"
  "  c[10]=   etak*2*mu*dt*(1.-alpf)*((1.-2*beta)/2./beta -(1.-gamma))           ;\n"
  "                                                                               \n";

 if(TimeDiscretization=="newmark_beta")
  writeIt
  "  c[0] =   rho/(beta*dt*dt) + etam*rho*gamma/beta/dt                          ;\n"
  "  c[1] =   lambda + lambda*etak*gamma/beta/dt                                 ;\n"
  "  c[2] =   2.*mu + 2.*mu*etak*gamma/beta/dt                                   ;\n"
  "  c[3] =   rho/beta/dt - etam*rho*(1-gamma/beta)                              ;\n"
  "  c[4] =   rho*( (1.-2.*beta)/2./beta  - etam*dt*(1.-gamma/2/beta))           ;\n"
  "  c[5] =  -lambda*etak*gamma/beta/dt                                          ;\n"
  "  c[6] =  -2.*mu*etak*gamma/beta/dt                                           ;\n"
  "  c[7] =   etak*lambda*(gamma/beta - 1)                                       ;\n"
  "  c[8] =   etak*lambda*dt*((1.-2*beta)/2./beta - (1.-gamma))                  ;\n"
  "  c[9] =   etak*2*mu*(gamma/beta -1)                                          ;\n"
  "  c[10]=   etak*2*mu*dt*((1.-2*beta)/2./beta -(1.-gamma))                     ;\n"
  "                                                                               \n";

 if(TimeDiscretization=="central_difference")
  writeIt
  "  c[0] =   rho/(dt*dt) + etam*rho*gamma/dt                                    ;\n"
  "  c[1] =   lambda + lambda*etak*gamma/dt                                      ;\n"
  "  c[2] =   2.*mu + 2.*mu*etak*gamma/dt                                        ;\n"
  "  c[3] =   rho/dt - etam*rho*(1.-gamma)                                       ;\n"
  "  c[4] =   rho*( 1./2.  - etam*dt*(1.-gamma/2))                               ;\n"
  "  c[5] =  -lambda*etak*gamma/dt                                               ;\n"
  "  c[6] =  -2.*mu*etak*gamma/dt                                                ;\n"
  "  c[7] =   etak*lambda*(gamma - 1)                                            ;\n"
  "  c[8] =   etak*lambda*dt*(1./2. - (1.-gamma))                                ;\n"
  "  c[9] =   etak*2*mu*(gamma -1)                                               ;\n"
  "  c[10]=   etak*2*mu*dt*(1./2. -(1.-gamma))                                   ;\n"
  "                                                                               \n";

 if(TimeDiscretization=="hht_alpha")
  writeIt
  "  c[0] =   rho/(beta*dt*dt) + etam*rho*gamma*(1-alpf)/beta/dt                 ;\n"
  "  c[1] =   lambda*(1.-alpf) + lambda*etak*gamma*(1-alpf)/beta/dt              ;\n"
  "  c[2] =   2.*mu*(1.-alpf) + 2.*mu*etak*gamma*(1-alpf)/beta/dt                ;\n"
  "  c[3] =   rho/beta/dt - etam*rho*(1-gamma*(1-alpf)/beta)                     ;\n"
  "  c[4] =   rho*( (1.-2.*beta)/2./beta  - etam*dt*(1.-alpf)*(1.-gamma/2/beta)) ;\n"
  "  c[5] =   lambda*alpf -    lambda*etak*gamma*(1.-alpf)/beta/dt               ;\n"
  "  c[6] =   2*mu*alpf   -    2.*mu*etak*gamma*(1.-alpf)/beta/dt                ;\n"
  "  c[7] =   etak*lambda*(gamma*(1.-alpf)/beta - 1)                             ;\n"
  "  c[8] =   etak*lambda*dt*(1.-alpf)*((1.-2*beta)/2./beta - (1.-gamma))        ;\n"
  "  c[9] =   etak*2*mu*(gamma*(1.-alpf)/beta -1)                                ;\n"
  "  c[10]=   etak*2*mu*dt*(1.-alpf)*((1.-2*beta)/2./beta -(1.-gamma))           ;\n"
  "                                                                               \n";

  if(tractionconditions>=1)
  writeIt
  "                                                                               \n"
  "//=============================================================================\n"
  "//  ------- Intermediate time holding variable for applying traction ------    \n"
  "//=============================================================================\n"
  "                                                                               \n"
  "  real tt ;                                                                    \n"
  "                                                                               \n";

 if(ParaViewPostProcess){
  writeIt
  "                                                                               \n"
  "//=============================================================================\n"
  "//  ------- Paraview plotting parameters -------                               \n"
  "//=============================================================================\n"
  "                                                                               \n"
  "  int      iterout  = 0                ;  // Loop counter                      \n";

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
