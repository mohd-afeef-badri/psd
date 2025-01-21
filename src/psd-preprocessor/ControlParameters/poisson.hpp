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

  func F1 = tanh(-100 * (y - 0.5 - 0.25*sin(2*pi*x)));
  func F2 = tanh(100 * (y - x));

  func dAx = 50 * pi * cos(2 * pi * x) * (1 - F1^2);
  func dAxx = 100 * pi * (pi * sin(2 * pi * x) * (F1^2 - 1) - cos(2 * pi * x) * dAx * F1);
  func dAy = 100 * (F1^2 -1);
  func dAyy = 200 * dAy * F1;

  func dBx = 100 * (F2^2 - 1);
  func dBxx = 200 * dBx * F2;
  func dBy = 100 * (1 - F2^2);
  func dByy = -200 * dBy * F2;

  func f = dAxx + dAyy + dBxx + dByy;
  func um = F1 + F2;


  macro    lambda() 1                            //
  macro    f()      (dAxx + dAyy + dBxx + dByy)  //
  macro    un()     0.                           //
  macro    ud()     (F1 + F2)                    //
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
    real hausdVal = 0.01;)"""";
if(adaptmeshisotropy)
{
codeSnippet R""""(
    real hgradVal = 1.3;)"""";
}
else
{
codeSnippet R""""(
    real hgradVal = 2.3;)"""";
}
codeSnippet R""""(
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
)"""";
if(adaptmeshisotropy)
{
codeSnippet R""""(
    lloptions(0) = 2;               // nnu 0
    lloptions(1) = 1;               // iso 1)"""";
}
else
{
codeSnippet R""""(
    lloptions(0) = 0;               // nnu 0
    lloptions(1) = 0;               // iso 1)"""";
}
codeSnippet R""""(
    lloptions(2) = 0;               // ls 0
    lloptions(3) = 1;               // ddebug 1
    lloptions(4) = 0;               // imprim verbosity
    lloptions(5) = 0;               // nlis 0
    lloptions(6) = 0;               // metric 0

//=======================================================================
// Todo list:
// 1. Rania adds doc for mshmt options
// 2. handle Drichlet
// 3. check qforder
//=======================================================================
)"""";
}
}

