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

if(!Sequential)
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "// ------- Domian decomposition suppoprt variables -------                     \n"
 "//=============================================================================\n"
 "                                                                               \n"
 " int[int][int] restrictionIntersectionP(0);  // Local-to-neighbors renumbering \n"
 " real[int] DP;                               // Partition of unity             \n";

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

 if(!Sequential)
  writeIt
  "                                                                                \n"
  "  if(mpirank==0)system(\"mkdir -p VTUs\");                                      \n";
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
  "  int[int]    PCi(PbcCord.n); PCi=-1;                                          \n"
  "  int[int]    mpirankPCi(PbcCord.n); mpirankPCi=-1;                            \n";

if(pointprobe && !Sequential)
 writeIt
  "                                                                               \n"
  "//============================================================================ \n"
  "//        ------- parameters for point probe -------                           \n"
  "// --------------------------------------------------------------------------- \n"
  "// iProbe     : point index of the probe in finite element space.              \n"
  "// Prank      : MPI rank that hold point iProbe                                \n"
  "// --------------------------------------------------------------------------- \n"
  "//  values of  iProbe and Prank are set to -1 as this will sereve as error     \n"
  "//  indicator should anything go wrong.                                        \n"
  "//============================================================================ \n"
  "                                                                               \n"
  "  int[int] iProbe(ProbePointCord.n), Prank(ProbePointCord.n);                  \n"
  "  iProbe=-1;    Prank=-1;                                                      \n"
  "                                                                               \n";

if(pointprobe && Sequential)
 writeIt
  "                                                                               \n"
  "//============================================================================ \n"
  "//        ------- parameters for point probe -------                           \n"
  "// --------------------------------------------------------------------------- \n"
  "// iProbe     : point index of the probe in finite element space.              \n"
  "// --------------------------------------------------------------------------- \n"
  "//  values of  iProbe  are set to -1 as this will sereve as error              \n"
  "//  indicator should anything go wrong.                                        \n"
  "//============================================================================ \n"
  "                                                                               \n"
  "  int[int] iProbe(ProbePointCord.n);                                           \n"
  "  iProbe=-1;                                                                   \n"
  "                                                                               \n";
