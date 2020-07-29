/**************************************************************************************
*                                                                                     *
* Author : Mohd Afeef BADRI                                                           *
* Email  : mohd-afeef.badri@cea.fr                                                    *
* Date   : 20/04/2020                                                                 *
* Type   : Support file                                                               *
*                                                                                     *
* Comment: This support file is  responsible for generating MeshAndFespace.edp which  *
*          is responsible for loading the mesh and defining finite element spaces.    *
*                                                                                     *
**************************************************************************************/

cout << " building MeshAndFeSpace.edp";

{ofstream  write("MeshAndFeSpace.edp");

writeHeader;

if(Sequential){
 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element mesh -------                                      \n"
 "//==============================================================================\n"
 "                                                                                \n"
 <<(timelog  ? "  timerbegin(\"Solver\",t1)\n" : ""                               )
 <<(timelog  ? "  timerbegin(\"Mesh Loading\",t0)\n" : ""                         )<<
 "  load \"gmsh\"                    // Load  gmsh                                \n"
 "  meshN Th = gmshloadN(\"\"+ThName+\".msh\");    // Mesh loaded                 \n"
 <<(RCM ? "  Th=trunc(Th, 1, renum=1);\n" : ""                                    )
 <<(timelog ? "  timerend  (\"Mesh Loading\",t0)\n" : ""                          )<<
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element spaces -------                                    \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace Vh   ( Th , Pk );            // Mixed FE space (displacemnt)           \n";

 if(Prblm=="damage" && Model=="hybrid-phase-field")
  writeIt
  " fespace Vh1  ( Th , Zk );            // Damage field    FE space              \n";

 if(Prblm=="damage" && Model=="hybrid-phase-field" && energydecomp)
  writeIt
  " fespace Wh0  ( Th , P0 );            // Energy decomposition FE space         \n"
  " fespace Sh0  ( Th , Sk );            // Strain vector FE space                \n";

 if(Prblm=="damage" && Model=="Mazar")
  writeIt
  " fespace Wh0    ( Th , P0 );            // stress/strain/damage FE space       \n";

 if(Prblm=="damage" && Model=="Mazar" && useGFP)
  writeIt
  " fespace VhStr  ( Th , Sk );            // stress/strain/damage FE space       \n";

}

if(!Sequential){
 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element mesh -------                                      \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " meshN   Th = DummyMesh;            // This is a dummy mesh for now             \n"
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element spaces -------                                    \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace Vh     ( Th , Pk );            // Local mixed FE space                 \n";

 if(Prblm=="damage" && Model=="hybrid-phase-field" && !vectorial)
  writeIt
  " fespace Vh1    ( Th , Zk );            // Damage field    FE space            \n";

 if(Prblm=="damage" && Model=="hybrid-phase-field" && energydecomp)
  writeIt
  " fespace Wh0    ( Th , P0 );            // Energy decomposition field          \n"
  " fespace Sh0    ( Th , Sk );            // Strain vector FE space              \n";

 if(Prblm=="soildynamics" && Model=="Hujeux")
  writeIt
  " fespace Q3vh   ( Th , Sk );            // Quadrature 3  vector FE space       \n"
  " fespace Q25vh  ( Th , Ik );            // Quadrature 25 vector FE space       \n";

 if(Prblm=="damage" && Model=="hybrid-phase-field" && vectorial)if(debug || plotAll)
  writeIt
  " fespace VhPlt  ( Th , P1 );            // Damage field    FE space            \n";

 if(Prblm=="damage" && Model=="Mazar")
  writeIt
  " fespace Wh0    ( Th , P0 );            // stress/strain/damage FE space       \n";

 if(Prblm=="damage" && Model=="Mazar" && useGFP)
  writeIt
  " fespace VhStr  ( Th , Sk );            // stress/strain/damage FE space       \n";

 if(!top2vol)
 {
 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ---- Function for building the restriction matrix and partion of unity ----  \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " func int PartThAndBuildCommunication(){                                        \n"
 "                                                                                \n"
 "  load \"gmsh\"                                      // Load meshes from gmsh   \n"
 "  Th = gmshloadN(\"\"+ThName+\".msh\");            // Global mesh loaded        \n"
 <<(RCM ? "  Th=trunc(Th, 1, renum=1);\n" : ""                                     );

 if(Prblm!="damage")
  writeIt
  "                                                                                \n"
  "  PETScMPIBuild(                                                                \n"
  "           Th                , // Local  mesh                                   \n"
  "           getARGV( \"-split\" , 1 )    , // Split factor                       \n"
  "           restrictionIntersectionP    , // Restriction matrix                  \n"
  "           DP                , // Partition of unity                            \n"
  "           Pk                , // Vectorial FE space                            \n"
  "           mpiCommWorld              // MPI world                               \n"
  "          )                                                                     \n";

 if(Prblm=="damage" && Model=="Mazar")
  writeIt
  "                                                                                \n"
  "  PETScMPIBuild(                                                                \n"
  "           Th                , // Local  mesh                                   \n"
  "           getARGV( \"-split\" , 1 )    , // Split factor                       \n"
  "           restrictionIntersectionP    , // Restriction matrix                  \n"
  "           DP                , // Partition of unity                            \n"
  "           Pk                , // Vectorial FE space                            \n"
  "           mpiCommWorld              // MPI world                               \n"
  "          )                                                                     \n";

 if(Prblm=="damage" && Model=="hybrid-phase-field" && !vectorial)
  writeIt
  "                                                                                \n"
  "  fespace Ph(Th, P0);                                                           \n"
  "           Ph part;                                                             \n"
  "                                                                                \n"
  "                                                                                \n"
  "  if(mpirank == 0)                                                              \n"
  "    partitionerSeq(part[], Th, mpisize);                                        \n"
  "                                                                                \n"
  "  partitionerPar(part[], Th, mpiCommWorld, mpisize);                            \n"
  "                                                                                \n"
  "  PETScMPIBuildWithPartitioning(                                                \n"
  "           Th                , // Local  mesh                                   \n"
  "           part[]            , // Partitions                                    \n"
  "           getARGV( \"-split\" , 1 )    , // Split factor                       \n"
  "           restrictionIntersectionZ    , // Restriction matrix                  \n"
  "           DZ                , // Partition of unity                            \n"
  "           Zk                , // Vectorial FE space                            \n"
  "           mpiCommWorld              // MPI world                               \n"
  "          )                                                                     \n"
  "                                                                                \n"
  "  Th = gmshloadN(\"\"+ThName+\".msh\");    // Global mesh re-loaded             \n"
  <<(RCM ? "  Th=trunc(Th, 1, renum=1);\n" : ""                                    )<<
  "                                                                                \n"
  "  PETScMPIBuildEdgeWithPartitioning(                                            \n"
  "           Th                , // Local  mesh                                   \n"
  "           part[]            , // Partitions                                    \n"
  "           getARGV( \"-split\" , 1 )    , // Split factor                       \n"
  "           restrictionIntersectionP    , // Restriction matrix                  \n"
  "           DP                , // Partition of unity                            \n"
  "           Pk                , // Vectorial FE space                            \n"
  "           mpiCommWorld            , // MPI world                               \n"
  "           Pk                , // Vectorial FE space                            \n"
  "           def2                , // Scalar definition                           \n"
  "           init2                // Scalar initilization                         \n"
  "          )                                                                     \n";

 if(Prblm=="damage" && Model=="hybrid-phase-field" && vectorial)
  writeIt
  "                                                                                \n"
  "  PETScMPIBuild(                                                                \n"
  "           Th                , // Local  mesh                                   \n"
  "           getARGV( \"-split\" , 1 )    , // Split factor                       \n"
  "           restrictionIntersectionP    , // Restriction matrix                  \n"
  "           DP                , // Partition of unity                            \n"
  "           Pk                , // Vectorial FE space                            \n"
  "           mpiCommWorld              // MPI world                               \n"
  "          )                                                                     \n"
  "                                                                                \n";

 writeIt
 "                                                                                \n"
 "  return 0;                                                                     \n"
 "                                                                                \n"
 " }                                                                              \n"
 "                                                                                \n"
 <<(timelog ? "  MPItimerbegin(\"Solver\",t1)\n" : ""                             )
 <<(timelog ? "  if(mpirank==0)cout<<\"\"<<endl;\n" : ""                          )
 <<(timelog ? "  MPItimerbegin(\"Mesh Partitioning\",t0)\n" : ""                  )<<
 "  PartThAndBuildCommunication();                                                \n"
 <<(timelog ? "  MPItimerend(\"Mesh Partitioning\",t0)\n" : " "                   )<<
 "                                                                                \n"
 "                                                                                \n";
 }
 if(top2vol)
 {
 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ---- creating a folder for top-ii-vol related files ----                     \n"
 "//==============================================================================\n"
 "                                                                                \n"
 "  if(mpirank==0)system(\"mkdir -p top-ii-vol-meshes\");                         \n"  
 "                                                                                \n"
 "//==============================================================================\n"
 "// ---- top-ii-vol point cloud partitioning + meshing ----                      \n"
 "//==============================================================================\n"
 "                                                                                \n"
 "  topiivolpart(                                                                 \n"
 "                 PcName,                                                        \n" 
 "                 outfile=\"./top-ii-vol-meshes/Pc-strip\",                      \n"
 "                 pointsx=32,                                                    \n" 
 "                 pointsy=29                                                     \n"  
 "              );                                                                \n"
 "                                                                                \n"   
 "  mpiBarrier(mpiCommWorld);                                                     \n" 
 "                                                                                \n" 
 "  topiivolmesh(                                                                 \n"
 "                \"./top-ii-vol-meshes/Pc-strip\",                               \n"
 "                outfile=\"./top-ii-vol-meshes/top2volmesh\",                    \n"
 "                pointsz=4,                                                      \n"
 "                zdepth=-1920.0                                                  \n"
 "              );                                                                \n"     
 "                                                                                \n"
 "                                                                                \n"
 "//==============================================================================\n"
 "// ---- Partitioned mesh reading and ghost reconstruction ----                  \n"
 "//==============================================================================\n"
 "                                                                                \n"
 "  Th=readmesh3(\"./top-ii-vol-meshes/top2volmesh_\"+mpirank+\".mesh\");         \n"
 "  reconstructDmesh(Th);                                                         \n"
 "                                                                                \n";       
 }  
}

} //-- [ostream terminator]  meshpartitioning.edp closed --//

cout << " ........................... Done \n";
