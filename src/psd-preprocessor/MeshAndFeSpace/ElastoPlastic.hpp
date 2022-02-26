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

codeSnippet R""""(

//==============================================================================
// ------- The finite element mesh name from commandline-------
//==============================================================================

  ThName = getARGV( "-mesh" , ThName );

//==============================================================================
// ------- Error message if wrong mesh detected -------
//==============================================================================

  if( ThName.find(".mesh") == -1 &&
      ThName.find(".msh")  == -1 &&
      ThName.find(".vtk")  == -1
    ){
      cout << "  ****************** ERROR ********************* \n"
           << "                                                 \n"
           << "  PSD only accepts the following mesh formats    \n"
           << "     1) .msh   Gmsh's  .msh  format version 2    \n"
           << "     2) .mesh  INRIA's medit format              \n"
           << "     3) .vtk   VTK's unstructured mesh format    \n"
           << "                                                 \n"
           << "  ****************** ERROR ********************* \n";
      exit(11111);
  }

)"""";

if(Sequential){
codeSnippet R""""(

//==============================================================================
// ------- The finite element mesh -------
// ----------------------------------------------------------------------------
//  Th        : Finite element mesh
//==============================================================================

  startProcedure("Mesh Loading",t0)

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

 if(spc==2)
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
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element space  -------                                    \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  Ih       : Quadratur finite element space  for internal state variables     \n"
 "//             FEQF2 implies 3 dof for a triangular cell in the mesh A vec-     \n"
 "//             torial FEM space is built  with  5 components.  To elaborate     \n"
 "//             First 4 are elastic stains [Exx, Eyy, Ezz, Exy] + 1 plasticity   \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace Ih  ( Th ,[ FEQF2, FEQF2, FEQF2, FEQF2, FEQF2 ]);                      \n"
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

 if(spc==3)
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
 "                                                                                \n"
 "                                                                                \n"
 "//==============================================================================\n"
 "// ------- The finite element space  -------                                    \n"
 "// ---------------------------------------------------------------------------- \n"
 "//  Ih       : Quadratur finite element space  for internal state variables     \n"
 "//             FEQF2 implies 3 dof for a triangular cell in the mesh A vec-     \n"
 "//             torial FEM space is built  with  5 components.  To elaborate     \n"
 "//             First 4 are elastic stains [Exx, Eyy, Ezz, Exy] + 1 plasticity   \n"
 "//==============================================================================\n"
 "                                                                                \n"
 " fespace Ih  ( Th ,[ FEQF2, FEQF2, FEQF2, FEQF2, FEQF2 ]);                      \n"
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
 "  perfromRCMreordering(Th);                                                     \n";

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
