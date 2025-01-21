/**************************************************************************************
*                                                                                     *
* Author : Mohd Afeef BADRI                                                           *
* Email  : mohd-afeef.badri@cea.fr                                                    *
* Date   : 03/10/2024                                                                 *
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

}

if(!Sequential){
if (!adaptmesh)
{
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
else
{
codeSnippet R""""(
//==============================================================================
// ------- The finite element mesh -------
// ----------------------------------------------------------------------------
//  Th        : Finite element mesh
//==============================================================================



  startProcedure("Mesh Partitioning",t0);
  mesh3 Th;
  loadfemesh(Th,ThName);
  DmeshCreate(Th);
  endProcedure("Mesh Partitioning",t0);

//==============================================================================
// ------- The finite element spaces -------
// ----------------------------------------------------------------------------
//  Vh        : Mixed finite element space  for displacement
//==============================================================================

  fespace Vh     ( Th , Pk );
)"""";
}
}
