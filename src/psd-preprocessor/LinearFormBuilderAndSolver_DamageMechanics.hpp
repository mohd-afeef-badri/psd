//=====================================================================================
// ------ Damage Mechanics for the LinearFormBuilderAndSolver.edp file ------ 
//=====================================================================================

if(Model=="hybrid-phase-field"){

if(Sequential)writesolver
<<"                                                                                \n"
<<"//==============================================================================\n"
<<"// ------- L_o calculation -------                                              \n"
<<"//==============================================================================\n"
<<"                                                                                \n"
<<"{                                                                               \n"
<<"  fespace  Vh0( Th , P0)    ;                                                   \n"
<<"  Vh0 size1 = hTriangle     ;                                                   \n"
<<"  lo = size1[].min          ;                                                   \n"
<<"  lo = lo*lfac              ;                                                   \n"
<<"}                                                                               \n";

/************************OLD METHOD*************************************************
if(pipegnu)if(!supercomp)writesolver
<<"                                                                                \n"
<<"  matrix  And                        ;        // PostProcessing                 \n";
if(vectorial)writesolver
<<"  Vh def(fr)                         ;        // Variables for force            \n"
<<"                                                                                \n"
<<"  int[int]  ldof( 1 )                        ;                                  \n"
<<"  ExtractDofBorderVectorial(2,Vh,ldof)        ;                                 \n"
<<"                                                                                \n";

if(!vectorial)writesolver
<<"  Vh def2(fr)                        ;        // Variables for force            \n"
<<"                                                                                \n"
<<"  int[int]  ldof( 1 )                ;                                          \n"
<<"  ExtractDofBorderP1(2,Vh,ldof)        ;                                        \n"
<<"                                                                                \n";
/************************OLD METHOD*************************************************/ 

if(!Sequential)writesolver
<<"                                                                                \n"
<<"//==============================================================================\n"
<<"// ------- L_o calculation in parallel -------                                  \n"
<<"//==============================================================================\n"
<<"                                                                                \n"
<<"{ real himlocal,himGlobal                                ;                      \n"
<<"  fespace Vh0(Th,P0)                                     ;                      \n"
<<"  Vh0 size1 = hTriangle                                  ;                      \n"
<<"  himlocal  = size1[].min                                ;                      \n"
<<"  mpiAllReduce(himlocal,himGlobal,mpiCommWorld,mpiMIN)   ;                      \n"
<<"  lo = himGlobal*lfac                                    ;                      \n"
<<"}                                                                               \n";


if(Sequential)if(NonLinearMethod=="Picard"){writesolver
<<"                                                                                \n"
<<"//==============================================================================\n"
<<"// ------- Traction loading loop -------                                        \n"
<<"//==============================================================================\n"
<<"                                                                                \n"
<<"while (tr <= maxtr){                                                            \n"
<<"                                                                                \n"
<<"  cout <<  \"-------------------------------------------------------\\n\"       \n"
<<"       <<  \"Applied traction \" << tr << \"\\n\" << endl;                      \n"
<<"                                                                                \n"
<<"  if (tr >= 5e-3)                                                               \n"
<<"    dtr = 1e-6;                                                                 \n"
<<"                                                                                \n"
<<"  //--------------------Assembly for linear----------------------//             \n"
<<"                                                                                \n"
<<(timelog ? "  timerbegin(\"RHS assembly for U\",t0)\n" : ""                        )
<<"  b = elast(0,Vh);                                                              \n"
<<(timelog ? "  timerend  (\"RHS assembly for U\",t0)\n" : ""                        )
<<"                                                                                \n"
<<"  //-----------------------Nonlinear loop------------------------//             \n"
<<"                                                                                \n"
<<"  for(int iter=0; iter<100; iter++){                                            \n"
<<"                                                                                \n"
<<"    //----------------Assembly for bilinear----------------------//             \n"
<<"                                                                                \n"
<<(timelog ? "    timerbegin(\"matrix assembly for U\",t0)\n" : ""                   )
<<"    A = elast(Vh,Vh,solver=CG,sym=1);                                           \n"
<<(timelog ? "    timerend  (\"matrix assembly for U\",t0)\n" : ""                   )
<<"                                                                                \n"
<<"    //-------------Linear system solving phase-------------------//             \n"
<<"                                                                                \n"
<<(timelog ? "    timerbegin(\"solving U\",t0)\n"         : ""                       )
<<"    set(A,solver=CG,sym=1);                                                     \n"
<<"    u[] = A^-1*b;                                                               \n"
<<(timelog ? "    timerend  (\"solving U\",t0)\n"         : ""                       );

if(energydecomp)writesolver
<<"                                                                                \n"
<<"    //---------------Energy decomposition phase-------------------//            \n"
<<"                                                                                \n"
<<(timelog ? "    timerbegin(\"energy decomposition\",t0)\n"         : ""           )
<<"    DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus)                 \n"
<<"    HistPlusP1=HistPlus; HistMinusP1=HistMinus;                                 \n"
<<(timelog ? "    timerend  (\"energy decomposition\",t0)\n"         : ""           );

writesolver
<<"                                                                                \n"
<<"    //----------------Assembly for bilinear----------------------//             \n"
<<"                                                                                \n"
<<(timelog ? "    timerbegin(\"matrix assembly for PHI\",t0)\n" : ""                 )
<<"    A1 = phase(Vh1,Vh1,solver=CG,sym=1);                                        \n"
<<(timelog ? "    timerend  (\"matrix assembly for PHI\",t0)\n" : ""                 )
<<"                                                                                \n"
<<"    //--------------------Assembly for linear----------------------//           \n"
<<"                                                                                \n"
<<(timelog ? "    timerbegin(\"RHS assembly for PHI\",t0)\n" : ""                    )
<<"    b1 = phase(0,Vh1);                                                          \n"
<<(timelog ? "    timerend  (\"RHS assembly for U\",t0)\n" : ""                      )
<<"                                                                                \n"
<<"    //-------------Linear system solving phase-------------------//             \n"
<<"                                                                                \n"
<<(timelog ? "    timerbegin(\"solving U\",t0)\n" : ""                               )
<<"    set(A1,solver=CG,sym=1);                                                    \n"
<<"    phi[] = A1^-1*b1;                                                           \n"
<<(timelog ? "    timerend  (\"solving U\",t0)\n" : ""                               )
<<"                                                                                \n";

if(energydecomp)writesolver
<<"    //-------------Hybrid phase-field condition-----------------//              \n"
<<"                                                                                \n"
<<(timelog ? "    MPItimerbegin(\"Phase-field condition\",t0)\n" : ""                )
<<"    for(int i=0; i < Vh1.ndof; i++ )                                            \n"
  "        if(HistPlusP1[][i]<HistMinusP1[][i])phi[][i]=0.;                        \n"
<<(timelog ? "    MPItimerend  (\"Phase-field condition\",t0)\n" : ""                )
<<"                                                                                \n";

writesolver
<<"    //------------------Error calculation------------------------//             \n"
<<"                                                                                \n"
<<(timelog ? "    timerbegin(\"NL error checking\",t0)\n" : ""                       )
<<"    uold[]    = uold[]-u[]                         ;                            \n"
<<"    phiold[]  = phiold[]-phi[]                     ;                            \n"
<<"    real err1 = sqrt( intN(Th,qforder=2) ( uold^2   )  )     ;                  \n"
<<"    real err2 = sqrt( intN(Th,qforder=2) ( phiold^2 )  )     ;                  \n"
<<(timelog ? "    timerend  (\"NL error checking\",t0)\n" : ""                       )
<<"                                                                                \n"
<<"    //--------------------Solution update-------------------------//            \n"
<<"                                                                                \n"
<<(timelog ? "    timerbegin(\"solution update\",t0)\n" : ""                         )
<<"    phiold[] = phi[]  ;                                                         \n"
<<"    uold[]   = u[]    ;                                                         \n"
<<(timelog ? "    timerend  (\"solution update\",t0)\n" : ""                         )
<<"                                                                                \n"
<<"    //--------------- Convergence conditional---------------------//            \n"
<<"                                                                                \n"
<<"    if(err1 < 1e-2 && err2 < 1e-2){                                             \n"
<<"                                                                                \n"
<<"      //------------------Screen output norm----------------------//            \n"
<<"                                                                                \n"
<<"      cout.scientific                                                           \n"
<<"      << \"NL iteration number :  [ \"      << iter                             \n"
<<"      << \" ]\\nL2 error in [u,phi] :  [ \"  << err1                            \n"
<<"      << \" , \" <<  err2 << \" ]\"           << endl;                          \n"
<<"                                                                                \n"
<<"      break;                                                                    \n"
<<"    }                                                                           \n"
<<"                                                                                \n"
<<"  }                                                                             \n";

if(pipegnu){writesolver
<<"                                                                                \n"
<<"  //-------------------Force calculation-----------------------//               \n"
<<"                                                                                \n"
<<(timelog ? "  timerbegin(\"force calculation\",t0)\n" : ""                         )
<<"  real forcetot  = 0.;                                                          \n"
<<"  forcetot = intN1(Th,qforder=2,2)(lambda*divergence(u)+2.*mu*dy(u1));          \n"
/************************OLD METHOD************************************************   
<<"      And = elastNoDirc(Vh,Vh);                                                 \n"
<<"      fr[] = And*u[];                                                           \n"
<<"                                                                                \n"
<<"      real forcetot  = 0. ;                                                     \n"
<<"      for(int i = 0; i < ldof.n; ++i)                                           \n"
<<"        forcetot = forcetot + fr1[][ldof[i]];                                   \n"
/************************OLD METHOD************************************************/
<<"  ofstream ff(\"force.data\",append);                                           \n"
<<"  ff << tr << \"        \" << forcetot*1e-3 << endl;                            \n";

if(!supercomp)writesolver
<<"  pgnuplot<<\"plot \\\"force.data\\\"u 1:2 w p pt 6 ps 2 t \\\"FEM\\\"\\n\";    \n"
//<<"    <<\",\\\"ambati.data\\\"u 1:2 w p pt 4 ps 2  t \\\"Ref\\\"\"              \n"
<<"  flush(pgnuplot);                                                              \n";

writesolver
<<(timelog ? "  timerend  (\"force calculation\",t0)\n" : ""                         );
}

if(plotAll)writesolver
<<"                                                                                \n"
<<"  //-------Paraview plotting every nth iteration -----------//                  \n"
<<"                                                                                \n"
<<"  iterout++;                                                                    \n"
<<"                                                                                \n"
<<(timelog ? "  timerbegin(\"ParaView post-processing\",t0)\n" : ""                 )
<<"  if(int(iterout%10)==0){                                                       \n"
<<"    string   namevtu=\"VTUs/Solution_\"+iterout1+\".vtu\";                      \n"
<<"    savevtk(     namevtu            ,                                           \n"
<<"                 Th                 ,                                           \n"
<<(spc==2 ? "\t\t [u,u1,0]\t\t,\n" : "\t\t [u,u1,u2]\t\t,\n"                        )
<<"                 phi                ,                                           \n"
<<"                 order=vtuorder     ,                                           \n"
<<"                 dataname=namedata                                              \n"
<<"          );                                                                    \n"
<<"                                                                                \n"
<<"    iterout1++;                                                                 \n"
<<"    }                                                                           \n"
<<(timelog ? "  timerend  (\"ParaView post-processing\",t0)\n" : ""                 );

if(debug)writesolver
<<"                                                                                \n"
<<"  //-----------------Debug glut plotting----------------------//                \n"
<<"                                                                                \n"
<<"  plot(phi,fill=1,value=1);                                                     \n";

writesolver
<<"                                                                                \n"
<<"  //-----------------updating traction----------------//                        \n"
<<"                                                                                \n"
<<"  tr += dtr;                                                                    \n"
<<"}                                                                               \n"
<<"                                                                                \n"
<<(timelog ? "timerend  (\"solver\",t1)\n" : " "                                    )
<<"                                                                                \n"
<<"//-------------------------------THE END------------------------------//        \n"; 
}  //-- [if loop terminator] Sequential ended --//



if(Sequential)if(NonLinearMethod=="Newton-Raphson"){writesolver
<<"                                                                                \n"
<<"  real TractionTotal=tr;                                                        \n"
<<"                                                                                \n"
<<"//==============================================================================\n"
<<"// ------- Traction loading loop -------                                        \n"
<<"//==============================================================================\n"
<<"                                                                                \n"
<<"while (TractionTotal <= maxtr){                                                 \n"
<<"                                                                                \n"
<<"  cout <<  \"-------------------------------------------------------\\n\"       \n"
<<"       <<  \"Applied traction \" << TractionTotal << \"\\n\" << endl;           \n"
<<"                                                                                \n"
<<"  if (TractionTotal >= 5e-3){                                                   \n"
<<"    tr = 1e-6; dtr = 1e-6;}                                                     \n"
<<"  //-----------------------Nonlinear loop------------------------//             \n"
<<"                                                                                \n"
<<"  for(int iter=0; iter<100; iter++){                                            \n"
<<"                                                                                \n"
<<"  //--------------------Assembly for linear----------------------//             \n"
<<"                                                                                \n"
<<(timelog ? "  timerbegin(\"RHS assembly for U\",t0)\n" : ""                       )
<<"    b = elast(0,Vh);                                                            \n"
<<(timelog ? "  timerend  (\"RHS assembly for U\",t0)\n" : ""                       )
<<"                                                                                \n"
<<"    //----------------Assembly for bilinear----------------------//             \n"
<<"                                                                                \n"
<<(timelog ? "    timerbegin(\"matrix assembly for U\",t0)\n" : ""                  )
<<"    A = elast(Vh,Vh,solver=CG,sym=1);                                           \n"
<<(timelog ? "    timerend  (\"matrix assembly for U\",t0)\n" : ""                  )
<<"                                                                                \n"
<<"    //-------------Linear system solving phase-------------------//             \n"
<<"                                                                                \n"
<<(timelog ? "    timerbegin(\"solving U\",t0)\n"         : ""                      )
<<"    set(A,solver=CG,sym=1);                                                     \n"
<<"    du[] = A^-1*b;                                                              \n"
<<(timelog ? "    timerend  (\"solving U\",t0)\n"         : ""                      )
<<"                                                                                \n"
<<"    //--------------Update of displacement u---------------------//             \n"
<<"                                                                                \n"
<<(timelog ? "    timerbegin(\"Updating U\",t0)\n"         : ""                     )
<<"    u[] += du[];                                                                \n"
<<(timelog ? "    timerend  (\"Updating U\",t0)\n"         : ""                     )
<<"                                                                                \n";

if(energydecomp)writesolver
<<"                                                                                \n"
<<"    //---------------Energy decomposition phase-------------------//            \n"
<<"                                                                                \n"
<<(timelog ? "    timerbegin(\"energy decomposition\",t0)\n"         : ""           )
<<"    DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus)                 \n"
<<"    HistPlusP1=HistPlus; HistMinusP1=HistMinus;                                 \n"
<<(timelog ? "    timerend  (\"energy decomposition\",t0)\n"         : ""           );

writesolver
<<"                                                                                \n"
<<"    //----------------Assembly for bilinear----------------------//             \n"
<<"                                                                                \n"
<<(timelog ? "    timerbegin(\"matrix assembly for PHI\",t0)\n" : ""                )
<<"    A1 = phase(Vh1,Vh1,solver=CG,sym=1);                                        \n"
<<(timelog ? "    timerend  (\"matrix assembly for PHI\",t0)\n" : ""                )
<<"                                                                                \n"
<<"    //--------------------Assembly for linear----------------------//           \n"
<<"                                                                                \n"
<<(timelog ? "    timerbegin(\"RHS assembly for PHI\",t0)\n" : ""                   )
<<"    b1 = phase(0,Vh1);                                                          \n"
<<(timelog ? "    timerend  (\"RHS assembly for U\",t0)\n" : ""                     )
<<"                                                                                \n"
<<"    //-------------Linear system solving phase-------------------//             \n"
<<"                                                                                \n"
<<(timelog ? "    timerbegin(\"solving U\",t0)\n" : ""                              )
<<"    set(A1,solver=CG,sym=1);                                                    \n"
<<"    dphi[] = A1^-1*b1;                                                          \n"
<<(timelog ? "    timerend  (\"solving U\",t0)\n" : ""                              )
<<"                                                                                \n"
<<"    //--------------Update of phase-field phi-------------------//              \n"
<<"                                                                                \n"
<<(timelog ? "    timerbegin(\"Updating U\",t0)\n"         : ""                     )
<<"    phi[] += dphi[];                                                            \n"
<<(timelog ? "    timerend  (\"Updating U\",t0)\n"         : ""                     )
<<"                                                                                \n";

if(energydecomp)writesolver
<<"    //-------------Hybrid phase-field condition-----------------//                   \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"Phase-field condition\",t0)\n" : ""                      )
<<"    for(int i=0; i < Vh1.ndof; i++ )                                            \n"
  "        if(HistPlusP1[][i]<HistMinusP1[][i])phi[][i]=0.;                            \n"
<<(timelog ? "    MPItimerend  (\"Phase-field condition\",t0)\n" : ""                      )
<<"                                                                                   \n";

writesolver
<<"    //------------------Error calculation------------------------//                   \n"
<<"                                                                                   \n"
<<(timelog ? "    timerbegin(\"NL error checking\",t0)\n" : ""                                      )
<<"    real err1 = sqrt( intN(Th,qforder=2) ( du^2   )  )     ;                           \n"
<<"    real err2 = sqrt( intN(Th,qforder=2) ( dphi^2 )  )     ;                           \n"
<<(timelog ? "    timerend  (\"NL error checking\",t0)\n" : ""                                      )
<<"                                                                                   \n"
<<"    //--------------- Convergence conditional---------------------//                     \n"
<<"                                                                                   \n"
<<"    if(err1 < 1e-2 && err2 < 1e-2){                                                   \n"
<<"                                                                                   \n"
<<"      //------------------Screen output norm----------------------//             \n"
<<"                                                                                   \n"
<<"      cout.scientific                                                            \n"
<<"      << \"NL iteration number :  [ \"      << iter                                          \n"
<<"      << \" ]\\nL2 error in [u,phi] :  [ \"  << err1                             \n"
<<"      << \" , \" <<  err2 << \" ]\"           << endl;                            \n"
<<"                                                                                   \n"
<<"      break;                                                                              \n"
<<"    }                                                                           \n"
<<"                                                                                   \n"
<<"    TractionIn = 0;                                                                   \n"
<<"  }                                                                                    \n"
<<"                                                                                   \n"
<<"  //-----------------updating traction----------------//                           \n"
<<"                                                                                   \n"
<<"    TractionIn     = tr;                                                                \n"
<<"    TractionTotal += dtr;                                                           \n";

if(pipegnu){writesolver
<<"                                                                                   \n"
<<"  //-------------------Force calculation-----------------------//                      \n"
<<"                                                                                   \n"
<<(timelog ? "  timerbegin(\"force calculation\",t0)\n" : ""                            )
<<"  real forcetot  = 0.;                                                           \n"
<<"  forcetot = intN1(Th,qforder=2,2)(lambda*divergence(u)+2.*mu*dy(u1));           \n"
<<"  ofstream ff(\"force.data\",append);                                             \n"
<<"  ff << TractionTotal << \"        \" << forcetot*1e-3 << endl;                              \n";

if(!supercomp)writesolver
<<"  pgnuplot<<\"plot \\\"force.data\\\"u 1:2 w p pt 6 ps 2 t \\\"FEM\\\"\\n\";           \n"
<<"  flush(pgnuplot);                                                                            \n";

writesolver
<<(timelog ? "  timerend  (\"force calculation\",t0)\n" : ""                            );
}

if(plotAll)writesolver
<<"                                                                                   \n"
<<"  //-------Paraview plotting every nth iteration -----------//                        \n"
<<"                                                                                   \n"
<<"  iterout++;                                                                           \n"
<<"                                                                                   \n"
<<(timelog ? "  timerbegin(\"ParaView post-processing\",t0)\n" : ""                 )
<<"  if(int(iterout%10)==0){                                                              \n"
<<"    string   namevtu=\"VTUs/Solution_\"+iterout1+\".vtu\";                              \n"
<<"    savevtk(     namevtu            ,                                            \n"
<<"                 Th                 ,                                              \n"
<<(spc==2 ? "\t\t [u,u1,0]\t\t,\n" : "\t\t [u,u1,u2]\t\t,\n"                                    )
<<"                 phi                ,                                              \n"
<<"                 order=vtuorder     ,                                              \n"
<<"                 dataname=namedata                                                        \n"
<<"          );                                                                                           \n"
<<"                                                                                   \n"
<<"    iterout1++;                                                                   \n"
<<"    }                                                                           \n"
<<(timelog ? "  timerend  (\"ParaView post-processing\",t0)\n" : ""                        );

if(debug)writesolver
<<"                                                                                   \n"
<<"  //-----------------Debug glut plotting----------------------//                     \n"
<<"                                                                                   \n"
<<"  plot(phi,fill=1,value=1);                                                             \n";

writesolver
<<"                                                                                   \n"
<<"}                                                                                   \n"
<<"                                                                                   \n"
<<(timelog ? "timerend  (\"solver\",t1)\n" : " "                                       )
<<"                                                                                   \n"
<<"//-------------------------------THE END------------------------------//           \n"; 
}  //-- [if loop terminator] Sequential ended --//

if(!Sequential)if(NonLinearMethod=="Picard"){writesolver
<<"                                                                                   \n"
<<"//==============================================================================\n"
<<"// -------  Traction loading loop  -------                                           \n"
<<"//==============================================================================\n"
<<"                                                                                   \n"
<<"while (tr <= maxtr){                                                                   \n"
<<"                                                                                   \n"
<<"  if(mpirank==0)                                                                   \n"
<<"  cout.scientific<<\"-----------------------------------------------------\\n\" \n"
<<"  <<  \"Applied traction \" << tr << \"\\n\" << endl;                              \n"
<<"                                                                                   \n"
<<"  if (tr >= 5e-3)                                                                   \n"
<<"    dtr = 1e-6;                                                                   \n"
<<"                                                                                   \n"
<<"  //--------------------Assembly for linear----------------------//                   \n"
<<"                                                                                   \n"
<<(timelog ? "  MPItimerbegin(\"RHS assembly for U\",t0)\n" : ""                           )
<<"  b = elast(0,Vh);                                                                    \n"
<<(timelog ? "  MPItimerend  (\"RHS assembly for U\",t0)\n" : ""                             )
<<"                                                                                   \n"
<<"  //-----------------------Nonlinear loop------------------------//                   \n"
<<"                                                                                   \n"
<<"  for(int iter=0; iter<100; iter++){                                                      \n"
<<"                                                                                   \n"
<<"    //----------------Assembly for bilinear----------------------//                    \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"matrix assembly for U\",t0)\n" : ""                     )
<<"    ALoc = elast(Vh,Vh,solver=CG,sym=1);                                             \n"
<<(timelog ? "    MPItimerend  (\"matrix assembly for U\",t0)\n" : ""                      )
<<"                                                                                   \n"
<<"    //-----------PETSc assembly for bilinear---------------------//                   \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"PETSc assembly for U\",t0)\n" : ""                       )
<<"    changeOperator(A, ALoc);                                                                 \n"
<<"    set(A,sparams =\"  -ksp_type cg  \");                                              \n"
<<(timelog ? "    MPItimerend  (\"PETSc assembly for U\",t0)\n" : ""                         )
<<"                                                                                   \n"
<<"    //-------------Linear system solving phase-------------------//                   \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"solving U\",t0)\n" : " "                               )
<<"    u[] = A^-1*b;                                                                    \n"
<<(timelog ? "    MPItimerend  (\"solving U\",t0)\n" : " "                                 );

if(!vectorial){
if(energydecomp)writesolver
<<"                                                                                   \n"
<<"    //---------------Energy decomposition phase-------------------//                     \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"energy decomposition\",t0)\n" : ""                       )
<<"    DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus);                   \n"
<<"    HistPlusP1=HistPlus; HistMinusP1=HistMinus;                                 \n"
<<(timelog ? "    MPItimerend  (\"energy decomposition\",t0)\n" : ""                         );

writesolver
<<"                                                                                   \n"
<<"    //----------------Assembly for bilinear----------------------//                    \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"matrix assembly for PHI\",t0)\n" : ""                    )
<<"    ALoc1 = phase(Vh1,Vh1,solver=CG,sym=1);                                              \n"
<<(timelog ? "    MPItimerend  (\"matrix assembly PHI\",t0)\n" : ""                          )
<<"                                                                                   \n"
<<"    //----------------Assembly for linear------------------------//                    \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"RHS assembly for PHI\",t0)\n" : ""                       )
<<"    b1 = phase(0,Vh1);                                                              \n"
<<(timelog ? "    MPItimerend  (\"RHS assembly for PHI\",t0)\n" : ""                       )
<<"                                                                                   \n"
<<"    //-----------PETSc assembly for bilinear---------------------//                   \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"PETSc assembly for PHI\",t0)\n" : ""                     )
<<"    changeOperator(A1, ALoc1);                                                     \n"
<<"    set(A1,sparams =\"  -ksp_type cg  \");                                              \n"
<<(timelog ? "    MPItimerend  (\"PETSc assembly for PHI\",t0)\n" : ""                     )
<<"                                                                                   \n"
<<"    //-------------Linear system solving phase-------------------//                   \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"solving PHI\",t0)\n" : ""                                       )
<<"    phi[] = A1^-1*b1;                                                                \n"
<<(timelog ? "    MPItimerend  (\"solving PHI\",t0)\n" : ""                                 )
<<"                                                                                   \n";

if(energydecomp)writesolver
<<"    //-------------Hybrid phase-field condition-----------------//                   \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"Phase-field condition\",t0)\n" : ""                      )
<<"    for(int i=0; i < Vh1.ndof; i++ )                                            \n"
  "        if(HistPlusP1[][i]<HistMinusP1[][i])phi[][i]=0.;                            \n"
<<(timelog ? "    MPItimerend  (\"Phase-field condition\",t0)\n" : ""                      )
<<"                                                                                   \n";

writesolver
<<"    //------------------Error calculation------------------------//                   \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"NL error checking\",t0)\n" : ""                            )
<<"    uold[]   = uold[]-u[]                ;                                           \n"
<<"    phiold[] = phiold[]-phi[]        ;                                            \n"
<<"    real err1Gather,err2Gather;                                                   \n"
<<"    real err1Loc=sqrt( intN(Th,qforder=2) ( DPspc*(uold)^2   )  );                   \n"
<<"    real err2Loc=sqrt( intN(Th,qforder=2) ( DZspc*(phiold)^2 )  );                   \n"
<<"    mpiAllReduce(err1Loc,err1Gather,mpiCommWorld,mpiSUM);                           \n"
<<"    mpiAllReduce(err2Loc,err2Gather,mpiCommWorld,mpiSUM);                           \n"
<<(timelog ? "    MPItimerend (\"NL error checking\",t0)\n" : ""                            )
<<"                                                                                   \n"
<<"    //--------------------Solution update-------------------------//                   \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"solution update\",t0)\n" : ""                            )
<<"    phiold[]=phi[];                                                                      \n"
<<"    uold[]=u[];                                                                      \n"
<<(timelog ? "    MPItimerend (\"solution update\",t0)\n" : ""                                    )
<<"                                                                                   \n"
<<"    //--------------- Convergence conditional---------------------//                     \n"
<<"                                                                                   \n"
<<"    if(err1Gather < 1e-2 && err2Gather < 1e-2){                                      \n";
}

if(vectorial){writesolver
<<"                                                                                   \n"
<<"    //------------------Error calculation------------------------//                   \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"NL error checking\",t0)\n" : ""                            )
<<"    uold[]   = uold[]-u[]                                          ;                   \n"
<<"    real err1Gather                                                ;                   \n"
<<"    real err1Loc=sqrt( intN(Th,qforder=2) ( DPspc*(uold)^2 )  )    ;                   \n"
<<"    mpiAllReduce(err1Loc,err1Gather,mpiCommWorld,mpiSUM)           ;                   \n"
<<(timelog ? "    MPItimerend (\"NL error checking\",t0)\n" : ""                            )
<<"                                                                                   \n"
<<"    //--------------------Solution update-------------------------//                   \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"solution update\",t0)\n" : ""                            )
<<"    uold[] = u[];                                                                      \n"
<<(timelog ? "    MPItimerend (\"solution update\",t0)\n" : ""                                    );

if(energydecomp)writesolver
<<"                                                                                   \n"
<<"    //---------------Energy decomposition phase-------------------//                     \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"energy decomposition\",t0)\n" : ""                       )
<<"    DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus);                   \n"
<<"    HistPlusP1=HistPlus; HistMinusP1=HistMinus;                                 \n"
<<(timelog ? "    MPItimerend  (\"energy decomposition\",t0)\n" : ""                         );

writesolver
<<"                                                                                   \n"
<<"    //--------------- Convergence conditional---------------------//                     \n"
<<"                                                                                   \n"
<<"    if(err1Gather < 1e-2){                                                              \n";

}  //-- [if loop terminator] vectorial ended --//


/************************OLD METHOD*************************************************
if(pipegnu){writesolver
<<"                                                                                   \n"
<<"      //-------------------Force calculation-----------------------//           \n"
<<"                                                                                   \n"
<<"        And = elastNoDirc(Vh,Vh);                                                   \n"
<<"        changeOperator(A2, And);                                                   \n"
<<"        fr[] = And*u[];                                                                   \n"
<<"                                                                                   \n"
<<"        fr[] .*= DP;                                                                   \n"
<<"                                                                                   \n"
<<"        real forcetot  = 0.,forcetotGath  = 0. ;                                   \n"
<<"                for(int i = 0; i < ldof.n; ++i)                                           \n"
<<"                forcetot = forcetot + fr1[][ldof[i]];                                   \n"
<<"                                                                                   \n"
/************************OLD METHOD*************************************************/

if(!vectorial)writesolver
<<"                                                                                   \n"
<<"      //------------------Screen output norm----------------------//             \n"
<<"                                                                                   \n"
<<"      if(mpirank==0)                                                                         \n"
<<"      cout.scientific << \"NL iteration number :  [ \"  << iter                       \n"
<<"      << \" ]\\nL2 error in [u,phi] :  [ \"    << err1Gather                      \n"
<<"      << \" , \" <<  err2Gather << \" ]\"      << endl;                              \n"
<<"                                                                                   \n";

if(vectorial)writesolver
<<"                                                                                   \n"
<<"      //------------------Screen output norm----------------------//             \n"
<<"                                                                                   \n"
<<"      if(mpirank==0)                                                                         \n"
<<"      cout.scientific << \"NL iteration number :  [ \" << iter                       \n"
<<"      << \" ]\\nL2  error  in  [U]  :  [ \" << err1Gather << \" ]\" <<endl;           \n";

writesolver
<<"                                                                                   \n"
<<"      break;                                                                           \n"
<<"    }                                                                           \n"
<<"  }                                                                                      \n";


if(pipegnu){writesolver
<<"                                                                                   \n"
<<"  //-------------------Force calculation-----------------------//                      \n"
<<"                                                                                   \n"
<<(timelog ? "  MPItimerbegin(\"force calculation\",t0)\n" : ""                       )
<<"  real forcetot  = 0., forcetotGath  = 0. ;                                              \n"
<<"  forcetot=intN1(Th,qforder=2,2)(DPspc*(lambda*divergence(u)+2.*mu*dy(u1)));           \n"
<<"  mpiAllReduce(forcetot,forcetotGath,mpiCommWorld,mpiSUM);                              \n"
<<"  if(mpirank==0){                                                                      \n"
<<"  ofstream ff(\"force.data\",append);                                           \n"
<<"  ff << tr << \"        \" << forcetotGath*1e-3 << endl;                              \n";

if(!supercomp)writesolver
<<"  pgnuplot<<\"plot \\\"force.data\\\" u 1:2 w lp pt 6 ps 2 t \\\"FEM\\\"\\n\";  \n"
//<<"      <<\",\\\"ambati.data\\\"u 1:2 w p pt 4 ps 2  t \\\"Ref\\\"\"              \n"
<<"  flush(pgnuplot);                                                                         \n";

writesolver
<<"  }                                                                                       \n"
<<(timelog ? "  MPItimerend  (\"force calculation\",t0)\n" : ""                       );

}  //-- [if loop terminator] !pipegnu ended --//

if(plotAll)if(!vectorial){writesolver
<<"                                                                                   \n"
<<"  //-------Paraview plotting every nth iteration -----------//                        \n"
<<"                                                                                   \n"
<<"  iterout++;                                                                           \n"
<<"                                                                                   \n"
<<(timelog ? "  MPItimerbegin(\"ParaView post-processing\",t0)\n" : ""              )
<<"  if(int(iterout%10)==0){                                                           \n";


writesolver            
<<"    savevtk(  \"VTUs/Solution.vtu\"   ,                                            \n"
<<"                 Th                 ,                                              \n";

if(PostProcess!="u" & PostProcess!="phi")writesolver
<<(spc==2 ? "\t\t [u,u1,0]\t    ,\n" : "\t\t [u,u1,u2]\t    ,\n"                        )
<<"                 phi                ,                                              \n";


if(PostProcess=="u")writesolver
<<(spc==2 ? "\t\t [u,u1,0]\t    ,\n" : "\t\t [u,u1,u2]\t    ,\n"                        );

if(PostProcess=="phi")writesolver
<<"                 phi                ,                                              \n";

if(PostProcess=="uphi")writesolver
<<(spc==2 ? "\t\t [u,u1,0]\t    ,\n" : "\t\t [u,u1,u2]\t    ,\n"                        )
<<"                 phi                ,                                              \n";

writesolver
<<"                 order=vtuorder     ,                                              \n"
<<"                 dataname=\"U  d\"    ,                                              \n"
<<"                 append=true                                                             \n"
<<"              );                                                                             \n";

writesolver
<<"                                                                                   \n"
<<"    iterout1++;                                                                   \n"
<<"  }                                                                                     \n"
<<(timelog ? "  MPItimerend  (\"ParaView post-processing\",t0)\n" : ""               );
}

if(plotAll)if(vectorial){writesolver
<<"                                                                                   \n"
<<"  //--------Paraview plotting every nth iteration ----------//                        \n"
<<"                                                                                   \n"
<<"  iterout++;                                                                              \n"
<<"                                                                                   \n"
<<(timelog ? "  MPItimerbegin(\"ParaView post-processing\",t0)\n" : ""              )
<<"                                                                                   \n"
<<"  if(int(iterout%10)==0){                                                            \n"
<<"                                                                                   \n"
<<"    fespace Vhplot(Th,P1); Vhplot phi=u2;              //interpolation for phi  \n";

writesolver                   
<<"    savevtk(  \"VTUs/Solution.vtu\"   ,                                            \n"
<<"                 Th                 ,                                              \n";

if(PostProcess!="u" & PostProcess!="phi")writesolver
<<(spc==2 ? "\t\t [u,u1,0]\t    ,\n" : "\t\t [u,u1,u2]\t    ,\n"                        )
<<"                 phi                ,                                              \n";


if(PostProcess=="u")writesolver
<<(spc==2 ? "\t\t [u,u1,0]\t    ,\n" : "\t\t [u,u1,u2]\t    ,\n"                        );

if(PostProcess=="phi")writesolver
<<"                 phi                ,                                              \n";

if(PostProcess=="uphi")writesolver
<<(spc==2 ? "\t\t [u,u1,0]\t    ,\n" : "\t\t [u,u1,u2]\t    ,\n"                        )
<<"                 phi                ,                                              \n";

writesolver
<<"                 order=vtuorder     ,                                              \n"
<<"                 dataname=\"U  d\"    ,                                              \n"
<<"                 append=true                                                             \n"
<<"              );                                                                             \n";


writesolver
<<"                                                                                   \n"
<<"    iterout1++;                                                                   \n"
<<"  }                                                                                   \n"
<<(timelog ? "  MPItimerend  (\"ParaView post-processing\",t0)\n" : ""               );
}

if(debug)if(!vectorial)writesolver
<<"                                                                                   \n"
<<"  //-----------------Debug glut plotting----------------------//                      \n"
<<"                                                                                   \n"
<<"  plotMPI(Th, phi, P1,  def, real, wait=0, cmm=\"Tr-\"+tr+\"\")                      \n";

if(debug)if(vectorial)writesolver
<<"                                                                                   \n"
<<"  //-----------------Debug glut plotting----------------------//                       \n"
<<"                                                                                   \n"
<<"  plotMPI(Th, u"<<spc<<", P1,  def0, real, wait=0, cmm=\"Tr-\"+tr+\"\")           \n";

writesolver
<<"                                                                                   \n"
<<"  //-----------------updating traction----------------//                           \n"
<<"                                                                                   \n"
<<"  tr += dtr;                                                                           \n"
<<"}                                                                                   \n"
<<"                                                                                   \n"
<<(timelog ? "if(mpirank==0)\n" : " "                                                           )
<<(timelog ? "cout << \" all operations ended, they \";\n" : ""                        )
<<(timelog ? "MPItimerend  (\"solver\",t1)\n" : " "                                       )
<<"                                                                                   \n"
<<"//-------------------------------THE END------------------------------//           \n"; 

}  //-- [if loop terminator] !Sequential ended --//

if(!Sequential)if(NonLinearMethod=="Newton-Raphson"){writesolver
<<"                                                                                   \n"
<<"real TractionTotal=tr;                                                           \n"
<<"                                                                                   \n"
<<"//==============================================================================\n"
<<"// -------  Traction loading loop  -------                                           \n"
<<"//==============================================================================\n"
<<"                                                                                   \n"
<<"while (TractionTotal <= maxtr){                                                   \n"
<<"                                                                                   \n"
<<"  if(mpirank==0)                                                                   \n"
<<"  cout.scientific<<\"-----------------------------------------------------\\n\" \n"
<<"  <<  \"Applied traction \" << TractionTotal << \"\\n\" << endl;                     \n"
<<"                                                                                   \n"
<<"  if (TractionTotal >= 5e-3){                                                   \n"
<<"    tr = 1e-6; dtr = 1e-6;}                                                           \n"
<<"                                                                                   \n"
<<"  //-----------------------Nonlinear loop------------------------//                   \n"
<<"                                                                                   \n"
<<"  for(int iter=0; iter<100; iter++){                                                      \n"
<<"                                                                                   \n"
<<"    //--------------------Assembly for linear----------------------//           \n"
<<"                                                                                   \n"
<<(timelog ? "  MPItimerbegin(\"RHS assembly for U\",t0)\n" : ""                           )
<<"    b = elast(0,Vh);                                                                    \n"
<<(timelog ? "  MPItimerend  (\"RHS assembly for U\",t0)\n" : ""                             )
<<"                                                                                   \n"
<<"    //----------------Assembly for bilinear----------------------//                    \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"matrix assembly for U\",t0)\n" : ""                     )
<<"    ALoc = elast(Vh,Vh,solver=CG,sym=1);                                             \n"
<<(timelog ? "    MPItimerend  (\"matrix assembly for U\",t0)\n" : ""                      )
<<"                                                                                   \n"
<<"    //-----------PETSc assembly for bilinear---------------------//                   \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"PETSc assembly for U\",t0)\n" : ""                       )
<<"    changeOperator(A, ALoc);                                                                 \n"
<<"    set(A,sparams =\"  -ksp_type cg  \");                                              \n"
<<(timelog ? "    MPItimerend  (\"PETSc assembly for U\",t0)\n" : ""                         )
<<"                                                                                   \n"
<<"    //-------------Linear system solving phase-------------------//                   \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"solving U\",t0)\n" : " "                               )
<<"    du[] = A^-1*b;                                                                    \n"
<<(timelog ? "    MPItimerend  (\"solving U\",t0)\n" : " "                                 )
<<"                                                                                   \n"
<<"    //--------------Update of displacement u---------------------//                   \n"
<<"                                                                                   \n"
<<(timelog ? "    timerbegin(\"Updating U\",t0)\n"         : ""                       )
<<"    u[] += du[];                                                                   \n"
<<(timelog ? "    timerend  (\"Updating U\",t0)\n"         : ""                       )
<<"                                                                                   \n";

if(!vectorial){
if(energydecomp)writesolver
<<"                                                                                   \n"
<<"    //---------------Energy decomposition phase-------------------//                     \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"energy decomposition\",t0)\n" : ""                       )
<<"    DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus);                   \n"
<<"    HistPlusP1=HistPlus; HistMinusP1=HistMinus;                                 \n"
<<(timelog ? "    MPItimerend  (\"energy decomposition\",t0)\n" : ""                         );

writesolver
<<"                                                                                   \n"
<<"    //----------------Assembly for bilinear----------------------//                    \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"matrix assembly for PHI\",t0)\n" : ""                    )
<<"    ALoc1 = phase(Vh1,Vh1,solver=CG,sym=1);                                              \n"
<<(timelog ? "    MPItimerend  (\"matrix assembly PHI\",t0)\n" : ""                          )
<<"                                                                                   \n"
<<"    //----------------Assembly for linear------------------------//                    \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"RHS assembly for PHI\",t0)\n" : ""                       )
<<"    b1 = phase(0,Vh1);                                                              \n"
<<(timelog ? "    MPItimerend  (\"RHS assembly for PHI\",t0)\n" : ""                       )
<<"                                                                                   \n"
<<"    //-----------PETSc assembly for bilinear---------------------//                   \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"PETSc assembly for PHI\",t0)\n" : ""                     )
<<"    changeOperator(A1, ALoc1);                                                     \n"
<<"    set(A1,sparams =\"  -ksp_type cg  \");                                              \n"
<<(timelog ? "    MPItimerend  (\"PETSc assembly for PHI\",t0)\n" : ""                     )
<<"                                                                                   \n"
<<"    //-------------Linear system solving phase-------------------//                   \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"solving PHI\",t0)\n" : ""                                       )
<<"    dphi[] = A1^-1*b1;                                                                \n"
<<(timelog ? "    MPItimerend  (\"solving PHI\",t0)\n" : ""                                 )
<<"                                                                                   \n"
<<"    //--------------Update of phase-field phi-------------------//                   \n"
<<"                                                                                   \n"
<<(timelog ? "    timerbegin(\"Updating U\",t0)\n"         : ""                       )
<<"    phi[] += dphi[];                                                                   \n"
<<(timelog ? "    timerend  (\"Updating U\",t0)\n"         : ""                       )
<<"                                                                                   \n";

if(energydecomp)writesolver
<<"    //-------------Hybrid phase-field condition-----------------//                   \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"Phase-field condition\",t0)\n" : ""                      )
<<"    for(int i=0; i < Vh1.ndof; i++ )                                            \n"
  "        if(HistPlusP1[][i]<HistMinusP1[][i])phi[][i]=0.;                            \n"
<<(timelog ? "    MPItimerend  (\"Phase-field condition\",t0)\n" : ""                      )
<<"                                                                                   \n";

/******************************  Old Method **********************************************
writesolver
<<"    //------------------Error calculation------------------------//                   \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"NL error checking\",t0)\n" : ""                            )
<<"    real err1Gather,err2Gather;                                                   \n"
<<"    real err1Loc=sqrt( intN(Th,qforder=2) ( DPspc*(du)^2   )  );                   \n"
<<"    real err2Loc=sqrt( intN(Th,qforder=2) ( DZspc*(dphi)^2 )  );                   \n"
<<"    mpiAllReduce(err1Loc,err1Gather,mpiCommWorld,mpiSUM);                           \n"
<<"    mpiAllReduce(err2Loc,err2Gather,mpiCommWorld,mpiSUM);                           \n"
<<(timelog ? "    MPItimerend (\"NL error checking\",t0)\n" : ""                            )
<<"                                                                                   \n"
<<"    //--------------- Convergence conditional---------------------//               \n"
<<"                                                                                   \n"
<<"    if(err1Gather < 1e-2 && err2Gather < 1e-2){                                    \n";
/******************************************************************************************/

writesolver
<<"    //------------------Error calculation------------------------//                \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"NL error checking\",t0)\n" : ""                      )
<<"    real err1Gather,err2Gather, err1Loc, err2Loc;                                  \n"
<<"                                                                                   \n"
<<"        b = b .* DP					 ;                            \n"			 
<<"        err1Loc = b.l2 				 ;                            \n"			   
<<"        err1Loc = err1Loc*err1Loc 			 ;                            \n"			   
<<"        mpiAllReduce(err1Loc,err1Gather,mpiCommWorld,mpiSUM)  ;                    \n"			   
<<"        err1Gather = sqrt(err1Gather) 				 ;            \n"
<<"                                                                                   \n"       
<<"        b1 = b1 .* DZ					 ;                    \n"			 
<<"        err2Loc = b1.l2 				 ;                            \n"			   
<<"        err2Loc = err2Loc*err2Loc 			 ;			      \n"
<<"        mpiAllReduce(err2Loc,err2Gather,mpiCommWorld,mpiSUM)  ;                    \n"			   
<<"        err1Gather = sqrt(err2Gather) 				 ;            \n"
<<"                                                                                   \n"       	
<<(timelog ? "    MPItimerend (\"NL error checking\",t0)\n" : ""                       )
<<"                                                                                   \n"
<<"    //--------------- Convergence conditional---------------------//               \n"
<<"                                                                                   \n"
<<"    if(err1Gather < 1e-2 && err2Gather < 1e-2){                                    \n";


}

if(vectorial){writesolver
<<"                                                                                   \n"
<<"    //------------------Error calculation------------------------//                   \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"NL error checking\",t0)\n" : ""                            )
<<"    uold[]   = uold[]-u[]                                          ;                   \n"
<<"    real err1Gather                                                ;                   \n"
<<"    real err1Loc=sqrt( intN(Th,qforder=2) ( DPspc*(uold)^2 )  )    ;                   \n"
<<"    mpiAllReduce(err1Loc,err1Gather,mpiCommWorld,mpiSUM)           ;                   \n"
<<(timelog ? "    MPItimerend (\"NL error checking\",t0)\n" : ""                            )
<<"                                                                                   \n"
<<"    //--------------------Solution update-------------------------//                   \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"solution update\",t0)\n" : ""                            )
<<"    uold[] = u[];                                                                      \n"
<<(timelog ? "    MPItimerend (\"solution update\",t0)\n" : ""                                    );

if(energydecomp)writesolver
<<"                                                                                   \n"
<<"    //---------------Energy decomposition phase-------------------//                     \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"energy decomposition\",t0)\n" : ""                       )
<<"    DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus);                   \n"
<<"    HistPlusP1=HistPlus; HistMinusP1=HistMinus;                                 \n"
<<(timelog ? "    MPItimerend  (\"energy decomposition\",t0)\n" : ""                         );

writesolver
<<"                                                                                   \n"
<<"    //--------------- Convergence conditional---------------------//                     \n"
<<"                                                                                   \n"
<<"    if(err1Gather < 1e-2){                                                              \n";

}  //-- [if loop terminator] vectorial ended --//

if(!vectorial)writesolver
<<"                                                                                   \n"
<<"      //------------------Screen output norm----------------------//             \n"
<<"                                                                                   \n"
<<"      if(mpirank==0)                                                                         \n"
<<"      cout.scientific << \"NL iteration number :  [ \"  << iter                       \n"
<<"      << \" ]\\nL2 error in [u,phi] :  [ \"    << err1Gather                      \n"
<<"      << \" , \" <<  err2Gather << \" ]\"      << endl;                              \n"
<<"                                                                                   \n";

if(vectorial)writesolver
<<"                                                                                   \n"
<<"      //------------------Screen output norm----------------------//             \n"
<<"                                                                                   \n"
<<"      if(mpirank==0)                                                                         \n"
<<"      cout.scientific << \"NL iteration number :  [ \" << iter                       \n"
<<"      << \" ]\\nL2  error  in  [U]  :  [ \" << err1Gather << \" ]\" <<endl;           \n";

writesolver
<<"                                                                                   \n"
<<"      break;                                                                           \n"
<<"    }                                                                           \n"
<<"                                                                                   \n"
<<"    TractionIn = 0;                                                                   \n"
<<"  }                                                                                    \n"
<<"                                                                                   \n"
<<"  //-----------------updating traction----------------//                           \n"
<<"                                                                                   \n"
<<"    TractionIn     = tr;                                                                \n"
<<"    TractionTotal += dtr;                                                           \n";


if(pipegnu){writesolver
<<"                                                                                   \n"
<<"  //-------------------Force calculation-----------------------//                      \n"
<<"                                                                                   \n"
<<(timelog ? "  MPItimerbegin(\"force calculation\",t0)\n" : ""                       )
<<"  real forcetot  = 0., forcetotGath  = 0. ;                                              \n"
<<"  forcetot=intN1(Th,qforder=2,2)(DPspc*(lambda*divergence(u)+2.*mu*dy(u1)));           \n"
<<"  mpiAllReduce(forcetot,forcetotGath,mpiCommWorld,mpiSUM);                              \n"
<<"  if(mpirank==0){                                                                      \n"
<<"  ofstream ff(\"force.data\",append);                                           \n"
<<"  ff << TractionTotal << \"        \" << forcetotGath*1e-3 << endl;                     \n";

if(!supercomp)writesolver
<<"  pgnuplot<<\"plot \\\"force.data\\\" u 1:2 w lp pt 6 ps 2 t \\\"FEM\\\"\\n\";  \n"
<<"  flush(pgnuplot);                                                                         \n";

writesolver
<<"  }                                                                                       \n"
<<(timelog ? "  MPItimerend  (\"force calculation\",t0)\n" : ""                       );

}  //-- [if loop terminator] !pipegnu ended --//

if(plotAll)if(!vectorial){writesolver
<<"                                                                                   \n"
<<"  //-------Paraview plotting every nth iteration -----------//                        \n"
<<"                                                                                   \n"
<<"  iterout++;                                                                           \n"
<<"                                                                                   \n"
<<(timelog ? "  MPItimerbegin(\"ParaView post-processing\",t0)\n" : ""              )
<<"  if(int(iterout%10)==0){                                                           \n";


writesolver            
<<"    savevtk(  \"VTUs/Solution.vtu\"   ,                                            \n"
<<"                 Th                 ,                                              \n";

if(PostProcess!="u" & PostProcess!="phi")writesolver
<<(spc==2 ? "\t\t [u,u1,0]\t    ,\n" : "\t\t [u,u1,u2]\t    ,\n"                        )
<<"                 phi                ,                                              \n";


if(PostProcess=="u")writesolver
<<(spc==2 ? "\t\t [u,u1,0]\t    ,\n" : "\t\t [u,u1,u2]\t    ,\n"                        );

if(PostProcess=="phi")writesolver
<<"                 phi                ,                                              \n";

if(PostProcess=="uphi")writesolver
<<(spc==2 ? "\t\t [u,u1,0]\t    ,\n" : "\t\t [u,u1,u2]\t    ,\n"                        )
<<"                 phi                ,                                              \n";

writesolver
<<"                 order=vtuorder     ,                                              \n"
<<"                 dataname=\"U  d\"    ,                                              \n"
<<"                 append=true                                                             \n"
<<"              );                                                                             \n";

writesolver
<<"                                                                                   \n"
<<"    iterout1++;                                                                   \n"
<<"  }                                                                                     \n"
<<(timelog ? "  MPItimerend  (\"ParaView post-processing\",t0)\n" : ""               );
}

if(plotAll)if(vectorial){writesolver
<<"                                                                                   \n"
<<"  //--------Paraview plotting every nth iteration ----------//                        \n"
<<"                                                                                   \n"
<<"  iterout++;                                                                              \n"
<<"                                                                                   \n"
<<(timelog ? "  MPItimerbegin(\"ParaView post-processing\",t0)\n" : ""              )
<<"                                                                                   \n"
<<"  if(int(iterout%10)==0){                                                            \n"
<<"                                                                                   \n"
<<"    fespace Vhplot(Th,P1); Vhplot phi=u2;              //interpolation for phi  \n";

writesolver                   
<<"    savevtk(  \"VTUs/Solution.vtu\"   ,                                            \n"
<<"                 Th                 ,                                              \n";

if(PostProcess!="u" & PostProcess!="phi")writesolver
<<(spc==2 ? "\t\t [u,u1,0]\t    ,\n" : "\t\t [u,u1,u2]\t    ,\n"                        )
<<"                 phi                ,                                              \n";


if(PostProcess=="u")writesolver
<<(spc==2 ? "\t\t [u,u1,0]\t    ,\n" : "\t\t [u,u1,u2]\t    ,\n"                        );

if(PostProcess=="phi")writesolver
<<"                 phi                ,                                              \n";

if(PostProcess=="uphi")writesolver
<<(spc==2 ? "\t\t [u,u1,0]\t    ,\n" : "\t\t [u,u1,u2]\t    ,\n"                        )
<<"                 phi                ,                                              \n";

writesolver
<<"                 order=vtuorder     ,                                              \n"
<<"                 dataname=\"U  d\"    ,                                              \n"
<<"                 append=true                                                             \n"
<<"              );                                                                             \n";


writesolver
<<"                                                                                   \n"
<<"    iterout1++;                                                                   \n"
<<"  }                                                                                   \n"
<<(timelog ? "  MPItimerend  (\"ParaView post-processing\",t0)\n" : ""               );
}

if(debug)if(!vectorial)writesolver
<<"                                                                                   \n"
<<"  //-----------------Debug glut plotting----------------------//                      \n"
<<"                                                                                   \n"
<<"  plotMPI(Th, phi, P1,  def, real, wait=0, cmm=\"Tr-\"+tr+\"\")                      \n";

if(debug)if(vectorial)writesolver
<<"                                                                                   \n"
<<"  //-----------------Debug glut plotting----------------------//                       \n"
<<"                                                                                   \n"
<<"  plotMPI(Th, u"<<spc<<", P1,  def0, real, wait=0, cmm=\"Tr-\"+tr+\"\")           \n";

writesolver
<<"                                                                                   \n"
<<"}                                                                                   \n"
<<"                                                                                   \n"
<<(timelog ? "if(mpirank==0)\n" : " "                                                           )
<<(timelog ? "cout << \" all operations ended, they \";\n" : ""                        )
<<(timelog ? "MPItimerend  (\"solver\",t1)\n" : " "                                       )
<<"                                                                                   \n"
<<"//-------------------------------THE END------------------------------//           \n"; 

}  //-- [if loop terminator] !Sequential ended --//

}  //-- [if loop terminator] hybrid-phase-field ended --//

if(Model=="Mazar"){writesolver
<<"                                                                                   \n"
<<"//==============================================================================\n"
<<"//  ------- Variable initilization -------                                             \n"
<<"//==============================================================================\n"           
<<"                                                                                   \n"
<<"      duimp         = 0.       ;                                                   \n"
//<<"    def(u)        = init(0.) ;                                                   \n"
<<"      intVar[]      = kappa0   ;                                                      \n"
<<"      mufield[]     = mu       ;                                                           \n"
<<"      lambdafield[] = lambda   ;                                                   \n"
<<"                                                                                   \n"
<<"//==============================================================================\n"
<<"//  ------- Quasistatic loop for linear assembly and solving -------                   \n"
<<"//==============================================================================\n"        
<<"                                                                                   \n"
<<"  for (int n = 0; n < npas; n++){                                                    \n"
<<"                                                                                   \n"
<<"    if(mpirank == 0)                                                                   \n"
<<"      cout <<\"============ \"<<\"Time step \"<< n <<\" ============ \\n\";           \n"
<<"                                                                                   \n"
<<"  //---------------Nonlinear Newton-Rapsons loop------------------//                   \n"
<<"                                                                                   \n"
<<"   for (int i = 0; i <= iterMaxNR; i++){                                            \n"
<<"                                                                                   \n"
<<"    //----------Adjust Dirichlet boundary conditions--------------//                   \n"
<<"                                                                                   \n"
<<"     if (i>=1) duimp = 0.;                                                           \n"
<<"                                                                                   \n"
<<"    //--------------------Assembly for linear---------------------//                   \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"RHS assembly for U\",t0)\n" : ""                  )
<<"     b = varIncr(0,Vh);                                                           \n"
<<(timelog ? "    MPItimerend  (\"RHS assembly for U\",t0)\n" : ""                    )
<<"                                                                                   \n"
<<"    //------------------Error calculation------------------------//                   \n"
<<"                                                                                   \n"
<<"     if(i>0){                                                                   \n"
<<(timelog ? "       MPItimerbegin(\"NL error checking\",t0)\n" : ""                            )
<<"        b = b .* DP                                         ;                           \n"
<<"        real errLoc, err                                 ;                           \n"
<<"        errLoc = b.l2                                  ;                           \n"
<<"        errLoc = errLoc*errLoc                          ;                           \n"
<<"        mpiAllReduce(errLoc,err,mpiCommWorld,mpiSUM)  ;                           \n"
<<"        err = sqrt(err)                                  ;                           \n"
<<"                                                                                   \n"
<<"        if(mpirank == 0)                                                            \n"
<<"        cout << \"    iteration =\" << i << \", NR error =\" << err << endl ;   \n"
<<(timelog ? "       MPItimerend (\"NL error checking\",t0)\n" : ""                            )
<<"       if(err <= tol) break;                                                   \n"
<<"     }                                                                           \n"

<<"                                                                                   \n"
<<"    //----------------Assembly for bilinear----------------------//                    \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"matrix assembly for U\",t0)\n" : ""                     )
<<"     ALoc = varIncr(Vh,Vh);                                                           \n"
<<(timelog ? "    MPItimerend  (\"matrix assembly for U\",t0)\n" : ""                      )
<<"                                                                                   \n"
<<"    //-----------PETSc assembly for bilinear---------------------//                   \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"PETSc assembly for U\",t0)\n" : ""                       )
<<"     changeOperator(A, ALoc);                                                   \n"
<<"     set(A,sparams =\"  -ksp_type cg   -ksp_rtol 1e-15 \");                           \n"
<<(timelog ? "    MPItimerend  (\"PETSc assembly for U\",t0)\n" : ""                         )
<<"                                                                                   \n"
<<"    //-------------Linear system solving phase-------------------//                   \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"solving U\",t0)\n" : ""                               )
<<"     du[] = A^-1*b;                                                                   \n"
<<(timelog ? "    MPItimerend  (\"solving U\",t0)\n" : ""                                 )
<<"                                                                                   \n"
<<"    //-------------Intermediate solution update-------------------//                   \n"
<<"                                                                                   \n"
<<(timelog ? "    MPItimerbegin(\"solution update\",t0)\n" : ""                            )
<<"     u[]   += du[]  ;                                                            \n"
//<<"     u1[]  += du1[] ;                                                            \n"
<<"                                                                                   \n"
<<"    //----------Damage field calulation using Mazrs model---------//                   \n";


if(useGFP){writesolver
<<"                                                                                   \n";
if(spc==2)writesolver
<<"     defStrain(strain) = [epsilon(u)[0]          ,                              \n"
<<"                          epsilon(u)[2]/sqrt(2.) ,                                   \n"
<<"                          epsilon(u)[1]                                            \n"
<<"                         ];                                                           \n"
<<"                                                                                   \n";
if(spc==3)writesolver
<<"     defStrain(strain) = [epsilon(u)[0]          ,                              \n"
<<"                          epsilon(u)[5]/sqrt(2.) ,                                   \n"
<<"                          epsilon(u)[4]/sqrt(2.) ,                                   \n"
<<"                          epsilon(u)[1]          ,                                   \n"
<<"                          epsilon(u)[3]/sqrt(2.) ,                                   \n"
<<"                          epsilon(u)[2]                                              \n"
<<"                         ];                                                           \n";

writesolver
<<"     GFPMazarsDamageUpdate(strain[],intVar[],damage[],kappa0,kappac);            \n";
}
else{ writesolver
<<"                                                                                   \n"
<<"     e11 = epsilon(u)[0] ;                                                           \n"
<<"     e22 = epsilon(u)[1] ;                                                           \n"
<<"     e12 = epsilon(u)[2]/sqrt(2.) ;                                                   \n"
<<"                                                                                   \n"
<<"     ep1=0.5*(e11+e22+sqrt((e11-e22)^2+4*e12^2));                                   \n"
<<"     ep2=0.5*(e11+e22-sqrt((e11-e22)^2+4*e12^2));                                   \n"
<<"                                                                                   \n"
<<"     eqStrain = sqrt((max(0,ep1))^2 + (max(0,ep2))^2)  ;  // Mazars Eq strain   \n"
<<"                                                                                   \n"
<<"     intVar = (intVar < eqStrain ? eqStrain : intVar);                           \n"
<<"                                                                                   \n"
<<"     damage = 1-(kappa0/intVar)*exp(-(intVar-kappa0)/(kappac-kappa0));           \n"
<<"     damage = floor(100000.*damage)/100000. ;                                   \n";
}

writesolver
<<"                                                                                   \n"
<<(timelog ? "    MPItimerend  (\"solution update\",t0)\n" : " "                            )
<<"                                                                                   \n"
<<"  }                                                                                   \n"
<<"                                                                                   \n"
<<"  //----------Adjust Dirichlet boundary conditions--------------//                   \n"
<<"                                                                                   \n"
<<"  duimp = Duimp ;                                                                   \n";


if(pipegnu){writesolver
<<"                                                                                   \n"
<<"  //-------------------Force calculation-----------------------//                   \n"
<<"                                                                                   \n"
<<(timelog ? "  MPItimerbegin(\"force calculation\",t0)\n" : ""                       )
<<"   real ForceXloc , ForceXGather ;                                                   \n"
<<"   ForceXloc = intN1(Th,4,qforder=2)                                            \n"
<<"                          (DPspc*(1-damage)*stress(u,lambdafield,mufield)[0]);  \n"
<<"   mpiAllReduce(ForceXloc,ForceXGather,mpiCommWorld,mpiSUM);                           \n"
<<"                                                                                   \n"
<<"   if(mpirank==0){                                                                   \n"
<<"     ofstream outputFile(\"output.data\", append);                                   \n"
<<"     outputFile << n*Duimp << \" \" << ForceXGather << endl;                           \n";

if(!supercomp)writesolver
<<"     pgnuplot                                                                    \n"
<<"      <<\"plot\"                                                                       \n"
<<"      <<\"\\\"output.data\\\"\"                                                          \n"
<<"      <<\"u ($1):($2) w lp lw 2 pt 7 ps 2 notitle\"                                      \n"
<<"      <<\"\\n\";                                                                          \n" 
<<"     flush(pgnuplot);                                                                 \n";

writesolver
<<"   }                                                                                   \n"
<<(timelog ? "  MPItimerend  (\"force calculation\",t0)\n" : ""                       );

}  //-- [if loop terminator]  pipegnu ended --//

writesolver
<<"}                                                                                   \n"
<<"                                                                                   \n"
<<(timelog ? "if(mpirank==0)\n" : " "                                                           )
<<(timelog ? "cout << \" all operations ended, they \";\n" : " "                        )
<<(timelog ? "MPItimerend  (\"solver\",t1)\n" : " "                                       )
<<"                                                                                   \n"
<<"//-------------------------------THE END------------------------------//           \n";
}
