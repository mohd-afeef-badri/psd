//=====================================================================================
// ------ Elasticity Mechanics for the LinearFormBuilderAndSolver.edp file ------
//=====================================================================================


if(!Sequential){
 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "//  ------- Local Au=b assembly and solving -------                             \n"
 "//==============================================================================\n"
 "                                                                                \n"
 "//--------------Assembly for bilinear--------------//                           \n"
 "                                                                                \n"
<<(timelog ? "  MPItimerbegin(\"matrix Assembly\",t0)\n" : ""                      )<<
 "  matrix     ALoc = elast(Vh,Vh,solver=CG,sym=1);                               \n"
<<(timelog ? "  MPItimerend  (\"matrix Assembly\",t0)\n" : ""                      )<<
 "                                                                                \n"
 "//---------------Assembly for linear---------------//                           \n"
 "                                                                                \n"
<<(timelog ? "  MPItimerbegin(\"RHS assembly\",t0)\n" : ""                         )<<
 "  real[int]    b = elast(0,Vh);                                                 \n"
<<(timelog ? "  MPItimerend  (\"RHS assembly\",t0)\n" : ""                          );

if(dirichletpointconditions>=1)
 writeIt
 "                                                                                \n"
 "//---------Additional assembly for A & b----------//                            \n"
 "                                                                                \n"
<<(timelog ? "  MPItimerbegin(\"point Dirichlet assembly\",t0)\n" : ""             )<<
 "  Pointbc(Dpointlab,Vh,ALoc,b,PnV);                                             \n"
<<(timelog ? "  MPItimerend(\"point Dirichlet assembly\",t0)\n" : ""                );


 writeIt
 "                                                                                \n"
 " //------------Memory optimization-----------------//                           \n";

if(dirichletpointconditions>=1)
 writeIt
 "                                                                                \n"
 "  Dpointlab.resize(0); PnV.resize(0);                                           \n";


 writeIt
 "                                                                                \n"
 "//---------------PETSc Assembly---------------------//                          \n"
 "                                                                                \n"
<<(timelog ? "  MPItimerbegin(\"PETSc assembly\",t0)\n" : ""                       )<<
 "  Mat A (ALoc, restrictionIntersectionP, DP, bs = "<<spc<<");                   \n"
<<(timelog ? "  MPItimerend(\"PETSc assembly\",t0)\n" : ""                         )<<
 "                                                                                \n"
 "//---------------PETSc solving---------------------//                           \n"
 "                                                                                \n"
<<(timelog ? "  MPItimerbegin(\"PETSc solving\",t0)\n" : ""                       )<<
 "  set(A,sparams =\" -ksp_type cg -ksp_rtol 1e-9 \");                            \n"
 "  u[] = A^-1*b;                                                                 \n"
<<(timelog ? "  MPItimerend(\"PETSc solving\",t0)\n" : ""                          );


if(debug)
 writeIt
 "                                                                                \n"
 "//-------------Debug glut plotting------------------//                          \n"
 "                                                                                \n"
 "  macro viz(i)i//                                                               \n"
 "  plotMPI(Th, u, P1,  viz, real, wait=0, cmm=\"displacement\")                  \n";

if(!plotAll)if(Prblm=="linear-elasticity")
 writeIt
 "                                                                                \n"
<<(timelog ? "MPItimerend(\"solver\",t1)\n" : ""                                   )<<
 "                                                                                \n";

}  //-- [if loop terminator] !Sequential ended --//

if(Sequential){
 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "//  ------- Local Au=b assembly and solving -------                             \n"
 "//==============================================================================\n"
 "                                                                                \n"
 "//--------------Assembly for bilinear--------------//                           \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"matrix assembly\",t0)\n" : ""                        )<<
 "  matrix A = elast(Vh,Vh,solver=CG,sym=1);                                      \n"
<<(timelog ? "  timerend  (\"matrix assembly\",t0)\n" : ""                        )<<
 "                                                                                \n"
 "//---------------Assembly for linear---------------//                           \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"RHS assembly\",t0)\n" : ""                           )<<
 "  real[int]    b = elast(0,Vh);                                                 \n"
<<(timelog ? "  timerend  (\"RHS assembly\",t0)\n" : ""                           )<<
 "                                                                                \n"
 "  //-----------------Solving du=A^-1*b--------------//                          \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"solving U\",t0)\n" : ""                              )<<
 "  set(A,solver=CG,sym=1);                                                       \n"
 "  u[] = A^-1*b;                                                                 \n"
<<(timelog ? "  timerend  (\"solving U\",t0)\n" : ""                               );


if(debug)
 writeIt
 "                                                                                \n"
 "  //--------------debug glut plotting---------------//                          \n"
 "                                                                                \n"
 "  plot (u, wait=1, fill=1, value=1, cmm= \"solution\");                         \n";

if(!plotAll)if(Prblm=="linear-elasticity")
 writeIt
 "                                                                                \n"
<<(timelog ? "timerend(\"solver\",t1)\n" : ""                                      )<<
 "                                                                                \n";

}  //-- [if loop terminator] Sequential liniear elasticity ended --//
