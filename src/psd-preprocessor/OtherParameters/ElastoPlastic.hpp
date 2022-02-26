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
"// ------- Variables for Newton-Raphsons loop ---                               \n"
"//==============================================================================\n"
"                                                                                \n"
" int niter;                                                                     \n"
" real nRes, nRes0;                                                              \n"
"                                                                                \n";

if(ParaViewPostProcess){
 writeIt
 "                                                                              \n"
 "//============================================================================\n"
 "// ------- Paraview plotting parameters -------                               \n"
 "//============================================================================\n"
 "                                                                              \n";

if(PostProcess=="u")
writeIt
"              int[int] vtuorder=[1];                                           \n";
}
