/**************************************************************************************
*                                                                                     *
* Author : Mohd Afeef BADRI                                                           *
* Email  : mohd-afeef.badri@cea.fr                                                    *
* Date   : 20/04/2020                                                                 *
* Type   : Support file                                                               *
*                                                                                     *
* Comment: This support file is  responsible for generating FemParameters.edp which   *
*          contain main solver finite element parameters of PSD.                      *
*                                                                                     *
**************************************************************************************/

cout << " building FemParameters.edp";

{ofstream  write("FemParameters.edp");

writeHeader;

if(Prblm=="linear-elasticity")
 writeIt
 "                                                                              \n"
 "//============================================================================\n"
 "// ------- Finite element variables -------                                   \n"
 "// -------------------------------------------------------------------        \n"
 "// def(u)  : displacement vector, it is [ux,uy] in 2D and [ux,uy,uz] in 3D    \n"
 "//============================================================================\n"
 "                                                                              \n"
 "  Vh  def(u)    ;                                                             \n";

if(Prblm=="damage" && Model=="hybrid-phase-field"){

 if(!vectorial){

  writeIt
  "                                                                              \n"
  "//============================================================================\n"
  "// -------Finite element variables -------                                    \n"
  "// -------------------------------------------------------------------        \n";
  if(NonLinearMethod=="Picard")writeIt
  "// def2(u) :   displacement vector, it is [ux,uy] in 2D and [ux,uy,uz] in 3D  \n"
  "// def2(uold)  :   previous iteration displacement vector                     \n" 
  "// def2(DPspc) :   Partition of unity for domain decomp. (displacement space) \n"
  "// phi    :   phase field variable for damage                                 \n"
  "// phiold :   previous iteration phase field variable                         \n"
  "// DZspc  :   Partition of unity for domain decomp. (damage space)            \n";
  if(reactionforce && reactionforcemethod=="variational-based")writeIt
  "// def2(F) : force vector, it is [Fx,Fy] in 2D and [Fx,Fy,Fz] in 3D           \n";
  if(NonLinearMethod=="Newton-Raphson")writeIt
  "// def2(du) :   displacement vector, it is [ux,uy] in 2D and [ux,uy,uz] in 3D \n"
  "// def2(u)  :   previous iteration displacement vector                        \n" 
  "// def2(DPspc) :   Partition of unity for domain decomp. (displacement space) \n"
  "// dphi    :   phase field variable for damage                                \n"
  "// phi     :   previous iteration phase field variable                        \n"
  "// DZspc   :   Partition of unity for domain decomp. (damage space)           \n";
  if(constrainHPF)writeIt
  "// phip    :   previous iteration phase field variable                        \n";
  if(energydecomp)writeIt
  "// PsiPlusP1    :   tensile energy P1 field                                   \n"
  "// PsiMinusP1   :   compressive energy P1 field                               \n"
  "// PsiPlus      :   tensile energy P0 field                                   \n"
  "// PsiMinus     :   compressive energy P0 field                               \n"  
  "// HistMinus    :   history function based on  compressive energy P0 field    \n"     
  "// HistPlus     :   history function based on  tensile energy  P0 field       \n";   
  writeIt    
  "//============================================================================\n"
  "                                                                              \n";

  if(NonLinearMethod=="Picard")
   writeIt
   "                                                                             \n"   
   "  Vh  def2(u)    ,                                                           \n"
   "      def2(uold) ,                                                           \n"
   "      def2(DPspc);                                                           \n"
   "                                                                             \n"
   "                                                                             \n"
   "  Vh1 phi       ,                                                            \n"
   "      phiold    ,                                                            \n"
   "      DZspc     ;                                                            \n";

  if(reactionforce && reactionforcemethod=="variational-based")
   writeIt
   "                                                                             \n" 
   "  Vh  def2(F)    ;                                                           \n";

  if(NonLinearMethod=="Newton-Raphson")
   writeIt
   "                                                                             \n"   
   "  Vh  def2(du)   ,                                                           \n"
   "      def2(u)    ,                                                           \n"
   "      def2(DPspc);                                                           \n"
   "                                                                             \n"
   "                                                                             \n"
   "  Vh1 dphi      ,                                                            \n"
   "      phi       ,                                                            \n"
   "      DZspc     ;                                                            \n";

   if(constrainHPF)
   writeIt
   "                                                                             \n"   
   "  Vh1  phip      ;                                                           \n";
   
  if(energydecomp)
   writeIt
   "                                                                             \n"
   "  Vh1 PsiPlusP1   ,                                                          \n"
   "      PsiMinusP1  ;                                                          \n"
   "                                                                             \n"
   "                                                                             \n"
   "  Wh0 HistPlus  ,                                                            \n"
   "      HistMinus ,                                                            \n"
   "      PsiPlus   ,                                                            \n"
   "      PsiMinus  ;                                                            \n";
 }

 if(vectorial && !constrainHPF){
  writeIt
  "                                                                              \n"
  "//============================================================================\n"
  "// ------- Finite element variables -------                                   \n"
  "// -------------------------------------------------------------------        \n"
  "// def(u)     :   vectorial displacement-damage vector, it is [ux,uy,phi] in  \n" 
  "//                2D and [ux,uy,uz,phi] in 3D                                 \n"
  "// def(uold)  :   previous iteration vectorial displacement-damage vector     \n" 
  "// def(DPspc) :   Partition of unity for domain decomp. (displacement-damage) \n";
  if(reactionforce && reactionforcemethod=="variational-based")writeIt 
  "// def(F)  : force vector, it is [Fx,Fy] in 2D and [Fx,Fy,Fz] in 3D           \n";
  if(ParaViewPostProcess)writeIt
  "// phi     : Scalar P1 visulization field phi                                 \n";
  if(energydecomp)writeIt
  "// PsiPlusP1    :   tensile energy P1 field                                   \n"
  "// PsiMinusP1   :   compressive energy P1 field                               \n"
  "// PsiPlus      :   tensile energy P0 field                                   \n"
  "// PsiMinus     :   compressive energy P0 field                               \n"  
  "// HistMinus    :   history function based on  compressive energy P0 field    \n"     
  "// HistPlus     :   history function based on  tensile energy  P0 field       \n";          
  writeIt 
  "//============================================================================\n"
  "                                                                              \n"
  "  Vh  def(u)    ,                                                             \n"
  "      def(uold) ,                                                             \n"
  "      def(DPspc);                                                             \n";

  if(reactionforce && reactionforcemethod=="variational-based")
   writeIt
   "                                                                            \n"   
   "  Vh  def(F)    ;                                                           \n";  
  
  if(ParaViewPostProcess)
   writeIt
   "                                                                             \n"
   "  Vh1  phi      ;                                                            \n";   

  if(energydecomp)
   writeIt
   "                                                                             \n"
   "  Vh1 PsiPlusP1   ,                                                          \n"
   "      PsiMinusP1  ;                                                          \n"
   "                                                                             \n"
   "                                                                             \n"
   "  Wh0 HistPlus  ,                                                            \n"
   "      HistMinus ,                                                            \n"
   "      PsiPlus   ,                                                            \n"
   "      PsiMinus  ;                                                            \n";
 }
 
 if(vectorial && constrainHPF){
  writeIt
  "                                                                              \n"
  "//============================================================================\n"
  "// ------- Finite element variables -------                                   \n"
  "// -------------------------------------------------------------------        \n"  
  "// def2(u)    :   vectorial displacement-damage vector, it is [ux,uy,phi] in  \n" 
  "//                2D and [ux,uy,uz,phi] in 3D                                 \n"
  "// def2(uold) :   previous iteration vectorial displacement-damage vector     \n" 
  "// def2(DPspc):   Partition of unity for domain decomp. (displacement-damage) \n" 
  "// def2(up)   :   previous iteration vectorial displacement-damage vector     \n";
  if(reactionforce && reactionforcemethod=="variational-based")writeIt 
  "// def2(F) : force vector, it is [Fx,Fy] in 2D and [Fx,Fy,Fz] in 3D           \n"; 
  if(ParaViewPostProcess)writeIt
  "// phi     : Scalar P1 visulization field phi                                 \n";   
  if(energydecomp)writeIt
  "// PsiPlusP1    :   tensile energy P1 field                                   \n"
  "// PsiMinusP1   :   compressive energy P1 field                               \n"
  "// PsiPlus      :   tensile energy P0 field                                   \n"
  "// PsiMinus     :   compressive energy P0 field                               \n"  
  "// HistMinus    :   history function based on  compressive energy P0 field    \n"     
  "// HistPlus     :   history function based on  tensile energy  P0 field       \n";     
  writeIt
  "//============================================================================\n"
  "                                                                              \n"
  "  Vh  def2(u)    ,                                                            \n"
  "      def2(uold) ,                                                            \n"
  "      def2(DPspc);                                                            \n"
  "                                                                              \n"   
  "  Vh  def2(up)    ;                                                           \n";  

  if(reactionforce && reactionforcemethod=="variational-based")
   writeIt
   "                                                                            \n"   
   "  Vh  def2(F)    ;                                                          \n";  
  
  if(ParaViewPostProcess)
   writeIt
   "                                                                             \n"
   "  Vh1  phi      ;                                                            \n";   

  if(energydecomp)
   writeIt
   "                                                                             \n"
   "  Vh1 PsiPlusP1   ,                                                          \n"
   "      PsiMinusP1  ;                                                          \n"
   "                                                                             \n"
   "                                                                             \n"
   "  Wh0 HistPlus  ,                                                            \n"
   "      HistMinus ,                                                            \n"
   "      PsiPlus   ,                                                            \n"
   "      PsiMinus  ;                                                            \n";
 } 
}

if(Prblm=="elastodynamics"  || Prblm=="soildynamics"){


if(Model!="pseudo-nonlinear" && Model!="Hujeux")
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

if(Model=="pseudo-nonlinear" || Model=="Hujeux" ){
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
 "// def(DPspc) :  Partition of unity field for integral                         \n";
 if(Model=="Hujeux")writeIt
 "// defSh(Sig) :  Three stress components                                       \n"
 "// defSh(Eps) :  Three strain components                                       \n"
 "// defIh(Iv)  :  25 component internal variables components                    \n";
 writeIt
 "//=============================================================================\n"
 "                                                                               \n"
 "  Vh  def(du)    ,                                                             \n"
 "      def(uold)  ,                                                             \n"
 "      def(uNL)   ,                                                             \n"
 "      def(vold)  ,                                                             \n"
 "      def(aold)  ,                                                             \n"
 "      def(DPspc) ;                                                             \n"
 "                                                                               \n";
 
 if(Model=="Hujeux")
 writeIt
 "                                                                               \n"
 "  Q3vh  defSh(Sig),                                                            \n"
 "        defSh(Eps);                                                            \n"
 "                                                                               \n"
 "  Q25vh defIh(Iv);                                                             \n"
 "                                                                               \n"; 
 
 }

}

if(Prblm=="damage" && Model=="hybrid-phase-field"){

 if(Sequential)
  writeIt
  "                                                                              \n"
  "//============================================================================\n"
  "// ------- Fem matrices and vectors -------                                   \n"
  "// -------------------------------------------------------------------        \n"
  "// A  :  FEM matrix assembled  linear momentum Eq. (stiffness matrix)         \n"
  "// A1 :  FEM matrix assembled  phase-field/Helmothz Eq.(stiffness matrix)     \n"
  "// b  :  RHS vector for the FE linear system  from linear momentum Eq.        \n"
  "// b1 :  RHS vector for the FE linear system  from lphase-field/Helmothz Eq.  \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  matrix  A, A1                              ;                                \n"
  "  real[int]  b(Vh.ndof), b1(Vh1.ndof)        ;                                \n";

  if(!Sequential){
   writeIt
   "                                                                             \n"
   "//===========================================================================\n"
   "// -------  Fem matrices and vectors -------                                 \n"
   "// -------------------------------------------------------------------       \n"
   "// A  : distributed FE matrix for PETSc                                      \n"   
   "//===========================================================================\n"
   "                                                                             \n"
   <<(timelog ? "  timerbegin(\"matrix sparsity assembly\",t0)\n" : ""           )<<
   "  Mat  A( Vh.ndof,  restrictionIntersectionP, DP)   ;                        \n";

   if(vectorial && constrainHPF)
    writeIt
    "                                                                            \n"
    "  Mat A1( DZ.n,  restrictionIntersectionZ, DZ);                             \n";

   if(!vectorial)
    writeIt
    "                                                                            \n"
    "  Mat A1( Vh1.ndof,  restrictionIntersectionZ, DZ);                         \n"
    <<(timelog ? "  timerend(\"matrix sparsity assembly\",t0)\n" : " "           )<<
    "                                                                            \n"
    "  matrix     ALoc, ALoc1                 ;  // Local matrices for bilinear  \n"
    "  real[int]  b(Vh.ndof), b1(Vh1.ndof)    ;  // Local vectors for  linear    \n";

   if(vectorial)
    writeIt
    "                                                                            \n"
    <<(timelog ? "  timerend(\"matrix sparsity assembly\",t0)\n" : " "           )<<
    "  matrix     ALoc           ;      // Local vectorial matrix for bilinear   \n"
    "  real[int]  b(Vh.ndof)     ;      // Local vectorial real vector for linear\n";


   writeIt
   "                                                                             \n"
   "//===========================================================================\n"
   "// ------- Partition of unity for integrals -------                          \n"
   "//===========================================================================\n"
   "                                                                             \n"
   "  for(int i=0; i<DP.n; i++)                                                  \n"
   "    DPspc[][i]=DP[i];                                                        \n";

   if(!vectorial)
    writeIt
    "                                                                            \n"
    "  for(int i=0; i<DZ.n; i++)                                                 \n"
    "    DZspc[][i]=DZ[i];                                                       \n";
  }
}


if(Prblm=="elastodynamics" || Prblm=="soildynamics"){

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

  if(pipegnu && !top2vol)
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

  if(!top2vol)
  writeIt
  "                                                                              \n"
  <<(timelog ? "  timerbegin(\"matrix sparsity assembly\",t0)\n" : ""         )<<
  "  Mat  A(Vh.ndof, restrictionIntersectionP, DP, symmetric=1)  ;               \n"
  <<(timelog ? "  timerend(\"matrix sparsity assembly\",t0)\n" : " "          )<<
  "                                                                              \n";

  if(top2vol)
  writeIt
  "                                                                              \n"
  <<(timelog ? "  timerbegin(\"matrix sparsity assembly\",t0)\n" : ""         )<<
  "  Mat A; createMat(Th, A, Pk);                                                \n"
  <<(timelog ? "  timerend(\"matrix sparsity assembly\",t0)\n" : " "          )<<
  "                                                                              \n";
    
 }
}

if(Prblm=="damage" && Model=="Mazar"){
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "// ------- Finite element variables -------                                    \n"
 "//=============================================================================\n"
 "                                                                               \n"
 "  Vh  def(u)      ,    // Current displacement                                 \n"
 "      def(du)     ,    // Incremental displacement (du{n})                     \n"
 "      def(DPspc)  ;    // Partition of unity                                   \n"
 "                                                                               \n"
 "  Wh0 damage      ,    //  Isotropic damage                                    \n"
 "      intVar      ,    //  Internal variable                                   \n"
 "                                                                               \n"; 

 if(!useGFP)
  writeIt
  "                                                                              \n"  
  "      e11         ,    //  11 component of strain                             \n"
  "      e22         ,    //  22 component of strain                             \n"
  "      e12         ,    //  12 component of strain                             \n"
  "      ep1         ,    //  1st principal strain component (in x)              \n"
  "      ep2         ,    //  2nd principal strain component (in y)              \n"
  "      eqStrain    ,    //  Equivalent strain                                  \n";

 writeIt
 "                                                                               \n" 
 "      lambdafield ,    //  lambda                                              \n"
 "      mufield     ;    //  mu                                                  \n"
 "                                                                               \n";

 if(useGFP)
  writeIt
  "                                                                              \n"  
  "  VhStr defStrain(strain)     ;    //  Stain defenition                       \n";

 if(!Sequential)
  writeIt
  "                                                                              \n"
  "//============================================================================\n"
  "// -------  Fem matrices and vectors -------                                  \n"
  "//============================================================================\n"
  "                                                                              \n"
  <<(timelog ? "  timerbegin(\"matrix sparsity assembly\",t0)\n" : ""         )<<
  "  Mat  A( Vh.ndof,  restrictionIntersectionP, DP)   ;                         \n"
  <<(timelog ? "  timerend(\"matrix sparsity assembly\",t0)\n" : " "          )<<
  "                                                                              \n"
  "  matrix     ALoc           ;        // Local vectorial matrix for bilinear   \n"
  "  real[int]  b(Vh.ndof)     ;        // Local vectorial real vector for linear\n"
  "                                                                              \n"
  "//============================================================================\n"
  "// ------- Partition of unity for integrals -------                           \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  for(int i=0; i<DP.n; i++)                                                   \n"
  "    DPspc[][i]=DP[i];                                                         \n";
}

} //-- [ostream terminator]  FemParameters.edp closed --//

cout << "     ........................ Done \n";
