//=====================================================================================
// ------ Soil Dynamics for the LinearFormBuilderAndSolver.edp file ------
//=====================================================================================

if(Sequential){
 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "//  ------- Assembly for stiffness matrix A -------                             \n"
 "//==============================================================================\n"
 "                                                                                \n"
 "  //-----------------Assembly for A-----------------//                          \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"matrix assembly\",t0)\n" : ""                        )<<
 "  A = soildynamics(Vh,Vh,solver=CG,sym=1);                                      \n"
 "  set(A,solver=CG,sym=1);                                                       \n"
<<(timelog ? "  timerend  (\"matrix assembly\",t0)\n" : ""                        )<<
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
 "                                                                                \n"
 "  tt  = t;                                                                      \n"
 "                                                                                \n"
 "  //-----------------Assembly for b-----------------//                          \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"RHS assembly\",t0)\n" : ""                           )<<
 "  b = soildynamics(0,Vh);                                                       \n"
<<(timelog ? "  timerend  (\"RHS assembly\",t0)\n" : ""                           )<<
 "                                                                                \n"
 "  //-----------------Solving du=A^-1*b--------------//                          \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"solving U\",t0)\n" : ""                              )<<
 "  du[] = A^-1*b;                                                                \n"
<<(timelog ? "  timerend  (\"solving U\",t0)\n" : ""                              )<<
 "                                                                                \n";

if(debug)
 writeIt
 "                                                                                \n"
 "  //-----------------Move mesh plotting------------//                           \n"
 "                                                                                \n"
 "  plot (du1,wait=0, cmm= \"t = \"+t+\" (s)\",value=1);                          \n";


 writeIt
 "                                                                                \n"
 "  //-----------------updating variables------------//                           \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"updating variables\",t0)\n" : ""                     )
<<(useGFP  ? "  GFPUpdateDynamic(du[],uold[],vold[],aold[],beta,gamma,dt);\n" : "")
<<(!useGFP ? "  updateVariables(du,uold,vold,aold,beta,gamma,dt)\n" : ""          )
<<(timelog ? "  timerend  (\"updating variables\",t0)\n" : ""                     );


if(ParaViewPostProcess){
 writeIt
 "                                                                                \n"
 "  //-----------------Paraview plotting-------------//                           \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"ParaView plotting\",t0)\n" : ""                       )<<
 "  string   namevtu=\"VTUs/Solution\"+iterout+\".vtu\";                          \n"
 "  savevtk  (  namevtu               ,                                           \n"
 "              Th                    ,                                           \n";

if(PostProcess=="u")
 writeIt
 "              PlotVec(uold)        ,                                            \n"
 "              dataname=\"U\"       ,                                            \n"; 
if(PostProcess=="v")
 writeIt
 "              PlotVec(vold)        ,                                            \n"
 "              dataname=\"V\"       ,                                            \n"; 
if(PostProcess=="a")
 writeIt
 "              PlotVec(aold)        ,                                            \n"
 "              dataname=\"A\"       ,                                            \n";  
if(PostProcess=="uv" || PostProcess=="vu")
 writeIt
 "              PlotVec(uold)        ,                                            \n"
 "              PlotVec(vold)        ,                                            \n"
 "              dataname=\"U V\"     ,                                            \n";  
if(PostProcess=="ua" || PostProcess=="au")
 writeIt
 "              PlotVec(uold)        ,                                            \n"
 "              PlotVec(aold)        ,                                            \n"
 "              dataname=\"U A\"     ,                                            \n";   
if(PostProcess=="va" || PostProcess=="av")
 writeIt
 "              PlotVec(vold)        ,                                            \n"
 "              PlotVec(aold)        ,                                            \n"
 "              dataname=\"V A\"     ,                                            \n";            
if(   PostProcess=="uva" || PostProcess=="uav" || PostProcess=="vau" 
   || PostProcess=="vua" || PostProcess=="auv" || PostProcess=="ava" )
 writeIt
 "              PlotVec(uold)        ,                                            \n"
 "              PlotVec(vold)        ,                                            \n"
 "              PlotVec(aold)        ,                                            \n"
 "              dataname=\"U V A\"   ,                                            \n";   


 writeIt
 "              order=vtuorder                                                    \n"
 "           );                                                                   \n"
 "                                                                                \n"
 "  //-----------updating iteration count-----------//                            \n"
 "                                                                                \n"
 "  iterout++;                                                                    \n" 
<<(timelog ? "  timerend  (\"ParaView plotting\",t0)\n" : ""                       );
}

 writeIt
 "                                                                                \n"
 "  //-----------------updating time----------------//                            \n"
 "                                                                                \n"
 "  t += dt;                                                                      \n"
 "                                                                                \n"
 "}                                                                               \n"
 "                                                                                \n"
<<(timelog ? "cout << \" all operations ended, they \";\n" : ""                     )
<<(timelog ? "timerend  (\"solver\",t1)\n" : " "                                  )<<
 "                                                                                \n"
 "//-------------------------------THE END------------------------------//        \n";

}  //-- [if loop terminator] Sequential Dynamic ended --//


if(!Sequential){



 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "//  ------- Assembly for stiffness matrix A -------                             \n"
 "//==============================================================================\n"
 "                                                                                \n"
 "  //-----------------Local Assembly-----------------//                          \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"matrix assembly\",t0)\n" : ""                     )<<
 "  ALoc = soildynamics(Vh,Vh,solver=CG,sym=1);                                   \n"
<<(timelog ? "  timerend  (\"matrix assembly\",t0)\n" : ""                     )<<
 "                                                                                \n";

if(doublecouple=="displacement_based" || doublecouple=="force_based"){


 if(!pointprobe) 
 writeIt 
 "                                                                                \n"
 "//==============================================================================\n"
 "//  ------- Applying double couple point boundary condition -------             \n"
 "//==============================================================================\n"
 "                                                                                \n"
 <<(timelog ? "  timerbegin(\"Applying double couple A\",t0)\n"  : ""             )<<
 "                                                                                \n" 
 "  GetDoubelCoupleIndicies(                                                      \n"
 "           DcNorthPointCord,DcSouthPointCord,DcEastPointCord, DcWestPointCord,  \n"
 "           iNorth,iSouth,iEast,iWest,                                           \n"
 "           Nrank,Srank,Erank,Wrank                                              \n"
 "   );                                                                           \n"
 "                                                                                \n";

 if(pointprobe && dirichletpointconditions<1) 
 writeIt 
 "                                                                                \n"
 "//==============================================================================\n"
 "//  ----- Applying double couple point boundary condition and point probe-----  \n"
 "//==============================================================================\n"
 "                                                                                \n"
 <<(timelog ? "  timerbegin(\"Applying double couple A & point probe\",t0)\n" : "")<<
 "                                                                                \n"  
 "  GetDoubelCoupleIndicies(                                                      \n"
 "           DcNorthPointCord,DcSouthPointCord,DcEastPointCord, DcWestPointCord,  \n"
 "           iNorth,iSouth,iEast,iWest,                                           \n"
 "           Nrank,Srank,Erank,Wrank,                                             \n"
 "           ProbePointCord,   iProbe, Prank                                      \n"  
 "   );                                                                           \n"
 "                                                                                \n";

if(doublecouple=="displacement_based")
 writeIt
 "                                                                                \n"
 "   ApplyDoubleCoupleToA(                                                        \n"
 "           ALoc,                                                                \n"
 "           iNorth,iSouth,iEast,iWest,                                           \n"
 "           Nrank,Srank,Erank,Wrank                                              \n"
 "   );                                                                           \n";


 writeIt
 "                                                                                \n"
<<(timelog ? "  timerend  (\"Applying double couple A\",t0)\n" : ""            )<<
 "                                                                                \n";
}


if(doublecouple=="unused" && pointprobe && dirichletpointconditions<1){
 writeIt
 "                                                                                \n"
 <<(timelog ? "  timerbegin(\"Finding point probe indicies\",t0)\n" : ""          )<<
 "  GetPointProbeIndicies(                                                        \n"
 "           ProbePointCord,   iProbe, Prank                                      \n"  
 "   );                                                                           \n"
 "                                                                                \n"
 <<(timelog ? "  timerend  (\"Finding point probe indicies\",t0)\n" : ""          )<< 
 "                                                                                \n";
}

if(pointprobe && spc==3)
 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "//  ------- Writing probe file  headers -------                                 \n"
 "//==============================================================================\n"
 "                                                                                \n"
 "  for(int j=0; j < iProbe.n; j++)                                               \n"
 "    if(mpirank==Prank[j]){                                                      \n"
 "      ofstream writeprobe(\"probe_\"+j+\"_rank_\"+mpirank+\".data\");           \n"
 "      writeprobe << \"# Probe location: P(x,y,z) = P(\"                         \n"
 "                 << ProbePointCord (j,0) << \" , \"                             \n"
 "                 << ProbePointCord (j,1) << \" , \"                             \n"
 "                 << ProbePointCord (j,2) << \")\"                               \n"
 "                 << \" Probe Rank :  \" << Prank[j]                             \n"
 "                 <<  endl;                                                      \n"
 "                                                                                \n"
 "      writeprobe << \"# u1  u2  u3  v1  v2  v3  a1  a2  a3\" << endl;           \n"
 "    }                                                                           \n"
 "                                                                                \n";      

if(pointprobe && spc==2)
 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "//  ------- Writing probe file  headers -------                                 \n"
 "//==============================================================================\n"
 "                                                                                \n"
 "  for(int j=0; j < iProbe.n; j++)                                               \n"
 "    if(mpirank==Prank[j]){                                                      \n"
 "      ofstream writeprobe(\"probe_\"+j+\"_rank_\"+mpirank+\".data\");           \n"
 "      writeprobe << \"# Probe location: P(x,y) = P(\"                           \n"
 "                 << ProbePointCord (j,0) << \" , \"                             \n"
 "                 << ProbePointCord (j,1) << \")\"                               \n"
 "                 << \" Probe Rank :  \" << Prank[j]                             \n"
 "                 <<  endl;                                                      \n"
 "                                                                                \n"
 "      writeprobe << \"# u1  u2   v1  v2   a1  a2\" << endl;                     \n"
 "    }                                                                           \n"
 "                                                                                \n";


 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "//  ------- PETSc Assembly for stiffness matrix A -------                       \n"
 "//==============================================================================\n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"PETSc assembly\",t0)\n"  : ""                     )<<
 "  A=ALoc;  //changeOperator(A, ALoc);                                           \n"
 "  set(A,sparams =\"  -ksp_type cg   \");                                        \n"
<<(timelog ? "  timerend(\"PETSc assembly\",t0)\n"    : ""                     )<<
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
 "                                                                                \n";

if(doublecouple=="unused")
 writeIt
 "  //--------------tt update for loading--------------//                         \n"
 "                                                                                \n"
 "  tt  = t;                                                                      \n"
 "                                                                                \n";



if(Model=="pseudo_nonlinear")
 writeIt
 "                                                                                \n"
 "  //---------update nonlinear displacement-----------//                         \n"
 "                                                                                \n"
 "  uNL[] = uold[];                                                               \n"
 "                                                                                \n"
 "  for (int k=0; k<5; k++){  // pseudo_nonlinear NR loop                         \n"
 "                                                                                \n";

if(Model=="Hujeux")
 writeIt
 "                                                                                \n"
 "  //---------update nonlinear displacement-----------//                         \n"
 "                                                                                \n"
 "  uNL[] = uold[];                                                               \n"
 "                                                                                \n"
 "  for (int k=0; k<5; k++){  // Hujeux NR loop                                   \n"
 "                                                                                \n";


 writeIt
 "                                                                                \n"
 "  //-----------------Assembly for b-----------------//                          \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"RHS assembly\",t0)\n" : ""                        )<<
 "  b = soildynamics(0,Vh);                                                       \n"
<<(timelog ? "  timerend  (\"RHS assembly\",t0)\n" : ""                        )<<
 "                                                                                \n";

if(doublecouple=="displacement_based" || doublecouple=="force_based" )
 writeIt
 "                                                                                 \n"
<<(timelog ? "  timerbegin(\"Applying double couple b\",t0)\n"  : ""             )<<
 "   ApplyDoubleCoupleToRHS(                                                       \n"
 "           b,                                                                    \n"
 "           DcNorthCondition,DcSouthCondition,DcEastCondition,DcWestCondition,    \n"
 "           iNorth,iSouth,iEast,iWest,                                            \n"
 "           Nrank,Srank,Erank,Wrank                                               \n"
 "   );                                                                            \n"
<<(timelog ? "  timerend  (\"Applying double couple b\",t0)\n" : ""             )<<
 "                                                                                 \n";

 writeIt
 "                                                                                \n"
 "  //-----------------Solving du=A^-1*b--------------//                          \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"solving U\",t0)\n" : ""                           )<<
 "  du[] = A^-1*b;                                                                \n"
<<(timelog ? "  timerend  (\"solving U\",t0)\n" : ""                           )<<
 "                                                                                \n";


if(Model=="pseudo_nonlinear")
 writeIt
 "                                                                                \n"
 "  //---------update Nonlinear displacement-----------//                         \n"
 "                                                                                \n"
 "  uNL[] += du[];                                                                \n"
 "                                                                                \n"
 "  //------Newton-Raphsons Error calculation---------//                          \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"NL error checking\",t0)\n" : ""                   )<<
 "  real err1Gather,  err1Loc ;                                                   \n"
 "                                                                                \n"
 "  b = b .* DP                                   ;                               \n"
 "  err1Loc = b.l2                                ;                               \n"
 "  err1Loc = err1Loc*err1Loc                     ;                               \n"
 "  mpiAllReduce(err1Loc,err1Gather,mpiCommWorld,mpiSUM);                         \n"
 "  err1Gather = sqrt(err1Gather) ;                                               \n"
 "                                                                                \n"
<<(timelog ? "  timerend (\"NL error checking\",t0)\n" : ""                    )<<
 "                                                                                \n"
 "  //--------------- Convergence conditional---------------------//              \n"
 "                                                                                \n"
 "  if(err1Gather < 1e-5 || k==4){                                                \n"
 "                                                                                \n"
 "  //------------------Screen output norm----------------------//                \n"
 "                                                                                \n"
 "   if(mpirank==0)                                                               \n"
 "    cout.scientific << \"NL iteration number :  [ \"  << k                      \n"
 "    << \" ]\\nL2 error in [u] :  [ \"    << err1Gather                          \n"
 "    << \" ]\"      << endl;                                                     \n"
 "                                                                                \n"
 "   break;                                                                       \n"
 "                                                                                \n"
 "  }                                                                             \n"
 " }    // pseudo-nonlinear NR loop ends                                          \n"
 "                                                                                \n"
 "  //---------------update  displacement--------------//                         \n"
 "                                                                                \n"
 "  du[] = uNL[];                                                                 \n"
 "                                                                                \n";


if(Model=="Hujeux")
 writeIt
 "                                                                                \n"
 "  //---------update nonlinear displacement-----------//                         \n"
 "                                                                                \n"
 "  uNL[] += du[];                                                                \n"
 "                                                                                \n"
 "  //------------calculate stress vector--------------//                         \n"
 "                                                                                \n"
 "  calculateStress(Sig,uNL,lambda,mu);                                           \n"
 "                                                                                \n"
 "  //------Newton-Raphsons error calculation---------//                          \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"NL error checking\",t0)\n" : ""                   )<<
 "  real err1Gather,  err1Loc ;                                                   \n"
 "                                                                                \n"
 "  b = b .* DP                                   ;                               \n"
 "  err1Loc = b.l2                                ;                               \n"
 "  err1Loc = err1Loc*err1Loc                     ;                               \n"
 "  mpiAllReduce(err1Loc,err1Gather,mpiCommWorld,mpiSUM);                         \n"
 "  err1Gather = sqrt(err1Gather) ;                                               \n"
 "                                                                                \n"
<<(timelog ? "  timerend (\"NL error checking\",t0)\n" : ""                    )<<
 "                                                                                \n"
 "  //--------------- convergence conditional---------------------//              \n"
 "                                                                                \n"
 "  if(err1Gather < 1e-5 || k==4){                                                \n"
 "                                                                                \n"
 "  //------------------screen output norm----------------------//                \n"
 "                                                                                \n"
 "   if(mpirank==0)                                                               \n"
 "    cout.scientific << \"NL iteration number :  [ \"  << k                      \n"
 "    << \" ]\\nL2 error in [u] :  [ \"    << err1Gather                          \n"
 "    << \" ]\"      << endl;                                                     \n"
 "                                                                                \n"
 "   break;                                                                       \n"
 "                                                                                \n"
 "  }                                                                             \n"
 " }    // Hujeux NR loop ends                                                    \n"
 "                                                                                \n"
 "  //---------------update  displacement--------------//                         \n"
 "                                                                                \n"
 "  du[] = uNL[];                                                                 \n"
 "                                                                                \n";

if(debug && !top2vol)
 writeIt
 "                                                                                \n"
 "  //-----------------Move mesh plotting------------//                           \n"
 "                                                                                \n"
 "  macro defplot(i) i//                                                          \n"
 "  plotMPI(Th, du1, P1, defplot, real, wait=0, cmm=\"T-\"+t+\"\");               \n";

if(debug && top2vol)
 writeIt
 "                                                                                \n"
 "  //-----------------Move mesh plotting------------//                           \n"
 "                                                                                \n"
 "  macro defplot(i) i//                                                          \n"
 "  plotMPI(Th, du1, P1, defplot, real,  cmm=\"T-\"+t+\"\");                      \n";

 writeIt
 "                                                                                \n"
 "  //-----------------updating variables------------//                           \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"updating variables\",t0)\n" : ""                   )
<<(useGFP  ? "  GFPUpdateDynamic(du[],uold[],vold[],aold[],beta,gamma,dt);\n" : "" )
<<(!useGFP ? "  updateVariables(du,uold,vold,aold,beta,gamma,dt)\n" : ""           )
<<(timelog ? "  timerend(\"updating variables\",t0)\n" : ""                     );


if(pointprobe && spc==3)
 writeIt
 "                                                                                \n"
 "  //-----------------pointprobe writing------------//                           \n"
 "                                                                                \n"
 "  for(int j=0; j < iProbe.n; j++)                                               \n"
 "     if(mpirank==Prank[j]){                                                     \n"
 "      ofstream writeprobe(\"probe_\"+j+\"_rank_\"+mpirank+\".data\",append);    \n"
 "      writeprobe << t                   << \"\\t\"                              \n" 
 "                 << uold[][iProbe[j]]   << \"\\t\"                              \n"  
 "                 << uold[][iProbe[j]+1] << \"\\t\"                              \n" 
 "                 << uold[][iProbe[j]+2] << \"\\t\"                              \n"  
 "                 << vold[][iProbe[j]]   << \"\\t\"                              \n"  
 "                 << vold[][iProbe[j]+1] << \"\\t\"                              \n"  
 "                 << vold[][iProbe[j]+2] << \"\\t\"                              \n" 
 "                 << aold[][iProbe[j]]   << \"\\t\"                              \n"  
 "                 << aold[][iProbe[j]+1] << \"\\t\"                              \n"  
 "                 << aold[][iProbe[j]+2] << \"\\t\"                              \n" 
 "                 << endl;                                                       \n" 
 "     }                                                                          \n";  


if(pointprobe && spc==2)
 writeIt
 "                                                                                \n"
 "  //-----------------pointprobe writing------------//                           \n"
 "                                                                                \n"
 "  for(int j=0; j < iProbe.n; j++)                                               \n"
 "     if(mpirank==Prank[j]){                                                     \n"
 "      ofstream writeprobe(\"probe_\"+j+\"_rank_\"+mpirank+\".data\",append);    \n"
 "      writeprobe << t                   << \"\\t\"                              \n"
 "                 << uold[][iProbe[j]]   << \"\\t\"                              \n" 
 "                 << uold[][iProbe[j]+1] << \"\\t\"                              \n"
 "                 << vold[][iProbe[j]]   << \"\\t\"                              \n" 
 "                 << vold[][iProbe[j]+1] << \"\\t\"                              \n" 
 "                 << aold[][iProbe[j]]   << \"\\t\"                              \n" 
 "                 << aold[][iProbe[j]+1] << \"\\t\"                              \n"
 "                 << endl;                                                       \n"
 "     }                                                                          \n"; 


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
 "              PlotVec(uold)        ,                                            \n"
 "              dataname=\"U\"       ,                                            \n"; 
if(PostProcess=="v")
 writeIt
 "              PlotVec(vold)        ,                                            \n"
 "              dataname=\"V\"       ,                                            \n"; 
if(PostProcess=="a")
 writeIt
 "              PlotVec(aold)        ,                                            \n"
 "              dataname=\"A\"       ,                                            \n";  
if(PostProcess=="uv" || PostProcess=="vu")
 writeIt
 "              PlotVec(uold)        ,                                            \n"
 "              PlotVec(vold)        ,                                            \n"
 "              dataname=\"U V\"     ,                                            \n";  
if(PostProcess=="ua" || PostProcess=="au")
 writeIt
 "              PlotVec(uold)        ,                                            \n"
 "              PlotVec(aold)        ,                                            \n"
 "              dataname=\"U A\"     ,                                            \n";   
if(PostProcess=="va" || PostProcess=="av")
 writeIt
 "              PlotVec(vold)        ,                                            \n"
 "              PlotVec(aold)        ,                                            \n"
 "              dataname=\"V A\"     ,                                            \n";            
if(   PostProcess=="uva" || PostProcess=="uav" || PostProcess=="vau" 
   || PostProcess=="vua" || PostProcess=="auv" || PostProcess=="ava" )
 writeIt
 "              PlotVec(uold)        ,                                            \n"
 "              PlotVec(vold)        ,                                            \n"
 "              PlotVec(aold)        ,                                            \n"
 "              dataname=\"U V A\"   ,                                            \n"; 

 writeIt
 "                 order=vtuorder     ,                                           \n" 
 "                 append=true                                                    \n"
 "              );                                                                \n";

 writeIt
 (timelog ? "  timerend(\"ParaView plotting\",t0)\n" : ""                      );

}

if(pipegnu){
 writeIt
 "                                                                                \n"
 "  //---------------Energy calculations-------------//                           \n"
 "                                                                                \n"
<<(timelog ? "  timerbegin(\"Energy calculations\",t0)\n" : ""                 )<<
 "  E[0] =intN(Th,qforder=2)( 0.5*DPspc*(vold*vold+vold1*vold1));                 \n"
 "  E[1] =intN(Th,qforder=2)( 0.5*DPspc*(lambda*divergence(uold)*divergence(uold) \n"
 "                            + 2. * mu * epsilon(uold)'*epsilon(uold))  );       \n"
 "                                                                                \n"
 "  mpiAllReduce(E[0],EG[0],mpiCommWorld,mpiSUM);                                 \n"
 "  mpiAllReduce(E[1],EG[1],mpiCommWorld,mpiSUM);                                 \n"
 "                                                                                \n"
 "  //----------Appending energies to a file----------//                          \n"
 "                                                                                \n"
 "  if(mpirank==0){                                                               \n"
 "     ofstream ff(\"energies.data\",append);                                     \n"
 "     ff<< t << \"  \" << EG[0] << \"  \"<< EG[1] <<endl;                        \n";

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
 "     <<\"u ($1):($3+$2) w lp lw 2 pt 7 ps 2 t \\\"T.E\\\" \"                    \n"
 "     <<\"\\n\";                                                                 \n"
 "     flush(pgnuplot);                                                           \n";


 writeIt
 "                                                                                \n"
 "   }                                                                            \n"
<<(timelog ? "   timerend(\"Energy calculations\",t0)\n" : ""                   );
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
<<(timelog ? "timerend  (\"solver\",t1)\n" : ""                                 )<<
 "                                                                                \n"
 "//-------------------------------THE END------------------------------//        \n";

}  //-- [if loop terminator] !Sequential Dynamic ended --//
