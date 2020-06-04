//=====================================================================================
// ------ Building the LinearFormBuilderAndSolver.edp file ------ 
//=====================================================================================

cout << " building LinearFormBuilderAndSolver.edp";

{ofstream  writesolver("LinearFormBuilderAndSolver.edp");

writesolver
<<"                                                                                                \n"
<<"/**************************Variational formulation******************************                \n"
<<"*                                                                              *                \n"
<<"* Note!!! This file is  generated  by  running  PSD PreProcessor  Do  not edit *                \n"
<<"*         in order to  control this  file please change flag arguments of  the *                \n"
<<"*         PSD_PreProcess, details of which are present in PSD_PreProcess or in *                \n"
<<"*         the README.MD file.                                                  *                \n"
<<"*                                                                              *                \n"
<<"*******************************************************************************/                \n"
<<"										   \n";

if(nonlinear){

if(Sequential)writesolver
<<"										   \n"
<<"//==============================================================================\n"
<<"// ------- L_o calculation -------						   \n"
<<"//==============================================================================\n"
<<"										   \n"
<<"{  										   \n"
<<"  fespace  Vh0( Th , P0)    ;						   \n"
<<"  Vh0 size1 = hTriangle     ;						   \n"
<<"  lo = size1[].min          ;						   \n"
<<"  lo = lo*lfac              ;						   \n"
<<"}										   \n";

/************************OLD METHOD*************************************************
if(pipegnu)if(!supercomp)writesolver
<<"										   \n"
<<"  matrix  And			;	// PostProcessing		   \n";
if(vectorial)writesolver
<<"  Vh def(fr) 			;	// Variables for force  	   \n"
<<"										   \n"
<<"  int[int]  ldof( 1 )			;				   \n"
<<"  ExtractDofBorderVectorial(2,Vh,ldof)	;				   \n"
<<"										   \n";

if(!vectorial)writesolver
<<"  Vh def2(fr)			;	// Variables for force  	   \n"
<<"										   \n"
<<"  int[int]  ldof( 1 )		;					   \n"
<<"  ExtractDofBorderP1(2,Vh,ldof)	;					   \n"
<<"										   \n";
/************************OLD METHOD*************************************************/ 

if(!Sequential)writesolver
<<"										   \n"
<<"//==============================================================================\n"
<<"// ------- L_o calculation in parallel -------				   \n"
<<"//==============================================================================\n"
<<"										   \n"
<<"{ real himlocal,himGlobal                                ;			   \n"
<<"  fespace Vh0(Th,P0)                                     ;			   \n"
<<"  Vh0 size1 = hTriangle                                  ;			   \n"
<<"  himlocal  = size1[].min                                ;			   \n"
<<"  mpiAllReduce(himlocal,himGlobal,mpiCommWorld,mpiMIN)   ;			   \n"
<<"  lo = himGlobal*lfac                                    ;			   \n"
<<"}										   \n";


if(Sequential)if(NonLinearMethod=="Picard"){writesolver
<<"										   \n"
<<"//==============================================================================\n"
<<"// ------- Traction loading loop -------					   \n"
<<"//==============================================================================\n"
<<"										   \n"
<<"while (tr <= maxtr){								   \n"
<<"										   \n"
<<"  cout <<  \"-------------------------------------------------------\\n\" 	   \n"
<<"       <<  \"Applied traction \" << tr << \"\\n\" << endl;			   \n"
<<"										   \n"
<<"  if (tr >= 5e-3)								   \n"
<<"    dtr = 1e-6;								   \n"
<<"										   \n"
<<"  //--------------------Assembly for linear----------------------//		   \n"
<<"										   \n"
<<(timelog ? "  timerbegin(\"RHS assembly for U\",t0)\n" : "" 	          	    )
<<"  b = elast(0,Vh);								   \n"
<<(timelog ? "  timerend  (\"RHS assembly for U\",t0)\n" : ""  	         	    )
<<"										   \n"
<<"  //-----------------------Nonlinear loop------------------------//		   \n"
<<"										   \n"
<<"  for(int iter=0; iter<100; iter++){					   	   \n"
<<"										   \n"
<<"    //----------------Assembly for bilinear----------------------//	 	   \n"
<<"										   \n"
<<(timelog ? "    timerbegin(\"matrix assembly for U\",t0)\n" : ""	       	    )
<<"    A = elast(Vh,Vh,solver=CG,sym=1);					   \n"
<<(timelog ? "    timerend  (\"matrix assembly for U\",t0)\n" : ""	            )
<<"										   \n"
<<"    //-------------Linear system solving phase-------------------//		   \n"
<<"										   \n"
<<(timelog ? "    timerbegin(\"solving U\",t0)\n"         : ""         	  	    )
<<"    set(A,solver=CG,sym=1);							   \n"
<<"    u[] = A^-1*b;						   		   \n"
<<(timelog ? "    timerend  (\"solving U\",t0)\n"         : ""         	  	    );

if(energydecomp)writesolver
<<"										   \n"
<<"    //---------------Energy decomposition phase-------------------//	  	   \n"
<<"										   \n"
<<(timelog ? "    timerbegin(\"energy decomposition\",t0)\n"         : ""           )
<<"    DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus)		   \n"
<<"    HistPlusP1=HistPlus; HistMinusP1=HistMinus;                                 \n"
<<(timelog ? "    timerend  (\"energy decomposition\",t0)\n"         : ""           );

writesolver
<<"										   \n"
<<"    //----------------Assembly for bilinear----------------------//	 	   \n"
<<"										   \n"
<<(timelog ? "    timerbegin(\"matrix assembly for PHI\",t0)\n" : ""           	    )
<<"    A1 = phase(Vh1,Vh1,solver=CG,sym=1);				  	   \n"
<<(timelog ? "    timerend  (\"matrix assembly for PHI\",t0)\n" : ""           	    )
<<"										   \n"
<<"    //--------------------Assembly for linear----------------------//	   \n"
<<"										   \n"
<<(timelog ? "    timerbegin(\"RHS assembly for PHI\",t0)\n" : "" 	            )
<<"    b1 = phase(0,Vh1);							   \n"
<<(timelog ? "    timerend  (\"RHS assembly for U\",t0)\n" : ""  	            )
<<"										   \n"
<<"    //-------------Linear system solving phase-------------------//		   \n"
<<"										   \n"
<<(timelog ? "    timerbegin(\"solving U\",t0)\n" : "" 	        	  	    )
<<"    set(A1,solver=CG,sym=1);							   \n"
<<"    phi[] = A1^-1*b1;						   	   \n"
<<(timelog ? "    timerend  (\"solving U\",t0)\n" : "" 	        	  	    )
<<"										   \n";

if(energydecomp)writesolver
<<"    //-------------Hybrid phase-field condition-----------------//		   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"Phase-field condition\",t0)\n" : ""          	    )
<<"    for(int i=0; i < Vh1.ndof; i++ )                                            \n"
  "        if(HistPlusP1[][i]<HistMinusP1[][i])phi[][i]=0.; 			   \n"
<<(timelog ? "    MPItimerend  (\"Phase-field condition\",t0)\n" : ""          	    )
<<"										   \n";

writesolver
<<"    //------------------Error calculation------------------------//		   \n"
<<"										   \n"
<<(timelog ? "    timerbegin(\"NL error checking\",t0)\n" : "" 	       	  	    )
<<"    uold[]    = uold[]-u[]                         ;				   \n"
<<"    phiold[]  = phiold[]-phi[]                     ;				   \n"
<<"    real err1 = sqrt( intN(Th,qforder=2) ( uold^2   )  )     ;		   \n"
<<"    real err2 = sqrt( intN(Th,qforder=2) ( phiold^2 )  )     ;		   \n"
<<(timelog ? "    timerend  (\"NL error checking\",t0)\n" : "" 	       	  	    )
<<"										   \n"
<<"    //--------------------Solution update-------------------------//		   \n"
<<"										   \n"
<<(timelog ? "    timerbegin(\"solution update\",t0)\n" : "" 	       	  	    )
<<"    phiold[] = phi[]  ;							   \n"
<<"    uold[]   = u[]    ;							   \n"
<<(timelog ? "    timerend  (\"solution update\",t0)\n" : "" 	       	  	    )
<<"										   \n"
<<"    //--------------- Convergence conditional---------------------//	  	   \n"
<<"										   \n"
<<"    if(err1 < 1e-2 && err2 < 1e-2){						   \n"
<<"										   \n"
<<"      //------------------Screen output norm----------------------//  	   \n"
<<"										   \n"
<<"      cout.scientific 							   \n"
<<"      << \"NL iteration number :  [ \"      << iter 	   	   		   \n"
<<"      << \" ]\\nL2 error in [u,phi] :  [ \"  << err1  			   \n"
<<"      << \" , \" <<  err2 << \" ]\"           << endl;		 	   \n"
<<"										   \n"
<<"      break;							   		   \n"
<<"    }									   \n"
<<"										   \n"
<<"  } 										   \n";

if(pipegnu){writesolver
<<"										   \n"
<<"  //-------------------Force calculation-----------------------//	   	   \n"
<<"										   \n"
<<(timelog ? "  timerbegin(\"force calculation\",t0)\n" : ""      	  	    )
<<"  real forcetot  = 0.;							   \n"
<<"  forcetot = intN1(Th,qforder=2,2)(lambda*divergence(u)+2.*mu*dy(u1));	   \n"
/************************OLD METHOD*************************************************   
<<"      And = elastNoDirc(Vh,Vh);						   \n"
<<"      fr[] = And*u[];							   \n"
<<"										   \n"
<<"      real forcetot  = 0. ; 							   \n"
<<"      for(int i = 0; i < ldof.n; ++i)					   \n"
<<"        forcetot = forcetot + fr1[][ldof[i]];				   \n"
/************************OLD METHOD*************************************************/
<<"  ofstream ff(\"force.data\",append);				  	   \n"
<<"  ff << tr << \"	\" << forcetot*1e-3 << endl; 			  	   \n";

if(!supercomp)writesolver
<<"  pgnuplot<<\"plot \\\"force.data\\\"u 1:2 w p pt 6 ps 2 t \\\"FEM\\\"\\n\";	   \n"
//<<"    <<\",\\\"ambati.data\\\"u 1:2 w p pt 4 ps 2  t \\\"Ref\\\"\"   	   \n"
<<"  flush(pgnuplot);					   	   	   	   \n";

writesolver
<<(timelog ? "  timerend  (\"force calculation\",t0)\n" : ""      	  	    );
}

if(plotAll)writesolver
<<"										   \n"
<<"  //-------Paraview plotting every nth iteration -----------//  	   	   \n"
<<"										   \n"
<<"  iterout++;									   \n"
<<"										   \n"
<<(timelog ? "  timerbegin(\"ParaView post-processing\",t0)\n" : ""                 )
<<"  if(int(iterout%10)==0){						   	   \n"
<<"    string   namevtu=\"VTUs/Solution_\"+iterout1+\".vtu\";		   	   \n"
<<"    savevtk(     namevtu            , 					   \n"
<<"                 Th                 ,				   	   \n"
<<(spc==2 ? "\t\t [u,u1,0]\t\t,\n" : "\t\t [u,u1,u2]\t\t,\n" 	   	    	    )
<<"                 phi                ,				   	   \n"
<<"                 order=vtuorder     ,				   	   \n"
<<"                 dataname=namedata				   	  	   \n"
<<"          );			       				   	      	   \n"
<<"										   \n"
<<"    iterout1++;								   \n"
<<"    }									   \n"
<<(timelog ? "  timerend  (\"ParaView post-processing\",t0)\n" : ""   	  	   );

if(debug)writesolver
<<"										   \n"
<<"  //-----------------Debug glut plotting----------------------//  	 	  \n"
<<"										   \n"
<<"  plot(phi,fill=1,value=1);				  			   \n";

writesolver
<<"										   \n"
<<"  //-----------------updating traction----------------//			   \n"
<<"										   \n"
<<"  tr += dtr;								  	   \n"
<<"}										   \n"
<<"										   \n"
<<(timelog ? "timerend  (\"solver\",t1)\n" : " "	   	        	    )
<<"										   \n"
<<"//-------------------------------THE END------------------------------//	   \n"; 
}  //-- [if loop terminator] Sequential ended --//



if(Sequential)if(NonLinearMethod=="Newton-Raphson"){writesolver
<<"										   \n"
<<"  real TractionTotal=tr;							   \n"
<<"										   \n"
<<"//==============================================================================\n"
<<"// ------- Traction loading loop -------					   \n"
<<"//==============================================================================\n"
<<"										   \n"
<<"while (TractionTotal <= maxtr){						   \n"
<<"										   \n"
<<"  cout <<  \"-------------------------------------------------------\\n\" 	   \n"
<<"       <<  \"Applied traction \" << TractionTotal << \"\\n\" << endl;	   \n"
<<"										   \n"
<<"  if (TractionTotal >= 5e-3){						   \n"
<<"    tr = 1e-6; dtr = 1e-6;}							   \n"
<<"  //-----------------------Nonlinear loop------------------------//		   \n"
<<"										   \n"
<<"  for(int iter=0; iter<100; iter++){					   	   \n"
<<"										   \n"
<<"  //--------------------Assembly for linear----------------------//		   \n"
<<"										   \n"
<<(timelog ? "  timerbegin(\"RHS assembly for U\",t0)\n" : "" 	          	    )
<<"    b = elast(0,Vh);								   \n"
<<(timelog ? "  timerend  (\"RHS assembly for U\",t0)\n" : ""  	         	    )
<<"										   \n"
<<"    //----------------Assembly for bilinear----------------------//	 	   \n"
<<"										   \n"
<<(timelog ? "    timerbegin(\"matrix assembly for U\",t0)\n" : ""	       	    )
<<"    A = elast(Vh,Vh,solver=CG,sym=1);					   \n"
<<(timelog ? "    timerend  (\"matrix assembly for U\",t0)\n" : ""	            )
<<"										   \n"
<<"    //-------------Linear system solving phase-------------------//		   \n"
<<"										   \n"
<<(timelog ? "    timerbegin(\"solving U\",t0)\n"         : ""         	  	    )
<<"    set(A,solver=CG,sym=1);							   \n"
<<"    du[] = A^-1*b;						   		   \n"
<<(timelog ? "    timerend  (\"solving U\",t0)\n"         : ""         	  	    )
<<"										   \n"
<<"    //--------------Update of displacement u---------------------//		   \n"
<<"										   \n"
<<(timelog ? "    timerbegin(\"Updating U\",t0)\n"         : ""           	    )
<<"    u[] += du[];								   \n"
<<(timelog ? "    timerend  (\"Updating U\",t0)\n"         : ""           	    )
<<"										   \n";

if(energydecomp)writesolver
<<"										   \n"
<<"    //---------------Energy decomposition phase-------------------//	  	   \n"
<<"										   \n"
<<(timelog ? "    timerbegin(\"energy decomposition\",t0)\n"         : ""           )
<<"    DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus)		   \n"
<<"    HistPlusP1=HistPlus; HistMinusP1=HistMinus;                                 \n"
<<(timelog ? "    timerend  (\"energy decomposition\",t0)\n"         : ""           );

writesolver
<<"										   \n"
<<"    //----------------Assembly for bilinear----------------------//	 	   \n"
<<"										   \n"
<<(timelog ? "    timerbegin(\"matrix assembly for PHI\",t0)\n" : ""           	    )
<<"    A1 = phase(Vh1,Vh1,solver=CG,sym=1);				  	   \n"
<<(timelog ? "    timerend  (\"matrix assembly for PHI\",t0)\n" : ""           	    )
<<"										   \n"
<<"    //--------------------Assembly for linear----------------------//	   \n"
<<"										   \n"
<<(timelog ? "    timerbegin(\"RHS assembly for PHI\",t0)\n" : "" 	            )
<<"    b1 = phase(0,Vh1);							   \n"
<<(timelog ? "    timerend  (\"RHS assembly for U\",t0)\n" : ""  	            )
<<"										   \n"
<<"    //-------------Linear system solving phase-------------------//		   \n"
<<"										   \n"
<<(timelog ? "    timerbegin(\"solving U\",t0)\n" : "" 	        	  	    )
<<"    set(A1,solver=CG,sym=1);							   \n"
<<"    dphi[] = A1^-1*b1;						   	   \n"
<<(timelog ? "    timerend  (\"solving U\",t0)\n" : "" 	        	  	    )
<<"										   \n"
<<"    //--------------Update of phase-field phi-------------------//		   \n"
<<"										   \n"
<<(timelog ? "    timerbegin(\"Updating U\",t0)\n"         : ""           	    )
<<"    phi[] += dphi[];								   \n"
<<(timelog ? "    timerend  (\"Updating U\",t0)\n"         : ""           	    )
<<"										   \n";

if(energydecomp)writesolver
<<"    //-------------Hybrid phase-field condition-----------------//		   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"Phase-field condition\",t0)\n" : ""          	    )
<<"    for(int i=0; i < Vh1.ndof; i++ )                                            \n"
  "        if(HistPlusP1[][i]<HistMinusP1[][i])phi[][i]=0.; 			   \n"
<<(timelog ? "    MPItimerend  (\"Phase-field condition\",t0)\n" : ""          	    )
<<"										   \n";

writesolver
<<"    //------------------Error calculation------------------------//		   \n"
<<"										   \n"
<<(timelog ? "    timerbegin(\"NL error checking\",t0)\n" : "" 	       	  	    )
<<"    real err1 = sqrt( intN(Th,qforder=2) ( du^2   )  )     ;		           \n"
<<"    real err2 = sqrt( intN(Th,qforder=2) ( dphi^2 )  )     ;		           \n"
<<(timelog ? "    timerend  (\"NL error checking\",t0)\n" : "" 	       	  	    )
<<"										   \n"
<<"    //--------------- Convergence conditional---------------------//	  	   \n"
<<"										   \n"
<<"    if(err1 < 1e-2 && err2 < 1e-2){						   \n"
<<"										   \n"
<<"      //------------------Screen output norm----------------------//  	   \n"
<<"										   \n"
<<"      cout.scientific 							   \n"
<<"      << \"NL iteration number :  [ \"      << iter 	   	   		   \n"
<<"      << \" ]\\nL2 error in [u,phi] :  [ \"  << err1  			   \n"
<<"      << \" , \" <<  err2 << \" ]\"           << endl;		 	   \n"
<<"										   \n"
<<"      break;							   		   \n"
<<"    }									   \n"
<<"										   \n"
<<"    TractionIn = 0;								   \n"
<<"  } 										   \n"
<<"										   \n"
<<"  //-----------------updating traction----------------//			   \n"
<<"										   \n"
<<"    TractionIn     = tr;		             				   \n"
<<"    TractionTotal += dtr;							   \n";

if(pipegnu){writesolver
<<"										   \n"
<<"  //-------------------Force calculation-----------------------//	   	   \n"
<<"										   \n"
<<(timelog ? "  timerbegin(\"force calculation\",t0)\n" : ""      	  	    )
<<"  real forcetot  = 0.;							   \n"
<<"  forcetot = intN1(Th,qforder=2,2)(lambda*divergence(u)+2.*mu*dy(u1));	   \n"
<<"  ofstream ff(\"force.data\",append);				  	   \n"
<<"  ff << TractionTotal << \"	\" << forcetot*1e-3 << endl; 		  	   \n";

if(!supercomp)writesolver
<<"  pgnuplot<<\"plot \\\"force.data\\\"u 1:2 w p pt 6 ps 2 t \\\"FEM\\\"\\n\";	   \n"
<<"  flush(pgnuplot);					   	   	   	   \n";

writesolver
<<(timelog ? "  timerend  (\"force calculation\",t0)\n" : ""      	  	    );
}

if(plotAll)writesolver
<<"										   \n"
<<"  //-------Paraview plotting every nth iteration -----------//  	   	   \n"
<<"										   \n"
<<"  iterout++;									   \n"
<<"										   \n"
<<(timelog ? "  timerbegin(\"ParaView post-processing\",t0)\n" : ""                 )
<<"  if(int(iterout%10)==0){						   	   \n"
<<"    string   namevtu=\"VTUs/Solution_\"+iterout1+\".vtu\";		   	   \n"
<<"    savevtk(     namevtu            , 					   \n"
<<"                 Th                 ,				   	   \n"
<<(spc==2 ? "\t\t [u,u1,0]\t\t,\n" : "\t\t [u,u1,u2]\t\t,\n" 	   	    	    )
<<"                 phi                ,				   	   \n"
<<"                 order=vtuorder     ,				   	   \n"
<<"                 dataname=namedata				   	  	   \n"
<<"          );			       				   	      	   \n"
<<"										   \n"
<<"    iterout1++;								   \n"
<<"    }									   \n"
<<(timelog ? "  timerend  (\"ParaView post-processing\",t0)\n" : ""   	  	   );

if(debug)writesolver
<<"										   \n"
<<"  //-----------------Debug glut plotting----------------------//  	 	  \n"
<<"										   \n"
<<"  plot(phi,fill=1,value=1);				  			   \n";

writesolver
<<"										   \n"
<<"}										   \n"
<<"										   \n"
<<(timelog ? "timerend  (\"solver\",t1)\n" : " "	   	        	    )
<<"										   \n"
<<"//-------------------------------THE END------------------------------//	   \n"; 
}  //-- [if loop terminator] Sequential ended --//

if(!Sequential)if(NonLinearMethod=="Picard"){writesolver
<<"										   \n"
<<"//==============================================================================\n"
<<"// -------  Traction loading loop  -------					   \n"
<<"//==============================================================================\n"
<<"										   \n"
<<"while (tr <= maxtr){								   \n"
<<"										   \n"
<<"  if(mpirank==0)								   \n"
<<"  cout.scientific<<\"-----------------------------------------------------\\n\" \n"
<<"  <<  \"Applied traction \" << tr << \"\\n\" << endl;	   		   \n"
<<"										   \n"
<<"  if (tr >= 5e-3)								   \n"
<<"    dtr = 1e-6;								   \n"
<<"										   \n"
<<"  //--------------------Assembly for linear----------------------//		   \n"
<<"										   \n"
<<(timelog ? "  MPItimerbegin(\"RHS assembly for U\",t0)\n" : ""       	            )
<<"  b = elast(0,Vh);							 	   \n"
<<(timelog ? "  MPItimerend  (\"RHS assembly for U\",t0)\n" : ""       	  	    )
<<"										   \n"
<<"  //-----------------------Nonlinear loop------------------------//		   \n"
<<"										   \n"
<<"  for(int iter=0; iter<100; iter++){					   	   \n"
<<"										   \n"
<<"    //----------------Assembly for bilinear----------------------//	 	   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"matrix assembly for U\",t0)\n" : ""         	    )
<<"    ALoc = elast(Vh,Vh,solver=CG,sym=1);				  	   \n"
<<(timelog ? "    MPItimerend  (\"matrix assembly for U\",t0)\n" : ""          	    )
<<"										   \n"
<<"    //-----------PETSc assembly for bilinear---------------------//		   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"PETSc assembly for U\",t0)\n" : ""           	    )
<<"    changeOperator(A, ALoc);				   	   		   \n"
<<"    set(A,sparams =\"  -ksp_type cg  \");				   	   \n"
<<(timelog ? "    MPItimerend  (\"PETSc assembly for U\",t0)\n" : ""   	  	    )
<<"										   \n"
<<"    //-------------Linear system solving phase-------------------//		   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"solving U\",t0)\n" : " "         	  	    )
<<"    u[] = A^-1*b;	                         				   \n"
<<(timelog ? "    MPItimerend  (\"solving U\",t0)\n" : " "           	  	    );

if(!vectorial){
if(energydecomp)writesolver
<<"										   \n"
<<"    //---------------Energy decomposition phase-------------------//	  	   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"energy decomposition\",t0)\n" : ""           	    )
<<"    DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus);		   \n"
<<"    HistPlusP1=HistPlus; HistMinusP1=HistMinus;                                 \n"
<<(timelog ? "    MPItimerend  (\"energy decomposition\",t0)\n" : ""   	  	    );

writesolver
<<"										   \n"
<<"    //----------------Assembly for bilinear----------------------//	 	   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"matrix assembly for PHI\",t0)\n" : ""        	    )
<<"    ALoc1 = phase(Vh1,Vh1,solver=CG,sym=1);			   		   \n"
<<(timelog ? "    MPItimerend  (\"matrix assembly PHI\",t0)\n" : ""    	  	    )
<<"										   \n"
<<"    //----------------Assembly for linear------------------------//	 	   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"RHS assembly for PHI\",t0)\n" : ""           	    )
<<"    b1 = phase(0,Vh1);				   			   \n"
<<(timelog ? "    MPItimerend  (\"RHS assembly for PHI\",t0)\n" : ""           	    )
<<"										   \n"
<<"    //-----------PETSc assembly for bilinear---------------------//		   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"PETSc assembly for PHI\",t0)\n" : ""         	    )
<<"    changeOperator(A1, ALoc1);					  	   \n"
<<"    set(A1,sparams =\"  -ksp_type cg  \");			   		   \n"
<<(timelog ? "    MPItimerend  (\"PETSc assembly for PHI\",t0)\n" : ""         	    )
<<"										   \n"
<<"    //-------------Linear system solving phase-------------------//		   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"solving PHI\",t0)\n" : ""    		       	    )
<<"    phi[] = A1^-1*b1;				  	   		   \n"
<<(timelog ? "    MPItimerend  (\"solving PHI\",t0)\n" : ""           	  	    )
<<"										   \n";

if(energydecomp)writesolver
<<"    //-------------Hybrid phase-field condition-----------------//		   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"Phase-field condition\",t0)\n" : ""          	    )
<<"    for(int i=0; i < Vh1.ndof; i++ )                                            \n"
  "        if(HistPlusP1[][i]<HistMinusP1[][i])phi[][i]=0.; 			   \n"
<<(timelog ? "    MPItimerend  (\"Phase-field condition\",t0)\n" : ""          	    )
<<"										   \n";

writesolver
<<"    //------------------Error calculation------------------------//		   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"NL error checking\",t0)\n" : "" 	       	    )
<<"    uold[]   = uold[]-u[]		;					   \n"
<<"    phiold[] = phiold[]-phi[]	; 					   \n"
<<"    real err1Gather,err2Gather;						   \n"
<<"    real err1Loc=sqrt( intN(Th,qforder=2) ( DPspc*(uold)^2   )  );		   \n"
<<"    real err2Loc=sqrt( intN(Th,qforder=2) ( DZspc*(phiold)^2 )  );		   \n"
<<"    mpiAllReduce(err1Loc,err1Gather,mpiCommWorld,mpiSUM);			   \n"
<<"    mpiAllReduce(err2Loc,err2Gather,mpiCommWorld,mpiSUM);			   \n"
<<(timelog ? "    MPItimerend (\"NL error checking\",t0)\n" : "" 	       	    )
<<"										   \n"
<<"    //--------------------Solution update-------------------------//		   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"solution update\",t0)\n" : "" 	       	    )
<<"    phiold[]=phi[];							   	   \n"
<<"    uold[]=u[];							   	   \n"
<<(timelog ? "    MPItimerend (\"solution update\",t0)\n" : "" 	   	    	    )
<<"										   \n"
<<"    //--------------- Convergence conditional---------------------//	  	   \n"
<<"										   \n"
<<"    if(err1Gather < 1e-2 && err2Gather < 1e-2){			   	   \n";
}

if(vectorial){writesolver
<<"										   \n"
<<"    //------------------Error calculation------------------------//		   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"NL error checking\",t0)\n" : "" 	       	    )
<<"    uold[]   = uold[]-u[]                                          ;		   \n"
<<"    real err1Gather                                                ;		   \n"
<<"    real err1Loc=sqrt( intN(Th,qforder=2) ( DPspc*(uold)^2 )  )    ;		   \n"
<<"    mpiAllReduce(err1Loc,err1Gather,mpiCommWorld,mpiSUM)           ;		   \n"
<<(timelog ? "    MPItimerend (\"NL error checking\",t0)\n" : "" 	       	    )
<<"										   \n"
<<"    //--------------------Solution update-------------------------//		   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"solution update\",t0)\n" : "" 	       	    )
<<"    uold[] = u[];							   	   \n"
<<(timelog ? "    MPItimerend (\"solution update\",t0)\n" : "" 	   	    	    );

if(energydecomp)writesolver
<<"										   \n"
<<"    //---------------Energy decomposition phase-------------------//	  	   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"energy decomposition\",t0)\n" : ""           	    )
<<"    DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus);		   \n"
<<"    HistPlusP1=HistPlus; HistMinusP1=HistMinus;                                 \n"
<<(timelog ? "    MPItimerend  (\"energy decomposition\",t0)\n" : ""   	  	    );

writesolver
<<"										   \n"
<<"    //--------------- Convergence conditional---------------------//	  	   \n"
<<"										   \n"
<<"    if(err1Gather < 1e-2){						   	   \n";

}  //-- [if loop terminator] vectorial ended --//


/************************OLD METHOD*************************************************
if(pipegnu){writesolver
<<"										   \n"
<<"      //-------------------Force calculation-----------------------//	   \n"
<<"										   \n"
<<"	And = elastNoDirc(Vh,Vh);						   \n"
<<"	changeOperator(A2, And);						   \n"
<<"	fr[] = And*u[];								   \n"
<<"										   \n"
<<"	fr[] .*= DP;								   \n"
<<"										   \n"
<<"	real forcetot  = 0.,forcetotGath  = 0. ;				   \n"
<<"		for(int i = 0; i < ldof.n; ++i)					   \n"
<<"		forcetot = forcetot + fr1[][ldof[i]];				   \n"
<<"										   \n"
/************************OLD METHOD*************************************************/

if(!vectorial)writesolver
<<"										   \n"
<<"      //------------------Screen output norm----------------------//  	   \n"
<<"										   \n"
<<"      if(mpirank==0)							      	   \n"
<<"      cout.scientific << \"NL iteration number :  [ \"  << iter 	   	   \n"
<<"      << \" ]\\nL2 error in [u,phi] :  [ \"    << err1Gather  	 	   \n"
<<"      << \" , \" <<  err2Gather << \" ]\"      << endl;	   		   \n"
<<"										   \n";

if(vectorial)writesolver
<<"										   \n"
<<"      //------------------Screen output norm----------------------//  	   \n"
<<"										   \n"
<<"      if(mpirank==0)							      	   \n"
<<"      cout.scientific << \"NL iteration number :  [ \" << iter    		   \n"
<<"      << \" ]\\nL2  error  in  [U]  :  [ \" << err1Gather << \" ]\" <<endl;	   \n";

writesolver
<<"										   \n"
<<"      break;									   \n"
<<"    }									   \n"
<<"  } 									  	   \n";


if(pipegnu){writesolver
<<"										   \n"
<<"  //-------------------Force calculation-----------------------//	   	   \n"
<<"										   \n"
<<(timelog ? "  MPItimerbegin(\"force calculation\",t0)\n" : ""           	    )
<<"  real forcetot  = 0., forcetotGath  = 0. ;				   	   \n"
<<"  forcetot=intN1(Th,qforder=2,2)(DPspc*(lambda*divergence(u)+2.*mu*dy(u1)));	   \n"
<<"  mpiAllReduce(forcetot,forcetotGath,mpiCommWorld,mpiSUM);		   	   \n"
<<"  if(mpirank==0){							   	   \n"
<<"  ofstream ff(\"force.data\",append);					   \n"
<<"  ff << tr << \"	\" << forcetotGath*1e-3 << endl;		   	   \n";

if(!supercomp)writesolver
<<"  pgnuplot<<\"plot \\\"force.data\\\" u 1:2 w lp pt 6 ps 2 t \\\"FEM\\\"\\n\";  \n"
//<<"      <<\",\\\"ambati.data\\\"u 1:2 w p pt 4 ps 2  t \\\"Ref\\\"\"   	   \n"
<<"  flush(pgnuplot);					   	   		   \n";

writesolver
<<"  }								   	 	   \n"
<<(timelog ? "  MPItimerend  (\"force calculation\",t0)\n" : ""           	    );

}  //-- [if loop terminator] !pipegnu ended --//

if(plotAll)if(!vectorial){writesolver
<<"										   \n"
<<"  //-------Paraview plotting every nth iteration -----------//  	   	   \n"
<<"										   \n"
<<"  iterout++;									   \n"
<<"										   \n"
<<(timelog ? "  MPItimerbegin(\"ParaView post-processing\",t0)\n" : ""              )
<<"  if(int(iterout%10)==0){							   \n";


writesolver    	
<<"    savevtk(  \"VTUs/Solution.vtu\"   ,	 				   \n"
<<"                 Th                 ,				   	   \n";

if(PostProcess!="u" & PostProcess!="phi")writesolver
<<(spc==2 ? "\t\t [u,u1,0]\t    ,\n" : "\t\t [u,u1,u2]\t    ,\n" 	   	    )
<<"                 phi                ,				   	   \n";


if(PostProcess=="u")writesolver
<<(spc==2 ? "\t\t [u,u1,0]\t    ,\n" : "\t\t [u,u1,u2]\t    ,\n" 	   	    );

if(PostProcess=="phi")writesolver
<<"                 phi                ,				   	   \n";

if(PostProcess=="uphi")writesolver
<<(spc==2 ? "\t\t [u,u1,0]\t    ,\n" : "\t\t [u,u1,u2]\t    ,\n" 	   	    )
<<"                 phi                ,				   	   \n";

writesolver
<<"                 order=vtuorder     ,				   	   \n"
<<"                 dataname=\"U  d\"    ,				   	   \n"
<<"                 append=true       					   	   \n"
<<"              );			       				   	   \n";

writesolver
<<"										   \n"
<<"    iterout1++;								   \n"
<<"  }									  	   \n"
<<(timelog ? "  MPItimerend  (\"ParaView post-processing\",t0)\n" : ""   	    );
}

if(plotAll)if(vectorial){writesolver
<<"										   \n"
<<"  //--------Paraview plotting every nth iteration ----------//  	   	   \n"
<<"										   \n"
<<"  iterout++;								   	   \n"
<<"										   \n"
<<(timelog ? "  MPItimerbegin(\"ParaView post-processing\",t0)\n" : ""              )
<<"										   \n"
<<"  if(int(iterout%10)==0){						 	   \n"
<<"										   \n"
<<"    fespace Vhplot(Th,P1); Vhplot phi=u2;              //interpolation for phi  \n";

writesolver   		
<<"    savevtk(  \"VTUs/Solution.vtu\"   , 					   \n"
<<"                 Th                 ,				   	   \n";

if(PostProcess!="u" & PostProcess!="phi")writesolver
<<(spc==2 ? "\t\t [u,u1,0]\t    ,\n" : "\t\t [u,u1,u2]\t    ,\n" 	   	    )
<<"                 phi                ,				   	   \n";


if(PostProcess=="u")writesolver
<<(spc==2 ? "\t\t [u,u1,0]\t    ,\n" : "\t\t [u,u1,u2]\t    ,\n" 	   	    );

if(PostProcess=="phi")writesolver
<<"                 phi                ,				   	   \n";

if(PostProcess=="uphi")writesolver
<<(spc==2 ? "\t\t [u,u1,0]\t    ,\n" : "\t\t [u,u1,u2]\t    ,\n" 	   	    )
<<"                 phi                ,				   	   \n";

writesolver
<<"                 order=vtuorder     ,				   	   \n"
<<"                 dataname=\"U  d\"    ,				   	   \n"
<<"                 append=true       					   	   \n"
<<"              );			       				   	   \n";


writesolver
<<"										   \n"
<<"    iterout1++;								   \n"
<<"  }										   \n"
<<(timelog ? "  MPItimerend  (\"ParaView post-processing\",t0)\n" : ""   	    );
}

if(debug)if(!vectorial)writesolver
<<"										   \n"
<<"  //-----------------Debug glut plotting----------------------//  	 	   \n"
<<"										   \n"
<<"  plotMPI(Th, phi, P1,  def, real, wait=0, cmm=\"Tr-\"+tr+\"\")	   	   \n";

if(debug)if(vectorial)writesolver
<<"										   \n"
<<"  //-----------------Debug glut plotting----------------------//  	  	   \n"
<<"										   \n"
<<"  plotMPI(Th, u"<<spc<<", P1,  def0, real, wait=0, cmm=\"Tr-\"+tr+\"\")	   \n";

writesolver
<<"										   \n"
<<"  //-----------------updating traction----------------//			   \n"
<<"										   \n"
<<"  tr += dtr;									   \n"
<<"}										   \n"
<<"										   \n"
<<(timelog ? "if(mpirank==0)\n" : " "	   	        	    		    )
<<(timelog ? "cout << \" all operations ended, they \";\n" : ""    		    )
<<(timelog ? "MPItimerend  (\"solver\",t1)\n" : " "	   	        	    )
<<"										   \n"
<<"//-------------------------------THE END------------------------------//	   \n"; 

}  //-- [if loop terminator] !Sequential ended --//
 
//}  //-- [if loop terminator] nonlinear ended --//

if(!Sequential)if(NonLinearMethod=="Newton-Raphson"){writesolver
<<"										   \n"
<<"real TractionTotal=tr;							   \n"
<<"										   \n"
<<"//==============================================================================\n"
<<"// -------  Traction loading loop  -------					   \n"
<<"//==============================================================================\n"
<<"										   \n"
<<"while (TractionTotal <= maxtr){						   \n"
<<"										   \n"
<<"  if(mpirank==0)								   \n"
<<"  cout.scientific<<\"-----------------------------------------------------\\n\" \n"
<<"  <<  \"Applied traction \" << TractionTotal << \"\\n\" << endl;	  	   \n"
<<"										   \n"
<<"  if (TractionTotal >= 5e-3){						   \n"
<<"    tr = 1e-6; dtr = 1e-6;}							   \n"
<<"										   \n"
<<"  //-----------------------Nonlinear loop------------------------//		   \n"
<<"										   \n"
<<"  for(int iter=0; iter<100; iter++){					   	   \n"
<<"										   \n"
<<"    //--------------------Assembly for linear----------------------//	   \n"
<<"										   \n"
<<(timelog ? "  MPItimerbegin(\"RHS assembly for U\",t0)\n" : ""       	            )
<<"    b = elast(0,Vh);							 	   \n"
<<(timelog ? "  MPItimerend  (\"RHS assembly for U\",t0)\n" : ""       	  	    )
<<"										   \n"
<<"    //----------------Assembly for bilinear----------------------//	 	   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"matrix assembly for U\",t0)\n" : ""         	    )
<<"    ALoc = elast(Vh,Vh,solver=CG,sym=1);				  	   \n"
<<(timelog ? "    MPItimerend  (\"matrix assembly for U\",t0)\n" : ""          	    )
<<"										   \n"
<<"    //-----------PETSc assembly for bilinear---------------------//		   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"PETSc assembly for U\",t0)\n" : ""           	    )
<<"    changeOperator(A, ALoc);				   	   		   \n"
<<"    set(A,sparams =\"  -ksp_type cg  \");				   	   \n"
<<(timelog ? "    MPItimerend  (\"PETSc assembly for U\",t0)\n" : ""   	  	    )
<<"										   \n"
<<"    //-------------Linear system solving phase-------------------//		   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"solving U\",t0)\n" : " "         	  	    )
<<"    du[] = A^-1*b;	                         				   \n"
<<(timelog ? "    MPItimerend  (\"solving U\",t0)\n" : " "           	  	    )
<<"										   \n"
<<"    //--------------Update of displacement u---------------------//		   \n"
<<"										   \n"
<<(timelog ? "    timerbegin(\"Updating U\",t0)\n"         : ""           	    )
<<"    u[] += du[];								   \n"
<<(timelog ? "    timerend  (\"Updating U\",t0)\n"         : ""           	    )
<<"										   \n";

if(!vectorial){
if(energydecomp)writesolver
<<"										   \n"
<<"    //---------------Energy decomposition phase-------------------//	  	   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"energy decomposition\",t0)\n" : ""           	    )
<<"    DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus);		   \n"
<<"    HistPlusP1=HistPlus; HistMinusP1=HistMinus;                                 \n"
<<(timelog ? "    MPItimerend  (\"energy decomposition\",t0)\n" : ""   	  	    );

writesolver
<<"										   \n"
<<"    //----------------Assembly for bilinear----------------------//	 	   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"matrix assembly for PHI\",t0)\n" : ""        	    )
<<"    ALoc1 = phase(Vh1,Vh1,solver=CG,sym=1);			   		   \n"
<<(timelog ? "    MPItimerend  (\"matrix assembly PHI\",t0)\n" : ""    	  	    )
<<"										   \n"
<<"    //----------------Assembly for linear------------------------//	 	   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"RHS assembly for PHI\",t0)\n" : ""           	    )
<<"    b1 = phase(0,Vh1);				   			   \n"
<<(timelog ? "    MPItimerend  (\"RHS assembly for PHI\",t0)\n" : ""           	    )
<<"										   \n"
<<"    //-----------PETSc assembly for bilinear---------------------//		   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"PETSc assembly for PHI\",t0)\n" : ""         	    )
<<"    changeOperator(A1, ALoc1);					  	   \n"
<<"    set(A1,sparams =\"  -ksp_type cg  \");			   		   \n"
<<(timelog ? "    MPItimerend  (\"PETSc assembly for PHI\",t0)\n" : ""         	    )
<<"										   \n"
<<"    //-------------Linear system solving phase-------------------//		   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"solving PHI\",t0)\n" : ""    		       	    )
<<"    dphi[] = A1^-1*b1;				  	   		   \n"
<<(timelog ? "    MPItimerend  (\"solving PHI\",t0)\n" : ""           	  	    )
<<"										   \n"
<<"    //--------------Update of phase-field phi-------------------//		   \n"
<<"										   \n"
<<(timelog ? "    timerbegin(\"Updating U\",t0)\n"         : ""           	    )
<<"    phi[] += dphi[];								   \n"
<<(timelog ? "    timerend  (\"Updating U\",t0)\n"         : ""           	    )
<<"										   \n";

if(energydecomp)writesolver
<<"    //-------------Hybrid phase-field condition-----------------//		   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"Phase-field condition\",t0)\n" : ""          	    )
<<"    for(int i=0; i < Vh1.ndof; i++ )                                            \n"
  "        if(HistPlusP1[][i]<HistMinusP1[][i])phi[][i]=0.; 			   \n"
<<(timelog ? "    MPItimerend  (\"Phase-field condition\",t0)\n" : ""          	    )
<<"										   \n";

writesolver
<<"    //------------------Error calculation------------------------//		   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"NL error checking\",t0)\n" : "" 	       	    )
<<"    real err1Gather,err2Gather;						   \n"
<<"    real err1Loc=sqrt( intN(Th,qforder=2) ( DPspc*(du)^2   )  );		   \n"
<<"    real err2Loc=sqrt( intN(Th,qforder=2) ( DZspc*(dphi)^2 )  );		   \n"
<<"    mpiAllReduce(err1Loc,err1Gather,mpiCommWorld,mpiSUM);			   \n"
<<"    mpiAllReduce(err2Loc,err2Gather,mpiCommWorld,mpiSUM);			   \n"
<<(timelog ? "    MPItimerend (\"NL error checking\",t0)\n" : "" 	       	    )
<<"										   \n"
<<"    //--------------- Convergence conditional---------------------//	  	   \n"
<<"										   \n"
<<"    if(err1Gather < 1e-2 && err2Gather < 1e-2){			   	   \n";
}

if(vectorial){writesolver
<<"										   \n"
<<"    //------------------Error calculation------------------------//		   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"NL error checking\",t0)\n" : "" 	       	    )
<<"    uold[]   = uold[]-u[]                                          ;		   \n"
<<"    real err1Gather                                                ;		   \n"
<<"    real err1Loc=sqrt( intN(Th,qforder=2) ( DPspc*(uold)^2 )  )    ;		   \n"
<<"    mpiAllReduce(err1Loc,err1Gather,mpiCommWorld,mpiSUM)           ;		   \n"
<<(timelog ? "    MPItimerend (\"NL error checking\",t0)\n" : "" 	       	    )
<<"										   \n"
<<"    //--------------------Solution update-------------------------//		   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"solution update\",t0)\n" : "" 	       	    )
<<"    uold[] = u[];							   	   \n"
<<(timelog ? "    MPItimerend (\"solution update\",t0)\n" : "" 	   	    	    );

if(energydecomp)writesolver
<<"										   \n"
<<"    //---------------Energy decomposition phase-------------------//	  	   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"energy decomposition\",t0)\n" : ""           	    )
<<"    DecomposeElasticEnergy(PsiPlus,PsiMinus,HistPlus,HistMinus);		   \n"
<<"    HistPlusP1=HistPlus; HistMinusP1=HistMinus;                                 \n"
<<(timelog ? "    MPItimerend  (\"energy decomposition\",t0)\n" : ""   	  	    );

writesolver
<<"										   \n"
<<"    //--------------- Convergence conditional---------------------//	  	   \n"
<<"										   \n"
<<"    if(err1Gather < 1e-2){						   	   \n";

}  //-- [if loop terminator] vectorial ended --//

if(!vectorial)writesolver
<<"										   \n"
<<"      //------------------Screen output norm----------------------//  	   \n"
<<"										   \n"
<<"      if(mpirank==0)							      	   \n"
<<"      cout.scientific << \"NL iteration number :  [ \"  << iter 	   	   \n"
<<"      << \" ]\\nL2 error in [u,phi] :  [ \"    << err1Gather  	 	   \n"
<<"      << \" , \" <<  err2Gather << \" ]\"      << endl;	   		   \n"
<<"										   \n";

if(vectorial)writesolver
<<"										   \n"
<<"      //------------------Screen output norm----------------------//  	   \n"
<<"										   \n"
<<"      if(mpirank==0)							      	   \n"
<<"      cout.scientific << \"NL iteration number :  [ \" << iter    		   \n"
<<"      << \" ]\\nL2  error  in  [U]  :  [ \" << err1Gather << \" ]\" <<endl;	   \n";

writesolver
<<"										   \n"
<<"      break;									   \n"
<<"    }									   \n"
<<"										   \n"
<<"    TractionIn = 0;								   \n"
<<"  } 										   \n"
<<"										   \n"
<<"  //-----------------updating traction----------------//			   \n"
<<"										   \n"
<<"    TractionIn     = tr;		             				   \n"
<<"    TractionTotal += dtr;							   \n";


if(pipegnu){writesolver
<<"										   \n"
<<"  //-------------------Force calculation-----------------------//	   	   \n"
<<"										   \n"
<<(timelog ? "  MPItimerbegin(\"force calculation\",t0)\n" : ""           	    )
<<"  real forcetot  = 0., forcetotGath  = 0. ;				   	   \n"
<<"  forcetot=intN1(Th,qforder=2,2)(DPspc*(lambda*divergence(u)+2.*mu*dy(u1)));	   \n"
<<"  mpiAllReduce(forcetot,forcetotGath,mpiCommWorld,mpiSUM);		   	   \n"
<<"  if(mpirank==0){							   	   \n"
<<"  ofstream ff(\"force.data\",append);					   \n"
<<"  ff << TractionTotal << \"	\" << forcetotGath*1e-3 << endl;	  	   \n";

if(!supercomp)writesolver
<<"  pgnuplot<<\"plot \\\"force.data\\\" u 1:2 w lp pt 6 ps 2 t \\\"FEM\\\"\\n\";  \n"
<<"  flush(pgnuplot);					   	   		   \n";

writesolver
<<"  }								   	 	   \n"
<<(timelog ? "  MPItimerend  (\"force calculation\",t0)\n" : ""           	    );

}  //-- [if loop terminator] !pipegnu ended --//

if(plotAll)if(!vectorial){writesolver
<<"										   \n"
<<"  //-------Paraview plotting every nth iteration -----------//  	   	   \n"
<<"										   \n"
<<"  iterout++;									   \n"
<<"										   \n"
<<(timelog ? "  MPItimerbegin(\"ParaView post-processing\",t0)\n" : ""              )
<<"  if(int(iterout%10)==0){							   \n";


writesolver    	
<<"    savevtk(  \"VTUs/Solution.vtu\"   ,	 				   \n"
<<"                 Th                 ,				   	   \n";

if(PostProcess!="u" & PostProcess!="phi")writesolver
<<(spc==2 ? "\t\t [u,u1,0]\t    ,\n" : "\t\t [u,u1,u2]\t    ,\n" 	   	    )
<<"                 phi                ,				   	   \n";


if(PostProcess=="u")writesolver
<<(spc==2 ? "\t\t [u,u1,0]\t    ,\n" : "\t\t [u,u1,u2]\t    ,\n" 	   	    );

if(PostProcess=="phi")writesolver
<<"                 phi                ,				   	   \n";

if(PostProcess=="uphi")writesolver
<<(spc==2 ? "\t\t [u,u1,0]\t    ,\n" : "\t\t [u,u1,u2]\t    ,\n" 	   	    )
<<"                 phi                ,				   	   \n";

writesolver
<<"                 order=vtuorder     ,				   	   \n"
<<"                 dataname=\"U  d\"    ,				   	   \n"
<<"                 append=true       					   	   \n"
<<"              );			       				   	   \n";

writesolver
<<"										   \n"
<<"    iterout1++;								   \n"
<<"  }									  	   \n"
<<(timelog ? "  MPItimerend  (\"ParaView post-processing\",t0)\n" : ""   	    );
}

if(plotAll)if(vectorial){writesolver
<<"										   \n"
<<"  //--------Paraview plotting every nth iteration ----------//  	   	   \n"
<<"										   \n"
<<"  iterout++;								   	   \n"
<<"										   \n"
<<(timelog ? "  MPItimerbegin(\"ParaView post-processing\",t0)\n" : ""              )
<<"										   \n"
<<"  if(int(iterout%10)==0){						 	   \n"
<<"										   \n"
<<"    fespace Vhplot(Th,P1); Vhplot phi=u2;              //interpolation for phi  \n";

writesolver   		
<<"    savevtk(  \"VTUs/Solution.vtu\"   , 					   \n"
<<"                 Th                 ,				   	   \n";

if(PostProcess!="u" & PostProcess!="phi")writesolver
<<(spc==2 ? "\t\t [u,u1,0]\t    ,\n" : "\t\t [u,u1,u2]\t    ,\n" 	   	    )
<<"                 phi                ,				   	   \n";


if(PostProcess=="u")writesolver
<<(spc==2 ? "\t\t [u,u1,0]\t    ,\n" : "\t\t [u,u1,u2]\t    ,\n" 	   	    );

if(PostProcess=="phi")writesolver
<<"                 phi                ,				   	   \n";

if(PostProcess=="uphi")writesolver
<<(spc==2 ? "\t\t [u,u1,0]\t    ,\n" : "\t\t [u,u1,u2]\t    ,\n" 	   	    )
<<"                 phi                ,				   	   \n";

writesolver
<<"                 order=vtuorder     ,				   	   \n"
<<"                 dataname=\"U  d\"    ,				   	   \n"
<<"                 append=true       					   	   \n"
<<"              );			       				   	   \n";


writesolver
<<"										   \n"
<<"    iterout1++;								   \n"
<<"  }										   \n"
<<(timelog ? "  MPItimerend  (\"ParaView post-processing\",t0)\n" : ""   	    );
}

if(debug)if(!vectorial)writesolver
<<"										   \n"
<<"  //-----------------Debug glut plotting----------------------//  	 	   \n"
<<"										   \n"
<<"  plotMPI(Th, phi, P1,  def, real, wait=0, cmm=\"Tr-\"+tr+\"\")	   	   \n";

if(debug)if(vectorial)writesolver
<<"										   \n"
<<"  //-----------------Debug glut plotting----------------------//  	  	   \n"
<<"										   \n"
<<"  plotMPI(Th, u"<<spc<<", P1,  def0, real, wait=0, cmm=\"Tr-\"+tr+\"\")	   \n";

writesolver
<<"										   \n"
<<"}										   \n"
<<"										   \n"
<<(timelog ? "if(mpirank==0)\n" : " "	   	        	    		    )
<<(timelog ? "cout << \" all operations ended, they \";\n" : ""    		    )
<<(timelog ? "MPItimerend  (\"solver\",t1)\n" : " "	   	        	    )
<<"										   \n"
<<"//-------------------------------THE END------------------------------//	   \n"; 

}  //-- [if loop terminator] !Sequential ended --//
 
}  //-- [if loop terminator] nonlinear ended --//

if(!nonlinear)if(!quasistatic){

if(!Sequential)if(!dynamic)if(!soildynamics){writesolver      
<<"										   \n"	
<<"//==============================================================================\n"
<<"//  ------- Local Au=b assembly and solving -------				   \n"
<<"//==============================================================================\n"	
<<"										   \n"
<<"//--------------Assembly for bilinear--------------//			   \n"
<<"										   \n"
<<(timelog ? "	MPItimerbegin(\"matrix Assembly\",t0)\n" : ""           	    )
<<"  matrix	ALoc = elast(Vh,Vh,solver=CG,sym=1);				   \n"
<<(timelog ? "	MPItimerend  (\"matrix Assembly\",t0)\n" : ""       	    	    )
<<"										   \n"
<<"//---------------Assembly for linear---------------//			   \n"
<<"										   \n"
<<(timelog ? "	MPItimerbegin(\"RHS assembly\",t0)\n" : ""          	 	    )
<<"  real[int]    b = elast(0,Vh);						   \n"
<<(timelog ? "	MPItimerend  (\"RHS assembly\",t0)\n" : ""       	    	    );

if(dirichletpointconditions>=1)writesolver
<<"										   \n"
<<"//---------Additional assembly for A & b----------//				   \n"
<<"										   \n"
<<(timelog ? "	MPItimerbegin(\"point Dirichlet assembly\",t0)\n" : ""  	    )
<<"  Pointbc(Dpointlab,Vh,ALoc,b,PnV);						   \n"
<<(timelog ? "	MPItimerend(\"point Dirichlet assembly\",t0)\n" : ""        	    );

writesolver
<<"										   \n"
<<" //------------Memory optimization-----------------//			   \n";

if(dirichletpointconditions>=1)writesolver
<<"										   \n"
<<"  Dpointlab.resize(0); PnV.resize(0);					   \n";

if(dirichletbc)writesolver
<<"										   \n"
<<"  Dlabel.resize(0); Dvalue.resize(0);					   \n";

if(tractionbc)writesolver
<<"										   \n"
<<"  Tlabel.resize(0);								   \n";
   
writesolver
<<"										   \n"
<<"//---------------PETSc Assembly---------------------//			   \n"
<<"										   \n"
<<(timelog ? "	MPItimerbegin(\"PETSc assembly\",t0)\n" : ""  	    		    )
<<"  Mat A (ALoc, restrictionIntersectionP, DP, bs = "<<spc<<");		   \n"
<<(timelog ? "	MPItimerend(\"PETSc assembly\",t0)\n" : ""  	    		    )
<<"										   \n"
<<"//---------------PETSc solving---------------------//			   \n"
<<"										   \n"
<<(timelog ? "	MPItimerbegin(\"PETSc solving\",t0)\n" : ""  	    		   )
<<"  set(A,sparams =\" -ksp_type cg \");					   \n"
<<"  u[] = A^-1*b;                     						   \n"
<<(timelog ? "	MPItimerend(\"PETSc solving\",t0)\n" : ""  	    		   );


if(debug)writesolver
<<"										   \n"
<<"//-------------Debug glut plotting------------------//  		  	   \n"
<<"										   \n"
<<"  macro viz(i)i//								   \n"
<<"  plotMPI(Th, u, P1,  viz, real, wait=0, cmm=\"displacement\")	   	   \n";

}  //-- [if loop terminator] !Sequential ended --//

if(Sequential)if(!dynamic)if(!soildynamics){writesolver    
<<"										   \n"	
<<"//==============================================================================\n"
<<"//  ------- Local Au=b assembly and solving -------				   \n"
<<"//==============================================================================\n"	
<<"										   \n"
<<"//--------------Assembly for bilinear--------------//			   \n"
<<"										   \n"
<<(timelog ? "	timerbegin(\"matrix assembly\",t0)\n" : ""  	    		   )
<<"  matrix A = elast(Vh,Vh,solver=CG,sym=1);					   \n"
<<(timelog ? "	timerend  (\"matrix assembly\",t0)\n" : ""  	    		   )
<<"										   \n"
<<"//---------------Assembly for linear---------------//			   \n"
<<"										   \n"
<<(timelog ? "	timerbegin(\"RHS assembly\",t0)\n" : ""  	    		   )
<<"  real[int]    b = elast(0,Vh);						   \n"
<<(timelog ? "	timerend  (\"RHS assembly\",t0)\n" : ""  	    		   )
<<"										   \n"
<<"  //-----------------Solving du=A^-1*b--------------//			   \n"
<<"										   \n"
<<(timelog ? "	timerbegin(\"solving U\",t0)\n" : ""  	    		   	   )
<<"  set(A,solver=CG,sym=1);					   		   \n"
<<"  u[] = A^-1*b;								   \n"
<<(timelog ? "	timerend  (\"solving U\",t0)\n" : ""  	   	 		   );


if(debug)writesolver
<<"										   \n"
<<"  //--------------debug glut plotting---------------//			   \n"
<<"										   \n"
<<"  plot (u, wait=1, fill=1, value=1, cmm= \"solution\");		   	   \n";


}  //-- [if loop terminator] Sequential Not Dynamic ended --//


if(Sequential)if(dynamic || soildynamics){writesolver    
<<"										   \n"
<<"//==============================================================================\n"
<<"//  ------- Dynamic loop for linear assembly and solving -------		   \n"
<<"//==============================================================================\n"	
<<"										   \n"
<<"while (t <= tmax){								   \n"
<<"										   \n"
<<"  cout.scientific<<\"-----------------------------------------------------\\n\" \n"
<<"  << \"Time iteration at t :\" << t << \" (s)\\n \"<< endl;	   		   \n"
<<"										   \n"
<<"  //--------------tt update for loading--------------//			   \n"
<<"										   \n";

if(TimeDiscretization=="generalized-alpha" || TimeDiscretization=="hht-alpha")
writesolver
<<"  tt  = t-real(alpf*dt);                            				   \n";

if(TimeDiscretization=="newmark-beta" || TimeDiscretization=="central-difference")
writesolver
<<"  tt  = t-dt;	                            				   \n";

writesolver
<<"										   \n"
<<"  //-----------------Assembly for A-----------------//			   \n"
<<"										   \n"
<<(timelog ? "  timerbegin(\"matrix assembly\",t0)\n" : ""  	    		   )
<<"  A = elastodynamics(Vh,Vh,solver=CG,sym=1);		 		           \n"
<<(timelog ? "  timerend  (\"matrix assembly\",t0)\n" : ""  	    		   )
<<"										   \n"
<<"  //-----------------Assembly for b-----------------//			   \n"
<<"										   \n"
<<(timelog ? "  timerbegin(\"RHS assembly\",t0)\n" : ""  	    		   )
<<"  b = elastodynamics(0,Vh);			    			           \n"
<<(timelog ? "  timerend  (\"RHS assembly\",t0)\n" : ""  	    		   )
<<"										   \n"
<<"  //-----------------Solving du=A^-1*b--------------//			   \n"
<<"										   \n"
<<(timelog ? "  timerbegin(\"solving U\",t0)\n" : ""  	    		   	   )
<<"  set(A,solver=CG,sym=1);                           				   \n"
<<"  du[] = A^-1*b;                                   				   \n"
<<(timelog ? "  timerend  (\"solving U\",t0)\n" : ""  	   	 		   )
<<"										   \n";

if(debug)if(spc==2)writesolver
<<"										   \n"
<<"  //-----------------Move mesh plotting------------//			   \n"
<<"										   \n"
<<"  meshN ThMoved = movemesh(Th, [x + du, y + du1])  ; 			   \n"
<<"  plot (ThMoved,wait=0, cmm= \"t = \"+t+\" (s)\")  ;				   \n";

if(debug)if(spc==3)writesolver
<<"										   \n"
<<"  //-----------------Move mesh plotting------------//			   \n"
<<"										   \n"
<<"  meshN ThMoved = movemesh3(Th, transfo =[x + du, y + du1, z + du2]) ; 	   \n"
<<"  plot (ThMoved,wait=0, cmm= \"t = \"+t+\" (s)\")  ;			   	   \n";

writesolver
<<"										   \n"
<<"  //-----------------updating variables------------//			   \n"
<<"										   \n"
<<(timelog ? "  timerbegin(\"updating variables\",t0)\n" : ""  	    	   	   )
<<(useGFP  ? "  GFPUpdateDynamic(du[],uold[],vold[],aold[],beta,gamma,dt);\n" : "" )
<<(!useGFP ? "  updateVariables(du,uold,vold,aold,beta,gamma,dt)\n" : "" 	   )
<<(timelog ? "  timerend  (\"updating variables\",t0)\n" : ""  	   		   );

if(plotAll)if(spc==2){writesolver
<<"										   \n"
<<"  //-----------------Paraview plotting-------------//			   \n"
<<"										   \n"
<<(timelog ? "  timerbegin(\"ParaView plotting\",t0)\n" : ""	  	       	   )
<<"  string   namevtu=\"VTUs/Solution\"+iterout+\".vtu\";  		           \n"
<<"  savevtk  (  namevtu               ,					   \n"
<<"              Th                    ,					   \n";

if(PostProcess!="v" & PostProcess!="a" & PostProcess!="uva")writesolver
<<"              [uold,uold1,0]        ,					   \n";
if(PostProcess=="v")writesolver
<<"              [vold,vold1,0]        ,					   \n";
if(PostProcess=="a")writesolver 
<<"              [aold,aold1,0]        ,					   \n";
if(PostProcess=="uva")writesolver
<<"              [uold,uold1,0]        ,					   \n"
<<"              [vold,vold1,0]        ,					   \n"
<<"              [aold,aold1,0]        ,					   \n";

writesolver
<<"              order=vtuorder        ,					   \n"
<<"              dataname=namedata 					    	   \n"
<<"           );  								   \n"
<<(timelog ? "  timerend  (\"ParaView plotting\",t0)\n" : ""  	   		   );
}

if(plotTime){writesolver
<<"										   \n"
<<"  //-----------------Paraview plotting-------------//			   \n"
<<"										   \n"
<<(timelog ? "  MPItimerbegin(\"ParaView plotting\",t0)\n" : ""	  	       	   )
<<"  exportTimeStep( namevtu,   			  		           \n"
<<"                  Th                    ,					   \n";

if(PostProcess!="v" & PostProcess!="a" & PostProcess!="uva")writesolver
<<(spc==2 ? "\t\t [uold,uold1,0]\t   ,\n" : "\t\t [uold,uold1,uold2]\t   ,\n" 	   );

if(PostProcess=="v")writesolver
<<(spc==2 ? "\t\t [vold,vold1,0]\t   ,\n" : "\t\t [vold,vold1,vold2]\t   ,\n" 	   );

if(PostProcess=="a")writesolver
<<(spc==2 ? "\t\t [aold,aold1,0]\t   ,\n" : "\t\t [aold,aold1,aold2]\t   ,\n" 	   );

if(PostProcess=="uva")writesolver
<<(spc==2 ? "\t\t [uold,uold1,0]\t   ,\n" : "\t\t [uold,uold1,uold2]\t   ,\n" 	   )
<<(spc==2 ? "\t\t [vold,vold1,0]\t   ,\n" : "\t\t [vold,vold1,vold2]\t   ,\n" 	   )
<<(spc==2 ? "\t\t [aold,aold1,0]\t   ,\n" : "\t\t [aold,aold1,aold2]\t   ,\n" 	   );

writesolver
<<"                  vtuorder              ,					   \n"
<<"                  iterout               ,					   \n"
<<"                  t                     ,					   \n"
<<"                  namedata              				    	   \n"
<<"           );  								   \n"
<<(timelog ? "  timerend  (\"ParaView plotting\",t0)\n" : ""  	   		   );
}


if(plotAll)if(spc==3){writesolver
<<"										   \n"
<<"  //-----------------Paraview plotting-------------//			   \n"
<<"										   \n"
<<(timelog ? "  timerbegin(\"ParaView plotting\",t0)\n" : ""	  	       	   )
<<"  string   namevtu=\"VTUs/Solution\"+iterout+\".vtu\";  		           \n"
<<"  savevtk  (  namevtu               ,					   \n"
<<"              Th                    ,					   \n";

if(PostProcess!="v" & PostProcess!="a" & PostProcess!="uva")writesolver
<<"              [uold,uold1,uold2]    ,					   \n";
if(PostProcess=="v")writesolver
<<"              [vold,vold1,vold2]    ,					   \n";
if(PostProcess=="a")writesolver 
<<"              [aold,aold1,aold2]    ,					   \n";
if(PostProcess=="uva")writesolver
<<"              [uold,uold1,uold2]    ,					   \n"
<<"              [vold,vold1,vold2]    ,					   \n"
<<"              [aold,aold1,aold2]    ,					   \n";

writesolver
<<"              order=vtuorder        ,					   \n"
<<"              dataname=namedata 					    	   \n"
<<"           );  								   \n"
<<(timelog ? "  timerend  (\"ParaView plotting\",t0)\n" : ""  	   		   );
}


if(pipegnu)if(!soildynamics){writesolver
<<"										   \n"
<<"  //---------------Energy calculations-------------//			   \n"
<<"										   \n"
<<(timelog ? "  timerbegin(\"Energy calculations\",t0)\n" : ""     		   )
<<"  Ek =intN(Th,qforder=2)(0.5*(vold*vold+vold1*vold1));			   \n"
<<"  El =intN(Th,qforder=2)(0.5*(lambda*divergence(uold)*divergence(uold) 	   \n"
<<"                         + 2. * mu * epsilon(uold)'*epsilon(uold)) );	   \n"
<<"  Ec += dt*intN(Th,qforder=2)(						   \n"
<<"                           (etam*rho) *def(vold)'*def(vold)			   \n"
<<"                         + (etak*lambda)*(divergence(vold)*divergence(vold))	   \n"
<<"                         + (etak* 2.*mu)*(epsilon(vold)'*epsilon(vold)) );	   \n"
<<"										   \n"
<<"  //----------Appending energies to a file----------//			   \n"
<<"										   \n"
<<"  ofstream ff(\"energies.data\",append);					   \n"
<<"  ff<< t << \"  \" << Ek << \"  \"<< El << \"  \" << Ec <<endl;		   \n";

if(!supercomp)writesolver
<<"										   \n"
<<"  //-----------------Gnuplot pipeping-------------//				   \n"
<<"										   \n"
<<"  pgnuplot <<\"plot\" 	   						   \n"
<<"  <<\"\\\"energies.data\\\"\" 	   				           \n"
<<"  <<\"u ($1):($2) w lp lw 2 pt 7 ps 2 t \\\"K.E\\\",\" 			   \n"
<<"  <<\"\\\"energies.data\\\"\" 	   	   				   \n"
<<"  <<\"u ($1):($3) w lp lw 2  pt 7 ps 2 t \\\"E.E\\\",\"			   \n"
<<"  <<\"\\\"energies.data\\\"\" 	   	   				   \n"
<<"  <<\"u ($1):($4) w lp lw 2 pt 7 ps 2 t \\\"D.E\\\",\" 			   \n"
<<"  <<\"\\\"energies.data\\\"		\" 	   	   			   \n"
<<"  <<\"u ($1):($3+$2+$4) w lp lw 2 pt 7 ps 2 t \\\"T.E\\\" \"   		   \n"
<<"  <<\"\\n\"; 	   	  						   \n" 
<<"  flush(pgnuplot);					   	  	 	   \n";

writesolver
<<"										   \n"
<<(timelog ? "  timerend(\"Energy calculations\",t0)\n" : ""     		   );

}  //-- [if loop terminator]  pipegnu ended --//

writesolver
<<"										   \n"
<<"  //-----------------updating time----------------//				   \n"
<<"										   \n"
<<"  t += dt; 									   \n";

if(plotAll || plotTime)writesolver
<<"										   \n"
<<"  //-----------updating iteration count-----------//				   \n"
<<"										   \n"
<<"  iterout++;									   \n";

writesolver
<<"										   \n"
<<"}										   \n"
<<"										   \n"
<<(plotTime ? "exportEnd(namevtu)\n" : " "	   	 		            )
<<"										   \n"
<<(timelog ? "cout << \" all operations ended, they \";\n" : ""    		    )
<<(timelog ? "timerend  (\"solver\",t1)\n" : " "	   	        	    )
<<"										   \n"
<<"//-------------------------------THE END------------------------------//	   \n"; 

}  //-- [if loop terminator] Sequential Dynamic ended --//


if(!Sequential)if(dynamic || soildynamics){writesolver    
<<"										   \n"
<<"//==============================================================================\n"
<<"//  ------- Dynamic loop for linear assembly and solving -------		   \n"
<<"//==============================================================================\n"	
<<"										   \n"
<<"while (t <= tmax){								   \n"
<<"										   \n"
<<"  if(mpirank==0)								   \n"
<<"  cout.scientific<<\"-----------------------------------------------------\\n\" \n"
<<"  << \"Time iteration at t :\" << t << \" (s)\\n \"<< endl;	   		   \n"
<<"										   \n"
<<"  //--------------tt update for loading--------------//			   \n"
<<"										   \n";

if(TimeDiscretization=="generalized-alpha" || TimeDiscretization=="hht-alpha")
writesolver
<<"  tt  = t-real(alpf*dt);                            				   \n";

if(TimeDiscretization=="newmark-beta" || TimeDiscretization=="central-difference")
writesolver
<<"  tt  = t-dt;	                            				   \n";

writesolver
<<"										   \n"
<<"  //-----------------Assembly for A-----------------//			   \n"
<<"										   \n"
<<(timelog ? "  MPItimerbegin(\"matrix assembly\",t0)\n" : ""  		    	   )
<<"  ALoc = elastodynamics(Vh,Vh,solver=CG,sym=1);   	        	           \n"
<<(timelog ? "  MPItimerend  (\"matrix assembly\",t0)\n" : ""  	  	  	   )
<<"										   \n"
<<(timelog ? "  MPItimerbegin(\"PETSc assembly\",t0)\n"  : ""  	    		   )
<<"  changeOperator(A, ALoc);			 				   \n"
<<(timelog ? "  MPItimerend(\"PETSc assembly\",t0)\n"    : ""  	    		   )
<<"										   \n"
<<"  //-----------------Assembly for b-----------------//			   \n"
<<"										   \n"
<<(timelog ? "  MPItimerbegin(\"RHS assembly\",t0)\n" : ""  	    		   )
<<"  b = elastodynamics(0,Vh);    				           	   \n"
<<(timelog ? "  MPItimerend  (\"RHS assembly\",t0)\n" : ""  	    		   )
<<"										   \n"
<<"  //-----------------Solving du=A^-1*b--------------//			   \n"
<<"										   \n"
<<(timelog ? "  MPItimerbegin(\"solving U\",t0)\n" : ""  	    	   	   )
<<"  set(A,sparams =\"  -ksp_type cg  \");             				   \n"
<<"  du[] = A^-1*b;                                   				   \n"
<<(timelog ? "  MPItimerend  (\"solving U\",t0)\n" : ""  	   		   )
<<"										   \n";

if(debug)if(spc==2)writesolver
<<"										   \n"
<<"  //-----------------Move mesh plotting------------//			   \n"
<<"										   \n"
<<"  meshN ThMoved = movemesh(Th, [x + du, y + du1]) ; 				   \n"
<<"  plotJustMeshMPI (ThMoved, wait=0, cmm=\"t=\"+t+\"(s)\")	 		   \n";

if(debug)if(spc==3)writesolver
<<"										   \n"
<<"  //-----------------Move mesh plotting------------//			   \n"
<<"										   \n"
<<"  meshN ThMoved = movemesh3(Th, transfo =[x + du, y + du1, z + du2]) ; 	   \n"
<<"  plotJustMeshMPI3 (ThMoved, wait=0, cmm=\"t=\"+t+\"(s)\")	 		   \n";

writesolver
<<"										   \n"
<<"  //-----------------updating variables------------//			   \n"
<<"										   \n"
//<<"  GFPUpdateDynamic(du[],uold[],vold[],aold[],beta,gamma,dt);		   \n"
//<<"  updateVariables(du,uold,vold,aold)					   \n"
<<(timelog ? "  MPItimerbegin(\"updating variables\",t0)\n" : ""      		   )
<<(useGFP  ? "  GFPUpdateDynamic(du[],uold[],vold[],aold[],beta,gamma,dt);\n" : "" )
<<(!useGFP ? "  updateVariables(du,uold,vold,aold,beta,gamma,dt)\n" : "" 	   )
<<(timelog ? "  MPItimerend(\"updating variables\",t0)\n" : ""      		   );


if(plotAll)if(spc==2){writesolver
<<"										   \n"
<<"  //-----------------ParaView plotting--------------//			   \n"
<<"										   \n"
<<(timelog ? "  MPItimerbegin(\"ParaView plotting\",t0)\n" : ""      		   )
<<"										   \n";


writesolver
<<"    savevtk(  \"VTUs/Solution.vtu\"   ,	 				   \n"
<<"                 Th                 ,				   	   \n";

if(PostProcess!="v" & PostProcess!="a" & PostProcess!="uva")writesolver
<<"                 [uold,uold1,0]     ,					   \n";
if(PostProcess=="v")writesolver
<<"                 [vold,vold1,0]     ,					   \n";
if(PostProcess=="a")writesolver 
<<"                 [aold,aold1,0]     ,					   \n";
if(PostProcess=="uva")writesolver
<<"                 [uold,uold1,0]     ,					   \n"
<<"                 [vold,vold1,0]     ,					   \n"
<<"                 [aold,aold1,0]     ,					   \n";

writesolver
<<"                 order=vtuorder     ,				   	   \n"
<<"                 dataname=\"U\"       ,				   	   \n"
<<"                 append=true       					   	   \n"
<<"              );			       				   	   \n"
<<(timelog ? "  MPItimerend(\"ParaView plotting\",t0)\n" : ""      		   );
}


if(plotTime)if(spc==3)writesolver
<<"										   \n"
<<"  //-----------------Paraview plotting-------------//			   \n"
<<"										   \n"
<<(timelog ? "  MPItimerbegin(\"ParaView plotting\",t0)\n" : ""	  	       	   )
<<"  exportTimeStep( namevtu,   			  		           \n"
<<"                  Th                    ,					   \n"
<<"                  [uold,uold1,uold2]    ,					   \n"
<<"                  vtuorder              ,					   \n"
<<"                  iterout               ,					   \n"
<<"                  t                     ,					   \n"
<<"                  namedata              ,				    	   \n"
<<"                  mpiCommWorld		 		   		   \n"
<<"           );  								   \n"
<<(timelog ? "  MPItimerend(\"ParaView plotting\",t0)\n" : ""      		   );

if(plotAll)if(spc==3){writesolver
<<"										   \n"
<<"  //-----------------ParaView plotting--------------//			   \n"
<<"										   \n"
<<(timelog ? "  MPItimerbegin(\"ParaView plotting\",t0)\n" : ""      		   );


writesolver
<<"    savevtk(  \"VTUs/Solution.vtu\"   ,	 				   \n"
<<"                 Th                 ,				   	   \n";

if(PostProcess!="v" & PostProcess!="a" & PostProcess!="uva")writesolver
<<"                 [uold,uold1,uold2] ,					   \n";
if(PostProcess=="v")writesolver
<<"                 [vold,vold1,vold2] ,					   \n";
if(PostProcess=="a")writesolver
<<"                 [aold,aold1,aold2] ,					   \n";
if(PostProcess=="uva")writesolver
<<"                 [uold,uold1,uold2] ,					   \n"
<<"                 [vold,vold1,vold2] ,					   \n"
<<"                 [aold,aold1,aold2] ,					   \n";

writesolver
<<"                 order=vtuorder     ,				   	   \n";

if(PostProcess!="v" & PostProcess!="a" & PostProcess!="uva")writesolver
<<"                 dataname=\"U\"       ,				   	   \n";

if(PostProcess=="v")writesolver
<<"                 dataname=\"U  V\" ,					   	   \n";
if(PostProcess=="a")writesolver
<<"                 dataname=\"U  A\" ,				 	  	   \n";
if(PostProcess=="uva")writesolver
<<"                 dataname=\"U  V  A\" ,				   	   \n";

writesolver
<<"                 append=true       					   	   \n"
<<"              );			       				   	   \n";


writesolver
<<(timelog ? "  MPItimerend(\"ParaView plotting\",t0)\n" : ""      		   );

}



if(pipegnu)if(!soildynamics){writesolver
<<"										   \n"
<<"  //---------------Energy calculations-------------//			   \n"
<<"										   \n"
<<(timelog ? "  MPItimerbegin(\"Energy calculations\",t0)\n" : ""	      	   )
<<"  E[0] =intN(Th,qforder=2)( 0.5*DPspc*(vold*vold+vold1*vold1));		   \n"
<<"  E[1] =intN(Th,qforder=2)( 0.5*DPspc*(lambda*divergence(uold)*divergence(uold) \n"
<<"                            + 2. * mu * epsilon(uold)'*epsilon(uold))  );	   \n"
<<"  E[2] += dt*intN(Th,qforder=2)( DPspc*(					   \n"
<<"		                  (etam*rho) *def(vold)'*def(vold)		   \n"
<<"		               +  (etak*lambda)*(divergence(vold)*divergence(vold))\n"
<<"		               +  (etak* 2.*mu)*(epsilon(vold)'*epsilon(vold))	   \n"
<<"			          ) );						   \n"
<<"  mpiAllReduce(E[0],EG[0],mpiCommWorld,mpiSUM);				   \n"
<<"  mpiAllReduce(E[1],EG[1],mpiCommWorld,mpiSUM);				   \n"
<<"  mpiAllReduce(E[2],EG[2],mpiCommWorld,mpiSUM);				   \n"
<<"										   \n"
<<"  //----------Appending energies to a file----------//			   \n"
<<"										   \n"
<<"  if(mpirank==0){								   \n"
<<"     ofstream ff(\"energies.data\",append);					   \n"
<<"     ff<< t << \"  \" << EG[0] << \"  \"<< EG[1] << \"  \" << EG[2] <<endl; 	   \n";

if(!supercomp)writesolver
<<"										   \n"
<<"     //---------------Gnuplot pipeping-------------//			   \n"
<<"										   \n"
<<"     pgnuplot <<\"plot\"		 				   	   \n"
<<"     <<\"\\\"energies.data\\\"\" 	   	           			   \n"
<<"     <<\"u ($1):($2) w lp lw 2 pt 7 ps 2 t \\\"K.E\\\",\" 	   		   \n"
<<"     <<\"\\\"energies.data\\\"\" 			   	   	   	   \n"
<<"     <<\"u ($1):($3) w lp lw 2  pt 7 ps 2 t \\\"E.E\\\",\"	   		   \n"
<<"     <<\"\\\"energies.data\\\"\" 	 		  	   		   \n"
<<"     <<\"u ($1):($4) w lp lw 2 pt 7 ps 2 t \\\"D.E\\\",\" 	  		   \n"
<<"     <<\"\\\"energies.data\\\"\" 	   	   	  			   \n"
<<"     <<\"u ($1):($3+$2+$4) w lp lw 2 pt 7 ps 2 t \\\"T.E\\\" \"     		   \n"
<<"     <<\"\\n\"; 	   	   						   \n" 
<<"     flush(pgnuplot);					   	   	   \n";

writesolver
<<"										   \n"
<<"   }							  	   		   \n"
<<(timelog ? "   MPItimerend(\"Energy calculations\",t0)\n" : ""      		   );
}  //-- [if loop terminator]  pipegnu ended --//



writesolver
<<"										   \n"
<<"  //-----------------updating time----------------//				   \n"
<<"										   \n"
<<"  t += dt; 									   \n";

writesolver
<<"}										   \n"
<<"										   \n";

writesolver
<<(timelog ? "if(mpirank==0)\n" : " "	   	        	    		    )
<<(timelog ? "cout << \" all operations ended, they \";\n" : ""    		    )
<<(timelog ? "MPItimerend  (\"solver\",t1)\n" : ""	   	        	    )
<<"										   \n"
<<"//-------------------------------THE END------------------------------//	   \n"; 

}  //-- [if loop terminator] !Sequential Dynamic ended --//
}  //-- [if loop terminator] !nonlinear ended --//



if(quasistatic){writesolver
<<"										   \n"
<<"//==============================================================================\n"
<<"//  ------- Variable initilization -------		  			   \n"
<<"//==============================================================================\n"	   
<<"										   \n"
<<"      duimp         = 0.       ;						   \n"
//<<"    def(u)        = init(0.) ;						   \n"
<<"      intVar[]      = kappa0   ;		   				   \n"
<<"      mufield[]     = mu       ;    	   	 				   \n"
<<"      lambdafield[] = lambda   ;        					   \n"
<<"										   \n"
<<"//==============================================================================\n"
<<"//  ------- Quasistatic loop for linear assembly and solving -------		   \n"
<<"//==============================================================================\n"	
<<"										   \n"
<<"  for (int n = 0; n < npas; n++){ 						   \n"
<<"										   \n"
<<"    if(mpirank == 0)							           \n"
<<"      cout <<\"============ \"<<\"Time step \"<< n <<\" ============ \\n\";	   \n"
<<"										   \n"
<<"  //---------------Nonlinear Newton-Rapsons loop------------------//		   \n"
<<"										   \n"
<<"   for (int i = 0; i <= iterMaxNR; i++){         			           \n"
<<"										   \n"
<<"    //----------Adjust Dirichlet boundary conditions--------------//		   \n"
<<"										   \n"
<<"     if (i>=1) duimp = 0.;							   \n"
<<"										   \n"
<<"    //--------------------Assembly for linear---------------------//		   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"RHS assembly for U\",t0)\n" : ""                  )
<<"     b = varIncr(0,Vh);							   \n"
<<(timelog ? "    MPItimerend  (\"RHS assembly for U\",t0)\n" : ""        	    )
<<"										   \n"
<<"    //------------------Error calculation------------------------//		   \n"
<<"										   \n"
<<"     if(i>0){							           \n"
<<(timelog ? "       MPItimerbegin(\"NL error checking\",t0)\n" : "" 	       	    )
<<"        b = b .* DP					 ;			   \n"
<<"        real errLoc, err				 ;			   \n"
<<"        errLoc = b.l2 				 ;			   \n"
<<"        errLoc = errLoc*errLoc 			 ;			   \n"
<<"        mpiAllReduce(errLoc,err,mpiCommWorld,mpiSUM)  ;			   \n"
<<"        err = sqrt(err) 				 ;			   \n"
<<"										   \n"
<<"        if(mpirank == 0) 							   \n"
<<"        cout << \"    iteration =\" << i << \", NR error =\" << err << endl ;   \n"
<<(timelog ? "       MPItimerend (\"NL error checking\",t0)\n" : "" 	       	    )
<<"       if(err <= tol) break;						   \n"
<<"     }									   \n"

<<"										   \n"
<<"    //----------------Assembly for bilinear----------------------//	 	   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"matrix assembly for U\",t0)\n" : ""         	    )
<<"     ALoc = varIncr(Vh,Vh);							   \n"
<<(timelog ? "    MPItimerend  (\"matrix assembly for U\",t0)\n" : ""          	    )
<<"										   \n"
<<"    //-----------PETSc assembly for bilinear---------------------//		   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"PETSc assembly for U\",t0)\n" : ""           	    )
<<"     changeOperator(A, ALoc);						   \n"
<<"     set(A,sparams =\"  -ksp_type cg   -ksp_rtol 1e-15 \");			   \n"
<<(timelog ? "    MPItimerend  (\"PETSc assembly for U\",t0)\n" : ""   	  	    )
<<"										   \n"
<<"    //-------------Linear system solving phase-------------------//		   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"solving U\",t0)\n" : ""         	  	    )
<<"     du[] = A^-1*b;								   \n"
<<(timelog ? "    MPItimerend  (\"solving U\",t0)\n" : ""           	  	    )
<<"										   \n"
<<"    //-------------Intermediate solution update-------------------//		   \n"
<<"										   \n"
<<(timelog ? "    MPItimerbegin(\"solution update\",t0)\n" : ""      	  	    )
<<"     u[]   += du[]  ; 							   \n"
//<<"     u1[]  += du1[] ; 							   \n"
<<"										   \n"
<<"    //----------Damage field calulation using Mazrs model---------//		   \n";


if(useGFP){writesolver
<<"										   \n";
if(spc==2)writesolver
<<"     defStrain(strain) = [epsilon(u)[0]          ,                              \n"
<<"                          epsilon(u)[2]/sqrt(2.) ,				   \n"
<<"                          epsilon(u)[1] 				           \n"
<<"                         ];  				      		   \n"
<<"										   \n";
if(spc==3)writesolver
<<"     defStrain(strain) = [epsilon(u)[0]          ,                              \n"
<<"                          epsilon(u)[5]/sqrt(2.) ,				   \n"
<<"                          epsilon(u)[4]/sqrt(2.) ,				   \n"
<<"                          epsilon(u)[1]          ,				   \n"
<<"                          epsilon(u)[3]/sqrt(2.) ,				   \n"
<<"                          epsilon(u)[2]   					   \n"
<<"                         ];  				      		   \n";

writesolver
<<"     GFPMazarsDamageUpdate(strain[],intVar[],damage[],kappa0,kappac); 	   \n";
}
else{ writesolver
<<"										   \n"
<<"     e11 = epsilon(u)[0] ;							   \n"
<<"     e22 = epsilon(u)[1] ;							   \n"
<<"     e12 = epsilon(u)[2]/sqrt(2.) ;						   \n"
<<"										   \n"
<<"     ep1=0.5*(e11+e22+sqrt((e11-e22)^2+4*e12^2));				   \n"
<<"     ep2=0.5*(e11+e22-sqrt((e11-e22)^2+4*e12^2));				   \n"
<<"										   \n"
<<"     eqStrain = sqrt((max(0,ep1))^2 + (max(0,ep2))^2)  ;  // Mazars Eq strain   \n"
<<"										   \n"
<<"     intVar = (intVar < eqStrain ? eqStrain : intVar);			   \n"
<<"										   \n"
<<"     damage = 1-(kappa0/intVar)*exp(-(intVar-kappa0)/(kappac-kappa0));	   \n"
<<"     damage = floor(100000.*damage)/100000. ;				   \n";
}

writesolver
<<"										   \n"
<<(timelog ? "    MPItimerend  (\"solution update\",t0)\n" : " "      	  	    )
<<"										   \n"
<<"  }										   \n"
<<"										   \n"
<<"  //----------Adjust Dirichlet boundary conditions--------------//		   \n"
<<"										   \n"
<<"  duimp = Duimp ;								   \n";


if(pipegnu){writesolver
<<"										   \n"
<<"  //-------------------Force calculation-----------------------//		   \n"
<<"										   \n"
<<(timelog ? "  MPItimerbegin(\"force calculation\",t0)\n" : ""           	    )
<<"   real ForceXloc , ForceXGather ;						   \n"
<<"   ForceXloc = intN1(Th,4,qforder=2)                                            \n"
<<"                          (DPspc*(1-damage)*stress(u,lambdafield,mufield)[0]);  \n"
<<"   mpiAllReduce(ForceXloc,ForceXGather,mpiCommWorld,mpiSUM);			   \n"
<<"										   \n"
<<"   if(mpirank==0){								   \n"
<<"     ofstream outputFile(\"output.data\", append);				   \n"
<<"     outputFile << n*Duimp << \" \" << ForceXGather << endl;			   \n";

if(!supercomp)writesolver
<<"     pgnuplot 								   \n"
<<"      <<\"plot\"		 				   		   \n"
<<"      <<\"\\\"output.data\\\"\" 	   	           			   \n"
<<"      <<\"u ($1):($2) w lp lw 2 pt 7 ps 2 notitle\" 	  			   \n"
<<"      <<\"\\n\"; 	   	   						   \n" 
<<"     flush(pgnuplot);					   	   	   \n";

writesolver
<<"   }										   \n"
<<(timelog ? "  MPItimerend  (\"force calculation\",t0)\n" : ""           	    );

}  //-- [if loop terminator]  pipegnu ended --//

writesolver
<<"}										   \n"
<<"										   \n"
<<(timelog ? "if(mpirank==0)\n" : " "	   	        	    		    )
<<(timelog ? "cout << \" all operations ended, they \";\n" : " "    		    )
<<(timelog ? "MPItimerend  (\"solver\",t1)\n" : " "	   	        	    )
<<"										   \n"
<<"//-------------------------------THE END------------------------------//	   \n";
}



if(!plotAll)if(!nonlinear)if(!dynamic)if(!soildynamics)if(!Sequential)writesolver
<<"										   \n"
<<(timelog ? "MPItimerend(\"solver\",t1)\n" : ""  	         	  	    )
<<"										   \n";

if(!plotAll)if(!nonlinear)if(!dynamic)if(!soildynamics)if(Sequential)writesolver
<<"										   \n"
<<(timelog ? "timerend(\"solver\",t1)\n" : ""  	         	  	   	    )
<<"										   \n";


} //-- [ostream terminator]  LinearFormBuilderAndSolver.edp closed --//

cout << " ............... Done \n";

