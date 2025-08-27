/**************************************************************************************
*                                                                                     *
*           This file is a part of PSD project                                        *
*                                                                                     *
*       -------------------------------------------------------------------           *
*                                                                                     *
*       Copyright 2019-2025 CEA/DES                                                   *
*                                                                                     *
*       Licensed under the Apache License, Version 2.0  (the "License");              *
*       you may not use this file except in compliance with the License.              *
*       You may obtain a copy of the License at                                       *
*                                                                                     *
*           http://www.apache.org/licenses/LICENSE-2.0                                *
*                                                                                     *
*       Unless required by applicable law or agreed to in writing, software           *
*       distributed under the License is distributed on an  "AS IS"  BASIS,           *
*       WITHOUT  WARRANTIES  OR  CONDITIONS  OF  ANY  KIND,  either express           *
*       or implied. See  the License  for  the  specific language governing           *
*       permissions and limitations under the License.                                *
*                                                                                     *
*       -------------------------------------------------------------------           *
*                                                                                     *
*                                                                                     *
* Comment: This support file is  responsible for generating MeshAndFespace.edp which  *
*          is responsible for loading the mesh and defining finite element spaces.    *
*                                                                                     *
**************************************************************************************/

writeHeader;

codeSnippet R""""(

//==============================================================================
// ------- The finite element mesh name from commandline-------
//==============================================================================

  ThName = getARGV( "-mesh" , ThName );

//==============================================================================
// ------- Error message if wrong mesh detected -------
//==============================================================================

  checkmesh(ThName);

)"""";


if(Sequential){
codeSnippet R""""(

//==============================================================================
// ------- The finite element mesh -------
// ----------------------------------------------------------------------------
//  Th        : Finite element mesh
//==============================================================================

  startProcedure("Mesh Loading",t0)

  meshN Th;
  loadfemesh(Th,ThName);
  perfromRCMreordering(Th);

  endProcedure  ("Mesh Loading",t0)

//==============================================================================
// ------- The finite element space  -------
// ----------------------------------------------------------------------------
//  Vh        : Mixed finite element space  for displacement
//==============================================================================

 fespace Vh   ( Th , Pk );

)"""";
}

if(Sequential){

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
 "  loadfemesh(Th,ThName);                                                        \n"
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
  "  loadfemesh(Th,ThName);                                                        \n"
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
  "  loadfemesh(Th,ThName);                                                        \n"
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
