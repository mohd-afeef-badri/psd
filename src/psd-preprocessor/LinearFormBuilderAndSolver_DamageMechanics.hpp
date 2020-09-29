//=====================================================================================
// ------ Damage Mechanics for the LinearFormBuilderAndSolver.edp file ------
//=====================================================================================

if(Model=="hybrid-phase-field"){

if(Sequential)
 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- L_o calculation -------                                              \n"
 "//==============================================================================\n"
 "                                                                                \n"
 "{                                                                               \n"
 "  fespace  Vh0( Th , P0)    ;                                                   \n"
 "  Vh0 size1 = hTriangle     ;                                                   \n"
 "  lo = size1[].min          ;                                                   \n"
 "  lo = lo*lfac              ;                                                   \n"
 "}                                                                               \n";

if(!Sequential)
 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- L_o calculation in parallel -------                                  \n"
 "//==============================================================================\n"
 "                                                                                \n"
 "{ real himlocal,himGlobal                                ;                      \n"
 "  fespace Vh0(Th,P0)                                     ;                      \n"
 "  Vh0 size1 = hTriangle                                  ;                      \n"
 "  himlocal  = size1[].min                                ;                      \n"
 "  mpiAllReduce(himlocal,himGlobal,mpiCommWorld,mpiMIN)   ;                      \n"
 "  lo = himGlobal*lfac                                    ;                      \n"
 "}                                                                               \n";


if(dirichletpointconditions>=1 && !Sequential)
 writeIt
 "                                                                                \n"
 "//---------Preprocessing for point bounday conditions----------//               \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"point Dirichlet preprocessing\",t0)\n" : ""          )<<
 "  GetPointIndiciesMpiRank(PbcCord, PCi, mpirankPCi);                            \n"
 <<(timelog ? "  timerend(\"point Dirichlet assembly\",t0)\n" : ""                );
 
 
if(Sequential)if(NonLinearMethod=="Picard"){
 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- Traction loading loop -------                                        \n"
 "//==============================================================================\n"
 "                                                                                \n"
 "while (tr <= maxtr){                                                            \n"
 "                                                                                \n"
 "  cout <<  \"-------------------------------------------------------\\n\"       \n"
 "       <<  \"Applied traction \" << tr << \"\\n\" << endl;                      \n"
 "                                                                                \n"
 "  if (tr >= 5e-3)                                                               \n"
 "    dtr = 1e-6;                                                                 \n"
 "                                                                                \n";
 
 if(constrainHPF)
 writeIt
 "                                                                                \n"
 <<(timelog ? "  timerbegin(\"copying solution befor NL iterations\",t0)\n" : ""  )<< 
 "   up[]=uold[];                                                              \n"
 <<(timelog ? "  timerend  (\"copying solution befor NL iterations\",t0)\n" : ""  )<<
 "                                                                                \n";  
 
 
 writeIt
 "  //--------------------Assembly for linear----------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "  timerbegin(\"RHS assembly for U\",t0)\n" : ""                    )<<
 "  b = elast(0,Vh);                                                              \n"
 <<(timelog ? "  timerend  (\"RHS assembly for U\",t0)\n" : ""                    )<<
 "                                                                                \n"
 "  //-----------------------Nonlinear loop------------------------//             \n"
 "                                                                                \n"
 "  for(int iter=0; iter<100; iter++){                                            \n"
 "                                                                                \n"
 "    //----------------Assembly for bilinear----------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"matrix assembly for U\",t0)\n" : ""               )<<
 "    A = elast(Vh,Vh,solver=CG,sym=1);                                           \n"
 <<(timelog ? "    timerend  (\"matrix assembly for U\",t0)\n" : ""               )<<
 "                                                                                \n"
 "    //-------------Linear system solving phase-------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"solving U\",t0)\n"         : ""                   )<<
 "    set(A,solver=CG,sym=1);                                                     \n"
 "    u[] = A^-1*b;                                                               \n"
 <<(timelog ? "    timerend  (\"solving U\",t0)\n"         : ""                   );

if(energydecomp)
 writeIt
 "                                                                                \n"
 "    //---------------Energy decomposition phase-------------------//            \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"energy decomposition\",t0)\n"         : ""        )<<
 "    DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus)                 \n"
 <<(timelog ? "    timerend  (\"energy decomposition\",t0)\n"         : ""        );



 writeIt
 "                                                                                \n"
 "    //----------------Assembly for bilinear----------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"matrix assembly for PHI\",t0)\n" : ""             )<<
 "    A1 = phase(Vh1,Vh1,solver=CG,sym=1);                                        \n"
 <<(timelog ? "    timerend  (\"matrix assembly for PHI\",t0)\n" : ""             )<<
 "                                                                                \n"
 "    //--------------------Assembly for linear----------------------//           \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"RHS assembly for PHI\",t0)\n" : ""                )<<
 "    b1 = phase(0,Vh1);                                                          \n"
 <<(timelog ? "    timerend  (\"RHS assembly for U\",t0)\n" : ""                   )<<
 "                                                                                \n"
 "    //-------------Linear system solving phase-------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"solving U\",t0)\n" : ""                            )<<
 "    set(A1,solver=CG,sym=1);                                                    \n"
 "    phi[] = A1^-1*b1;                                                           \n"
 <<(timelog ? "    timerend  (\"solving U\",t0)\n" : ""                            )<<
 "                                                                                \n";


if(energydecomp && constrainHPF && vectorial)
 writeIt
 "                                                                                \n"
 "    //---------------Hybrid phase field constrain-------------------//          \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"Hybrid phase field constrain\",t0)\n"         : "")<<
 "    PsiPlusP1=PsiPlus; PsiMinusP1=PsiMinus;                                     \n"
 "    for(int i=0; i < PsiPlusP1[].n; i++ )                                       \n"
 "      if(PsiPlusP1[][i]<PsiMinusP1[][i])uold[][i*"<<Fdofs<<"+"<<spc<<"]=0.;     \n"    
 <<(timelog ? "    timerend  (\"Hybrid phase field constrain\",t0)\n"         : "");

if(energydecomp && constrainHPF && !vectorial)
 writeIt
 "                                                                                \n"
 "    //---------------Hybrid phase field constrain-------------------//          \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"Hybrid phase field constrain\",t0)\n"         : "")<<
 "    PsiPlusP1=PsiPlus; PsiMinusP1=PsiMinus;                                     \n"
 "    for(int i=0; i < PsiPlusP1[].n; i++ )                                       \n"
 "      if(PsiPlusP1[][i]<PsiMinusP1[][i])phi[][i]=0.;                            \n"    
 <<(timelog ? "    timerend  (\"Hybrid phase field constrain\",t0)\n"         : "");


 writeIt
 "    //------------------Error calculation------------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"NL error checking\",t0)\n" : ""                    )<<
 "    uold[]    = uold[]-u[]                         ;                            \n"
 "    phiold[]  = phiold[]-phi[]                     ;                            \n"
 "    real err1 = sqrt( intN(Th,qforder=2) ( uold^2   )  )     ;                  \n"
 "    real err2 = sqrt( intN(Th,qforder=2) ( phiold^2 )  )     ;                  \n"
 <<(timelog ? "    timerend  (\"NL error checking\",t0)\n" : ""                    )<<
 "                                                                                \n"
 "    //--------------------Solution update-------------------------//            \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"solution update\",t0)\n" : ""                      )<<
 "    phiold[] = phi[]  ;                                                         \n"
 "    uold[]   = u[]    ;                                                         \n"
 <<(timelog ? "    timerend  (\"solution update\",t0)\n" : ""                      )<<
 "                                                                                \n"
 "    //--------------- Convergence conditional---------------------//            \n"
 "                                                                                \n"
 "    if(err1 < 1e-2 && err2 < 1e-2){                                             \n"
 "                                                                                \n"
 "      //------------------Screen output norm----------------------//            \n"
 "                                                                                \n"
 "      cout.scientific                                                           \n"
 "      << \"NL iteration number :  [ \"      << iter                             \n"
 "      << \" ]\\nL2 error in [u,phi] :  [ \"  << err1                            \n"
 "      << \" , \" <<  err2 << \" ]\"           << endl;                          \n"
 "                                                                                \n"
 "      break;                                                                    \n"
 "    }                                                                           \n"
 "                                                                                \n"
 "  }                                                                             \n";

if(reactionforce){
 writeIt
 "                                                                                \n"
 "  //-------------------Force calculation-----------------------//               \n"
 "                                                                                \n" 
 <<(timelog ? "  timerbegin(\"force calculation\",t0)\n" : ""                     )<<
 "                                                                                \n"
 "  real forcetotx  = 0. , forcetoty  = 0.;                                       \n";   
 
 if(reactionforcemethod=="stress-based" && spc==2 )
 writeIt
 "                                                                                \n"
 "  forcetotx = intN1(Th,qforder=2,RFOn)(  lambda*divergence(u)+2.*mu*dx(u)       \n"
 "                                     + mu*(dx(u1)+dy(u))                 );     \n" 
 "                                                                                \n"
 "  forcetoty = intN1(Th,qforder=2,RFOn)(  lambda*divergence(u)+2.*mu*dy(u1)      \n"
 "                                     + mu*(dx(u1)+dy(u))                 );     \n" 
 "                                                                                \n";

 if(reactionforcemethod=="stress-based" && spc==3)
 writeIt
 "                                                                                \n"
 "  forcetotx = intN1(Th,qforder=2,RFOn)( ( lambda*divergence(u)+2.*mu*dx(u)      \n" 
 "                                            + mu*(dx(u1)+dy(u))                 \n" 
 "                                            + mu*(dx(u2)+dz(u))            ) ); \n"   
 "                                                                                \n"
 "  forcetoty = intN1(Th,qforder=2,RFOn)( ( lambda*divergence(u)+2.*mu*dy(u)      \n" 
 "                                            + mu*(dx(u1)+dy(u))                 \n"
 "                                            + mu*(dy(u2)+dz(u1))           ) ); \n"    
 "                                                                                \n"
 "  forcetotz = intN1(Th,qforder=2,RFOn)( ( lambda*divergence(u)+2.*mu*dz(u)      \n" 
 "                                            + mu*(dx(u2)+dz(u))                 \n"
 "                                            + mu*(dy(u2)+dz(u1))           ) ); \n"        
 "                                                                                \n"; 

 if(reactionforcemethod=="variational-based" && spc==2)
 writeIt
 "                                                                                \n"
 "  A = varfForce(Vh,Vh,solver=CG,sym=1);                                         \n"
 "  F[] = A*u[];                                                                  \n"
 "                                                                                \n"
 "  for(int i=0; i < Th.nv; i++){                                                 \n"
 "     if(abs(Th(i).y-1.)<.000001){                                               \n"
 "        forcetotx = forcetotx + F[][i*"<<Fdofs<<"];                             \n"
 "        forcetoty = forcetoty + F[][i*"<<Fdofs<<"+1];                           \n" 
 "     }                                                                          \n"
 "  }                                                                             \n"   
 "                                                                                \n";
 
 if(reactionforcemethod=="variational-based" && spc==3)
 writeIt
 "                                                                                \n"
 "  A = varfForce(Vh,Vh,solver=CG,sym=1);                                         \n"
 "  F[] = A*u[];                                                                  \n"
 "                                                                                \n"
 "  for(int i=0; i < Th.nv; i++){                                                 \n"
 "     if(abs(Th(i).y-1.)<.000001){                                               \n"
 "        forcetotx = forcetotx + F[][i*"<<Fdofs<<"];                             \n"
 "        forcetoty = forcetoty + F[][i*"<<Fdofs<<"+1];                           \n"
 "        forcetotz = forcetotz + F[][i*"<<Fdofs<<"+2];                           \n"   
 "     }                                                                          \n"
 "  }                                                                             \n"   
 "                                                                                \n";   

 if(spc==2)
 writeIt
 "                                                                                \n"
 "  ofstream ff(\"force.data\",append);                                           \n"
 "  ff << tr << \"  \" << forcetotx*1e-3 << \"  \" << forcetoty*1e-3 << endl;     \n";

 if(spc==3)
 writeIt
 "                                                                                \n"
 "  ofstream ff(\"force.data\",append);                                           \n"
 "  ff << tr << \"  \" << forcetotx*1e-3 << \"  \" << forcetoty*1e-3 <<           \n"
 "              \"  \" << forcetotz*1e-3 <<                             endl;     \n"; 
 
 if(plotreaction && spc==2)
 writeIt
 "                                                                                \n" 
 "  pgnuplot<<\"plot \\\"force.data\\\"u 1:2 w p pt 6 ps 2 t \\\"Fx\\\",  \"      \n"
 "          <<\"     \\\"force.data\\\"u 1:3 w p pt 5 ps 2 t \\\"Fy\\\"\\n\";     \n" 
 "  flush(pgnuplot);                                                              \n";
 
 if(plotreaction && spc==3)
 writeIt
 "                                                                                \n" 
 "  pgnuplot<<\"plot \\\"force.data\\\"u 1:2 w p pt 6 ps 2 t \\\"Fx\\\",  \"      \n"
 "          <<\"     \\\"force.data\\\"u 1:3 w p pt 5 ps 2 t \\\"Fy\\\",  \"      \n" 
 "          <<\"     \\\"force.data\\\"u 1:4 w p pt 4 ps 2 t \\\"Fz\\\"\\n\";     \n" 
 "  flush(pgnuplot);                                                              \n"; 

 writeIt
 (timelog ? "  timerend  (\"force calculation\",t0)\n" : ""                         );
}

if(ParaViewPostProcess){
 writeIt
 "                                                                                \n"
 "  //-------Paraview plotting every nth iteration -----------//                  \n"
 "                                                                                \n"
 "  iterout++;                                                                    \n"
 "                                                                                \n"
 <<(timelog ? "  timerbegin(\"ParaView post-processing\",t0)\n" : ""              )<<
 "  if(int(iterout%10)==0){                                                       \n"
 "    savevtk(     \"VTUs/Solution_\"+iterout1+\".vtu\"  ,                        \n"
 "                 Th                 ,                                           \n";
 
 if(PostProcess=="u")
 writeIt
 "                 PlotVec(u)         ,                                           \n";

 if(PostProcess=="d")
 writeIt
 "                 phi                ,                                           \n"; 
 
 if(PostProcess=="ud" || PostProcess=="du")
 writeIt
 "                 PlotVec(u)         ,                                           \n"
 "                 phi                ,                                           \n"; 
 
 writeIt
 "                 order=vtuorder     ,                                           \n";
 
 if(PostProcess=="u")
 writeIt
 "                 dataname = \"U\"                                               \n";

 if(PostProcess=="d")
 writeIt
 "                 dataname = \"d\"                                               \n";
 
 if(PostProcess=="ud" || PostProcess=="du")
 writeIt
 "                 dataname = \"U d\"                                             \n";
  
 writeIt
 "          );                                                                    \n"
 "                                                                                \n"
 "    iterout1++;                                                                 \n"
 "    }                                                                           \n"
 <<(timelog ? "  timerend  (\"ParaView post-processing\",t0)\n" : ""              );
}  

if(debug)
 writeIt
 "                                                                                \n"
 "  //-----------------Debug glut plotting----------------------//                \n"
 "                                                                                \n"
 "  plot(phi,fill=1,value=1);                                                     \n";


 writeIt
 "                                                                                \n"
 "  //-----------------updating traction----------------//                        \n"
 "                                                                                \n"
 "  tr += dtr;                                                                    \n"
 "}                                                                               \n"
 "                                                                                \n"
 <<(timelog ? "timerend  (\"solver\",t1)\n" : " "                                  )<<
 "                                                                                \n"
 "//-------------------------------THE END------------------------------//        \n";
}  //-- [if loop terminator] Sequential ended --//



if(Sequential)if(NonLinearMethod=="Newton-Raphson"){
 writeIt
 "                                                                                \n"
 "  real TractionTotal=tr;                                                        \n"
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- Traction loading loop -------                                        \n"
 "//==============================================================================\n"
 "                                                                                \n"
 "while (TractionTotal <= maxtr){                                                 \n"
 "                                                                                \n"
 "  cout <<  \"-------------------------------------------------------\\n\"       \n"
 "       <<  \"Applied traction \" << TractionTotal << \"\\n\" << endl;           \n"
 "                                                                                \n"
 "  if (TractionTotal >= 5e-3){                                                   \n"
 "    tr = 1e-6; dtr = 1e-6;}                                                     \n";
 
  
 if(constrainHPF)
 writeIt
 "                                                                                \n"
 <<(timelog ? "  timerbegin(\"copying solution befor NL iterations\",t0)\n" : ""  )<< 
 "   up[]=uold[];                                                              \n"
 <<(timelog ? "  timerend  (\"copying solution befor NL iterations\",t0)\n" : ""  )<<
 "                                                                                \n"; 
 
 writeIt
 "  //-----------------------Nonlinear loop------------------------//             \n"
 "                                                                                \n"
 "  for(int iter=0; iter<100; iter++){                                            \n"
 "                                                                                \n"
 "  //--------------------Assembly for linear----------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "  timerbegin(\"RHS assembly for U\",t0)\n" : ""                     )<<
 "    b = elast(0,Vh);                                                            \n"
 <<(timelog ? "  timerend  (\"RHS assembly for U\",t0)\n" : ""                     )<<
 "                                                                                \n"
 "    //----------------Assembly for bilinear----------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"matrix assembly for U\",t0)\n" : ""                )<<
 "    A = elast(Vh,Vh,solver=CG,sym=1);                                           \n"
 <<(timelog ? "    timerend  (\"matrix assembly for U\",t0)\n" : ""                )<<
 "                                                                                \n"
 "    //-------------Linear system solving phase-------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"solving U\",t0)\n"         : ""                    )<<
 "    set(A,solver=CG,sym=1);                                                     \n"
 "    du[] = A^-1*b;                                                              \n"
 <<(timelog ? "    timerend  (\"solving U\",t0)\n"         : ""                    )<<
 "                                                                                \n"
 "    //--------------Update of displacement u---------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"Updating U\",t0)\n"         : ""                   )<<
 "    u[] += du[];                                                                \n"
 <<(timelog ? "    timerend  (\"Updating U\",t0)\n"         : ""                   )<<
 "                                                                                \n";

if(energydecomp)
 writeIt
 "                                                                                \n"
 "    //---------------Energy decomposition phase-------------------//            \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"energy decomposition\",t0)\n"         : ""         )<<
 "    DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus)                 \n"
 <<(timelog ? "    timerend  (\"energy decomposition\",t0)\n"         : ""           );


 writeIt
 "                                                                                \n"
 "    //----------------Assembly for bilinear----------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"matrix assembly for PHI\",t0)\n" : ""              )<<
 "    A1 = phase(Vh1,Vh1,solver=CG,sym=1);                                        \n"
 <<(timelog ? "    timerend  (\"matrix assembly for PHI\",t0)\n" : ""              )<<
 "                                                                                \n"
 "    //--------------------Assembly for linear----------------------//           \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"RHS assembly for PHI\",t0)\n" : ""                 )<<
 "    b1 = phase(0,Vh1);                                                          \n"
 <<(timelog ? "    timerend  (\"RHS assembly for U\",t0)\n" : ""                   )<<
 "                                                                                \n"
 "    //-------------Linear system solving phase-------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"solving U\",t0)\n" : ""                            )<<
 "    set(A1,solver=CG,sym=1);                                                    \n"
 "    dphi[] = A1^-1*b1;                                                          \n"
 <<(timelog ? "    timerend  (\"solving U\",t0)\n" : ""                            )<<
 "                                                                                \n"
 "    //--------------Update of phase-field phi-------------------//              \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"Updating U\",t0)\n"         : ""                   )<<
 "    phi[] += dphi[];                                                            \n"
 <<(timelog ? "    timerend  (\"Updating U\",t0)\n"         : ""                   )<<
 "                                                                                \n";

if(energydecomp && constrainHPF && vectorial)
 writeIt
 "                                                                                \n"
 "    //---------------Hybrid phase field constrain-------------------//          \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"Hybrid phase field constrain\",t0)\n"         : "")<<
 "    PsiPlusP1=PsiPlus; PsiMinusP1=PsiMinus;                                     \n"
 "    exchange(A1,PsiPlusP1[],scaled=true);                                       \n"
 "    exchange(A1,PsiMinusP1[],scaled=true);                                      \n"
 "    for(int i=0; i < PsiPlusP1[].n; i++ )                                       \n"
 "      if(PsiPlusP1[][i]<PsiMinusP1[][i])uold[][i*"<<Fdofs<<"+"<<spc<<"]=0.;     \n"    
 <<(timelog ? "    timerend  (\"Hybrid phase field constrain\",t0)\n"         : "");

if(energydecomp && constrainHPF && !vectorial)
 writeIt
 "                                                                                \n"
 "    //---------------Hybrid phase field constrain-------------------//          \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"Hybrid phase field constrain\",t0)\n"         : "")<<
 "    PsiPlusP1=PsiPlus; PsiMinusP1=PsiMinus;                                     \n"
 "    exchange(A1,PsiPlusP1[],scaled=true);                                       \n"
 "    exchange(A1,PsiMinusP1[],scaled=true);                                      \n"
 "    for(int i=0; i < PsiPlusP1[].n; i++ )                                       \n"
 "      if(PsiPlusP1[][i]<PsiMinusP1[][i])phi[][i]=0.;                            \n"    
 <<(timelog ? "    timerend  (\"Hybrid phase field constrain\",t0)\n"         : "");


 writeIt
 "    //------------------Error calculation------------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"NL error checking\",t0)\n" : ""                   )<<
 "    real err1 = sqrt( intN(Th,qforder=2) ( du^2   )  )     ;                    \n"
 "    real err2 = sqrt( intN(Th,qforder=2) ( dphi^2 )  )     ;                    \n"
 <<(timelog ? "    timerend  (\"NL error checking\",t0)\n" : ""                   )<<
 "                                                                                \n"
 "    //--------------- Convergence conditional---------------------//            \n"
 "                                                                                \n"
 "    if(err1 < 1e-2 && err2 < 1e-2){                                             \n"
 "                                                                                \n"
 "      //------------------Screen output norm----------------------//            \n"
 "                                                                                \n"
 "      cout.scientific                                                           \n"
 "      << \"NL iteration number :  [ \"      << iter                             \n"
 "      << \" ]\\nL2 error in [u,phi] :  [ \"  << err1                            \n"
 "      << \" , \" <<  err2 << \" ]\"           << endl;                          \n"
 "                                                                                \n"
 "      break;                                                                    \n"
 "    }                                                                           \n"
 "                                                                                \n"
 "    TractionIn = 0;                                                             \n"
 "  }                                                                             \n"
 "                                                                                \n"
 "  //-----------------updating traction----------------//                        \n"
 "                                                                                \n"
 "    TractionIn     = tr;                                                        \n"
 "    TractionTotal += dtr;                                                       \n";

if(reactionforce){
 writeIt
 "                                                                                \n"
 "  //-------------------Force calculation-----------------------//               \n"
 "                                                                                \n" 
 <<(timelog ? "  timerbegin(\"force calculation\",t0)\n" : ""                     )<<
 "                                                                                \n"
 "  real forcetotx  = 0. , forcetoty  = 0.;                                       \n";   
 
 if(reactionforcemethod=="stress-based" && spc==2 )
 writeIt
 "                                                                                \n"
 "  forcetotx = intN1(Th,qforder=2,RFOn)(  lambda*divergence(u)+2.*mu*dx(u)       \n"
 "                                     + mu*(dx(u1)+dy(u))                 );     \n" 
 "                                                                                \n"
 "  forcetoty = intN1(Th,qforder=2,RFOn)(  lambda*divergence(u)+2.*mu*dy(u1)      \n"
 "                                     + mu*(dx(u1)+dy(u))                 );     \n" 
 "                                                                                \n";

 if(reactionforcemethod=="stress-based" && spc==3)
 writeIt
 "                                                                                \n"
 "  forcetotx = intN1(Th,qforder=2,RFOn)( ( lambda*divergence(u)+2.*mu*dx(u)      \n" 
 "                                            + mu*(dx(u1)+dy(u))                 \n" 
 "                                            + mu*(dx(u2)+dz(u))            ) ); \n"   
 "                                                                                \n"
 "  forcetoty = intN1(Th,qforder=2,RFOn)( ( lambda*divergence(u)+2.*mu*dy(u)      \n" 
 "                                            + mu*(dx(u1)+dy(u))                 \n"
 "                                            + mu*(dy(u2)+dz(u1))           ) ); \n"    
 "                                                                                \n"
 "  forcetotz = intN1(Th,qforder=2,RFOn)( ( lambda*divergence(u)+2.*mu*dz(u)      \n" 
 "                                            + mu*(dx(u2)+dz(u))                 \n"
 "                                            + mu*(dy(u2)+dz(u1))           ) ); \n"        
 "                                                                                \n"; 

 if(reactionforcemethod=="variational-based" && spc==2)
 writeIt
 "                                                                                \n"
 "  A = varfForce(Vh,Vh,solver=CG,sym=1);                                         \n"
 "  F[] = A*u[];                                                                  \n"
 "                                                                                \n"
 "  for(int i=0; i < Th.nv; i++){                                                 \n"
 "     if(abs(Th(i).y-1.)<.000001){                                               \n"
 "        forcetotx = forcetotx + F[][i*"<<Fdofs<<"];                             \n"
 "        forcetoty = forcetoty + F[][i*"<<Fdofs<<"+1];                           \n" 
 "     }                                                                          \n"
 "  }                                                                             \n"   
 "                                                                                \n";
 
 if(reactionforcemethod=="variational-based" && spc==3)
 writeIt
 "                                                                                \n"
 "  A = varfForce(Vh,Vh,solver=CG,sym=1);                                         \n"
 "  F[] = A*u[];                                                                  \n"
 "                                                                                \n"
 "  for(int i=0; i < Th.nv; i++){                                                 \n"
 "     if(abs(Th(i).y-1.)<.000001){                                               \n"
 "        forcetotx = forcetotx + F[][i*"<<Fdofs<<"];                             \n"
 "        forcetoty = forcetoty + F[][i*"<<Fdofs<<"+1];                           \n"
 "        forcetotz = forcetotz + F[][i*"<<Fdofs<<"+2];                           \n"   
 "     }                                                                          \n"
 "  }                                                                             \n"   
 "                                                                                \n";   

 if(spc==2)
 writeIt
 "                                                                                \n"
 "  ofstream ff(\"force.data\",append);                                           \n"
 "  ff << TractionTotal << \"  \" << forcetotx*1e-3 <<                            \n"
 "                         \"  \" << forcetoty*1e-3 << endl;                      \n";

 if(spc==3)
 writeIt
 "                                                                                \n"
 "  ofstream ff(\"force.data\",append);                                           \n"
 "  ff << TractionTotal << \"  \" << forcetotx*1e-3 <<                            \n"
 "                         \"  \" << forcetoty*1e-3 <<                            \n"
 "                         \"  \" << forcetotz*1e-3 <<                  endl;     \n"; 
 
 if(plotreaction && spc==2)
 writeIt
 "                                                                                \n" 
 "  pgnuplot<<\"plot \\\"force.data\\\"u 1:2 w p pt 6 ps 2 t \\\"Fx\\\",  \"      \n"
 "          <<\"     \\\"force.data\\\"u 1:3 w p pt 5 ps 2 t \\\"Fy\\\"\\n\";     \n" 
 "  flush(pgnuplot);                                                              \n";
 
 if(plotreaction && spc==3)
 writeIt
 "                                                                                \n" 
 "  pgnuplot<<\"plot \\\"force.data\\\"u 1:2 w p pt 6 ps 2 t \\\"Fx\\\",  \"      \n"
 "          <<\"     \\\"force.data\\\"u 1:3 w p pt 5 ps 2 t \\\"Fy\\\",  \"      \n" 
 "          <<\"     \\\"force.data\\\"u 1:4 w p pt 4 ps 2 t \\\"Fz\\\"\\n\";     \n" 
 "  flush(pgnuplot);                                                              \n"; 

 writeIt
 (timelog ? "  timerend  (\"force calculation\",t0)\n" : ""                         );
}

if(ParaViewPostProcess){
 writeIt
 "                                                                                \n"
 "  //-------Paraview plotting every nth iteration -----------//                  \n"
 "                                                                                \n"
 "  iterout++;                                                                    \n"
 "                                                                                \n"
 <<(timelog ? "  timerbegin(\"ParaView post-processing\",t0)\n" : ""              )<<
 "  if(int(iterout%10)==0){                                                       \n"
 "    savevtk(     \"VTUs/Solution_\"+iterout1+\".vtu\" ,                         \n"
 "                 Th                 ,                                           \n";

 if(PostProcess=="u")
 writeIt
 "                 PlotVec(u)         ,                                           \n";

 if(PostProcess=="d")
 writeIt
 "                 phi                ,                                           \n"; 
 
 if(PostProcess=="ud" || PostProcess=="du")
 writeIt
 "                 PlotVec(u)         ,                                           \n"
 "                 phi                ,                                           \n"; 
 
 writeIt
 "                 order=vtuorder     ,                                           \n";
 
 if(PostProcess=="u")
 writeIt
 "                 dataname = \"U\"                                               \n";

 if(PostProcess=="d")
 writeIt
 "                 dataname = \"d\"                                               \n";
 
 if(PostProcess=="ud" || PostProcess=="du")
 writeIt
 "                 dataname = \"U d\"                                             \n"; 
 
 writeIt
 "          );                                                                    \n"
 "                                                                                \n"
 "    iterout1++;                                                                 \n"
 "    }                                                                           \n"
 <<(timelog ? "  timerend  (\"ParaView post-processing\",t0)\n" : ""                );
} 

if(debug)
 writeIt
 "                                                                                \n"
 "  //-----------------Debug glut plotting----------------------//                \n"
 "                                                                                \n"
 "  plot(phi,fill=1,value=1);                                                     \n";


 writeIt
 "                                                                                \n"
 "}                                                                               \n"
 "                                                                                \n"
 <<(timelog ? "timerend  (\"solver\",t1)\n" : " "                                 )<<
 "                                                                                \n"
 "//-------------------------------THE END------------------------------//        \n";
}  //-- [if loop terminator] Sequential ended --//

if(!Sequential)if(NonLinearMethod=="Picard"){
 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// -------  Traction loading loop  -------                                      \n"
 "//==============================================================================\n"
 "                                                                                \n"
 "while (tr <= maxtr){                                                            \n"
 "                                                                                \n"
 "  if(mpirank==0)                                                                \n"
 "  cout.scientific<<\"-----------------------------------------------------\\n\" \n"
 "  <<  \"Applied traction \" << tr << \"\\n\" << endl;                           \n"
 "                                                                                \n"
 "  if (tr >= 5e-3)                                                               \n"
 "    dtr = 1e-6;                                                                 \n";
 
 if(constrainHPF)
 writeIt
 "                                                                                \n"
 <<(timelog ? "  timerbegin(\"copying solution befor NL iterations\",t0)\n" : ""  )<< 
 "   up[]=uold[];                                                              \n"
 <<(timelog ? "  timerend  (\"copying solution befor NL iterations\",t0)\n" : ""  )<<
 "                                                                                \n"; 
 
 if(!vectorial)
 writeIt
 "                                                                                \n"
 "  //--------------------Assembly for linear----------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "  timerbegin(\"RHS assembly for U\",t0)\n" : ""                 )<<
 "  b = elast(0,Vh);                                                              \n"
 <<(timelog ? "  timerend  (\"RHS assembly for U\",t0)\n" : ""                 )<<
 "                                                                                \n";
 
 writeIt
 "  //-----------------------Nonlinear loop------------------------//             \n"
 "                                                                                \n"
 "  for(int iter=0; iter<100; iter++){                                            \n";

 if(vectorial)
 writeIt 
 "                                                                                \n"
 "  //--------------------Assembly for linear----------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"RHS assembly for U\",t0)\n" : ""                 )<<
 "    b = elast(0,Vh);                                                            \n"
 <<(timelog ? "    timerend  (\"RHS assembly for U\",t0)\n" : ""                 )<<
 "                                                                                \n";
 
 writeIt
 "                                                                                \n"
 "    //----------------Assembly for bilinear----------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"matrix assembly for U\",t0)\n" : ""            )<<
 "    ALoc = elast(Vh,Vh,solver=CG,sym=1);                                        \n"
 <<(timelog ? "    timerend  (\"matrix assembly for U\",t0)\n" : ""            )<<
 "                                                                                \n";

 if(dirichletpointconditions>=1){
 writeIt
 "                                                                                \n"
 "//---------Additional assembly for A & b (point bounday condition)----------//  \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"point Dirichlet assembly\",t0)\n" : ""             );
 
 for(int i=0; i<dirichletpointconditions; i++)
 writeIt 
 "    ApplyPointBc"<<i<<"(ALoc,b);                                               \n"; 

 writeIt 
 (timelog ? "    timerend(\"point Dirichlet assembly\",t0)\n" : ""                );
 }
 
 writeIt
 "                                                                                \n" 
 "    //-----------PETSc assembly for bilinear---------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"PETSc assembly for U\",t0)\n" : ""             )<<
 "     A = ALoc;   //changeOperator(A, ALoc);                                     \n"
 "    set(A,sparams =\"  -ksp_type cg  \");                                       \n"
 <<(timelog ? "    timerend  (\"PETSc assembly for U\",t0)\n" : ""             )<<
 "                                                                                \n"
 "    //-------------Linear system solving phase-------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"solving U\",t0)\n" : " "                       )<<
 "    u[] = A^-1*b;                                                               \n"
 <<(timelog ? "    timerend  (\"solving U\",t0)\n" : " "                         );

if(!vectorial){
if(energydecomp)
 writeIt
 "                                                                                \n"
 "    //---------------Energy decomposition phase-------------------//            \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"energy decomposition\",t0)\n" : ""             )<<
 "    DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus);                \n"
 <<(timelog ? "    timerend  (\"energy decomposition\",t0)\n" : ""               );


 writeIt
 "                                                                                \n"
 "    //----------------Assembly for bilinear----------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"matrix assembly for PHI\",t0)\n" : ""          )<<
 "    ALoc1 = phase(Vh1,Vh1,solver=CG,sym=1);                                     \n"
 <<(timelog ? "    timerend  (\"matrix assembly PHI\",t0)\n" : ""              )<<
 "                                                                                \n"
 "    //----------------Assembly for linear------------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"RHS assembly for PHI\",t0)\n" : ""             )<<
 "    b1 = phase(0,Vh1);                                                          \n"
 <<(timelog ? "    timerend  (\"RHS assembly for PHI\",t0)\n" : ""             )<<
 "                                                                                \n"
 "    //-----------PETSc assembly for bilinear---------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"PETSc assembly for PHI\",t0)\n" : ""           )<<
 "    A1=ALoc1;//changeOperator(A1, ALoc1);                                       \n"
 "    set(A1,sparams =\"  -ksp_type cg  \");                                      \n"
 <<(timelog ? "    timerend  (\"PETSc assembly for PHI\",t0)\n" : ""           )<<
 "                                                                                \n"
 "    //-------------Linear system solving phase-------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"solving PHI\",t0)\n" : ""                      )<<
 "    phi[] = A1^-1*b1;                                                           \n"
 <<(timelog ? "    timerend  (\"solving PHI\",t0)\n" : ""                      )<<
 "                                                                                \n";

if(energydecomp && constrainHPF && vectorial)
 writeIt
 "                                                                                \n"
 "    //---------------Hybrid phase field constrain-------------------//          \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"Hybrid phase field constrain\",t0)\n"         : "")<<
 "    PsiPlusP1=PsiPlus; PsiMinusP1=PsiMinus;                                     \n"
 "    exchange(A1,PsiPlusP1[],scaled=true);                                       \n"
 "    exchange(A1,PsiMinusP1[],scaled=true);                                      \n"
 "    for(int i=0; i < PsiPlusP1[].n; i++ )                                       \n"
 "      if(PsiPlusP1[][i]<PsiMinusP1[][i])uold[][i*"<<Fdofs<<"+"<<spc<<"]=0.;     \n"    
 <<(timelog ? "    timerend  (\"Hybrid phase field constrain\",t0)\n"         : "");

if(energydecomp && constrainHPF && !vectorial)
 writeIt
 "                                                                                \n"
 "    //---------------Hybrid phase field constrain-------------------//          \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"Hybrid phase field constrain\",t0)\n"         : "")<<
 "    PsiPlusP1=PsiPlus; PsiMinusP1=PsiMinus;                                     \n"
 "    exchange(A1,PsiPlusP1[],scaled=true);                                       \n"
 "    exchange(A1,PsiMinusP1[],scaled=true);                                      \n"
 "    for(int i=0; i < PsiPlusP1[].n; i++ )                                       \n"
 "      if(PsiPlusP1[][i]<PsiMinusP1[][i])phi[][i]=0.;                            \n"    
 <<(timelog ? "    timerend  (\"Hybrid phase field constrain\",t0)\n"         : "");


 writeIt
 "    //------------------Error calculation------------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"NL error checking\",t0)\n" : ""                  )<<
 "    uold[]   = uold[]-u[]                ;                                      \n"
 "    phiold[] = phiold[]-phi[]        ;                                          \n"
 "    real err1Gather,err2Gather;                                                 \n"
 "    real err1Loc=sqrt( intN(Th,qforder=2) ( DPspc*(uold)^2   )  );              \n"
 "    real err2Loc=sqrt( intN(Th,qforder=2) ( DZspc*(phiold)^2 )  );              \n"
 "    mpiAllReduce(err1Loc,err1Gather,mpiCommWorld,mpiSUM);                       \n"
 "    mpiAllReduce(err2Loc,err2Gather,mpiCommWorld,mpiSUM);                       \n"
 <<(timelog ? "    timerend (\"NL error checking\",t0)\n" : ""                   )<<
 "                                                                                \n"
 "    //--------------------Solution update-------------------------//            \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"solution update\",t0)\n" : ""                    )<<
 "    phiold[]=phi[];                                                             \n"
 "    uold[]=u[];                                                                 \n"
 <<(timelog ? "    timerend (\"solution update\",t0)\n" : ""                     )<<
 "                                                                                \n"
 "    //--------------- Convergence conditional---------------------//            \n"
 "                                                                                \n"
 "    if(err1Gather < 1e-2 && err2Gather < 1e-2){                                 \n";
}

if(vectorial){
 writeIt
 "                                                                                \n"
 "    //------------------Error calculation------------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"NL error checking\",t0)\n" : ""                  )<<
 "    uold[]   = uold[]-u[]                                          ;            \n"
 "    real err1Gather                                                ;            \n"
 "    real err1Loc=sqrt( intN(Th,qforder=2) ( DPspc*(uold)^2 )  )    ;            \n"
 "    mpiAllReduce(err1Loc,err1Gather,mpiCommWorld,mpiSUM)           ;            \n"
 <<(timelog ? "    timerend (\"NL error checking\",t0)\n" : ""                   )<<
 "                                                                                \n"
 "    //--------------------Solution update-------------------------//            \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"solution update\",t0)\n" : ""                    )<<
 "    uold[] = u[];                                                               \n"
 <<(timelog ? "    timerend (\"solution update\",t0)\n" : ""                     );

if(energydecomp)
 writeIt
 "                                                                                \n"
 "    //---------------Energy decomposition phase-------------------//            \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"energy decomposition\",t0)\n" : ""               )<<
 "    DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus);                \n"
 <<(timelog ? "    timerend  (\"energy decomposition\",t0)\n" : ""               )<<
 "                                                                                \n";
 
 
if(energydecomp && constrainHPF && vectorial)
 writeIt
 "                                                                                \n"
 "    //---------------Hybrid phase field constrain-------------------//          \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"Hybrid phase field constrain\",t0)\n"         : "")<<
 "    PsiPlusP1=PsiPlus; PsiMinusP1=PsiMinus;                                     \n"
 "    exchange(A1,PsiPlusP1[],scaled=true);                                       \n"
 "    exchange(A1,PsiMinusP1[],scaled=true);                                      \n"
 "    for(int i=0; i < PsiPlusP1[].n; i++ )                                       \n"
 "      if(PsiPlusP1[][i]<PsiMinusP1[][i])uold[][i*"<<Fdofs<<"+"<<spc<<"]=0.;     \n"    
 <<(timelog ? "    timerend  (\"Hybrid phase field constrain\",t0)\n"         : "");

if(energydecomp && constrainHPF && !vectorial)
 writeIt
 "                                                                                \n"
 "    //---------------Hybrid phase field constrain-------------------//          \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"Hybrid phase field constrain\",t0)\n"         : "")<<
 "    PsiPlusP1=PsiPlus; PsiMinusP1=PsiMinus;                                     \n"
 "    exchange(A1,PsiPlusP1[],scaled=true);                                       \n"
 "    exchange(A1,PsiMinusP1[],scaled=true);                                      \n"
 "    for(int i=0; i < PsiPlusP1[].n; i++ )                                       \n"
 "      if(PsiPlusP1[][i]<PsiMinusP1[][i])phi[][i]=0.;                            \n"    
 <<(timelog ? "    timerend  (\"Hybrid phase field constrain\",t0)\n"         : "");


 writeIt
 "                                                                                \n"
 "    //--------------- Convergence conditional---------------------//            \n"
 "                                                                                \n"
 "    if(err1Gather < 1e-2){                                                      \n";

}  //-- [if loop terminator] vectorial ended --//

if(!vectorial)
 writeIt
 "                                                                                \n"
 "      //------------------Screen output norm----------------------//            \n"
 "                                                                                \n"
 "      if(mpirank==0)                                                            \n"
 "      cout.scientific << \"NL iteration number :  [ \"  << iter                 \n"
 "      << \" ]\\nL2 error in [u,phi] :  [ \"    << err1Gather                    \n"
 "      << \" , \" <<  err2Gather << \" ]\"      << endl;                         \n"
 "                                                                                \n";

if(vectorial)
 writeIt
 "                                                                                \n"
 "      //------------------Screen output norm----------------------//            \n"
 "                                                                                \n"
 "      if(mpirank==0)                                                            \n"
 "      cout.scientific << \"NL iteration number :  [ \" << iter                  \n"
 "      << \" ]\\nL2  error  in  [U]  :  [ \" << err1Gather << \" ]\" <<endl;     \n";


 writeIt
 "                                                                                \n"
 "      break;                                                                    \n"
 "    }                                                                           \n"
 "  }                                                                             \n";


if(reactionforce){
 writeIt
 "                                                                                \n"
 "  //-------------------Force calculation-----------------------//               \n"
 "                                                                                \n" 
 <<(timelog ? "  timerbegin(\"force calculation\",t0)\n" : ""                     )<<
 "                                                                                \n"
 "  real forcetotx   = 0., forcetotGathx  = 0. ;                                  \n"
 "  real forcetoty   = 0., forcetotGathy  = 0. ;                                  \n" 
 "  real forcetotz   = 0., forcetotGathz  = 0. ;                                  \n";   
 
 if(reactionforcemethod=="stress-based" && spc==2)
 writeIt
 "                                                                                \n"
 "  forcetotx = intN1(Th,qforder=2,RFOn)(DPspc*( lambda*divergence(u)+2.*mu*dx(u) \n" 
 "                                            + mu*(dx(u1)+dy(u))              ) );\n" 
 "                                                                                \n"
 "  forcetoty = intN1(Th,qforder=2,RFOn)(DPspc*( lambda*divergence(u)+2.*mu*dy(u) \n" 
 "                                            + mu*(dx(u1)+dy(u))             ) );\n"  
 "                                                                                \n"
 "                                                                                \n"; 

 if(reactionforcemethod=="stress-based" && spc==3)
 writeIt
 "                                                                                \n"
 "  forcetotx = intN1(Th,qforder=2,RFOn)(DPspc*( lambda*divergence(u)+2.*mu*dx(u) \n" 
 "                                            + mu*(dx(u1)+dy(u))                 \n" 
 "                                            + mu*(dx(u2)+dz(u))            ) ); \n"   
 "                                                                                \n"
 "  forcetoty = intN1(Th,qforder=2,RFOn)(DPspc*( lambda*divergence(u)+2.*mu*dy(u) \n" 
 "                                            + mu*(dx(u1)+dy(u))                 \n"
 "                                            + mu*(dy(u2)+dz(u1))           ) ); \n"    
 "                                                                                \n"
 "  forcetotz = intN1(Th,qforder=2,RFOn)(DPspc*( lambda*divergence(u)+2.*mu*dz(u) \n" 
 "                                            + mu*(dx(u2)+dz(u))                 \n"
 "                                            + mu*(dy(u2)+dz(u1))           ) ); \n"        
 "                                                                                \n"
 "  mpiAllReduce(forcetotx,forcetotGathx,mpiCommWorld,mpiSUM);                    \n"
 "  mpiAllReduce(forcetoty,forcetotGathy,mpiCommWorld,mpiSUM);                    \n"
 "  mpiAllReduce(forcetotz,forcetotGathz,mpiCommWorld,mpiSUM);                    \n"  
 "                                                                                \n";  

 if(reactionforcemethod=="variational-based" && spc==2)
 writeIt
 "                                                                                \n"
 "  ALoc = varfForce(Vh,Vh,solver=CG,sym=1);  A = ALoc;                           \n"
 "  F[] = A*u[];                                                                  \n"
 "                                                                                \n"
 "  for(int i=0; i < Th.nv; i++){                                                 \n"
 "     if(abs(Th(i).y-1.)<.000001){                                               \n"
 "        forcetotx = forcetotx + F[][i*"<<Fdofs<<"]*DP[i*"<<Fdofs<<"];           \n"
 "        forcetoty = forcetoty + F[][i*"<<Fdofs<<"+1]*DP[i*"<<Fdofs<<"+1];       \n" 
 "     }                                                                          \n"
 "  }                                                                             \n"  
 "                                                                                \n";
 
 if(reactionforcemethod=="variational-based" && spc==3)
 writeIt
 "                                                                                \n"
 "  ALoc = varfForce(Vh,Vh,solver=CG,sym=1);  A = ALoc;                           \n"
 "  F[] = A*u[];                                                                  \n"
 "                                                                                \n"
 "  for(int i=0; i < Th.nv; i++){                                                 \n"
 "     if(abs(Th(i).y-1.)<.000001){                                               \n"
 "        forcetotx = forcetotx + F[][i*"<<Fdofs<<"]*DP[i*"<<Fdofs<<"];           \n"
 "        forcetoty = forcetoty + F[][i*"<<Fdofs<<"+1]*DP[i*"<<Fdofs<<"+1];       \n"
 "        forcetotz = forcetotz + F[][i*"<<Fdofs<<"+2]*DP[i*"<<Fdofs<<"+2];       \n"   
 "     }                                                                          \n"
 "  }                                                                             \n"   
 "                                                                                \n";   

 if(spc==2)
 writeIt
 "                                                                                \n"
 "  mpiAllReduce(forcetotx,forcetotGathx,mpiCommWorld,mpiSUM);                    \n"
 "  mpiAllReduce(forcetoty,forcetotGathy,mpiCommWorld,mpiSUM);                    \n"
 "                                                                                \n"  
 "  if(mpirank==0){                                                               \n" 
 "  ofstream ff(\"force.data\",append);                                           \n"
 "  ff << tr << \"  \" << forcetotGathx*1e-3 <<                                   \n"
 "                         \"  \" << forcetotGathy*1e-3 << endl;                  \n"; 

 if(spc==3)
 writeIt
 "                                                                                \n"
 "  mpiAllReduce(forcetotx,forcetotGathx,mpiCommWorld,mpiSUM);                    \n"
 "  mpiAllReduce(forcetoty,forcetotGathy,mpiCommWorld,mpiSUM);                    \n"
 "  mpiAllReduce(forcetotz,forcetotGathz,mpiCommWorld,mpiSUM);                    \n" 
 "                                                                                \n" 
 "  if(mpirank==0){                                                               \n" 
 "  ofstream ff(\"force.data\",append);                                           \n"
 "  ff << tr << \"  \" << forcetotGathx*1e-3  <<                                  \n"
 "                         \"  \" << forcetotGathy*1e-3  <<                       \n" 
 "                         \"  \" << forcetotGathz*1e-3  <<              endl;    \n"; 
 
 if(plotreaction && spc==2)
 writeIt
 "                                                                                \n" 
 "  pgnuplot<<\"plot \\\"force.data\\\"u 1:2 w p pt 6 ps 2 t \\\"Fx\\\",  \"      \n"
 "          <<\"     \\\"force.data\\\"u 1:3 w p pt 5 ps 2 t \\\"Fy\\\"\\n\";     \n" 
 "  flush(pgnuplot);                                                              \n";
 
 if(plotreaction && spc==3)
 writeIt
 "                                                                                \n" 
 "  pgnuplot<<\"plot \\\"force.data\\\"u 1:2 w p pt 6 ps 2 t \\\"Fx\\\",  \"      \n"
 "          <<\"     \\\"force.data\\\"u 1:3 w p pt 5 ps 2 t \\\"Fy\\\",  \"      \n" 
 "          <<\"     \\\"force.data\\\"u 1:4 w p pt 4 ps 2 t \\\"Fz\\\"\\n\";     \n" 
 "  flush(pgnuplot);                                                              \n"; 

 writeIt
 "  }                                                                             \n" 
 <<(timelog ? "  timerend  (\"force calculation\",t0)\n" : ""                      );
}

if(ParaViewPostProcess)if(!vectorial){
 writeIt
 "                                                                                \n"
 "  //-------Paraview plotting every nth iteration -----------//                  \n"
 "                                                                                \n"
 "  iterout++;                                                                    \n"
 "                                                                                \n"
 <<(timelog ? "  timerbegin(\"ParaView post-processing\",t0)\n" : ""             )<<
 "  if(int(iterout%10)==0){                                                       \n";



 writeIt
 "    savevtk(  \"VTUs/Solution.vtu\"   ,                                         \n"
 "                 Th                 ,                                           \n";

if(PostProcess=="u")
 writeIt
 "              PlotVec(uold)        ,                                            \n";

if(PostProcess=="d")
 writeIt
 "                 phi                ,                                           \n";

if(PostProcess=="ud" || PostProcess=="du")
 writeIt
 "              PlotVec(uold)        ,                                            \n"
 "              phi                  ,                                            \n";


 writeIt
 "                 order=vtuorder     ,                                           \n";
 
if(PostProcess=="u")
 writeIt
 "                 dataname=\"U\"  ,                                             \n";
 
if(PostProcess=="d")
 writeIt
 "                 dataname=\"d\"  ,                                             \n"; 

if(PostProcess=="ud" || PostProcess=="du")
 writeIt   
 "                 dataname=\"U  d\"  ,                                           \n";
 
 writeIt
 "                 append=true                                                    \n"
 "              );                                                                \n";


 writeIt
 "                                                                                \n"
 "    iterout1++;                                                                 \n"
 "  }                                                                             \n"
 <<(timelog ? "  timerend  (\"ParaView post-processing\",t0)\n" : ""             );
}

if(ParaViewPostProcess)if(vectorial){
 writeIt
 "                                                                                \n"
 "  //--------Paraview plotting every nth iteration ----------//                  \n"
 "                                                                                \n"
 "  iterout++;                                                                    \n"
 "                                                                                \n"
 <<(timelog ? "  timerbegin(\"ParaView post-processing\",t0)\n" : ""           )<<
 "                                                                                \n"
 "  if(int(iterout%10)==0){                                                       \n"
 "                                                                                \n"
 "    phi=u2;              														                            \n";


 writeIt
 "    savevtk(  \"VTUs/Solution.vtu\"   ,                                         \n"
 "                 Th                 ,                                           \n";

if(PostProcess=="u")
 writeIt
 "              PlotVec(uold)        ,                                            \n";

if(PostProcess=="d")
 writeIt
 "                 phi                ,                                           \n";

if(PostProcess=="ud" || PostProcess=="du")
 writeIt
 "              PlotVec(uold)        ,                                            \n"
 "              phi                  ,                                            \n";


 writeIt
 "                 order=vtuorder     ,                                           \n";
 
if(PostProcess=="u")
 writeIt
 "                 dataname=\"U\"  ,                                             \n";
 
if(PostProcess=="d")
 writeIt
 "                 dataname=\"d\"  ,                                             \n"; 

if(PostProcess=="ud" || PostProcess=="du")
 writeIt   
 "                 dataname=\"U  d\"  ,                                           \n";


 writeIt
 "                 append=true                                                    \n"
 "              );                                                                \n";



 writeIt
 "                                                                                \n"
 "    iterout1++;                                                                 \n"
 "  }                                                                             \n"
 <<(timelog ? "  timerend  (\"ParaView post-processing\",t0)\n" : ""             );
}

if(debug)if(!vectorial)
 writeIt
 "                                                                                \n"
 "  //-----------------Debug glut plotting----------------------//                \n"
 "                                                                                \n"
 "  plotMPI(Th, phi, P1,  def, real, wait=0, cmm=\"Tr-\"+tr+\"\")                 \n";

if(debug)if(vectorial)
 writeIt
 "                                                                                \n"
 "  //-----------------Debug glut plotting----------------------//                \n"
 "                                                                                \n"
 "  plotMPI(Th, u"<<spc<<", P1,  def0, real, wait=0, cmm=\"Tr-\"+tr+\"\")         \n";


 writeIt
 "                                                                                \n"
 "  //-----------------updating traction----------------//                        \n"
 "                                                                                \n"
 "  tr += dtr;                                                                    \n"
 "}                                                                               \n"
 "                                                                                \n"
 <<(timelog ? "if(mpirank==0)\n" : " "                                            )<<
 (timelog ? "cout << \" all operations ended, they \";\n" : ""                    )<<
 (timelog ? "timerend  (\"solver\",t1)\n" : " "                                )<<
 "                                                                                \n"
 "//-------------------------------THE END------------------------------//        \n";

}  //-- [if loop terminator] !Sequential ended --//

if(!Sequential)if(NonLinearMethod=="Newton-Raphson"){
 writeIt
 "                                                                                \n"
 "real TractionTotal=tr;                                                          \n"
 "                                                                                \n"
 "//==============================================================================\n"
 "// -------  Traction loading loop  -------                                      \n"
 "//==============================================================================\n"
 "                                                                                \n"
 "while (TractionTotal <= maxtr){                                                 \n"
 "                                                                                \n"
 "  if(mpirank==0)                                                                \n"
 "  cout.scientific<<\"-----------------------------------------------------\\n\" \n"
 "  <<  \"Applied traction \" << TractionTotal << \"\\n\" << endl;                \n"
 "                                                                                \n"
 "  if (TractionTotal >= 5e-3){                                                   \n"
 "    tr = 1e-6; dtr = 1e-6;}                                                     \n"
 "                                                                                \n";
 
 if(constrainHPF)
 writeIt
 "                                                                                \n"
 <<(timelog ? "  timerbegin(\"copying solution befor NL iterations\",t0)\n" : ""  )<< 
 "   up[]=uold[];                                                              \n"
 <<(timelog ? "  timerend  (\"copying solution befor NL iterations\",t0)\n" : ""  )<<
 "                                                                                \n"; 
 
 writeIt
 "                                                                                \n"
 "  //-----------------------Nonlinear loop------------------------//             \n"
 "                                                                                \n"
 "  for(int iter=0; iter<100; iter++){                                            \n"
 "                                                                                \n"
 "    //--------------------Assembly for linear----------------------//           \n"
 "                                                                                \n"
 <<(timelog ? "  timerbegin(\"RHS assembly for U\",t0)\n" : ""                 )<<
 "    b = elast(0,Vh);                                                            \n"
 <<(timelog ? "  timerend  (\"RHS assembly for U\",t0)\n" : ""                 )<<
 "                                                                                \n"
 "    //----------------Assembly for bilinear----------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"matrix assembly for U\",t0)\n" : ""            )<<
 "    ALoc = elast(Vh,Vh,solver=CG,sym=1);                                        \n"
 <<(timelog ? "    timerend  (\"matrix assembly for U\",t0)\n" : ""            )<<
 "                                                                                \n";
 
 
 if(dirichletpointconditions>=1){
 writeIt
 "                                                                                \n"
 "//---------Additional assembly for A & b (point bounday condition)----------//  \n"
 "                                                                                \n"
 <<(timelog ? "  timerbegin(\"point Dirichlet assembly\",t0)\n" : ""            )<<
 "                                                                                \n";
 
 for(int i=0; i<dirichletpointconditions; i++)
 writeIt 
 "  ApplyPointBc"<<i<<"(ALoc,b);                                                  \n"; 

 writeIt
 "                                                                                \n" 
 <<(timelog ? "  timerend(\"point Dirichlet assembly\",t0)\n" : ""              );
 }
 
 writeIt
 "    //-----------PETSc assembly for bilinear---------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"PETSc assembly for U\",t0)\n" : ""             )<<
 "    A=ALoc;//changeOperator(A, ALoc);                                           \n"
 "    set(A,sparams =\"  -ksp_type cg  \");                                       \n"
 <<(timelog ? "    timerend  (\"PETSc assembly for U\",t0)\n" : ""             )<<
 "                                                                                \n"
 "    //-------------Linear system solving phase-------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"solving U\",t0)\n" : " "                       )<<
 "    du[] = A^-1*b;                                                              \n"
 <<(timelog ? "    timerend  (\"solving U\",t0)\n" : " "                       )<<
 "                                                                                \n"
 "    //--------------Update of displacement u---------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"Updating U\",t0)\n"         : ""                  )<<
 "    u[] += du[];                                                                \n"
 <<(timelog ? "    timerend  (\"Updating U\",t0)\n"         : ""                  )<<
 "                                                                                \n";

if(!vectorial){
if(energydecomp)
 writeIt
 "                                                                                \n"
 "    //---------------Energy decomposition phase-------------------//            \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"energy decomposition\",t0)\n" : ""             )<<
 "    DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus);                \n"
 <<(timelog ? "    timerend  (\"energy decomposition\",t0)\n" : ""               );


 writeIt
 "                                                                                \n"
 "    //----------------Assembly for bilinear----------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"matrix assembly for PHI\",t0)\n" : ""             )<<
 "    ALoc1 = phase(Vh1,Vh1,solver=CG,sym=1);                                     \n"
 <<(timelog ? "    timerend  (\"matrix assembly PHI\",t0)\n" : ""                 )<<
 "                                                                                \n"
 "    //----------------Assembly for linear------------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"RHS assembly for PHI\",t0)\n" : ""                )<<
 "    b1 = phase(0,Vh1);                                                          \n"
 <<(timelog ? "    timerend  (\"RHS assembly for PHI\",t0)\n" : ""                )<<
 "                                                                                \n"
 "    //-----------PETSc assembly for bilinear---------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"PETSc assembly for PHI\",t0)\n" : ""              )<<
 "    A1=ALoc1;//changeOperator(A1, ALoc1);                                       \n"
 "    set(A1,sparams =\"  -ksp_type cg  \");                                      \n"
 <<(timelog ? "    timerend  (\"PETSc assembly for PHI\",t0)\n" : ""              )<<
 "                                                                                \n"
 "    //-------------Linear system solving phase-------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"solving PHI\",t0)\n" : ""                         )<<
 "    dphi[] = A1^-1*b1;                                                          \n"
 <<(timelog ? "    timerend  (\"solving PHI\",t0)\n" : ""                         )<<
 "                                                                                \n"
 "    //--------------Update of phase-field phi-------------------//              \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"Updating U\",t0)\n"         : ""                  )<<
 "    phi[] += dphi[];                                                            \n"
 <<(timelog ? "    timerend  (\"Updating U\",t0)\n"         : ""                  )<<
 "                                                                                \n";

if(energydecomp && constrainHPF && vectorial)
 writeIt
 "                                                                                \n"
 "    //---------------Hybrid phase field constrain-------------------//          \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"Hybrid phase field constrain\",t0)\n"         : "")<<
 "    PsiPlusP1=PsiPlus; PsiMinusP1=PsiMinus;                                     \n"
 "    exchange(A1,PsiPlusP1[],scaled=true);                                       \n"
 "    exchange(A1,PsiMinusP1[],scaled=true);                                      \n"
 "    for(int i=0; i < PsiPlusP1[].n; i++ )                                       \n"
 "      if(PsiPlusP1[][i]<PsiMinusP1[][i])uold[][i*"<<Fdofs<<"+"<<spc<<"]=0.;     \n"    
 <<(timelog ? "    timerend  (\"Hybrid phase field constrain\",t0)\n"         : "");

if(energydecomp && constrainHPF && !vectorial)
 writeIt
 "                                                                                \n"
 "    //---------------Hybrid phase field constrain-------------------//          \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"Hybrid phase field constrain\",t0)\n"         : "")<<
 "    PsiPlusP1=PsiPlus; PsiMinusP1=PsiMinus;                                     \n"
 "    exchange(A1,PsiPlusP1[],scaled=true);                                       \n"
 "    exchange(A1,PsiMinusP1[],scaled=true);                                      \n"
 "    for(int i=0; i < PsiPlusP1[].n; i++ )                                       \n"
 "      if(PsiPlusP1[][i]<PsiMinusP1[][i])phi[][i]=0.;                            \n"    
 <<(timelog ? "    timerend  (\"Hybrid phase field constrain\",t0)\n"         : "");

/******************************  Old Method **********************************************

 writeIt
 "    //------------------Error calculation------------------------//             \n"
 "                                                                                \n"
 (timelog ? "    timerbegin(\"NL error checking\",t0)\n" : ""                  )
 "    real err1Gather,err2Gather;                                                 \n"
 "    real err1Loc=sqrt( intN(Th,qforder=2) ( DPspc*(du)^2   )  );                \n"
 "    real err2Loc=sqrt( intN(Th,qforder=2) ( DZspc*(dphi)^2 )  );                \n"
 "    mpiAllReduce(err1Loc,err1Gather,mpiCommWorld,mpiSUM);                       \n"
 "    mpiAllReduce(err2Loc,err2Gather,mpiCommWorld,mpiSUM);                       \n"
 (timelog ? "    timerend (\"NL error checking\",t0)\n" : ""                            )
 "                                                                                \n"
 "    //--------------- Convergence conditional---------------------//            \n"
 "                                                                                \n"
 "    if(err1Gather < 1e-2 && err2Gather < 1e-2){                                 \n";
/******************************************************************************************/


 writeIt
 "    //------------------Error calculation------------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"NL error checking\",t0)\n" : ""                )<<
 "    real err1Gather,err2Gather, err1Loc, err2Loc;                               \n"
 "                                                                                \n"
 "        b = b .* DP                                   ;                         \n"
 "        err1Loc = b.l2                                ;                         \n"
 "        err1Loc = err1Loc*err1Loc                     ;                         \n"
 "        mpiAllReduce(err1Loc,err1Gather,mpiCommWorld,mpiSUM)  ;                 \n"
 "        err1Gather = sqrt(err1Gather)                                 ;         \n"
 "                                                                                \n"
 "        b1 = b1 .* DZ                                         ;                 \n"
 "        err2Loc = b1.l2                               ;                         \n"
 "        err2Loc = err2Loc*err2Loc                     ;                         \n"
 "        mpiAllReduce(err2Loc,err2Gather,mpiCommWorld,mpiSUM)  ;                 \n"
 "        err1Gather = sqrt(err2Gather)                                 ;         \n"
 "                                                                                \n"
 <<(timelog ? "    timerend (\"NL error checking\",t0)\n" : ""                 )<<
 "                                                                                \n"
 "    //--------------- Convergence conditional---------------------//            \n"
 "                                                                                \n"
 "    if(err1Gather < 1e-2 && err2Gather < 1e-2){                                 \n";


}

if(vectorial){
 writeIt
 "                                                                                \n"
 "    //------------------Error calculation------------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"NL error checking\",t0)\n" : ""                )<<
 "    uold[]   = uold[]-u[]                                          ;            \n"
 "    real err1Gather                                                ;            \n"
 "    real err1Loc=sqrt( intN(Th,qforder=2) ( DPspc*(uold)^2 )  )    ;            \n"
 "    mpiAllReduce(err1Loc,err1Gather,mpiCommWorld,mpiSUM)           ;            \n"
 <<(timelog ? "    timerend (\"NL error checking\",t0)\n" : ""                   )<<
 "                                                                                \n"
 "    //--------------------Solution update-------------------------//            \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"solution update\",t0)\n" : ""                    )<<
 "    uold[] = u[];                                                               \n"
 <<(timelog ? "    timerend (\"solution update\",t0)\n" : ""                      );

if(energydecomp)
 writeIt
 "                                                                                \n"
 "    //---------------Energy decomposition phase-------------------//            \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"energy decomposition\",t0)\n" : ""                )<<
 "    DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus);                \n"
 <<(timelog ? "    timerend  (\"energy decomposition\",t0)\n" : ""               );
 
if(energydecomp && constrainHPF && vectorial)
 writeIt
 "                                                                                \n"
 "    //---------------Hybrid phase field constrain-------------------//          \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"Hybrid phase field constrain\",t0)\n"         : "")<<
 "    PsiPlusP1=PsiPlus; PsiMinusP1=PsiMinus;                                     \n"
 "    exchange(A1,PsiPlusP1[],scaled=true);                                       \n"
 "    exchange(A1,PsiMinusP1[],scaled=true);                                      \n"
 "    for(int i=0; i < PsiPlusP1[].n; i++ )                                       \n"
 "      if(PsiPlusP1[][i]<PsiMinusP1[][i])uold[][i*"<<Fdofs<<"+"<<spc<<"]=0.;     \n"    
 <<(timelog ? "    timerend  (\"Hybrid phase field constrain\",t0)\n"         : "");

if(energydecomp && constrainHPF && !vectorial)
 writeIt
 "                                                                                \n"
 "    //---------------Hybrid phase field constrain-------------------//          \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"Hybrid phase field constrain\",t0)\n"         : "")<<
 "    PsiPlusP1=PsiPlus; PsiMinusP1=PsiMinus;                                     \n"
 "    exchange(A1,PsiPlusP1[],scaled=true);                                       \n"
 "    exchange(A1,PsiMinusP1[],scaled=true);                                      \n"
 "    for(int i=0; i < PsiPlusP1[].n; i++ )                                       \n"
 "      if(PsiPlusP1[][i]<PsiMinusP1[][i])phi[][i]=0.;                            \n"    
 <<(timelog ? "    timerend  (\"Hybrid phase field constrain\",t0)\n"         : ""); 


 writeIt
 "                                                                                \n"
 "    //--------------- Convergence conditional---------------------//            \n"
 "                                                                                \n"
 "    if(err1Gather < 1e-2){                                                      \n";

}  //-- [if loop terminator] vectorial ended --//

if(!vectorial)
 writeIt
 "                                                                                \n"
 "      //------------------Screen output norm----------------------//            \n"
 "                                                                                \n"
 "      if(mpirank==0)                                                            \n"
 "      cout.scientific << \"NL iteration number :  [ \"  << iter                 \n"
 "      << \" ]\\nL2 error in [u,phi] :  [ \"    << err1Gather                    \n"
 "      << \" , \" <<  err2Gather << \" ]\"      << endl;                         \n"
 "                                                                                \n";

if(vectorial)
 writeIt
 "                                                                                \n"
 "      //------------------Screen output norm----------------------//            \n"
 "                                                                                \n"
 "      if(mpirank==0)                                                            \n"
 "      cout.scientific << \"NL iteration number :  [ \" << iter                  \n"
 "      << \" ]\\nL2  error  in  [U]  :  [ \" << err1Gather << \" ]\" <<endl;     \n";


 writeIt
 "                                                                                \n"
 "      break;                                                                    \n"
 "    }                                                                           \n"
 "                                                                                \n"
 "    TractionIn = 0;                                                             \n"
 "    PhiCracked = 0;                                                             \n"
 "  }                                                                             \n"
 "                                                                                \n"
 "  //-----------------updating traction----------------//                        \n"
 "                                                                                \n"
 "    TractionIn     = tr;                                                        \n"
 "    TractionTotal += dtr;                                                       \n";



if(reactionforce){
 writeIt
 "                                                                                \n"
 "  //-------------------Force calculation-----------------------//               \n"
 "                                                                                \n" 
 <<(timelog ? "  timerbegin(\"force calculation\",t0)\n" : ""                     )<<
 "                                                                                \n"
 "  real forcetotx   = 0., forcetotGathx  = 0. ;                                  \n"
 "  real forcetoty   = 0., forcetotGathy  = 0. ;                                  \n" 
 "  real forcetotz   = 0., forcetotGathz  = 0. ;                                  \n";   
 
 if(reactionforcemethod=="stress-based" && spc==2)
 writeIt
 "                                                                                \n"
 "  forcetotx = intN1(Th,qforder=2,RFOn)(DPspc*( lambda*divergence(u)+2.*mu*dx(u) \n" 
 "                                            + mu*(dx(u1)+dy(u))              ) );\n" 
 "                                                                                \n"
 "  forcetoty = intN1(Th,qforder=2,RFOn)(DPspc*( lambda*divergence(u)+2.*mu*dy(u) \n" 
 "                                            + mu*(dx(u1)+dy(u))             ) );\n"  
 "                                                                                \n"
 "                                                                                \n"; 

 if(reactionforcemethod=="stress-based" && spc==3)
 writeIt
 "                                                                                \n"
 "  forcetotx = intN1(Th,qforder=2,RFOn)(DPspc*( lambda*divergence(u)+2.*mu*dx(u) \n" 
 "                                            + mu*(dx(u1)+dy(u))                 \n" 
 "                                            + mu*(dx(u2)+dz(u))            ) ); \n"   
 "                                                                                \n"
 "  forcetoty = intN1(Th,qforder=2,RFOn)(DPspc*( lambda*divergence(u)+2.*mu*dy(u) \n" 
 "                                            + mu*(dx(u1)+dy(u))                 \n"
 "                                            + mu*(dy(u2)+dz(u1))           ) ); \n"    
 "                                                                                \n"
 "  forcetotz = intN1(Th,qforder=2,RFOn)(DPspc*( lambda*divergence(u)+2.*mu*dz(u) \n" 
 "                                            + mu*(dx(u2)+dz(u))                 \n"
 "                                            + mu*(dy(u2)+dz(u1))           ) ); \n"        
 "                                                                                \n"
 "  mpiAllReduce(forcetotx,forcetotGathx,mpiCommWorld,mpiSUM);                    \n"
 "  mpiAllReduce(forcetoty,forcetotGathy,mpiCommWorld,mpiSUM);                    \n"
 "  mpiAllReduce(forcetotz,forcetotGathz,mpiCommWorld,mpiSUM);                    \n"  
 "                                                                                \n";  

 if(reactionforcemethod=="variational-based" && spc==2)
 writeIt
 "                                                                                \n"
 "  ALoc = varfForce(Vh,Vh,solver=CG,sym=1);  A = ALoc;                           \n"
 "  F[] = A*u[];                                                                  \n"
 "                                                                                \n"
 "  for(int i=0; i < Th.nv; i++){                                                 \n"
 "     if(abs(Th(i).y-1.)<.000001){                                               \n"
 "        forcetotx = forcetotx + F[][i*"<<Fdofs<<"]*DP[i*"<<Fdofs<<"];           \n"
 "        forcetoty = forcetoty + F[][i*"<<Fdofs<<"+1]*DP[i*"<<Fdofs<<"+1];       \n" 
 "     }                                                                          \n"
 "  }                                                                             \n"  
 "                                                                                \n";
 
 if(reactionforcemethod=="variational-based" && spc==3)
 writeIt
 "                                                                                \n"
 "  ALoc = varfForce(Vh,Vh,solver=CG,sym=1);  A = ALoc;                           \n"
 "  F[] = A*u[];                                                                  \n"
 "                                                                                \n"
 "  for(int i=0; i < Th.nv; i++){                                                 \n"
 "     if(abs(Th(i).y-1.)<.000001){                                               \n"
 "        forcetotx = forcetotx + F[][i*"<<Fdofs<<"]*DP[i*"<<Fdofs<<"];           \n"
 "        forcetoty = forcetoty + F[][i*"<<Fdofs<<"+1]*DP[i*"<<Fdofs<<"+1];       \n"
 "        forcetotz = forcetotz + F[][i*"<<Fdofs<<"+2]*DP[i*"<<Fdofs<<"+2];       \n"   
 "     }                                                                          \n"
 "  }                                                                             \n"   
 "                                                                                \n";   

 if(spc==2)
 writeIt
 "                                                                                \n"
 "  mpiAllReduce(forcetotx,forcetotGathx,mpiCommWorld,mpiSUM);                    \n"
 "  mpiAllReduce(forcetoty,forcetotGathy,mpiCommWorld,mpiSUM);                    \n"
 "                                                                                \n"  
 "  if(mpirank==0){                                                               \n" 
 "  ofstream ff(\"force.data\",append);                                           \n"
 "  ff << TractionTotal << \"  \" << forcetotGathx*1e-3 <<                        \n"
 "                         \"  \" << forcetotGathy*1e-3 << endl;                  \n"; 

 if(spc==3)
 writeIt
 "                                                                                \n"
 "  mpiAllReduce(forcetotx,forcetotGathx,mpiCommWorld,mpiSUM);                    \n"
 "  mpiAllReduce(forcetoty,forcetotGathy,mpiCommWorld,mpiSUM);                    \n"
 "  mpiAllReduce(forcetotz,forcetotGathz,mpiCommWorld,mpiSUM);                    \n" 
 "                                                                                \n" 
 "  if(mpirank==0){                                                               \n" 
 "  ofstream ff(\"force.data\",append);                                           \n"
 "  ff << TractionTotal << \"  \" << forcetotGathx*1e-3  <<                       \n"
 "                         \"  \" << forcetotGathy*1e-3  <<                       \n" 
 "                         \"  \" << forcetotGathz*1e-3  <<              endl;    \n"; 
 
 if(plotreaction && spc==2)
 writeIt
 "                                                                                \n" 
 "  pgnuplot<<\"plot \\\"force.data\\\"u 1:2 w p pt 6 ps 2 t \\\"Fx\\\",  \"      \n"
 "          <<\"     \\\"force.data\\\"u 1:3 w p pt 5 ps 2 t \\\"Fy\\\"\\n\";     \n" 
 "  flush(pgnuplot);                                                              \n";
 
 if(plotreaction && spc==3)
 writeIt
 "                                                                                \n" 
 "  pgnuplot<<\"plot \\\"force.data\\\"u 1:2 w p pt 6 ps 2 t \\\"Fx\\\",  \"      \n"
 "          <<\"     \\\"force.data\\\"u 1:3 w p pt 5 ps 2 t \\\"Fy\\\",  \"      \n" 
 "          <<\"     \\\"force.data\\\"u 1:4 w p pt 4 ps 2 t \\\"Fz\\\"\\n\";     \n" 
 "  flush(pgnuplot);                                                              \n"; 

 writeIt
 "  }                                                                             \n" 
 <<(timelog ? "  timerend  (\"force calculation\",t0)\n" : ""                      );
}


if(ParaViewPostProcess)if(!vectorial){
 writeIt
 "                                                                                \n"
 "  //-------Paraview plotting every nth iteration -----------//                  \n"
 "                                                                                \n"
 "  iterout++;                                                                    \n"
 "                                                                                \n"
 <<(timelog ? "  timerbegin(\"ParaView post-processing\",t0)\n" : ""              )<<
 "  if(int(iterout%10)==0){                                                       \n";



 writeIt
 "    savevtk(  \"VTUs/Solution.vtu\"   ,                                         \n"
 "                 Th                 ,                                           \n";

if(PostProcess=="u")
 writeIt
 "              PlotVec(uold)        ,                                            \n";

if(PostProcess=="d")
 writeIt
 "                 phi                ,                                           \n";

if(PostProcess=="ud" || PostProcess=="du")
 writeIt
 "              PlotVec(uold)        ,                                            \n"
 "              phi                  ,                                            \n";


 writeIt
 "                 order=vtuorder     ,                                           \n";
 
if(PostProcess=="u")
 writeIt
 "                 dataname=\"U\"  ,                                             \n";
 
if(PostProcess=="d")
 writeIt
 "                 dataname=\"d\"  ,                                             \n"; 

if(PostProcess=="ud" || PostProcess=="du")
 writeIt   
 "                 dataname=\"U  d\"  ,                                           \n";
 writeIt
 "                 append=true                                                    \n"
 "              );                                                                \n"
 "                                                                                \n"
 "    iterout1++;                                                                 \n"
 "  }                                                                             \n"
 <<(timelog ? "  timerend  (\"ParaView post-processing\",t0)\n" : ""              );
}

if(ParaViewPostProcess)if(vectorial){
 writeIt
 "                                                                                \n"
 "  //--------Paraview plotting every nth iteration ----------//                  \n"
 "                                                                                \n"
 "  iterout++;                                                                    \n"
 "                                                                                \n"
 <<(timelog ? "  timerbegin(\"ParaView post-processing\",t0)\n" : ""              )<<
 "                                                                                \n"
 "  if(int(iterout%10)==0){                                                       \n"
 "                                                                                \n"
 "    fespace Vhplot(Th,P1); Vhplot phi=u2;              //interpolation for phi  \n";


 writeIt
 "    savevtk(  \"VTUs/Solution.vtu\"   ,                                         \n"
 "                 Th                 ,                                           \n";

if(PostProcess=="u")
 writeIt
 "              PlotVec(uold)        ,                                            \n";

if(PostProcess=="d")
 writeIt
 "                 phi                ,                                           \n";

if(PostProcess=="ud" || PostProcess=="du")
 writeIt
 "              PlotVec(uold)        ,                                            \n"
 "              phi                  ,                                            \n";


 writeIt
 "                 order=vtuorder     ,                                           \n";
 
if(PostProcess=="u")
 writeIt
 "                 dataname=\"U\"  ,                                             \n";
 
if(PostProcess=="d")
 writeIt
 "                 dataname=\"d\"  ,                                             \n"; 

if(PostProcess=="ud" || PostProcess=="du")
 writeIt   
 "                 dataname=\"U  d\"  ,                                          \n";



 writeIt
 "                 append=true                                                    \n"
 "              );                                                                \n"
 "                                                                                \n"
 "    iterout1++;                                                                 \n"
 "  }                                                                             \n"
 <<(timelog ? "  timerend  (\"ParaView post-processing\",t0)\n" : ""              );
}

if(debug)if(!vectorial)
 writeIt
 "                                                                                \n"
 "  //-----------------Debug glut plotting----------------------//                \n"
 "                                                                                \n"
 "  plotMPI(Th, phi, P1,  def, real, wait=0, cmm=\"Tr-\"+tr+\"\")                 \n";

if(debug)if(vectorial)
 writeIt
 "                                                                                \n"
 "  //-----------------Debug glut plotting----------------------//                \n"
 "                                                                                \n"
 "  plotMPI(Th, u"<<spc<<", P1,  def0, real, wait=0, cmm=\"Tr-\"+tr+\"\")         \n";


 writeIt
 "                                                                                \n"
 "}                                                                               \n"
 "                                                                                \n"
 <<(timelog ? "if(mpirank==0)\n" : " "                                            )<<
 (timelog ? "cout << \" all operations ended, they \";\n" : ""                    )<<
 (timelog ? "timerend  (\"solver\",t1)\n" : " "                                   )<<
 "                                                                                \n"
 "//-------------------------------THE END------------------------------//        \n";

}  //-- [if loop terminator] !Sequential ended --//

}  //-- [if loop terminator] hybrid-phase-field ended --//

if(Model=="Mazar"){
 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "//  ------- Variable initilization -------                                      \n"
 "//==============================================================================\n"
 "                                                                                \n"
 "      duimp         = 0.       ;                                                \n"
 "      intVar[]      = kappa0   ;                                                \n"
 "      mufield[]     = mu       ;                                                \n"
 "      lambdafield[] = lambda   ;                                                \n"
 "                                                                                \n"
 "//==============================================================================\n"
 "//  ------- Quasistatic loop for linear assembly and solving -------            \n"
 "//==============================================================================\n"
 "                                                                                \n"
 "  for (int n = 0; n < npas; n++){                                               \n"
 "                                                                                \n"
 "    if(mpirank == 0)                                                            \n"
 "      cout <<\"============ \"<<\"Time step \"<< n <<\" ============ \\n\";     \n"
 "                                                                                \n"
 "  //---------------Nonlinear Newton-Rapsons loop------------------//            \n"
 "                                                                                \n"
 "   for (int i = 0; i <= iterMaxNR; i++){                                        \n"
 "                                                                                \n"
 "    //----------Adjust Dirichlet boundary conditions--------------//            \n"
 "                                                                                \n"
 "     if (i>=1) duimp = 0.;                                                      \n"
 "                                                                                \n"
 "    //--------------------Assembly for linear---------------------//            \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"RHS assembly for U\",t0)\n" : ""                  )<<
 "     b = varIncr(0,Vh);                                                         \n"
 <<(timelog ? "    timerend  (\"RHS assembly for U\",t0)\n" : ""                  )<<
 "                                                                                \n"
 "    //------------------Error calculation------------------------//             \n"
 "                                                                                \n"
 "     if(i>0){                                                                   \n"
 <<(timelog ? "       timerbegin(\"NL error checking\",t0)\n" : ""                )<<
 "        b = b .* DP                                         ;                   \n"
 "        real errLoc, err                                 ;                      \n"
 "        errLoc = b.l2                                  ;                        \n"
 "        errLoc = errLoc*errLoc                          ;                       \n"
 "        mpiAllReduce(errLoc,err,mpiCommWorld,mpiSUM)  ;                         \n"
 "        err = sqrt(err)                                  ;                      \n"
 "                                                                                \n"
 "        if(mpirank == 0)                                                        \n"
 "        cout << \"    iteration =\" << i << \", NR error =\" << err << endl ;   \n"
 <<(timelog ? "       timerend (\"NL error checking\",t0)\n" : ""                 )<<
 "       if(err <= tol) break;                                                    \n"
 "     }                                                                          \n"

 "                                                                                \n"
 "    //----------------Assembly for bilinear----------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"matrix assembly for U\",t0)\n" : ""               )<<
 "     ALoc = varIncr(Vh,Vh);                                                     \n"
 <<(timelog ? "    timerend  (\"matrix assembly for U\",t0)\n" : ""               )<<
 "                                                                                \n"
 "    //-----------PETSc assembly for bilinear---------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"PETSc assembly for U\",t0)\n" : ""                )<<
 "    A=ALoc;//changeOperator(A, ALoc);                                           \n"
 "     set(A,sparams =\"  -ksp_type cg   -ksp_rtol 1e-15 \");                     \n"
 <<(timelog ? "    timerend  (\"PETSc assembly for U\",t0)\n" : ""                )<<
 "                                                                                \n"
 "    //-------------Linear system solving phase-------------------//             \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"solving U\",t0)\n" : ""                           )<<
 "     du[] = A^-1*b;                                                             \n"
 <<(timelog ? "    timerend  (\"solving U\",t0)\n" : ""                           )<<
 "                                                                                \n"
 "    //-------------Intermediate solution update-------------------//            \n"
 "                                                                                \n"
 <<(timelog ? "    timerbegin(\"solution update\",t0)\n" : ""                     )<<
 "     u[]   += du[]  ;                                                           \n"
 "                                                                                \n"
 "    //----------Damage field calulation using Mazrs model---------//            \n";


if(useGFP){
 writeIt
 "                                                                                \n";
if(spc==2)
 writeIt
 "     defStrain(strain) = [epsilon(u)[0]          ,                              \n"
 "                          epsilon(u)[2]/sqrt(2.) ,                              \n"
 "                          epsilon(u)[1]                                         \n"
 "                         ];                                                     \n"
 "                                                                                \n";
if(spc==3)
 writeIt
 "     defStrain(strain) = [epsilon(u)[0]          ,                              \n"
 "                          epsilon(u)[5]/sqrt(2.) ,                              \n"
 "                          epsilon(u)[4]/sqrt(2.) ,                              \n"
 "                          epsilon(u)[1]          ,                              \n"
 "                          epsilon(u)[3]/sqrt(2.) ,                              \n"
 "                          epsilon(u)[2]                                         \n"
 "                         ];                                                     \n";


 writeIt
 "     GFPMazarsDamageUpdate(strain[],intVar[],damage[],kappa0,kappac);           \n";
}
else{ 
 writeIt
 "                                                                                \n"
 "     e11 = epsilon(u)[0] ;                                                      \n"
 "     e22 = epsilon(u)[1] ;                                                      \n"
 "     e12 = epsilon(u)[2]/sqrt(2.) ;                                             \n"
 "                                                                                \n"
 "     ep1=0.5*(e11+e22+sqrt((e11-e22)^2+4*e12^2));                               \n"
 "     ep2=0.5*(e11+e22-sqrt((e11-e22)^2+4*e12^2));                               \n"
 "                                                                                \n"
 "     eqStrain = sqrt((max(0,ep1))^2 + (max(0,ep2))^2)  ;  // Mazars Eq strain   \n"
 "                                                                                \n"
 "     intVar = (intVar < eqStrain ? eqStrain : intVar);                          \n"
 "                                                                                \n"
 "     damage = 1-(kappa0/intVar)*exp(-(intVar-kappa0)/(kappac-kappa0));          \n"
 "     damage = floor(100000.*damage)/100000. ;                                   \n";
}


 writeIt
 "                                                                                \n"
 <<(timelog ? "    timerend  (\"solution update\",t0)\n" : " "                   )<<
 "                                                                                \n"
 "  }                                                                             \n"
 "                                                                                \n"
 "  //----------Adjust Dirichlet boundary conditions--------------//              \n"
 "                                                                                \n"
 "  duimp = Duimp ;                                                               \n";


if(pipegnu){
 writeIt
 "                                                                                \n"
 "  //-------------------Force calculation-----------------------//               \n"
 "                                                                                \n"
 <<(timelog ? "  timerbegin(\"force calculation\",t0)\n" : ""                     )<<
 "   real ForceXloc , ForceXGather ;                                              \n"
 "   ForceXloc = intN1(Th,4,qforder=2)                                            \n"
 "                          (DPspc*(1-damage)*stress(u,lambdafield,mufield)[0]);  \n"
 "   mpiAllReduce(ForceXloc,ForceXGather,mpiCommWorld,mpiSUM);                    \n"
 "                                                                                \n"
 "   if(mpirank==0){                                                              \n"
 "     ofstream outputFile(\"output.data\", append);                              \n"
 "     outputFile << n*Duimp << \" \" << ForceXGather << endl;                    \n";

if(plotreaction)
 writeIt
 "     pgnuplot                                                                   \n"
 "      <<\"plot\"                                                                \n"
 "      <<\"\\\"output.data\\\"\"                                                 \n"
 "      <<\"u ($1):($2) w lp lw 2 pt 7 ps 2 notitle\"                             \n"
 "      <<\"\\n\";                                                                \n"
 "     flush(pgnuplot);                                                           \n";


 writeIt
 "   }                                                                            \n"
 <<(timelog ? "  timerend  (\"force calculation\",t0)\n" : ""                      );

}  //-- [if loop terminator]  pipegnu ended --//


 writeIt
 "}                                                                               \n"
 "                                                                                \n"
 <<(timelog ? "if(mpirank==0)\n" : " "                                            )<<
 (timelog ? "cout << \" all operations ended, they \";\n" : " "                   )<<
 (timelog ? "timerend  (\"solver\",t1)\n" : " "                                   )<<
 "                                                                                \n"
 "//-------------------------------THE END------------------------------//        \n";
}
