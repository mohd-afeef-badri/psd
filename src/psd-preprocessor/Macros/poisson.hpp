/**************************************************************************************
*                                                                                     *
* Author : Mohd Afeef BADRI                                                           *
* Email  : mohd-afeef.badri@cea.fr                                                    *
* Date   : 03/10/2024                                                                 *
* Type   : Support file                                                               *
*                                                                                     *
* Comment: This support  file is responsible for generating Macro.edp  which contains *
*           main macros compiletime/runtime for PSD solver.                           *
*                                                                                     *
**************************************************************************************/
writeHeader;

if(!Sequential && spc==2){

codeSnippet R""""(
//=============================================================================
//      ------- Essential Macros -------
// ---------------------------------------------------------------------------
// partitioner : mesh partitioner to be used use metis, parmetis, or scotch
// dimension   : dimension of the problem 2 or 3 for 2D or 3D
//=============================================================================

  macro partitioner parmetis     //
  macro dimension   2            //
  macro Pk          P1           //
  macro def(i)      [i]          //
  macro init(i)     [i]          //

)"""";
}


if(!Sequential && spc==3){

codeSnippet R""""(
//=============================================================================
//      ------- Essential Macros -------
// ---------------------------------------------------------------------------
// partitioner : mesh partitioner to be used use metis, parmetis, or scotch
// dimension   : dimension of the problem 2 or 3 for 2D or 3D
//=============================================================================

  macro partitioner parmetis     //
  macro dimension   3            //
  macro Pk          P1           //  
  macro def(i)      [i]          //
  macro init(i)     [i]          //

)"""";
}
