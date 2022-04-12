/*****************************************************************************

     This file is a part of PSD (Parallel Structural/Seismic/Solid dynamics)

     -------------------------------------------------------------------

     Author(s): Mohd Afeef Badri
     Email    : mohd-afeef.badri@cea.com
     Date     : 06/04/2022
     Comment  : The program collects functions needed by the PSD

     -------------------------------------------------------------------

     medio is PSD plugin intended to enable usage of med files within PSD.
     medio is distributed   in  the  hope that it  will be useful, HOWEVER
     WITHOUT ANY WARRANTY;  or  without  even  implied warranty of FITNESS
     FOR A PARTICULAR PURPOSE.

*******************************************************************************/

int savemedmesh(const Fem2D::Mesh3* const &pTh, std::string* const &inputfile) {

#ifdef DEBUG
  cout << "\n"
          "--------------------------------------\n"
          " saving med file for 3D  \n"
          "--------------------------------------\n";
#endif

  const Mesh3 &Th = *pTh;

//  double medNodeCoords[Th.nv * 3];
  double* medNodeCoords = new double[Th.nv * 3];
  for (int i = 0; i < Th.nv; i++) {
     medNodeCoords[i * 3]     = double(Th(i).x);
     medNodeCoords[i * 3 + 1] = double(Th(i).y);
     medNodeCoords[i * 3 + 2] = double(Th(i).z);     
  }

  int  nNodes      = (sizeof(medNodeCoords)/sizeof(medNodeCoords[0]))/3;
  int  nNodesArray = (sizeof(medNodeCoords)/sizeof(medNodeCoords[0]))  ;

  //  get cells  //
  int TotalCells = Th.nt;
//  mcIdType medCellConn[Th.nt*4 + Th.nbe*3];
  mcIdType *medCellConn = new mcIdType[Th.nt*4 + Th.nbe*3];

  int count = 0;
  for (int i = 0; i < Th.nt; i++) {
    medCellConn[count] = Th(Th[i][0]) ; count++;
    medCellConn[count] = Th(Th[i][1]) ; count++;
    medCellConn[count] = Th(Th[i][2]) ; count++;
    medCellConn[count] = Th(Th[i][3]) ; count++;
  }

  cout << " \n\n" << endl;
  for (int i = 0; i < Th.nbe; i++) {
    medCellConn[count] = Th(Th.be(i)[0]) ; count++;
    medCellConn[count] = Th(Th.be(i)[1]) ; count++;
    medCellConn[count] = Th(Th.be(i)[2]) ; count++;
  }

  MEDCouplingUMesh * medMesh3d = MEDCouplingUMesh::New();

  medMesh3d -> setMeshDimension(3);
  medMesh3d -> allocateCells(Th.nt);
  medMesh3d -> setName("TetrahedralMesh");

  count = 0;
  for (int i = 0; i < Th.nt; i++) {
    medMesh3d -> insertNextCell(INTERP_KERNEL::NORM_TETRA4, 4, medCellConn + count);
    count += 4;
  }

  medMesh3d -> finishInsertingCells();


  MEDCouplingUMesh * medMesh2d = MEDCouplingUMesh::New();

  medMesh2d -> setMeshDimension(2);
  medMesh2d -> allocateCells(Th.nbe);
  medMesh2d -> setName("TetrahedralMesh");

  for (int i = 0; i < Th.nbe; i++) {
    medMesh2d -> insertNextCell(INTERP_KERNEL::NORM_TRI3, 3, medCellConn + count);
    count += 3;
  }

  medMesh2d -> finishInsertingCells();

  DataArrayDouble * myCoords = DataArrayDouble::New();
  myCoords -> alloc(nNodes, 3);
  myCoords -> setInfoOnComponent(0, "x");
  myCoords -> setInfoOnComponent(1, "y");
  myCoords -> setInfoOnComponent(2, "z");  
  std::copy(medNodeCoords, medNodeCoords + nNodesArray, myCoords -> getPointer());
  medMesh3d -> setCoords(myCoords);
  medMesh2d -> setCoords(myCoords);

  std::vector<const MEDCouplingUMesh *> finalMesh;
  finalMesh.push_back(medMesh3d);
  finalMesh.push_back(medMesh2d);

  WriteUMeshes(*inputfile,finalMesh,true);

  medMesh3d  -> decrRef();
  medMesh2d  -> decrRef();
  myCoords   -> decrRef();
  delete[]     medNodeCoords;
  delete[]     medCellConn;

  return 0;
}

int savemedmesh(const Fem2D::Mesh* const &pTh, std::string* const &inputfile) {

#ifdef DEBUG
  cout << "\n"
          "--------------------------------------\n"
          " saving med file for 2D planar  \n"
          "--------------------------------------\n";
#endif

  const Mesh &Th = *pTh;

//  double medNodeCoords[Th.nv * 2];
  double* medNodeCoords = new double[Th.nv * 2];
  for (int i = 0; i < Th.nv; i++) {
     medNodeCoords[i * 2]     = double(Th(i).x);
     medNodeCoords[i * 2 + 1] = double(Th(i).y);
  }

  int  nNodes      = (sizeof(medNodeCoords)/sizeof(medNodeCoords[0]))/2;
  int  nNodesArray = (sizeof(medNodeCoords)/sizeof(medNodeCoords[0]))  ;

  //  get cells  //
  int TotalCells = Th.nt;
//  mcIdType medCellConn[Th.nt*3 +Th.neb*2];
  mcIdType *medCellConn = new mcIdType[Th.nt*3 +Th.neb*2];

  int count = 0;
  for (int i = 0; i < Th.nt; i++) {
    medCellConn[count] = Th(Th[i][0]) ; count++;
    medCellConn[count] = Th(Th[i][1]) ; count++;
    medCellConn[count] = Th(Th[i][2]) ; count++;
  }

  for (int i = 0; i < Th.neb; i++) {
    medCellConn[count] = Th(Th.be(i)[0]) ; count++;
    medCellConn[count] = Th(Th.be(i)[1]) ; count++;
  }

  MEDCouplingUMesh * medMesh2d = MEDCouplingUMesh::New();

  medMesh2d -> setMeshDimension(2);
  medMesh2d -> allocateCells(Th.nt);
  medMesh2d -> setName("TriangularMesh");

  count = 0;
  for (int i = 0; i < Th.nt; i++) {
    medMesh2d -> insertNextCell(INTERP_KERNEL::NORM_TRI3, 3, medCellConn + count);
    count += 3;
  }

  medMesh2d -> finishInsertingCells();


  MEDCouplingUMesh * medMesh1d = MEDCouplingUMesh::New();

  medMesh1d -> setMeshDimension(1);
  medMesh1d -> allocateCells(Th.neb);
  medMesh1d -> setName("TriangularMesh");

  for (int i = 0; i < Th.neb; i++) {
    medMesh1d -> insertNextCell(INTERP_KERNEL::NORM_SEG2, 2, medCellConn + count);
    count += 2;
  }

  medMesh1d -> finishInsertingCells();

  DataArrayDouble * myCoords = DataArrayDouble::New();
  myCoords -> alloc(nNodes, 2);
  myCoords -> setInfoOnComponent(0, "x");
  myCoords -> setInfoOnComponent(1, "y");
  std::copy(medNodeCoords, medNodeCoords + nNodesArray, myCoords -> getPointer());
  medMesh2d -> setCoords(myCoords);
  medMesh1d -> setCoords(myCoords);

  std::vector<const MEDCouplingUMesh *> finalMesh;
  finalMesh.push_back(medMesh2d);
  finalMesh.push_back(medMesh1d);

  WriteUMeshes(*inputfile,finalMesh,true);

  medMesh1d  -> decrRef();
  medMesh2d  -> decrRef();
  myCoords   -> decrRef();
  delete[]     medNodeCoords;
  delete[]     medCellConn;

  return 0;
}



int savemedmesh(const Fem2D::MeshS* const &pTh, std::string* const &inputfile) {

#ifdef DEBUG
  cout << "\n"
          "--------------------------------------\n"
          " saving med file for 2D surface \n"
          "--------------------------------------\n";
#endif

  const MeshS &Th = *pTh;

//  double medNodeCoords[Th.nv * 3];
  double* medNodeCoords = new double[Th.nv * 3];
  for (int i = 0; i < Th.nv; i++) {
     medNodeCoords[i * 3]     = double(Th(i).x);
     medNodeCoords[i * 3 + 1] = double(Th(i).y);
     medNodeCoords[i * 3 + 2] = double(Th(i).z);     
  }

  int  nNodes      = (sizeof(medNodeCoords)/sizeof(medNodeCoords[0]))/3;
  int  nNodesArray = (sizeof(medNodeCoords)/sizeof(medNodeCoords[0]))  ;

  //  get cells  //
  int TotalCells = Th.nt;
//  mcIdType medCellConn[Th.nt*3 +Th.nbe*2];
  mcIdType *medCellConn = new mcIdType[Th.nt*3 +Th.nbe*2];

  int count = 0;
  for (int i = 0; i < Th.nt; i++) {
    medCellConn[count] = Th(Th[i][0]) ; count++;
    medCellConn[count] = Th(Th[i][1]) ; count++;
    medCellConn[count] = Th(Th[i][2]) ; count++;
  }

  for (int i = 0; i < Th.nbe; i++) {
    medCellConn[count] = Th(Th.be(i)[0]) ; count++;
    medCellConn[count] = Th(Th.be(i)[1]) ; count++;
  }

  MEDCouplingUMesh * medMesh2d = MEDCouplingUMesh::New();

  medMesh2d -> setMeshDimension(2);
  medMesh2d -> allocateCells(Th.nt);
  medMesh2d -> setName("TriangularMesh");

  count = 0;
  for (int i = 0; i < Th.nt; i++) {
    medMesh2d -> insertNextCell(INTERP_KERNEL::NORM_TRI3, 3, medCellConn + count);
    count += 3;
  }

  medMesh2d -> finishInsertingCells();


  MEDCouplingUMesh * medMesh1d = MEDCouplingUMesh::New();

  medMesh1d -> setMeshDimension(1);
  medMesh1d -> allocateCells(Th.nbe);
  medMesh1d -> setName("TriangularMesh");

  for (int i = 0; i < Th.nbe; i++) {
    medMesh1d -> insertNextCell(INTERP_KERNEL::NORM_SEG2, 2, medCellConn + count);
    count += 2;
  }

  medMesh1d -> finishInsertingCells();

  DataArrayDouble * myCoords = DataArrayDouble::New();
  myCoords -> alloc(nNodes, 3);
  myCoords -> setInfoOnComponent(0, "x");
  myCoords -> setInfoOnComponent(1, "y");
  myCoords -> setInfoOnComponent(2, "z");  
  std::copy(medNodeCoords, medNodeCoords + nNodesArray, myCoords -> getPointer());
  medMesh2d -> setCoords(myCoords);
  medMesh1d -> setCoords(myCoords);

  std::vector<const MEDCouplingUMesh *> finalMesh;
  finalMesh.push_back(medMesh2d);
  finalMesh.push_back(medMesh1d);

  WriteUMeshes(*inputfile,finalMesh,true);

  medMesh1d  -> decrRef();
  medMesh2d  -> decrRef();
  myCoords   -> decrRef();
  delete[]     medNodeCoords;
  delete[]     medCellConn;

  return 0;
}

int savemedmesh(const Fem2D::MeshL* const &pTh, std::string* const &inputfile) {

#ifdef DEBUG
  cout << "\n"
          "--------------------------------------\n"
          " saving med file for 1D curve \n"
          "--------------------------------------\n";
#endif

  const MeshL &Th = *pTh;

//  double medNodeCoords[Th.nv * 3];
  double* medNodeCoords = new double[Th.nv * 3];
  for (int i = 0; i < Th.nv; i++) {
     medNodeCoords[i * 3]     = double(Th(i).x);
     medNodeCoords[i * 3 + 1] = double(Th(i).y);
     medNodeCoords[i * 3 + 2] = double(Th(i).z);     
  }

  int  nNodes      = (sizeof(medNodeCoords)/sizeof(medNodeCoords[0]))/3;
  int  nNodesArray = (sizeof(medNodeCoords)/sizeof(medNodeCoords[0]))  ;

  //  get cells  //
  int TotalCells = Th.nt;
//  mcIdType medCellConn[Th.nt*3];
  mcIdType *medCellConn = new mcIdType[Th.nt*3];

  int count = 0;
  for (int i = 0; i < Th.nt; i++) {
    medCellConn[count] = Th(Th[i][0]) ; count++;
    medCellConn[count] = Th(Th[i][1]) ; count++;
  }

  MEDCouplingUMesh * medMesh1d = MEDCouplingUMesh::New();

  medMesh1d -> setMeshDimension(1);
  medMesh1d -> allocateCells(Th.nt);
  medMesh1d -> setName("TriangularMesh");

  count = 0;
  for (int i = 0; i < Th.nt; i++) {
    medMesh1d -> insertNextCell(INTERP_KERNEL::NORM_SEG2, 2, medCellConn + count);
    count += 2;
  }

  medMesh1d -> finishInsertingCells();

  DataArrayDouble * myCoords = DataArrayDouble::New();
  myCoords -> alloc(nNodes, 3);
  myCoords -> setInfoOnComponent(0, "x");
  myCoords -> setInfoOnComponent(1, "y");
  myCoords -> setInfoOnComponent(2, "z");  
  std::copy(medNodeCoords, medNodeCoords + nNodesArray, myCoords -> getPointer());
  medMesh1d -> setCoords(myCoords);

  std::vector<const MEDCouplingUMesh *> finalMesh;
  finalMesh.push_back(medMesh1d);

  WriteUMeshes(*inputfile,finalMesh,true);

  medMesh1d  -> decrRef();
  myCoords   -> decrRef();
  delete[]     medNodeCoords;
  delete[]     medCellConn;

  return 0;
}
