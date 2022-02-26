/**************************************************************************************
*                                                                                     *
* Author : Mohd Afeef BADRI                                                           *
* Email  : mohd-afeef.badri@cea.fr                                                    *
* Date   : 25/02/2022                                                                 *
* Type   : Support file                                                               *
*                                                                                     *
* Comment: This support file is  responsible for generating OtherParameters.edp which *
*          is responsible for defining some parameters needed in PSD.                 *
*                                                                                     *
**************************************************************************************/

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

if(ParaViewPostProcess  && !Sequential)
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "// ------- Paraview folder suppoprt  -------                                   \n"
 "//=============================================================================\n"
 "                                                                               \n"
 "  if(mpirank==0)system(\"mkdir -p VTUs\");                                     \n"
 "  if(mpirank==0)system(\"rm -rf VTUs/Solution_\"+mpisize+\".pvd\");            \n";

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
