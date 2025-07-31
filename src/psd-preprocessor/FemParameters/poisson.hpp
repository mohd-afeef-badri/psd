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
* Comment: This support file is  responsible for generating FemParameters.edp which   *
*          contain main solver finite element parameters of PSD.                      *
*                                                                                     *
**************************************************************************************/

codeSnippet R""""(

//============================================================================
// ------- Fem matrices and vectors -------
//============================================================================

)"""";

if(Sequential){

  codeSnippet R""""(
  matrix  A;
  real[int]  b(Vh.ndof);
  real[int]  x(Vh.ndof);
  )"""";
}

if(!Sequential)
if(!adaptmesh)
{
codeSnippet R""""(

  matrix       ALoc;
  real[int]    b(Vh.ndof);

  startProcedure("matrix sparsity assembly",t0);
  Mat  A(Vh.ndof, restrictionIntersectionP, DP, symmetric=1)  ;
  endProcedure("matrix sparsity assembly",t0);

//============================================================================
// ------- Finite element variables -------
// -------------------------------------------------------------------
// u  : trial function
// v  : test function
//============================================================================

  Vh  u , v ;
)"""";
}
else
{
codeSnippet R""""(
  startProcedure("matrix sparsity assembly",t0);
  Mat<PetscScalar> A;
  MatCreate(Th, A, P1);
  Vh<PetscScalar> u;
  endProcedure("matrix sparsity assembly",t0);
)"""";
}
