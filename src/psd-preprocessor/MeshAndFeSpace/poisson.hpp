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
