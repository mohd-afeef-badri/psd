//=====================================================================================
// ------ Soil Dynamics for the LinearFormBuilderAndSolver.edp file ------ 
//=====================================================================================

if(Sequential){write    
<<"                                                                                \n"
<<"//==============================================================================\n"
<<"//  ------- Dynamic loop for linear assembly and solving -------                \n"
<<"//==============================================================================\n"  
<<"                                                                                \n"
<<"while (t <= tmax){                                                              \n"
<<"                                                                                \n"
<<"  cout.scientific<<\"-----------------------------------------------------\\n\" \n"
<<"  << \"Time iteration at t :\" << t << \" (s)\\n \"<< endl;                     \n"
<<"                                                                                \n"
<<"  //--------------tt update for loading--------------//                         \n"
<<"                                                                                \n"
<<"  tt  = t;                                                                      \n"
<<"                                                                                \n"
<<"  //-----------------Assembly for A-----------------//                          \n"
<<"                                                                                \n"
<<(timelog ? "  timerbegin(\"matrix assembly\",t0)\n" : ""                         )
<<"  A = soildynamics(Vh,Vh,solver=CG,sym=1);                                      \n"
<<(timelog ? "  timerend  (\"matrix assembly\",t0)\n" : ""                         )
<<"                                                                                \n"
<<"  //-----------------Assembly for b-----------------//                          \n"
<<"                                                                                \n"
<<(timelog ? "  timerbegin(\"RHS assembly\",t0)\n" : ""                            )
<<"  b = soildynamics(0,Vh);                                                       \n"
<<(timelog ? "  timerend  (\"RHS assembly\",t0)\n" : ""                            )
<<"                                                                                \n"
<<"  //-----------------Solving du=A^-1*b--------------//                          \n"
<<"                                                                                \n"
<<(timelog ? "  timerbegin(\"solving U\",t0)\n" : ""                               )
<<"  set(A,solver=CG,sym=1);                                                       \n"
<<"  du[] = A^-1*b;                                                                \n"
<<(timelog ? "  timerend  (\"solving U\",t0)\n" : ""                               )
<<"                                                                                \n";

if(debug)write
<<"                                                                                \n"
<<"  //-----------------Move mesh plotting------------//                           \n"
<<"                                                                                \n"
<<"  plot (du1,wait=0, cmm= \"t = \"+t+\" (s)\",value=1);                          \n";

write
<<"                                                                                \n"
<<"  //-----------------updating variables------------//                           \n"
<<"                                                                                \n"
<<(timelog ? "  timerbegin(\"updating variables\",t0)\n" : ""                      )
<<(useGFP  ? "  GFPUpdateDynamic(du[],uold[],vold[],aold[],beta,gamma,dt);\n" : "" )
<<(!useGFP ? "  updateVariables(du,uold,vold,aold,beta,gamma,dt)\n" : ""           )
<<(timelog ? "  timerend  (\"updating variables\",t0)\n" : ""                      );

if(plotAll)if(spc==2){write
<<"                                                                                \n"
<<"  //-----------------Paraview plotting-------------//                           \n"
<<"                                                                                \n"
<<(timelog ? "  timerbegin(\"ParaView plotting\",t0)\n" : ""                       )
<<"  string   namevtu=\"VTUs/Solution\"+iterout+\".vtu\";                          \n"
<<"  savevtk  (  namevtu               ,                                           \n"
<<"              Th                    ,                                           \n";

if(PostProcess!="v" & PostProcess!="a" & PostProcess!="uva")write
<<"              [uold,uold1,0]        ,                                           \n";
if(PostProcess=="v")write
<<"              [vold,vold1,0]        ,                                           \n";
if(PostProcess=="a")write 
<<"              [aold,aold1,0]        ,                                           \n";
if(PostProcess=="uva")write
<<"              [uold,uold1,0]        ,                                           \n"
<<"              [vold,vold1,0]        ,                                           \n"
<<"              [aold,aold1,0]        ,                                           \n";

write
<<"              order=vtuorder        ,                                           \n"
<<"              dataname=namedata                                                 \n"
<<"           );                                                                   \n"
<<(timelog ? "  timerend  (\"ParaView plotting\",t0)\n" : ""                       );
}

if(plotTime){write
<<"                                                                                \n"
<<"  //-----------------Paraview plotting-------------//                           \n"
<<"                                                                                \n"
<<(timelog ? "  MPItimerbegin(\"ParaView plotting\",t0)\n" : ""                    )
<<"  exportTimeStep( namevtu,                                                      \n"
<<"                  Th                    ,                                       \n";

if(PostProcess!="v" & PostProcess!="a" & PostProcess!="uva")write
<<(spc==2 ? "\t\t [uold,uold1,0]\t   ,\n" : "\t\t [uold,uold1,uold2]\t   ,\n"      );

if(PostProcess=="v")write
<<(spc==2 ? "\t\t [vold,vold1,0]\t   ,\n" : "\t\t [vold,vold1,vold2]\t   ,\n"      );

if(PostProcess=="a")write
<<(spc==2 ? "\t\t [aold,aold1,0]\t   ,\n" : "\t\t [aold,aold1,aold2]\t   ,\n"      );

if(PostProcess=="uva")write
<<(spc==2 ? "\t\t [uold,uold1,0]\t   ,\n" : "\t\t [uold,uold1,uold2]\t   ,\n"      )
<<(spc==2 ? "\t\t [vold,vold1,0]\t   ,\n" : "\t\t [vold,vold1,vold2]\t   ,\n"      )
<<(spc==2 ? "\t\t [aold,aold1,0]\t   ,\n" : "\t\t [aold,aold1,aold2]\t   ,\n"      );

write
<<"                  vtuorder              ,                                       \n"
<<"                  iterout               ,                                       \n"
<<"                  t                     ,                                       \n"
<<"                  namedata                                                      \n"
<<"           );                                                                   \n"
<<(timelog ? "  timerend  (\"ParaView plotting\",t0)\n" : ""                       );
}


if(plotAll)if(spc==3){write
<<"                                                                                \n"
<<"  //-----------------Paraview plotting-------------//                           \n"
<<"                                                                                \n"
<<(timelog ? "  timerbegin(\"ParaView plotting\",t0)\n" : ""                       )
<<"  string   namevtu=\"VTUs/Solution\"+iterout+\".vtu\";                          \n"
<<"  savevtk  (  namevtu               ,                                           \n"
<<"              Th                    ,                                           \n";

if(PostProcess!="v" & PostProcess!="a" & PostProcess!="uva")write
<<"              [uold,uold1,uold2]    ,                                           \n";
if(PostProcess=="v")write
<<"              [vold,vold1,vold2]    ,                                           \n";
if(PostProcess=="a")write 
<<"              [aold,aold1,aold2]    ,                                           \n";
if(PostProcess=="uva")write
<<"              [uold,uold1,uold2]    ,                                           \n"
<<"              [vold,vold1,vold2]    ,                                           \n"
<<"              [aold,aold1,aold2]    ,                                           \n";

write
<<"              order=vtuorder        ,                                           \n"
<<"              dataname=namedata                                                 \n"
<<"           );                                                                   \n"
<<(timelog ? "  timerend  (\"ParaView plotting\",t0)\n" : ""                       );
}

write
<<"                                                                                \n"
<<"  //-----------------updating time----------------//                            \n"
<<"                                                                                \n"
<<"  t += dt;                                                                      \n";

if(plotAll || plotTime)write
<<"                                                                                \n"
<<"  //-----------updating iteration count-----------//                            \n"
<<"                                                                                \n"
<<"  iterout++;                                                                    \n";

write
<<"                                                                                \n"
<<"}                                                                               \n"
<<"                                                                                \n"
<<(plotTime ? "exportEnd(namevtu)\n" : " "                                          )
<<"                                                                                \n"
<<(timelog ? "cout << \" all operations ended, they \";\n" : ""                     )
<<(timelog ? "timerend  (\"solver\",t1)\n" : " "                                    )
<<"                                                                                \n"
<<"//-------------------------------THE END------------------------------//        \n"; 

}  //-- [if loop terminator] Sequential Dynamic ended --//


if(!Sequential){write    
<<"                                                                                \n"
<<"//==============================================================================\n"
<<"//  ------- Dynamic loop for linear assembly and solving -------                \n"
<<"//==============================================================================\n"  
<<"                                                                                \n"
<<"while (t <= tmax){                                                              \n"
<<"                                                                                \n"
<<"  if(mpirank==0)                                                                \n"
<<"  cout.scientific<<\"-----------------------------------------------------\\n\" \n"
<<"  << \"Time iteration at t :\" << t << \" (s)\\n \"<< endl;                     \n"
<<"                                                                                \n"
<<"  //--------------tt update for loading--------------//                         \n"
<<"                                                                                \n"
<<"  tt  = t;                                                                      \n"
<<"                                                                                \n"
<<"  //-----------------Assembly for A-----------------//                          \n"
<<"                                                                                \n"
<<(timelog ? "  MPItimerbegin(\"matrix assembly\",t0)\n" : ""                      )
<<"  ALoc = soildynamics(Vh,Vh,solver=CG,sym=1);                                 \n"
<<(timelog ? "  MPItimerend  (\"matrix assembly\",t0)\n" : ""                      )
<<"                                                                                \n"
<<(timelog ? "  MPItimerbegin(\"PETSc assembly\",t0)\n"  : ""                      )
<<"  changeOperator(A, ALoc);                                                      \n"
<<(timelog ? "  MPItimerend(\"PETSc assembly\",t0)\n"    : ""                      )
<<"                                                                                \n";

if(Model=="pseudo-nonlinear")write
<<"                                                                                \n"
<<"  //---------update Nonlinear displacement-----------//                         \n"
<<"                                                                                \n"
<<"  uNL[] = uold[];                                                               \n"
<<"                                                                                \n"
<<"  for (int k=0; k<5; k++){                   // Nonlinear NR loop               \n"
<<"                                                                                \n";

write
<<"                                                                                \n"
<<"  //-----------------Assembly for b-----------------//                          \n"
<<"                                                                                \n"
<<(timelog ? "  MPItimerbegin(\"RHS assembly\",t0)\n" : ""                         )
<<"  b = soildynamics(0,Vh);                                                     \n"
<<(timelog ? "  MPItimerend  (\"RHS assembly\",t0)\n" : ""                         )
<<"                                                                                \n"
<<"  //-----------------Solving du=A^-1*b--------------//                          \n"
<<"                                                                                \n"
<<(timelog ? "  MPItimerbegin(\"solving U\",t0)\n" : ""                            )
<<"  set(A,sparams =\"  -ksp_type cg  \");                                         \n"
<<"  du[] = A^-1*b;                                                                \n"
<<(timelog ? "  MPItimerend  (\"solving U\",t0)\n" : ""                            )
<<"                                                                                \n";


if(Model=="pseudo-nonlinear")write
<<"                                                                                \n"
<<"  //---------update Nonlinear displacement-----------//                         \n"
<<"                                                                                \n"
<<"  uNL[] += du[];                                                                \n"
<<"                                                                                \n"
<<"    //------Newton-Raphsons Error calculation---------//                        \n"
<<"                                                                                \n"
<<(timelog ? "    MPItimerbegin(\"NL error checking\",t0)\n" : ""                  )
<<"    real err1Gather,  err1Loc ;                                                 \n"
<<"                                                                                \n"
<<"        b = b .* DP                                   ;                         \n"                        
<<"        err1Loc = b.l2                                ;                         \n"                          
<<"        err1Loc = err1Loc*err1Loc                     ;                         \n"                          
<<"        mpiAllReduce(err1Loc,err1Gather,mpiCommWorld,mpiSUM);                   \n"                          
<<"        err1Gather = sqrt(err1Gather) ;                                         \n"
<<"                                                                                \n"               
<<(timelog ? "    MPItimerend (\"NL error checking\",t0)\n" : ""                   )
<<"                                                                                \n"
<<"    //--------------- Convergence conditional---------------------//            \n"
<<"                                                                                \n"
<<"    if(err1Gather < 1e-5 || k==4){                                              \n"
<<"                                                                                \n"
<<"      //------------------Screen output norm----------------------//            \n"
<<"                                                                                \n"
<<"      if(mpirank==0)                                                            \n"
<<"      cout.scientific << \"NL iteration number :  [ \"  << k                    \n"
<<"      << \" ]\\nL2 error in [u] :  [ \"    << err1Gather                        \n"
<<"      << \" ]\"      << endl;                                                   \n"
<<"                                                                                \n"
<<"      break;                                                                    \n"
<<"                                                                                \n"
<<"     }                                                                          \n"
<<" }    // Nonlinear NR loop ends                                                 \n"
<<"                                                                                \n"
<<"  //---------------update  displacement--------------//                         \n"
<<"                                                                                \n"
<<"  du[] = uNL[];                                                                 \n"
<<"                                                                                \n";

if(debug)write
<<"                                                                                \n"
<<"  //-----------------Move mesh plotting------------//                           \n"
<<"                                                                                \n"
<<"  macro defplot(i) i//                                                          \n"
<<"  plotMPI(Th, du1, P1, defplot, real, wait=0, cmm=\"T-\"+t+\"\");               \n";

write
<<"                                                                                \n"
<<"  //-----------------updating variables------------//                           \n"
<<"                                                                                \n"
<<(timelog ? "  MPItimerbegin(\"updating variables\",t0)\n" : ""                   )
<<(useGFP  ? "  GFPUpdateDynamic(du[],uold[],vold[],aold[],beta,gamma,dt);\n" : "" )
<<(!useGFP ? "  updateVariables(du,uold,vold,aold,beta,gamma,dt)\n" : ""           )
<<(timelog ? "  MPItimerend(\"updating variables\",t0)\n" : ""                     );


if(plotAll)if(spc==2){write
<<"                                                                                \n"
<<"  //-----------------ParaView plotting--------------//                          \n"
<<"                                                                                \n"
<<(timelog ? "  MPItimerbegin(\"ParaView plotting\",t0)\n" : ""                    )
<<"                                                                                \n";


write
<<"    savevtk(  \"VTUs/Solution.vtu\"   ,                                         \n"
<<"                 Th                 ,                                           \n";

if(PostProcess!="v" & PostProcess!="a" & PostProcess!="uva")write
<<"                 [uold,uold1,0]     ,                                           \n";
if(PostProcess=="v")write
<<"                 [vold,vold1,0]     ,                                           \n";
if(PostProcess=="a")write 
<<"                 [aold,aold1,0]     ,                                           \n";
if(PostProcess=="uva")write
<<"                 [uold,uold1,0]     ,                                           \n"
<<"                 [vold,vold1,0]     ,                                           \n"
<<"                 [aold,aold1,0]     ,                                           \n";

write
<<"                 order=vtuorder     ,                                           \n"
<<"                 dataname=\"U\"       ,                                         \n"
<<"                 append=true                                                    \n"
<<"              );                                                                \n"
<<(timelog ? "  MPItimerend(\"ParaView plotting\",t0)\n" : ""                      );
}


if(plotTime)if(spc==3)write
<<"                                                                                \n"
<<"  //-----------------Paraview plotting-------------//                           \n"
<<"                                                                                \n"
<<(timelog ? "  MPItimerbegin(\"ParaView plotting\",t0)\n" : ""                    )
<<"  exportTimeStep( namevtu,                                                      \n"
<<"                  Th                    ,                                       \n"
<<"                  [uold,uold1,uold2]    ,                                       \n"
<<"                  vtuorder              ,                                       \n"
<<"                  iterout               ,                                       \n"
<<"                  t                     ,                                       \n"
<<"                  namedata              ,                                       \n"
<<"                  mpiCommWorld                                                  \n"
<<"           );                                                                   \n"
<<(timelog ? "  MPItimerend(\"ParaView plotting\",t0)\n" : ""                      );

if(plotAll)if(spc==3){write
<<"                                                                                \n"
<<"  //-----------------ParaView plotting--------------//                          \n"
<<"                                                                                \n"
<<(timelog ? "  MPItimerbegin(\"ParaView plotting\",t0)\n" : ""                    );


write
<<"    savevtk(  \"VTUs/Solution.vtu\"   ,                                         \n"
<<"                 Th                 ,                                           \n";

if(PostProcess!="v" & PostProcess!="a" & PostProcess!="uva")write
<<"                 [uold,uold1,uold2] ,                                           \n";
if(PostProcess=="v")write
<<"                 [vold,vold1,vold2] ,                                           \n";
if(PostProcess=="a")write
<<"                 [aold,aold1,aold2] ,                                           \n";
if(PostProcess=="uva")write
<<"                 [uold,uold1,uold2] ,                                           \n"
<<"                 [vold,vold1,vold2] ,                                           \n"
<<"                 [aold,aold1,aold2] ,                                           \n";

write
<<"                 order=vtuorder     ,                                           \n";

if(PostProcess!="v" & PostProcess!="a" & PostProcess!="uva")write
<<"                 dataname=\"U\"       ,                                         \n";

if(PostProcess=="v")write
<<"                 dataname=\"U  V\" ,                                            \n";
if(PostProcess=="a")write
<<"                 dataname=\"U  A\" ,                                            \n";
if(PostProcess=="uva")write
<<"                 dataname=\"U  V  A\" ,                                         \n";

write
<<"                 append=true                                                    \n"
<<"              );                                                                \n";


write
<<(timelog ? "  MPItimerend(\"ParaView plotting\",t0)\n" : ""                      );

}

write
<<"                                                                                \n"
<<"  //-----------------updating time----------------//                            \n"
<<"                                                                                \n"
<<"  t += dt;                                                                      \n";

write
<<"}                                                                               \n"
<<"                                                                                \n";

write
<<(timelog ? "if(mpirank==0)\n" : " "                                               )
<<(timelog ? "cout << \" all operations ended, they \";\n" : ""                     )
<<(timelog ? "MPItimerend  (\"solver\",t1)\n" : ""                                  )
<<"                                                                                \n"
<<"//-------------------------------THE END------------------------------//        \n"; 

}  //-- [if loop terminator] !Sequential Dynamic ended --//