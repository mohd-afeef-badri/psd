/**************************************************************************************
*                                                                                     *
* Author : Mohd Afeef BADRI                                                           *
* Email  : mohd-afeef.badri@cea.fr                                                    *
* Date   : 03/10/2024                                                                 *
* Type   : Support file                                                               *
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
