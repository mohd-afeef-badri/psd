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


if(!top2vol)
 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element mesh name from commandline-------                 \n"
 "//==============================================================================\n"
 "                                                                                \n"
 "  ThName = getARGV( \"-mesh\" , ThName );                                       \n"
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- Error message if wrong mesh detected -------                         \n"
 "//==============================================================================\n"
 "                                                                                \n" 
 "  if(ThName.find(\".mesh\") == -1 && ThName.find(\".msh\") == -1)               \n"
 "   cout <<\"INVALID MESH: PSD only accepts '.msh' or '.mesh' formats\"<< endl;  \n";        
   
if(Sequential){
 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element mesh -------                                      \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  Th        : Finite element mesh                                             \n"
 "//==============================================================================\n"
 "                                                                                \n"
 <<(timelog  ? "  timerbegin(\"Solver\",t1)\n" : ""                               )
 <<(timelog  ? "  timerbegin(\"Mesh Loading\",t0)\n" : ""                         )<<
 "                                                                                \n" 
 "  meshN Th;                                                                     \n"
 "                                                                                \n"  
 "  if(ThName.find(\".msh\") > -1)                                                \n" 
 "    {                                                                           \n"   
 "      load \"gmsh\"                                                             \n"
 "      Th = gmshloadN(ThName);                                                   \n"
 "    }                                                                           \n"
 "  if(ThName.find(\".mesh\") > -1)                                               \n" 
 "    {                                                                           \n"   
 "      Th = readmeshN(ThName);                                                   \n"
 "    }                                                                           \n"
 "                                                                                \n" 
 <<(RCM ? "  Th=trunc(Th, 1, renum=1);\n" : ""                                    )
 <<(timelog ? "  timerend  (\"Mesh Loading\",t0)\n" : ""                          )<<
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element space  -------                                    \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  Vh        : Mixed finite element space  for displacement                    \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace Vh   ( Th , Pk );                                                      \n";

 if(Prblm=="damage" && Model=="hybrid-phase-field")
  writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element space  -------                                    \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  Vh1       : P1 finite element space  for damage                             \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace Vh1  ( Th , Zk );                                                      \n";

 if(Prblm=="damage" && Model=="hybrid-phase-field" && energydecomp)
  writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element spaces -------                                    \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  Wh0       : P0 finite element space  for damage decomposition               \n"
 "//  Sh0       : P0 finite element space  for stress/strain decomposition        \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace Wh0  ( Th , P0 );            // Energy decomposition FE space          \n"
 " fespace Sh0  ( Th , Sk );            // Strain vector FE space                 \n";

 if(Prblm=="damage" && Model=="Mazar")
  writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element space  -------                                    \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  Wh0       : P0 finite element space  for stress/strain/damage               \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace Wh0    ( Th , P0 );                                                    \n";

 if(Prblm=="damage" && Model=="Mazar" && useGFP)
  writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element space  -------                                    \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  VhStr     : P0 finite element space  for stress/strain/damage               \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace VhStr  ( Th , Sk );                                                    \n";

}

if(!Sequential){
 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element mesh -------                                      \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  Th        : Finite element mesh                                             \n"
 "//  DummyMesh : Dummy mesh i.e, square for 2D and cube for 3D                   \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " meshN   Th = DummyMesh;                                                        \n"
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element spaces -------                                    \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  Vh        : Mixed finite element space  for displacement                    \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace Vh     ( Th , Pk );                                                    \n";

 if(Prblm=="damage" && Model=="hybrid-phase-field" && !vectorial)
  writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element space  -------                                    \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  Vh1       : P1 finite element space  for damage                             \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace Vh1    ( Th , Zk );                                                    \n";

 if(Prblm=="damage" && Model=="hybrid-phase-field" && energydecomp)
  writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element spaces -------                                    \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  Wh0       : P0 finite element space  for damage decomposition               \n"
 "//  Sh0       : P0 finite element space  for stress/strain decomposition        \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace Wh0    ( Th , P0 );                                                    \n"
 " fespace Sh0    ( Th , Sk );                                                    \n";

 if(Prblm=="soildynamics" && Model=="Hujeux")
  writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element spaces -------                                    \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  Q3vh      : Quadrature 3  vector finite element space                       \n"
 "//  Q25vh     : Quadrature 25 vector finite element space                       \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace Q3vh   ( Th , Sk );                                                    \n"
 " fespace Q25vh  ( Th , Ik );                                                    \n";

 if(Prblm=="damage" && Model=="hybrid-phase-field" && vectorial)
  writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element space  -------                                    \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  Vh1       : P1 finite element space  for damage                             \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace Vh1  ( Th , P1 );                                                      \n";

 if(Prblm=="damage" && Model=="Mazar")
  writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element space  -------                                    \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  Wh0       : P0 finite element space  for stress/strain/damage               \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace Wh0    ( Th , P0 );                                                    \n";

 if(Prblm=="damage" && Model=="Mazar" && useGFP)
  writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element space  -------                                    \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  VhStr     : P0 finite element space  for stress/strain/damage               \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace VhStr  ( Th , Sk );                                                    \n";

 if(!top2vol)
 {
 writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ---- Function for building the restriction matrix and partiton of unity ----  \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " func int PartThAndBuildCommunication(){                                        \n"
 "                                                                                \n"
 "  if(ThName.find(\".msh\") > -1)                                                \n" 
 "    {                                                                           \n"   
 "      load \"gmsh\"                                                             \n"
 "      Th = gmshloadN(ThName);                                                   \n"
 "    }                                                                           \n"
 "  if(ThName.find(\".mesh\") > -1)                                               \n" 
 "    {                                                                           \n"   
 "      Th = readmeshN(ThName);                                                   \n"
 "    }                                                                           \n"
 "                                                                                \n"
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

 if(Prblm=="damage" && Model=="hybrid-phase-field")
 if(!vectorial) 
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
  "  if(ThName.find(\".msh\") > -1)                                                \n" 
  "    {                                                                           \n"   
  "      Th = gmshloadN(ThName);                                                   \n"
  "    }                                                                           \n"
  "  if(ThName.find(\".mesh\") > -1)                                               \n" 
  "    {                                                                           \n"   
  "      Th = readmeshN(ThName);                                                   \n"
  "    }                                                                           \n"
  "                                                                                \n"  
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

 if(Prblm=="damage" && Model=="hybrid-phase-field")
 if(vectorial && constrainHPF) 
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
  "                                                                                \n"
  "  if(ThName.find(\".msh\") > -1)                                                \n" 
  "    {                                                                           \n"   
  "      Th = gmshloadN(ThName);                                                   \n"
  "    }                                                                           \n"
  "  if(ThName.find(\".mesh\") > -1)                                               \n" 
  "    {                                                                           \n"   
  "      Th = readmeshN(ThName);                                                   \n"
  "    }                                                                           \n"
  "                                                                                \n" 
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

 if(Prblm=="damage" && Model=="hybrid-phase-field")
 if(vectorial && !constrainHPF)  
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
 <<(timelog ? "  timerbegin(\"Solver\",t1)\n" : ""                             )
 <<(timelog ? "  if(mpirank==0)cout<<\"\"<<endl;\n" : ""                          )
 <<(timelog ? "  timerbegin(\"Mesh Partitioning\",t0)\n" : ""                  )<<
 "  PartThAndBuildCommunication();                                                \n"
 <<(timelog ? "  timerend(\"Mesh Partitioning\",t0)\n" : " "                   )<<
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
 "                 pointsx=PcNx,                                                  \n"
 "                 pointsy=PcNy,                                                  \n"
 "                 pointsz=PcNz,                                                  \n"
 "                 zdepth=Dptz,                                                   \n"
 "                 partx=PartX,                                                   \n"  
 "                 party=PartY,                                                   \n"  
 "                 partz=PartZ                                                    \n"
 "              );                                                                \n"
 "                                                                                \n"
 "  mpiBarrier(mpiCommWorld);                                                     \n"
 "                                                                                \n"   
 "  topiivolmesh(                                                                 \n"
 "                \"./top-ii-vol-meshes/Pc-strip\",                               \n"
 "                outfile=\"./top-ii-vol-meshes/top2volmesh\",                    \n"
 "                pointsz=PcNz,                                                   \n"
 "                zdepth=Dptz,                                                    \n"
 "                partx=PartX,                                                    \n"  
 "                party=PartY,                                                    \n"  
 "                partz=PartZ                                                     \n" 
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
