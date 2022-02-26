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


if(Model=="hybrid_phase_field"){

if(!Sequential) if(!vectorial || constrainHPF)
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "// ------- Domian decomposition suppoprt variables -------                     \n"
 "//=============================================================================\n"
 "                                                                               \n"
 " int[int][int] restrictionIntersectionZ(0);  // Local-to-neighbors renumbering \n"
 " real[int] DZ;                               // Partition of unity             \n";


if(ParaViewPostProcess){
 writeIt
 "                                                                              \n"
 "//============================================================================\n"
 "// ------- Paraview plotting parameters -------                               \n"
 "//============================================================================\n"
 "                                                                              \n"
 "  int iterout  = 0 ,               // Loop Counter                            \n"
 "      iterout1 = 0 ;               // Loop Counter                            \n";

if(PostProcess=="u" || PostProcess=="d")
 writeIt
 "              int[int] vtuorder=[1];                                           \n";

if(PostProcess=="ud" || PostProcess=="du")
 writeIt
 "              int[int] vtuorder=[1,1];                                         \n";
}

}

if(plotreaction)
  writeIt
  "                                                                             \n"
  "//===========================================================================\n"
  "// ------- Gnuplot pipeing parameters ------                                 \n"
  "//===========================================================================\n"
  "                                                                             \n"
  "  pstream pgnuplot(\"gnuplot -p\");                                          \n"
  <<(Sequential ? "" : "  if(mpirank==0)\n"                                     )<<
  "  pgnuplot                                                                   \n"
  "  <<\" set title  \\\"Traction = \"+tr+\"\\\";                        \\n\"  \n"
  "  <<\" set termoption font \\\"Arial-Bold,20\\\";                \\n\"       \n"
  "  <<\" set xlabel \\\" Displacement \\\";                        \\n\"       \n"
  "  <<\" set ylabel \\\" Force (kN)\\\";                        \\n\"          \n"
  "  <<\" set grid x y;    set key left;                        \\n\";          \n";


if(reactionforce)
 writeIt
 "                                                                              \n"
 <<(Sequential ? "" : "  if(mpirank==0)\n"                                      )<<
 "  system(\"rm -rf  force.data\");                                             \n"
 "                                                                              \n";
