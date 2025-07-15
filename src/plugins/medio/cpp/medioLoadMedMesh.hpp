/**************************************************************************************
*                                                                                     *
*           This file is a part of PSD (Parallel Structural Dynamics)                 *
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
**************************************************************************************/

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
  MCAuto < MEDFileUMesh > medmesh = MEDFileUMesh::New(inputfile);       // mesh for fields

  // mesh info variables //
  int nv     ,       // # verticies
      nt  = 0,       // # triangles
      nbe = 0;       // # boundary edges

  // get mesh info //
  nv  = mesh->getNumberOfNodes();
  nt  = mesh->getNumberOfCells();
  nbe = mesh1d->getNumberOfCells();


  // reading mesh Ids labels //
  const DataArrayIdType * famIds    = medmesh->getFamilyFieldAtLevel(0);
  const DataArrayIdType * famIds1d  = medmesh->getFamilyFieldAtLevel(-1);


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
    (ttff++)->set(vff, NodalConnectivity[i*4 + 1], NodalConnectivity[i*4 + 2], NodalConnectivity[i*4 + 3], famIds->getIJ(i,0));

  if(verbosity > 99)
    for (int i=0; i < mesh->getNumberOfCells(); i++)
      cout << "Tria   "<< i << " (" <<  NodalConnectivity[i*4 + 1]
                            << "\t" <<  NodalConnectivity[i*4 + 2]
                            << "\t" <<  NodalConnectivity[i*4 + 3]
                            << ")\tlab\t" << famIds->getIJ(i,0) << endl;


  // create edges //
  Mesh::BorderElement *bff = new Mesh::BorderElement[nbe];
  Mesh::BorderElement *bbff = bff;

  // get edges //
  mcIdType *NodalConnectivity1d ;
  NodalConnectivity1d = mesh1d->getNodalConnectivity()->getPointer();

  // set edges //
  for (int i=0; i < mesh1d->getNumberOfCells(); i++)
    (bbff++)->set(vff, NodalConnectivity1d[i*3 + 1], NodalConnectivity1d[i*3 + 2], famIds1d->getIJ(i,0));

  if(verbosity > 99)
    for (int i=0; i < mesh1d->getNumberOfCells(); i++)
      cout << "Edge   "<< i << " (" <<  NodalConnectivity1d[i*3 + 1]
                            << "\t" <<  NodalConnectivity1d[i*3 + 2]
                            << ")\tlab\t" << famIds1d->getIJ(i,0) << endl;

  // create mesh //
  Mesh *pTh = new Mesh(nv, nt, nbe, vff, tff, bff);

  // free memory //
  delete[] nodesRead;
  delete[] NodalConnectivity;
  delete[] NodalConnectivity1d;

  return pTh;
}


//------------------------------------------------------------------------------
// loadmed3: a function to load med file for a 3D mesh for a FreeFEM mesh object
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
  MCAuto < MEDFileUMesh > medmesh = MEDFileUMesh::New(inputfile);       // mesh for fields

  // mesh info variables //
  int nv     ,       // # verticies
      nt  = 0,       // # triangles
      nbe = 0;       // # boundary edges


  // get mesh info //
  nv  = mesh->getNumberOfNodes();
  nt  = mesh->getNumberOfCells();
  nbe = mesh2d->getNumberOfCells();


  // reading mesh Ids labels //
  const DataArrayIdType * famIds    = medmesh->getFamilyFieldAtLevel(0);
  const DataArrayIdType * famIds2d  = medmesh->getFamilyFieldAtLevel(-1);

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
    (ttff++)->set(vff, indexTet, famIds->getIJ(i,0));
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
    (bbff++)->set(vff, indexTria, famIds2d->getIJ(i,0));
  }


  // create mesh //
  Mesh3 *pTh3 = new Mesh3(nv, nt, nbe, vff, tff, bff);

  // free memory //
  delete[] nodesRead;
  delete[] NodalConnectivity;
  delete[] NodalConnectivity2d;

  return pTh3;
}


//------------------------------------------------------------------------------
// loadmed3S: a function to load med file for a 3DS mesh for a FreeFEM mesh object
//          This  functions  expects  two  inputs i) 3DS mesh name be saved, and
//          ii) the name of the mesh in med mesh. And returns the mesh object.
//------------------------------------------------------------------------------

MeshS *loadmedS(std::string &inputfile, std::string &meshname){

#ifdef DEBUG
  cout << "\n"
          "--------------------------------------\n"
          " loading med mesh \n"
          "--------------------------------------\n";
#endif

  MEDCouplingUMesh *mesh=ReadUMeshFromFile(inputfile,meshname,0);       // 3dS mesh (triangles)
  MEDCouplingUMesh *mesh1d=ReadUMeshFromFile(inputfile,meshname,-1);    // 1d mesh  (edges)
  MCAuto < MEDFileUMesh > medmesh = MEDFileUMesh::New(inputfile);       // mesh for fields


  // mesh info variables //
  int nv     ,       // # verticies
      nt  = 0,       // # triangles
      nbe = 0;       // # boundary edges



  // reading mesh Ids labels //
  const DataArrayIdType * famIds    = medmesh->getFamilyFieldAtLevel(0);
  const DataArrayIdType * famIds1d  = medmesh->getFamilyFieldAtLevel(-1);

  // get mesh info //
  nv  = mesh->getNumberOfNodes();
  nt  = mesh->getNumberOfCells();
  nbe = mesh1d->getNumberOfCells();

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


  // create triangles //
  TriangleS *tff = new TriangleS[nt];
  TriangleS *ttff = tff;

  // get triangles //
  mcIdType *NodalConnectivity ;
  NodalConnectivity = mesh->getNodalConnectivity()->getPointer();

  // set triangles //
  int indexTet[3];
  for (int i=0; i < mesh->getNumberOfCells(); i++){
    indexTet[0]= NodalConnectivity[i*4 + 1];
    indexTet[1]= NodalConnectivity[i*4 + 2];
    indexTet[2]= NodalConnectivity[i*4 + 3];
    (ttff++)->set(vff, indexTet, famIds->getIJ(i,0));
  }

  if(verbosity > 99)
    for (int i=0; i < mesh->getNumberOfCells(); i++)
      cout << "Tria   "<< i << " (" <<  NodalConnectivity[i*4 + 1]
                            << "\t" <<  NodalConnectivity[i*4 + 2]
                            << "\t" <<  NodalConnectivity[i*4 + 3]
                            << ")\tlab\t" << famIds->getIJ(i,0) << endl;

  // create edges //
  BoundaryEdgeS *bff = new BoundaryEdgeS[nbe];
  BoundaryEdgeS *bbff = bff;

  // get edges //
  mcIdType *NodalConnectivity1d ;
  NodalConnectivity1d = mesh1d->getNodalConnectivity()->getPointer();

  // set edges //
  int indexSeg[2];
  for (int i=0; i < mesh1d->getNumberOfCells(); i++){
    indexSeg[0]= NodalConnectivity1d[i*3 + 1];
    indexSeg[1]= NodalConnectivity1d[i*3 + 2];
    (bbff++)->set(vff, indexSeg, famIds1d->getIJ(i,0));
  }

  if(verbosity > 99)
    for (int i=0; i < mesh1d->getNumberOfCells(); i++)
      cout << "Edge   "<< i << " (" <<  NodalConnectivity1d[i*3 + 1]
                            << "\t" <<  NodalConnectivity1d[i*3 + 2]
                            << ")\tlab\t" << famIds1d->getIJ(i,0) << endl;

  // create mesh //
  MeshS *pThS = new MeshS(nv, nt, nbe, vff, tff, bff);

  // free memory //
  delete[] nodesRead;
  delete[] NodalConnectivity;
  delete[] NodalConnectivity1d;

  return pThS;
}


//------------------------------------------------------------------------------
// loadmedL: a function to load med file for a 3DL mesh for a FreeFEM mesh object
//          This  functions  expects  two  inputs i) 3DL mesh name be saved, and
//          ii) the name of the mesh in med mesh. And returns the mesh object.
//------------------------------------------------------------------------------

MeshL *loadmedL(std::string &inputfile, std::string &meshname){

#ifdef DEBUG
  cout << "\n"
          "--------------------------------------\n"
          " loading med mesh \n"
          "--------------------------------------\n";
#endif


int ii;
  MEDCouplingUMesh *mesh=ReadUMeshFromFile(inputfile,meshname,0);       // 3dL mesh (edges 3D)
//  MEDCouplingUMesh *mesh0d=ReadUMeshFromFile(inputfile,meshname,1);    // 0d mesh (point 3D)
  MCAuto < MEDFileUMesh > medmesh = MEDFileUMesh::New(inputfile);       // mesh for fields

  // mesh info variables //
  int nv     ,       // # verticies
      nt  = 0,       // # triangles
      nbe = 0;       // # boundary edges

  // get mesh info //
  nv  = mesh->getNumberOfNodes();
  nt  = mesh->getNumberOfCells();
  //nbe = mesh0d->getNumberOfCells();

  // reading mesh Ids labels //
  const DataArrayIdType * famIds    = medmesh->getFamilyFieldAtLevel(0);
//  const DataArrayIdType * famIds1d  = medmesh->getFamilyFieldAtLevel(-1);

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



  // create edges //
  EdgeL *tff  = new EdgeL[nt];
  EdgeL *ttff = tff;

  // get edges //
  mcIdType *NodalConnectivity ;
  NodalConnectivity = mesh->getNodalConnectivity()->getPointer();

  // set edges //
  int indexTet[2];
  for (int i=0; i < mesh->getNumberOfCells(); i++){
    indexTet[0]= NodalConnectivity[i*3 + 1];
    indexTet[1]= NodalConnectivity[i*3 + 2];
    (ttff++)->set(vff, indexTet, famIds->getIJ(i,0));
  }


  // create points //
  nbe=0;               // TODO : THIS IS NOT WORKING WHEN MORE THAN 0 INVESTIGATE
  BoundaryPointL *bff = new BoundaryPointL[nbe];
  BoundaryPointL *bbff = bff;

/*
  // get points //
  mcIdType *NodalConnectivity0d ;
  NodalConnectivity0d = mesh0d->getNodalConnectivity()->getPointer();

  // set points //
  int indexVert[1];
  for (int i=0; i < mesh0d->getNumberOfCells(); i++){
    indexVert[0]= NodalConnectivity0d[i*2 + 1];
    cout << " NodalConnectivity0d[i*2 + 1] " << NodalConnectivity0d[i*2 + 1] << endl;
    (bbff++)->set(vff, indexVert, NodalConnectivity0d[i*2 + 0]);
  }
*/
  // create mesh //
  MeshL *pThL = new MeshL(nv, nt, nbe, vff, tff, bff);

  // free memory //
  delete[] nodesRead;
  delete[] NodalConnectivity;

  return pThL;
}
