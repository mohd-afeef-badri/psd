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
* Comment: This support file is  responsible for generating FemParameters.edp which   *
*          contain main solver finite element parameters of PSD.                      *
*                                                                                     *
**************************************************************************************/

writeHeader;

if(Model!="pseudo_nonlinear")
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "// -------Finite element variables -------                                     \n"
 "// -------------------------------------------------------------------         \n"
 "// def(du)    : Displacement FE field                                          \n"
 "// def(uold)  : Previous iteration displacement FE field                       \n"
 "// def(vold)  : Previous iteration velocity FE field                           \n"
 "// def(aold)  : Previous iteration acceleration FE field                       \n"
 "// def(DPspc) : Partition of unity field for integral                          \n"
 "//=============================================================================\n"
 "                                                                               \n"
 "  Vh  def(du)    ,                                                             \n"
 "      def(uold)  ,                                                             \n"
 "      def(vold)  ,                                                             \n"
 "      def(aold)  ,                                                             \n"
 "      def(DPspc) ;                                                             \n"
 "                                                                               \n";

if(Model=="pseudo_nonlinear")
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "// -------Finite element variables -------                                     \n"
 "// -------------------------------------------------------------------         \n"
 "// def(du)    :  Displacement FE field                                         \n"
 "// def(uold)  :  Previous iteration displacement FE field                      \n"
 "// def(uNL)   :  Nonlinear iteration displacement FE field                     \n"
 "// def(vold)  :  Previous iteration velocity FE field                          \n"
 "// def(aold)  :  Previous iteration acceleration FE field                      \n"
 "// def(DPspc) :  Partition of unity field for integral                         \n"
 "//=============================================================================\n"
 "                                                                               \n"
 "  Vh  def(du)    ,                                                             \n"
 "      def(uold)  ,                                                             \n"
 "      def(uNL)   ,                                                             \n"
 "      def(vold)  ,                                                             \n"
 "      def(aold)  ,                                                             \n"
 "      def(DPspc) ;                                                             \n"
 "                                                                               \n";

 if(Sequential)
  writeIt
  "                                                                              \n"
  "//============================================================================\n"
  "// ------- Fem matrices and vectors -------                                   \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  matrix  A;                                                                  \n"
  "  real[int]  b(Vh.ndof);                                                      \n";

 if(!Sequential){

  if(pipegnu)
   writeIt
   "                                                                             \n"
   "//===========================================================================\n"
   "// ------- Partion of unity for integrals -------                            \n"
   "//===========================================================================\n"
   "                                                                             \n"
   "  for(int i=0; i<DP.n; i++)                                                  \n"
   "    DPspc[][i]=DP[i];                                                        \n";


  writeIt
  "                                                                              \n"
  "//============================================================================\n"
  "//  -------  Fem matrices and vectors -------                                 \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  matrix       ALoc    ;                                                      \n"
  "  real[int]    b(Vh.ndof);                                                    \n";

  writeIt
  "                                                                              \n"
  "  startProcedure(\"matrix sparsity assembly\",t0)                             \n"
  "  Mat  A(Vh.ndof, restrictionIntersectionP, DP, symmetric=1)  ;               \n"
  "  endProcedure(\"matrix sparsity assembly\",t0)                               \n"
  "                                                                              \n";
 }
