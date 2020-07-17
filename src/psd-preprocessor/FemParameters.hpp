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
 "//============================================================================\n"
 "                                                                              \n"
 "  Vh  def(u)    ;    //  Displacement                                         \n";

if(Prblm=="damage" && Model=="hybrid-phase-field"){

 if(!vectorial){
 
  writeIt
  "                                                                              \n"
  "//============================================================================\n"
  "// -------Finite element variables -------                                    \n"
  "//============================================================================\n"
  "                                                                              \n";

  if(NonLinearMethod=="Picard")
   writeIt
   "  Vh  def2(u)    ,    //  Displacement                                       \n"
   "      def2(uold) ,    //  Previous displacement                              \n"
   "      def2(DPspc);    //  Partition of unity                                 \n"
   "                                                                             \n"
   "                                                                             \n"
   "  Vh1 phi       ,     //  Phase field                                        \n"
   "      phiold    ,     //  Previous iteration phase field                     \n"
   "      DZspc     ;     //  Partition of unity                                 \n";


  if(NonLinearMethod=="Newton-Raphson")
   writeIt
   "  Vh  def2(du)   ,    //  Displacement                                       \n"
   "      def2(u)    ,    //  Previous displacement                              \n"
   "      def2(DPspc);    //  Partition of unity                                 \n"
   "                                                                             \n"
   "                                                                             \n"
   "  Vh1 dphi      ,     //  Phase field                                        \n"
   "      phi       ,     //  Previous iteration phase field                     \n"
   "      DZspc     ;     //  Partition of unity                                 \n";


  if(energydecomp)
   writeIt
   "                                                                             \n"
   "  Vh1 HistPlusP1   ,    //  History tesile energy P1 field                   \n"
   "      HistMinusP1  ;    //  History compressive energy P1 fiels              \n"
   "                                                                             \n"
   "                                                                             \n"
   "  Wh0 HistPlus  ,    // Tensile history                                      \n"
   "      HistMinus ,    // Compressive energy history                           \n"
   "      PsiPlus   ,    // Tensile energy                                       \n"
   "      PsiMinus  ;    // Compressive nergy                                    \n";
 }

 if(vectorial){
  writeIt
  "                                                                              \n"
  "//============================================================================\n"
  "// ------- Finite element variables -------                                   \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  Vh  def(u)    ,    // Vectorial variable for [u,phi]                        \n"
  "      def(uold) ,    // Vectorial variable for old [u,phi]                    \n"
  "      def(DPspc);    // Vectorial variables for partition of unity            \n";

  if(energydecomp)
   writeIt
   "                                                                             \n"
   "  Vh1 HistPlusP1   ,    //  History tesile energy P1 field                   \n"
   "      HistMinusP1  ;    //  History compressive energy P1 fiels              \n"
   "                                                                             \n"
   "                                                                             \n"
   "  Wh0 HistPlus  ,    // Tensile history                                      \n"
   "      HistMinus ,    // Compressive energy history                           \n"
   "      PsiPlus   ,    // Tensile energy                                       \n"
   "      PsiMinus  ;    // Compressive nergy                                    \n";
 }
}

if(Prblm=="elastodynamics"  || Prblm=="soildynamics"){
if(Model!="pseudo-nonlinear" && Model!="Hujeux")
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "// -------Finite element variables -------                                     \n"
 "//=============================================================================\n"
 "                                                                               \n"
 "  Vh  def(du)    ,      // Displacement FE field                               \n"
 "      def(uold)  ,      // Previous iteration displacement FE field            \n"
 "      def(vold)  ,      // Previous iteration velocity FE field                \n"
 "      def(aold)  ,      // Previous iteration acceleration FE field            \n"
 "      def(DPspc) ;      // Partition of unity field for integral               \n"
 "                                                                               \n";

if(Model=="pseudo-nonlinear" || Model=="Hujeux" )
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "// -------Finite element variables -------                                     \n"
 "//=============================================================================\n"
 "                                                                               \n"
 "  Vh  def(du)    ,      // Displacement FE field                               \n"
 "      def(uold)  ,      // Previous iteration displacement FE field            \n"
 "      def(uNL)   ,      // Nonlinear iteration displacement FE field           \n"
 "      def(vold)  ,      // Previous iteration velocity FE field                \n"
 "      def(aold)  ,      // Previous iteration acceleration FE field            \n"
 "      def(DPspc) ;      // Partition of unity field for integral               \n"
 "                                                                               \n";
 
 if(Model=="Hujeux")
 writeIt
 "                                                                               \n"
 "  Q3vh  defSh(Sig),      // Three stress components                            \n" 
 "        defSh(Eps);      // Three strain components                            \n"
 "                                                                               \n"
 "  Q25vh defIh(Iv);       // 25 component internal variables components         \n"
 "                                                                               \n";
     
}

if(Prblm=="damage" && Model=="hybrid-phase-field"){

 if(Sequential)
  writeIt
  "                                                                              \n"
  "//============================================================================\n"
  "// ------- Fem matrices and vectors -------                                   \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  matrix  A, A1                              ;                                \n"
  "  real[int]  b(Vh.ndof), b1(Vh1.ndof)        ;                                \n";

  if(!Sequential){
   writeIt
   "                                                                             \n"
   "//===========================================================================\n"
   "// -------  Fem matrices and vectors -------                                 \n"
   "//===========================================================================\n"
   "                                                                             \n"
   <<(timelog ? "  MPItimerbegin(\"matrix sparsity assembly\",t0)\n" : ""        )<<
   "  Mat  A( Vh.ndof,  restrictionIntersectionP, DP)   ;                        \n";

   if(!vectorial)
    writeIt
    "                                                                            \n"
    "  Mat A1( Vh1.ndof,  restrictionIntersectionZ, DZ);                         \n"
    <<(timelog ? "  MPItimerend(\"matrix sparsity assembly\",t0)\n" : " "        )<<
    "                                                                            \n"
    "  matrix     ALoc, ALoc1                 ;  // Local matrices for bilinear  \n"
    "  real[int]  b(Vh.ndof), b1(Vh1.ndof)    ;  // Local vectors for  linear    \n";

   if(vectorial)
    writeIt
    "                                                                            \n"
    <<(timelog ? "  MPItimerend(\"matrix sparsity assembly\",t0)\n" : " "        )<<
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
  "  matrix  A                        ;                                          \n"
  "  real[int]  b(Vh.ndof)        ;                                              \n";

 if(!Sequential){
  
  if(pipegnu)
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
  "  real[int]    b(Vh.ndof);                                                    \n"
  "                                                                              \n"
  <<(timelog ? "  MPItimerbegin(\"matrix sparsity assembly\",t0)\n" : ""         )<<
  "  Mat  A(Vh.ndof, restrictionIntersectionP, DP, symmetric=1)  ;               \n"
  <<(timelog ? "  MPItimerend(\"matrix sparsity assembly\",t0)\n" : " "          )<<
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
 "      intVar      ,    //  Internal variable                                   \n";

 if(!useGFP)
  writeIt
  "      e11         ,    //  11 component of strain                             \n"
  "      e22         ,    //  22 component of strain                             \n"
  "      e12         ,    //  12 component of strain                             \n"
  "      ep1         ,    //  1st principal strain component (in x)              \n"
  "      ep2         ,    //  2nd principal strain component (in y)              \n"
  "      eqStrain    ,    //  Equivalent strain                                  \n";

 writeIt        
 "      lambdafield ,    //  lambda                                              \n"
 "      mufield     ;    //  mu                                                  \n"
 "                                                                               \n";

 if(useGFP)
  writeIt
  "  VhStr defStrain(strain)     ;    //  Stain defenition                       \n";

 if(!Sequential)
  writeIt
  "                                                                              \n"
  "//============================================================================\n"
  "// -------  Fem matrices and vectors -------                                  \n"
  "//============================================================================\n"
  "                                                                              \n"
  <<(timelog ? "  MPItimerbegin(\"matrix sparsity assembly\",t0)\n" : ""         )<<
  "  Mat  A( Vh.ndof,  restrictionIntersectionP, DP)   ;                         \n"
  <<(timelog ? "  MPItimerend(\"matrix sparsity assembly\",t0)\n" : " "          )<<
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
