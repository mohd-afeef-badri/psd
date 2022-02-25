//=====================================================================================
// ------ Elasto-Plastic Mechanics for the LinearFormBuilderAndSolver.edp file ------
//=====================================================================================


 writeIt
 "                                                                                \n"
 "if(mpirank==0)                                                                  \n"
 "  cout                                                                          \n"
 "  << \"\\n#---------------------------------------------------------------\\n\" \n"
 "  << \"# TimeStep\tPressure\tNRiterations\tRelResidual\"                        \n"
 "  << \"\\n#---------------------------------------------------------------\\n\" \n"
 "  <<endl;                                                                       \n"
 "                                                                                \n"
 "//==============================================================================\n"
 "//  ------------------------------------------------------------                \n"
 "//  ------- Algorithm below is explained here -------                           \n"
 "//  ------------------------------------------------------------                \n"
 "//    Loop 1 : TlMaxItr;            # Time Loop                                 \n"
 "//      update_load();                                                          \n"
 "//      assemble_linear_system();   # Assemble A,b                              \n"
 "//      calculate_residual();       # L_2(b)                                    \n"
 "//      Loop 1 : NrMaxItr;          # Newton-Raphsons Loop                      \n"
 "//        solve_linear_system();    # du = A^-1*b                               \n"
 "//        update_displacements();   # u += du                                   \n"
 "//        update_stains();                                                      \n"
 "//        mfront_update();                                                      \n"
 "//        assemble_linear_system();                                             \n"
 "//        calculate_residual();                                                 \n"
 "//        check_convergence();                                                  \n"
 "//        exit_if_converged();                                                  \n"
 "//  ------------------------------------------------------------                \n"
 "//==============================================================================\n"
 "                                                                                \n"
 "for (int i=0; i<TlMaxItr; i++){  // Quas-time step                              \n"
 "                                                                                \n"
 "  tl = sqrt( 1.1/TlMaxItr*(i+1) );                                              \n"
 "                                                                                \n"
 "  //--------------Assembly for linear system---------//                         \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"linear-system Assembly\",t0)\n" : ""                 )<<
 "  ALoc = elast(Vh,Vh,solver=CG,sym=1);                                          \n"
 "  A = ALoc ;                                                                    \n"
 "  b = elast(0,Vh);                                                              \n"
<<(timelog ? "  timerend  (\"linear-system assembly\",t0)\n" : ""                 )<<
 "                                                                                \n"
 "  //------residual  calculation---------//                                      \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"residual checking\",t0)\n" : ""                      )<<
 "  real resGather,  resLoc ;                                                     \n"
 "                                                                                \n"
 "  b = b .* DP                                   ;                               \n"
 "  resLoc = b.l2                                ;                                \n"
 "  resLoc = resLoc*resLoc                     ;                                  \n"
 "  mpiAllReduce(resLoc,resGather,mpiCommWorld,mpiSUM);                           \n"
 "  resGather = sqrt(resGather) ;                                                 \n"
 "                                                                                \n"
<<(timelog ? "  timerend (\"residual checking\",t0)\n" : ""                       )<<
 "                                                                                \n"
 "  nRes0 = resGather;                                                            \n"
 "  nRes = nRes0;                                                                 \n"
 "                                                                                \n"
 "  niter = 0;                                                                    \n"
 "                                                                                \n"
 "  while(nRes/nRes0 > EpsNrCon && niter <= NrMaxItr){  // Newton-Raphsons        \n"
 "                                                                                \n"
 "    niter++;                                                                    \n"
 "                                                                                \n"
 "    //---------------Linear-system solving-----------//                         \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"Linear-system solving\",t0)\n" : ""                  )<<
 "    set(A,sparams =\" -ksp_type cg -ksp_rtol 1e-9 \");                          \n"
 "    du[] = A^-1*b;                                                              \n"
<<(timelog ? "  timerend(\"Linear-system solving\",t0)\n" : ""                     )<<
 "                                                                                \n"
 "    //---------------Update Solution---------------------//                     \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"Solution update\",t0)\n" : ""                        )<<
 "    u[] += du[];                                                                  \n"
<<(timelog ? "  timerend(\"Solution update\",t0)\n" : ""                          )<<
 "                                                                                \n"
 "    //-----Update Stress using Mfront-------------------//                      \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"Stress update via MFront\",t0)\n" : ""               )<<
 "                                                                                \n";

 if(spc==2)
 writeIt
 "    [Eps11,Eps22,Eps12] = epsilon(u);                                           \n";

 if(spc==3)
 writeIt
 "    [Eps11,Eps22,Eps33,Eps12,Eps13,Eps23] = epsilon(u);                         \n";

 writeIt
 "                                                                               \n"
 "    PsdMfrontHandler( MaterialBehaviour                                      , \n"
 "                          mfrontBehaviourHypothesis = MaterialHypothesis     , \n"
 "                          mfrontPropertyNames       = PropertyNames          , \n"
 "                          mfrontPropertyValues      = PropertyValues         , \n"
 "                          mfrontMaterialTensor      = Mt11[]                 , \n"
 "                          mfrontStrainTensor        = Eps11[]                , \n"
 "                          mfrontStressTensor        = Sig11[]           //   , \n"
 "//                        mfrontStateVariable       = Isv1[]                   \n"
 "                        );                                                     \n"
<<(timelog ? "  timerend(\"Stress update via MFront\",t0)\n" : ""                 )<<
 "                                                                               \n"
 "                                                                               \n"
 "    //--------------Assembly for linear system---------//                      \n"
 "                                                                               \n"
<<(timelog ? "  timerbegin(\"linear-system Assembly\",t0)\n" : ""                )<<
 "    ALoc = elast(Vh,Vh,solver=CG,sym=1);                                       \n"
 "    A = ALoc ;                                                                 \n"
 "    b = elast(0,Vh);                                                           \n"
<<(timelog ? "  timerend  (\"linear-system assembly\",t0)\n" : ""                )<<
 "                                                                               \n"
 "    //------residual  calculation---------//                                   \n"
 "                                                                               \n"
<<(timelog ? "  timerbegin(\"residual checking\",t0)\n" : ""                     )<<
 "    real res1Gather,  res1Loc ;                                                \n"
 "                                                                               \n"
 "    b = b .* DP                                   ;                            \n"
 "    res1Loc = b.l2                                ;                            \n"
 "    res1Loc = res1Loc*res1Loc                     ;                            \n"
 "    mpiAllReduce(res1Loc,res1Gather,mpiCommWorld,mpiSUM);                      \n"
 "    res1Gather = sqrt(res1Gather) ;                                            \n"
 "                                                                               \n"
 "    nRes = res1Gather;                                                         \n"
<<(timelog ? "  timerend (\"residual checking\",t0)\n" : ""                      )<<
 "                                                                               \n"
 "    if(niter==NrMaxItr)                                                        \n"
 "      if(mpirank==0)                                                           \n"
 "         cout << \"Error Newton-Raphsons iterations maxed out\" << endl;       \n"
 "                                                                               \n"
 "  }                                                                            \n"
 "  //------------------Screen output ----------------------//                   \n"
 "                                                                               \n"
 "  if(mpirank==0)                                                               \n"
 "    cout.scientific                                                            \n"
 "    << \" \" << i << \"\\t\\t\" << tl*Qlim  << \"\\t\" << niter  << \"\\t\\t\" << nRes \n"
 "    << endl;                                                                   \n"
 "                                                                               \n";

 if(ParaViewPostProcess){
 writeIt
 "                                                                                \n"
 "  //-----------------ParaView plotting--------------//                          \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"ParaView plotting\",t0)\n" : ""                      );

 writeIt
 "    savevtk(  \"VTUs/Solution.vtu\"   ,                                         \n"
 "                 Th                 ,                                           \n";

 if(PostProcess=="u")
 writeIt
 "              PlotVec(u)        ,                                               \n"
 "              dataname=\"U\"       ,                                            \n";

 writeIt
 "                 order=vtuorder     ,                                           \n"
 "                 append=i ? true : false                                        \n"
 "              );                                                                \n";

 writeIt
 (timelog ? "  timerend(\"ParaView plotting\",t0)\n" : ""                          );

 }

 if(debug)
 writeIt
 "                                                                               \n"
 "    //-------------Debug glut plotting------------------//                     \n"
 "                                                                               \n"
 "    macro viz(i)i//                                                            \n"
 "    plotMPI(Th, u, P1,  viz, real, wait=0, cmm=\"displacement\")               \n"
 "                                                                               \n";

 writeIt
 "}                                                                               \n"
 "                                                                                \n"
 "if(mpirank==0)                                                                  \n"
 "  cout                                                                          \n"
 "  << \"\\n#---------------------------------------------------------------\\n\" \n"
 "  <<endl;                                                                       \n"
 "                                                                                \n";
