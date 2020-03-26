//=====================================================================================
// ------ Building the Parameters.edp file ------ 
//=====================================================================================

cout << " building ControlParameters.edp";

{ofstream  writemeshParameters("ControlParameters.edp");

writemeshParameters
<<"                                                                                \n"
<<"/***********************************Parameters**********************************\n"
<<"*                                                                              *\n"
<<"* Note!!! This file is  generated  by running SolverGenerator.edp. Do not edit *\n"
<<"*         in order to  control this  file please change flag arguments of  the *\n"
<<"*         SolverGenerator, details of which are present in SolverGenerator.edp *\n"
<<"*         or in the README.MD file.                                            *\n"
<<"*                                                                              *\n"
<<"*******************************************************************************/\n"
<<"                                                                                \n"
<<"//==============================================================================\n"
<<"// ------- Mesh parameters (Un-partitioned) -------                             \n"
<<"//==============================================================================\n";


if(!nonlinear)if(!dynamic)if(!quasistatic)if(!soildynamics)writemeshParameters
<<"                                                                                \n"
<<"  string ThName = \"../Meshes/"<<spc<<"D/bar\";  // Mesh  name                  \n";

if(nonlinear)if(!dynamic)writemeshParameters
<<"                                                                                \n"
<<"  string ThName = \"../Meshes/"<<spc<<"D/tensile-crack\"; // Mesh  name         \n";

if(dynamic)writemeshParameters
<<"                                                                                \n"
<<"  string ThName = \"../Meshes/"<<spc<<"D/bar-dynamic\"; // Mesh  name  	   \n";

if(quasistatic)writemeshParameters
<<"                                                                                \n"
<<"  string ThName = \"../Meshes/"<<spc<<"D/quasistatic\"; // Mesh  name    	   \n";

if(soildynamics)writemeshParameters
<<"                                                                                \n"
<<"  string ThName = \"../Meshes/"<<spc<<"D/soil\";       // Mesh  name            \n";

if(!nonlinear)if(!dynamic)if(!quasistatic)if(!soildynamics){writemeshParameters
<<"                                                                                \n"
<<"//==============================================================================\n"
<<"// ------- Material parameters ------- 		 			   \n"
<<"//==============================================================================\n"
<<"                                                                                \n";

if(fastmethod)writemeshParameters
<<"  real    mu                        // Lame parameter			   \n"
<<"         ,lambda;                   // Lame parameter			   \n"
<<"                                                                                \n"
<<"{										   \n"
<<"  real E  = 200.e9  ,                // Modulus of Elasticity - [Pa]	  	   \n"
<<"       nu = 0.3     ;                // Poisson ratio - [-]		   	   \n"
<<"	 									   \n"
<<"  mu     = E/(2.*(1.+nu))            ;					   \n"
<<"  lambda = E*nu/((1.+nu)*(1.-2.*nu)) ;					   \n"
<<"}	 									   \n";

if(!fastmethod){writemeshParameters
<<"                                                                                \n"
<<"  real a1,a2,a3        ;                // Building material tensor	   	   \n"
<<"{										   \n"
<<"  real E  = 200.e9     ,                // Modulus of Elasticity - [Pa]	   \n"
<<"       nu = 0.3        ;                // Poisson ratio - [-]		   \n"
<<"	 									   \n"
<<"       a1 = E*(1.-nu)/((1.+nu)*(1.-2.*nu))   ;				   \n"
<<"       a2 = a1*nu/(1.-nu)                    ;				   \n"
<<"       a3 = E/(2*(1.+nu))                    ;				   \n"
<<"}	 									   \n";

if(spc==2)writemeshParameters
<<"                                                                                \n"
<<"  macro Mt   [[ a1 ,  a2 , 0 ],						   \n"
<<"              [ a2 ,  a1 , 0 ],						   \n"
<<"              [ 0  ,  0  , a3]]               // Material tensor		   \n";

if(spc==3)writemeshParameters
<<"                                                                                \n"
<<"  macro Mt   [[ a1 ,  a2 , a2 , 0  , 0  , 0 ],				   \n"
<<"              [ a2 ,  a1 , a2 , 0  , 0  , 0 ],				   \n"
<<"              [ a2 ,  a2 , a1 , 0  , 0  , 0 ],     				   \n"
<<"              [ 0  ,  0  , 0  , a3 , 0  , 0 ],      				   \n"
<<"              [ 0  ,  0  , 0  , 0  , a3 , 0 ],     				   \n"
<<"              [ 0  ,  0  , 0  , 0  , 0  , a3]]// Material tensor		   \n";
}}

if(quasistatic)writemeshParameters
<<"                                                                                \n"
<<"//==============================================================================\n"
<<"// ------- Material parameters ------- 		 			   \n"
<<"//==============================================================================\n"
<<"                                                                                \n"
<<"  real    mu                        // Lame parameter			   \n"
<<"         ,lambda                    // Lame parameter			   \n"
<<"         ,kappa0 = 1.e-4            // Damage initiation threshold		   \n"
<<"         ,kappac = 1.e-3            // Critical strain level			   \n"
<<"         ;	   								   \n"
<<"                                                                                \n"
<<"{										   \n"
<<"  real E  = 100.e6  ,              // Modulus of Elasticity - [Pa]	   	   \n"
<<"       nu = 0.2     ;              // Poisson ratio - [-]		   	   \n"
<<"	 									   \n"
<<"  mu     = E/(2.*(1.+nu))            ;					   \n"
<<"  lambda = E*nu/((1.+nu)*(1.-2.*nu)) ;					   \n"
<<"}	 									   \n"
<<"                                                                                \n"
<<"//==============================================================================\n"
<<"// ------- Solver parameters ------- 		 			   \n"
<<"//==============================================================================\n"
<<"                                                                                \n"
<<"  real tol      = 1.e-5 ;          // Tolerance of the NR procedure	   	   \n"
<<"                                                                                \n"
<<"  int npas      = 2000  ,          // # of pseudo-time steps		   	   \n"
<<"      iterMaxNR = 10    ;          // Max # of iterations for the NR loop       \n"
<<"                                                                                \n"
<<"//==============================================================================\n"
<<"// ------- Loading parameters ------- 		 			   \n"
<<"//==============================================================================\n"
<<"  real Duimp = 2.e-7,              // Imposed displacement variation		   \n"
<<"       duimp        ;              // Dummy Imposed displacement variation      \n";


if(nonlinear){writemeshParameters
<<"                                                                                \n"
<<"//==============================================================================\n"
<<"// ------- Material parameters ------- 		 			   \n"
<<"//==============================================================================\n"
<<"                                                                                \n"
<<"  real lambda = 121.15e3 ,							   \n"
<<"       mu     = 80.77e3  ;							   \n"
<<"	 									   \n"
<<"//==============================================================================\n"
<<"// ------- Nonlinear parameters ------- 		 			   \n"
<<"//==============================================================================\n"
<<"	 									   \n"
<<"  real Gc    = 2.7  ,							   \n"
<<"       lfac  = 2.0  ,							   \n"
<<"       maxtr = 7e-3 ,							   \n"
<<"       tr    = 1e-5 ,							   \n"
<<"       dtr   = 1e-5 ,							   \n"
<<"       lo           ;	// Calculated in OtherParameters.edp		   \n";
}



if(dynamic){writemeshParameters
<<"                                                                                \n"
<<"//==============================================================================\n"
<<"// ------- Material parameters ------- 		 			   \n"
<<"//==============================================================================\n"
<<"                                                                                \n"
<<"  real lambda = 576.9230769  ,           // E=1000. & nu=0.3			   \n"
<<"       mu     = 384.6153846  ;           // E=1000. & nu=0.3			   \n"
<<"	 									   \n"
<<"//==============================================================================\n"
<<"// ------- Dynamic parameters ------- 	 			   	   \n"
<<"//==============================================================================\n"
<<"	 									   \n";

if(TimeDiscretization=="generalized-alpha")writemeshParameters
<<"  real rho  = 1.0  ,								   \n"
<<"       etam = 0.01 ,								   \n"
<<"       etak = 0.01 ,								   \n"
<<"       alpm = 0.2  ,								   \n"
<<"       alpf = 0.4  ,								   \n"
<<"       tmax = 4.0  ,								   \n"
<<"       t    = 0.08 ,								   \n"
<<"       dt   = 0.08 ;								   \n"
<<"	 									   \n"
<<"  real gamma = 0.5 + alpf - alpm         ,					   \n"
<<"       beta  = (1./4.)*(gamma+0.5)^2     ;					   \n"
<<"	 									   \n";

if(TimeDiscretization=="newmark-beta")writemeshParameters
<<"  real rho  = 1.0  ,								   \n"
<<"       etam = 0.01 ,								   \n"
<<"       etak = 0.01 ,								   \n"
<<"       tmax = 4.0  ,								   \n"
<<"       t    = 0.08 ,								   \n"
<<"       dt   = 0.08 ;								   \n"
<<"	 									   \n"
<<"  real gamma = 0.5                       ,					   \n"
<<"       beta  = (1./4.)*(gamma+0.5)^2     ;					   \n"
<<"	 									   \n";

if(TimeDiscretization=="central-difference")writemeshParameters
<<"  real rho  = 1.0  ,								   \n"
<<"       etam = 0.01 ,								   \n"
<<"       etak = 0.01 ,								   \n"
<<"       tmax = 4.0  ,								   \n"
<<"       t    = 0.08 ,								   \n"
<<"       dt   = 0.08 ,								   \n"
<<"       gamma = 0.5 ;								   \n"
<<"	 									   \n";


if(TimeDiscretization=="hht-alpha")writemeshParameters
<<"  real rho  = 1.0  ,								   \n"
<<"       etam = 0.01 ,								   \n"
<<"       etak = 0.01 ,								   \n"
<<"       alpf = 0.4  ,								   \n"
<<"       tmax = 4.0  ,								   \n"
<<"       t    = 0.08 ,								   \n"
<<"       dt   = 0.08 ;								   \n"
<<"	 									   \n"
<<"  real gamma = 0.5 + alpf                ,					   \n"
<<"       beta  = (1./4.)*(gamma+0.5)^2     ;					   \n"
<<"	 									   \n";

}


if(soildynamics){writemeshParameters
<<"                                                                                \n"
<<"//==============================================================================\n"
<<"// ------- Soil parameters -------    		 			   \n"
<<"//==============================================================================\n"
<<"                                                                                \n"
<<"  real rho  = 2500.0 ;              // Density				   \n"
<<"                                                                                \n"
<<"  real    mu                        // Lame parameter			   \n"
<<"         ,lambda                    // Lame parameter			   \n"
<<"         ;	   								   \n"
<<"                                                                                \n"
<<"{										   \n"
<<"  real E  = 6.62e6  ,                // Modulus of Elasticity - [Pa]	   	   \n"
<<"       nu = 0.45    ;                // Poisson ratio - [-]		   	   \n"
<<"	 									   \n"
<<"  mu     = E/(2.*(1.+nu))            ;					   \n"
<<"  lambda = E*nu/((1.+nu)*(1.-2.*nu)) ;					   \n"
<<"}	 									   \n"
<<"  real cs   = sqrt(mu/rho)               ,					   \n"
<<"       cp   = sqrt((lambda+(2.*mu))/rho) ;					   \n"
<<"	 									   \n"
<<"//==============================================================================\n"
<<"// ------- Dynamic parameters ------- 	 			   	   \n"
<<"//==============================================================================\n"
<<"	 									   \n";

if(TimeDiscretization=="generalized-alpha")writemeshParameters
<<"  real alpm = 0.2     ,							   \n"
<<"       alpf = 0.4     ,							   \n"
<<"       tmax = 4.0     ,							   \n"
<<"       t    = 0.01    ,							   \n"
<<"       dt   = 0.01    ;							   \n"
<<"	 									   \n"
<<"  real gamma = 0.5 + alpf - alpm         ,					   \n"
<<"       beta  = (1./4.)*(gamma+0.5)^2     ;					   \n"
<<"	 									   \n";

if(TimeDiscretization=="newmark-beta")writemeshParameters
<<"  real tmax = 4.0     ,							   \n"
<<"       t    = 0.01    ,							   \n"
<<"       dt   = 0.01    ;							   \n"
<<"	 									   \n"
<<"  real gamma = 0.5                       ,					   \n"
<<"       beta  = (1./4.)*(gamma+0.5)^2     ;					   \n"
<<"	 									   \n";

if(TimeDiscretization=="central-difference")writemeshParameters
<<"  real tmax = 4.0     ,							   \n"
<<"       t    = 0.01    ,							   \n"
<<"       dt   = 0.01    ,							   \n"
<<"       gamma = 0.5    ;							   \n"
<<"	 									   \n";

if(TimeDiscretization=="hht-alpha")writemeshParameters
<<"  real alpf = 0.4     ,							   \n"
<<"       tmax = 4.0     ,							   \n"
<<"       t    = 0.01    ,							   \n"
<<"       dt   = 0.01    ;							   \n"
<<"	 									   \n"
<<"  real gamma = 0.5 + alpf                ,					   \n"
<<"       beta  = (1./4.)*(gamma+0.5)^2     ;					   \n"
<<"	 									   \n";


writemeshParameters
<<"//==============================================================================\n"
<<"// -------Paraxial boundary-condition parameters-------			   \n"
<<"//==============================================================================\n"
<<"                                                                                \n";

if(spc==2)writemeshParameters
<<"  int [int]   PAlabels = [2,4,5];   \t// Vector of Paraxial load	   	   \n"
<<"  int [int]   LoadLabels = [3];   \t// Vector of Paraxial load	   	   \n"
<<"  real tt;									   \n"
<<"  func v1in = (tt <= 1.0 ? real(sin(tt*(2.*pi/1.0)))*(x>20&&x<30) : 0. );       \n";

if(spc==3)writemeshParameters
<<"  int [int]   PAlabels = [1,2,3,5];   \t// Vector of Paraxial load	   	   \n"
<<"  int [int]   LoadLabels = [4];   \t// Vector of Paraxial load	   	   \n"
<<"  real tt;									   \n"
<<"  func v1in = (tt <= 1.0 ? real(sin(tt*(2.*pi/1.0)))*(x>10&&x<40)*(z>10&&z<40) : 0. );\n";


writemeshParameters
<<"	 									   \n";
}

if(dirichletconditions>=1)if(!quasistatic)if(!soildynamics){writemeshParameters
<<"                                                                                \n"
<<"//==============================================================================\n"
<<"// -------Dirichlet boundary-condition parameters-------			   \n"
<<"//==============================================================================\n"
<<"                                                                                \n"
<<"  int [int]   Dlabel = ["<<labelDirichlet<<"\t//  Label for Dirichlet border 0  \n";

for(int i=1; i<dirichletconditions; i++)
writemeshParameters
<<"                       ,"<<labelDirichlet<<"\t//  Label Dirichlet border "<<i<<"\n";

writemeshParameters
<<"                       ];							   \n"
<<"                                                                                \n";


if(spc==2){
writemeshParameters
<<"  real[int]   Dvalue = [ 0., 0.	// u1,u2 of Dirichlet border 0	 	   \n";
for(int i=1; i<dirichletconditions; i++)
writemeshParameters
<<"                        ,0., 0.	// u1,u2 of Dirichlet border "<<i<<" 	   \n";
}

if(spc==3){
writemeshParameters
<<"  real[int]   Dvalue = [ 0., 0., 0.	// u1,u2,u3 of Dirichlet border 0	   \n";
for(int i=1; i<dirichletconditions; i++)
writemeshParameters
<<"                        ,0., 0., 0.	// u1,u2,u3 of Dirichlet border "<<i<<"    \n";
}

writemeshParameters
<<"                       ];							   \n"
<<"                                                                                \n";

}

if(dirichletpointconditions>=1){writemeshParameters
<<"                                                                                \n"
<<"//==============================================================================\n"
<<"// -------Dirichlet point boundary-condition parameters-------		   \n"
<<"//==============================================================================\n"
<<"                                                                                \n"
<<"  int [int]   Dpointlab = ["<<labelDirichlet<<"\t// Labels containing point 0   \n";


for(int i=1; i<dirichletpointconditions; i++)
writemeshParameters
<<"                          ,"<<labelDirichlet<<"\t//  Labels containing point "<<i<<"\n";

writemeshParameters
<<"                          ];							   \n"
<<"                                                                                \n";


if(spc==2){
writemeshParameters
<<"  real[int]   PnV = [ 0., 0., 0., 0. // [x, y, u1, u2] of point border 0	   \n";
for(int i=1; i<dirichletpointconditions; i++)
writemeshParameters
<<"                     ,0., 0., 0., 0. // [x, y, u1, u2] of point border "<<i<<"   \n";
}

if(spc==3){
writemeshParameters
<<"  real[int]   PnV = [ 0., 0., 0., 0., 0., 0.	// [x,y,z,u1,u2,u3] of point 0	   \n";
for(int i=1; i<dirichletpointconditions; i++)
writemeshParameters
<<"                     ,0., 0., 0., 0., 0., 0.	// [x,y,z,u1,u2,u3] of point "<<i<<"\n";
}

writemeshParameters
<<"                    ];							   \n"
<<"                                                                                \n";
}


if(tractionconditions>=1){writemeshParameters
<<"                                                                                \n"
<<"//==============================================================================\n"
<<"// ------- Neumann/traction boundary-condition parameters -------		   \n"
<<"//==============================================================================\n"
<<"                                                                                \n"
<<"  int [int]   Tlabel = [ 4		//  Label for traction border 1	           \n";                      

for(int i=1; i<tractionconditions; i++)
writemeshParameters
<<"                        ,4		//  Label for traction border "<<i<<"	   \n";

writemeshParameters
<<"                       ];							   \n"
<<"                                                                                \n"
<<"                                                                                \n";

if(spc==2){
for(int i=0; i<tractionconditions; i++)
writemeshParameters
<<"  real  tx"<<i<<"=0, ty"<<i<<"=10.;\t\t\t// Traction forces on label "<<i<<"    \n";

writemeshParameters
<<"                                                                                \n"
<<"  macro T(i,j) [i,j]			// Traction vector	                   \n"; 
}


if(spc==3){
for(int i=0; i<tractionconditions; i++)
writemeshParameters
<<"  real tx"<<i<<"=0, ty"<<i<<"=0, tz"<<i<<"=0 ;// Component traction  on label "<<i<<"\n";

writemeshParameters
<<"  macro T(i,j,k) [i,j,k]		// Three component traction forces         \n"; 
}

}

if(dynamic)writemeshParameters
<<"                                                                                \n"
<<"//==============================================================================\n"
<<"// ------- Neumann boundary-condition parameters -------			   \n"
<<"//==============================================================================\n"
<<"                                                                                \n"
<<"  real tt;									   \n"
<<"  func tr = (tt <= 0.8 ? real(1.*tt/0.8) : 0. );    // tr is dynamic loading	   \n"
<<"                                                                                \n";


if(bodyforce){writemeshParameters
<<"                                                                                \n"
<<"//==============================================================================\n"
<<"// ------- Bodyforce  parameters -------					   \n"
<<"//==============================================================================\n"
<<"                                                                                \n"
<<"  real f1 = 0.;                      // X component body forces	  	   \n"
<<"  real f2 = 8.e3*(-9.81);            // Y component body forces		   \n";

if(spc==2)writemeshParameters
<<"                                                                                \n"
<<"  macro BF [f1,f2]                   // Two component body forces	   	   \n"; 

if(spc==3)writemeshParameters
<<"  real f3 = 0.;                      // Z component body forces		   \n"
<<"                                                                                \n"
<<"  macro BF [f1,f2,f3]                // Three component body forces	   	   \n"; 
}

writemeshParameters
<<"	 									   \n"
<<"//==============================================================================\n"
<<"// ------- Solver control parameters ------- 	 			   \n"
<<"//==============================================================================\n"
<<"	 	// TO DO							   \n"
<<"	 									   \n";

} //-- [ostream terminator]  ControlParameters.edp closed --//

cout << " ........................ Done \n";

