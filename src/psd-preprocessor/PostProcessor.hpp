//=====================================================================================
// ------ Building the PostProcessor.edp file ------ 
//=====================================================================================

cout << " building PostProcessor.edp"; 

if(plotAll){
ofstream  writePostProcessor("PostProcessor.edp");

writePostProcessor
<<"                                                                                                \n"
<<"/**************************Variational formulation******************************                \n"
<<"*                                                                              *                \n"
<<"* Note!!! This file is  generated  by  running  PSD PreProcessor  Do  not edit *                \n"
<<"*         in order to  control this  file please change flag arguments of  the *                \n"
<<"*         PSD_PreProcess, details of which are present in PSD_PreProcess or in *                \n"
<<"*         the README.MD file.                                                  *                \n"
<<"*                                                                              *                \n"
<<"*******************************************************************************/                \n"
<<"										   \n"
<<"										   \n";

if(!Sequential)if(soildynamics)writePostProcessor
<<"  if(mpirank==0){								   \n"
<<"     system(\"mv  VTUs/  VTUs_`date '+%b-%d-%Y-%H:%M'`\");  			   \n"
<<"     system(\"echo \\\"Soil-dynamics\\t$(date '+%Y-%b-%d\\t%H:%M')\\t$HOSTNAME\\t\\t"<<spc<<"D\\t"
<<"\\t\"+mpisize+\"\\\" >>simulation-log.csv\");					   \n"
<<"  }										   \n";	

if(Sequential)if(soildynamics)writePostProcessor
<<"     system(\"mv  VTUs/  VTUs_`date '+%b-%d-%Y-%H:%M'`\");  			   \n"
<<"     system(\"echo \\\"Soil-dynamics\\t$(date '+%Y-%b-%d\\t%H:%M')\\t$HOSTNAME\\t\\t"<<spc<<"D\\t"
<<"\\tSeq.\\\" >>simulation-log.csv\");						   \n";

if(!Sequential)if(dynamic)writePostProcessor
<<"  if(mpirank==0){								   \n"
<<"     system(\"mv  VTUs/  VTUs_`date '+%b-%d-%Y-%H:%M'`\");  			   \n"
<<"     system(\"echo \\\"Elasto-dynamics\\t$(date '+%Y-%b-%d\\t%H:%M')\\t$HOSTNAME\\t\\t"<<spc<<"D\\t"
<<"\\t\"+mpisize+\"\\\" >>simulation-log.csv\");					   \n"
<<"  }										   \n";

if(Sequential)if(dynamic)writePostProcessor
<<"     system(\"mv  VTUs/  VTUs_`date '+%b-%d-%Y-%H:%M'`\");  			   \n"
<<"     system(\"echo \\\"Elasto-dynamics\\t$(date '+%Y-%b-%d\\t%H:%M')\\t$HOSTNAME\\t\\t"<<spc<<"D\\t"
<<"\\tSeq.\\\" >>simulation-log.csv\");						   \n";

if(!Sequential)if(nonlinear)writePostProcessor
<<"  if(mpirank==0){								   \n"
<<"     system(\"mv  VTUs/  VTUs_`date '+%b-%d-%Y-%H:%M'`\");  			   \n"
<<"     system(\"echo \\\"Phase-field\\t$(date '+%Y-%b-%d\\t%H:%M')\\t$HOSTNAME\\t\\t"<<spc<<"D\\t"
<<"\\t\"+mpisize+\"\\\" >>simulation-log.csv\");					   \n"
<<"  }										   \n";	

if(Sequential)if(nonlinear)writePostProcessor
<<"     system(\"mv  VTUs/  VTUs_`date '+%b-%d-%Y-%H:%M'`\");  			   \n"
<<"     system(\"echo \\\"Phase-field\\t$(date '+%Y-%b-%d\\t%H:%M')\\t$HOSTNAME\\t\\t"<<spc<<"D\\t"
<<"\\tSeq.\\\" >>simulation-log.csv\");						   \n";

if(!Sequential)if(!nonlinear)if(!dynamic)if(!soildynamics){writePostProcessor
<<"										   \n"        
<<"//==============================================================================\n"
<<"// -------Plotting with paraview-------//					   \n"
<<"//==============================================================================\n"
<<"										   \n"
<<"  if(mpirank==0)								   \n"
<<"     system(\"mkdir -p VTUs/\");			  			   \n"
<<"  mpiBarrier(mpiCommWorld);							   \n"
<<"										   \n"
<<(timelog ? "	MPItimerbegin(\"Paraview Plotting\",t0)\n" : ""       		    )
<<"  int[int] vtuorder=[1];			// Solution export order   	   \n";

/* 
<<"	string   namevtu=\"VTUs/Solution\";		// Name of PV files	   \n"
<<"	string   namedata=\"U\";			// Name of export data	   \n"
<<"	bool     withsur=true;				// Export surface mesh	   \n";
*/
/*
if(spc==2)writePostProcessor
<<"										   \n"
<<"     exportpvd(namevtu, Th,[u,u1,0], vtuorder, withsur, namedata, mpiCommWorld);\n"; 

if(spc==3)writePostProcessor
<<"										   \n"
<<"     exportpvd(namevtu, Th,[u,u1,u2], vtuorder, withsur,namedata, mpiCommWorld);\n";
*/

if(spc==2)writePostProcessor
<<"  savevtk( \"VTUs/Solution.vtu\"	,					   \n"
<<"            Th                  ,					   	   \n"
<<"            [u,u1,0]			,					   \n";
 
if(spc==3)writePostProcessor     
<<"  savevtk(\"VTUs/Solution.vtu\"	,			  		   \n"
<<"            Th                  ,						   \n"
<<"            [u,u1,u2]		,					   \n";    
  
writePostProcessor       
<<"             order=vtuorder		,					   \n"
<<"             dataname=\"U\"        						   \n"
<<"         );				   			 		   \n"        
<<(timelog  ? "	MPItimerend(\"Paraview Plotting\",t0)\n" : " "       		    )
<<(timelog ? "	MPItimerend(\"Solver\",t1)\n" : " "  	         	  	    )
<<"										   \n";

writePostProcessor       
<<"  if(mpirank==0){								   \n"
<<"     system(\"mv  VTUs/  VTUs_`date '+%b-%d-%Y-%H:%M'`\");  			   \n"
<<"     system(\"echo \\\"Elasticity\\t$(date '+%Y-%b-%d\\t%H:%M')\\t$HOSTNAME\\t\\t"<<spc<<"D\\t"
<<"\\t\"+mpisize+\"\\\" >>simulation-log.csv\");					   \n"
<<"  }										   \n";

}  //-- [if loop terminator] !Sequential ended --//

if(Sequential)if(!nonlinear)if(!dynamic)if(!soildynamics){writePostProcessor
<<"										   \n"	
<<"//==============================================================================\n"
<<"// -------Plotting with paraview-------					   \n"
<<"//==============================================================================\n"
<<"										   \n"
<<"     system(\"mkdir -p VTUs/\");			  			   \n"
<<"										   \n"
<<(timelog ? "	timerbegin(\"Post-Processing\",t0)\n" : " "  	    		   )
<<"  int[int] vtuorder=[1];				// Solution export order   \n"; 
  
if(spc==2)writePostProcessor
<<"  savevtk( \"VTUs/Solution-Seq.vtu\"	,					   \n"
<<"            Th			,					   \n"
<<"            [u,u1,0]			,					   \n";
 
if(spc==3)writePostProcessor     
<<"  savevtk(\"VTUs/Solution-Seq.vtu\"	,			  		   \n"
<<"            Th			,					   \n"
<<"            [u,u1,u2]		,					   \n"; 
  
writePostProcessor       
<<"             order=vtuorder		,					   \n"
<<"             dataname=\"U\"							   \n"
<<"         );				   			 		   \n"
<<(timelog ? "	timerend  (\"Post-Processing\",t0)\n" : " "  	    		    )
<<(timelog ? "	timerend  (\"Solver\",t1)\n" : " "  	         	  	    )	
<<"										   \n";

writePostProcessor
<<"     system(\"mv  VTUs/  VTUs_`date '+%b-%d-%Y-%H:%M'`\");  			   \n"
<<"     system(\"echo \\\"Elasticity\\t$(date '+%Y-%b-%d\\t%H:%M')\\t$HOSTNAME\\t\\t"<<spc<<"D\\t"
<<"\\tSeq.\\\" >>simulation-log.csv\");						   \n";

}  //-- [if loop terminator] Sequential ended --//

} //-- [ostream terminator]  varfmatsolve.edp closed --//

cout << " ............................ Done \n";