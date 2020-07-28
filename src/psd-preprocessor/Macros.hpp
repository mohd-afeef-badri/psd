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

writeIt
"                                                                               \n"
"//=============================================================================\n"
"// ------- Essential Macros -------                                            \n"
"//=============================================================================\n";

if(spc==2)
 {
 writeIt
 "                                                                              \n";

 if(!Sequential)
 writeIt
 "  macro partitioner "<<Partitioner<<"\t\t        // Mesh partitioner used    \n"
 "  macro dimension 2                              // Two-dimensional problem  \n";

 if(Prblm=="elastodynamics")
 writeIt
 "  macro Ux   du                                  // x displacement           \n"
 "  macro Uy   du1                                 // y displacement           \n";

 if(Prblm=="linear-elasticity" || Prblm=="damage")
 writeIt
 "  macro Ux    u                                  // x displacement           \n"
 "  macro Uy    u1                                 // y displacement           \n";

 if(vectorial && Prblm=="damage" && Model=="hybrid-phase-field")
 writeIt
 "  macro Pk       [ P"<<lag<<", P"<<lag<<" , P"<<lag<<"  ]\t\t// FE space     \n"
 "  macro def  (i) [ i , i#1, i#2 ]                // Vect. field definition   \n"
 "  macro init (i) [ i ,  i ,  i  ]                // Vect. field initialize   \n";

 if(vectorial && Prblm=="damage" && Model=="hybrid-phase-field")
 if(plotAll || debug)
 writeIt
 "  macro Pltk         P1                          // FE space                 \n"
 "  macro def0 (i)           i                     // Vect. field definition   \n";

 if(Prblm=="damage" && Model=="hybrid-phase-field" && energydecomp)
 writeIt
 "  macro Sk       [ P0, P0 , P0  ]       // Third order strain vector         \n";

 if(Prblm=="soildynamics" && Model=="Hujeux")
 writeIt
 "                                                                              \n"
 "  macro Sk [ FEQF1, FEQF1 , FEQF1 ]       // Quadrature element space order 3 \n"
 "  macro defSh (i) [ i , i#1, i#2 ]        // 3rd order Vect. field definition \n"
 "                                                                              \n"
 "  macro Ik [FEQF1,FEQF1,FEQF1,FEQF1,FEQF1,FEQF1,FEQF1,FEQF1,FEQF1,FEQF1,      \n"
 "            FEQF1,FEQF1,FEQF1,FEQF1,FEQF1,FEQF1,FEQF1,FEQF1,FEQF1,FEQF1,      \n"
 "            FEQF1,FEQF1,FEQF1,FEQF1,FEQF1]// Quadrature element space order 25\n"
 "  macro defIh (i) [ i,        i#1,i#2,i#3,i#4,i#5,i#6,i#7,i#8,i#9,i#10,       \n"
 "                     i#11,i#12,i#13,i#14,i#15,i#16,i#17,i#18,i#19,i#20,       \n"
 "                     i#21,i#22,i#23,i#24]// 25th order Vect. field definition \n"
 "                                                                              \n"
 "                                                                              \n"
 "  macro calculateStress(i,j,lambdaVal,muVal)                                  \n"
 "     defSh (i) = [ lambdaVal*(dx(j)+dy(j#1))+2.*muVal*dx(j),                  \n"
 "                   lambdaVal*(dx(j)+dy(j#1))+2.*muVal*dy(j#1) ,               \n"
 "                   2.*muVal*(dx(j#1)+dy(j))];                                 \n"
 "     //                                                                       \n"
 "                                                                              \n"
 "  macro calculateStrain(i,j){                                                 \n"
 "     defSh (i) = [ dx(j), dy(j#1), 0.5*(dx(j#1)+dy(j))];                      \n"
 "     }//                                                                      \n"
 "                                                                              \n"
 "  macro Epsl(i) [dx(i), dy(i#1), (dy(i)+dx(i#1))/2.]   // Strain definition   \n"
 "                                                                              \n";

 if(useGFP && Prblm=="damage" && Model=="Mazar")
 writeIt
 "  macro Sk           [ P0, P0 , P0  ]       // Third order strain vector     \n"
 "  macro defStrain(i) [ i , i#1, i#2 ]       // Vect. field definition        \n";

 if(!vectorial)
  {
  writeIt
  "  macro Pk       [ P"<<lag<<", P"<<lag<<"  ]\t\t    // Finite element space  \n";

  if(Prblm!="damage")
  writeIt
  "  macro def  (i) [ i , i#1 ]                // Vect. field definition       \n";

  if(!Sequential && Prblm!="damage")
  writeIt
  "  macro init (i) [ i ,  i  ]                // Vect. field initialize       \n"
  "                                                                            \n";

  if(Prblm=="damage" && Model=="Mazar")
  writeIt
  "  macro def  (i) [ i , i#1 ]                // Vect. field definition       \n";

  if(!Sequential  && Prblm=="damage" && Model=="Mazar")
  writeIt
  "  macro init (i) [ i ,  i  ]                // Vect. field initialize       \n"
  "                                                                            \n";
  }   //-- [if loop terminator] !vectorial ended --//

 writeIt
 "                                                                              \n"
 "//--------------------Divergence and epsilion macros---------------------//   \n"
 "                                                                              \n"
 "  macro divergence(i)(dx(i) + dy(i#1))          // Divergence function        \n"
 "  macro epsilon(i) [dx(i), dy(i#1),                                           \n"
 "                   (dy(i)+dx(i#1))/SQ2]        // Strain definition           \n";

 if(!vectorial && Prblm=="damage" && Model=="hybrid-phase-field")
 writeIt
 "                                                                              \n"
 "//---------------------------Non-linear macros---------------------------//   \n"
 "                                                                              \n"
 "  macro def2  (i) [ i , i#1 ]                         // Vect. field          \n"
 "  macro init2 (i) [ i ,  i  ]                         // Vect. initialize     \n"
 "  macro def   (i)     i                               // Scalar field         \n"
 "  macro init  (i)     i                               // Initialize           \n"
 "  macro Zk            P1                              // FE space             \n";

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
<<"  macro sxx  (i) ( lambda*divergence(i) + 2*mu*dx( i ) )     // Sigma_xx   \n"
<<"  macro syy  (i) ( lambda*divergence(i) + 2*mu*dy(i#1) )     // Sigma_yy   \n"
<<"  macro sxy  (i) ( mu*( dy(i) + dx(i#1) ) )                  // Sigma_yx   \n"
<<"  macro sig  (i) [ sxx(i), syy(i), SQ2*sxy(i) ]        // Sigma            \n"
<<"  macro Hplus(i) (0.5*(sig(i)'*epsilon(i)))                  // Hplus      \n"
/************************OLD METHOD*************************************************/

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

 if(Prblm=="damage" && Model=="hybrid-phase-field" && energydecomp)
 writeIt
 "                                                                              \n"
 "//------------------------------Hplus macros-------------------------------// \n"
 "                                                                              \n"
 "  macro DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus){          \n"
 "    real[int] par = [lambda,mu];                                              \n"
<<(vectorial  ? "    Sh0 [Eps1,Eps2,Eps12] = [dx(uold),dy(uold1),0.5*(dx(uold1)+dy(uold))]; \n": "")
<<(!vectorial ? "    Sh0 [Eps1,Eps2,Eps12] = [dx(u),dy(u1),0.5*(dx(u1)+dy(u))];\n": "")
<<"                                                                             \n"
 "    GFPSplitEnergy(Eps1[],PsiPlus[],PsiMinus[],HistPlus[],HistMinus[],par)  ; \n"
 "  }//                                                                         \n"
 "                                                                              \n";

 if(Prblm=="damage" && Model=="Mazar")
 writeIt
 "                                                                              \n"
 "//-----------------------Stess calculation macro--------------------------//  \n"
 "                                                                              \n"
 "  macro stress(i,lambdaVal,muVal)                                             \n"
 "     [lambdaVal*(epsilon(i)[0]+epsilon(i)[1])+2.*muVal*epsilon(i)[0],         \n"
 "     lambdaVal*(epsilon(i)[0]+epsilon(i)[1])+2.*muVal*epsilon(i)[1] ,         \n"
 "     2.*muVal*epsilon(i)[2]]//                                                \n"
 "                                                                              \n";

 if(Sequential)
 writeIt
 "                                                                              \n"
 "//--------------------Sequential remapping macros-------------------------//  \n"
 "                                                                              \n"
 "  macro meshN()mesh                   // Two-dimensional problem              \n"
 "  macro intN()int2d                   // Two-dimensional integral             \n"
 "  macro intN1()int1d                  // One-dimensional integral             \n"
 "  macro readmeshN()readmesh           // Two-dimensional 'mesh' reader        \n"
 "  macro gmshloadN()gmshload           // Two-dimensional 'msh' reader         \n"
 "  macro grad(i) [dx(i),dy(i)]         // two-dimensional gradient             \n"
 "                                                                              \n";

} //-- [if loop terminator] space==2 ended --//



if(spc==3){write
<<"                                                                            \n"
<<"//--------------------Macros needed by DDmacro.idp------------------------//\n"
<<"                                                                            \n";

if(!Sequential)write
<<"  macro partitioner "<<Partitioner<<"\t          // Mesh partitioner used   \n"
<<"  macro dimension   3                          // Three-D problem           \n";

 if(Prblm=="elastodynamics")
 writeIt
 "  macro Ux   du                                  // x displacement           \n"
 "  macro Uy   du1                                 // y displacement           \n"
 "  macro Uz   du2                                 // z displacement           \n";

 if(Prblm=="linear-elasticity" || Prblm=="damage")
 writeIt
 "  macro Ux    u                                  // x displacement           \n"
 "  macro Uy    u1                                 // y displacement           \n"
 "  macro Uz    u2                                 // z displacement           \n";

if(vectorial)if(Prblm=="damage" && Model=="hybrid-phase-field")write
<<"  macro Pk       [P"<<lag<<",P"<<lag<<",P"<<lag<<",P"<<lag<<"]// FE space   \n"
<<"  macro def  (i) [ i , i#1, i#2, i#3 ]           // Vect. field definition  \n"
<<"  macro init (i) [ i ,  i ,  i,  i  ]            // Vect. field initialize  \n";

if(vectorial)if(Prblm=="damage" && Model=="hybrid-phase-field")
if(plotAll || debug)write
<<"  macro Pltk         P1                          // FE space                \n"
<<"  macro def0 (i)           i                     // Vect. field definition  \n";

if(Prblm=="damage" && Model=="hybrid-phase-field" && energydecomp)write
<<"  macro Sk           [ P0,P0,P0,P0,P0,P0  ]  // Sixth order strain vector   \n";

if(Prblm=="damage" && Model=="Mazar")if(useGFP)write
<<"  macro Sk           [   P0,P0,P0,P0,P0,P0   ]  // Sixth order strain vector\n"
<<"  macro defStrain(i) [ i,i#1,i#2,i#3,i#4,i#5 ]  // Vect. field definition   \n";

if(!vectorial){write
<<"  macro Pk [P"<<lag<<",P"<<lag<<",P"<<lag<<"]\t\t  // Finite element space  \n";

if(Prblm!="damage")write
<<"                                                                            \n"
<<"  macro def(i)  [i, i#1, i#2]                    // Vect. field definition  \n";

if(Prblm!="damage")if(!Sequential)write
<<"  macro init(i) [i,   i,   i]                    // Vect. field initialize  \n"
<<"                                                                            \n";

if(Prblm=="damage" && Model=="Mazar")write
<<"                                                                            \n"
<<"  macro def(i)  [i, i#1, i#2]                    // Vect. field definition  \n";

if(Prblm=="damage" && Model=="Mazar")if(!Sequential)write
<<"  macro init(i) [i,   i,   i]                    // Vect. field initialize  \n"
<<"                                                                            \n";

} //-- [if loop terminator] !vectorial ended --//

write
<<"                                                                           \n"
<<"//--------------------Divergence and epsilion macros---------------------//\n"
<<"                                                                           \n"
<<"  macro divergence(i) ( dx( i ) + dy(i#1) + dz(i#2) )   // Divergence macro\n"
<<"  macro epsilon   (i) [ dx( i ) , dy(i#1) , dz(i#2) ,                      \n"
<<"                       (dz(i#1) + dy(i#2))/SQ2,                            \n"
<<"                       (dz( i ) + dx(i#2))/SQ2,                            \n"
<<"                       (dy( i ) + dx(i#1))/SQ2]        // Strain macro     \n"
<<"                                                                           \n";

if(Prblm=="damage" && Model=="hybrid-phase-field")if(!vectorial)write
<<"                                                                           \n"
<<"//---------------------------Non-linear macros---------------------------//\n"
<<"                                                                           \n"
<<"  macro def2  (i)  [   i  ,  i#1 ,  i#2  ]        // Vect. field definition\n"
<<"  macro init2 (i)  [   i  ,   i  ,   i   ]        // Vect. field initialize\n"
<<"  macro def   (i)     i                                 // Scalar field    \n"
<<"  macro init  (i)     i                                 // Initialize      \n"
<<"  macro Zk            P1                                // FE space        \n";


if(Prblm=="damage" && Model=="hybrid-phase-field" && !energydecomp)write
<<"                                                                           \n"
<<"//------------------------------Hplus macros-----------------------------//\n"
<<"                                                                           \n"
/*
<<"  macro sxx (i) ( lambda*divergence(i)+2*mu*dx( i ) )        // Sigma_xx   \n"
<<"  macro syy (i) ( lambda*divergence(i)+2*mu*dy(i#1) )        // Sigma_yy   \n"
<<"  macro szz (i) ( lambda*divergence(i)+2*mu*dz(i#2) )        // Sigma_zz   \n"
<<"  macro sxy (i) (     mu*( dy( i ) + dx(i#1) )      )        // Sigma_xy   \n"
<<"  macro sxz (i) (     mu*( dz( i ) + dx(i#2) )      )        // Sigma_xz   \n"
<<"  macro syz (i) (     mu*( dz(i#1) + dy(i#2) )      )        // Sigma_yz   \n"
<<"  macro sig (i) [     sxx(i), syy(i), szz(i)        ,                      \n"
<<"                         SQ2 * syz(i)         ,                            \n"
<<"                         SQ2 * sxz(i)         ,                            \n"
<<"                         SQ2 * sxy(i)         ]        // Sigma            \n"
<<"  macro Hplus(i) (    0.5*( sig(i)'*epsilon(i) )    )        // Hplus      \n"
*/
<<"  macro Hplus (i) ( (0.5*lambda+mu)*(  epsilon(i)[0]*epsilon(i)[0]         \n"
<<"                                     + epsilon(i)[1]*epsilon(i)[1]         \n"
<<"                                     + epsilon(i)[2]*epsilon(i)[2] )       \n"
<<"                   + lambda*(epsilon(i)[0]*epsilon(i)[1]                   \n"
<<"                   +         epsilon(i)[0]*epsilon(i)[2]                   \n"
<<"                   +         epsilon(i)[1]*epsilon(i)[2] )                 \n"
<<"                   + mu*(epsilon(i)[5]*epsilon(i)[5]                       \n"
<<"                   +     epsilon(i)[4]*epsilon(i)[4]                       \n"
<<"                   +     epsilon(i)[3]*epsilon(i)[3] )                     \n"
<<"                  )                                           // Hplus     \n"
<<"                                                                           \n";

if(Prblm=="damage" && Model=="Mazar")write
<<"                                                                           \n"
<<"//-----------------------Stess calculation macro-------------------------//\n"
<<"                                                                           \n"
<<"  macro stress(i,lambdaVal,muVal)                                          \n"
<<"  [                                                                        \n"
<<"   lambdaVal*(epsilon(i)[0]+epsilon(i)[1]+epsilon(i)[2])+2.*muVal*epsilon(i)[0],\n"
<<"   lambdaVal*(epsilon(i)[0]+epsilon(i)[1]+epsilon(i)[2])+2.*muVal*epsilon(i)[1],\n"
<<"   lambdaVal*(epsilon(i)[0]+epsilon(i)[1]+epsilon(i)[2])+2.*muVal*epsilon(i)[2],\n"
<<"   2.*muVal*epsilon(i)[3],                                                 \n"
<<"   2.*muVal*epsilon(i)[4],                                                 \n"
<<"   2.*muVal*epsilon(i)[5]                                                  \n"
<<"  ]//                                                                      \n"
<<"                                                                           \n";

/******************************************************************************************
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
<<"    GFPDecompEnergy3D(e1[],e2[],e3[],e4[],e5[],e6[],PsiPlus[],PsiMinus[],HistPlus[],HistMinus[],par);  \n"
<<"  }//                                                                      \n"
<<"                                                                           \n";
/********************************************************************************************/

if(Prblm=="damage" && Model=="hybrid-phase-field" && energydecomp)write<<
"                                                                             \n"

"//----------------------------Hplus macros---------------------------------//\n"
 "                                                                            \n"
 "  macro DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus){        \n"
 "    real[int] par = [lambda,mu];                                            \n"
 <<(!vectorial  ? "    Sh0 [Eps1,Eps2,Eps3,Eps12,Eps13,Eps23] = [dx(u),dy(u1),dz(u2),0.5*(dx(u1)+dy(u)),0.5*(dx(u2)+dz(u)),0.5*(dy(u2)+dz(u1))]; \n": "")
 <<(vectorial  ? "    Sh0 [Eps1,Eps2,Eps3,Eps12,Eps13,Eps23] = [dx(uold),dy(uold1),dz(uold2),0.5*(dx(uold1)+dy(uold)),0.5*(dx(uold2)+dz(uold)),0.5*(dy(uold2)+dz(uold1))]; \n": "")<<
 "                                                                            \n"
 "    GFPSplitEnergy(Eps1[],PsiPlus[],PsiMinus[],HistPlus[],HistMinus[],par); \n"
 "  }//                                                                       \n"
 "                                                                            \n";

if(Sequential)write
<<"                                                                           \n"
<<"//---------------------Sequential remapping macros-----------------------//\n"
<<"                                                                           \n"
<<"  load \"msh3\"                           // Loading 3D mesh               \n"
<<"  macro meshN()mesh3                    // Three-dimensional problem       \n"
<<"  macro intN()int3d                     // Three-dimensional integral      \n"
<<"  macro intN1()int2d                    // Two-dimensional integral        \n"
<<"  macro readmeshN()readmesh3            // Three-dimensional problem       \n"
<<"  macro gmshloadN()gmshload3            // Three-dimensional 'msh' reader  \n"
<<"  macro grad(i)[dx(i),dy(i),dz(i)]      // three-dimensional gradient      \n"
<<"                                                                           \n";

} //-- [if loop terminator] space==3 ended --//



if(dirichletpointconditions>=1){write
<<"                                                                           \n"
<<"//----------------------------Point BC macro-----------------------------//\n"
<<"                                                                           \n"
<<"  macro Pointbc(Dpointlab,Wh,A,b,PnV){                                     \n"
<<"    int count=0;                                                           \n"
<<"    meshN Th=Wh.Th;                                                        \n"
<<"                                                                           \n";

if(spc==2)write
<<"                                                                           \n"
<<"        varf vlabs(def(u),def(v))                                          \n"
<<"        = on( Dpointlab,                                                   \n"
<<"                u  = -1*( x==PnV[0] && y==PnV[1] ),                        \n"
<<"                u1 = -1*( x==PnV[0] && y==PnV[1] )                         \n"
<<"             );                                                            \n"
<<"                                                                           \n";

if(spc==3)
write
<<"                                                                           \n"
<<"    varf vlabs(def(u),def(v))                                              \n"
<<"        = on( Dpointlab,                                                   \n"
<<"                u  = -1*( x==PnV[0] && y==PnV[1] && z==PnV[2] ),           \n"
<<"                u1 = -1*( x==PnV[0] && y==PnV[1] && z==PnV[2] ),           \n"
<<"                u2 = -1*( x==PnV[0] && y==PnV[1] && z==PnV[2] )            \n"
<<"            );                                                             \n"
<<"                                                                           \n";

write
<<"                                                                           \n"
<<"    real[int] absc=vlabs(0,Wh);                                            \n"
<<"                                                                           \n"
<<"    for (int i=0; i<Wh.ndof; i++){                                         \n"
<<"      if(abs(-1e+30-absc(i))==0 ){                                         \n"
<<"        A(i,i)=tgv;                                                        \n"
<<"        b[i]=PnV["<<spc<<"+count]*tgv;                                     \n"
<<"        count++;                                                           \n"
<<"         if(count=="<<spc<<") break;                                       \n"
<<"      }                                                                    \n"
<<"    }                                                                      \n"
<<"  }//                                                                      \n"
<<"                                                                           \n"
<<"                                                                           \n";

} //-- [if loop terminator] pointbc ended --//


if(timelog){write
<<"                                                                           \n"
<<"//-----------------------------------Timing macros-----------------------//\n"
<<"                                                                           \n";

if(!Sequential)write
<<"                                                                           \n"
<<"  macro MPItimerbegin(str1,t0){                                            \n"
<<"    mpiBarrier(mpiCommWorld);                                              \n"
<<"    t0 = mpiWtime();                                                       \n"
<<"    if(mpirank==0)                                                         \n"
<<"    cout << \"-->\"+str1+\" began....\\n\";                                \n"
<<"  }//                                                                      \n"
<<"                                                                           \n"
<<"  macro MPItimerend(str1,t0){                                              \n"
<<"    mpiBarrier(mpiCommWorld);                                              \n"
<<"    if(mpirank==0)                                                         \n"
<<"    cout.scientific << \"finished in [ \"<< mpiWtime()-t0                  \n"
<<"      << \" ] seconds\\n\\n\";                                             \n"
<<"  }//                                                                      \n"
<<"                                                                           \n"
<<"                                                                           \n";

if(Sequential)write
<<"                                                                           \n"
<<"  macro timerbegin(str1,t0){                                               \n"
<<"    t0 = clock();                                                          \n"
<<"    cout << \"-->\"+str1+\" began....\\n\";                                \n"
<<"  }//                                                                      \n"
<<"                                                                           \n"
<<"  macro timerend(str1,t0){                                                 \n"
<<"    cout.scientific << \"finished in [ \"<< clock()-t0                     \n"
<<"      << \" ] seconds\\n\\n\";                                             \n"
<<"  }//                                                                      \n"
<<"                                                                           \n"
<<"                                                                           \n";

} //-- [if loop terminator] timelog ended --//


if(Prblm=="elastodynamics" || Prblm=="soildynamics")if(!useGFP)write
<<"                                                                           \n"
<<"//------------------------------update macros----------------------------//\n"
<<"                                                                           \n"
<<"  macro updateVariables(du,uold,vold,aold,beta,gamma,dt){                  \n"
<<"                                                                           \n"
<<"    real aloc  ;                                                           \n"
<<"                                                                           \n"
<<"    for (int i=0; i< Vh.ndof; i++){                                        \n"
<<"      aloc     =   (du[][i]-uold[][i]-dt*vold[][i])/beta/(dt*dt)           \n"
<<"                  - (1.-2.*beta)/2./beta*aold[][i];                        \n"
<<"      vold[][i] = vold[][i] + dt*((1.-gamma)*aold[][i] + gamma*aloc);      \n"
<<"      aold[][i] = aloc;                                                    \n"
<<"      uold[][i] = du[][i]    ;                                             \n"
<<"    }                                                                      \n"
<<"  }//                                                                      \n"
<<"                                                                           \n";


if(Prblm=="soildynamics"){write
<<"                                                                           \n"
<<"//----------------------Paraxial rotation macro--------------------------//\n"
<<"                                                                           \n";

if(spc==2)write
<<"  macro PA0(i)                                                             \n"
<<"        [ cp*(N.x*N.x*i + N.x*N.y*i#1) + cs*( N.y*N.y*i - N.x*N.y*i#1),    \n"
<<"          cp*(N.x*N.y*i + N.y*N.y*i#1) + cs*(-N.x*N.y*i + N.x*N.x*i#1)     \n"
<<"        ]//                                                                \n";


if(spc==3)write
<<"  macro PA0(i)                                                             \n"
<<"        [ cp*(N.x*N.x*i + N.x*N.y*i#1 + N.x*N.z*i#2) + cs*( (1.-N.x*N.x)*i - N.x*N.y*i#1 - N.x*N.z*i#2)  ,      \n"
<<"          cp*(N.x*N.y*i + N.y*N.y*i#1 + N.y*N.z*i#2) + cs*(-N.x*N.y*i + (1.-N.y*N.y)*i#1 - N.y*N.z*i#2)  ,      \n"
<<"          cp*(N.x*N.z*i + N.y*N.z*i#1 + N.z*N.z*i#2) + cs*(-N.x*N.z*i - N.y*N.z*i#1 + (1.-N.z*N.z)*i#2)         \n"
<<"        ]//                                                                \n";

if(Sequential)write
<<"                                                                           \n"
<<"//----------------------ParaView plotting macro--------------------------//\n"
<<"                                                                           \n"
<<"  macro exportBegin(name)                                                  \n"
<<"    {ofstream pvd(name +\".pvd\");                                         \n"
<<"      pvd << \"<?xml version=\\\"1.0\\\"?>\\n\";                           \n"
<<"      pvd << \"<VTKFile type=\\\"Collection\\\" version=\\\"0.1\\\"\\n\";  \n"
<<"      pvd << \"         byte_order=\\\"LittleEndian\\\"\\n\";              \n"
<<"      pvd << \"         compressor=\\\"vtkZLibDataCompressor\\\">\\n\";    \n"
<<"      pvd << \"  <Collection>\\n\";                                        \n"
<<"    }//                                                                    \n"
<<"                                                                           \n"
<<"                                                                           \n"
<<"  macro exportEnd(name)                                                    \n"
<<"    {ofstream pvd(name +\".pvd\", append);                                 \n"
<<"    pvd << \"  </Collection>\\n\";                                         \n"
<<"    pvd << \"</VTKFile>\\n\";}                                             \n"
<<"    system(\"mv \"+name+\".pvd .\");                                       \n"
<<"  //                                                                       \n"
<<"                                                                           \n"
<<"                                                                           \n"
<<"  macro exportTimeStep(name, mesh, sol, forder, iterno, ts, nam )          \n"
<<"    savevtk(name+\"_\"+int(iterno)+\".vtu\",mesh,sol,order=forder,dataname=nam);\n"
<<"    ofstream pvd(name +\".pvd\", append);                                  \n"
<<"      pvd << \"    <DataSet timestep=\\\"\" + real(ts) + \"\\\"\\n\";      \n"
<<"      pvd << \"             file=\\\"\";                                   \n"
<<"      pvd << name << \"_\" << int(iterno) << \".vtu\\\"/>\\n\";            \n"
<<"  //                                                                       \n"
<<"                                                                           \n";

/*
if(doublecouple=="force-based"){
write
<<"                                                                           \n"
<<"//-----------------------Double Couple macro-----------------------------//\n"
<<"                                                                           \n"
<<"  macro DcNorthSouth(Dpointlab,Wh,b,PnV,Cond){                             \n"
<<"        varf vlabs(def(u),def(v))                                          \n"
<<"        = on( Dpointlab,                                                   \n"
<<"              u  = 1*( x==PnV[0] && y==PnV[1]                              \n"
<<(spc==3 ? "    && z==PnV[2] ) \n":   "                       )\n"            )
<<"             );                                                            \n"
<<"    real[int] absc=vlabs(0,Wh, tgv = -1);                                  \n"
<<"                                                                           \n"
<<"    for (int i=0; i<Wh.ndof; i++){                                         \n"
<<"      if(absc(i)>0.1){                                                     \n"
<<"        b[i]=Cond;                                                         \n"
<<"        break;                                                             \n"
<<"      }                                                                    \n"
<<"    }                                                                      \n"
<<"  }//                                                                      \n"
<<"                                                                           \n"
<<"  macro DcEastWest(Dpointlab,Wh,b,PnV,Cond){                               \n"
<<"        varf vlabs(def(u),def(v))                                          \n"
<<"        = on( Dpointlab,                                                   \n"
<<(spc==3 ? "               u2 \n"    :   "               u1 \n"               )
<<"                = 1*( x==PnV[0] && y==PnV[1]                                \n"
<<(spc==3 ? "    && z==PnV[2] ) \n":                   ")\n"                   )
<<"             );                                                            \n"
<<"    real[int] absc=vlabs(0,Wh, tgv = -1);                                  \n"
<<"                                                                           \n"
<<"    for (int i=0; i<Wh.ndof; i++){                                         \n"
<<"      if(absc(i)>0.1){                                                     \n"
<<"        b[i]=Cond;                                                         \n"
<<"        break;                                                             \n"
<<"      }                                                                    \n"
<<"    }                                                                      \n"
<<"  }//                                                                      \n"
<<"                                                                           \n";
}
*/

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
  "//  Inputs  : DcLabelPoints,  PnN, PnS, PnE, PnW                               \n"
  "//  Outputs : DcFlag,  iN, iS, iE, iW,  Nrank, Srank, Erank, Wrank             \n"
  "// -------------------------------------------------------------------         \n"
  "//  DcLabelPoints : is the vector of [int] contains labels of borders          \n"
  "//                  that contain the double couple points.                     \n"
  "//  DcFlag : is a Boolean flag to assert if the  processor  holds any          \n"
  "//           double couple points.                                             \n"
  "//  PnN : is the vector containing the point coordinates of the North          \n"
  "//        point of the double couple. Same is true for PnS, PnE, PnW.          \n"
  "//  iN  : is finite element degree of freedom of the Northern  double          \n"
  "//        couple point. Same is true for iS, iE, iW.                           \n"
  "//  Nrank  : is rank of the MPI process that holds the finite element          \n"
  "//           degree of freedom of the  Northern  double couple point.          \n"
  "//           Same is true for Srank, Erank, Wrank.                             \n"
  "//=============================================================================\n"
<<"                                                                           \n"
<<"                                                                           \n"
<<"  macro GetDoubelCoupleIndicies(DcLabelPoints, Wh, DcFlag,                 \n"
<<"                                PnN,   PnS,   PnE,   PnW,                  \n"
<<"                                iN,    iS,    iE,    iW,                   \n"
<<"                                Nrank, Srank, Erank, Wrank)                \n"
<<"   {                                                                       \n"
<<"    varf VarfPointLabs(def(u),def(v))                                      \n"
<<"    = on( DcLabelPoints,                                                   \n"
<<"          u  =  1*( x==PnN[0] && y==PnN[1]) + 2*( x==PnS[0] && y==PnS[1]), \n"
<<"          u1 =  3*( x==PnE[0] && y==PnE[1]) + 4*( x==PnW[0] && y==PnW[1])  \n"
<<"        );                                                                 \n"
<<"                                                                           \n"
<<"    real[int] PointMarker=VarfPointLabs(0,Wh, tgv = -1);                   \n"
<<"                                                                           \n"
<<"    for (int i=0; i<Wh.ndof; i++){                                         \n"
<<"      if(PointMarker(i)>0.1 && PointMarker(i)<1.1)                         \n"
<<"      {iN=i; Nrank=mpirank; DcFlag=true;}                                  \n"
<<"      if(PointMarker(i)>1.1 && PointMarker(i)<2.1)                         \n"
<<"      {iS=i; Srank=mpirank; DcFlag=true;}                                  \n"
<<"      if(PointMarker(i)>2.1 && PointMarker(i)<3.1)                         \n"
<<"      {iE=i; Erank=mpirank; DcFlag=true;}                                  \n"
<<"      if(PointMarker(i)>3.1 && PointMarker(i)<4.1)                         \n"
<<"      {iW=i; Wrank=mpirank; DcFlag=true;}                                  \n"
<<"    }                                                                      \n"
<<"  }//                                                                      \n";

if(doublecouple=="displacement-based")
write
<<"                                                                           \n"
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
  "//  DcFlag : is a Boolean flag to assert if the  processor  holds any          \n"
  "//           double couple points.                                             \n"
  "//  iN  : is finite element degree of freedom of the Northern  double          \n"
  "//        couple point. Same is true for iS, iE, iW.                           \n"
  "//  Nrank  : is rank of the MPI process that holds the finite element          \n"
  "//           degree of freedom of the  Northern  double couple point.          \n"
  "//           Same is true for Srank, Erank, Wrank.                             \n"
  "//  tgv  : is the large penalization term tgv=1e30.                            \n"
  "//=============================================================================\n"
<<"                                                                           \n"
<<"  macro ApplyDoubleCoupleToA(A,DcFlag,iN,iS,iE,iW,Nrank,Srank,Erank,Wrank) \n"
<<"   if(DcFlag){                                                             \n"
<<"     if(mpirank==Nrank)                                                    \n"
<<"       A(iN,iN)= tgv;                                                      \n"
<<"     if(mpirank==Srank)                                                    \n"
<<"       A(iS,iS)= tgv;                                                      \n"
<<"     if(mpirank==Erank)                                                    \n"
<<"       A(iE,iE)= tgv;                                                      \n"
<<"     if(mpirank==Wrank)                                                    \n"
<<"       A(iW,iW)= tgv;                                                      \n"
<<"    }                                                                      \n"
<<"  //                                                                       \n"
<<"                                                                           \n"
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
  "//  DcFlag : is a Boolean flag to assert if the  processor  holds any          \n"
  "//           double couple points.                                             \n"
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
<<"                                                                           \n"
<<"  macro ApplyDoubleCoupleToRHS( RHS, DcFlag,                               \n"
<<"                                CondN,CondS,CondE,CondW,                   \n"
<<"                                iN,   iS,   iE,   iW,                      \n"
<<"                                Nrank,Srank,Erank,Wrank)                   \n"
<<"   if(DcFlag){                                                             \n"
<<"     if(mpirank==Nrank)                                                    \n"
<<"       RHS[iN]= CondN*tgv;                                                 \n"
<<"     if(mpirank==Srank)                                                    \n"
<<"       RHS[iS]= CondS*tgv;                                                 \n"
<<"     if(mpirank==Erank)                                                    \n"
<<"       RHS[iE]= CondE*tgv;                                                 \n"
<<"     if(mpirank==Wrank)                                                    \n"
<<"       RHS[iW]= CondW*tgv;                                                 \n"
<<"    }                                                                      \n"
<<"  //                                                                       \n"
<<"                                                                           \n";

if(doublecouple=="force-based")
write
<<"                                                                           \n"
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
  "//  DcFlag : is a Boolean flag to assert if the  processor  holds any          \n"
  "//           double couple points.                                             \n"
  "//  CondN  : is boundary condition force applied to the norther point          \n"
  "//           of the double couple. Same is true for Conds, CondW, and          \n"
  "//           CondE.                                                            \n"
  "//  iN  : is finite element degree of freedom of the Northern  double          \n"
  "//        couple point. Same is true for iS, iE, iW.                           \n"
  "//  Nrank  : is rank of the MPI process that holds the finite element          \n"
  "//           degree of freedom of the  Northern  double couple point.          \n"
  "//           Same is true for Srank, Erank, Wrank.                             \n"
  "//=============================================================================\n"
<<"                                                                           \n"
<<"  macro ApplyDoubleCoupleToRHS( RHS, DcFlag,                               \n"
<<"                                CondN,CondS,CondE,CondW,                   \n"
<<"                                iN,   iS,   iE,   iW,                      \n"
<<"                                Nrank,Srank,Erank,Wrank)                   \n"
<<"   if(DcFlag){                                                             \n"
<<"     if(mpirank==Nrank)                                                    \n"
<<"       RHS[iN]= CondN;                                                     \n"
<<"     if(mpirank==Srank)                                                    \n"
<<"       RHS[iS]= CondS;                                                     \n"
<<"     if(mpirank==Erank)                                                    \n"
<<"       RHS[iE]= CondE;                                                     \n"
<<"     if(mpirank==Wrank)                                                    \n"
<<"       RHS[iW]= CondW;                                                     \n"
<<"    }                                                                      \n"
<<"  //                                                                       \n"
<<"                                                                           \n";
}


/*
<<"//-----------------------Double Couple macro-----------------------------//\n"
<<"                                                                           \n"
<<"  macro DcNorthSouth(Dpointlab,Wh,A,b,PnV,Cond){                           \n"
<<"        varf vlabs(def(u),def(v))                                          \n"
<<"        = on( Dpointlab,                                                   \n"
<<"              u  = 1*( x==PnV[0] && y==PnV[1]                              \n"
<<(spc==3 ? "    && z==PnV[2] ) \n":   "                       )\n"            )
<<"             );                                                            \n"
<<"    real[int] absc=vlabs(0,Wh, tgv = -1);                                  \n"
<<"                                                                           \n"
<<"    for (int i=0; i<Wh.ndof; i++){                                         \n"
<<"      if(absc(i)>0.1){                                                     \n"
<<"        A(i,i)=tgv; b[i]=Cond*tgv; break;                                  \n"
<<"      }                                                                    \n"
<<"    }                                                                      \n"
<<"  }//                                                                      \n"
<<"                                                                           \n"
<<"  macro DcEastWest(Dpointlab,Wh,A,b,PnV,Cond){                             \n"
<<"        varf vlabs(def(u),def(v))                                          \n"
<<"        = on( Dpointlab,                                                   \n"
<<(spc==3 ? "               u2 \n"    :   "               u1 \n"               )
<<"                = 1*( x==PnV[0] && y==PnV[1]                                \n"
<<(spc==3 ? "    && z==PnV[2] ) \n":                   ")\n"                   )
<<"             );                                                            \n"
<<"    real[int] absc=vlabs(0,Wh, tgv = -1);                                  \n"
<<"                                                                           \n"
<<"    for (int i=0; i<Wh.ndof; i++){                                         \n"
<<"      if(absc(i)>0.1){                                                     \n"
<<"        A(i,i)=tgv; b[i]=Cond*tgv; break;                                  \n"
<<"      }                                                                    \n"
<<"    }                                                                      \n"
<<"  }//                                                                      \n"
<<"                                                                           \n";
}
*/

}

} //-- [ostream terminator]  macros.edp closed --//

cout << " ................................... Done \n";

