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

if(AdaptmeshMetricBackend=="freefem")
{
codeSnippet R""""(

//============================================================================
// ------- Freefem Adaption Parameters -------
// -------------------------------------------------------------------
//  adaptErr : the error passed to the freefem adaption frunction
//  adaptErrRate : the value by which the error is divided at each iteration
//=============================================================================

real adaptErr = 0.05;
real adaptErrRate = 1;

)"""";

}

if(AdaptmeshBackend=="parmmg")
{
codeSnippet R""""(
//============================================================================
// ------- Mesh Adaption ParMmg Parameters -------
// -------------------------------------------------------------------
//  parMmgIter : number of iteration in parmmg values (1,2,3)
//  rt         : required triangles that are conserved and not adapted
//  parMmgVerbosityVal : verbosity of parmmg)"""";
if (ParmmgMethod == "partition_regrouping" || ParmmgMethod == "partition_automatic_regrouping")
codeSnippet R""""(
//  Pgroups : number of groups used in ParMmg)"""";
if (ParmmgMethod == "partition_automatic_regrouping")
codeSnippet R""""(
//  elemsPerGroup : number of elements per group used in ParMmg
//  maxP : maximum number of groups used in ParMmg, equal to the number of processes by default
//  nt: counted number of elements per process)"""";
codeSnippet R""""(
//=============================================================================
    int parMmgIter = 3;
    int[int] rt(0); 
    real parMmgVerbosityVal = verbosity;
)"""";

if (ParmmgMethod == "partition_regrouping")
    codeSnippet R""""(
    macro Pgroups()  2//
    )"""";
if (ParmmgMethod == "partition_automatic_regrouping")
    codeSnippet R""""(
    int elemsPerGroup = 8000;
    int maxP = mpisize;
    int nt = 0;
    macro getNt()
    {
	fespace Ph(Th, P0);
        Ph part;
        PartitionCreate(Th, part[], P0);
        part = abs(part - 1.0) < 1e-1;
        int ntLocal = part[].l1;
        int nt = 0;
        mpiAllReduce(ntLocal, nt, mpiCommWorld, mpiSUM);
    }//
    macro Pgroups() min(maxP, min(mpisize, max(1, nt / elemsPerGroup)))//
    )"""";
}

if(AdaptmeshBackend=="mmg" || AdaptmeshBackend=="parmmg")
{
codeSnippet R""""(
//============================================================================
// ------- Mesh Adaption mmg/parmmg Parameters -------
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
)"""";

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
    bool nomoveVal = false;
    bool noswapVal = false;
    bool noinsertVal = false;
)"""";
}

if(AdaptmeshBackend=="mmg")
{
  codeSnippet R""""(
    real mmgMemory = 20000;
    real mmgVerbosityVal = verbosity;
)"""";
}

if(AdaptmeshMetricBackend=="mshmet"){
codeSnippet R""""(
//============================================================================
// ------- Mesh Adaption metric mshmet parameters -------
// -------------------------------------------------------------------
//  ddoption 0 hmin : minimal edge size (the mshmet default values)
//  ddoption 1 hmax : maximal edge size (the mshmet default values)
//  ddoption 2 eps : tolerence over the error of P1 interpolation (the mshmet default values)
//  ddoption 3 width : relative width for level sets (the mshmet default values)
//  lloption 0 nnu : normalization mode (the optimal values)
//  		- 0 : no normalization, multiplies the hessian values by (1/eps)
//  		- 1 : normalization relative to the scale of the function, multiplies the Hessian values by 1/(eps * umax)
//  		- 2 : normalization following local values of the function, multiplies the Hessian values by 1/(err*u)
//  			with err = 0.01 * umax or err = 0.01 for u = 0, u being the function
//  		- 3 : normalization relative to the function and its gradient, not yet implemented in mshmet
//  lloption 1 iso : isotropic or anisotropic metric calculation (the mshmet default values)
//  lloption 2 ls : level set mode (the mshmet default values)
//  lloption 3 ddebug : debugging logs (the mshmet default values)
//  lloption 4 imprim : mshmet verbosity (the value of the verbosity argument)
//  lloption 5 nlis : number of regularization’s iteration of solutions given (the mshmet default values)
//  lloption 6 metric : the initial metric (the mshmet default values)
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
    lloptions(0) = 2;               // nnu 0
    lloptions(1) = 0;               // iso 1)"""";
}
codeSnippet R""""(
    lloptions(2) = 0;               // ls 0
    lloptions(3) = 1;               // ddebug 1
    lloptions(4) = verbosity;       // imprim verbosity
    lloptions(5) = 0;               // nlis 0
    lloptions(6) = 0;               // metric 0

//=======================================================================
// Todo list:
// 2. handle Drichlet
// 3. check qforder
//=======================================================================
)"""";
}

}

