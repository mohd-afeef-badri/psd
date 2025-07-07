//=====================================================================================
// ------ Elasticity Mechanics for the LinearFormBuilderAndSolver.edp file ------
//=====================================================================================


if(!Sequential){
 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "//  ------- Local Au=b assembly and solving ------- //                          \n"
 "//==============================================================================\n"
 "                                                                                \n"
 "//--------------Assembly for bilinear--------------//                           \n"
 "                                                                                \n"
 "  startProcedure(\"matrix Assembly\",t0);                                       \n"
 "  ALoc = elast(Vh,Vh,solver=CG,sym=1);                                          \n"
 "  endProcedure  (\"matrix Assembly\",t0);                                       \n"
 "                                                                                \n";

if(Model=="pseudo_nonlinear")
 writeIt
 "                                                                                \n"
 "//---------------PETSc Assembly---------------------//                          \n"
 "                                                                                \n"
 "  startProcedure(\"PETSc assembly\",t0);                                        \n"
 "  A = ALoc ;                                                                    \n"
 "  endProcedure(\"PETSc assembly\",t0);                                          \n"
 "                                                                                \n"
 "  //---------Pseudo Nonlinear Loop-----------//                                 \n"
 "                                                                                \n"
 "  for (int k=0; k<5; k++){  // Pseudo-nonlinear NR loop                         \n"
 "                                                                                \n";

 writeIt
 "//---------------Assembly for linear---------------//                           \n"
 "                                                                                \n"
 "  startProcedure(\"RHS assembly\",t0);                                          \n"
 "  b = elast(0,Vh);                                                              \n"
 "  endProcedure  (\"RHS assembly\",t0);                                          \n";

if(dirichletpointconditions>=1 && !pointprobe && Model!="pseudo_nonlinear"){
 writeIt
 "                                                                                \n"
 "//---------Additional assembly for A & b----------//                            \n"
 "                                                                                \n"
 "  startProcedure(\"point Dirichlet assembly\",t0);                              \n"
 "                                                                                \n"
 "  GetPointIndiciesMpiRank(PbcCord, PCi, mpirankPCi);                            \n";

 for(int i=0; i<dirichletpointconditions; i++)
 writeIt
 "  ApplyPointBc"<<i<<"(ALoc,b);                                                  \n";


 writeIt
 "                                                                                \n"
 "  endProcedure(\"point Dirichlet assembly\",t0);                                \n";
}


if(dirichletpointconditions>=1 && pointprobe && Model!="pseudo_nonlinear"){
 writeIt
 "                                                                                \n"
 "//---------Additional assembly for A & b----------//                            \n"
 "                                                                                \n"
 "  startProcedure(\"point Dirichlet assembly\",t0);                              \n"
 "                                                                                \n"
 "  GetPointIndiciesMpiRank( PbcCord, PCi, mpirankPCi,                            \n"
 "                           ProbePointCord, iProbe, Prank);                      \n";

 for(int i=0; i<dirichletpointconditions; i++)
 writeIt
 "  ApplyPointBc"<<i<<"(ALoc,b);                                                  \n";

 writeIt
 "                                                                                \n"
 "  endProcedure(\"point Dirichlet assembly\",t0);                                \n";
}

if(dirichletpointconditions<1 && pointprobe && Model!="pseudo_nonlinear"){
 writeIt
 "                                                                                \n"
 "//---------Point Probe coordinate detection----------//                         \n"
 "                                                                                \n"
 "  startProcedure(\"finding point probe cords\",t0);                             \n"
 "                                                                                \n"
 "  GetPointProbeIndicies( ProbePointCord, iProbe, Prank);                        \n"
 "                                                                                \n";

 writeIt
 "                                                                                \n"
 "  endProcedure(\"finding point probe cords\",t0);                               \n";
}

 if( Model!="pseudo_nonlinear")
 writeIt
 "                                                                                \n"
 "//---------------PETSc Assembly---------------------//                          \n"
 "                                                                                \n"
 "  startProcedure(\"PETSc assembly\",t0);                                        \n"
 "  A = ALoc ;                                                                    \n"
 "  endProcedure(\"PETSc assembly\",t0);                                          \n"
 "                                                                                \n"
 "                                                                                \n"
 "                                                                                \n"
 "//---------------PETSc solving---------------------//                           \n"
 "                                                                                \n"
 "  startProcedure(\"PETSc solving\",t0);                                         \n"
 "  set(A,sparams =\" -ksp_type cg -ksp_rtol 1e-9 \");                            \n"
 "  u[] = A^-1*b;                                                                 \n"
 "  endProcedure(\"PETSc solving\",t0);                                           \n";

 if( Model=="pseudo_nonlinear")
 {
 writeIt
 "                                                                                \n"
 " //----------------PETSc solving----------------------//                        \n"
 "                                                                                \n"
 "  startProcedure(\"PETSc solving\",t0);                                         \n"
 "  set(A,sparams =\" -ksp_type cg -ksp_rtol 1e-9 \");                            \n"
 "  du[] = A^-1*b;                                                                \n"
 "  endProcedure(\"PETSc solving\",t0);                                           \n"
 "                                                                                \n"
 " //---------------Update Solution---------------------//                        \n"
 "                                                                                \n"
 "  startProcedure(\"Solution update\",t0);                                       \n"
 "  u[] += du[];                                                                  \n"
 "  endProcedure(\"Solution update\",t0);                                         \n"
 "                                                                                \n";

 if(useMfront){
 writeIt
 " //-----Update Stress using Mfront-------------------//                         \n"
 "                                                                                \n"
 "  startProcedure(\"Stress update via MFront\",t0);                              \n"
 "                                                                                \n";

 if(spc==2)
 writeIt
 "  [Eps11,Eps22,Eps12] = epsilon(u);                                             \n";

 if(spc==3)
 writeIt
 "  [Eps11,Eps22,Eps33,Eps12,Eps13,Eps23] = epsilon(u);                          \n";

 writeIt
 "                                                                               \n"
 "   PsdMfrontHandler( MaterialBehaviour                                       , \n"
 "                          mfrontBehaviourHypothesis = MaterialHypothesis     , \n"
 "                          mfrontPropertyNames       = PropertyNames          , \n"
 "                          mfrontPropertyValues      = PropertyValues         , \n"
 "                          mfrontStrainTensor        = Eps11[]                , \n"
 "                          mfrontStressTensor        = Sig11[]                  \n"
 "                        );                                                     \n"
 "  endProcedure(\"Stress update via MFront\",t0);                               \n"
 "                                                                                \n";
 }

 writeIt
 "                                                                                \n"
 "  //------pseudo-nonlinear Error calculation---------//                         \n"
 "                                                                                \n"
 "  startProcedure(\"NL error checking\",t0);                                     \n"
 "  real err1Gather,  err1Loc ;                                                   \n"
 "                                                                                \n"
 "  b = b .* DP                                   ;                               \n"
 "  err1Loc = b.l2                                ;                               \n"
 "  err1Loc = err1Loc*err1Loc                     ;                               \n"
 "  mpiAllReduce(err1Loc,err1Gather,mpiCommWorld,mpiSUM);                         \n"
 "  err1Gather = sqrt(err1Gather) ;                                               \n"
 "                                                                                \n"
 "  endProcedure (\"NL error checking\",t0);                                      \n"
 "                                                                                \n"
 "  //--------------- Convergence conditional---------------------//              \n"
 "                                                                                \n"
 "  if(err1Gather < 1e-5 || k==4){                                                \n"
 "                                                                                \n"
 "    //-------------- Error out if 4 iterations -----------------//              \n"
 "                                                                                \n"
 "    if(k==4)                                                                    \n"
 "    { cout << \"ERROR PSEUDO-NONLINEAR ITERATIONS MAXED OUT\"<<endl;            \n"
 "      exit(1);                                                                  \n"
 "    }                                                                           \n"
 "                                                                                \n"
 "    //------------------Screen output norm----------------------//              \n"
 "                                                                                \n"
 "    if(mpirank==0)                                                              \n"
 "      cout.scientific                                                           \n"
 "      << \"\\n----------------------------------------\\n\"                     \n"
 "      << \"NL iteration number :  [ \"  << k                                    \n"
 "      << \" ]\\nL2 error in [u] :  [ \"    << err1Gather                        \n"
 "      << \" ]\"                                                                 \n"
 "      << \"\\n----------------------------------------\\n\"                     \n"
 "      << endl;                                                                  \n"
 "                                                                                \n"
 "      break;                                                                    \n"
 "                                                                                \n"
 "     }                                                                          \n"
 " }    // Nonlinear NR loop ends                                                 \n"
 "                                                                                \n"
 "                                                                                \n";
 }

 if(debug)
 writeIt
 "                                                                                \n"
 "//-------------Debug glut plotting------------------//                          \n"
 "                                                                                \n"
 "  macro viz(i)i//                                                               \n"
 "  plotMPI(Th, u, P1,  viz, real, wait=0, cmm=\"displacement\")                  \n";


 if(ParaViewPostProcess)
 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// -------Postprocess with paraview-------//                                    \n"
 "//==============================================================================\n"
 "                                                                                \n"
 "  startProcedure(\"Paraview Postprocess\",t0);                                  \n"
 "  int[int] vtuorder=[1];                     // Solution export order           \n"
 "  savevtk( \"VTUs/Solution.vtu\"  ,                                             \n"
 "            Th                  ,                                               \n"
 "            PlotVec(u)          ,                                               \n"
 "            order=vtuorder      ,                                               \n"
 "            dataname=\"U\"                                                      \n"
 "         );                                                                     \n"
 "  endProcedure(\"Paraview Postprocess\",t0);                                    \n"
 "                                                                                \n";


if(reactionforce){

codeSnippet R""""(

//==============================================================================
// -------Reaction force calculation-------//
//==============================================================================

startProcedure("force calculation",t0);
)"""";

if(spc == 2){

if(reactionforcemethod=="variational_based"){
codeSnippet R""""(

  Vh def(F);    // F is internal force vector
  
  A   =   varfForce(Vh,Vh,solver=CG,sym=1);
  F[] = A*u[];

  real forcetotx  = 0. , forcetoty  = 0.;
  
  for(int i=0; i < Th.nv; i++){                                                 
     if(abs(Th(i).x)<.000001){
        forcetotx = forcetotx + F[][i*2];                             
        forcetoty = forcetoty + F[][i*2+1];                           
     }                                                                          
  }

  cout << "Vertical reaction Ry              :: "       <<  forcetoty  << endl;
  cout << "Horizontal reaction Rx            :: "       <<  forcetotx  << endl;   
)"""";}


if(reactionforcemethod=="stress_based"){
codeSnippet R""""(
  Vh def(Sigx);   //  stress vector in x and y direction

  def(Sigx) = [ lambda*(dx(u) + dy(u1) ) + 2*mu*dx(u)  ,  // Sigx  = Sigma_xx
                mu*(dy(u) + dx(u1))                    ]; // Sigx1 = Sigma_xy

  real forcetotx = intN1(Th,Dbc0On)( - Sigx   );
  real forcetoty = intN1(Th,Dbc0On)( - Sigx1  );

  cout << "Vertical reaction Ry              :: "       <<  forcetoty  << endl;
  cout << "Horizontal reaction Rx            :: "       <<  forcetotx  << endl;   
)"""";}
}


codeSnippet R""""(

endProcedure("force calculation",t0);

)"""";

}

}  //-- [if loop terminator] !Sequential ended --//

if(Sequential){
 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "//  ------- Local Au=b assembly and solving ------- //                          \n"
 "//==============================================================================\n"
 "                                                                                \n"
 "//--------------Assembly for bilinear--------------//                           \n"
 "                                                                                \n"
 "  startProcedure(\"matrix assembly\",t0);                                       \n"
 "  A = elast(Vh,Vh,solver=CG,sym=1);                                             \n"
 "  endProcedure  (\"matrix assembly\",t0);                                       \n"
 "                                                                                \n"
 "//---------------Assembly for linear---------------//                           \n"
 "                                                                                \n"
 "  startProcedure(\"RHS assembly\",t0);                                          \n"
 "  b = elast(0,Vh);                                                              \n"
 "  endProcedure  (\"RHS assembly\",t0);                                          \n"
 "                                                                                \n"
 "  //-----------------Solving du=A^-1*b--------------//                          \n"
 "                                                                                \n"
 "  startProcedure(\"solving U\",t0);                                             \n"
 "  set(A,solver=CG,sym=1);                                                       \n"
 "  u[] = A^-1*b;                                                                 \n"
 "  endProcedure  (\"solving U\",t0);                                             \n";


if(debug)
 writeIt
 "                                                                                \n"
 "  //--------------debug glut plotting---------------//                          \n"
 "                                                                                \n"
 "  plot (u, wait=1, fill=1, value=1, cmm= \"solution\");                         \n";

 if(ParaViewPostProcess)
 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// -------Postprocess with paraview-------//                                    \n"
 "//==============================================================================\n"
 "                                                                                \n"
 "  startProcedure(\"Paraview Postprocess\",t0);                                  \n"
 "  int[int] vtuorder=[1];                             // Solution export order   \n"
 "  savevtk( \"VTUs/Solution-Seq.vtu\"   ,                                        \n"
 "            Th                       ,                                          \n"
 "            PlotVec(u)               ,                                          \n"
 "            order=vtuorder           ,                                          \n"
 "            dataname=\"U\"                                                      \n"
 "         );                                                                     \n"
 "  endProcedure  (\"Paraview Postprocess\",t0);                                  \n"
 "                                                                                \n";

}  //-- [if loop terminator] Sequential liniear elasticity ended --//
