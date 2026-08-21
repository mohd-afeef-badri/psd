//=====================================================================================
// ------ Elasto-Plastic Mechanics for the LinearFormBuilderAndSolver.edp file ------
//=====================================================================================

if(useMfront){
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
 "  startProcedure(\"linear-system Assembly\",t0);                                \n"
 "  ALoc = elast(Vh,Vh,solver=CG,sym=1);                                          \n"
 "  A = ALoc ;                                                                    \n"
 "  b = elast(0,Vh);                                                              \n"
 "  endProcedure  (\"linear-system assembly\",t0)                                 \n"
 "                                                                                \n"
 "  //------residual  calculation---------//                                      \n"
 "                                                                                \n"
 "  startProcedure(\"residual checking\",t0)                                      \n"
 "  real resGather,  resLoc ;                                                     \n"
 "                                                                                \n"
 "  b = b .* DP                                   ;                               \n"
 "  resLoc = b.l2                                ;                                \n"
 "  resLoc = resLoc*resLoc                     ;                                  \n"
 "  mpiAllReduce(resLoc,resGather,mpiCommWorld,mpiSUM);                           \n"
 "  resGather = sqrt(resGather) ;                                                 \n"
 "                                                                                \n"
 "  endProcedure (\"residual checking\",t0)                                       \n"
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
 "  startProcedure(\"Linear-system solving\",t0)                                  \n"
 "    set(A,sparams =\" -ksp_type cg -ksp_rtol 1e-9 \");                          \n"
 "    du[] = A^-1*b;                                                              \n"
 "  endProcedure(\"Linear-system solving\",t0)                                    \n"
 "                                                                                \n"
 "    //---------------Update Solution---------------------//                     \n"
 "                                                                                \n"
 "  startProcedure(\"Solution update\",t0)                                        \n"
 "    u[] += du[];                                                                \n"
 "  endProcedure(\"Solution update\",t0)                                          \n"
 "                                                                                \n"
 "    //-----Update Stress using Mfront-------------------//                      \n"
 "                                                                                \n"
 "  startProcedure(\"Stress update via MFront\",t0)                               \n"
 "                                                                                \n";
}

if(!useMfront){
codeSnippet R""""(

if(mpirank==0)
  cout
  << "\n#-----------------------------------------------------------------\n"
  << "# TimeStep\tPressure\tNRiterations\tRelativeResidual"
  << "\n#-----------------------------------------------------------------\n"
  << endl;

//==============================================================================
//  ------------------------------------------------------------
//  ------- Algorithm below is explained here -------
//  ------------------------------------------------------------
//    Loop 1 : TlMaxItr;             # Quasi-time/load loop
//      update_load();
//      initialize_increment();      # Δu = 0
//      restore_converged_state();   # Stress and plastic history
//      initialize_elastic_tangent();
//      assemble_linear_system();    # Assemble A,b
//      calculate_residual();        # L_2(b)
//      Loop 2 : NrMaxItr;           # Newton-Raphson loop
//        solve_linear_system();     # du = A^-1*b
//        update_increment();        # Δu += du
//        compute_trial_state();     # Elastic trial stress
//        evaluate_yield_function();
//        radial_return_update();    # Stress and plastic increment
//        update_consistent_tangent();
//        assemble_linear_system();
//        calculate_residual();
//        check_convergence();
//        exit_if_converged();
//      exit_if_not_converged();
//      commit_displacements();      # u += Δu
//      commit_internal_variables(); # Stress and plastic history
//  ------------------------------------------------------------
//==============================================================================

// Native small-strain J2 plasticity with linear isotropic hardening.
// The 2D displacement problem is plane strain; sigma_zz is retained by the
// local constitutive update. Tensor shear components use Kelvin notation.
// Relative Newton-increment norm: ε = ‖Δu‖₂ / (1 + ‖u‖₂).

for (int i=0; i<TlMaxItr; i++) {

  // --- update_load ---- //
  tl = sqrt(1.1/TlMaxItr*(i+1));

  // --- initialize_increment ---- //
  startProcedure("increment initialization",t0)
  Du[] = 0.;
  du[] = 0.;
  niter = 0;
  endProcedure("increment initialization",t0)

  // --- restore_converged_state ---- //
  startProcedure("converged state restoration",t0)
  [Sig11,Sig22,Sig12] = [SigOld11,SigOld22,SigOld12]; 
  Sig33 = SigOld33;
  [Mt11,Mt12,Mt13,Mt22,Mt23,Mt33]
      = [lambda+2.*mu,lambda,0.,lambda+2.*mu,0.,2.*mu];
  endProcedure("converged state restoration",t0)

  // --- assemble_linear_system ---- //
  startProcedure("linear-system assembly",t0)
  ALoc = elast(Vh,Vh,solver=CG,sym=1);
  A = ALoc;
  b = elast(0,Vh);
  endProcedure("linear-system assembly",t0)

  // --- calculate_residual ---- //
  startProcedure("residual checking",t0)
  b = b .* DP;
  real resLoc = b.l2;
  real resGather = 0.;
  resLoc = resLoc*resLoc;
  mpiAllReduce(resLoc,resGather,mpiCommWorld,mpiSUM);
  nRes0 = sqrt(resGather);
  nRes = nRes0;
  endProcedure("residual checking",t0)

  while(nRes/(nRes0+1.e-30) > EpsNrCon && niter < NrMaxItr) {
    niter++;

    // --- solve_linear_system ---- //
    startProcedure("linear-system solving",t0)
    set(A,sparams=" -ksp_type cg -ksp_rtol 1e-10 ");
    du[] = A^-1*b;
    endProcedure("linear-system solving",t0)

    // --- update_increment ---- //
    startProcedure("increment update",t0)
    Du[] += du[];
    endProcedure("increment update",t0)

    // Elastic trial state from the last converged state and the total
    // displacement increment Δu of this load step.
    // --- compute_trial_state ---- //
    startProcedure("trial stress computation",t0)
    [Eps11,Eps22,Eps12] = epsilon(Du);
    [SigTrial11,SigTrial22,SigTrial12] = [
      SigOld11 + lambda*(Eps11+Eps22) + 2.*mu*Eps11,
      SigOld22 + lambda*(Eps11+Eps22) + 2.*mu*Eps22,
      SigOld12 + 2.*mu*Eps12];
    SigTrial33 = SigOld33 + lambda*(Eps11+Eps22);

    meanTrial = (SigTrial11+SigTrial22+SigTrial33)/3.;
    [Dev11,Dev22,Dev12] = [SigTrial11-meanTrial,
                           SigTrial22-meanTrial,SigTrial12];
    Dev33 = SigTrial33-meanTrial;
    seqTrial = sqrt(1.5*(Dev11^2+Dev22^2+Dev33^2+Dev12^2));
    endProcedure("trial stress computation",t0)

    // --- evaluate_yield_function ---- //
    startProcedure("yield function evaluation",t0)
    yieldFunction = seqTrial-sig0-H*pOld;
    yieldPositive = (yieldFunction+abs(yieldFunction))/2.;
    dp = yieldPositive/(3.*mu+H);
    plasticSwitch = yieldPositive/(abs(yieldFunction)+1.e-14*sig0);
    endProcedure("yield function evaluation",t0)

    // --- radial_return_update ---- //
    startProcedure("radial return update",t0)
    [FlowN11,FlowN22,FlowN12] = [
      plasticSwitch*Dev11/(seqTrial+1.e-14*sig0),
      plasticSwitch*Dev22/(seqTrial+1.e-14*sig0),
      plasticSwitch*Dev12/(seqTrial+1.e-14*sig0)];
    FlowN33 = plasticSwitch*Dev33/(seqTrial+1.e-14*sig0);
    beta = 3.*mu*dp/(seqTrial+1.e-14*sig0);
    endProcedure("radial return update",t0)

    // --- update_consistent_tangent ---- //
    startProcedure("consistent tangent update",t0)
    [Sig11,Sig22,Sig12] = [SigTrial11-beta*Dev11,
                            SigTrial22-beta*Dev22,
                            SigTrial12-beta*Dev12];
    Sig33 = SigTrial33-beta*Dev33;

    // Consistent algorithmic tangent for the radial-return update:
    // C_alg = C - 3μ(3μ/(3μ+H)-β)n⊗n - 2μβ DEV.
    tangentA = 3.*mu*(3.*mu/(3.*mu+H)-beta);
    [Mt11,Mt12,Mt13,Mt22,Mt23,Mt33] = [
      lambda+2.*mu-tangentA*FlowN11^2-4.*mu*beta/3.,
      lambda-tangentA*FlowN11*FlowN22+2.*mu*beta/3.,
      -tangentA*FlowN11*FlowN12,
      lambda+2.*mu-tangentA*FlowN22^2-4.*mu*beta/3.,
      -tangentA*FlowN22*FlowN12,
      2.*mu-tangentA*FlowN12^2-2.*mu*beta];
    endProcedure("consistent tangent update",t0)

    startProcedure("linear-system assembly",t0)
    ALoc = elast(Vh,Vh,solver=CG,sym=1);
    A = ALoc;
    b = elast(0,Vh);
    endProcedure("linear-system assembly",t0)

    // --- calculate_residual ---- //
    startProcedure("residual checking",t0)
    b = b .* DP;
    resLoc = b.l2;
    resLoc = resLoc*resLoc;
    mpiAllReduce(resLoc,resGather,mpiCommWorld,mpiSUM);
    nRes = sqrt(resGather);
    endProcedure("residual checking",t0)
  }

  if(nRes/(nRes0+1.e-30) > EpsNrCon) {
    if(mpirank==0)
      cout << "Error: native von Mises Newton iterations maxed out at load step "
           << i << endl;
    exit(1201);
  }

  // Commit only after Newton convergence; a failed iterate never contaminates
  // the history used by the next load step.
  // --- commit_displacements ---- //
  startProcedure("displacement commit",t0)
  u[] += Du[];
  endProcedure("displacement commit",t0)

  // --- commit_internal_variables ---- //
  startProcedure("internal variable commit",t0)
  [SigOld11,SigOld22,SigOld12] = [Sig11,Sig22,Sig12]; 
  SigOld33 = Sig33;
  pOld = pOld+dp;
  endProcedure("internal variable commit",t0)

  if(mpirank==0)
    cout.scientific
         << " " << i << "\t\t" << tl*Qlim << "\t" << niter << "\t\t"
         << nRes/(nRes0+1.e-30) << endl;
)"""";

 if(ParaViewPostProcess){
 writeIt
 "  savevtk(\"VTUs/Solution.vtu\",Th,PlotVec(u),dataname=\"U\",order=vtuorder,append=i?true:false);\n";
 }

 if(debug)
 writeIt
 "  macro viz(i)i//\n"
 "  plotMPI(Th,u,P1,viz,real,wait=0,cmm=\"displacement\")\n";

codeSnippet R""""(
}

if(mpirank==0)
  cout << "\n#-----------------------------------------------------------------\n" << endl;

)"""";
}

if(useMfront){
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
 "  endProcedure(\"Stress update via MFront\",t0)                                \n"
 "                                                                               \n"
 "                                                                               \n"
 "    //--------------Assembly for linear system---------//                      \n"
 "                                                                               \n"
 "  startProcedure(\"linear-system Assembly\",t0)                                \n"
 "    ALoc = elast(Vh,Vh,solver=CG,sym=1);                                       \n"
 "    A = ALoc ;                                                                 \n"
 "    b = elast(0,Vh);                                                           \n"
 "  endProcedure  (\"linear-system assembly\",t0)                                \n"
 "                                                                               \n"
 "    //------residual  calculation---------//                                   \n"
 "                                                                               \n"
 "  startProcedure(\"residual checking\",t0)                                     \n"
 "    real res1Gather,  res1Loc ;                                                \n"
 "                                                                               \n"
 "    b = b .* DP                                   ;                            \n"
 "    res1Loc = b.l2                                ;                            \n"
 "    res1Loc = res1Loc*res1Loc                     ;                            \n"
 "    mpiAllReduce(res1Loc,res1Gather,mpiCommWorld,mpiSUM);                      \n"
 "    res1Gather = sqrt(res1Gather) ;                                            \n"
 "                                                                               \n"
 "    nRes = res1Gather;                                                         \n"
 "  endProcedure (\"residual checking\",t0)                                      \n"
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
 "  startProcedure(\"ParaView plotting\",t0)                                      \n";

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
 "  endProcedure(\"ParaView plotting\",t0)                                        \n";

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
}
