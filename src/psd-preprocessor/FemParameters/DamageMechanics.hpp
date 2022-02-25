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

writeHeader;

if(Model=="hybrid_phase_field"){

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
  if(reactionforce && reactionforcemethod=="variational_based")writeIt
  "// def2(F) : force vector, it is [Fx,Fy] in 2D and [Fx,Fy,Fz] in 3D           \n";
  if(NonLinearMethod=="Newton_Raphson")writeIt
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

  if(reactionforce && reactionforcemethod=="variational_based")
   writeIt
   "                                                                             \n"
   "  Vh  def2(F)    ;                                                           \n";

  if(NonLinearMethod=="Newton_Raphson")
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
  if(reactionforce && reactionforcemethod=="variational_based")writeIt
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

  if(reactionforce && reactionforcemethod=="variational_based")
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
  if(reactionforce && reactionforcemethod=="variational_based")writeIt
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

  if(reactionforce && reactionforcemethod=="variational_based")
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
   "// A  : distributed FE matrix for PETSc                                      \n";
   if(vectorial && constrainHPF)writeIt
   "// A1 : distributed FE matrix for PETSc (for damage)                         \n";
   if(!vectorial)writeIt
   "// A1    : distributed FE matrix for PETSc (for damage)                      \n"
   "// ALoc  : local matrices for assembling bilinear form linear momentum Eq    \n"
   "// ALoc1 : local matrices for assembling bilinear form phase field Eq        \n"
   "// b     : local vector for assembling bc vector form linear momentum Eq     \n"
   "// b1    : local vector for assembling bc vector form phase field Eq         \n";
   if(vectorial)writeIt
   "// ALoc  : local matrices for assembling bilinear form of vectorial equation \n"
   "//         linear momentum Eq  coupled to phase-field equation               \n"
   "// b     : local vector for assembling bc vector form of vectorial equation  \n"
   "//         linear momentum Eq  coupled to phase-field equation               \n";
   writeIt
   "//===========================================================================\n"
   "                                                                             \n"
   "  startProcedure(\"matrix sparsity assembly\",t0)                            \n"
   "  Mat  A( Vh.ndof,  restrictionIntersectionP, DP)   ;                        \n";

   if(vectorial && constrainHPF)
    writeIt
    "                                                                            \n"
    "  Mat A1( DZ.n,  restrictionIntersectionZ, DZ);                             \n";

   if(!vectorial)
    writeIt
    "                                                                            \n"
    "  Mat A1( Vh1.ndof,  restrictionIntersectionZ, DZ);                         \n"
    "  endProcedure(\"matrix sparsity assembly\",t0)                             \n"
    "                                                                            \n"
    "  matrix     ALoc, ALoc1                 ;                                  \n"
    "  real[int]  b(Vh.ndof), b1(Vh1.ndof)    ;                                  \n";

   if(vectorial)
    writeIt
    "                                                                            \n"
    "  endProcedure(\"matrix sparsity assembly\",t0)                             \n"
    "  matrix     ALoc           ;                                               \n"
    "  real[int]  b(Vh.ndof)     ;                                               \n";


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


if(Model=="Mazar"){
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
  "  startProcedure(\"matrix sparsity assembly\",t0)                             \n"
  "  Mat  A( Vh.ndof,  restrictionIntersectionP, DP)   ;                         \n"
  "  endProcedure(\"matrix sparsity assembly\",t0)                               \n"
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

