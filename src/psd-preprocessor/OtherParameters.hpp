/**************************************************************************************
*                                                                                     *
* Author : Mohd Afeef BADRI                                                           *
* Email  : mohd-afeef.badri@cea.fr                                                    *
* Date   : 20/04/2020                                                                 *
* Type   : Support file                                                               *
*                                                                                     *
* Comment: This support file is  responsible for generating OtherParameters.edp which *
*          is responsible for defining some parameters needed in PSD.                 *
*                                                                                     *
**************************************************************************************/

cout << " building OtherParameters.edp";

{ofstream  write("OtherParameters.edp");

writeHeader;

writeIt
"                                                                                \n"
"//==============================================================================\n"
"// ------- Square root of 2 -------                                             \n"
"//==============================================================================\n"
"                                                                                \n"
"  real SQ2 = sqrt(2.0);                                                         \n";


if(timelog)
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "// ------- Time logging parameters -------                                     \n"
 "//=============================================================================\n"
 "                                                                               \n"
 "  real t0,t1;                                                                  \n";

if(!Sequential){
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "// ------- Domian decomposition suppoprt variables -------                     \n"
 "//=============================================================================\n"
 "                                                                               \n"
 " int[int][int] restrictionIntersectionP(0);  // Local-to-neighbors renumbering \n"
 " real[int] DP;                               // Partition of unity             \n";


 if(Prblm=="damage" && Model=="hybrid-phase-field" && !vectorial)
  writeIt
  "                                                                              \n"
  " int[int][int] restrictionIntersectionZ(0);  // Local-to-neighbors renumbering\n"
  " real[int] DZ;                               // Partition of unity            \n";
}

if(Prblm=="damage" && Model=="hybrid-phase-field"){

 if(plotAll)
  writeIt
  "                                                                              \n"
  "//============================================================================\n"
  "// ------- Paraview plotting parameters -------                               \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  int[int] vtuorder=[1,1];                                                    \n"
  "  string   namedata=\"U Phi\";                                                \n"
  "  bool     withsur=true;                                                      \n"
  "                                                                              \n"
  "  int iterout  = 0 ,               // Loop Counter                            \n"
  "      iterout1 = 0 ;               // Loop Counter                            \n";

 if(plotAll && !Sequential)
  writeIt
  "                                                                              \n"
  "  if(mpirank==0)system(\"rm -rf VTUs/Solution_\"+mpisize+\".pvd\");           \n"
  "  if(mpirank==0)system(\"mkdir -p VTUs\");                                    \n";

 if(pipegnu){
  writeIt
  "                                                                              \n"
  "//============================================================================\n"
  "// ------- Gnuplot pipeing parameters ------                                  \n"
  "//============================================================================\n"
  "                                                                              \n"
  <<(Sequential ? "" : "  if(mpirank==0)\n"                                      )<<
  "  system(\"rm force.data\");                                                  \n"
  "                                                                              \n";

  if(!supercomp)
   writeIt
   "  pstream pgnuplot(\"gnuplot -p\");                                          \n"
   <<(Sequential ? "" : "  if(mpirank==0)\n"                                     )<<
   "  pgnuplot                                                                   \n"
   "  <<\" set title  \\\"Traction = \"+tr+\"\\\";                        \\n\"  \n"
   "  <<\" set termoption font \\\"Arial-Bold,20\\\";                \\n\"       \n"
   "  <<\" set xrange [0:.008]; set yrange [0:.9];                \\n\"          \n"
   "  <<\" set xlabel \\\" Displacement \\\";                        \\n\"       \n"
   "  <<\" set ylabel \\\" Force (kN)\\\";                        \\n\"          \n"
   "  <<\" set grid x y;    set key left;                        \\n\";          \n";
 }

}



if(Prblm=="elastodynamics"){
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "// ------- Elasto-dynamic constant parameters -------                          \n"
 "//=============================================================================\n"
 "                                                                               \n"
 "  real[int] c(11);                                                             \n"
 "                                                                               \n";

 if(TimeDiscretization=="generalized-alpha")
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

 if(TimeDiscretization=="newmark-beta")
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

 if(TimeDiscretization=="central-difference")
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

 if(TimeDiscretization=="hht-alpha")
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
  
 if(plotAll || plotTime)
  writeIt
  "                                                                               \n"
  "//=============================================================================\n"
  "//  ------- Paraview plotting parameters -------                               \n"
  "//=============================================================================\n"
  "                                                                               \n"
  "  string   namedata = \"U\"              ;  // Name of export data             \n"
  "  bool     withsur  = true             ;  // With surfaces                     \n"
  "  int      iterout  = 0                ;  // Loop counter                      \n";

 if(PostProcess!="v" && PostProcess!="a" && PostProcess!="uva")
  writeIt
  "  int[int] vtuorder = [1]                ;  // Solution export order           \n";

 if(PostProcess=="v" || PostProcess=="a")
  writeIt
  "  int[int] vtuorder = [1,1]              ;  // Solution export order           \n";

 if(PostProcess=="uva")
  writeIt
  "  int[int] vtuorder = [1,1,1]            ;  // Solution export order           \n";

 if(plotAll && !Sequential)
  writeIt
  "                                                                               \n"
  "  if(mpirank==0)system(\"mkdir -p VTUs\");                                     \n";

 if(plotAll && !Sequential)
  writeIt
  "                                                                               \n"
  "  if(mpirank==0)system(\"rm -rf VTUs/Solution_\"+mpisize+\".pvd\");            \n";

 if(plotTime)
  writeIt
  "  string   namevtu  = \"VTUs/Result\"    ;  // File name                       \n"
  "  exportBegin(                                                                 \n"
  <<(!Sequential ? "              namevtu, mpiCommWorld" : "              namevtu")<<
  " )                                                                             \n"
  "                                                                               \n";

 if(pipegnu){
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
  "  system(\"rm energies.data\");                                                \n";

 if(!supercomp)
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
}

if(Prblm=="soildynamics"){
 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- Variational formulation constant parameters -------                  \n"
 "//==============================================================================\n"
 "                                                                                \n"
 "  real[int] c(10);                                                              \n"
 "                                                                                \n";

 if(TimeDiscretization=="generalized-alpha")
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

 if(TimeDiscretization=="newmark-beta")
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

 if(TimeDiscretization=="central-difference")
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

 if(TimeDiscretization=="hht-alpha")
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

 if(plotAll || plotTime)
  writeIt
  "                                                                                \n"
  "//==============================================================================\n"
  "//  ------- Paraview plotting parameters -------                                \n"
  "//==============================================================================\n"
  "                                                                                \n";

 if(Sequential)
  writeIt
  "  bool     withsur  = true             ;  // With surfaces                      \n"
  "  int      iterout  = 0                ;  // Loop counter                       \n";

 if(PostProcess=="u")
  writeIt
  "  int[int] vtuorder = [1]  ;  // Solution export order                         \n"
  "  macro   namedata()\"U\"       // Name of export data                         \n";

 if(PostProcess=="v")
  writeIt
  "  int[int] vtuorder = [1]  ;  // Solution export order                         \n"
  "  macro   namedata()\"V\"       // Name of export data                         \n";

 if(PostProcess=="a")
  writeIt
  "  int[int] vtuorder = [1]  ;  // Solution export order                         \n"
  "  macro   namedata()\"A\"       // Name of export data                         \n";

 if(PostProcess=="uv" || PostProcess=="vu")
  writeIt
  "  int[int] vtuorder = [1,1]  ;  // Solution export order                        \n"
  "  macro   namedata()\"U V\"       // Name of export data                        \n";

 if(PostProcess=="ua" || PostProcess=="au")
  writeIt
  "  int[int] vtuorder = [1,1]  ;  // Solution export order                        \n"
  "  macro   namedata()\"U A\"       // Name of export data                        \n";

 if(PostProcess=="va" || PostProcess=="av")
  writeIt
  "  int[int] vtuorder = [1,1]  ;  // Solution export order                        \n"
  "  macro   namedata()\"V A\"       // Name of export data                        \n";

 if(PostProcess=="uva" || PostProcess=="uav" || PostProcess=="auv" ||
    PostProcess=="avu" || PostProcess=="vau" || PostProcess=="vua"  )
  writeIt
  "  int[int] vtuorder = [1,1,1]  ;  // Solution export order                      \n"
  "  macro   namedata()\"U V A\"       // Name of export data                      \n";

 if(plotAll && !Sequential)
  writeIt
  "                                                                                \n"
  "  if(mpirank==0)system(\"mkdir -p VTUs\");                                      \n";

 if(plotTime)
  writeIt
  "  string   namevtu  = \"VTUs/Result\"    ;  // File name                        \n"
  "  exportBegin(                                                                  \n"
  <<(!Sequential ? "              namevtu, mpiCommWorld" : "              namevtu" )<<
  " )                                                                              \n"
  "                                                                                \n";

 if(pipegnu){
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
  "  system(\"rm energies.data\");                                                \n";

 if(!supercomp)
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

 if(doublecouple=="force-based" || doublecouple=="displacement-based")
  writeIt
  "                                                                               \n"
  "//=============================================================================\n"
  "//                  ------- double couple  parameters  -------                 \n"
  "// --------------------------------------------------------------------------- \n"
  "// iNorth : is the integer index of the northern degree of freedom             \n"
  "//          as it is assembled in the linear system. This is  used             \n"
  "//          to force boundary coditions of double-couple whcih can             \n"
  "//          be a point load or a force. Same is true for iSouth,..             \n"
  "//  DcFlag : is a Boolean flag to assert if the  processor  holds any          \n"
  "//           double couple points.                                             \n"
  "//  Nrank  : is rank of the MPI process that holds the finite element          \n"
  "//           degree of freedom of the  Northern  double couple point.          \n"
  "//           Same is true for Srank, Erank, Wrank.                             \n"
  "// --------------------------------------------------------------------------- \n"
  "//  values of  iNorth,....,iWest and Nrank,...,Wrank are set to -1 as          \n" 
  "//  this will sereve as error indicator should anything go wrong.              \n"         
  "//=============================================================================\n"
  "                                                                               \n"
  "  int iNorth=-1, iSouth=-1, iEast=-1, iWest=-1;                                \n"
  "  int Nrank=-1, Srank=-1, Erank=-1, Wrank=-1;                                  \n"
  "  bool DcFlag=false;                                                           \n";

 }

if(dirichletpointconditions>=1)
  writeIt
  "                                                                               \n"
  "//=============================================================================\n"
  "//       ------- point boundary condition  parameters  -------                 \n"
  "// --------------------------------------------------------------------------- \n"
  "// PCi        : point index in finite element space.                           \n"
  "// mpirankPCi : MPI rank that hold point PCi                                   \n"
  "// --------------------------------------------------------------------------- \n"
  "//  values of  PCi and mpirankPCi are set to -1 as this will sereve as error   \n" 
  "//  indicator should anything go wrong.                                        \n"         
  "//=============================================================================\n"
  "                                                                               \n"
  "  int[int]    PCi(PC.n); PCi=-1;                                               \n"
  "  int[int]    mpirankPCi(PC.n); mpirankPCi=-1;                                 \n";



if(pipegnu)if(Prblm=="damage" && Model=="Mazar"){
 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- Gnuplot pipeing parameters ------                                    \n"
 "//==============================================================================\n"
 "                                                                                \n"
 <<(Sequential ? "" : "  if(mpirank==0)\n"                                        )<<
 "  system(\"rm output.data\");                                                   \n"
 "                                                                                \n";

 if(!supercomp)
  writeIt
  "  pstream pgnuplot(\"gnuplot -p\");                                            \n"
  <<(Sequential ? "" : "  if(mpirank==0)\n"                                       )<<
  "  pgnuplot                                                                     \n"
  "  <<\" set title  \\\" Force-Displacement-Curve\\\";                \\n\"      \n"
  "  <<\" set termoption font \\\"Arial-Bold,20\\\";                \\n\"         \n"
  "  <<\" set xlabel \\\" Displacement \\\";                        \\n\"         \n"
  "  <<\" set ylabel \\\" Force (N)\\\";                        \\n\"             \n"
  "  <<\" set grid x y;    set key left;                        \\n\";            \n";
}

} //-- [ostream terminator]  parameters.edp closed --//

cout << " .......................... Done \n";
