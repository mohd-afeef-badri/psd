//=====================================================================================
// ------ Building the PostProcessor.edp file ------
//=====================================================================================

cout << " building PostProcessor.edp";

if(plotAll){
ofstream  write("PostProcessor.edp");

writeHeader;

if(!Sequential)if(Prblm=="soildynamics")write
<<"  if(mpirank==0){                                                               \n"
<<"     system(\"mv  VTUs/  VTUs_`date '+%b-%d-%Y-%H:%M'`\");                      \n"
<<"     system(\"echo \\\"Soil-dynamics\\t$(date '+%Y-%b-%d\\t%H:%M')\\t$HOSTNAME\\t\\t"<<spc<<"D\\t"
<<"\\t\"+mpisize+\"\\\" >>simulation-log.csv\");                                           \n"
<<"  }                                                                             \n";

if(Sequential)if(Prblm=="soildynamics")write
<<"     system(\"mv  VTUs/  VTUs_`date '+%b-%d-%Y-%H:%M'`\");                      \n"
<<"     system(\"echo \\\"Soil-dynamics\\t$(date '+%Y-%b-%d\\t%H:%M')\\t$HOSTNAME\\t\\t"<<spc<<"D\\t"
<<"\\tSeq.\\\" >>simulation-log.csv\");                                            \n";

if(!Sequential)if(Prblm=="elastodynamics")write
<<"  if(mpirank==0){                                                               \n"
<<"     system(\"mv  VTUs/  VTUs_`date '+%b-%d-%Y-%H:%M'`\");                      \n"
<<"     system(\"echo \\\"Elasto-dynamics\\t$(date '+%Y-%b-%d\\t%H:%M')\\t$HOSTNAME\\t\\t"<<spc<<"D\\t"
<<"\\t\"+mpisize+\"\\\" >>simulation-log.csv\");                                           \n"
<<"  }                                                                             \n";

if(Sequential)if(Prblm=="elastodynamics")write
<<"     system(\"mv  VTUs/  VTUs_`date '+%b-%d-%Y-%H:%M'`\");                      \n"
<<"     system(\"echo \\\"Elasto-dynamics\\t$(date '+%Y-%b-%d\\t%H:%M')\\t$HOSTNAME\\t\\t"<<spc<<"D\\t"
<<"\\tSeq.\\\" >>simulation-log.csv\");                                            \n";

if(!Sequential)if(Prblm=="damage" && Model=="hybrid-phase-field")write
<<"  if(mpirank==0){                                                               \n"
<<"     system(\"mv  VTUs/  VTUs_`date '+%b-%d-%Y-%H:%M'`\");                      \n"
<<"     system(\"echo \\\"Phase-field\\t$(date '+%Y-%b-%d\\t%H:%M')\\t$HOSTNAME\\t\\t"<<spc<<"D\\t"
<<"\\t\"+mpisize+\"\\\" >>simulation-log.csv\");                                           \n"
<<"  }                                                                             \n";

if(Sequential)if(Prblm=="damage" && Model=="hybrid-phase-field")write
<<"     system(\"mv  VTUs/  VTUs_`date '+%b-%d-%Y-%H:%M'`\");                      \n"
<<"     system(\"echo \\\"Phase-field\\t$(date '+%Y-%b-%d\\t%H:%M')\\t$HOSTNAME\\t\\t"<<spc<<"D\\t"
<<"\\tSeq.\\\" >>simulation-log.csv\");                                            \n";

if(!Sequential)if(Prblm=="linear-elasticity"){write
<<"                                                                                \n"
<<"//==============================================================================\n"
<<"// -------Plotting with paraview-------//                                       \n"
<<"//==============================================================================\n"
<<"                                                                                \n"
<<"  if(mpirank==0)                                                                \n"
<<"     system(\"mkdir -p VTUs/\");                                                \n"
<<"  mpiBarrier(mpiCommWorld);                                                     \n"
<<"                                                                                \n"
<<(timelog ? "  MPItimerbegin(\"Paraview Plotting\",t0)\n" : ""                     )
<<"  int[int] vtuorder=[1];                     // Solution export order           \n";

/*
<<"     string   namevtu=\"VTUs/Solution\";             // Name of PV files        \n"
<<"     string   namedata=\"U\";                        // Name of export data     \n"
<<"     bool     withsur=true;                          // Export surface mesh     \n";
*/
/*
if(spc==2)write
<<"                                                                                \n"
<<"     exportpvd(namevtu, Th,[u,u1,0], vtuorder, withsur, namedata, mpiCommWorld);\n";

if(spc==3)write
<<"                                                                                \n"
<<"     exportpvd(namevtu, Th,[u,u1,u2], vtuorder, withsur,namedata, mpiCommWorld);\n";
*/

if(spc==2)write
<<"  savevtk( \"VTUs/Solution.vtu\"     ,                                          \n"
<<"            Th                  ,                                               \n"
<<"            [u,u1,0]                 ,                                          \n";

if(spc==3)write
<<"  savevtk(\"VTUs/Solution.vtu\"      ,                                          \n"
<<"            Th                  ,                                               \n"
<<"            [u,u1,u2]                ,                                          \n";

write
<<"             order=vtuorder          ,                                          \n"
<<"             dataname=\"U\"                                                     \n"
<<"         );                                                                     \n"
<<(timelog  ? " MPItimerend(\"Paraview Plotting\",t0)\n" : " "                      )
<<(timelog ? "  MPItimerend(\"Solver\",t1)\n" : " "                                 )
<<"                                                                                \n";

write
<<"  if(mpirank==0){                                                               \n"
<<"     system(\"mv  VTUs/  VTUs_`date '+%b-%d-%Y-%H:%M'`\");                      \n"
<<"     system(\"echo \\\"Elasticity\\t$(date '+%Y-%b-%d\\t%H:%M')\\t$HOSTNAME\\t\\t"<<spc<<"D\\t"
<<"\\t\"+mpisize+\"\\\" >>simulation-log.csv\");                                           \n"
<<"  }                                                                             \n";

}  //-- [if loop terminator] !Sequential ended --//

if(Sequential)if(Prblm=="linear-elasticity"){write
<<"                                                                                \n"
<<"//==============================================================================\n"
<<"// -------Plotting with paraview-------                                         \n"
<<"//==============================================================================\n"
<<"                                                                                \n"
<<"     system(\"mkdir -p VTUs/\");                                                \n"
<<"                                                                                \n"
<<(timelog ? "  timerbegin(\"Post-Processing\",t0)\n" : " "                        )
<<"  int[int] vtuorder=[1];                             // Solution export order   \n";

if(spc==2)write
<<"  savevtk( \"VTUs/Solution-Seq.vtu\" ,                                          \n"
<<"            Th                       ,                                          \n"
<<"            [u,u1,0]                 ,                                          \n";

if(spc==3)write
<<"  savevtk(\"VTUs/Solution-Seq.vtu\"  ,                                          \n"
<<"            Th                       ,                                          \n"
<<"            [u,u1,u2]                ,                                          \n";

write
<<"             order=vtuorder          ,                                          \n"
<<"             dataname=\"U\"                                                     \n"
<<"         );                                                                     \n"
<<(timelog ? "  timerend  (\"Post-Processing\",t0)\n" : " "                         )
<<(timelog ? "  timerend  (\"Solver\",t1)\n" : " "                                  )
<<"                                                                                \n";

write
<<"     system(\"mv  VTUs/  VTUs_`date '+%b-%d-%Y-%H:%M'`\");                      \n"
<<"     system(\"echo \\\"Elasticity\\t$(date '+%Y-%b-%d\\t%H:%M')\\t$HOSTNAME\\t\\t"<<spc<<"D\\t"
<<"\\tSeq.\\\" >>simulation-log.csv\");                                            \n";

}  //-- [if loop terminator] Sequential ended --//

} //-- [ostream terminator]  varfmatsolve.edp closed --//

cout << " ............................ Done \n";
