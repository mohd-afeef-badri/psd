/**************************************************************************************
*                                                                                     *
* Author : Mohd Afeef BADRI, Rania SAADI                                              *
* Email  : mohd-afeef.badri@cea.fr, rania.saadi@cea.fr                                *
* Date   : 15/10/2024                                                                 *
* Type   : Support file                                                               *
*                                                                                     *
* Comment: This support  file is  responsible for generating  ControlParameters.edp   *
*          which contain main solver control parameters of PSD.                       *
*                                                                                     *
**************************************************************************************/
writeHeader;

codeSnippet R""""(

//============================================================================
// ------- Mesh parameters (Un-partitioned) -------
// -------------------------------------------------------------------
//  ThName : Name of the .msh file in Meshses/2D or  Meshses/3D folder
//=============================================================================

  string ThName = "../Meshes/2D/bar.msh";

//============================================================================
//                   ------- Material parameters ------
// -------------------------------------------------------------------
//  lambda : material parameter (conductivity, difusivity, ...)
//  f      : source term
//  un     : neumann term
//  ud     : dirichlet term
//============================================================================

  macro    lambda() 1.5 // 
  macro    f()      1.  //
  macro    un()     0.  //
  macro    ud()     5.  // 
)"""";

if(adaptmesh){

codeSnippet R""""(

//============================================================================
// ------- Mesh Adaption Parameters -------
// -------------------------------------------------------------------
//  adaptIter : number of iteration for mesh adaption
//  adaptIso : isotropy conditions for mesh adaption
//=============================================================================

)"""";

writeIt
"  int adaptIter = "<< adaptmeshiteration <<"; \n";

writeIt 
"  bool adaptIso = "<< adaptmeshisotropy <<"; \n";

if(AdaptmeshBackend=="mmg")
{
codeSnippet R""""(
//============================================================================
// ------- Mesh Adaption mmg Parameters -------
// -------------------------------------------------------------------
//  hminVal : minimal edge size (not the mmgtools default values)
//  hmaxVal : maximal edge size (not the mmgtools default values)
//  hausdVal : maximal hausdorff distance for the boundaries approximation
//  hgradVal : graduation value
//  nomoveVal : no point relocation
//  noswapVal : no edge flipping
//  noinsertVal : no point insertion or deletion
//=============================================================================

    real hminVal = 0.0001;
    real hmaxVal = 0.5;
    real hausdVal = 0.01;
    real hgradVal = 1.3; 

    bool nomoveVal = false;
    bool noswapVal = false;
    bool noinsertVal = false;

)"""";
}
}

