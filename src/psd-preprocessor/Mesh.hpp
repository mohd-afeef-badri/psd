//=====================================================================================
// ------ Building the MeshPartitioning.edp or Mesh.edp file ------ 
//=====================================================================================

cout << " building MeshAndFeSpace.edp"; 
 
{ofstream  writemeshPartitioning("MeshAndFeSpace.edp");

writemeshPartitioning
<<"                                                                                                \n"
<<"/**************************Variational formulation******************************                \n"
<<"*                                                                              *                \n"
<<"* Note!!! This file is  generated  by  running  PSD PreProcessor  Do  not edit *                \n"
<<"*         in order to  control this  file please change flag arguments of  the *                \n"
<<"*         PSD_PreProcess, details of which are present in PSD_PreProcess or in *                \n"
<<"*         the README.MD file.                                                  *                \n"
<<"*                                                                              *                \n"
<<"*******************************************************************************/                \n"
<<"                                                                                \n";

//-----------------------------SEQUENTIAL------------------------------------------//

if(Sequential){writemeshPartitioning
<<"                                                                                \n"
<<"//==============================================================================\n"
<<"// ------- The finite element mesh -------                                      \n"
<<"//==============================================================================\n"
<<"                                                                                \n"
<<(timelog  ? "  timerbegin(\"Solver\",t1)\n" : ""                                  )
<<(timelog  ? "  timerbegin(\"Mesh Loading\",t0)\n" : ""                            )
<<"  load \"gmsh\"					// Load  gmsh                                  \n"
<<"  meshN Th = gmshloadN(\"\"+ThName+\".msh\");	// Mesh loaded                 \n"
<<(RCM ? "  Th=trunc(Th, 1, renum=1);\n" : ""                                       )
<<(timelog ? "  timerend  (\"Mesh Loading\",t0)\n" : ""                             )
<<"                                                                                \n"
<<"//==============================================================================\n"
<<"// ------- The finite element spaces -------                                    \n"
<<"//==============================================================================\n"
<<"                                                                                \n"
<<" fespace Vh   ( Th , Pk );			// Mixed FE space (displacemnt)            \n";

if(nonlinear)writemeshPartitioning
<<" fespace Vh1  ( Th , Zk );			// Damage field	FE space                   \n";

if(nonlinear)if(energydecomp)writemeshPartitioning
<<" fespace Wh0  ( Th , P0 );			// Energy decomposition field              \n";

}

//-------------------------------PARALLEL------------------------------------------//

if(!Sequential){writemeshPartitioning
<<"                                                                                \n"
<<"//==============================================================================\n"
<<"// ------- The finite element mesh -------                                      \n"
<<"//==============================================================================\n"
<<"                                                                                \n"
<<" meshN   Th = DummyMesh;			// This is a dummy mesh for now                \n"
<<"                                                                                \n"
<<"//==============================================================================\n"
<<"// ------- The finite element spaces -------                                    \n"
<<"//==============================================================================\n"
<<"                                                                                \n"
<<" fespace Vh     ( Th , Pk );			// Local mixed FE space                    \n";

if(nonlinear)if(!vectorial)writemeshPartitioning
<<" fespace Vh1    ( Th , Zk );			// Damage field	FE space                   \n";

if(nonlinear)if(energydecomp)writemeshPartitioning
<<" fespace Wh0    ( Th , P0 );			// Energy decomposition field              \n";

if(nonlinear)if(vectorial)if(debug || plotAll)writemeshPartitioning
<<" fespace VhPlt  ( Th , P1 );			// Damage field	FE space                   \n";

if(quasistatic)writemeshPartitioning
<<" fespace Wh0    ( Th , P0 );			// stress/strain/damage FE space           \n";

if(quasistatic)if(useGFP)writemeshPartitioning
<<" fespace VhStr  ( Th , Sk );			// stress/strain/damage FE space           \n";

writemeshPartitioning
<<"                                                                                \n"
<<"//==============================================================================\n"
<<"// ---- Function for building the restriction matrix and partion of unity ----  \n"
<<"//==============================================================================\n"
<<"                                                                                \n"
<<" func int PartThAndBuildCommunication(){                                        \n"
<<"                                                                                \n"
<<"  load \"gmsh\"                                      // Load meshes from gmsh   \n"
<<"  Th = gmshloadN(\"\"+ThName+\".msh\");    		// Global mesh loaded          \n"
<<(RCM ? "  Th=trunc(Th, 1, renum=1);\n" : ""                                       );

if(!nonlinear)writemeshPartitioning
<<"                                                                                \n"
<<"  PETScMPIBuild(                                                                \n"
<<"		   Th				, // Local  mesh                                       \n"
<<"		   getARGV( \"-split\" , 1 )	, // Split factor                          \n"
<<"		   restrictionIntersectionP	, // Restriction matrix                        \n"
<<"		   DP				, // Partition of unity                                \n"
<<"		   Pk				, // Vectorial FE space                                \n"
<<"		   mpiCommWorld			  // MPI world                                     \n"
<<"		  )                                                                        \n";

if(nonlinear)if(!vectorial)writemeshPartitioning
<<"                                                                                \n"
<<"  fespace Ph(Th, P0);                                                           \n"
<<"  	     Ph part;                                                              \n"
<<"                                                                                \n"
<<"                                                                                \n"
<<"  if(mpirank == 0)                                                              \n"
<<"	partitionerSeq(part[], Th, mpisize);                                           \n"
<<"                                                                                \n"
<<"  partitionerPar(part[], Th, mpiCommWorld, mpisize);                            \n"
<<"                                                                                \n"
<<"  PETScMPIBuildWithPartitioning(                                                \n"
<<"		   Th				, // Local  mesh                                       \n"
<<"		   part[]			, // Partitions                                        \n"
<<"		   getARGV( \"-split\" , 1 )	, // Split factor                          \n"
<<"		   restrictionIntersectionZ	, // Restriction matrix                        \n"
<<"		   DZ				, // Partition of unity                                \n"
<<"		   Zk				, // Vectorial FE space                                \n"
<<"		   mpiCommWorld			  // MPI world                                     \n"
<<"		  )                                                                        \n"
<<"                                                                                \n"
<<"  Th = gmshloadN(\"\"+ThName+\".msh\");    // Global mesh re-loaded             \n"
<<(RCM ? "  Th=trunc(Th, 1, renum=1);\n" : ""                                      )
<<"                                                                                \n"
<<"  PETScMPIBuildEdgeWithPartitioning(                                            \n"
<<"		   Th				, // Local  mesh                                       \n"
<<"		   part[]			, // Partitions                                        \n"
<<"		   getARGV( \"-split\" , 1 )	, // Split factor                          \n"
<<"		   restrictionIntersectionP	, // Restriction matrix                        \n"
<<"		   DP				, // Partition of unity                                \n"
<<"		   Pk				, // Vectorial FE space                                \n"
<<"		   mpiCommWorld			, // MPI world                                     \n"
<<"		   Pk				, // Vectorial FE space                                \n"
<<"		   def2				, // Scalar definition                                 \n"
<<"		   init2		  	  // Scalar initilization                              \n"
<<"		  )                                                                        \n";

if(nonlinear)if(vectorial)writemeshPartitioning
<<"                                                                                \n"
<<"  PETScMPIBuild(                                                                \n"
<<"		   Th				, // Local  mesh                                       \n"
<<"		   getARGV( \"-split\" , 1 )	, // Split factor                          \n"
<<"		   restrictionIntersectionP	, // Restriction matrix                        \n"
<<"		   DP				, // Partition of unity                                \n"
<<"		   Pk				, // Vectorial FE space	   	                           \n"
<<"		   mpiCommWorld			  // MPI world                                     \n"
<<"		  )                                                                        \n"
<<"                                                                                \n";

writemeshPartitioning
<<"                                                                                \n"
<<"  return 0;                                                                     \n"
<<"                                                                                \n"
<<" }                                                                              \n"
<<"                                                                                \n"
<<(timelog ? "  MPItimerbegin(\"Solver\",t1)\n" : "" 	         	 	    )
<<(timelog ? "  if(mpirank==0)cout<<\"\"<<endl;\n" : ""          	 	    )
<<(timelog ? "  MPItimerbegin(\"Mesh Partitioning\",t0)\n" : ""           	    )
<<"  PartThAndBuildCommunication();						   \n"
<<(timelog ? "  MPItimerend(\"Mesh Partitioning\",t0)\n" : " "           	    )
<<"                                                                                \n"
<<"                                                                                \n";

}

} //-- [ostream terminator]  meshpartitioning.edp closed --//

cout << " ........................... Done \n";