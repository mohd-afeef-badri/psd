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
 

 if(Model=="Hujeux")
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
 "  mpiBarrier(mpiCommWorld);                                                     \n"
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
