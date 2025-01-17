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
//  ThName : Name of the .msh file in Meshses  folder
//=============================================================================
)"""";

if(spc==3)
  writeIt
  "  string ThName = \"../Meshes/3D/cube.msh\"; \n";
if(spc==2)
  writeIt
  "  string ThName = \"../Meshes/2D/bar.msh\"; \n";

codeSnippet R""""(
//============================================================================
//                   ------- Material parameters ------
// -------------------------------------------------------------------
//  lambda : material parameter (conductivity, difusivity, ...)
//  f      : source term
//  un     : neumann term
//  ud     : dirichlet term
//============================================================================

  real pi100 = 100. * pi;
  real pi50 = 50. * pi;
  real pi2 = 2. * pi;

  macro left tanh(-100 * (y - 0.5 - 0.25*sin(2*pi*x)))//
  macro right  tanh(100 * (y - x))//

  macro dLx() (pi50 * cos(pi2 * x) * (1 - left^2))//
  macro dLxx() (pi100 * (pi * sin(pi2 * x) * (left^2 - 1) - cos(pi2 * x) * dLx * left))//
  macro dLy() (100 * (left^2 -1))//
  macro dLyy() (200 * dLy * left)//

  macro dRx() (100 * (right^2 - 1))//
  macro dRxx() (200 * dRx * right)//
  macro dRy() (100 * (1 - right^2))//
  macro dRyy() (-200 * dRy * right)//


  macro    lambda() 1                            //
  macro    f()      (dLxx + dLyy + dRxx + dRyy)  //
  macro    un()     0.                           //
  macro    ud()     (left + right)               //
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
    real mmgMemory = 20000;

    bool nomoveVal = false;
    bool noswapVal = false;
    bool noinsertVal = false;

//============================================================================
// ------- Mesh Adaption metric mshmet parameters -------
// -------------------------------------------------------------------
//=============================================================================

    real[int] ddoptions(4);
    int[int] lloptions(7);

    ddoptions(0) = 0.01; // hmin 0.01
    ddoptions(1) = 1.0;  // hmax 1.0
    ddoptions(2) = 0.01; // eps 0.01
    ddoptions(3) = 0.05; // width 0.05

    lloptions(0) = 2;               // nnu 0
    lloptions(1) = 1;               // iso 1
    lloptions(2) = 0;               // ls 0
    lloptions(3) = 1;               // ddebug 1
    lloptions(4) = 0;               // imprim verbosity
    lloptions(5) = 0;               // nlis 0
    lloptions(6) = 0;               // metric 0

//=======================================================================
// Todo list:
// 1. Rania adds doc for mshmt options
// 2. handle Drichlet
//=======================================================================

)"""";
}
}

