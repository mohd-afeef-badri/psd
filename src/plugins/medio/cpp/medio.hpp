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

  //  get cells  //
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
  myCoords -> alloc(Th.nv, 3);
  myCoords -> setInfoOnComponent(0, "x");
  myCoords -> setInfoOnComponent(1, "y");
  myCoords -> setInfoOnComponent(2, "z");
  std::copy(medNodeCoords, medNodeCoords + Th.nv*3, myCoords -> getPointer());
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

  //  get cells  //
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
  myCoords -> alloc(Th.nv, 2);
  myCoords -> setInfoOnComponent(0, "x");
  myCoords -> setInfoOnComponent(1, "y");
  std::copy(medNodeCoords, medNodeCoords + Th.nv*2, myCoords -> getPointer());
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

  //  get cells  //
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
  myCoords -> alloc(Th.nv, 3);
  myCoords -> setInfoOnComponent(0, "x");
  myCoords -> setInfoOnComponent(1, "y");
  myCoords -> setInfoOnComponent(2, "z");
  std::copy(medNodeCoords, medNodeCoords + Th.nv*3, myCoords -> getPointer());
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

  //  get cells  //
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
  myCoords -> alloc(Th.nv, 3);
  myCoords -> setInfoOnComponent(0, "x");
  myCoords -> setInfoOnComponent(1, "y");
  myCoords -> setInfoOnComponent(2, "z");
  std::copy(medNodeCoords, medNodeCoords + Th.nv*3, myCoords -> getPointer());
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



Mesh *loadmed(std::string &inputfile, std::string &meshname){

#ifdef DEBUG
  cout << "\n"
          "--------------------------------------\n"
          " loading med mesh \n"
          "--------------------------------------\n";
#endif

  MEDCouplingUMesh *mesh=ReadUMeshFromFile(inputfile,meshname,0);
  MEDCouplingUMesh *mesh1d=ReadUMeshFromFile(inputfile,meshname,-1);

  int nv, nt = 0, nbe = 0, ret;
  Mesh::Vertex *vff;

  nv = mesh->getNumberOfNodes();
  vff = new Mesh::Vertex[nv];

  double *nodesRead ;
  nodesRead = mesh->getCoords()->getPointer();

  for (int i=0; i < nv; i++){
    vff[i].x = nodesRead[i*2  ];
    vff[i].y = nodesRead[i*2+1];
    vff[i].lab = 1;
  }

  nt = mesh->getNumberOfCells();
  Mesh::Triangle *tff = new Mesh::Triangle[nt];
  Mesh::Triangle *ttff = tff;

  mcIdType *NodalConnectivity ;
  NodalConnectivity = mesh->getNodalConnectivity()->getPointer();
  for (int i=0; i < mesh->getNumberOfCells(); i++)
    (ttff++)->set(vff, NodalConnectivity[i*4 + 1], NodalConnectivity[i*4 + 2], NodalConnectivity[i*4 + 3], NodalConnectivity[i*4 + 0]);

  nbe = mesh1d->getNumberOfCells();
  Mesh::BorderElement *bff = new Mesh::BorderElement[nbe];
  Mesh::BorderElement *bbff = bff;

  mcIdType *NodalConnectivity1d ;
  NodalConnectivity1d = mesh1d->getNodalConnectivity()->getPointer();
  for (int i=0; i < mesh1d->getNumberOfCells(); i++)
    (bbff++)->set(vff, NodalConnectivity1d[i*3 + 1], NodalConnectivity1d[i*3 + 2], NodalConnectivity1d[i*3 + 0]);


  Mesh *pTh = new Mesh(nv, nt, nbe, vff, tff, bff);
  return pTh;
}



Mesh3 *loadmed3(std::string &inputfile, std::string &meshname){

#ifdef DEBUG
  cout << "\n"
          "--------------------------------------\n"
          " loading med mesh \n"
          "--------------------------------------\n";
#endif

  MEDCouplingUMesh *mesh=ReadUMeshFromFile(inputfile,meshname,0);
  MEDCouplingUMesh *mesh2d=ReadUMeshFromFile(inputfile,meshname,-1);

  int nv, nt = 0, nbe = 0, ret;
  Vertex3 *vff;

  nv = mesh->getNumberOfNodes();
  vff = new Vertex3[nv];

  double *nodesRead ;
  nodesRead = mesh->getCoords()->getPointer();

  for (int i=0; i < nv; i++){
    vff[i].x = nodesRead[i*3  ];
    vff[i].y = nodesRead[i*3+1];
    vff[i].z = nodesRead[i*3+2];
    vff[i].lab = 1;
  }

  nt = mesh->getNumberOfCells();
  Tet *tff = new Tet[nt];
  Tet *ttff = tff;

  mcIdType *NodalConnectivity ;
  NodalConnectivity = mesh->getNodalConnectivity()->getPointer();

  int indexTet[4];
  for (int i=0; i < mesh->getNumberOfCells(); i++){
    indexTet[0]= NodalConnectivity[i*5 + 1];
    indexTet[1]= NodalConnectivity[i*5 + 2];
    indexTet[2]= NodalConnectivity[i*5 + 3];
    indexTet[3]= NodalConnectivity[i*5 + 4];
    (ttff++)->set(vff, indexTet, NodalConnectivity[i*5 + 0]);
  }

  nbe = mesh2d->getNumberOfCells();
  Triangle3 *bff = new Triangle3[nbe];
  Triangle3 *bbff = bff;

  mcIdType *NodalConnectivity1d ;
  NodalConnectivity1d = mesh2d->getNodalConnectivity()->getPointer();

  int indexTria[3];
  for (int i=0; i < mesh2d->getNumberOfCells(); i++){
    indexTria[0]= NodalConnectivity1d[i*4 + 1];
    indexTria[1]= NodalConnectivity1d[i*4 + 2];
    indexTria[2]= NodalConnectivity1d[i*4 + 3];
    (bbff++)->set(vff, indexTria, NodalConnectivity1d[i*4 + 0]);

  }


  Mesh3 *pTh3 = new Mesh3(nv, nt, nbe, vff, tff, bff);
  return pTh3;
}


class medloader_Op : public E_F0mps
{
public:
    Expression filename			                ;

    static const int n_name_param = 1		        ;
    static basicAC_F0::name_and_type name_param[]	;
    Expression nargs[n_name_param]			;

    medloader_Op(const basicAC_F0& args		,
                      Expression param1
                     ) :
        filename     (param1)
    {
        args.SetNameParam(n_name_param	,
                          name_param	,
                          nargs
                         )		;
    }

    AnyType operator()(Stack stack) const		;
};


basicAC_F0::name_and_type medloader_Op::name_param[] =
{
    {"meshname", &typeid(std::string*)}
};

class medloader : public OneOperator
{
public:
  medloader() : OneOperator(atype< pmesh >( ), atype< string * >( )) {}

  E_F0 *code(const basicAC_F0 &args) const {
    return new medloader_Op(args, t[0]->CastTo(args[0]));
  }
};

AnyType medloader_Op::operator()(Stack stack) const
{
  string* inputfile  = GetAny<string*>((*filename)(stack))	;
  string* meshname   = nargs[0] ? GetAny<std::string*>((*nargs[0])(stack)) : NULL;

  Mesh *Th = loadmed(*inputfile, *meshname);
  Add2StackOfPtr2FreeRC(stack, Th);
  return Th;
}




class medloader3_Op : public E_F0mps
{
public:
    Expression filename			                ;

    static const int n_name_param = 1		        ;
    static basicAC_F0::name_and_type name_param[]	;
    Expression nargs[n_name_param]			;

 public:
    medloader3_Op(const basicAC_F0& args		,
                      Expression param1
                     ) :
        filename     (param1)
    {
        args.SetNameParam(n_name_param	,
                          name_param	,
                          nargs
                         )		;
    }

    AnyType operator()(Stack stack) const		;
};


basicAC_F0::name_and_type medloader3_Op::name_param[] =
{
    {"meshname", &typeid(std::string*)}
};

class medloader3 : public OneOperator
{
public:
  medloader3() : OneOperator(atype< pmesh3 >( ), atype< string * >( )) {}

  E_F0 *code(const basicAC_F0 &args) const {
    return new medloader3_Op(args, t[0]->CastTo(args[0]));
  }
};

AnyType medloader3_Op::operator()(Stack stack) const
{
  string* inputfile  = GetAny<string*>((*filename)(stack))	;
  string* meshname   = nargs[0] ? GetAny<std::string*>((*nargs[0])(stack)) : NULL;

  Mesh3 *Th3 = loadmed3(*inputfile, *meshname);
  Add2StackOfPtr2FreeRC(stack, Th3);
  return Th3;
}
