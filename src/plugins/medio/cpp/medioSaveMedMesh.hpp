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
// savemedmesh: a function to save med file for a 3D mesh coming from FreeFEM
//              This functions expects two inputs i) 3D mesh to be saved, and
//              ii) the name of the mesh in med mesh.
//------------------------------------------------------------------------------

int savemedmesh( const Fem2D::Mesh3* const &pTh, std::string* const &inputfile ){

#ifdef DEBUG
  cout << "\n"
          "--------------------------------------\n"
          " saving med file for 3D  \n"
          "--------------------------------------\n";
#endif

  const Mesh3 &Th = *pTh;

  double*   medNodeCoords = new double[Th.nv * 3];              // to store mesh nodes
  mcIdType* medCellConn   = new mcIdType[Th.nt*4 + Th.nbe*3];   // to store mesh elements
                                                                // elements = Tets + Tria

  // get nodes //
  for (int i = 0; i < Th.nv; i++) {
     medNodeCoords[i * 3]     = double(Th(i).x);
     medNodeCoords[i * 3 + 1] = double(Th(i).y);
     medNodeCoords[i * 3 + 2] = double(Th(i).z);
  }

  //  get tetrahedrons //
  int count = 0;
  for (int i = 0; i < Th.nt; i++) {
    medCellConn[count] = Th(Th[i][0]) ; count++;
    medCellConn[count] = Th(Th[i][1]) ; count++;
    medCellConn[count] = Th(Th[i][2]) ; count++;
    medCellConn[count] = Th(Th[i][3]) ; count++;
  }

  //  get triangles //
  for (int i = 0; i < Th.nbe; i++) {
    medCellConn[count] = Th(Th.be(i)[0]) ; count++;
    medCellConn[count] = Th(Th.be(i)[1]) ; count++;
    medCellConn[count] = Th(Th.be(i)[2]) ; count++;
  }

  // create medcoupling unstructured meshes //
  MEDCouplingUMesh * medMesh3d = MEDCouplingUMesh::New();      // to store 3d mesh
  MEDCouplingUMesh * medMesh2d = MEDCouplingUMesh::New();      // to store 2d mesh

  // set 3d mesh characteristics //
  medMesh3d -> setMeshDimension(3);
  medMesh3d -> allocateCells(Th.nt);
  medMesh3d -> setName("TetrahedralMesh");

  // set tetrahedrons //
  count = 0;
  for (int i = 0; i < Th.nt; i++) {
    medMesh3d -> insertNextCell(INTERP_KERNEL::NORM_TETRA4, 4, medCellConn + count);
    count += 4;
  }
  medMesh3d -> finishInsertingCells();

  // set 2d mesh characteristics //
  medMesh2d -> setMeshDimension(2);
  medMesh2d -> allocateCells(Th.nbe);
  medMesh2d -> setName("TetrahedralMesh");

  // set triangles //
  for (int i = 0; i < Th.nbe; i++) {
    medMesh2d -> insertNextCell(INTERP_KERNEL::NORM_TRI3, 3, medCellConn + count);
    count += 3;
  }
  medMesh2d -> finishInsertingCells();


  // set nodes //
  DataArrayDouble * myCoords = DataArrayDouble::New();
  myCoords -> alloc(Th.nv, 3);
  myCoords -> setInfoOnComponent(0, "x");
  myCoords -> setInfoOnComponent(1, "y");
  myCoords -> setInfoOnComponent(2, "z");
  std::copy(medNodeCoords, medNodeCoords + Th.nv*3, myCoords -> getPointer());
  medMesh3d -> setCoords(myCoords);
  medMesh2d -> setCoords(myCoords);

  // combine meshes 3d + 2d //
  std::vector<const MEDCouplingUMesh *> finalMesh;
  finalMesh.push_back(medMesh3d);
  finalMesh.push_back(medMesh2d);

  // write mesh //
  WriteUMeshes(*inputfile,finalMesh,true);

  // free memory //
  medMesh3d  -> decrRef();
  medMesh2d  -> decrRef();
  myCoords   -> decrRef();
  delete[]     medNodeCoords;
  delete[]     medCellConn;

  return 0;
}


//------------------------------------------------------------------------------
// savemedmesh: a function to save med file for a 2D mesh coming from FreeFEM
//              This functions expects two inputs i) 2D mesh to be saved, and
//              ii) the name of the mesh in med mesh.
//------------------------------------------------------------------------------

int savemedmesh(const Fem2D::Mesh* const &pTh, std::string* const &inputfile) {

#ifdef DEBUG
  cout << "\n"
          "--------------------------------------\n"
          " saving med file for 2D planar  \n"
          "--------------------------------------\n";
#endif

  const Mesh &Th = *pTh;

  double* medNodeCoords = new double[Th.nv * 2];              // to store mesh nodes
  mcIdType *medCellConn = new mcIdType[Th.nt*3 +Th.neb*2];    // to store mesh elements
                                                              // elements = Tria + Edges

  //  get nodes  //
  for (int i = 0; i < Th.nv; i++) {
     medNodeCoords[i * 2]     = double(Th(i).x);
     medNodeCoords[i * 2 + 1] = double(Th(i).y);
  }

  //  get triangles  //
  int count = 0;
  for (int i = 0; i < Th.nt; i++) {
    medCellConn[count] = Th(Th[i][0]) ; count++;
    medCellConn[count] = Th(Th[i][1]) ; count++;
    medCellConn[count] = Th(Th[i][2]) ; count++;
  }

  //  get edges  //
  for (int i = 0; i < Th.neb; i++) {
    medCellConn[count] = Th(Th.be(i)[0]) ; count++;
    medCellConn[count] = Th(Th.be(i)[1]) ; count++;
  }

  // create medcoupling unstructured meshes //
  MEDCouplingUMesh * medMesh2d = MEDCouplingUMesh::New();      // to store 2d mesh
  MEDCouplingUMesh * medMesh1d = MEDCouplingUMesh::New();      // to store 1d mesh

  // set 2d mesh characteristics //
  medMesh2d -> setMeshDimension(2);
  medMesh2d -> allocateCells(Th.nt);
  medMesh2d -> setName("TriangularMesh");

  // set triangles //
  count = 0;
  for (int i = 0; i < Th.nt; i++) {
    medMesh2d -> insertNextCell(INTERP_KERNEL::NORM_TRI3, 3, medCellConn + count);
    count += 3;
  }
  medMesh2d -> finishInsertingCells();

  // set 1d mesh characteristics //
  medMesh1d -> setMeshDimension(1);
  medMesh1d -> allocateCells(Th.neb);
  medMesh1d -> setName("TriangularMesh");

  // set edges //
  for (int i = 0; i < Th.neb; i++) {
    medMesh1d -> insertNextCell(INTERP_KERNEL::NORM_SEG2, 2, medCellConn + count);
    count += 2;
  }
  medMesh1d -> finishInsertingCells();


  // set nodes //
  DataArrayDouble * myCoords = DataArrayDouble::New();
  myCoords -> alloc(Th.nv, 2);
  myCoords -> setInfoOnComponent(0, "x");
  myCoords -> setInfoOnComponent(1, "y");
  std::copy(medNodeCoords, medNodeCoords + Th.nv*2, myCoords -> getPointer());
  medMesh2d -> setCoords(myCoords);
  medMesh1d -> setCoords(myCoords);

  // combine meshes 2d + 1d //
  std::vector<const MEDCouplingUMesh *> finalMesh;
  finalMesh.push_back(medMesh2d);
  finalMesh.push_back(medMesh1d);

  // write mesh //
  WriteUMeshes(*inputfile,finalMesh,true);

  // free memory //
  medMesh1d  -> decrRef();
  medMesh2d  -> decrRef();
  myCoords   -> decrRef();
  delete[]     medNodeCoords;
  delete[]     medCellConn;

  return 0;
}


//------------------------------------------------------------------------------
// savemedmesh: a function to save med file for a 3DS mesh coming from FreeFEM
//              This functions expects two inputs i) 3DS mesh to be saved, and
//              ii) the name of the mesh in med mesh.
//------------------------------------------------------------------------------

int savemedmesh(const Fem2D::MeshS* const &pTh, std::string* const &inputfile) {

#ifdef DEBUG
  cout << "\n"
          "--------------------------------------\n"
          " saving med file for 2D surface \n"
          "--------------------------------------\n";
#endif

  const MeshS &Th = *pTh;

  double* medNodeCoords = new double[Th.nv * 3];              // to store mesh nodes
  mcIdType *medCellConn = new mcIdType[Th.nt*3 +Th.nbe*2];    // to store mesh elements
                                                              // elements = Tria + edges


  // get nodes //
  for (int i = 0; i < Th.nv; i++) {
     medNodeCoords[i * 3]     = double(Th(i).x);
     medNodeCoords[i * 3 + 1] = double(Th(i).y);
     medNodeCoords[i * 3 + 2] = double(Th(i).z);
  }

  //  get triangles //
  int count = 0;
  for (int i = 0; i < Th.nt; i++) {
    medCellConn[count] = Th(Th[i][0]) ; count++;
    medCellConn[count] = Th(Th[i][1]) ; count++;
    medCellConn[count] = Th(Th[i][2]) ; count++;
  }

  //  get edges  //
  for (int i = 0; i < Th.nbe; i++) {
    medCellConn[count] = Th(Th.be(i)[0]) ; count++;
    medCellConn[count] = Th(Th.be(i)[1]) ; count++;
  }

  // create medcoupling unstructured meshes //
  MEDCouplingUMesh * medMesh2d = MEDCouplingUMesh::New();      // to store 3DS mesh
  MEDCouplingUMesh * medMesh1d = MEDCouplingUMesh::New();      // to store 1d mesh

  // set 3ds mesh characteristics //
  medMesh2d -> setMeshDimension(2);
  medMesh2d -> allocateCells(Th.nt);
  medMesh2d -> setName("TriangularMesh");

  // set triangles //
  count = 0;
  for (int i = 0; i < Th.nt; i++) {
    medMesh2d -> insertNextCell(INTERP_KERNEL::NORM_TRI3, 3, medCellConn + count);
    count += 3;
  }
  medMesh2d -> finishInsertingCells();

  // set 1d mesh characteristics //
  medMesh1d -> setMeshDimension(1);
  medMesh1d -> allocateCells(Th.nbe);
  medMesh1d -> setName("TriangularMesh");

  // set edges //
  for (int i = 0; i < Th.nbe; i++) {
    medMesh1d -> insertNextCell(INTERP_KERNEL::NORM_SEG2, 2, medCellConn + count);
    count += 2;
  }
  medMesh1d -> finishInsertingCells();

  // set nodes //
  DataArrayDouble * myCoords = DataArrayDouble::New();
  myCoords -> alloc(Th.nv, 3);
  myCoords -> setInfoOnComponent(0, "x");
  myCoords -> setInfoOnComponent(1, "y");
  myCoords -> setInfoOnComponent(2, "z");
  std::copy(medNodeCoords, medNodeCoords + Th.nv*3, myCoords -> getPointer());
  medMesh2d -> setCoords(myCoords);
  medMesh1d -> setCoords(myCoords);

  // combine meshes 3ds + 1d //
  std::vector<const MEDCouplingUMesh *> finalMesh;
  finalMesh.push_back(medMesh2d);
  finalMesh.push_back(medMesh1d);

  // write mesh //
  WriteUMeshes(*inputfile,finalMesh,true);

  // free memory //
  medMesh1d  -> decrRef();
  medMesh2d  -> decrRef();
  myCoords   -> decrRef();
  delete[]     medNodeCoords;
  delete[]     medCellConn;

  return 0;
}

//------------------------------------------------------------------------------
// savemedmesh: a function to save med file for a 1DL mesh coming from FreeFEM
//              This functions expects two inputs i) 1DL mesh to be saved, and
//              ii) the name of the mesh in med mesh.
//------------------------------------------------------------------------------

int savemedmesh(const Fem2D::MeshL* const &pTh, std::string* const &inputfile) {

#ifdef DEBUG
  cout << "\n"
          "--------------------------------------\n"
          " saving med file for 1D curve \n"
          "--------------------------------------\n";
#endif

  const MeshL &Th = *pTh;

  double* medNodeCoords = new double[Th.nv * 3];    // to store mesh nodes
  mcIdType *medCellConn = new mcIdType[Th.nt*2];    // to store mesh elements
                                                    // elements = Tria + Edges

  //  get nodes  //
  for (int i = 0; i < Th.nv; i++) {
     medNodeCoords[i * 3]     = double(Th(i).x);
     medNodeCoords[i * 3 + 1] = double(Th(i).y);
     medNodeCoords[i * 3 + 2] = double(Th(i).z);
  }

  //  get edges  //
  int count = 0;
  for (int i = 0; i < Th.nt; i++) {
    medCellConn[count] = Th(Th[i][0]) ; count++;
    medCellConn[count] = Th(Th[i][1]) ; count++;
  }

  // create medcoupling unstructured meshes //
  MEDCouplingUMesh * medMesh1d = MEDCouplingUMesh::New();

  // set 2d mesh characteristics //
  medMesh1d -> setMeshDimension(1);
  medMesh1d -> allocateCells(Th.nt);
  medMesh1d -> setName("CurveMesh");

  // set edges //
  count = 0;
  for (int i = 0; i < Th.nt; i++) {
    medMesh1d -> insertNextCell(INTERP_KERNEL::NORM_SEG2, 2, medCellConn + count);
    count += 2;
  }
  medMesh1d -> finishInsertingCells();

  // set nodes //
  DataArrayDouble * myCoords = DataArrayDouble::New();
  myCoords -> alloc(Th.nv, 3);
  myCoords -> setInfoOnComponent(0, "x");
  myCoords -> setInfoOnComponent(1, "y");
  myCoords -> setInfoOnComponent(2, "z");
  std::copy(medNodeCoords, medNodeCoords + Th.nv*3, myCoords -> getPointer());
  medMesh1d -> setCoords(myCoords);

  // write mesh //
  std::vector<const MEDCouplingUMesh *> finalMesh;
  finalMesh.push_back(medMesh1d);
  WriteUMeshes(*inputfile,finalMesh,true);

  // free memory //
  medMesh1d  -> decrRef();
  myCoords   -> decrRef();
  delete[]     medNodeCoords;
  delete[]     medCellConn;

  return 0;
}
