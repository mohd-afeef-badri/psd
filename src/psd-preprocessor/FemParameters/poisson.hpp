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
// ------- Finite element variables -------
// -------------------------------------------------------------------
// u  : trial function
// v  : test function
//============================================================================

  Vh  u , v ;

//============================================================================
// ------- Fem matrices and vectors -------
//============================================================================

)"""";

if(Sequential)
codeSnippet R""""(

  matrix  A;
  real[int]  b(Vh.ndof);

)"""";

if(!Sequential)
codeSnippet R""""(

  matrix       ALoc;
  real[int]    b(Vh.ndof);

  startProcedure("matrix sparsity assembly",t0);
  Mat  A(Vh.ndof, restrictionIntersectionP, DP, symmetric=1)  ;
  endProcedure("matrix sparsity assembly",t0);

)"""";

