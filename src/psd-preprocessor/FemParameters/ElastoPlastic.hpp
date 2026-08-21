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


writeHeader;

if(!useMfront && spc==2)
codeSnippet R""""(

 //============================================================================
 // ------- Finite element variables -------
 // -------------------------------------------------------------------
 // def(du)  : displacement vector (u = u_old + du), it is [dux,duy] in 2D
 //            and [dux,duy,duz] in 3D
 // def(u)   : displacement vector, it is [ux,uy] in 2D and [ux,uy,uz] in 3D
 // def(Du)  : displacement increment accumulated in the current load step
 //============================================================================

   Vh  def(du)   ,
       def(u)    ,
       def(Du)   ;
)"""";

if(useMfront)
codeSnippet R""""(

 //============================================================================
 // ------- Finite element variables -------
 // -------------------------------------------------------------------
 // def(du)  : displacement vector (u = u_old + du), it is [dux,duy] in 2D
 //            and [dux,duy,duz] in 3D
 // def(u)   : displacement vector, it is [ux,uy] in 2D and [ux,uy,uz] in 3D
 //============================================================================

   Vh  def(du)   ,
       def(u)    ;
)"""";

 if(spc==2){
 writeIt
  "                                                                              \n"
  "//============================================================================\n"
  "// ------- Material Tensor using Quadrature FE space -------                  \n"
  "// -------------------------------------------------------------------        \n"
  "// Mt[int]  : is an array of finite element variable belonging to quadratu    \n"
  "//            re space Qh. This array is used  to define components of the    \n"
  "//            material tensor. 3X3 in 2D and 6X6 in 3D                        \n"
  "//            In 2D the material tensor looks like                            \n"
  "//                                                                            \n"
  "//         [ 2*mu+lambda ,  lambda      , 0  ]    [ Mt11 , Mt12 , Mt13 ]      \n"
  "//   Mt =  [ lambda      ,  2*mu+lambda , 0  ] =  [ Mt12 , Mt22 , Mt23 ]      \n"
  "//         [   0         ,     0        , 2mu]    [ Mt13 , Mt23 , Mt33 ]      \n"
  "//                                                                            \n"
  "// PsdMfrontHandler : is a function in mfront interface that helps            \n"
  "//                    building the material tensor  Mt  given with            \n"
  "//                    material prpts.  from  ControlParameters.edp            \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  Qh           [ Mt11 ,  Mt12 , Mt13 ,                                        \n"
  "                         Mt22 , Mt23 ,                                        \n"
  "                                Mt33 ];                                       \n";

  if(useMfront) writeIt
  "                                                                              \n"
  "  startProcedure(\"Material tensor building via MFront\",t0)                  \n"
  "                                                                              \n"
  "  PsdMfrontHandler( MaterialBehaviour                                      ,  \n"
  "                       mfrontBehaviourHypothesis = MaterialHypothesis      ,  \n"
  "                       mfrontPropertyNames       = PropertyNames           ,  \n"
  "                       mfrontPropertyValues      = PropertyValues          ,  \n"
  "                       mfrontMaterialTensor      = Mt11[]                     \n"
  "                   );                                                         \n"
  "                                                                              \n"
  "  endProcedure(\"Material tensor building via MFront\",t0)                    \n"
  "                                                                              \n"
  "                                                                              \n";
  if(!useMfront) writeIt
  "                                                                              \n"
  "  startProcedure(\"Material tensor building\",t0)                             \n"
  "                                                                              \n"
  "  [ Mt11 ,  Mt12 , Mt13 ,                                                     \n"
  "            Mt22 , Mt23 ,                                                     \n"
  "                   Mt33 ] = [lambda+2.*mu,  lambda      ,    0.    ,          \n"
  "                                            lambda+2.*mu,    0.    ,          \n"
  "                                                             2.*mu ];         \n"
  "                                                                              \n"
  "  endProcedure(\"Material tensor building\",t0)                               \n"
  "                                                                              \n"
  "                                                                              \n";

  if(useMfront)
  writeIt
   "                                                                              \n"
   "//============================================================================\n"
   "// ------- Stress/Strain Tensor using Quadrature FE space -------             \n"
   "// -------------------------------------------------------------------        \n"
   "// Eps  : is array of finite element variable belonging to quadrature         \n"
   "//         space Sh. This array  is  used  to define components of the        \n"
   "//         symmetric Strain tensor. 3X3 in 2D hence 3 components.             \n"
   "// Sig  : is array of finite element variable belonging to quadrature         \n"
   "//         space Sh. This array  is  used  to define components of the        \n"
   "//         symmetric Stress tensor. 3X3 in 2D hence 3 components.             \n"
   "//============================================================================\n"
   "                                                                              \n"
   "   Sh [Eps11,Eps22,Eps12];                                                    \n"
   "   Sh [Sig11,Sig22,Sig12];                                                    \n"
   "                                                                              \n"
   "                                                                              \n"
   "//============================================================================\n"
   "// ------- Internal state variable  vector using Quadrature FE space -------  \n"
   "// -------------------------------------------------------------------        \n"
   "// Isv  : is array of finite element variable belonging to quadrature         \n"
   "//         space Ih. This array  is  used  to define components of the        \n"
   "//         elastic Strain tensor (first four components). And a plastic       \n"
   "//         state componenent the last 5th component.                          \n"
   "//============================================================================\n"
   "                                                                              \n"
   "   Ih [Isv1,Isv2,Isv3,Isv4,Isv5];                                             \n"
   "                                                                              \n";


  if(!useMfront)
  writeIt
   "                                                                              \n"
   "//============================================================================\n"
   "// ------- Stress/Strain Tensor using Quadrature FE space -------             \n"
   "// -------------------------------------------------------------------        \n"
   "// Eps  : is array of finite element variable belonging to quadrature         \n"
   "//         space Sh. This array  is  used  to define components of the        \n"
   "//         symmetric Strain tensor. 3X3 in 2D hence 3 components.             \n"
   "// Sig  : is array of finite element variable belonging to quadrature         \n"
   "//         space Sh. This array  is  used  to define components of the        \n"
   "//         symmetric Stress tensor. 3X3 in 2D hence 3 components.             \n"
   "// SigOld  : is array of finite element variable belonging to quadrature      \n"
   "//         space Sh. This array  is  used  to define components of the        \n"
   "//         symmetric Stress tensor at previous time  step. 3X3  in  2D        \n"
   "//         hence 3 components.                                                \n"
   "// SigTrial  : is array of finite element variable belonging to quadrature    \n"
   "//         space Sh. This array  is  used  to define components of the        \n"
   "//         symmetric Stress tensor at trial state. 3X3 in 2D hence three      \n"
   "//         components.                                                        \n"
   "// Dev  : is array of finite element variable belonging to quadrature         \n"
   "//         space Sh. This array  is  used  to define components of the        \n"
   "//         symmetric deviatoric Stress tensor. 3X3 in 2D hence 3 components.  \n"
   "//============================================================================\n"
   "                                                                              \n"
   "   Sh [Eps11,Eps22,Eps12];                                                    \n"
   "   Sh [Sig11,Sig22,Sig12];                                                    \n"
   "   Sh [SigOld11,SigOld22,SigOld12];                                          \n"
   "   Sh [SigTrial11,SigTrial22,SigTrial12];                                    \n"
   "   Sh [Dev11,Dev22,Dev12];                                                   \n"
   "   Sh [FlowN11,FlowN22,FlowN12];                                             \n"
   "                                                                              \n"
   "   Ph Sig33, SigOld33, SigTrial33, Dev33, FlowN33;                           \n"
   "   Ph pOld, dp, seqTrial, yieldFunction, yieldPositive;                      \n"
   "   Ph plasticSwitch, beta, tangentA, meanTrial;                              \n"
   "                                                                             \n"
   "   [Sig11,Sig22,Sig12] = [0.,0.,0.]; Sig33 = 0.;                             \n"
   "   [SigOld11,SigOld22,SigOld12] = [0.,0.,0.]; SigOld33 = 0.;                 \n"
   "   pOld = 0.; dp = 0.;                                                       \n"
   "                                                                             \n";
  }
  
 if(spc==3){
 writeIt
  "                                                                              \n"
  "                                                                              \n"
  "//============================================================================\n"
  "// ------- Material Tensor using Quadrature FE space -------                  \n"
  "// -------------------------------------------------------------------        \n"
  "// Mt[int]  : is an array of finite element variable belonging to quadratu    \n"
  "//            re space Qh. This array is used  to define components of the    \n"
  "//            material tensor. 3X3 in 2D and 6X6 in 3D                        \n"
  "//            In 3D the material tensor looks like                            \n"
  "//                                                                            \n"
  "//      [ 2*mu+lambda ,  lambda      ,   lambda    ,   0  ,  0 ,  0 ]         \n"
  "// Mt = [ lambda      ,  2*mu+lambda ,   lambda    ,   0  ,  0 ,  0 ]         \n"
  "//      [ lambda      ,  lambda      , 2*mu+lambda ,   0  ,  0 ,  0 ]         \n"
  "//      [    0        ,    0         ,     0       ,   mu ,  0 ,  0 ]         \n"
  "//      [    0        ,    0         ,     0       ,   0  ,  mu,  0 ]         \n"
  "//      [    0        ,    0         ,     0       ,   0  ,  0 ,  mu]         \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  startProcedure(\"Material tensor building\",t0)                             \n"
  "  Qh [ Mt11 , Mt12 ,  Mt13 , Mt14 , Mt15 , Mt16 ,                             \n"
  "              Mt22 ,  Mt23 , Mt24 , Mt25 , Mt26 ,                             \n"
  "                      Mt33 , Mt34 , Mt35 , Mt36 ,                             \n"
  "                             Mt44 , Mt45 , Mt46 ,                             \n"
  "                                    Mt55 , Mt56 ,                             \n"
  "                                           Mt66 ] ;                           \n"
  "                                                                              \n"
  "  endProcedure(\"Material tensor building\",t0)                               \n"
  "                                                                              \n"
  "  startProcedure(\"Material tensor building via MFront\",t0)                  \n"
  "                                                                                  \n"
  "  PsdMfrontHandler( MaterialBehaviour                                   ,         \n"
  "                           mfrontBehaviourHypothesis = MaterialHypothesis      ,  \n"
  "                           mfrontPropertyNames       = PropertyNames           ,  \n"
  "                           mfrontPropertyValues      = PropertyValues          ,  \n"
  "                           mfrontMaterialTensor      = Mt11[]                     \n"
  "                         );                                                       \n"
  "                                                                                  \n"
  "  endProcedure(\"Material tensor building via MFront\",t0)                    \n"
  "                                                                              \n"
  "                                                                              \n";
  }


 if(Sequential)
  writeIt
  "                                                                              \n"
  "//============================================================================\n"
  "// ------- Fem matrices and vectors -------                                   \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  matrix  A;                                                                  \n"
  "  real[int]  b(Vh.ndof);                                                      \n";

 if(!Sequential)
  writeIt
  "                                                                              \n"
  "//============================================================================\n"
  "//  -------  Fem matrices and vectors -------                                 \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  matrix       ALoc    ;                                                      \n"
  "  real[int]    b(Vh.ndof);                                                    \n"
  "                                                                              \n"
  "  startProcedure(\"matrix sparsity assembly\",t0)                             \n"
  "  Mat  A(Vh.ndof, restrictionIntersectionP, DP, symmetric=1)  ;               \n"
  "  endProcedure(\"matrix sparsity assembly\",t0)                               \n"
  "                                                                              \n";
