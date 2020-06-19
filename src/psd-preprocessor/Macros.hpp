//=============================================================================
// ------ Building the Macros.edp file ------ 
//=============================================================================

cout << " building Macros.edp";
   
{ofstream  writemacros("Macros.edp");

writemacros<<
"/********************************* Macros *************************************\n"
"*                                                                             *\n"
"* Note!!! This file is  generated  by  running  PSD PreProcessor. Do not edit *\n"
"*         in order to  control this file please change flag arguments of  the *\n"
"*         PSD_PreProcess. To know the available flags run PSD_PreProcess with *\n"
"*         -help or read the PSD manual.                                       *\n"
"*                                                                             *\n"
"******************************************************************************/\n"
"                                                                               \n";

if(spc==2){writemacros
<<"                                                                                \n"
<<"//------------------------- Essential Macros ---------------------------------//\n"
<<"                                                                                \n";

if(!Sequential)writemacros
<<"  macro partitioner "<<Partitioner<<"\t\t        // Mesh partitioner used              \n"
<<"  macro dimension 2                              // Two-dimensional problem            \n";

if(vectorial)if(Prblm=="damage" && Model=="hybrid-phase-field")writemacros
<<"  macro Pk       [ P"<<lag<<", P"<<lag<<" , P"<<lag<<"  ]\t\t// FE space             \n"
<<"  macro def  (i) [ i , i#1, i#2 ]                // Vect. field definition             \n"
<<"  macro init (i) [ i ,  i ,  i  ]                // Vect. field initialize             \n";

if(vectorial)if(Prblm=="damage" && Model=="hybrid-phase-field")
if(plotAll || debug)writemacros
<<"  macro Pltk         P1                             // FE space                               \n"
<<"  macro def0 (i)           i                         // Vect. field definition             \n";

if(Prblm=="damage" && Model=="hybrid-phase-field" && energydecomp)writemacros<<
"  macro Sk       [ P0, P0 , P0  ]       // Third order strain vector              \n";

if(Prblm=="damage" && Model=="Mazar")if(useGFP)writemacros
<<"  macro Sk           [ P0, P0 , P0  ]            // Third order strain vector   \n"
<<"  macro defStrain(i) [ i , i#1, i#2 ]            // Vect. field definition             \n";

if(!vectorial){writemacros
<<"  macro Pk       [ P"<<lag<<", P"<<lag<<"  ]\t\t    // Finite element space           \n";

if(Prblm!="damage")writemacros
<<"  macro def  (i) [ i , i#1 ]                // Vect. field definition             \n";

if(Prblm!="damage")if(!Sequential)writemacros
<<"  macro init (i) [ i ,  i  ]                // Vect. field initialize             \n"
<<"                                                                                   \n";

if(Prblm=="damage" && Model=="Mazar")writemacros
<<"  macro def  (i) [ i , i#1 ]                // Vect. field definition             \n";

if(Prblm=="damage" && Model=="Mazar")if(!Sequential)writemacros
<<"  macro init (i) [ i ,  i  ]                // Vect. field initialize             \n"
<<"                                                                                   \n";

} //-- [if loop terminator] !vectorial ended --//

writemacros
<<"                                                                                   \n"
<<"//--------------------Divergence and epsilion macros--------------------------//\n"
<<"                                                                                   \n"
<<"  macro divergence(i)(dx(i) + dy(i#1))                // Divergence function     \n"
<<"  macro epsilon(i) [dx(i), dy(i#1),                                                   \n" 
<<"                   (dy(i)+dx(i#1))/SQ2]        // Strain definition           \n";

if(Prblm=="damage" && Model=="hybrid-phase-field")if(!vectorial)writemacros
<<"                                                                                   \n"
<<"//---------------------------Non-linear macros--------------------------------//\n"
<<"                                                                                   \n"
<<"  macro def2  (i) [ i , i#1 ]                                // Vect. field            \n"
<<"  macro init2 (i) [ i ,  i  ]                                // Vect. initialize\n"
<<"  macro def   (i)     i                                        // Scalar field    \n"
<<"  macro init  (i)     i                                        // Initialize             \n"
<<"  macro Zk            P1                                            // FE space           \n";

if(Prblm=="damage" && Model=="hybrid-phase-field" && !energydecomp)writemacros
<<"                                                                                   \n"
<<"//------------------------------Hplus macros----------------------------------//\n"
<<"                                                                                   \n"
/************************OLD METHOD*************************************************
<<"  macro sxx  (i) ( lambda*divergence(i) + 2*mu*dx( i ) )     // Sigma_xx           \n"
<<"  macro syy  (i) ( lambda*divergence(i) + 2*mu*dy(i#1) )     // Sigma_yy           \n"
<<"  macro sxy  (i) ( mu*( dy(i) + dx(i#1) ) )                  // Sigma_yx           \n"
<<"  macro sig  (i) [ sxx(i), syy(i), SQ2*sxy(i) ]        // Sigma           \n"
<<"  macro Hplus(i) (0.5*(sig(i)'*epsilon(i)))                  // Hplus              \n"
/************************OLD METHOD*************************************************/  
<<"  macro Hplus (i) ( (0.5*lambda+mu)*(  epsilon(i)[0]*epsilon(i)[0]                    \n"
<<"                                     + epsilon(i)[1]*epsilon(i)[1] )            \n"
<<"                   + lambda*epsilon(i)[0]*epsilon(i)[1]                            \n"
<<"                   + mu*epsilon(i)[2]*epsilon(i)[2]                                      \n"
<<"                  )                                           // Hplus              \n"
<<"                                                                                   \n";


/************************OLD METHOD*************************************************
if(Prblm=="damage" && Model=="hybrid-phase-field" && energydecomp)writemacros
<<"                                                                                   \n"
<<"//------------------------------Hplus macros----------------------------------//\n"
<<"  macro DecomposeElasticEnergy(Hplus,Hminus,H){                                   \n"
<<"    fespace WWh0(Th,P0);                                                           \n"
<<"    WWh0 e1,e2,e3,ud;                                                           \n"
<<(!vectorial ? "    e1=dx(u); e2=dy(u1);\n"        : ""                                  )
<<(vectorial  ? "    e1=dx(uold); e2=dy(uold1);\n"  : ""                                  )  
<<"    e1=dx(u); e2=dy(u1);                                                           \n"
<<"    ud[] = e1[] + e2[];                                                           \n"
<<"    e3 = max(0.,ud);                                                                   \n"
<<"    Hplus = 0.5*lambda*(e3*e3);                                                   \n"
<<"    e3 = min(0.,ud);                                                                   \n"
<<"    Hminus = 0.5*lambda*(e3*e3);                                                   \n"
<<(!vectorial ? "    e3=0.5*(dx(u1)+dy(u));\n"        : ""                                  )
<<(vectorial  ? "    e3=0.5*(dx(uold1)+dy(uold));\n"  : ""                                  )
<<"    real[int] eval(2),eval1(2);                                                   \n"
<<"    real[int,int] A(2,2);                                                           \n"
<<"    for(int i=0; i< Wh0.ndof; i++){                                                    \n"
<<"      A(0,0)= e1[][i];                                                           \n"
<<"      A(0,1)= e3[][i];                                                           \n"
<<"      A(1,1)= e2[][i];                                                           \n"
<<"      GFPeigenAlone (A, eval);                                                   \n"
<<"      eval1[0]=max(0.,eval[0]);                                                   \n"
<<"      eval1[1]=max(0.,eval[1]);                                                   \n"
<<"      eval[0]=min(0.,eval[0]);                                                   \n"
<<"      eval[1]=min(0.,eval[1]);                                                   \n"
<<"      Hplus[][i] +=mu*(eval1[0]*eval1[0] + eval1[1]*eval1[1]);                   \n"
<<"      Hminus[][i]+=mu*(eval[0]*eval[0] + eval[1]*eval[1]);                           \n"
<<"    }                                                                           \n"
<<"    GFPmaxintwoFEfields(H[],Hplus[]);                                           \n"
<<"  }//                                                                           \n"
/************************OLD METHOD*************************************************/

/************************OLD METHOD*************************************************
if(Prblm=="damage" && Model=="hybrid-phase-field" && energydecomp)writemacros
<<"                                                                                   \n"
<<"//------------------------------Hplus macros----------------------------------//\n"
<<"                                                                                   \n"
<<"  macro DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus){           \n"
<<"    fespace WWh0(Th,P0);                                                           \n"
<<"    WWh0 e1,e2,e3;                                                                   \n"
<<(vectorial  ? "    e1=dx(uold); e2=dy(uold1);\n"    : ""                                  )
<<(vectorial  ? "    e3=0.5*(dx(uold1)+dy(uold));\n"  : ""                                  )
<<(!vectorial ? "    e1=dx(u); e2=dy(u1);\n"          : ""                                  )
<<(!vectorial ? "    e3=0.5*(dx(u1)+dy(u));\n"        : ""                                  )
<<"                                                                                   \n"
<<"    GFPDecompEnergy2D(e1[],e2[],e3[],PsiPlus[],PsiMinus[],HistPlus[],HistMinus[],lambda,mu);           \n"
<<"  }//                                                                           \n" 
<<"                                                                                   \n";
/************************OLD METHOD*************************************************/

if(Prblm=="damage" && Model=="hybrid-phase-field" && energydecomp)writemacros<<
 "                                                                             \n"
 "//------------------------------Hplus macros-------------------------------//\n"
 "                                                                             \n"
 "  macro DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus){         \n"
 "    real[int] par = [lambda,mu];                                             \n"
<<(vectorial  ? "    Sh0 [Eps1,Eps2,Eps12] = [dx(uold),dy(uold1),0.5*(dx(uold1)+dy(uold))]; \n": "")
<<(!vectorial ? "    Sh0 [Eps1,Eps2,Eps12] = [dx(u),dy(u1),0.5*(dx(u1)+dy(u))];\n": "")
<<"                                                                            \n"
 "    GFPSplitEnergy(Eps1[],PsiPlus[],PsiMinus[],HistPlus[],HistMinus[],par)  ;\n"
 "  }//                                                                        \n" 
 "                                                                             \n";



if(Prblm=="damage" && Model=="Mazar")writemacros
<<"                                                                                   \n"
<<"//-----------------------Stess calculation macro------------------------------//\n"
<<"                                                                                   \n"
<<"  macro stress(i,lambdaVal,muVal)                                                    \n"
<<"     [lambdaVal*(epsilon(i)[0]+epsilon(i)[1])+2.*muVal*epsilon(i)[0],           \n"
<<"     lambdaVal*(epsilon(i)[0]+epsilon(i)[1])+2.*muVal*epsilon(i)[1] ,           \n"
<<"     2.*muVal*epsilon(i)[2]]//                                                    \n"
<<"                                                                                   \n";
  
if(Sequential)writemacros
<<"                                                                                   \n"
<<"//--------------------Sequential remapping macros-----------------------------//\n"
<<"                                                                                   \n"
<<"  macro meshN()mesh                          // Two-dimensional problem           \n"
<<"  macro intN()int2d                          // Two-dimensional integral           \n"
<<"  macro intN1()int1d                         // One-dimensional integral           \n"
<<"  macro readmeshN()readmesh                  // Two-dimensional 'mesh' reader   \n"
<<"  macro gmshloadN()gmshload                  // Two-dimensional 'msh' reader           \n"
<<"  macro grad(i) [dx(i),dy(i)]                // two-dimensional gradient           \n"
<<"                                                                                   \n";

} //-- [if loop terminator] space==2 ended --//



if(spc==3){writemacros
<<"                                                                                   \n"
<<"//--------------------Macros needed by DDmacro.idp----------------------------//\n"
<<"                                                                                   \n";

if(!Sequential)writemacros
<<"  macro partitioner "<<Partitioner<<"\t                // Mesh partitioner used   \n"
<<"  macro dimension   3                                // Three-D problem           \n";

if(vectorial)if(Prblm=="damage" && Model=="hybrid-phase-field")writemacros
<<"  macro Pk       [P"<<lag<<",P"<<lag<<",P"<<lag<<",P"<<lag<<"]// FE space       \n"
<<"  macro def  (i) [ i , i#1, i#2, i#3 ]                // Vect. field definition  \n"
<<"  macro init (i) [ i ,  i ,  i,  i  ]                // Vect. field initialize  \n";

if(vectorial)if(Prblm=="damage" && Model=="hybrid-phase-field")
if(plotAll || debug)writemacros
<<"  macro Pltk         P1                             // FE space                               \n"
<<"  macro def0 (i)           i                         // Vect. field definition             \n";

if(Prblm=="damage" && Model=="hybrid-phase-field" && energydecomp)writemacros
<<"  macro Sk           [ P0,P0,P0,P0,P0,P0  ]  // Sixth order strain vector       \n";

if(Prblm=="damage" && Model=="Mazar")if(useGFP)writemacros
<<"  macro Sk           [   P0,P0,P0,P0,P0,P0   ]  // Sixth order strain vector           \n"
<<"  macro defStrain(i) [ i,i#1,i#2,i#3,i#4,i#5 ]  // Vect. field definition       \n";

if(!vectorial){writemacros
<<"  macro Pk [P"<<lag<<",P"<<lag<<",P"<<lag<<"]\t\t        // Finite element space           \n";

if(Prblm!="damage")writemacros
<<"                                                                                   \n"
<<"  macro def(i)  [i, i#1, i#2]                        // Vect. field definition  \n";

if(Prblm!="damage")if(!Sequential)writemacros
<<"  macro init(i) [i,   i,   i]                        // Vect. field initialize  \n"
<<"                                                                                   \n";

if(Prblm=="damage" && Model=="Mazar")writemacros
<<"                                                                                   \n"
<<"  macro def(i)  [i, i#1, i#2]                        // Vect. field definition  \n";

if(Prblm=="damage" && Model=="Mazar")if(!Sequential)writemacros
<<"  macro init(i) [i,   i,   i]                        // Vect. field initialize  \n"
<<"                                                                                   \n";

} //-- [if loop terminator] !vectorial ended --//

writemacros
<<"                                                                                   \n"
<<"//--------------------Divergence and epsilion macros--------------------------//\n"
<<"                                                                                   \n"
<<"  macro divergence(i) ( dx( i ) + dy(i#1) + dz(i#2) )        // Divergence macro\n"
<<"  macro epsilon   (i) [ dx( i ) , dy(i#1) , dz(i#2) ,                           \n"
<<"                       (dz(i#1) + dy(i#2))/SQ2,                           \n"
<<"                       (dz( i ) + dx(i#2))/SQ2,                           \n"
<<"                       (dy( i ) + dx(i#1))/SQ2]        // Strain macro    \n"
<<"                                                                                   \n";

if(Prblm=="damage" && Model=="hybrid-phase-field")if(!vectorial)writemacros
<<"                                                                                   \n"
<<"//---------------------------Non-linear macros--------------------------------//\n"
<<"                                                                                   \n"
<<"  macro def2  (i)  [   i  ,  i#1 ,  i#2  ]        // Vect. field definition             \n"
<<"  macro init2 (i)  [   i  ,   i  ,   i   ]        // Vect. field initialize             \n"
<<"  macro def   (i)     i                                        // Scalar field    \n"
<<"  macro init  (i)     i                                        // Initialize             \n"
<<"  macro Zk            P1                                            // FE space           \n";


if(Prblm=="damage" && Model=="hybrid-phase-field" && !energydecomp)writemacros
<<"                                                                                   \n"
<<"//------------------------------Hplus macros----------------------------------//\n"
<<"                                                                                   \n"
/*
<<"  macro sxx (i) ( lambda*divergence(i)+2*mu*dx( i ) )        // Sigma_xx           \n"
<<"  macro syy (i) ( lambda*divergence(i)+2*mu*dy(i#1) )        // Sigma_yy           \n"
<<"  macro szz (i) ( lambda*divergence(i)+2*mu*dz(i#2) )        // Sigma_zz           \n"
<<"  macro sxy (i) (     mu*( dy( i ) + dx(i#1) )      )        // Sigma_xy           \n"
<<"  macro sxz (i) (     mu*( dz( i ) + dx(i#2) )      )        // Sigma_xz           \n"
<<"  macro syz (i) (     mu*( dz(i#1) + dy(i#2) )      )        // Sigma_yz           \n"
<<"  macro sig (i) [     sxx(i), syy(i), szz(i)        ,                           \n"
<<"                         SQ2 * syz(i)         ,                           \n"
<<"                         SQ2 * sxz(i)         ,                           \n"
<<"                         SQ2 * sxy(i)         ]        // Sigma              \n"
<<"  macro Hplus(i) (    0.5*( sig(i)'*epsilon(i) )    )        // Hplus              \n"
*/
<<"  macro Hplus (i) ( (0.5*lambda+mu)*(  epsilon(i)[0]*epsilon(i)[0]                    \n"
<<"                                     + epsilon(i)[1]*epsilon(i)[1]                     \n"
<<"                                     + epsilon(i)[2]*epsilon(i)[2] )            \n"
<<"                   + lambda*(epsilon(i)[0]*epsilon(i)[1]                            \n"
<<"                   +         epsilon(i)[0]*epsilon(i)[2]                            \n"
<<"                   +         epsilon(i)[1]*epsilon(i)[2] )                           \n"
<<"                   + mu*(epsilon(i)[5]*epsilon(i)[5]                              \n"
<<"                   +     epsilon(i)[4]*epsilon(i)[4]                              \n"
<<"                   +     epsilon(i)[3]*epsilon(i)[3] )                             \n"
<<"                  )                                           // Hplus              \n"
<<"                                                                                   \n";

if(Prblm=="damage" && Model=="Mazar")writemacros
<<"                                                                                   \n"
<<"//-----------------------Stess calculation macro------------------------------//\n"
<<"                                                                                   \n"
<<"  macro stress(i,lambdaVal,muVal)                                                    \n"
<<"  [                                                                                   \n"
<<"   lambdaVal*(epsilon(i)[0]+epsilon(i)[1]+epsilon(i)[2])+2.*muVal*epsilon(i)[0],\n"
<<"   lambdaVal*(epsilon(i)[0]+epsilon(i)[1]+epsilon(i)[2])+2.*muVal*epsilon(i)[1],\n"
<<"   lambdaVal*(epsilon(i)[0]+epsilon(i)[1]+epsilon(i)[2])+2.*muVal*epsilon(i)[2],\n"
<<"   2.*muVal*epsilon(i)[3],                                                            \n"
<<"   2.*muVal*epsilon(i)[4],                                                           \n"
<<"   2.*muVal*epsilon(i)[5]                                                            \n"
<<"  ]//                                                                             \n"
<<"                                                                                   \n";

/******************************************************************************************
if(Prblm=="damage" && Model=="hybrid-phase-field" && energydecomp)writemacros
<<"                                                                                   \n"
<<"//------------------------------Hplus macros----------------------------------//\n"
<<"                                                                                   \n"
<<"  macro DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus){                   \n"
<<"    fespace WWh0(Th,P0);                                                           \n"
<<"    WWh0 e1,e2,e3,e4,e5,e6;                                                           \n"
<<"                                                                                   \n"
<<"    real[int] par(2);                                                           \n"
<<"    par[0] = lambda ;                                                           \n"
<<"    par[1] = mu     ;                                                           \n"
<<"                                                                                   \n"
<<(!vectorial ? "    e1=dx(u); e2=dy(u1); e3=dy(u2);\n"           : ""              )
<<(!vectorial ? "    e4=0.5*(dx(u1)+dy(u));\n"                          : ""              )
<<(!vectorial ? "    e5=0.5*(dz(u)+dx(u2));\n"                    : ""              )
<<(!vectorial ? "    e6=0.5*(dz(u1)+dy(u2));\n"                   : ""              )
<<(vectorial  ? "    e1=dx(uold); e2=dy(uold1); e3=dy(uold2);\n"  : ""              )
<<(vectorial  ? "    e4=0.5*(dx(uold1)+dy(uold));\n"              : ""              )
<<(vectorial  ? "    e5=0.5*(dz(uold)+dx(uold2));\n"              : ""              )
<<(vectorial  ? "    e6=0.5*(dz(uold1)+dy(uold2));\n"             : ""              )
<<"                                                                                   \n"
<<"    GFPDecompEnergy3D(e1[],e2[],e3[],e4[],e5[],e6[],PsiPlus[],PsiMinus[],HistPlus[],HistMinus[],par);  \n"
<<"  }//                                                                           \n" 
<<"                                                                                   \n";
/********************************************************************************************/

if(Prblm=="damage" && Model=="hybrid-phase-field" && energydecomp)writemacros<<
"                                                                               \n"
 
"//------------------------------Hplus macros----------------------------------//\n"
 "                                                                               \n"
 "  macro DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus){           \n"
 "    real[int] par = [lambda,mu];                                               \n"
 <<(!vectorial  ? "    Sh0 [Eps1,Eps2,Eps3,Eps12,Eps13,Eps23] = [dx(u),dy(u),dz(u),0.5*(dx(u1)+dy(u)),0.5*(dx(u2)+dz(u)),0.5*(dy(u2)+dz(u1))]; \n": "")<<
 <<(vectorial  ? "    Sh0 [Eps1,Eps2,Eps3,Eps12,Eps13,Eps23] = [dx(uold),dy(uold),dz(uold),0.5*(dx(uold1)+dy(uold)),0.5*(dx(uold2)+dz(uold)),0.5*(dy(uold2)+dz(uold1))]; \n": "")<< 
 "                                                                               \n"
 "    GFPSplitEnergy(Eps1[],PsiPlus[],PsiMinus[],HistPlus[],HistMinus[],par)  ;  \n"
<<"  }//                                                                         \n" 
<<"                                                                              \n";

if(Sequential)writemacros
<<"                                                                                   \n"
<<"//---------------------Sequential remapping macros----------------------------//\n"
<<"                                                                                   \n"
<<"  load \"msh3\"                                // Loading 3D mesh                   \n"
<<"  macro meshN()mesh3                                // Three-dimensional problem           \n"
<<"  macro intN()int3d                                // Three-dimensional integral           \n"
<<"  macro intN1()int2d                                // Two-dimensional integral           \n"
<<"  macro readmeshN()readmesh3                        // Three-dimensional problem           \n"
<<"  macro gmshloadN()gmshload3                        // Three-dimensional 'msh' reader  \n"
<<"  macro grad(i)[dx(i),dy(i),dz(i)]                // three-dimensional gradient           \n"
<<"                                                                                   \n";

} //-- [if loop terminator] space==3 ended --//



if(dirichletpointconditions>=1){writemacros
<<"                                                                                   \n"
<<"//----------------------------Point BC macro----------------------------------//\n"
<<"                                                                                   \n"
<<"  macro Pointbc(Dpointlab,Wh,A,b,PnV){                                           \n"
<<"    int count=0;                                                                   \n"
<<"    meshN Th=Wh.Th;                                                                   \n"
<<"                                                                                   \n";
 
if(spc==2)writemacros
<<"                                                                                   \n"
<<"        varf vlabs(def(u),def(v))                                                    \n"
<<"        = on( Dpointlab,                                                            \n"
<<"                u  = -1*( x==PnV[0] && y==PnV[1] ),                                      \n"
<<"                u1 = -1*( x==PnV[0] && y==PnV[1] )                                   \n"
<<"             );                                                                           \n"
<<"                                                                                   \n";

if(spc==3)
writemacros
<<"                                                                                   \n"
<<"    varf vlabs(def(u),def(v))                                                    \n"
<<"        = on( Dpointlab,                                                            \n"
<<"                u  = -1*( x==PnV[0] && y==PnV[1] && z==PnV[2] ),                     \n"
<<"                u1 = -1*( x==PnV[0] && y==PnV[1] && z==PnV[2] ),                      \n"
<<"                u2 = -1*( x==PnV[0] && y==PnV[1] && z==PnV[2] )                       \n"
<<"            );                                                                           \n"
<<"                                                                                   \n";

writemacros
<<"                                                                                   \n"
<<"    real[int] absc=vlabs(0,Wh);                                                   \n"
<<"                                                                                   \n"
<<"    for (int i=0; i<Wh.ndof; i++){                                                   \n"
<<"      if(abs(-1e+30-absc(i))==0 ){                                                   \n"
<<"        A(i,i)=tgv;                                                                   \n"
<<"        b[i]=PnV["<<spc<<"+count]*tgv;                                           \n"
<<"        count++;                                                                   \n"
<<"         if(count=="<<spc<<") break;                                                   \n"
<<"      }                                                                           \n"
<<"    }                                                                           \n"
<<"  }//                                                                           \n"
<<"                                                                                   \n"
<<"                                                                                   \n";

} //-- [if loop terminator] pointbc ended --//


if(timelog){writemacros
<<"                                                                                   \n"
<<"//-----------------------------------Timing macros----------------------------//\n"
<<"                                                                                   \n";

if(!Sequential)writemacros
<<"                                                                                   \n"
<<"  macro MPItimerbegin(str1,t0){                                                   \n"
<<"    mpiBarrier(mpiCommWorld);                                                   \n"
<<"    t0 = mpiWtime();                                                                      \n"
<<"    if(mpirank==0)                                                                   \n"
<<"    cout << \"-->\"+str1+\" began....\\n\";                                              \n"
<<"  }//                                                                           \n"
<<"                                                                                   \n"
<<"  macro MPItimerend(str1,t0){                                                   \n"
<<"    mpiBarrier(mpiCommWorld);                                                   \n"
<<"    if(mpirank==0)                                                                   \n"
<<"    cout.scientific << \"finished in [ \"<< mpiWtime()-t0                            \n"
<<"      << \" ] seconds\\n\\n\";                                                   \n"
<<"  }//                                                                           \n"
<<"                                                                                   \n"
<<"                                                                                   \n";

if(Sequential)writemacros
<<"                                                                                   \n"
<<"  macro timerbegin(str1,t0){                                                           \n"
<<"    t0 = clock();                                                                   \n"
<<"    cout << \"-->\"+str1+\" began....\\n\";                                           \n"
<<"  }//                                                                           \n"
<<"                                                                                   \n"
<<"  macro timerend(str1,t0){                                                           \n"
<<"    cout.scientific << \"finished in [ \"<< clock()-t0                            \n"
<<"      << \" ] seconds\\n\\n\";                                                   \n"
<<"  }//                                                                           \n"
<<"                                                                                   \n"
<<"                                                                                   \n";

} //-- [if loop terminator] timelog ended --//


if(Prblm=="elastodynamics" || Prblm=="soildynamics")if(!useGFP)writemacros
<<"                                                                                   \n"
<<"//------------------------------update macros---------------------------------//\n"
<<"                                                                                   \n"
<<"  macro updateVariables(du,uold,vold,aold,beta,gamma,dt){                           \n"
<<"                                                                                       \n"
<<"    fespace Vloc(Th,Pk)  ;                                                           \n"
<<"    Vloc def(aloc)       ;                                                           \n"
<<"                                                                                   \n"
<<"    for (int i=0; i< Vh.ndof; i++){                                                   \n"
<<"      aloc[][i] =   (du[][i]-uold[][i]-dt*vold[][i])/beta/(dt*dt)               \n"
<<"                  - (1.-2.*beta)/2./beta*aold[][i]                          ;   \n"
<<"      vold[][i] = vold[][i] + dt*((1.-gamma)*aold[][i] + gamma*aloc[][i])   ;   \n"
<<"      aold[][i]= aloc[][i]  ;                                                   \n"
<<"      uold[][i]= du[][i]    ;                                                   \n"
<<"    }                                                                           \n"
<<"  }//                                                                           \n"
<<"                                                                                   \n";


if(Prblm=="soildynamics"){writemacros
<<"                                                                                   \n"
<<"//----------------------Paraxial rotation macro-------------------------------//\n"
<<"                                                                                   \n";

if(spc==2)writemacros
<<"  macro PA0(i)                                                                    \n"
<<"        [ cp*(N.x*N.x*i + N.x*N.y*i#1) + cs*( N.y*N.y*i - N.x*N.y*i#1),           \n"
<<"          cp*(N.x*N.y*i + N.y*N.y*i#1) + cs*(-N.x*N.y*i + N.x*N.x*i#1)               \n"
<<"        ]//                                                                           \n";


if(spc==3)writemacros
<<"  macro PA0(i)                                                                    \n"
<<"        [ cp*(N.x*N.x*i + N.x*N.y*i#1 + N.x*N.z*i#2) + cs*( (1.-N.x*N.x)*i - N.x*N.y*i#1 - N.x*N.z*i#2)  ,           \n"
<<"          cp*(N.x*N.y*i + N.y*N.y*i#1 + N.y*N.z*i#2) + cs*(-N.x*N.y*i + (1.-N.y*N.y)*i#1 - N.y*N.z*i#2)  ,      \n"
<<"          cp*(N.x*N.z*i + N.y*N.z*i#1 + N.z*N.z*i#2) + cs*(-N.x*N.z*i - N.x*N.y*i#1 + (1.-N.z*N.z)*i#2)         \n"
<<"        ]//                                                                           \n";

if(Sequential)writemacros
<<"                                                                                   \n"
<<"//----------------------ParaView plotting macro-------------------------------//\n"
<<"                                                                                   \n"
<<"  macro exportBegin(name)                                                           \n"
//<<"    system(\"mkdir -p VTUs\");                                                   \n"
<<"    {ofstream pvd(name +\".pvd\");                                                      \n"
<<"      pvd << \"<?xml version=\\\"1.0\\\"?>\\n\";                                   \n"
<<"      pvd << \"<VTKFile type=\\\"Collection\\\" version=\\\"0.1\\\"\\n\";           \n"
<<"      pvd << \"         byte_order=\\\"LittleEndian\\\"\\n\";                   \n"
<<"      pvd << \"         compressor=\\\"vtkZLibDataCompressor\\\">\\n\";           \n"
<<"      pvd << \"  <Collection>\\n\";                                                    \n"
<<"    }//                                                                           \n"
<<"                                                                                   \n"
<<"                                                                                   \n"
<<"  macro exportEnd(name)                                                           \n"
<<"    {ofstream pvd(name +\".pvd\", append);                                           \n"
<<"    pvd << \"  </Collection>\\n\";                                                   \n"
<<"    pvd << \"</VTKFile>\\n\";}                                                   \n"
<<"    system(\"mv \"+name+\".pvd .\");                                                            \n"
<<"  //                                                                            \n"
<<"                                                                                   \n"
<<"                                                                                   \n"
<<"  macro exportTimeStep(name, mesh, sol, forder, iterno, ts, nam )                      \n"
<<"    savevtk(name+\"_\"+int(iterno)+\".vtu\",mesh,sol,order=forder,dataname=nam);\n"
<<"    ofstream pvd(name +\".pvd\", append);                                           \n"
<<"      pvd << \"    <DataSet timestep=\\\"\" + real(ts) + \"\\\"\\n\";           \n"
<<"      pvd << \"             file=\\\"\";                                           \n"
<<"      pvd << name << \"_\" << int(iterno) << \".vtu\\\"/>\\n\";                   \n"
<<"  //                                                                            \n"
<<"                                                                                   \n";
}

} //-- [ostream terminator]  macros.edp closed --//  

cout << " ................................... Done \n";

