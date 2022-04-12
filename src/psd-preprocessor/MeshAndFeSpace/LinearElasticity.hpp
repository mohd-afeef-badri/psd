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


if(!fastmethod && spc==2)
codeSnippet R""""(

//==============================================================================
// ------- The finite element space  -------
// ----------------------------------------------------------------------------
//  Vh1       : Quadratur finite element space  for material tensor
//              FEQF2 implies 3 dof for triagular cell in the mesh.
//              A vectorial FEM space is built with 6 components
//==============================================================================

 fespace Qh  ( Th , [FEQF2, FEQF2, FEQF2,
                            FEQF2, FEQF2,
                                   FEQF2] );
)"""";


if(!fastmethod && spc==3)
codeSnippet R""""(

//==============================================================================
// ------- The finite element space  -------
// ----------------------------------------------------------------------------
//  Qh       : Quadratur finite element space  for material tensor
//             FEQF23d implies 4 dof for a tetra cell in the mesh
//             A vectorial FEM space is built with 21 components
//==============================================================================

 fespace Qh ( Th, [ FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
                             FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
                                      FEQF23d, FEQF23d, FEQF23d, FEQF23d,
                                               FEQF23d, FEQF23d, FEQF23d,
                                                        FEQF23d, FEQF23d,
                                                                 FEQF23d] );
)"""";

}

if(!Sequential){

codeSnippet R""""(

//==============================================================================
// ------- The finite element mesh -------
// ----------------------------------------------------------------------------
//  Th        : Finite element mesh
//  DummyMesh : Dummy mesh i.e, square for 2D and cube for 3D
//==============================================================================

 meshN   Th = DummyMesh;

//==============================================================================
// ------- The finite element spaces -------
// ----------------------------------------------------------------------------
//  Vh        : Mixed finite element space  for displacement
//==============================================================================

 fespace Vh     ( Th , Pk );
)"""";


 if(!fastmethod && spc==2)
codeSnippet R""""(

//==============================================================================
// ------- The finite element space  -------
// ----------------------------------------------------------------------------
//  Qh       : Quadratur finite element space  for material tensor
//             FEQF2 implies 3 dof for a triangular cell in the mesh
//             A vectorial FEM space is built with 6 components
//==============================================================================

 fespace Qh  ( Th ,[ FEQF2, FEQF2, FEQF2,
                            FEQF2, FEQF2,
                                   FEQF2] );
)"""";

 if(useMfront && Model=="pseudo_nonlinear" && spc==2)
codeSnippet R""""(

//==============================================================================
// ------- The finite element space  -------
// ----------------------------------------------------------------------------
//  Sh       : Quadratur finite element space  for Stress/Strain tensor
//             FEQF2 implies 3 dof for a triangular cell in the mesh
//             A vectorial FEM space is built with 3 components
//==============================================================================

 fespace Sh  ( Th ,[ FEQF2, FEQF2, FEQF2]);

)"""";


if(!fastmethod && spc==3)
codeSnippet R""""(

//==============================================================================
// ------- The finite element space  -------
// ----------------------------------------------------------------------------
//  Qh       : Quadratur finite element space  for material tensor
//             FEQF23d implies 4 dof for a tetra cell in the mesh
//             A vectorial FEM space is built with 21 components
//==============================================================================

 fespace Qh ( Th, [ FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
                             FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d,
                                      FEQF23d, FEQF23d, FEQF23d, FEQF23d,
                                               FEQF23d, FEQF23d, FEQF23d,
                                                        FEQF23d, FEQF23d,
                                                                 FEQF23d] );
)"""";

if(useMfront && Model=="pseudo_nonlinear" && spc==3)
codeSnippet R""""(

//==============================================================================
// ------- The finite element space  -------
// ----------------------------------------------------------------------------
//  Sh       : Quadratur finite element space  for Stress/Strain tensor
//             FEQF2 implies 4 dof for a tetraheron cell in the mesh
//             A vectorial FEM space is built with 6 components
//==============================================================================

 fespace Sh  ( Th ,[ FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d, FEQF23d ]);

)"""";


codeSnippet R""""(

//==============================================================================
// ---- Function for building the restriction matrix and partiton of unity ----
//==============================================================================

 func int PartThAndBuildCommunication(){

  loadfemesh(Th,ThName);
  perfromRCMreordering(Th);

  PETScMPIBuild(
           Th                         , // Local  mesh
           getARGV( "-split" , 1 )    , // Split factor
           restrictionIntersectionP   , // Restriction matrix
           DP                         , // Partition of unity
           Pk                         , // Vectorial FE space
           mpiCommWorld                 // MPI world
          );

  return 0;

 }

  startProcedure("Mesh Partitioning",t0);
  PartThAndBuildCommunication();
  endProcedure("Mesh Partitioning",t0);


)"""";
}
