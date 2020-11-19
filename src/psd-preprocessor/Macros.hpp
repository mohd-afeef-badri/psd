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

cout << " building Macros.edp";

{ofstream  write("Macros.edp");

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
 if(vectorial)if(Prblm=="damage" && Model=="hybrid-phase-field")
 if(ParaViewPostProcess || debug)writeIt
 "// Pltk        : paraview post-processing macro on P1 function possible        \n"
 "// def0(i)     : macro needed post-processing via paraview                     \n";
 if(Prblm=="damage" && Model=="hybrid-phase-field" && energydecomp)
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

 if(Prblm=="elastodynamics")
 writeIt
 "  macro Ux du  //                                                              \n"
 "  macro Uy du1 //                                                              \n";

 if(Prblm=="linear-elasticity" || Prblm=="damage")
 writeIt
 "  macro Ux u  //                                                                \n"
 "  macro Uy u1 //                                                                \n";   
    
 if(Prblm=="damage" && Model=="hybrid-phase-field")
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
 
 if(Prblm=="damage" && Model=="hybrid-phase-field")
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
  
 if(vectorial && Prblm=="damage" && Model=="hybrid-phase-field")
 if(ParaViewPostProcess || debug)
 writeIt
 "  macro Pltk    P1 //                                                           \n"
 "  macro def0(i) i  //                                                           \n";

 if(Prblm=="damage" && Model=="hybrid-phase-field" && energydecomp)
 writeIt
 "  macro Sk [ P0 ,                                                               \n"
 "             P0 ,                                                               \n"
 "             P0 ] //                                                            \n"
 "                                                                                \n"
 "                                                                                \n";  
 
 if(Prblm=="soildynamics" && Model=="Hujeux")
 writeIt
 "                                                                                \n"
 "  macro Sk [ FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ] // Quadrature element space order 3                        \n"
 "                                                                                \n" 
 "  macro defSh(i) [ i   ,                                                        \n"
 "                   i#1 ,                                                        \n"
 "                   i#2 ] // 3rd order Vect. field definition                    \n"
 "                                                                                \n"
 "  macro Ik [ FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ] // Quadrature element space order 25                       \n"
 "                                                                                \n" 
 "  macro defIh(i) [ i    ,                                                       \n"
 "                   i#1  ,                                                       \n"
 "                   i#2  ,                                                       \n"
 "                   i#3  ,                                                       \n"
 "                   i#4  ,                                                       \n"
 "                   i#5  ,                                                       \n"
 "                   i#6  ,                                                       \n"
 "                   i#7  ,                                                       \n"
 "                   i#8  ,                                                       \n"
 "                   i#9  ,                                                       \n"
 "                   i#10 ,                                                       \n"
 "                   i#11 ,                                                       \n"
 "                   i#12 ,                                                       \n"
 "                   i#13 ,                                                       \n"
 "                   i#14 ,                                                       \n"
 "                   i#15 ,                                                       \n"
 "                   i#16 ,                                                       \n"
 "                   i#17 ,                                                       \n"
 "                   i#18 ,                                                       \n"
 "                   i#19 ,                                                       \n"
 "                   i#20 ,                                                       \n"
 "                   i#21 ,                                                       \n"
 "                   i#22 ,                                                       \n"
 "                   i#23 ,                                                       \n"
 "                   i#24 ] // 25th order Vect. field definition                  \n"
 "                                                                                \n"
 "  macro calculateStress(i,j,lambdaVal,muVal)                                    \n"
 "     defSh(i) = [ lambdaVal*(dx(j)+dy(j#1))+2.*muVal*dx(j)   ,                  \n"
 "                  lambdaVal*(dx(j)+dy(j#1))+2.*muVal*dy(j#1) ,                  \n"
 "                  2.*muVal*(dx(j#1)+dy(j))                   ]; //              \n"
 "                                                                                \n"
 "  macro calculateStrain(i,j)                                                    \n"
 "     defSh(i) = [ dx(j)               ,                                         \n"
 "                  dy(j#1)             ,                                         \n"
 "                  0.5*(dx(j#1)+dy(j)) ];  //                                    \n"
 "                                                                                \n"
 "  macro Epsl(i) [ dx(i)              ,                                          \n"
 "                  dy(i#1)            ,                                          \n"
 "                  (dy(i)+dx(i#1))/2. ]   // Strain definition                   \n"
 "                                                                                \n";

 if(useGFP && Prblm=="damage" && Model=="Mazar")
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

  if(Prblm!="damage")
  writeIt
  "  macro def(i) [ i   ,                                                         \n"
  "                 i#1 ] //                                                      \n"
  "                                                                               \n";  

  if(!Sequential && Prblm!="damage")
  writeIt
  "  macro init(i) [ i ,                                                          \n"
  "                  i ] //                                                       \n"
  "                                                                               \n";

  if(Prblm=="damage" && Model=="Mazar")
  writeIt
  "  macro def(i) [ i   ,                                                         \n"
  "                 i#1 ] //                                                      \n"
  "                                                                               \n";  

  if(!Sequential  && Prblm=="damage" && Model=="Mazar")
  writeIt
  "  macro init(i) [ i ,                                                          \n"
  "                  i ] //                                                       \n"
  "                                                                               \n";
  }   //-- [if loop terminator] !vectorial ended --//


 if(Prblm=="damage" && Model=="hybrid-phase-field") 
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
 
 if(Prblm=="damage" && Model=="hybrid-phase-field") 
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



 if(Prblm=="damage" && Model=="hybrid-phase-field" && !energydecomp)
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

/************************OLD METHOD*************************************************
if(Prblm=="damage" && Model=="hybrid-phase-field" && energydecomp)write
<<"                                                                           \n"
<<"//------------------------------Hplus macros-------------------------------\n"
<<"  macro DecomposeElasticEnergy(Hplus,Hminus,H){                            \n"
<<"    fespace WWh0(Th,P0);                                                   \n"
<<"    WWh0 e1,e2,e3,ud;                                                      \n"
<<(!vectorial ? "    e1=dx(u); e2=dy(u1);\n"        : ""                      )
<<(vectorial  ? "    e1=dx(uold); e2=dy(uold1);\n"  : ""                      )
<<"    e1=dx(u); e2=dy(u1);                                                   \n"
<<"    ud[] = e1[] + e2[];                                                    \n"
<<"    e3 = max(0.,ud);                                                       \n"
<<"    Hplus = 0.5*lambda*(e3*e3);                                            \n"
<<"    e3 = min(0.,ud);                                                       \n"
<<"    Hminus = 0.5*lambda*(e3*e3);                                           \n"
<<(!vectorial ? "    e3=0.5*(dx(u1)+dy(u));\n"        : ""                    )
<<(vectorial  ? "    e3=0.5*(dx(uold1)+dy(uold));\n"  : ""                    )
<<"    real[int] eval(2),eval1(2);                                            \n"
<<"    real[int,int] A(2,2);                                                  \n"
<<"    for(int i=0; i< Wh0.ndof; i++){                                        \n"
<<"      A(0,0)= e1[][i];                                                     \n"
<<"      A(0,1)= e3[][i];                                                     \n"
<<"      A(1,1)= e2[][i];                                                     \n"
<<"      GFPeigenAlone (A, eval);                                             \n"
<<"      eval1[0]=max(0.,eval[0]);                                            \n"
<<"      eval1[1]=max(0.,eval[1]);                                            \n"
<<"      eval[0]=min(0.,eval[0]);                                             \n"
<<"      eval[1]=min(0.,eval[1]);                                             \n"
<<"      Hplus[][i] +=mu*(eval1[0]*eval1[0] + eval1[1]*eval1[1]);             \n"
<<"      Hminus[][i]+=mu*(eval[0]*eval[0] + eval[1]*eval[1]);                 \n"
<<"    }                                                                      \n"
<<"    GFPmaxintwoFEfields(H[],Hplus[]);                                      \n"
<<"  }//                                                                      \n"
/************************OLD METHOD*************************************************/

/************************OLD METHOD*************************************************
if(Prblm=="damage" && Model=="hybrid-phase-field" && energydecomp)write
<<"                                                                           \n"
<<"//------------------------------Hplus macros----------------------------------//\n"
<<"                                                                           \n"
<<"  macro DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus){       \n"
<<"    fespace WWh0(Th,P0);                                                   \n"
<<"    WWh0 e1,e2,e3;                                                         \n"
<<(vectorial  ? "    e1=dx(uold); e2=dy(uold1);\n"    : ""                    )
<<(vectorial  ? "    e3=0.5*(dx(uold1)+dy(uold));\n"  : ""                    )
<<(!vectorial ? "    e1=dx(u); e2=dy(u1);\n"          : ""                    )
<<(!vectorial ? "    e3=0.5*(dx(u1)+dy(u));\n"        : ""                    )
<<"                                                                           \n"
<<"    GFPDecompEnergy2D(e1[],e2[],e3[],PsiPlus[],PsiMinus[],HistPlus[],HistMinus[],lambda,mu);           \n"
<<"  }//                                                                      \n"
<<"                                                                           \n";
/************************OLD METHOD*************************************************/

 if(Prblm=="damage" && Model=="hybrid-phase-field" && energydecomp){
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

 if(Prblm=="damage" && Model=="Mazar")
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
 if(vectorial)if(Prblm=="damage" && Model=="hybrid-phase-field")
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

 if(Prblm=="elastodynamics")
 writeIt
 "  macro Ux   du  //                                                            \n"
 "  macro Uy   du1 //                                                            \n"
 "  macro Uz   du2 //                                                            \n";

 if(Prblm=="linear-elasticity" || Prblm=="damage")
 writeIt
 "  macro Ux    u  //                                                            \n"
 "  macro Uy    u1 //                                                            \n"
 "  macro Uz    u2 //                                                            \n";

 if(Prblm=="damage" && Model=="hybrid-phase-field")
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


 if(Prblm=="damage" && Model=="hybrid-phase-field")
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
 
 if(vectorial)if(Prblm=="damage" && Model=="hybrid-phase-field")
 if(ParaViewPostProcess || debug)
  writeIt
  "  macro Pltk      P1  //                                                      \n"
  "  macro def0 (i)  i   //                                                      \n";

 if(Prblm=="soildynamics" && top2vol)
 writeIt
 "  macro DummyMesh() cube(1,1,1);       // Dummy mesh macro                     \n";
 
 if(Prblm=="damage" && Model=="hybrid-phase-field" && energydecomp)
  writeIt
  "  macro Sk [ P0 ,                                                             \n"
  "             P0 ,                                                             \n"
  "             P0 ,                                                             \n"
  "             P0 ,                                                             \n"
  "             P0 ,                                                             \n"
  "             P0 ] // Sixth order strain vector                                \n"
  "                                                                              \n";  

 if(Prblm=="damage" && Model=="Mazar")if(useGFP)
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

if(Prblm!="damage")
  writeIt
  "  macro def(i)  [i   ,                                                        \n"
  "                 i#1 ,                                                        \n"
  "                 i#2 ] //                                                     \n"
  "                                                                              \n";    

if(Prblm!="damage" && !Sequential)
  writeIt
  "  macro init(i) [ i ,                                                         \n"
  "                  i ,                                                         \n"
  "                  i ] //                                                      \n"
  "                                                                              \n";

if(Prblm=="damage" && Model=="Mazar")
  writeIt
  "  macro def(i)  [ i  ,                                                        \n"
  "                  i#1,                                                        \n"
  "                  i#2] //                                                     \n"
  "                                                                              \n";  

if(Prblm=="damage" && Model=="Mazar"  && !Sequential)
  writeIt
  "  macro init(i) [ i ,                                                         \n"
  "                  i ,                                                         \n"
  "                  i ] //                                                      \n"
  "                                                                              \n";

} //-- [if loop terminator] !vectorial ended --//

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

if(Prblm=="damage" && Model=="hybrid-phase-field" && !vectorial)
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

if(Prblm=="damage" && Model=="hybrid-phase-field")  
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
  "                                                                              \n"
  "  macro def2  (i)  [   i  ,  i#1 ,  i#2  ]  //                                \n"
  "  macro init2 (i)  [   i  ,   i  ,   i   ]  //                                \n"
  "  macro def   (i)     i                     //                                \n"
  "  macro init  (i)     i                     //                                \n"
  "  macro Zk            P1                    //                                \n";   


if(Prblm=="damage" && Model=="hybrid-phase-field" && !energydecomp)
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

if(Prblm=="damage" && Model=="Mazar")
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

/********************************************************************************
if(Prblm=="damage" && Model=="hybrid-phase-field" && energydecomp)write
<<"                                                                           \n"
<<"//------------------------------Hplus macros-----------------------------//\n"
<<"                                                                           \n"
<<"  macro DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus){       \n"
<<"    fespace WWh0(Th,P0);                                                   \n"
<<"    WWh0 e1,e2,e3,e4,e5,e6;                                                \n"
<<"                                                                           \n"
<<"    real[int] par(2);                                                      \n"
<<"    par[0] = lambda ;                                                      \n"
<<"    par[1] = mu     ;                                                      \n"
<<"                                                                           \n"
<<(!vectorial ? "    e1=dx(u); e2=dy(u1); e3=dy(u2);\n"           : ""        )
<<(!vectorial ? "    e4=0.5*(dx(u1)+dy(u));\n"                          : ""  )
<<(!vectorial ? "    e5=0.5*(dz(u)+dx(u2));\n"                    : ""        )
<<(!vectorial ? "    e6=0.5*(dz(u1)+dy(u2));\n"                   : ""        )
<<(vectorial  ? "    e1=dx(uold); e2=dy(uold1); e3=dy(uold2);\n"  : ""        )
<<(vectorial  ? "    e4=0.5*(dx(uold1)+dy(uold));\n"              : ""        )
<<(vectorial  ? "    e5=0.5*(dz(uold)+dx(uold2));\n"              : ""        )
<<(vectorial  ? "    e6=0.5*(dz(uold1)+dy(uold2));\n"             : ""        )
<<"                                                                           \n"
<<"GFPDecompEnergy3D(e1[],e2[],e3[],e4[],e5[],e6[],                           \n"
<<"                  PsiPlus[],PsiMinus[],                                    \n"
<<"                  HistPlus[],HistMinus[],par   );                          \n"
<<"  }//                                                                      \n"
<<"                                                                           \n";
/*******************************************************************************/

if(Prblm=="damage" && Model=="hybrid-phase-field" && energydecomp){
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



if(dirichletpointconditions<1 && Sequential)
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

if(dirichletpointconditions<1 && !Sequential)
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
 "//                         points PC.                                          \n"
 "// ApplyPointBc(I) : will define the full point boundary condition on point I  \n"              
 "//=============================================================================\n";
  
 if(spc==2){
 
 if(!pointprobe)
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

 if(pointprobe)
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
      
 for(int i=0; i<dirichletpointconditions; i++)
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


 if(Prblm=="elastodynamics" || Prblm=="soildynamics")if(!useGFP)
  writeIt
  "                                                                           \n"
  "//------------------------------update macros----------------------------//\n"
  "                                                                           \n"
  "  macro updateVariables(du,uold,vold,aold,beta,gamma,dt){                  \n"
  "                                                                           \n"
  "    real aloc  ;                                                           \n"
  "                                                                           \n"
  "    for (int i=0; i< Vh.ndof; i++){                                        \n"
  "      aloc     =   (du[][i]-uold[][i]-dt*vold[][i])/beta/(dt*dt)           \n"
  "                  - (1.-2.*beta)/2./beta*aold[][i];                        \n"
  "      vold[][i] = vold[][i] + dt*((1.-gamma)*aold[][i] + gamma*aloc);      \n"
  "      aold[][i] = aloc;                                                    \n"
  "      uold[][i] = du[][i]    ;                                             \n"
  "    }                                                                      \n"
  "  }//                                                                      \n"
  "                                                                           \n";


 if(Prblm=="soildynamics")
 {
  writeIt
  "                                                                           \n"
  "//----------------------Paraxial rotation macro--------------------------//\n"
  "                                                                           \n";

 if(spc==2)
  writeIt
  "  macro PA0(i)                                                               \n"
  "        [  cp*(N.x*N.x*i + N.x*N.y*i#1)                                      \n"
  "          +cs*( N.y*N.y*i - N.x*N.y*i#1) ,                                   \n"
  "                                                                             \n"  
  "           cp*(N.x*N.y*i + N.y*N.y*i#1)                                      \n"
  "          +cs*(-N.x*N.y*i + N.x*N.x*i#1) ]//                                 \n"
  "                                                                             \n";


 if(spc==3)
  writeIt
  "  macro PA0(i)                                                               \n"
  "   [  cp*(N.x*N.x*i + N.x*N.y*i#1 + N.x*N.z*i#2)                             \n"
  "     +cs*( (1.-N.x*N.x)*i - N.x*N.y*i#1 - N.x*N.z*i#2)  ,                    \n"
  "                                                                             \n"
  "     cp*(N.x*N.y*i + N.y*N.y*i#1 + N.y*N.z*i#2)                              \n"
  "     +cs*(-N.x*N.y*i + (1.-N.y*N.y)*i#1 - N.y*N.z*i#2)  ,                    \n"
  "                                                                             \n"  
  "     cp*(N.x*N.z*i + N.y*N.z*i#1 + N.z*N.z*i#2)                              \n"
  "     +cs*(-N.x*N.z*i - N.y*N.z*i#1 + (1.-N.z*N.z)*i#2) ]//                   \n"
  "                                                                             \n";

 if(Sequential)
  writeIt
  "                                                                                   \n"
  "//----------------------ParaView plotting macro--------------------------//        \n"
  "                                                                                   \n"
  "  macro exportBegin(name)                                                          \n"
  "    {ofstream pvd(name +\".pvd\");                                                 \n"
  "      pvd << \"<?xml version=\\\"1.0\\\"?>\\n\";                                   \n"
  "      pvd << \"<VTKFile type=\\\"Collection\\\" version=\\\"0.1\\\"\\n\";          \n"
  "      pvd << \"         byte_order=\\\"LittleEndian\\\"\\n\";                      \n"
  "      pvd << \"         compressor=\\\"vtkZLibDataCompressor\\\">\\n\";            \n"
  "      pvd << \"  <Collection>\\n\";                                                \n"
  "    }//                                                                            \n"
  "                                                                                   \n"
  "                                                                                   \n"
  "  macro exportEnd(name)                                                            \n"
  "    {ofstream pvd(name +\".pvd\", append);                                         \n"
  "    pvd << \"  </Collection>\\n\";                                                 \n"
  "    pvd << \"</VTKFile>\\n\";}                                                     \n"
  "    system(\"mv \"+name+\".pvd .\");                                               \n"
  "  //                                                                               \n"
  "                                                                                   \n"
  "                                                                                   \n"
  "  macro exportTimeStep(name, mesh, sol, forder, iterno, ts, nam )                  \n"
  "    savevtk(name+\"_\"+int(iterno)+\".vtu\",mesh,sol,order=forder,dataname=nam);   \n"
  "    ofstream pvd(name +\".pvd\", append);                                          \n"
  "      pvd << \"    <DataSet timestep=\\\"\" + real(ts) + \"\\\"\\n\";              \n"
  "      pvd << \"             file=\\\"\";                                           \n"
  "      pvd << name << \"_\" << int(iterno) << \".vtu\\\"/>\\n\";                    \n"
  "  //                                                                               \n"
  "                                                                                   \n";
  
  if(pointprobe && doublecouple=="unused"){
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
  "//=============================================================================\n"
  "                                                                               \n";

  if(spc==2  && dirichletpointconditions<1)
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


  if(spc==3  && dirichletpointconditions<1)
  writeIt    
  "                                                                               \n"
  "  macro GetPointProbeIndicies(                                                 \n"
  "                                PnP,   iProbe, Prank                           \n" 
  "                               )                                               \n"
  "    for (int i = 0; i < Th.nv; i++){                                           \n"
  "     for(int j=0; j < iProbe.n; j++)                                           \n"
  "        if( abs(Th(i).x-PnP(j,0))<.01 &&                                       \n"
  "            abs(Th(i).y-PnP(j,1))<.01 &&                                       \n"
  "            abs(Th(i).z-PnP(j,2))<.01    )                                     \n"
  "          { iProbe[j]=i*3; Prank[j]=mpirank; }                                 \n"  
  "     }//                                                                       \n";  
  
  
  }  
  

if(doublecouple=="displacement-based" || doublecouple=="force-based"){
  writeIt
  "                                                                               \n"
  "//=============================================================================\n"
  "//            ------ double couple  Indicies macro  -------                    \n"
  "// -------------------------------------------------------------------         \n"
  "//  GetDoubelCoupleIndicies is a  macro designed  to  get  the  double         \n"
  "//  couple finite element degree of freedom so that Dirichlet condition        \n"
  "//  can be applied easily by knowing these   indices. The  macro  also         \n"
  "//  gives information of the ranks holding the double couple points in         \n"
  "//  the distributed mesh.                                                      \n"
  "// -------------------------------------------------------------------         \n"
  "//  Inputs  : PnN, PnS, PnE, PnW                                               \n"
  "//  Outputs : iN, iS, iE, iW,  Nrank, Srank, Erank, Wrank                      \n"
  "// -------------------------------------------------------------------         \n"
  "//  PnN : is the vector containing the point coordinates of the North          \n"
  "//        point of the double couple. Same is true for PnS, PnE, PnW.          \n"
  "//  iN  : is finite element degree of freedom of the Northern  double          \n"
  "//        couple point. Same is true for iS, iE, iW.                           \n"
  "//  Nrank  : is rank of the MPI process that holds the finite element          \n"
  "//           degree of freedom of the  Northern  double couple point.          \n"
  "//           Same is true for Srank, Erank, Wrank.                             \n"
  "//=============================================================================\n"
  "                                                                               \n";
  
  if(spc==2 && !pointprobe)
  writeIt    
  "                                                                               \n"
  "  macro GetDoubelCoupleIndicies(                                               \n"
  "                                PnN,   PnS,   PnE,   PnW,                      \n"
  "                                iN,    iS,    iE,    iW,                       \n"
  "                                Nrank, Srank, Erank, Wrank)                    \n"
  "    for (int i = 0; i < Th.nv; i++){                                           \n"
  "     if(Th(i).x==PnN[0] && Th(i).y==PnN[1])                                    \n"
  "       {iN=i*2; Nrank=mpirank; }                                               \n"
  "     if(Th(i).x==PnS[0] && Th(i).y==PnS[1])                                    \n"
  "       {iS=i*2; Srank=mpirank; }                                               \n"
  "     if(Th(i).x==PnE[0] && Th(i).y==PnE[1])                                    \n"
  "       {iE=i*2+1; Erank=mpirank; }                                             \n"
  "     if(Th(i).x==PnW[0] && Th(i).y==PnW[1])                                    \n"
  "       {iW=i*2+1; Wrank=mpirank; }                                             \n"
  "     }//                                                                       \n";

  if(spc==2 && pointprobe && dirichletpointconditions<1)
  writeIt    
  "                                                                               \n"
  "  macro GetDoubelCoupleIndicies(                                               \n"
  "                                PnN,   PnS,   PnE,   PnW,                      \n"
  "                                iN,    iS,    iE,    iW,                       \n"
  "                                Nrank, Srank, Erank, Wrank,                    \n"
  "                                PnP,   iProbe, Prank                           \n" 
  "                               )                                               \n"   
  "    for (int i = 0; i < Th.nv; i++){                                           \n"
  "     if(Th(i).x==PnN[0] && Th(i).y==PnN[1])                                    \n"
  "       {iN=i*2; Nrank=mpirank; }                                               \n"
  "     if(Th(i).x==PnS[0] && Th(i).y==PnS[1])                                    \n"
  "       {iS=i*2; Srank=mpirank; }                                               \n"
  "     if(Th(i).x==PnE[0] && Th(i).y==PnE[1])                                    \n"
  "       {iE=i*2+1; Erank=mpirank; }                                             \n"
  "     if(Th(i).x==PnW[0] && Th(i).y==PnW[1])                                    \n"
  "       {iW=i*2+1; Wrank=mpirank; }                                             \n"
  "     for(int j=0; j < iProbe.n; j++)                                           \n"
  "        if(abs(Th(i).x-PnP(j,0))<.01 && abs(Th(i).y-PnP(j,1))<.01 )            \n"
  "          { iProbe[j]=i*2; Prank[j]=mpirank; }                                 \n"
  "     }//                                                                       \n";

  
  if(spc==3  && !pointprobe)
  writeIt    
  "                                                                               \n"
  "  macro GetDoubelCoupleIndicies(                                               \n"
  "                                PnN,   PnS,   PnE,   PnW,                      \n"
  "                                iN,    iS,    iE,    iW,                       \n"
  "                                Nrank, Srank, Erank, Wrank)                    \n"
  "    for (int i = 0; i < Th.nv; i++){                                           \n"
  "     if(Th(i).x==PnN[0] && Th(i).y==PnN[1] && abs(Th(i).z-PnN[2])<.01)         \n"
  "       {iN=i*3; Nrank=mpirank;}                                                \n"
  "     if(Th(i).x==PnS[0] && Th(i).y==PnS[1] && abs(Th(i).z-PnS[2])<.01)         \n"
  "       {iS=i*3; Srank=mpirank;}                                                \n"
  "     if(Th(i).x==PnE[0] && Th(i).y==PnE[1] && abs(Th(i).z-PnE[2])<.01)         \n"
  "       {iE=i*3+2; Erank=mpirank;}                                              \n"
  "     if(Th(i).x==PnW[0] && Th(i).y==PnW[1] && abs(Th(i).z-PnW[2])<.01)         \n"
  "       {iW=i*3+2; Wrank=mpirank;}                                              \n"
  "     }//                                                                       \n";

  if(spc==3  && pointprobe && dirichletpointconditions<1)
  writeIt    
  "                                                                               \n"
  "  macro GetDoubelCoupleIndicies(                                               \n"
  "                                PnN,   PnS,   PnE,   PnW,                      \n"
  "                                iN,    iS,    iE,    iW,                       \n"
  "                                Nrank, Srank, Erank, Wrank,                    \n"
  "                                PnP,   iProbe, Prank                           \n" 
  "                               )                                               \n"
  "    for (int i = 0; i < Th.nv; i++){                                           \n"
  "     if(Th(i).x==PnN[0] && Th(i).y==PnN[1] && abs(Th(i).z-PnN[2])<.01)         \n"
  "       {iN=i*3; Nrank=mpirank;}                                                \n"
  "     if(Th(i).x==PnS[0] && Th(i).y==PnS[1] && abs(Th(i).z-PnS[2])<.01)         \n"
  "       {iS=i*3; Srank=mpirank;}                                                \n"
  "     if(Th(i).x==PnE[0] && Th(i).y==PnE[1] && abs(Th(i).z-PnE[2])<.01)         \n"
  "       {iE=i*3+2; Erank=mpirank;}                                              \n"
  "     if(Th(i).x==PnW[0] && Th(i).y==PnW[1] && abs(Th(i).z-PnW[2])<.01)         \n"
  "       {iW=i*3+2; Wrank=mpirank;}                                              \n"
  "     for(int j=0; j < iProbe.n; j++)                                           \n"
  "        if( abs(Th(i).x-PnP(j,0))<.01 &&                                       \n"
  "            abs(Th(i).y-PnP(j,1))<.01 &&                                       \n"
  "            abs(Th(i).z-PnP(j,2))<.01    )                                     \n"
  "          { iProbe[j]=i*3; Prank[j]=mpirank; }                                 \n"  
  "     }//                                                                       \n";

if(doublecouple=="displacement-based")
  writeIt
  "                                                                               \n"
  "//=============================================================================\n"
  "//  ------ double couple Stiffness matrix penalization macro  -------          \n"
  "// -------------------------------------------------------------------         \n"
  "//  ApplyDoubleCoupleToA is a macro  designed  to  apply  the  double          \n"
  "//  couple Dirichlet boundary condition via penalization. This can be          \n"
  "//  applied easily by knowing the  finite element  degree of  freedom          \n"
  "//  that corresponds to these  indices, and the MPI rank that  holds           \n"
  "//  these degrees of freedom.                                                  \n"
  "// -------------------------------------------------------------------         \n"
  "//  A : is the stiffness matrix assembled from bilinear.                       \n"
  "//  iN  : is finite element degree of freedom of the Northern  double          \n"
  "//        couple point. Same is true for iS, iE, iW.                           \n"
  "//  Nrank  : is rank of the MPI process that holds the finite element          \n"
  "//           degree of freedom of the  Northern  double couple point.          \n"
  "//           Same is true for Srank, Erank, Wrank.                             \n"
  "//  tgv  : is the large penalization term tgv=1e30.                            \n"
  "//=============================================================================\n"
  "                                                                               \n"
  "  macro ApplyDoubleCoupleToA(A,iN,iS,iE,iW,Nrank,Srank,Erank,Wrank)            \n"
  "     if(mpirank==Nrank)                                                        \n"
  "       A(iN,iN)= tgv;                                                          \n"
  "     if(mpirank==Srank)                                                        \n"
  "       A(iS,iS)= tgv;                                                          \n"
  "     if(mpirank==Erank)                                                        \n"
  "       A(iE,iE)= tgv;                                                          \n"
  "     if(mpirank==Wrank)                                                        \n"
  "       A(iW,iW)= tgv;                                                          \n"
  "  //                                                                           \n"
  "                                                                               \n"
  "//=============================================================================\n"
  "//       ------ double couple RHS  macro  -------                              \n"
  "// -------------------------------------------------------------------         \n"
  "//  ApplyDoubleCoupleToRHS is a macro designed to  apply  the  double          \n"
  "//  couple Dirichlet boundary condition via penalization. This can be          \n"
  "//  applied easily by knowing the  finite element  degree of  freedom          \n"
  "//  that corresponds to these  indices, and the MPI rank that  holds           \n"
  "//  these degrees of freedom.                                                  \n"
  "// -------------------------------------------------------------------         \n"
  "//  RHS : is the right hand side vector  assembled from linear.                \n"
  "//  CondN  : is boundary condition displacement applied to the norther         \n"
  "//           point of the double couple. Same is true for Conds, CondW,        \n"
  "//           and CondE.                                                        \n"
  "//  iN  : is finite element degree of freedom of the Northern  double          \n"
  "//        couple point. Same is true for iS, iE, iW.                           \n"
  "//  Nrank  : is rank of the MPI process that holds the finite element          \n"
  "//           degree of freedom of the  Northern  double couple point.          \n"
  "//           Same is true for Srank, Erank, Wrank.                             \n"
  "//  tgv  : is the large penalization term tgv=1e30.                            \n"
  "//=============================================================================\n"
  "                                                                               \n"
  "  macro ApplyDoubleCoupleToRHS( RHS,                                           \n"
  "                                CondN,CondS,CondE,CondW,                       \n"
  "                                iN,   iS,   iE,   iW,                          \n"
  "                                Nrank,Srank,Erank,Wrank)                       \n"
  "     if(mpirank==Nrank)                                                        \n"
  "       RHS[iN]= CondN*tgv;                                                     \n"
  "     if(mpirank==Srank)                                                        \n"
  "       RHS[iS]= CondS*tgv;                                                     \n"
  "     if(mpirank==Erank)                                                        \n"
  "       RHS[iE]= CondE*tgv;                                                     \n"
  "     if(mpirank==Wrank)                                                        \n"
  "       RHS[iW]= CondW*tgv;                                                     \n"
  "  //                                                                           \n"
  "                                                                               \n";

if(doublecouple=="force-based")
  writeIt
  "                                                                               \n"
  "//=============================================================================\n"
  "//       ------ double couple RHS force macro  -------                         \n"
  "// -------------------------------------------------------------------         \n"
  "//  ApplyDoubleCoupleToRHS is a macro designed to  apply  the  double          \n"
  "//  couple Dirichlet boundary condition. This  can be  applied easily          \n"
  "//  by knowing the finite element degree of  freedom that corresponds          \n"
  "//  to these  indices, and the MPI rank that  holds these degrees of           \n"
  "//  freedom.                                                                   \n"
  "// -------------------------------------------------------------------         \n"
  "//  RHS : is the right hand side vector  assembled from linear.                \n"
  "//  CondN  : is boundary condition force applied to the norther point          \n"
  "//           of the double couple. Same is true for Conds, CondW, and          \n"
  "//           CondE.                                                            \n"
  "//  iN  : is finite element degree of freedom of the Northern  double          \n"
  "//        couple point. Same is true for iS, iE, iW.                           \n"
  "//  Nrank  : is rank of the MPI process that holds the finite element          \n"
  "//           degree of freedom of the  Northern  double couple point.          \n"
  "//           Same is true for Srank, Erank, Wrank.                             \n"
  "//=============================================================================\n"
  "                                                                               \n"
  "  macro ApplyDoubleCoupleToRHS( RHS,                                           \n"
  "                                CondN,CondS,CondE,CondW,                       \n"
  "                                iN,   iS,   iE,   iW,                          \n"
  "                                Nrank,Srank,Erank,Wrank)                       \n"
  "     if(mpirank==Nrank)                                                        \n"
  "       RHS[iN]= CondN;                                                         \n"
  "     if(mpirank==Srank)                                                        \n"
  "       RHS[iS]= CondS;                                                         \n"
  "     if(mpirank==Erank)                                                        \n"
  "       RHS[iE]= CondE;                                                         \n"
  "     if(mpirank==Wrank)                                                        \n"
  "       RHS[iW]= CondW;                                                         \n"
  "  //                                                                           \n"
  "                                                                               \n";
}  // if(doublecouple=="displacement-based" || doublecouple=="force-based") ENDED

}

} //-- [ostream terminator]  macros.edp closed --//

cout << " ................................... Done \n";

