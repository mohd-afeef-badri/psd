//=====================================================================================
// ------ Elasticity Dynamics for the LinearFormBuilderAndSolver.edp file ------
//=====================================================================================

if(Sequential){
 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "//  ------- Dynamic loop for linear assembly and solving -------                \n"
 "//==============================================================================\n"
 "                                                                                \n"
 "while (t <= tmax){                                                              \n"
 "                                                                                \n"
 "  cout.scientific<<\"-----------------------------------------------------\\n\" \n"
 "  << \"Time iteration at t :\" << t << \" (s)\\n \"<< endl;                     \n"
 "                                                                                \n"
 "  //--------------tt update for loading--------------//                         \n"
 "                                                                                \n";

if(TimeDiscretization=="generalized-alpha" || TimeDiscretization=="hht-alpha")

 writeIt
 "  tt  = t-real(alpf*dt);                                                        \n";

if(TimeDiscretization=="newmark-beta" || TimeDiscretization=="central-difference")

 writeIt
 "  tt  = t-dt;                                                                   \n";


 writeIt
 "                                                                                \n"
 "  //-----------------Assembly for A-----------------//                          \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"matrix assembly\",t0)\n" : ""                         )<<
 "  A = elastodynamics(Vh,Vh,solver=CG,sym=1);                                    \n"
<<(timelog ? "  timerend  (\"matrix assembly\",t0)\n" : ""                         )<<
 "                                                                                \n"
 "  //-----------------Assembly for b-----------------//                          \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"RHS assembly\",t0)\n" : ""                            )<<
 "  b = elastodynamics(0,Vh);                                                     \n"
<<(timelog ? "  timerend  (\"RHS assembly\",t0)\n" : ""                            )<<
 "                                                                                \n"
 "  //-----------------Solving du=A^-1*b--------------//                          \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"solving U\",t0)\n" : ""                               )<<
 "  set(A,solver=CG,sym=1);                                                       \n"
 "  du[] = A^-1*b;                                                                \n"
<<(timelog ? "  timerend  (\"solving U\",t0)\n" : ""                               )<<
 "                                                                                \n";

if(debug)if(spc==2)
 writeIt
 "                                                                                \n"
 "  //-----------------Move mesh plotting------------//                           \n"
 "                                                                                \n"
 "  meshN ThMoved = movemesh(Th, [x + du, y + du1])  ;                            \n"
 "  plot (ThMoved,wait=0, cmm= \"t = \"+t+\" (s)\")  ;                            \n";

if(debug)if(spc==3)
 writeIt
 "                                                                                \n"
 "  //-----------------Move mesh plotting------------//                           \n"
 "                                                                                \n"
 "  meshN ThMoved = movemesh3(Th, transfo =[x + du, y + du1, z + du2]) ;          \n"
 "  plot (ThMoved,wait=0, cmm= \"t = \"+t+\" (s)\")  ;                            \n";


 writeIt
 "                                                                                \n"
 "  //-----------------updating variables------------//                           \n"
 "                                                                                \n"
 <<(timelog ? "  timerbegin(\"updating variables\",t0)\n" : ""                     )
 <<(useGFP  ? "  GFPUpdateDynamic(du[],uold[],vold[],aold[],beta,gamma,dt);\n" : "" )
 <<(!useGFP ? "  updateVariables(du,uold,vold,aold,beta,gamma,dt)\n" : ""           )
 <<(timelog ? "  timerend  (\"updating variables\",t0)\n" : ""                      );

if(plotAll)if(spc==2){
 writeIt
 "                                                                                \n"
 "  //-----------------Paraview plotting-------------//                           \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"ParaView plotting\",t0)\n" : ""                       )<<
 "  string   namevtu=\"VTUs/Solution\"+iterout+\".vtu\";                          \n"
 "  savevtk  (  namevtu               ,                                           \n"
 "              Th                    ,                                           \n";

if(PostProcess!="v" & PostProcess!="a" & PostProcess!="uva")
 writeIt
 "              [uold,uold1,0]        ,                                           \n";
if(PostProcess=="v")
 writeIt
 "              [vold,vold1,0]        ,                                           \n";
if(PostProcess=="a")
 writeIt
 "              [aold,aold1,0]        ,                                           \n";
if(PostProcess=="uva")
 writeIt
 "              [uold,uold1,0]        ,                                           \n"
 "              [vold,vold1,0]        ,                                           \n"
 "              [aold,aold1,0]        ,                                           \n";


 writeIt
 "              order=vtuorder        ,                                           \n"
 "              dataname=namedata                                                 \n"
 "           );                                                                   \n"
<<(timelog ? "  timerend  (\"ParaView plotting\",t0)\n" : ""                       );
}

if(plotTime){
 writeIt
 "                                                                                \n"
 "  //-----------------Paraview plotting-------------//                           \n"
 "                                                                                \n"
<<(timelog ? "  MPItimerbegin(\"ParaView plotting\",t0)\n" : ""                    )<<
 "  exportTimeStep( namevtu,                                                      \n"
 "                  Th                    ,                                       \n";

if(PostProcess!="v" & PostProcess!="a" & PostProcess!="uva")
 writeIt
 (spc==2 ? "\t\t [uold,uold1,0]\t   ,\n" : "\t\t [uold,uold1,uold2]\t   ,\n"      );

if(PostProcess=="v")
 writeIt
 (spc==2 ? "\t\t [vold,vold1,0]\t   ,\n" : "\t\t [vold,vold1,vold2]\t   ,\n"      );

if(PostProcess=="a")
 writeIt
 (spc==2 ? "\t\t [aold,aold1,0]\t   ,\n" : "\t\t [aold,aold1,aold2]\t   ,\n"      );

if(PostProcess=="uva")
 writeIt
  (spc==2 ? "\t\t [uold,uold1,0]\t   ,\n" : "\t\t [uold,uold1,uold2]\t   ,\n"     )
<<(spc==2 ? "\t\t [vold,vold1,0]\t   ,\n" : "\t\t [vold,vold1,vold2]\t   ,\n"     )
<<(spc==2 ? "\t\t [aold,aold1,0]\t   ,\n" : "\t\t [aold,aold1,aold2]\t   ,\n"     );


 writeIt
 "                  vtuorder              ,                                       \n"
 "                  iterout               ,                                       \n"
 "                  t                     ,                                       \n"
 "                  namedata                                                      \n"
 "           );                                                                   \n"
<<(timelog ? "  timerend  (\"ParaView plotting\",t0)\n" : ""                       );
}


if(plotAll)if(spc==3){
 writeIt
 "                                                                                \n"
 "  //-----------------Paraview plotting-------------//                           \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"ParaView plotting\",t0)\n" : ""                       )<<
 "  string   namevtu=\"VTUs/Solution\"+iterout+\".vtu\";                          \n"
 "  savevtk  (  namevtu               ,                                           \n"
 "              Th                    ,                                           \n";

if(PostProcess!="v" & PostProcess!="a" & PostProcess!="uva")
 writeIt
 "              [uold,uold1,uold2]    ,                                           \n";
if(PostProcess=="v")
 writeIt
 "              [vold,vold1,vold2]    ,                                           \n";
if(PostProcess=="a")
 writeIt
 "              [aold,aold1,aold2]    ,                                           \n";
if(PostProcess=="uva")
 writeIt
 "              [uold,uold1,uold2]    ,                                           \n"
 "              [vold,vold1,vold2]    ,                                           \n"
 "              [aold,aold1,aold2]    ,                                           \n";


 writeIt
 "              order=vtuorder        ,                                           \n"
 "              dataname=namedata                                                 \n"
 "           );                                                                   \n"
<<(timelog ? "  timerend  (\"ParaView plotting\",t0)\n" : ""                       );
}


if(pipegnu){
 writeIt
 "                                                                                \n"
 "  //---------------Energy calculations-------------//                           \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"Energy calculations\",t0)\n" : ""                     )<<
 "  Ek =intN(Th,qforder=2)(0.5*(vold*vold+vold1*vold1));                          \n"
 "  El =intN(Th,qforder=2)(0.5*(lambda*divergence(uold)*divergence(uold)          \n"
 "                         + 2. * mu * epsilon(uold)'*epsilon(uold)) );           \n"
 "  Ec += dt*intN(Th,qforder=2)(                                                  \n"
 "                           (etam*rho) *def(vold)'*def(vold)                     \n"
 "                         + (etak*lambda)*(divergence(vold)*divergence(vold))    \n"
 "                         + (etak* 2.*mu)*(epsilon(vold)'*epsilon(vold)) );      \n"
 "                                                                                \n"
 "  //----------Appending energies to a file----------//                          \n"
 "                                                                                \n"
 "  ofstream ff(\"energies.data\",append);                                        \n"
 "  ff<< t << \"  \" << Ek << \"  \"<< El << \"  \" << Ec <<endl;                 \n";

if(!supercomp)
 writeIt
 "                                                                                \n"
 "  //-----------------Gnuplot pipeping-------------//                            \n"
 "                                                                                \n"
 "  pgnuplot <<\"plot\"                                                           \n"
 "  <<\"\\\"energies.data\\\"\"                                                   \n"
 "  <<\"u ($1):($2) w lp lw 2 pt 7 ps 2 t \\\"K.E\\\",\"                          \n"
 "  <<\"\\\"energies.data\\\"\"                                                   \n"
 "  <<\"u ($1):($3) w lp lw 2  pt 7 ps 2 t \\\"E.E\\\",\"                         \n"
 "  <<\"\\\"energies.data\\\"\"                                                   \n"
 "  <<\"u ($1):($4) w lp lw 2 pt 7 ps 2 t \\\"D.E\\\",\"                          \n"
 "  <<\"\\\"energies.data\\\"          \"                                         \n"
 "  <<\"u ($1):($3+$2+$4) w lp lw 2 pt 7 ps 2 t \\\"T.E\\\" \"                    \n"
 "  <<\"\\n\";                                                                    \n"
 "  flush(pgnuplot);                                                              \n";


 writeIt
 "                                                                                \n"
<<(timelog ? "  timerend(\"Energy calculations\",t0)\n" : ""                       );

}  //-- [if loop terminator]  pipegnu ended --//


 writeIt
 "                                                                                \n"
 "  //-----------------updating time----------------//                            \n"
 "                                                                                \n"
 "  t += dt;                                                                      \n";

if(plotAll || plotTime)
 writeIt
 "                                                                                \n"
 "  //-----------updating iteration count-----------//                            \n"
 "                                                                                \n"
 "  iterout++;                                                                    \n";


 writeIt
 "                                                                                \n"
 "}                                                                               \n"
 "                                                                                \n"
<<(plotTime ? "exportEnd(namevtu)\n" : " "                                          )<<
 "                                                                                \n"
<<(timelog ? "cout << \" all operations ended, they \";\n" : ""                     )
<<(timelog ? "timerend  (\"solver\",t1)\n" : " "                                    )<<
 "                                                                                \n"
 "//-------------------------------THE END------------------------------//        \n";

}  //-- [if loop terminator] Sequential Dynamic ended --//


if(!Sequential){
 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "//  ------- Dynamic loop for linear assembly and solving -------                \n"
 "//==============================================================================\n"
 "                                                                                \n"
 "while (t <= tmax){                                                              \n"
 "                                                                                \n"
 "  if(mpirank==0)                                                                \n"
 "  cout.scientific<<\"-----------------------------------------------------\\n\" \n"
 "  << \"Time iteration at t :\" << t << \" (s)\\n \"<< endl;                     \n"
 "                                                                                \n"
 "  //--------------tt update for loading--------------//                         \n"
 "                                                                                \n";

if(TimeDiscretization=="generalized-alpha" || TimeDiscretization=="hht-alpha")

 writeIt
 "  tt  = t-real(alpf*dt);                                                        \n";

if(TimeDiscretization=="newmark-beta" || TimeDiscretization=="central-difference")

 writeIt
 "  tt  = t-dt;                                                                   \n";


 writeIt
 "                                                                                \n"
 "  //-----------------Assembly for A-----------------//                          \n"
 "                                                                                \n"
<<(timelog ? "  MPItimerbegin(\"matrix assembly\",t0)\n" : ""                      )<<
 "  ALoc = elastodynamics(Vh,Vh,solver=CG,sym=1);                                 \n"
<<(timelog ? "  MPItimerend  (\"matrix assembly\",t0)\n" : ""                      )<<
 "                                                                                \n"
<<(timelog ? "  MPItimerbegin(\"PETSc assembly\",t0)\n"  : ""                      )<<
 "  changeOperator(A, ALoc);                                                      \n"
<<(timelog ? "  MPItimerend(\"PETSc assembly\",t0)\n"    : ""                      )<<
 "                                                                                \n";

if(Model=="pseudo-nonlinear")
 writeIt
 "                                                                                \n"
 "  //---------update Nonlinear displacement-----------//                         \n"
 "                                                                                \n"
 "  uNL[] = uold[];                                                               \n"
 "                                                                                \n"
 "  for (int k=0; k<5; k++){  // Pseudo-nonlinear NR loop                         \n"
 "                                                                                \n";


 writeIt
 "                                                                                \n"
 "  //-----------------Assembly for b-----------------//                          \n"
 "                                                                                \n"
<<(timelog ? "  MPItimerbegin(\"RHS assembly\",t0)\n" : ""                         )<<
 "  b = elastodynamics(0,Vh);                                                     \n"
<<(timelog ? "  MPItimerend  (\"RHS assembly\",t0)\n" : ""                         )<<
 "                                                                                \n"
 "  //-----------------Solving du=A^-1*b--------------//                          \n"
 "                                                                                \n"
<<(timelog ? "  MPItimerbegin(\"solving U\",t0)\n" : ""                            )<<
 "  set(A,sparams =\"  -ksp_type cg  \");                                         \n"
 "  du[] = A^-1*b;                                                                \n"
<<(timelog ? "  MPItimerend  (\"solving U\",t0)\n" : ""                            )<<
 "                                                                                \n";

if(Model=="pseudo-nonlinear")
 writeIt
 "                                                                                \n"
 "  //---------update Nonlinear displacement-----------//                         \n"
 "                                                                                \n"
 "  uNL[] += du[];                                                                \n"
 "                                                                                \n"
 "  //------Newton-Raphsons Error calculation---------//                          \n"
 "                                                                                \n"
<<(timelog ? "  MPItimerbegin(\"NL error checking\",t0)\n" : ""                    )<<
 "  real err1Gather,  err1Loc ;                                                   \n"
 "                                                                                \n"
 "  b = b .* DP                                   ;                               \n"
 "  err1Loc = b.l2                                ;                               \n"
 "  err1Loc = err1Loc*err1Loc                     ;                               \n"
 "  mpiAllReduce(err1Loc,err1Gather,mpiCommWorld,mpiSUM);                         \n"
 "  err1Gather = sqrt(err1Gather) ;                                               \n"
 "                                                                                \n"
<<(timelog ? "  MPItimerend (\"NL error checking\",t0)\n" : ""                     )<<
 "                                                                                \n"
 "  //--------------- Convergence conditional---------------------//              \n"
 "                                                                                \n"
 "  if(err1Gather < 1e-5 || k==4){                                                \n"
 "                                                                                \n"
 "    //------------------Screen output norm----------------------//              \n"
 "                                                                                \n"
 "    if(mpirank==0)                                                              \n"
 "      cout.scientific << \"NL iteration number :  [ \"  << k                    \n"
 "      << \" ]\\nL2 error in [u] :  [ \"    << err1Gather                        \n"
 "      << \" ]\"      << endl;                                                   \n"
 "                                                                                \n"
 "      break;                                                                    \n"
 "                                                                                \n"
 "     }                                                                          \n"
 " }    // Nonlinear NR loop ends                                                 \n"
 "                                                                                \n"
 "  //---------------update  displacement--------------//                         \n"
 "                                                                                \n"
 "  du[] = uNL[];                                                                 \n"
 "                                                                                \n";

if(debug)if(spc==2)
 writeIt
 "                                                                                \n"
 "  //-----------------Move mesh plotting------------//                           \n"
 "                                                                                \n"
 "  meshN ThMoved = movemesh(Th, [x + du, y + du1]) ;                             \n"
 "  plotJustMeshMPI (ThMoved, wait=0, cmm=\"t=\"+t+\"(s)\")                       \n";

if(debug)if(spc==3)
 writeIt
 "                                                                                \n"
 "  //-----------------Move mesh plotting------------//                           \n"
 "                                                                                \n"
 "  meshN ThMoved = movemesh3(Th, transfo =[x + du, y + du1, z + du2]) ;          \n"
 "  plotJustMeshMPI3 (ThMoved, wait=0, cmm=\"t=\"+t+\"(s)\")                      \n";


 writeIt
 "                                                                                \n"
 "  //-----------------updating variables------------//                           \n"
 "                                                                                \n"
<<(timelog ? "  MPItimerbegin(\"updating variables\",t0)\n" : ""                  )
<<(useGFP  ? "  GFPUpdateDynamic(du[],uold[],vold[],aold[],beta,gamma,dt);\n" : "")
<<(!useGFP ? "  updateVariables(du,uold,vold,aold,beta,gamma,dt)\n" : ""          )
<<(timelog ? "  MPItimerend(\"updating variables\",t0)\n" : ""                    );


if(plotAll)if(spc==2){
 writeIt
 "                                                                                \n"
 "  //-----------------ParaView plotting--------------//                          \n"
 "                                                                                \n"
<<(timelog ? "  MPItimerbegin(\"ParaView plotting\",t0)\n" : ""                    )<<
 "                                                                                \n";



 writeIt
 "    savevtk(  \"VTUs/Solution.vtu\"   ,                                         \n"
 "                 Th                 ,                                           \n";

if(PostProcess!="v" & PostProcess!="a" & PostProcess!="uva")
 writeIt
 "                 [uold,uold1,0]     ,                                           \n";
if(PostProcess=="v")
 writeIt
 "                 [vold,vold1,0]     ,                                           \n";
if(PostProcess=="a")
 writeIt
 "                 [aold,aold1,0]     ,                                           \n";
if(PostProcess=="uva")
 writeIt
 "                 [uold,uold1,0]     ,                                           \n"
 "                 [vold,vold1,0]     ,                                           \n"
 "                 [aold,aold1,0]     ,                                           \n";


 writeIt
 "                 order=vtuorder     ,                                           \n"
 "                 dataname=\"U\"       ,                                         \n"
 "                 append=true                                                    \n"
 "              );                                                                \n"
<<(timelog ? "  MPItimerend(\"ParaView plotting\",t0)\n" : ""                      );
}


if(plotTime)if(spc==3)
 writeIt
 "                                                                                \n"
 "  //-----------------Paraview plotting-------------//                           \n"
 "                                                                                \n"
<<(timelog ? "  MPItimerbegin(\"ParaView plotting\",t0)\n" : ""                    )<<
 "  exportTimeStep( namevtu,                                                      \n"
 "                  Th                    ,                                       \n"
 "                  [uold,uold1,uold2]    ,                                       \n"
 "                  vtuorder              ,                                       \n"
 "                  iterout               ,                                       \n"
 "                  t                     ,                                       \n"
 "                  namedata              ,                                       \n"
 "                  mpiCommWorld                                                  \n"
 "           );                                                                   \n"
<<(timelog ? "  MPItimerend(\"ParaView plotting\",t0)\n" : ""                      );

if(plotAll)if(spc==3){
 writeIt
 "                                                                                \n"
 "  //-----------------ParaView plotting--------------//                          \n"
 "                                                                                \n"
<<(timelog ? "  MPItimerbegin(\"ParaView plotting\",t0)\n" : ""                    );



 writeIt
 "    savevtk(  \"VTUs/Solution.vtu\"   ,                                         \n"
 "                 Th                 ,                                           \n";

if(PostProcess!="v" & PostProcess!="a" & PostProcess!="uva")
 writeIt
 "                 [uold,uold1,uold2] ,                                           \n";
if(PostProcess=="v")
 writeIt
 "                 [vold,vold1,vold2] ,                                           \n";
if(PostProcess=="a")
 writeIt
 "                 [aold,aold1,aold2] ,                                           \n";
if(PostProcess=="uva")
 writeIt
 "                 [uold,uold1,uold2] ,                                           \n"
 "                 [vold,vold1,vold2] ,                                           \n"
 "                 [aold,aold1,aold2] ,                                           \n";


 writeIt
 "                 order=vtuorder     ,                                           \n";

if(PostProcess!="v" & PostProcess!="a" & PostProcess!="uva")
 writeIt
 "                 dataname=\"U\"       ,                                         \n";

if(PostProcess=="v")
 writeIt
 "                 dataname=\"U  V\" ,                                            \n";
if(PostProcess=="a")
 writeIt
 "                 dataname=\"U  A\" ,                                            \n";
if(PostProcess=="uva")
 writeIt
 "                 dataname=\"U  V  A\" ,                                         \n";


 writeIt
 "                 append=true                                                    \n"
 "              );                                                                \n";



 writeIt
 (timelog ? "  MPItimerend(\"ParaView plotting\",t0)\n" : ""                      );

}



if(pipegnu){
 writeIt
 "                                                                                \n"
 "  //---------------Energy calculations-------------//                           \n"
 "                                                                                \n"
<<(timelog ? "  MPItimerbegin(\"Energy calculations\",t0)\n" : ""                  )<<
 "  E[0] =intN(Th,qforder=2)( 0.5*DPspc*(vold*vold+vold1*vold1));                 \n"
 "  E[1] =intN(Th,qforder=2)( 0.5*DPspc*(lambda*divergence(uold)*divergence(uold) \n"
 "                            + 2. * mu * epsilon(uold)'*epsilon(uold))  );       \n"
 "  E[2] += dt*intN(Th,qforder=2)( DPspc*(                                        \n"
 "                               (etam*rho) *def(vold)'*def(vold)                 \n"
 "                            +  (etak*lambda)*(divergence(vold)*divergence(vold))\n"
 "                            +  (etak* 2.*mu)*(epsilon(vold)'*epsilon(vold))     \n"
 "                               ) );                                             \n"
 "  mpiAllReduce(E[0],EG[0],mpiCommWorld,mpiSUM);                                 \n"
 "  mpiAllReduce(E[1],EG[1],mpiCommWorld,mpiSUM);                                 \n"
 "  mpiAllReduce(E[2],EG[2],mpiCommWorld,mpiSUM);                                 \n"
 "                                                                                \n"
 "  //----------Appending energies to a file----------//                          \n"
 "                                                                                \n"
 "  if(mpirank==0){                                                               \n"
 "     ofstream ff(\"energies.data\",append);                                     \n"
 "     ff<< t << \"  \" << EG[0] << \"  \"<< EG[1] << \"  \" << EG[2] <<endl;     \n";

if(!supercomp)
 writeIt
 "                                                                                \n"
 "     //---------------Gnuplot pipeping-------------//                           \n"
 "                                                                                \n"
 "     pgnuplot <<\"plot\"                                                        \n"
 "     <<\"\\\"energies.data\\\"\"                                                \n"
 "     <<\"u ($1):($2) w lp lw 2 pt 7 ps 2 t \\\"K.E\\\",\"                       \n"
 "     <<\"\\\"energies.data\\\"\"                                                \n"
 "     <<\"u ($1):($3) w lp lw 2  pt 7 ps 2 t \\\"E.E\\\",\"                      \n"
 "     <<\"\\\"energies.data\\\"\"                                                \n"
 "     <<\"u ($1):($4) w lp lw 2 pt 7 ps 2 t \\\"D.E\\\",\"                       \n"
 "     <<\"\\\"energies.data\\\"\"                                                \n"
 "     <<\"u ($1):($3+$2+$4) w lp lw 2 pt 7 ps 2 t \\\"T.E\\\" \"                 \n"
 "     <<\"\\n\";                                                                 \n"
 "     flush(pgnuplot);                                                           \n";


 writeIt
 "                                                                                \n"
 "   }                                                                            \n"
<<(timelog ? "   MPItimerend(\"Energy calculations\",t0)\n" : ""                   );
}  //-- [if loop terminator]  pipegnu ended --//




 writeIt
 "                                                                                \n"
 "  //-----------------updating time----------------//                            \n"
 "                                                                                \n"
 "  t += dt;                                                                      \n";


 writeIt
 "}                                                                               \n"
 "                                                                                \n";


 writeIt
 (timelog ? "if(mpirank==0)\n" : " "                                               )
<<(timelog ? "cout << \" all operations ended, they \";\n" : ""                     )
<<(timelog ? "MPItimerend  (\"solver\",t1)\n" : ""                                  )<<
 "                                                                                \n"
 "//-------------------------------THE END------------------------------//        \n";

}  //-- [if loop terminator] !Sequential Dynamic ended --//
