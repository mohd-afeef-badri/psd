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

 if(!fastmethod && spc==2)
  writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element space  -------                                    \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  Vh1       : Quadratur finite element space  for material tensor             \n"
 "//              FEQF2 implies 3 dof for triagular cell in the mesh.             \n"
 "//              A vectorial FEM space is built with 6 components                \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace Qh  ( Th , [FEQF2, FEQF2, FEQF2,                                       \n"
 "                            FEQF2, FEQF2,                                       \n"
 "                                   FEQF2] );                                    \n";

 if(!fastmethod && spc==3)
  writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element space  -------                                    \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  Qh       : Quadratur finite element space  for material tensor              \n"
 "//             FEQF23d implies 4 dof for a tetra cell in the mesh               \n"
 "//             A vectorial FEM space is built with 21 components                \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace Qh ( Th, [ FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,       \n"
 "                             FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,       \n"
 "                                      FEQF23d, FEQF23d, FEQF23d, FEQF23d,       \n"
 "                                               FEQF23d, FEQF23d, FEQF23d,       \n"
 "                                                        FEQF23d, FEQF23d,       \n"
 "                                                                 FEQF23d] );    \n";
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
 
 if(!fastmethod && spc==2)
  writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element space  -------                                    \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  Qh       : Quadratur finite element space  for material tensor              \n"
 "//             FEQF2 implies 3 dof for a triangular cell in the mesh            \n"
 "//             A vectorial FEM space is built with 6 components                 \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace Qh  ( Th ,[ FEQF2, FEQF2, FEQF2,                                       \n"
 "                            FEQF2, FEQF2,                                       \n"
 "                                   FEQF2] );                                    \n";
 
 if(useMfront && Model=="pseudo_nonlinear" && spc==2)
  writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element space  -------                                    \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  Sh       : Quadratur finite element space  for Stress/Strain tensor         \n"
 "//             FEQF2 implies 3 dof for a triangular cell in the mesh            \n"
 "//             A vectorial FEM space is built with 3 components                 \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace Sh  ( Th ,[ FEQF2, FEQF2, FEQF2]);                                     \n"
 "                                                                                \n";
 
 if(!fastmethod && spc==3)
  writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element space  -------                                    \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  Qh       : Quadratur finite element space  for material tensor              \n"
 "//             FEQF23d implies 4 dof for a tetra cell in the mesh               \n"
 "//             A vectorial FEM space is built with 21 components                \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace Qh ( Th, [ FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,       \n"
 "                             FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,       \n"
 "                                      FEQF23d, FEQF23d, FEQF23d, FEQF23d,       \n"
 "                                               FEQF23d, FEQF23d, FEQF23d,       \n"
 "                                                        FEQF23d, FEQF23d,       \n"
 "                                                                 FEQF23d] );    \n";
 
 if(useMfront && Model=="pseudo_nonlinear" && spc==3)
  writeIt
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element space  -------                                    \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  Sh       : Quadratur finite element space  for Stress/Strain tensor         \n"
 "//             FEQF2 implies 4 dof for a tetraheron cell in the mesh            \n"
 "//             A vectorial FEM space is built with 6 components                 \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace Sh  ( Th ,[ FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d ]);   \n"
 "                                                                                \n"; 

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
