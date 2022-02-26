//=====================================================================================
// ------ Building the PostProcessor.edp file ------
//=====================================================================================

cout << " building PostProcessor.edp";


ofstream  write("PostProcessor.edp");

writeHeader;


if(ParaViewPostProcess){
if(!Sequential)
 writeIt
 "  if(mpirank==0)                                                                \n";
 writeIt
 "     system(\"mv  VTUs/  VTUs_`date '+%b-%d-%Y-%H:%M'`\");                      \n";
} //-- [ostream terminator]  PostProcessor.edp closed --//


if(!Sequential)
 writeIt
 "  if(mpirank==0)                                                                \n";
 writeIt
 "     system(\"echo \\\""<<Prblm<<"\\t$(date '+%Y-%b-%d\\t%H:%M')\\t$HOSTNAME\\t\\t"<<spc<<"D\\t"
 "\\tSeq.\\\" >>simulation-log.csv\");                                            \n";


cout << " ............................ Done \n";
