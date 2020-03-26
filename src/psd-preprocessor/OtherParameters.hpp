//=====================================================================================
// ------ Building the Parameters.edp file ------ 
//=====================================================================================

cout << " building OtherParameters.edp"; 

{ofstream  writemeshParameters("OtherParameters.edp");

writemeshParameters
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


if(timelog)writemeshParameters
<<"	 									   \n"
<<"//==============================================================================\n"
<<"// ------- Time logging parameters ------- 		 			   \n"
<<"//==============================================================================\n"
<<"	 									   \n"
<<"  real t0,t1;								   \n";

if(!Sequential){

writemeshParameters
<<"										   \n"
<<"//==============================================================================\n"
<<"// ------- Domian decomposition suppoprt variables -------  			   \n"
<<"//==============================================================================\n"
<<"										   \n"
<<" int[int][int] restrictionIntersectionP(0);  // Local-to-neighbors renumbering  \n"
<<" real[int] DP;                               // Partition of unity		   \n";


if(nonlinear)if(!vectorial)writemeshParameters
<<"										   \n"
<<" int[int][int] restrictionIntersectionZ(0);  // Local-to-neighbors renumbering  \n"
<<" real[int] DZ;                               // Partition of unity		   \n";


}

if(nonlinear){

if(plotAll)writemeshParameters
<<"	 									   \n"
<<"//==============================================================================\n"
<<"// ------- Paraview plotting parameters ------- 	 			   \n"
<<"//==============================================================================\n"
<<"	 									   \n"
<<"  int[int] vtuorder=[1,1];   						   \n" 
<<"  string   namedata=\"U Phi\";						   \n"
<<"  bool     withsur=true;						  	   \n"
<<"	 									   \n"
<<"  int iterout  = 0 ,               // Loop Counter			    	   \n"
<<"      iterout1 = 0 ;               // Loop Counter				   \n";

if(plotAll)if(!Sequential)writemeshParameters
<<"										   \n"
<<"  if(mpirank==0)system(\"rm -rf VTUs/Solution_\"+mpisize+\".pvd\");	    	   \n";

if(plotAll)if(!Sequential)writemeshParameters
<<"										   \n"
<<"  if(mpirank==0)system(\"mkdir -p VTUs\");	    	   			   \n";

if(pipegnu){writemeshParameters 
<<"										   \n"
<<"//==============================================================================\n"
<<"// ------- Gnuplot pipeing parameters ------					   \n"
<<"//==============================================================================\n"
<<"										   \n"
<<(Sequential ? "" : "  if(mpirank==0)\n"	   				    )
<<"  system(\"rm force.data\");							   \n"
<<"										   \n";

if(!supercomp)writemeshParameters
<<"  pstream pgnuplot(\"gnuplot -p\");						   \n"
<<(Sequential ? "" : "  if(mpirank==0)\n"	   				    )
<<"  pgnuplot 									   \n"
<<"  <<\" set title  \\\"Traction = \"+tr+\"\\\";			\\n\"      \n"
<<"  <<\" set termoption font \\\"Arial-Bold,20\\\";		\\n\"		   \n"
<<"  <<\" set xrange [0:.008]; set yrange [0:.9];		\\n\"    	   \n"
<<"  <<\" set xlabel \\\" Displacement \\\";			\\n\"	   	   \n"
<<"  <<\" set ylabel \\\" Force (kN)\\\";			\\n\"  	  	   \n"
<<"  <<\" set grid x y;    set key left;			\\n\"; 	   	   \n";
}

}



if(dynamic){writemeshParameters
<<"	 									   \n"
<<"//==============================================================================\n"
<<"// ------- Dynamic constant parameters -------  			   	   \n"
<<"//==============================================================================\n"
<<"	 									   \n"
<<"  real[int] c(11);								   \n"
<<"	 									   \n";

if(TimeDiscretization=="generalized-alpha")writemeshParameters
<<"  c[0] =   rho*(1.-alpm)/(beta*dt*dt) + etam*rho*gamma*(1-alpf)/beta/dt        ;\n"
<<"  c[1] =   lambda*(1.-alpf) + lambda*etak*gamma*(1-alpf)/beta/dt               ;\n"
<<"  c[2] =   2.*mu*(1.-alpf) + 2.*mu*etak*gamma*(1-alpf)/beta/dt                 ;\n"
<<"  c[3] =   rho*(1.-alpm)/beta/dt - etam*rho*(1-gamma*(1-alpf)/beta)            ;\n"
<<"  c[4] =   rho*( (1.-alpm)*(1.-2.*beta)/2./beta - alpm - etam*dt*(1.-alpf)*(1.-gamma/2/beta))   ;\n"
<<"  c[5] =   lambda*alpf -    lambda*etak*gamma*(1.-alpf)/beta/dt                ;\n"
<<"  c[6] =   2*mu*alpf   -    2.*mu*etak*gamma*(1.-alpf)/beta/dt                 ;\n"
<<"  c[7] =   etak*lambda*(gamma*(1.-alpf)/beta - 1)                              ;\n"
<<"  c[8] =   etak*lambda*dt*(1.-alpf)*((1.-2*beta)/2./beta - (1.-gamma))         ;\n"
<<"  c[9] =   etak*2*mu*(gamma*(1.-alpf)/beta -1)                                 ;\n"
<<"  c[10]=   etak*2*mu*dt*(1.-alpf)*((1.-2*beta)/2./beta -(1.-gamma))            ;\n"
<<"	 									   \n";

if(TimeDiscretization=="newmark-beta")writemeshParameters
<<"  c[0] =   rho/(beta*dt*dt) + etam*rho*gamma/beta/dt        	  		  ;\n"
<<"  c[1] =   lambda + lambda*etak*gamma/beta/dt               	  		  ;\n"
<<"  c[2] =   2.*mu + 2.*mu*etak*gamma/beta/dt                 	  		  ;\n"
<<"  c[3] =   rho/beta/dt - etam*rho*(1-gamma/beta)            	  		  ;\n"
<<"  c[4] =   rho*( (1.-2.*beta)/2./beta  - etam*dt*(1.-gamma/2/beta))  	  ;\n"
<<"  c[5] =  -lambda*etak*gamma/beta/dt                		  		  ;\n"
<<"  c[6] =  -2.*mu*etak*gamma/beta/dt                 		  	  	  ;\n"
<<"  c[7] =   etak*lambda*(gamma/beta - 1)                              	  ;\n"
<<"  c[8] =   etak*lambda*dt*((1.-2*beta)/2./beta - (1.-gamma))         	  ;\n"
<<"  c[9] =   etak*2*mu*(gamma/beta -1)                                 	  ;\n"
<<"  c[10]=   etak*2*mu*dt*((1.-2*beta)/2./beta -(1.-gamma))            	  ;\n"
<<"	 									   \n";

if(TimeDiscretization=="central-difference")writemeshParameters
<<"  c[0] =   rho/(dt*dt) + etam*rho*gamma/dt        	  			  ;\n"
<<"  c[1] =   lambda + lambda*etak*gamma/dt               	  		  ;\n"
<<"  c[2] =   2.*mu + 2.*mu*etak*gamma/dt                 	  		  ;\n"
<<"  c[3] =   rho/dt - etam*rho*(1.-gamma)            	  			  ;\n"
<<"  c[4] =   rho*( 1./2.  - etam*dt*(1.-gamma/2))  				  ;\n"
<<"  c[5] =  -lambda*etak*gamma/dt                		  	  	  ;\n"
<<"  c[6] =  -2.*mu*etak*gamma/dt                 		  	  	  ;\n"
<<"  c[7] =   etak*lambda*(gamma - 1)                              	  	  ;\n"
<<"  c[8] =   etak*lambda*dt*(1./2. - (1.-gamma))         	  		  ;\n"
<<"  c[9] =   etak*2*mu*(gamma -1)                                 	  	  ;\n"
<<"  c[10]=   etak*2*mu*dt*(1./2. -(1.-gamma))            	  		  ;\n"
<<"	 									   \n";

if(TimeDiscretization=="hht-alpha")writemeshParameters
<<"  c[0] =   rho/(beta*dt*dt) + etam*rho*gamma*(1-alpf)/beta/dt        	  ;\n"
<<"  c[1] =   lambda*(1.-alpf) + lambda*etak*gamma*(1-alpf)/beta/dt               ;\n"
<<"  c[2] =   2.*mu*(1.-alpf) + 2.*mu*etak*gamma*(1-alpf)/beta/dt                 ;\n"
<<"  c[3] =   rho/beta/dt - etam*rho*(1-gamma*(1-alpf)/beta)            	  ;\n"
<<"  c[4] =   rho*( (1.-2.*beta)/2./beta  - etam*dt*(1.-alpf)*(1.-gamma/2/beta))  ;\n"
<<"  c[5] =   lambda*alpf -    lambda*etak*gamma*(1.-alpf)/beta/dt                ;\n"
<<"  c[6] =   2*mu*alpf   -    2.*mu*etak*gamma*(1.-alpf)/beta/dt                 ;\n"
<<"  c[7] =   etak*lambda*(gamma*(1.-alpf)/beta - 1)                              ;\n"
<<"  c[8] =   etak*lambda*dt*(1.-alpf)*((1.-2*beta)/2./beta - (1.-gamma))         ;\n"
<<"  c[9] =   etak*2*mu*(gamma*(1.-alpf)/beta -1)                                 ;\n"
<<"  c[10]=   etak*2*mu*dt*(1.-alpf)*((1.-2*beta)/2./beta -(1.-gamma))            ;\n"
<<"	 									   \n";

if(plotAll || plotTime)writemeshParameters
<<"										   \n"
<<"//==============================================================================\n"
<<"//  ------- Paraview plotting parameters -------				   \n"
<<"//==============================================================================\n"
<<"										   \n"
//<<"  int[int] vtuorder = [1]             ;  // Solution export order  	   \n"
<<"  string   namedata = \"U\"              ;  // Name of export data		   \n"
<<"  bool     withsur  = true             ;  // With surfaces	   		   \n"
<<"  int      iterout  = 0                ;  // Loop counter			   \n";

if(PostProcess!="v" & PostProcess!="a" & PostProcess!="uva")writemeshParameters
<<"  int[int] vtuorder = [1]                ;  // Solution export order            \n";

if(PostProcess=="v" || PostProcess=="a")writemeshParameters
<<"  int[int] vtuorder = [1,1]              ;  // Solution export order  	   \n";

if(PostProcess=="uva")writemeshParameters
<<"  int[int] vtuorder = [1,1,1]            ;  // Solution export order  	   \n";

if(plotAll)if(!Sequential)writemeshParameters
<<"										   \n"
<<"  if(mpirank==0)system(\"mkdir -p VTUs\");	    	   			   \n";

if(plotAll)if(!Sequential)writemeshParameters
<<"										   \n"
<<"  if(mpirank==0)system(\"rm -rf VTUs/Solution_\"+mpisize+\".pvd\");	    	   \n";

if(plotTime)writemeshParameters
<<"  string   namevtu  = \"VTUs/Result\"    ;  // File name			   \n"
<<"  exportBegin(					           		   \n"
<<(!Sequential ? "              namevtu, mpiCommWorld" : "              namevtu"    )
<<" )					           		 		   \n"	
<<"  					           				   \n";

if(pipegnu){writemeshParameters
<<"										   \n"
<<"//==============================================================================\n"
<<"// ------- Gnuplot pipeing parameters  -------				   \n"
<<"//==============================================================================\n"
<<"										   \n"
<<(Sequential ? "  real Ek,El,Ec;" : "  real[int] E(3),EG(3);"			    )
<<"  // To store damping energy		   					   \n"
<<"										   \n"
<<(Sequential ? "" : "  if(mpirank==0)\n"	   				    )
<<"  system(\"rm energies.data\");						   \n";

if(!supercomp)writemeshParameters
<<"										   \n"
<<"  pstream pgnuplot(\"gnuplot -p\");						   \n"
<<(Sequential ? "" : "  if(mpirank==0)\n"	   				    )
<<"  pgnuplot 									   \n"
<<"  <<\" set title\\\"E-Energy\t E-Elastic\tT-Total\tK-Kinetic\\\";	\\n\"	   \n"
<<"  <<\" set termoption font \\\"Arial-Bold,20\\\";    	    \t\t\\n\"	   \n"
<<"  <<\" set format x \\\"%.1t\\\";				    \t\t\\n\"      \n"
<<"  <<\" set xlabel \\\" Time     \\\";			    \t\t\\n\"	   \n"
<<"  <<\" set ylabel \\\" Energies \\\";			    \t\t\\n\"  	   \n"
<<"  <<\" set grid x y; set key left;					\\n\"; 	   \n"
<<"										   \n";
}

}

if(soildynamics){writemeshParameters
<<"	 									   \n"
<<"//==============================================================================\n"
<<"// ------- Variational formulation constant parameters -------  	   	   \n"
<<"//==============================================================================\n"
<<"	 									   \n"
<<"  real[int] c(10);								   \n"
<<"	 									   \n";

if(TimeDiscretization=="generalized-alpha")writemeshParameters
<<"  c[0] =   rho*(1.-alpm)/(beta*dt*dt)                                          ;\n"
<<"  c[1] =   lambda*(1.-alpf)                                                    ;\n"
<<"  c[2] =   2.*mu*(1.-alpf)                                                     ;\n"
<<"  c[3] =   rho*(1.-alpm)/(beta*dt)                                             ;\n"
<<"  c[4] =   rho*((1.-alpm)/2./beta -1.)                                         ;\n"
<<"  c[5] =   lambda*alpf                                                         ;\n"
<<"  c[6] =   2*mu*alpf                                                           ;\n"
<<"  c[7] =   rho*(1.-alpf)*gamma/beta/dt                                         ;\n"
<<"  c[8] =   rho*(1.-gamma*(1-alpf)/beta)                                        ;\n"
<<"  c[9] =   rho*(1.-alpf)*dt*(1.-gamma/(2.*beta))                               ;\n"
<<"	 									   \n";

if(TimeDiscretization=="newmark-beta")writemeshParameters
<<"  c[0] =   rho/(beta*dt*dt)                                          	  ;\n"
<<"  c[1] =   lambda                                                    	  ;\n"
<<"  c[2] =   2.*mu                                                     	  ;\n"
<<"  c[3] =   rho/(beta*dt)                                             	  ;\n"
<<"  c[4] =   rho*(1./2./beta -1.)                                         	  ;\n"
<<"  c[5] =   0.                                                         	  ;\n"
<<"  c[6] =   0.                                                           	  ;\n"
<<"  c[7] =   rho*gamma/beta/dt                                         	  ;\n"
<<"  c[8] =   rho*(1.-gamma/beta)                                        	  ;\n"
<<"  c[9] =   rho*dt*(1.-gamma/(2.*beta))                               	  ;\n"
<<"	 									   \n";

if(TimeDiscretization=="central-difference")writemeshParameters
<<"  c[0] =   rho/(dt*dt)                                          	  	  ;\n"
<<"  c[1] =   lambda                                                    	  ;\n"
<<"  c[2] =   2.*mu                                                     	  ;\n"
<<"  c[3] =   rho/(dt)                                             	  	  ;\n"
<<"  c[4] =   rho*(1./2. -1.)                                         	  	  ;\n"
<<"  c[5] =   0.                                                         	  ;\n"
<<"  c[6] =   0.                                                           	  ;\n"
<<"  c[7] =   rho*gamma/dt                                         	  	  ;\n"
<<"  c[8] =   rho*(1.-gamma)                                        	  	  ;\n"
<<"  c[9] =   rho*dt*(1.-gamma/2.)                               	  	  ;\n"
<<"	 									   \n";

if(TimeDiscretization=="hht-alpha")writemeshParameters
<<"  c[0] =   rho/(beta*dt*dt)                                          	  ;\n"
<<"  c[1] =   lambda*(1.-alpf)                                                    ;\n"
<<"  c[2] =   2.*mu*(1.-alpf)                                                     ;\n"
<<"  c[3] =   rho/(beta*dt)                                             	  ;\n"
<<"  c[4] =   rho*(1./2./beta -1.)                                         	  ;\n"
<<"  c[5] =   lambda*alpf                                                         ;\n"
<<"  c[6] =   2*mu*alpf                                                           ;\n"
<<"  c[7] =   rho*(1.-alpf)*gamma/beta/dt                                         ;\n"
<<"  c[8] =   rho*(1.-gamma*(1-alpf)/beta)                                        ;\n"
<<"  c[9] =   rho*(1.-alpf)*dt*(1.-gamma/(2.*beta))                               ;\n"
<<"	 									   \n";

if(plotAll || plotTime)writemeshParameters
<<"										   \n"
<<"//==============================================================================\n"
<<"//  ------- Paraview plotting parameters -------				   \n"
<<"//==============================================================================\n"
<<"										   \n";

if(Sequential)writemeshParameters
//<<"  int[int] vtuorder = [1]                ;  // Solution export order            \n"
<<"  string   namedata = \"U\"              ;  // Name of export data		   \n"
<<"  bool     withsur  = true             ;  // With surfaces	   		   \n"
<<"  int      iterout  = 0                ;  // Loop counter			   \n";

if(PostProcess!="v" & PostProcess!="a" & PostProcess!="uva")writemeshParameters
<<"  int[int] vtuorder = [1]                ;  // Solution export order            \n";

if(PostProcess=="v" || PostProcess=="a")writemeshParameters
<<"  int[int] vtuorder = [1,1]              ;  // Solution export order  	   \n";

if(PostProcess=="uva")writemeshParameters
<<"  int[int] vtuorder = [1,1,1]            ;  // Solution export order  	   \n";

if(plotAll)if(!Sequential)writemeshParameters
<<"										   \n"
<<"  if(mpirank==0)system(\"mkdir -p VTUs\");	    	   			   \n";

if(plotTime)writemeshParameters
<<"  string   namevtu  = \"VTUs/Result\"    ;  // File name			   \n"
<<"  exportBegin(					           		   \n"
<<(!Sequential ? "              namevtu, mpiCommWorld" : "              namevtu"    )
<<" )					           		 		   \n"	
<<"  					           				   \n";

}

if(pipegnu)if(quasistatic){writemeshParameters 
<<"										   \n"
<<"//==============================================================================\n"
<<"// ------- Gnuplot pipeing parameters ------					   \n"
<<"//==============================================================================\n"
<<"										   \n"
<<(Sequential ? "" : "  if(mpirank==0)\n"	   				    )
<<"  system(\"rm output.data\");						   \n"
<<"										   \n";

if(!supercomp)writemeshParameters
<<"  pstream pgnuplot(\"gnuplot -p\");						   \n"
<<(Sequential ? "" : "  if(mpirank==0)\n"	   				    )
<<"  pgnuplot 									   \n"
<<"  <<\" set title  \\\" Force-Displacement-Curve\\\";		\\n\"              \n"
<<"  <<\" set termoption font \\\"Arial-Bold,20\\\";		\\n\"		   \n"
<<"  <<\" set xlabel \\\" Displacement \\\";			\\n\"	   	   \n"
<<"  <<\" set ylabel \\\" Force (N)\\\";			\\n\"  	  	   \n"
<<"  <<\" set grid x y;    set key left;			\\n\"; 	   	   \n";
}

} //-- [ostream terminator]  parameters.edp closed --//

cout << " .......................... Done \n";
