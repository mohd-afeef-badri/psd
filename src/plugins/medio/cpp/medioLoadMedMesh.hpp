/*****************************************************************************

     This file is a part of PSD (Parallel Structural/Seismic/Solid dynamics)

     -------------------------------------------------------------------

     Author(s): Mohd Afeef Badri
     Email    : mohd-afeef.badri@cea.com
     Date     : 13/04/2022
     Comment  : The program collects functions needed by the medio

     -------------------------------------------------------------------

     medio is PSD plugin intended to enable usage of med files within PSD.
     medio is distributed   in  the  hope that it  will be useful, HOWEVER
     WITHOUT ANY WARRANTY;  or  without  even  implied warranty of FITNESS
     FOR A PARTICULAR PURPOSE.

*******************************************************************************/

//------------------------------------------------------------------------------
// loadmed: a function to load med file for a 2D mesh for a FreeFEM mesh object
//          This  functions  expects  two  inputs i) 2D mesh name be saved, and
//          ii) the name of the mesh in med mesh. And returns the mesh object.
//------------------------------------------------------------------------------

Mesh *loadmed(std::string &inputfile, std::string &meshname){

#ifdef DEBUG
  cout << "\n"
          "--------------------------------------\n"
          " loading med mesh \n"
          "--------------------------------------\n";
#endif

  MEDCouplingUMesh *mesh=ReadUMeshFromFile(inputfile,meshname,0);       // 2d mesh (triangles)
  MEDCouplingUMesh *mesh1d=ReadUMeshFromFile(inputfile,meshname,-1);    // 1d mesh (edges)

  // mesh info variables //
  int nv     ,       // # verticies
      nt  = 0,       // # triangles
      nbe = 0;       // # boundary edges

  // get mesh info //
  nv  = mesh->getNumberOfNodes();
  nt  = mesh->getNumberOfCells();
  nbe = mesh1d->getNumberOfCells();



  // create nodes //
  Mesh::Vertex *vff;
  vff = new Mesh::Vertex[nv];

  // get nodes //
  double *nodesRead ;
  nodesRead = mesh->getCoords()->getPointer();

  // set nodes //
  for (int i=0; i < nv; i++){
    vff[i].x = nodesRead[i*2  ];
    vff[i].y = nodesRead[i*2+1];
    vff[i].lab = 1;
  }



  // create triangles //
  Mesh::Triangle *tff = new Mesh::Triangle[nt];
  Mesh::Triangle *ttff = tff;

  // get triangles //
  mcIdType *NodalConnectivity ;
  NodalConnectivity = mesh->getNodalConnectivity()->getPointer();

  // set triangles //
  for (int i=0; i < mesh->getNumberOfCells(); i++)
    (ttff++)->set(vff, NodalConnectivity[i*4 + 1], NodalConnectivity[i*4 + 2], NodalConnectivity[i*4 + 3], NodalConnectivity[i*4 + 0]);




  // create edges //
  Mesh::BorderElement *bff = new Mesh::BorderElement[nbe];
  Mesh::BorderElement *bbff = bff;

  // get edges //
  mcIdType *NodalConnectivity1d ;
  NodalConnectivity1d = mesh1d->getNodalConnectivity()->getPointer();

  // set edges //
  for (int i=0; i < mesh1d->getNumberOfCells(); i++)
    (bbff++)->set(vff, NodalConnectivity1d[i*3 + 1], NodalConnectivity1d[i*3 + 2], NodalConnectivity1d[i*3 + 0]);


  // create mesh //
  Mesh *pTh = new Mesh(nv, nt, nbe, vff, tff, bff);

  // free memory //
  delete[] nodesRead;
  delete[] NodalConnectivity;
  delete[] NodalConnectivity1d;

  return pTh;
}


//------------------------------------------------------------------------------
// loadmed: a function to load med file for a 3D mesh for a FreeFEM mesh object
//          This  functions  expects  two  inputs i) 3D mesh name be saved, and
//          ii) the name of the mesh in med mesh. And returns the mesh object.
//------------------------------------------------------------------------------

Mesh3 *loadmed3(std::string &inputfile, std::string &meshname){

#ifdef DEBUG
  cout << "\n"
          "--------------------------------------\n"
          " loading med mesh \n"
          "--------------------------------------\n";
#endif

  MEDCouplingUMesh *mesh=ReadUMeshFromFile(inputfile,meshname,0);       // 3d mesh (tetrahedral)
  MEDCouplingUMesh *mesh2d=ReadUMeshFromFile(inputfile,meshname,-1);    // 2d mesh (triangles)

  // mesh info variables //
  int nv     ,       // # verticies
      nt  = 0,       // # triangles
      nbe = 0;       // # boundary edges


  // get mesh info //
  nv  = mesh->getNumberOfNodes();
  nt  = mesh->getNumberOfCells();
  nbe = mesh2d->getNumberOfCells();

  // create nodes //
  Vertex3 *vff;
  vff = new Vertex3[nv];

  // get nodes //
  double *nodesRead ;
  nodesRead = mesh->getCoords()->getPointer();

  // set nodes //
  for (int i=0; i < nv; i++){
    vff[i].x = nodesRead[i*3  ];
    vff[i].y = nodesRead[i*3+1];
    vff[i].z = nodesRead[i*3+2];
    vff[i].lab = 1;
  }


  // create tetrahedrons //
  Tet *tff = new Tet[nt];
  Tet *ttff = tff;

  // get tetrahedrons //
  mcIdType *NodalConnectivity ;
  NodalConnectivity = mesh->getNodalConnectivity()->getPointer();

  // set tetrahedrons //
  int indexTet[4];
  for (int i=0; i < mesh->getNumberOfCells(); i++){
    indexTet[0]= NodalConnectivity[i*5 + 1];
    indexTet[1]= NodalConnectivity[i*5 + 2];
    indexTet[2]= NodalConnectivity[i*5 + 3];
    indexTet[3]= NodalConnectivity[i*5 + 4];
    (ttff++)->set(vff, indexTet, NodalConnectivity[i*5 + 0]);
  }


  // create triangles //
  Triangle3 *bff = new Triangle3[nbe];
  Triangle3 *bbff = bff;

  // get triangles //
  mcIdType *NodalConnectivity2d ;
  NodalConnectivity2d = mesh2d->getNodalConnectivity()->getPointer();

  // set triangles //
  int indexTria[3];
  for (int i=0; i < mesh2d->getNumberOfCells(); i++){
    indexTria[0]= NodalConnectivity2d[i*4 + 1];
    indexTria[1]= NodalConnectivity2d[i*4 + 2];
    indexTria[2]= NodalConnectivity2d[i*4 + 3];
    (bbff++)->set(vff, indexTria, NodalConnectivity2d[i*4 + 0]);
  }


  // create mesh //
  Mesh3 *pTh3 = new Mesh3(nv, nt, nbe, vff, tff, bff);

  // free memory //
  delete[] nodesRead;
  delete[] NodalConnectivity;
  delete[] NodalConnectivity2d;

  return pTh3;
}
