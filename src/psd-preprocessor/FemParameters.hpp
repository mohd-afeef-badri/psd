//=====================================================================================
// ------ Building the Parameters.edp file ------ 
//=====================================================================================

cout << " building FemParameters.edp";

{ofstream  writFemParameters("FemParameters.edp");

writFemParameters
<<"										   \n"
<<"/***********************************Parameters**********************************\n"
<<"*                                                                              *\n"
<<"* Note!!! This file is  generated  by running SolverGenerator.edp. Do not edit *\n"
<<"*         in order to  control this  file please change flag arguments of  the *\n"
<<"*         SolverGenerator, details of which are present in SolverGenerator.edp *\n"
<<"*         or in the README.MD file.                                            *\n"
<<"*                                                                              *\n"
<<"*******************************************************************************/\n"
<<"										   \n";

if(!nonlinear)if(!vectorial)if(!dynamic)if(!soildynamics)if(!quasistatic)writFemParameters
<<"										   \n"
<<"//==============================================================================\n"
<<"// ------- Finite element variables -------					   \n"
<<"//==============================================================================\n"
<<"										   \n"
<<"  Vh  def(u)    ;    //  Displacement					   \n";

if(nonlinear)if(!vectorial)if(!dynamic)if(!soildynamics){writFemParameters
<<"										   \n"
<<"//==============================================================================\n"
<<"// -------Finite element variables -------					   \n"
<<"//==============================================================================\n"
<<"										   \n"
<<"  Vh  def2(u)    ,    //  Displacement			   		   \n"
<<"      def2(uold) ,    //  Previous displacement		   		   \n"
<<"      def2(DPspc);    //  Partition of unity 	   	   		   \n"
<<"										   \n"
<<"										   \n"
<<"  Vh1 phi       ,     //  Phase field 			   		   \n"
<<"      phiold    ,     //  Previous iteration phase field			   \n"
<<"      DZspc     ;     //  Partition of unity		  	 	   	   \n";

if(energydecomp)writFemParameters
<<"										   \n"
<<"  Wh0 H         ,    // Stress history 					   \n"
<<"      Hplus     ,    // Tensile stress history				   \n"
<<"      Hminus    ;    // Compressive stress history				   \n";
}

if(nonlinear)if(vectorial)if(!dynamic)if(!soildynamics){writFemParameters
<<"										   \n"
<<"//==============================================================================\n"
<<"// ------- Finite element variables -------					   \n"
<<"//==============================================================================\n"
<<"										   \n"
<<"  Vh  def(u)    ,    // Vectorial variable for [u,phi]			   \n"
<<"      def(uold) ,    // Vectorial variable for old [u,phi] 			   \n"
<<"      def(DPspc);    // Vectorial variables for partition of unity    	   \n";

if(energydecomp)writFemParameters
<<"										   \n"
<<"  Wh0 H         ,    // Stress history 			   		   \n"
<<"      Hplus     ,    // Tensile stress history		   		   \n"
<<"      Hminus    ;    // Compressive stress history		   		   \n";
}

if(dynamic || soildynamics){writFemParameters
<<"										   \n"
<<"//==============================================================================\n"
<<"// -------Finite element variables -------					   \n"
<<"//==============================================================================\n"
<<"										   \n"
<<"  Vh  def(du)    ,      // Displacement FE field				   \n"
<<"      def(uold)  ,      // Previous iteration displacement FE field		   \n"
<<"      def(vold)  ,      // Previous iteration velocity FE field		   \n"
<<"      def(aold)  ,      // Previous iteration acceleration FE field		   \n"
<<"      def(DPspc) ;      // Partition of unity field for integral		   \n"
<<"										   \n";
}



if(nonlinear){

if(Sequential){

writFemParameters
<<"										   \n"
<<"//==============================================================================\n"
<<"// ------- Fem matrices and vectors -------					   \n"
<<"//==============================================================================\n"
<<"										   \n"
<<"  matrix  A, A1				;  				   \n"
<<"  real[int]  b(Vh.ndof), b1(Vh1.ndof)	;				   \n";
}

if(!Sequential){

writFemParameters
<<"										   \n"
<<"//==============================================================================\n"
<<"// -------  Fem matrices and vectors -------	   				   \n"
<<"//==============================================================================\n"
<<"										   \n"
<<(timelog ? "  MPItimerbegin(\"matrix sparsity assembly\",t0)\n" : ""         	    )
<<"  Mat  A( Vh.ndof,  restrictionIntersectionP, DP)   ; 	 		   \n";

if(!vectorial)writFemParameters
<<"										   \n"
<<"  Mat A1( Vh1.ndof,  restrictionIntersectionZ, DZ);  			   \n"
<<(timelog ? "  MPItimerend(\"matrix sparsity assembly\",t0)\n" : " "          	    )
<<"										   \n"
<<"  matrix     ALoc, ALoc1                 ;  // Local matrices for bilinear	   \n"
<<"  real[int]  b(Vh.ndof), b1(Vh1.ndof)    ;  // Local vectors for  linear	   \n";

if(vectorial)writFemParameters
<<(timelog ? "  MPItimerend(\"matrix sparsity assembly\",t0)\n" : " "          	    )
<<"  matrix     ALoc           ;        // Local vectorial matrix for bilinear	   \n"
<<"  real[int]  b(Vh.ndof)     ;        // Local vectorial real vector for linear  \n";


writFemParameters
<<"										   \n"
<<"//==============================================================================\n"
<<"// ------- Partition of unity for integrals -------				   \n"
<<"//==============================================================================\n"
<<"										   \n"
<<"  for(int i=0; i<DP.n; i++) 							   \n"
<<"    DPspc[][i]=DP[i];							   \n";

if(!vectorial)writFemParameters
<<"										   \n"
<<"  for(int i=0; i<DZ.n; i++) 							   \n"
<<"    DZspc[][i]=DZ[i];							   \n";
}

}


if(dynamic || soildynamics){
if(Sequential)writFemParameters
<<"										   \n"
<<"//==============================================================================\n"
<<"// ------- Fem matrices and vectors -------					   \n"
<<"//==============================================================================\n"
<<"										   \n"
<<"  matrix  A			;						   \n"
<<"  real[int]  b(Vh.ndof)	;						   \n";

if(!Sequential){
if(pipegnu)writFemParameters
<<"										   \n"
<<"//==============================================================================\n"
<<"// ------- Partion of unity for integrals -------				   \n"
<<"//==============================================================================\n"
<<"										   \n"
<<"  for(int i=0; i<DP.n; i++) 							   \n"
<<"    DPspc[][i]=DP[i];							   \n";

writFemParameters
<<"										   \n"
<<"//==============================================================================\n"
<<"//  -------  Fem matrices and vectors -------				   \n"
<<"//==============================================================================\n"
<<"										   \n"
<<"  matrix       ALoc    ;							   \n"
<<"  real[int]    b(Vh.ndof);							   \n"
<<"										   \n"
<<(timelog ? "  MPItimerbegin(\"matrix sparsity assembly\",t0)\n" : ""         	    )
<<"  Mat  A(Vh.ndof, restrictionIntersectionP, DP, symmetric=1)  ;		   \n"
<<(timelog ? "  MPItimerend(\"matrix sparsity assembly\",t0)\n" : " "          	    )
<<"										   \n";
}

}

if(quasistatic){writFemParameters
<<"										   \n"
<<"//==============================================================================\n"
<<"// ------- Finite element variables -------					   \n"
<<"//==============================================================================\n"
<<"										   \n"
<<"  Vh  def(u)      ,    // Current displacement		   		   \n"
<<"      def(du)     ,    // Incremental displacement (du{n})       		   \n"
<<"      def(DPspc)  ;    // Partition of unity 	   			   \n"
<<"										   \n"
<<"  Wh0 damage      ,    //  Isotropic damage					   \n"
<<"      intVar      ,    //  Internal variable		   			   \n";

if(!useGFP)writFemParameters
<<"      e11         ,    //  11 component of strain				   \n"
<<"      e22         ,    //  22 component of strain				   \n"
<<"      e12         ,    //  12 component of strain 				   \n"
<<"      ep1         ,    //  1st principal strain component (in x)		   \n"
<<"      ep2         ,    //  2nd principal strain component (in y)		   \n"
<<"      eqStrain    ,    //  Equivalent strain	 				   \n";

writFemParameters	
<<"      lambdafield ,    //  lambda						   \n"
<<"      mufield     ;    //  mu	 					   \n"
<<"										   \n";

if(useGFP)writFemParameters
<<"  VhStr defStrain(strain)     ;    //  Stain defenition			   \n";

if(!Sequential)writFemParameters
<<"										   \n"
<<"//==============================================================================\n"
<<"// -------  Fem matrices and vectors -------	   				   \n"
<<"//==============================================================================\n"
<<"										   \n"
<<(timelog ? "  MPItimerbegin(\"matrix sparsity assembly\",t0)\n" : ""         	    )
<<"  Mat  A( Vh.ndof,  restrictionIntersectionP, DP)   ; 	 		   \n"
<<(timelog ? "  MPItimerend(\"matrix sparsity assembly\",t0)\n" : " "          	    )
<<"										   \n"
<<"  matrix     ALoc           ;        // Local vectorial matrix for bilinear	   \n"
<<"  real[int]  b(Vh.ndof)     ;        // Local vectorial real vector for linear  \n"
<<"										   \n"
<<"//==============================================================================\n"
<<"// ------- Partition of unity for integrals -------				   \n"
<<"//==============================================================================\n"
<<"										   \n"
<<"  for(int i=0; i<DP.n; i++) 							   \n"
<<"    DPspc[][i]=DP[i];							   \n";
}



} //-- [ostream terminator]  FemParameters.edp closed --//

cout << "     ........................ Done \n";