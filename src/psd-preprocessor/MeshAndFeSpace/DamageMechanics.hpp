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

writeHeader;

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
 "  startProcedure(\"Solver\",t1)                                                 \n"
 "  startProcedure(\"Mesh Loading\",t0)                                           \n"
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
 "  perfromRCMreordering(Th);                                                     \n"
 "  endProcedure  (\"Mesh Loading\",t0)                                           \n"
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element space  -------                                    \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  Vh        : Mixed finite element space  for displacement                    \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace Vh   ( Th , Pk );                                                      \n";

 if(Model=="hybrid_phase_field")
  writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element space  -------                                    \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  Vh1       : P1 finite element space  for damage                             \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace Vh1  ( Th , Zk );                                                      \n";

 if(Model=="hybrid_phase_field" && energydecomp)
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

 if(Model=="Mazar")
  writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element space  -------                                    \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  Wh0       : P0 finite element space  for stress/strain/damage               \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace Wh0    ( Th , P0 );                                                    \n";

 if(Model=="Mazar" && useGFP)
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
 
 

 if(Model=="hybrid_phase_field" && !vectorial)
  writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element space  -------                                    \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  Vh1       : P1 finite element space  for damage                             \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace Vh1    ( Th , Zk );                                                    \n";

 if(Model=="hybrid_phase_field" && energydecomp)
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


 if(Model=="hybrid_phase_field" && vectorial)
  writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element space  -------                                    \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  Vh1       : P1 finite element space  for damage                             \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace Vh1  ( Th , P1 );                                                      \n";

 if(Model=="Mazar")
  writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element space  -------                                    \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  Wh0       : P0 finite element space  for stress/strain/damage               \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace Wh0    ( Th , P0 );                                                    \n";

 if(Model=="Mazar" && useGFP)
  writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element space  -------                                    \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  VhStr     : P0 finite element space  for stress/strain/damage               \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace VhStr  ( Th , Sk );                                                    \n";


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
 "  perfromRCMreordering(Th);                                                     \n";

 if(Model=="Mazar")
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

 if(Model=="hybrid_phase_field")
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
  "  perfromRCMreordering(Th);                                                     \n"
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

 if(Model=="hybrid_phase_field")
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
  "  perfromRCMreordering(Th);                                                     \n"
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

 if(Model=="hybrid_phase_field")
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
 "  startProcedure(\"Mesh Partitioning\",t0)                                      \n"
 "  PartThAndBuildCommunication();                                                \n"
 "  endProcedure(\"Mesh Partitioning\",t0)                                        \n"
 "                                                                                \n"
 "                                                                                \n";

}
