/**************************************************************************************
*                                                                                     *
* Author : Mohd Afeef BADRI                                                           *
* Email  : mohd-afeef.badri@cea.fr                                                    *
* Date   : 20/04/2020                                                                 *
* Type   : Support file                                                               *
*                                                                                     *
* Comment: This support  file is responsible for generating Macro.edp  which contains *
*           main macros compiletime/runtime for PSD solver.                           *
*                                                                                     *
**************************************************************************************/

writeHeader;

if(spc==2)
 {

 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "//                     ------- Essential Macros -------                        \n"
 "// --------------------------------------------------------------------------- \n";
 if(!Sequential)writeIt
 "// partitioner : mesh partitioner to be used use metis, parmetis, or scotch    \n"
 "// dimension   : dimension of the problem 2 or 3 for 2D or 3D                  \n";
 if(vectorial)if(Prblm=="damage" && Model=="hybrid_phase_field")
 if(ParaViewPostProcess || debug)writeIt
 "// Pltk        : paraview post-processing macro on P1 function possible        \n"
 "// def0(i)     : macro needed post-processing via paraview                     \n";
 if(Prblm=="damage" && Model=="hybrid_phase_field" && energydecomp)
 writeIt
 "// Sk          : third order strain vector                                     \n";
 writeIt
 "// Ux, Uy      : x and y displacements                                         \n"
 "// Pk          : finite element space definition                               \n"
 "// def(i)      : to define a vectorial field                                   \n"
 "// init(i)     : to initialize a vectorial field                               \n"
 "//=============================================================================\n"
 "                                                                               \n";

 if(!Sequential)
 writeIt
 "  macro partitioner "<<Partitioner<<" //                                       \n"
 "  macro dimension 2 //                                                         \n";

 writeIt
 "  macro Ux u  //                                                                \n"
 "  macro Uy u1 //                                                                \n";

 if(Model=="hybrid_phase_field")
 if(vectorial && !constrainHPF)
 writeIt
 "  macro Pk [ P"<<lag<<" ,                                                       \n"
 "             P"<<lag<<" ,                                                       \n"
 "             P"<<lag<<" ] //                                                    \n"
 "                                                                                \n"
 "  macro def(i) [ i   ,                                                          \n"
 "                 i#1 ,                                                          \n"
 "                 i#2 ] //                                                       \n"
 "                                                                                \n"
 "  macro init(i) [ i ,                                                           \n"
 "                  i ,                                                           \n"
 "                  i ] //                                                        \n"
 "                                                                                \n";

 if(Model=="hybrid_phase_field")
 if(vectorial && constrainHPF)
 writeIt
 "  macro Pk [ P"<<lag<<" ,                                                       \n"
 "             P"<<lag<<" ,                                                       \n"
 "             P"<<lag<<" ] //                                                    \n"
 "                                                                                \n";

 if(ParaViewPostProcess)
 writeIt
 "  macro PlotVec(i) [ i   ,                                                      \n"
 "                     i#1 ,                                                      \n"
 "                     0   ] //                                                   \n"
 "                                                                                \n";

 if(vectorial && Model=="hybrid_phase_field")
 if(ParaViewPostProcess || debug)
 writeIt
 "  macro Pltk    P1 //                                                           \n"
 "  macro def0(i) i  //                                                           \n";

 if(Model=="hybrid_phase_field" && energydecomp)
 writeIt
 "  macro Sk [ P0 ,                                                               \n"
 "             P0 ,                                                               \n"
 "             P0 ] //                                                            \n"
 "                                                                                \n"
 "                                                                                \n";

 if(useGFP && Model=="Mazar")
 writeIt
 "  macro Sk [ P0 ,                                                               \n"
 "             P0 ,                                                               \n"
 "             P0 ]       // Third order strain vector                            \n"
 "                                                                                \n"
 "  macro defStrain(i) [ i   ,                                                    \n"
 "                       i#1 ,                                                    \n"
 "                       i#2 ] // Vect. field definition                          \n"
  "                                                                               \n";

 if(!vectorial)
  {
  writeIt
  "  macro Pk     [ P"<<lag<<" ,                                                  \n"
  "                 P"<<lag<<" ] //                                               \n"
  "                                                                               \n";

  if(Model=="Mazar")
  writeIt
  "  macro def(i) [ i   ,                                                         \n"
  "                 i#1 ] //                                                      \n"
  "                                                                               \n";

  if(!Sequential  && Model=="Mazar")
  writeIt
  "  macro init(i) [ i ,                                                          \n"
  "                  i ] //                                                       \n"
  "                                                                               \n";
  }   //-- [if loop terminator] !vectorial ended --//


 if(Model=="hybrid_phase_field")
 if(vectorial && constrainHPF)
 writeIt
 "                                                                              \n"
 "//---------------------------Non-linear macros---------------------------//   \n"
 "                                                                              \n"
 "  macro def2  (i) [ i , i#1 , i#2 ]                   // Vect. field          \n"
 "  macro init2 (i) [ i ,  i  , i   ]                   // Vect. initialize     \n"
 "  macro def   (i)     i                               // Scalar field         \n"
 "  macro init  (i)     i                               // Initialize           \n"
 "  macro Zk            P1                              // FE space             \n";

 if(Model=="hybrid_phase_field")
 if(!vectorial)
 writeIt
 "                                                                              \n"
 "//---------------------------Non-linear macros---------------------------//   \n"
 "                                                                              \n"
 "  macro def2  (i) [ i , i#1 ]                         // Vect. field          \n"
 "  macro init2 (i) [ i ,  i  ]                         // Vect. initialize     \n"
 "  macro def   (i)     i                               // Scalar field         \n"
 "  macro init  (i)     i                               // Initialize           \n"
 "  macro Zk            P1                              // FE space             \n";

 if(fastmethod)
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "//                 ------- operator definition macros  -------                 \n"
 "// --------------------------------------------------------------------------- \n"
 "// divergence(i) : divergence operator definition, given a displacement vector \n"
 "//                 'i' returns scalar value                                    \n"
 "// epsilon(i)    : symmetric strain tensor operator given  displacement vector \n"
 "//                 'i' returns strain  vector [Exx,Eyy,Ezz,Eyz,Exz,Exy]        \n"
 "//=============================================================================\n"
 "                                                                               \n"
 "  macro divergence(i) (dx(i) + dy(i#1)) //                                     \n"
 "  macro epsilon(i) [ dx(i)               ,                                     \n"
 "                     dy(i#1)             ,                                     \n"
 "                     (dy(i)+dx(i#1))/SQ2 ] //                                  \n";
 
 
 if(Model=="hybrid_phase_field" && !energydecomp)
 writeIt
 "                                                                              \n"
 "//------------------------------Hplus macros-------------------------------   \n"
 "                                                                              \n"
 "  macro Hplus (i) ( (0.5*lambda+mu)*(  epsilon(i)[0]*epsilon(i)[0]            \n"
 "                                     + epsilon(i)[1]*epsilon(i)[1] )          \n"
 "                   + lambda*epsilon(i)[0]*epsilon(i)[1]                       \n"
 "                   + mu*epsilon(i)[2]*epsilon(i)[2]                           \n"
 "                  )                                           // Hplus        \n"
 "                                                                              \n";


 if(Model=="hybrid_phase_field" && energydecomp){
 writeIt
 "                                                                              \n"
 "//------------------------------Hplus macros-------------------------------// \n"
 "                                                                              \n"
 "  macro DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus){          \n"
 "    real[int] par = [lambda,mu];                                              \n";

 if(vectorial && !constrainHPF)
 writeIt
 "                                                                              \n"
 "    Sh0 [Eps1,Eps2,Eps12] = [dx(uold),dy(uold1),0.5*(dx(uold1)+dy(uold))];    \n";

 if(vectorial && constrainHPF)
 writeIt
 "                                                                              \n"
 "    Sh0 [Eps1,Eps2,Eps12] = [dx(u),dy(u1),0.5*(dx(u1)+dy(u))];                \n";

 if(!vectorial && !constrainHPF)
 writeIt
 "                                                                              \n"
 "    Sh0 [Eps1,Eps2,Eps12] = [dx(u),dy(u1),0.5*(dx(u1)+dy(u))];                \n";

 if(!vectorial && constrainHPF)
 writeIt
 "                                                                              \n"
 "    Sh0 [Eps1,Eps2,Eps12] = [dx(u),dy(u1),0.5*(dx(u1)+dy(u))];                \n";

 writeIt
 "    GFPSplitEnergy(Eps1[],PsiPlus[],PsiMinus[],HistPlus[],HistMinus[],par)  ; \n"
 "  }//                                                                         \n"
 "                                                                              \n";
 }

 if(Model=="Mazar")
 writeIt
 "                                                                              \n"
 "//-----------------------Stess calculation macro--------------------------//  \n"
 "                                                                              \n"
 "  macro stress(i,lambdaVal,muVal)                                             \n"
 "     [lambdaVal*(epsilon(i)[0]+epsilon(i)[1])+2.*muVal*epsilon(i)[0] ,        \n"
 "     lambdaVal*(epsilon(i)[0]+epsilon(i)[1])+2.*muVal*epsilon(i)[1]  ,        \n"
 "     2.*muVal*epsilon(i)[2]                                          ] //     \n"
 "                                                                              \n";

 if(Sequential)
 writeIt
  "                                                                               \n"
  "//=============================================================================\n"
  "//      ------- remapping Macros -------                                       \n"
  "// --------------------------------------------------------------------------- \n"
  "// meshN     : Two-dimensional problem mesh                                    \n"
  "// intN      : Two-dimensional integral                                        \n"
  "// intN1     : One-dimensional integral                                        \n"
  "// grad      : Two-dimensional gradient                                        \n"
  "// readmeshN : Two-dimensional mesh reading .mesh format                       \n"
  "// gmshloadN : Two-dimensional mesh reading .msh format                        \n"
  "//=============================================================================\n"
 "                                                                                \n"
 "  macro meshN()mesh                   //                                        \n"
 "  macro intN()int2d                   //                                        \n"
 "  macro intN1()int1d                  //                                        \n"
 "  macro readmeshN()readmesh           //                                        \n"
 "  macro gmshloadN()gmshload           //                                        \n"
 "  macro grad(i) [dx(i),dy(i)]         //                                        \n"
 "                                                                                \n";


 if(tractionconditions>=1)
 {
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "//      ------- Neumann/Traction boundary condition Macros -------             \n"
 "// --------------------------------------------------------------------------- \n"
 "// NeumannBc'I' : will define the full Neumann boundary condition on border I  \n"
 "//=============================================================================\n";

 for(int i=0; i<tractionconditions; i++)
 writeIt
 "                                                                               \n"
 "  IFMACRO(Tbc"<<i<<"Tx) IFMACRO(!Tbc"<<i<<"Ty)                                 \n"
 "    NewMacro NeumannBc"<<i<<"() (Tbc"<<i<<"Tx)*v  EndMacro                     \n"
 "  ENDIFMACRO ENDIFMACRO                                                        \n"
 "                                                                               \n"
 "  IFMACRO(!Tbc"<<i<<"Tx) IFMACRO(Tbc"<<i<<"Ty)                                 \n"
 "    NewMacro NeumannBc"<<i<<"() (Tbc"<<i<<"Ty)*v1  EndMacro                    \n"
 "  ENDIFMACRO ENDIFMACRO                                                        \n"
 "                                                                               \n"
 "  IFMACRO(Tbc"<<i<<"Tx) IFMACRO(Tbc"<<i<<"Ty)                                  \n"
 "    NewMacro NeumannBc"<<i<<"() (Tbc"<<i<<"Tx)*v+(Tbc"<<i<<"Ty)*v1  EndMacro   \n"
 "  ENDIFMACRO ENDIFMACRO                                                        \n"
 "                                                                               \n";
 }

 if(dirichletconditions>=1)
 {
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "//         ------- Dirichlet boundary condition macros -------                 \n"
 "// --------------------------------------------------------------------------- \n"
 "// DirichletBc'I' : will define the full Dirichlet boundary condition on       \n"
 "//                  border I                                                   \n"
 "//=============================================================================\n";

 for(int i=0; i<dirichletconditions; i++)
 writeIt
 "                                                                               \n"
 "  IFMACRO(Dbc"<<i<<"Ux) IFMACRO(!Dbc"<<i<<"Uy)                                 \n"
 "    NewMacro DirichletBc"<<i<<"() Ux=Dbc"<<i<<"Ux  EndMacro                    \n"
 "  ENDIFMACRO ENDIFMACRO                                                        \n"
 "                                                                               \n"
 "  IFMACRO(!Dbc"<<i<<"Ux) IFMACRO(Dbc"<<i<<"Uy)                                 \n"
 "    NewMacro DirichletBc"<<i<<"() Uy=Dbc"<<i<<"Uy  EndMacro                    \n"
 "  ENDIFMACRO ENDIFMACRO                                                        \n"
 "                                                                               \n"
 "  IFMACRO(Dbc"<<i<<"Ux) IFMACRO(Dbc"<<i<<"Uy)                                  \n"
 "    NewMacro DirichletBc"<<i<<"() Ux=Dbc"<<i<<"Ux,Uy=Dbc"<<i<<"Uy  EndMacro    \n"
 "  ENDIFMACRO ENDIFMACRO                                                        \n"
 "                                                                               \n";
 }

 if(bodyforceconditions>=1)
 {
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "//      ------- volumetric bodyforce  conditions macro -------                 \n"
 "// --------------------------------------------------------------------------- \n"
 "// BodyforceBc'I' : will define the body force boundary condition on region I  \n"
 "//=============================================================================\n";

 for(int i=0; i<bodyforceconditions; i++)
 writeIt
 "                                                                               \n"
 "  IFMACRO(Fbc"<<i<<"Fx) IFMACRO(!Fbc"<<i<<"Fy)                                 \n"
 "    NewMacro BodyforceBc"<<i<<"() Fbc"<<i<<"Fx*v  EndMacro                     \n"
 "  ENDIFMACRO ENDIFMACRO                                                        \n"
 "                                                                               \n"
 "  IFMACRO(!Fbc"<<i<<"Fx) IFMACRO(Fbc"<<i<<"Fy)                                 \n"
 "    NewMacro BodyforceBc"<<i<<"() Fbc"<<i<<"Fy*v1  EndMacro                    \n"
 "  ENDIFMACRO ENDIFMACRO                                                        \n"
 "                                                                               \n"
 "  IFMACRO(Fbc"<<i<<"Fx) IFMACRO(Fbc"<<i<<"Fy)                                  \n"
 "    NewMacro BodyforceBc"<<i<<"() Fbc"<<i<<"Fx*v+Fbc"<<i<<"Fy*v1  EndMacro     \n"
 "  ENDIFMACRO ENDIFMACRO                                                        \n"
 "                                                                               \n";
 }

} //-- [if loop terminator] space==2 ended --//



if(spc==3){

 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "//                     ------- Essential Macros -------                        \n"
 "// --------------------------------------------------------------------------- \n";
 if(!Sequential)writeIt
 "// partitioner : mesh partitioner to be used use metis, parmetis, or scotch    \n"
 "// dimension   : dimension of the problem 2 or 3 for 2D or 3D                  \n";
 if(vectorial)if(Prblm=="damage" && Model=="hybrid_phase_field")
 if(ParaViewPostProcess || debug)
 "// Pltk        : paraview post-processing macro on P1 function possible        \n"
 "// def0(i)     : macro needed post-processing via paraview                     \n";
 writeIt
 "// Ux, Uy      : x and y displacements                                         \n"
 "// Pk          : finite element space definition                               \n"
 "// def(i)      : to define a vectorial field of same order as Pk               \n"
 "// init(i)     : to initialize a vectorial field of same order as Pk           \n"
 "//=============================================================================\n"
 "                                                                               \n";

 if(!Sequential)
  writeIt
  "  macro partitioner "<<Partitioner<<" //                                      \n"
  "  macro dimension   3 //                                                      \n";

 writeIt
 "  macro Ux    u  //                                                            \n"
 "  macro Uy    u1 //                                                            \n"
 "  macro Uz    u2 //                                                            \n";

 if(Model=="hybrid_phase_field")
 if(vectorial && !constrainHPF)
 writeIt
 "  macro Pk [ P"<<lag<<" ,                                                      \n"
 "             P"<<lag<<" ,                                                      \n"
 "             P"<<lag<<" ,                                                      \n"
 "             P"<<lag<<" ] //                                                   \n"
 "                                                                               \n"
 "  macro def(i) [ i   ,                                                         \n"
 "                 i#1 ,                                                         \n"
 "                 i#2 ,                                                         \n"
 "                 i#3 ] //                                                      \n"
 "                                                                               \n"
 "  macro init(i) [ i ,                                                          \n"
 "                  i ,                                                          \n"
 "                  i ,                                                          \n"
 "                  i ] //                                                       \n"
 "                                                                               \n";


 if(Model=="hybrid_phase_field")
 if(vectorial && constrainHPF)
 writeIt
 "  macro Pk [ P"<<lag<<" ,                                                      \n"
 "             P"<<lag<<" ,                                                      \n"
 "             P"<<lag<<" ,                                                      \n"
 "             P"<<lag<<" ] //                                                   \n"
 "                                                                               \n";

 if(ParaViewPostProcess)
 writeIt
 "  macro PlotVec(i) [ i   ,                                                      \n"
 "                     i#1 ,                                                      \n"
 "                     i#2 ] //                                                   \n"
 "                                                                                \n";

 if(vectorial)if(Model=="hybrid_phase_field")
 if(ParaViewPostProcess || debug)
  writeIt
  "  macro Pltk      P1  //                                                      \n"
  "  macro def0 (i)  i   //                                                      \n";



 if(Model=="hybrid_phase_field" && energydecomp)
  writeIt
  "  macro Sk [ P0 ,                                                             \n"
  "             P0 ,                                                             \n"
  "             P0 ,                                                             \n"
  "             P0 ,                                                             \n"
  "             P0 ,                                                             \n"
  "             P0 ] // Sixth order strain vector                                \n"
  "                                                                              \n";

 if(Model=="Mazar")if(useGFP)
  writeIt
  "  macro Sk [ P0 ,                                                             \n"
  "             P0 ,                                                             \n"
  "             P0 ,                                                             \n"
  "             P0 ,                                                             \n"
  "             P0 ,                                                             \n"
  "             P0 ] // Sixth order strain vector                                \n"
  "                                                                              \n"
  "  macro defStrain(i) [ i   ,                                                  \n"
  "                       i#1 ,                                                  \n"
  "                       i#2 ,                                                  \n"
  "                       i#3 ,                                                  \n"
  "                       i#4 ,                                                  \n"
  "                       i#5 ]  // Vect. field definition                       \n"
  "                                                                              \n";

if(!vectorial){
  writeIt
  "  macro Pk [ P"<<lag<<" ,                                                     \n"
  "             P"<<lag<<" ,                                                     \n"
  "             P"<<lag<<" ] //                                                  \n"
  "                                                                              \n";

if(Model=="Mazar")
  writeIt
  "  macro def(i)  [ i  ,                                                        \n"
  "                  i#1,                                                        \n"
  "                  i#2] //                                                     \n"
  "                                                                              \n";

if(Model=="Mazar"  && !Sequential)
  writeIt
  "  macro init(i) [ i ,                                                         \n"
  "                  i ,                                                         \n"
  "                  i ] //                                                      \n"
  "                                                                              \n";

} //-- [if loop terminator] !vectorial ended --//


 if(fastmethod)
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "//                 ------- operator definition macros  -------                 \n"
 "// --------------------------------------------------------------------------- \n"
 "// divergence(i) : divergence operator definition, given a displacement vector \n"
 "//                 'i' returns scalar value                                    \n"
 "// epsilon(i)    : symmetric strain tensor operator given  displacement vector \n"
 "//                 'i' returns strain  vector [Exx,Eyy,Ezz,Eyz,Exz,Exy]        \n"
 "//=============================================================================\n"
 "                                                                               \n"
 "  macro divergence(i) ( dx( i ) + dy(i#1) + dz(i#2) )   //                     \n"
 "  macro epsilon   (i) [ dx( i ) , dy(i#1) , dz(i#2) ,                          \n"
 "                       (dz(i#1) + dy(i#2))/SQ2,                                \n"
 "                       (dz( i ) + dx(i#2))/SQ2,                                \n"
 "                       (dy( i ) + dx(i#1))/SQ2 ]        //                     \n"
 "                                                                               \n";
 
if(Model=="hybrid_phase_field" && !vectorial)
  writeIt
  "                                                                               \n"
  "//=============================================================================\n"
  "//                 ------- FE field definition macros  -------                 \n"
  "// --------------------------------------------------------------------------- \n"
  "// def2(i)   : Three component vectorial field definition                      \n"
  "// init2(i)  : Three component vectorial field initilization                   \n"
  "// def(i)    : Scalar field definition                                         \n"
  "// init(i)   : Scalar field initilization                                      \n"
  "// Zk        : Synonym of P1 fespace                                           \n"
  "//=============================================================================\n"
  "                                                                               \n"
  "  macro def2  (i)  [   i  ,  i#1 ,  i#2  ]   //                                \n"
  "  macro init2 (i)  [   i  ,   i  ,   i   ]   //                                \n"
  "  macro def   (i)     i                      //                                \n"
  "  macro init  (i)     i                      //                                \n"
  "  macro Zk            P1                     //                                \n";

if(Model=="hybrid_phase_field")
if(vectorial && constrainHPF)
  writeIt
  "                                                                               \n"
  "//=============================================================================\n"
  "//                 ------- FE field definition macros  -------                 \n"
  "// --------------------------------------------------------------------------- \n"
  "// def2(i)   : Three component vectorial field definition                      \n"
  "// init2(i)  : Three component vectorial field initilization                   \n"
  "// def(i)    : Scalar field definition                                         \n"
  "// init(i)   : Scalar field initilization                                      \n"
  "// Zk        : Synonym of P1 fespace                                           \n"
  "//=============================================================================\n"
  "                                                                               \n"
  "  macro def2  (i)  [   i  ,  i#1 ,  i#2 , i#3  ]  //                           \n"
  "  macro init2 (i)  [   i  ,   i  ,   i  , i    ]  //                           \n"
  "  macro def   (i)     i                           //                           \n"
  "  macro init  (i)     i                           //                           \n"
  "  macro Zk            P1                          //                           \n";


if(Model=="hybrid_phase_field" && !energydecomp)
  writeIt
  "                                                                              \n"
  "//------------------------------Hplus macros-----------------------------//   \n"
  "                                                                              \n"
  "  macro Hplus (i) ( (0.5*lambda+mu)*(  epsilon(i)[0]*epsilon(i)[0]            \n"
  "                                     + epsilon(i)[1]*epsilon(i)[1]            \n"
  "                                     + epsilon(i)[2]*epsilon(i)[2] )          \n"
  "                   + lambda*(epsilon(i)[0]*epsilon(i)[1]                      \n"
  "                   +         epsilon(i)[0]*epsilon(i)[2]                      \n"
  "                   +         epsilon(i)[1]*epsilon(i)[2] )                    \n"
  "                   + mu*(epsilon(i)[5]*epsilon(i)[5]                          \n"
  "                   +     epsilon(i)[4]*epsilon(i)[4]                          \n"
  "                   +     epsilon(i)[3]*epsilon(i)[3] )                        \n"
  "                  )                                           // Hplus        \n"
  "                                                                              \n";

if(Model=="Mazar")
  writeIt
  "                                                                              \n"
  "//-----------------------Stess calculation macro-------------------------//   \n"
  "                                                                              \n"
  "  macro stress(i,lmd,mu)                                                      \n"
  "  [                                                                           \n"
  "   lmd*(epsilon(i)[0]+epsilon(i)[1]+epsilon(i)[2])+2.*mu*epsilon(i)[0],       \n"
  "   lmd*(epsilon(i)[0]+epsilon(i)[1]+epsilon(i)[2])+2.*mu*epsilon(i)[1],       \n"
  "   lmd*(epsilon(i)[0]+epsilon(i)[1]+epsilon(i)[2])+2.*mu*epsilon(i)[2],       \n"
  "   2.*mu*epsilon(i)[3],                                                       \n"
  "   2.*mu*epsilon(i)[4],                                                       \n"
  "   2.*mu*epsilon(i)[5]                                                        \n"
  "  ]//                                                                         \n"
  "                                                                              \n";

if(Model=="hybrid_phase_field" && energydecomp){
 writeIt
 "                                                                               \n"
 "//----------------------------Hplus macros---------------------------------//  \n"
 "                                                                               \n"
 "  macro DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus){           \n"
 "    real[int] par = [lambda,mu];                                               \n"
 "    Sh0 [Eps1,Eps2,Eps3,Eps12,Eps13,Eps23] =                                   \n"
 "                                                                               \n";

 if(!vectorial && !constrainHPF)
 writeIt
 "                               [ dx(u) ,                                       \n"
 "                                 dy(u1),                                       \n"
 "                                 dz(u2),                                       \n"
 "                                 0.5*(dx(u1)+dy(u)),                           \n"
 "                                 0.5*(dx(u2)+dz(u)),                           \n"
 "                                 0.5*(dy(u2)+dz(u1)) ];                        \n";

 if(!vectorial && constrainHPF)
 writeIt
 "                               [ dx(u) ,                                       \n"
 "                                 dy(u1),                                       \n"
 "                                 dz(u2),                                       \n"
 "                                 0.5*(dx(u1)+dy(u)),                           \n"
 "                                 0.5*(dx(u2)+dz(u)),                           \n"
 "                                 0.5*(dy(u2)+dz(u1)) ];                        \n";

 if(vectorial && !constrainHPF)
 writeIt
 "                              [ dx(uold) ,                                     \n"
 "                                dy(uold1),                                     \n"
 "                                dz(uold2),                                     \n"
 "                                0.5*(dx(uold1)+dy(uold)),                      \n"
 "                                0.5*(dx(uold2)+dz(uold)),                      \n"
 "                                0.5*(dy(uold2)+dz(uold1)) ];                   \n";

 if(vectorial && constrainHPF)
 writeIt
 "                               [ dx(u) ,                                       \n"
 "                                 dy(u1),                                       \n"
 "                                 dz(u2),                                       \n"
 "                                 0.5*(dx(u1)+dy(u)),                           \n"
 "                                 0.5*(dx(u2)+dz(u)),                           \n"
 "                                 0.5*(dy(u2)+dz(u1)) ];                        \n";

 writeIt
 "                                                                               \n"
 "    GFPSplitEnergy(Eps1[],PsiPlus[],PsiMinus[],HistPlus[],HistMinus[],par);    \n"
 "  }//                                                                          \n"
 "                                                                               \n";
 }

 if(Sequential)
  writeIt
  "                                                                               \n"
  "//=============================================================================\n"
  "//      ------- remapping Macros -------                                       \n"
  "// --------------------------------------------------------------------------- \n"
  "// meshN     : Three-dimensional problem mesh                                  \n"
  "// intN      : Three-dimensional integral                                      \n"
  "// intN1     : Two-dimensional integral                                        \n"
  "// grad      : Three-dimensional gradient                                      \n"
  "// readmeshN : Three-dimensional mesh reading .mesh format                     \n"
  "// gmshloadN : Three-dimensional mesh reading .msh format                      \n"
  "//=============================================================================\n"
  "                                                                              \n"
  "  load \"msh3\"                          //                                   \n"
  "  macro meshN()mesh3                     //                                   \n"
  "  macro intN()int3d                      //                                   \n"
  "  macro intN1()int2d                     //                                   \n"
  "  macro readmeshN()readmesh3             //                                   \n"
  "  macro gmshloadN()gmshload3             //                                   \n"
  "  macro grad(i)[dx(i),dy(i),dz(i)]       //                                   \n"
  "                                                                              \n";

 if(tractionconditions>=1){
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "//      ------- Neumann/Traction boundary condition Macros -------             \n"
 "// --------------------------------------------------------------------------- \n"
 "// NeumannBc'I' : will define the full Neumann boundary condition on border I  \n"
 "//=============================================================================\n";

 for(int i=0; i<tractionconditions; i++)
 writeIt
 "                                                                                                   \n"
 "  IFMACRO(Tbc"<<i<<"Tx) IFMACRO(!Tbc"<<i<<"Ty) IFMACRO(!Tbc"<<i<<"Tz)                              \n"
 "    NewMacro NeumannBc"<<i<<"() (Tbc"<<i<<"Tx)*v  EndMacro                                         \n"
 "  ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                                                \n"
 "                                                                                                   \n"
 "  IFMACRO(!Tbc"<<i<<"Tx) IFMACRO(Tbc"<<i<<"Ty) IFMACRO(!Tbc"<<i<<"Tz)                              \n"
 "    NewMacro NeumannBc"<<i<<"() (Tbc"<<i<<"Ty)*v1  EndMacro                                        \n"
 "  ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                                                \n"
 "                                                                                                   \n"
 "  IFMACRO(!Tbc"<<i<<"Tx) IFMACRO(!Tbc"<<i<<"Ty) IFMACRO(Tbc"<<i<<"Tz)                              \n"
 "    NewMacro NeumannBc"<<i<<"() (Tbc"<<i<<"Tz)*v2  EndMacro                                        \n"
 "  ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                                                \n"
 "                                                                                                   \n"
 "  IFMACRO(Tbc"<<i<<"Tx) IFMACRO(Tbc"<<i<<"Ty) IFMACRO(!Tbc"<<i<<"Tz)                               \n"
 "    NewMacro NeumannBc"<<i<<"() (Tbc"<<i<<"Tx)*v + (Tbc"<<i<<"Ty)*v1  EndMacro                     \n"
 "  ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                                                \n"
 "                                                                                                   \n"
 "  IFMACRO(Tbc"<<i<<"Tx) IFMACRO(!Tbc"<<i<<"Ty) IFMACRO(Tbc"<<i<<"Tz)                               \n"
 "    NewMacro NeumannBc"<<i<<"() (Tbc"<<i<<"Tx)*v + (Tbc"<<i<<"Tz)*v2  EndMacro                     \n"
 "  ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                                                \n"
 "                                                                                                   \n"
 "  IFMACRO(!Tbc"<<i<<"Tx) IFMACRO(Tbc"<<i<<"Ty) IFMACRO(Tbc"<<i<<"Tz)                               \n"
 "    NewMacro NeumannBc"<<i<<"() (Tbc"<<i<<"Ty)*v1 +(Tbc"<<i<<"Tz)*v2  EndMacro                     \n"
 "  ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                                                \n"
 "                                                                                                   \n"
 "  IFMACRO(Tbc"<<i<<"Tx) IFMACRO(Tbc"<<i<<"Ty) IFMACRO(Tbc"<<i<<"Tz)                                \n"
 "    NewMacro NeumannBc"<<i<<"() (Tbc"<<i<<"Tx)*v + (Tbc"<<i<<"Ty)*v1 +(Tbc"<<i<<"Tz)*v2  EndMacro  \n"
 "  ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                                                \n";
 }


 if(dirichletconditions>=1)
 {
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "//         ------- Dirichlet boundary condition macros -------                 \n"
 "// --------------------------------------------------------------------------- \n"
 "// DirichletBc'I' : will define the full Dirichlet boundary condition on       \n"
 "//                  border I                                                   \n"
 "//=============================================================================\n";

 for(int i=0; i<dirichletconditions; i++)
 writeIt
 "                                                                                               \n"
 "  IFMACRO(Dbc"<<i<<"Ux) IFMACRO(!Dbc"<<i<<"Uy) IFMACRO(!Dbc"<<i<<"Uz)                          \n"
 "    NewMacro DirichletBc"<<i<<"() Ux=Dbc"<<i<<"Ux  EndMacro                                    \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n"
 "  IFMACRO(!Dbc"<<i<<"Ux) IFMACRO(Dbc"<<i<<"Uy) IFMACRO(!Dbc"<<i<<"Uz)                          \n"
 "    NewMacro DirichletBc"<<i<<"() Uy=Dbc"<<i<<"Uy  EndMacro                                    \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n"
 "  IFMACRO(!Dbc"<<i<<"Ux) IFMACRO(!Dbc"<<i<<"Uy) IFMACRO(Dbc"<<i<<"Uz)                          \n"
 "    NewMacro DirichletBc"<<i<<"() Uz=Dbc"<<i<<"Uz  EndMacro                                    \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n"
 "  IFMACRO(Dbc"<<i<<"Ux) IFMACRO(Dbc"<<i<<"Uy) IFMACRO(!Dbc"<<i<<"Uz)                           \n"
 "    NewMacro DirichletBc"<<i<<"() Ux=Dbc"<<i<<"Ux,Uy=Dbc"<<i<<"Uy  EndMacro                    \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n"
 "  IFMACRO(Dbc"<<i<<"Ux) IFMACRO(!Dbc"<<i<<"Uy) IFMACRO(Dbc"<<i<<"Uz)                           \n"
 "    NewMacro DirichletBc"<<i<<"() Ux=Dbc"<<i<<"Ux,Uz=Dbc"<<i<<"Uz  EndMacro                    \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n"
 "  IFMACRO(!Dbc"<<i<<"Ux) IFMACRO(Dbc"<<i<<"Uy) IFMACRO(Dbc"<<i<<"Uz)                           \n"
 "    NewMacro DirichletBc"<<i<<"() Uy=Dbc"<<i<<"Uy,Uz=Dbc"<<i<<"Uz  EndMacro                    \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n"
 "  IFMACRO(Dbc"<<i<<"Ux) IFMACRO(Dbc"<<i<<"Uy) IFMACRO(Dbc"<<i<<"Uz)                            \n"
 "    NewMacro DirichletBc"<<i<<"() Ux=Dbc"<<i<<"Ux,Uy=Dbc"<<i<<"Uy,Uz=Dbc"<<i<<"Uz  EndMacro    \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n";
 }


 if(bodyforceconditions>=1)
 {
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "//      ------- volumetric bodyforce  conditions macro -------                 \n"
 "// --------------------------------------------------------------------------- \n"
 "// BodyforceBc'I' : will define the body force boundary condition on region I  \n"
 "//=============================================================================\n";

 for(int i=0; i<bodyforceconditions; i++)
 writeIt
 "                                                                                               \n"
 "  IFMACRO(Fbc"<<i<<"Fx) IFMACRO(!Fbc"<<i<<"Fy) IFMACRO(!Fbc"<<i<<"Fz)                          \n"
 "    NewMacro BodyforceBc"<<i<<"() Fbc"<<i<<"Fx*v  EndMacro                                     \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n"
 "  IFMACRO(!Fbc"<<i<<"Fx) IFMACRO(Fbc"<<i<<"Fy) IFMACRO(!Fbc"<<i<<"Fz)                          \n"
 "    NewMacro BodyforceBc"<<i<<"() Fbc"<<i<<"Fy*v1  EndMacro                                    \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n"
 "  IFMACRO(!Fbc"<<i<<"Fx) IFMACRO(!Fbc"<<i<<"Fy) IFMACRO(Fbc"<<i<<"Fz)                          \n"
 "    NewMacro BodyforceBc"<<i<<"() Fbc"<<i<<"Fz*v2  EndMacro                                    \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n"
 "  IFMACRO(Fbc"<<i<<"Fx) IFMACRO(Fbc"<<i<<"Fy) IFMACRO(!Fbc"<<i<<"Fz)                           \n"
 "    NewMacro BodyforceBc"<<i<<"() Fbc"<<i<<"Fx*v+Fbc"<<i<<"Fy*v1  EndMacro                     \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n"
 "  IFMACRO(Fbc"<<i<<"Fx) IFMACRO(!Fbc"<<i<<"Fy) IFMACRO(Fbc"<<i<<"Fz)                           \n"
 "    NewMacro BodyforceBc"<<i<<"() Fbc"<<i<<"Fx*v+Fbc"<<i<<"Fz*v2  EndMacro                     \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n"
 "  IFMACRO(!Fbc"<<i<<"Fx) IFMACRO(Fbc"<<i<<"Fy) IFMACRO(Fbc"<<i<<"Fz)                           \n"
 "    NewMacro BodyforceBc"<<i<<"() Fbc"<<i<<"Fy*v1+Fbc"<<i<<"Fz*v2  EndMacro                    \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n"
 "  IFMACRO(Fbc"<<i<<"Fx) IFMACRO(Fbc"<<i<<"Fy) IFMACRO(Fbc"<<i<<"Fz)                            \n"
 "    NewMacro BodyforceBc"<<i<<"() Fbc"<<i<<"Fx*v+Fbc"<<i<<"Fy*v1+Fbc"<<i<<"Fz*v2  EndMacro     \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n";
 }


} //-- [if loop terminator] space==3 ended --//



if(dirichletpointconditions<1 && Sequential && pointprobe)
 {
  writeIt
  "                                                                               \n"
  "//=============================================================================\n"
  "//            ------ point probe  Indicies macro  -------                      \n"
  "// -------------------------------------------------------------------         \n"
  "//  GetPointProbeIndicies is a  macro designed to  get the  point probe        \n"
  "//  indicies of the fi nite  element degree  of freedom that correspond        \n"
  "//  to the  point probe indices. The  macro  also  gives information of        \n"
  "//  the ranks holding the point probe points in the distributed mesh.          \n"
  "// -------------------------------------------------------------------         \n"
  "//  Inputs  : PnP                                                              \n"
  "//  Outputs : iProbe                                                           \n"
  "// -------------------------------------------------------------------         \n"
  "//  PnP : is the vector containing the point coordinates of the point          \n"
  "//        probe points.                                                        \n"
  "//  iProbe : is finite element degree of freedom vector of the  point          \n"
  "//        probe points.                                                        \n"
  "//=============================================================================\n";

  if(spc==2)
  writeIt
  "                                                                               \n"
  "  macro GetPointProbeIndicies(                                                 \n"
  "                                PnP,   iProbe                                  \n"
  "                             )                                                 \n"
  "    for (int i = 0; i < Th.nv; i++){                                           \n"
  "     for(int j=0; j < iProbe.n; j++)                                           \n"
  "        if(abs(Th(i).x-PnP(j,0))<.01 && abs(Th(i).y-PnP(j,1))<.01 )            \n"
  "          { iProbe[j]=i*2;  }                                                  \n"
  "     }//                                                                       \n";

  if(spc==3)
  writeIt
  "                                                                               \n"
  "  macro GetPointProbeIndicies(                                                 \n"
  "                                PnP,   iProbe                                  \n"
  "                             )                                                 \n"
  "    for (int i = 0; i < Th.nv; i++){                                           \n"
  "     for(int j=0; j < iProbe.n; j++)                                           \n"
  "        if( abs(Th(i).x-PnP(j,0))<.01 &&                                       \n"
  "            abs(Th(i).y-PnP(j,1))<.01 &&                                       \n"
  "            abs(Th(i).z-PnP(j,2))<.01    )                                     \n"
  "          { iProbe[j]=i*3;  }                                                  \n"
  "     }//                                                                       \n";

 }

if(dirichletpointconditions<1 && !Sequential  && pointprobe)
 {
  writeIt
  "                                                                               \n"
  "//=============================================================================\n"
  "//            ------ point probe  Indicies macro  -------                      \n"
  "// -------------------------------------------------------------------         \n"
  "//  GetPointProbeIndicies is a  macro designed to  get the  point probe        \n"
  "//  indicies of the fi nite  element degree  of freedom that correspond        \n"
  "//  to the  point probe indices. The  macro  also  gives information of        \n"
  "//  the ranks holding the point probe points in the distributed mesh.          \n"
  "// -------------------------------------------------------------------         \n"
  "//  Inputs  : PnP                                                              \n"
  "//  Outputs : iProbe, Prank                                                    \n"
  "// -------------------------------------------------------------------         \n"
  "//  PnP : is the vector containing the point coordinates of the point          \n"
  "//        probe points.                                                        \n"
  "//  iProbe : is finite element degree of freedom vector of the  point          \n"
  "//        probe points.                                                        \n"
  "//  Prank  : is rank of the MPI process that holds the finite element          \n"
  "//           degree of freedom of the  point probe points vector.              \n"
  "//=============================================================================\n";

  if(spc==2)
  writeIt
  "                                                                               \n"
  "  macro GetPointProbeIndicies(                                                 \n"
  "                                PnP,   iProbe, Prank                           \n"
  "                             )                                                 \n"
  "    for (int i = 0; i < Th.nv; i++){                                           \n"
  "     for(int j=0; j < iProbe.n; j++)                                           \n"
  "        if(abs(Th(i).x-PnP(j,0))<.01 && abs(Th(i).y-PnP(j,1))<.01 )            \n"
  "          { iProbe[j]=i*2; Prank[j]=mpirank; }                                 \n"
  "     }//                                                                       \n";


  if(spc==3)
  writeIt
  "                                                                               \n"
  "  macro GetPointProbeIndicies(                                                 \n"
  "                                PnP,   iProbe, Prank                           \n"
  "                             )                                                 \n"
  "    for (int i = 0; i < Th.nv; i++){                                           \n"
  "     for(int j=0; j < iProbe.n; j++)                                           \n"
  "        if( abs(Th(i).x-PnP(j,0))<.01 &&                                       \n"
  "            abs(Th(i).y-PnP(j,1))<.01 &&                                       \n"
  "            abs(Th(i).z-PnP(j,2))<.01    )                                     \n"
  "          { iProbe[j]=i*3; Prank[j]=mpirank; }                                 \n"
  "     }//                                                                       \n";

 }


if(dirichletpointconditions>=1)
 {
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "//                 ------- Point boundary condition macros -------             \n"
 "// --------------------------------------------------------------------------- \n"
 "// PointCoordinates : macro to define point x,y,z coordinates                  \n"
 "// GetPointIndiciesMpiRank : macro to get the finite element space index (PCi) \n"
 "//                         of vector of points PC and the MPIrank (mpirankPCi) \n"
 "//                         that holds the distributed chuck of mesh containing \n"
 "//                         points PC (if parallel calculation).                \n"
 "// ApplyPointBc(I) : will define the full point boundary condition on point I  \n"
 "//=============================================================================\n";

 if(spc==2){

 if(!pointprobe && !Sequential)
  writeIt
  "                                                                              \n"
  "  macro GetPointIndiciesMpiRank(PC, PCi, mpirankPCi)                          \n"
  "   for (int i = 0; i < Th.nv; i++){                                           \n"
  "     for(int j = 0; j < PC.n; j++){                                           \n"
  "       if(Th(i).x==PC(j,0) && Th(i).y==PC(j,1)){                              \n"
  "         PCi[j]=i; mpirankPCi[j]=mpirank;                                     \n"
  "       }                                                                      \n"
  "     }                                                                        \n"
  "   }                                                                          \n"
  "  //                                                                          \n";
 
 if(!pointprobe && Sequential)
  writeIt
 "                                                                              \n"
 "  macro GetPointIndiciesMpiRank(PC, PCi)                                      \n"
 "   for (int i = 0; i < Th.nv; i++){                                           \n"
 "     for(int j = 0; j < PC.n; j++){                                           \n"
 "       if(Th(i).x==PC(j,0) && Th(i).y==PC(j,1)){                              \n"
 "         PCi[j]=i;                                                            \n"
 "       }                                                                      \n"
 "     }                                                                        \n"
 "   }                                                                          \n"
 "  //

 if(pointprobe && !Sequential)
  writeIt
  "                                                                              \n"
  "  macro GetPointIndiciesMpiRank(PC, PCi, mpirankPCi, PnP, iProbe, Prank)      \n"
  "   for (int i = 0; i < Th.nv; i++){                                           \n"
  "     for(int j = 0; j < PC.n; j++){                                           \n"
  "       if(Th(i).x==PC(j,0) && Th(i).y==PC(j,1)){                              \n"
  "         PCi[j]=i; mpirankPCi[j]=mpirank;                                     \n"
  "       }                                                                      \n"
  "     }                                                                        \n"
  "     for(int j=0; j < iProbe.n; j++){                                         \n"
  "        if(abs(Th(i).x-PnP(j,0))<.01 && abs(Th(i).y-PnP(j,1))<.01 ){          \n"
  "           iProbe[j]=i*2; Prank[j]=mpirank;                                   \n"
  "       }                                                                      \n"
  "     }                                                                        \n"
  "   }                                                                          \n"
  "  //                                                                          \n";
     
 if(pointprobe && Sequential)
  writeIt
 "                                                                              \n"
 "  macro GetPointIndiciesMpiRank(PC, PCi, PnP, iProbe)                         \n"
 "   for (int i = 0; i < Th.nv; i++){                                           \n"
 "     for(int j = 0; j < PC.n; j++){                                           \n"
 "       if(Th(i).x==PC(j,0) && Th(i).y==PC(j,1)){                              \n"
 "         PCi[j]=i;                                                            \n"
 "       }                                                                      \n"
 "     }                                                                        \n"
 "     for(int j=0; j < iProbe.n; j++){                                         \n"
 "        if(abs(Th(i).x-PnP(j,0))<.01 && abs(Th(i).y-PnP(j,1))<.01 ){          \n"
 "           iProbe[j]=i*2;                                                     \n"
 "       }                                                                      \n"
 "     }                                                                        \n"
 "   }                                                                          \n"
 "  //                                                                          \n";

 for(int i=0; i<dirichletpointconditions; i++)
 if(!Sequential)
 writeIt
 "                                                                               \n"
 "  IFMACRO(!Pbc"<<i<<"Ux) IFMACRO(!Pbc"<<i<<"Uy)                                \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO                                                      \n"
 "                                                                               \n"
 "    IFMACRO(Pbc"<<i<<"Ux) IFMACRO(!Pbc"<<i<<"Uy)                               \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "         if(mpirank==mpirankPCi["<<i<<"]){                                     \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<",PCi["<<i<<"]*"<<Fdofs<<")=tgv;            \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"]= Pbc"<<i<<"Ux*tgv;}                      \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO                                                      \n"
 "                                                                               \n"
 "    IFMACRO(!Pbc"<<i<<"Ux) IFMACRO(Pbc"<<i<<"Uy)                               \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "         if(mpirank==mpirankPCi["<<i<<"]){                                     \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<"+1 , PCi["<<i<<"]*"<<Fdofs<<"+1)=tgv;      \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"+1]= Pbc"<<i<<"Uy*tgv;}                    \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO                                                      \n"
 "                                                                               \n"
 "    IFMACRO(Pbc"<<i<<"Ux) IFMACRO(Pbc"<<i<<"Uy)                                \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "         if(mpirank==mpirankPCi["<<i<<"]){                                     \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<"  ,PCi["<<i<<"]*"<<Fdofs<<"  )=tgv;        \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"  ] = Pbc"<<i<<"Ux*tgv;                    \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<"+1,PCi["<<i<<"]*"<<Fdofs<<"+1)=tgv;        \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"+1] = Pbc"<<i<<"Uy*tgv; }                  \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO                                                      \n"
 "                                                                               \n";
 
 if(Sequential)
 writeIt
 "                                                                               \n"
 "  IFMACRO(!Pbc"<<i<<"Ux) IFMACRO(!Pbc"<<i<<"Uy)                                \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO                                                      \n"
 "                                                                               \n"
 "    IFMACRO(Pbc"<<i<<"Ux) IFMACRO(!Pbc"<<i<<"Uy)                               \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<",PCi["<<i<<"]*"<<Fdofs<<")=tgv;            \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"]= Pbc"<<i<<"Ux*tgv;                       \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO                                                      \n"
 "                                                                               \n"
 "    IFMACRO(!Pbc"<<i<<"Ux) IFMACRO(Pbc"<<i<<"Uy)                               \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<"+1 , PCi["<<i<<"]*"<<Fdofs<<"+1)=tgv;      \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"+1]= Pbc"<<i<<"Uy*tgv;                     \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO                                                      \n"
 "                                                                               \n"
 "    IFMACRO(Pbc"<<i<<"Ux) IFMACRO(Pbc"<<i<<"Uy)                                \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<"  ,PCi["<<i<<"]*"<<Fdofs<<"  )=tgv;        \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"  ] = Pbc"<<i<<"Ux*tgv;                    \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<"+1,PCi["<<i<<"]*"<<Fdofs<<"+1)=tgv;        \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"+1] = Pbc"<<i<<"Uy*tgv;                    \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO                                                      \n"
 "                                                                               \n";
 ;
 }



 if(spc==3){

 if(!pointprobe)
 writeIt
 "                                                                               \n"
 "  macro GetPointIndiciesMpiRank(PC, PCi, mpirankPCi)                           \n"
 "   for (int i = 0; i < Th.nv; i++){                                            \n"
 "     for(int j = 0; j < PC.n; j++){                                            \n"
 "       if(Th(i).x==PC(j,0) && Th(i).y==PC(j,1) && Th(i).z==PC(j,2)){           \n"
 "         PCi[j]=i; mpirankPCi[j]=mpirank;                                      \n"
 "       }                                                                       \n"
 "     }                                                                         \n"
 "   }                                                                           \n"
 "  //                                                                           \n";

 if(pointprobe)
 writeIt
 "                                                                               \n"
 "  macro GetPointIndiciesMpiRank(PC, PCi, mpirankPCi, PnP, iProbe, Prank)       \n"
 "   for (int i = 0; i < Th.nv; i++){                                            \n"
 "     for(int j = 0; j < PC.n; j++){                                            \n"
 "       if(Th(i).x==PC(j,0) && Th(i).y==PC(j,1) && Th(i).z==PC(j,2)){           \n"
 "         PCi[j]=i; mpirankPCi[j]=mpirank;                                      \n"
 "       }                                                                       \n"
 "     }                                                                         \n"
 "     for(int j=0; j < iProbe.n; j++){                                          \n"
 "        if( abs(Th(i).x-PnP(j,0))<.01 &&                                       \n"
 "            abs(Th(i).y-PnP(j,1))<.01 &&                                       \n"
 "            abs(Th(i).z-PnP(j,2))<.01    ){                                    \n"
 "           iProbe[j]=i*3; Prank[j]=mpirank;                                    \n"
 "       }                                                                       \n"
 "     }                                                                         \n"
 "   }                                                                           \n"
 "  //                                                                           \n";

 for(int i=0; i<dirichletpointconditions; i++)
 writeIt
 "                                                                               \n"
 "  IFMACRO(!Pbc"<<i<<"Ux) IFMACRO(!Pbc"<<i<<"Uy) IFMACRO(!Pbc"<<i<<"Uz)         \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                          \n"
 "                                                                               \n"
 "    IFMACRO(Pbc"<<i<<"Ux) IFMACRO(!Pbc"<<i<<"Uy) IFMACRO(!Pbc"<<i<<"Uz)        \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "         if(mpirank==mpirankPCi["<<i<<"]){                                     \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<",PCi["<<i<<"]*"<<Fdofs<<")=tgv;            \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"]= Pbc"<<i<<"Ux*tgv;}                      \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                          \n"
 "                                                                               \n"
 "    IFMACRO(!Pbc"<<i<<"Ux) IFMACRO(Pbc"<<i<<"Uy) IFMACRO(!Pbc"<<i<<"Uz)        \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "         if(mpirank==mpirankPCi["<<i<<"]){                                     \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<"+1 , PCi["<<i<<"]*"<<Fdofs<<"+1)=tgv;      \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"+1]= Pbc"<<i<<"Uy*tgv;}                    \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                          \n"
 "                                                                               \n"
 "    IFMACRO(!Pbc"<<i<<"Ux) IFMACRO(!Pbc"<<i<<"Uy) IFMACRO(Pbc"<<i<<"Uz)        \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "         if(mpirank==mpirankPCi["<<i<<"]){                                     \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<"+2 , PCi["<<i<<"]*"<<Fdofs<<"+2)=tgv;      \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"+2]= Pbc"<<i<<"Uz*tgv;}                    \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                          \n"
 "                                                                               \n"
 "    IFMACRO(Pbc"<<i<<"Ux) IFMACRO(Pbc"<<i<<"Uy) IFMACRO(!Pbc"<<i<<"Uz)         \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "         if(mpirank==mpirankPCi["<<i<<"]){                                     \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<",PCi["<<i<<"]*"<<Fdofs<<")=tgv;            \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"]= Pbc"<<i<<"Ux*tgv;                       \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<"+1 , PCi["<<i<<"]*"<<Fdofs<<"+1)=tgv;      \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"+1]= Pbc"<<i<<"Uy*tgv;}                    \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                          \n"
 "                                                                               \n"
 "    IFMACRO(Pbc"<<i<<"Ux) IFMACRO(!Pbc"<<i<<"Uy) IFMACRO(Pbc"<<i<<"Uz)         \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "         if(mpirank==mpirankPCi["<<i<<"]){                                     \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<",PCi["<<i<<"]*"<<Fdofs<<")=tgv;            \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"]= Pbc"<<i<<"Ux*tgv;                       \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<"+2 , PCi["<<i<<"]*"<<Fdofs<<"+2)=tgv;      \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"+2]= Pbc"<<i<<"Uz*tgv;}                    \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                          \n"
 "                                                                               \n"
 "    IFMACRO(!Pbc"<<i<<"Ux) IFMACRO(Pbc"<<i<<"Uy) IFMACRO(Pbc"<<i<<"Uz)         \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "         if(mpirank==mpirankPCi["<<i<<"]){                                     \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<"+1 , PCi["<<i<<"]*"<<Fdofs<<"+1)=tgv;      \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"+1]= Pbc"<<i<<"Uy*tgv;                     \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<"+2 , PCi["<<i<<"]*"<<Fdofs<<"+2)=tgv;      \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"+2]= Pbc"<<i<<"Uz*tgv;}                    \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                          \n"
 "                                                                               \n"
 "    IFMACRO(Pbc"<<i<<"Ux) IFMACRO(Pbc"<<i<<"Uy) IFMACRO(Pbc"<<i<<"Uz)          \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "         if(mpirank==mpirankPCi["<<i<<"]){                                     \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<"  ,PCi["<<i<<"]*"<<Fdofs<<"  )=tgv;        \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"  ] = Pbc"<<i<<"Ux*tgv;                    \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<"+1,PCi["<<i<<"]*"<<Fdofs<<"+1)=tgv;        \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"+1] = Pbc"<<i<<"Uy*tgv;                    \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<"+2,PCi["<<i<<"]*"<<Fdofs<<"+2)=tgv;        \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"+2] = Pbc"<<i<<"Uz*tgv; }                  \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                          \n"
 "                                                                               \n";
  }

} //-- [if loop terminator] pointbc ended --//
     




if(timelog){
  writeIt
  "                                                                           \n"
  "//-----------------------------------Timing macros-----------------------//\n"
  "                                                                           \n";

 if(!Sequential)
  writeIt
  "                                                                           \n"
  "  macro timerbegin(str1,t0){                                               \n"
  "    mpiBarrier(mpiCommWorld);                                              \n"
  "    t0 = mpiWtime();                                                       \n"
  "    if(mpirank==0)                                                         \n"
  "    cout << \"-->\"+str1+\" began....\\n\";                                \n"
  "  }//                                                                      \n"
  "                                                                           \n"
  "  macro timerend(str1,t0){                                                 \n"
  "    mpiBarrier(mpiCommWorld);                                              \n"
  "    if(mpirank==0)                                                         \n"
  "    cout.scientific << \"finished in [ \"<< mpiWtime()-t0                  \n"
  "      << \" ] seconds\\n\\n\";                                             \n"
  "  }//                                                                      \n"
  "                                                                           \n"
  "                                                                           \n";

 if(Sequential)
  writeIt
  "                                                                           \n"
  "  macro timerbegin(str1,t0){                                               \n"
  "    t0 = clock();                                                          \n"
  "    cout << \"-->\"+str1+\" began....\\n\";                                \n"
  "  }//                                                                      \n"
  "                                                                           \n"
  "  macro timerend(str1,t0){                                                 \n"
  "    cout.scientific << \"finished in [ \"<< clock()-t0                     \n"
  "      << \" ] seconds\\n\\n\";                                             \n"
  "  }//                                                                      \n"
  "                                                                           \n"
  "                                                                           \n";

} //-- [if loop terminator] timelog ended --//

