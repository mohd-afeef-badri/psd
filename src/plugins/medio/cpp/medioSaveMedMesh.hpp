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
// medMeshInfo: a function to save an ASSCII text file when saving a med mesh
//------------------------------------------------------------------------------

int medMeshInfo(std::string* const &filename, int Nnodes, int Npoly, int Ntet, int Ntri, int Nseg,
                std::set < int > Lnodes, std::set < int > Lpoly, std::set < int > Ltet, std::set < int > Ltri, std::set < int > Lseg ){


  ofstream infoWrite;
  infoWrite.open(""+* filename+"_INFO.txt");

  infoWrite << "======================================================= \n"
               " info on mesh file < " << * filename << " >'\n"
               "======================================================= \n"
               "\n"
               "Mesh statistics: \n";
  if(Nnodes)
  infoWrite << "  # nodes         " << Nnodes << "\n";

  if(Npoly)
  infoWrite << "  # polygons      " << Npoly << "\n";

  if(Ntet)
  infoWrite << "  # tetrahedrons  " << Ntet << "\n";

  if(Ntri)
  infoWrite << "  # triangles     " << Ntri << "\n";

  if(Nseg)
  infoWrite << "  # edges         " << Nseg << "\n";

  infoWrite << "\nList of families , tags , groups:\n"
               "----------------------------------------------------\n"
               " Name         Family           Tag            Group\n"
               "----------------------------------------------------\n"
               "\n";

  if( Lnodes.size()  ){
    infoWrite << " < nodes > \n";

    for (std::set < int > ::iterator it = Lnodes.begin(); it != Lnodes.end(); ++it) {
      int avoideZero = 0;
      if( * it == 0 ) avoideZero = 1000;
      int tag = * it + avoideZero;
      infoWrite << "              'tria_family_" + to_string( tag ) + "'\t" <<  tag << "\t'tria_group_" + to_string( tag ) + "' " <<  endl;
    }
    infoWrite << "\n";
  }


  if( Lseg.size()  ){
    infoWrite << " < edges > \n";

    for (std::set < int > ::iterator it = Lseg.begin(); it != Lseg.end(); ++it) {
      int avoideZero = 0;
      if( * it == 0 ) avoideZero = 2000;
      int tag = * it + avoideZero;
      infoWrite << "              'edge_family_" + to_string( tag ) + "'\t" <<  tag << "\t'edge_group_" + to_string( tag ) + "' " <<  endl;
    }
    infoWrite << "\n";
  }

  if( Ltri.size()  ){
    infoWrite << " < triangles > \n";

    for (std::set < int > ::iterator it = Ltri.begin(); it != Ltri.end(); ++it) {
      int avoideZero = 0;
      if( * it == 0 ) avoideZero = 3000;
      int tag = * it + avoideZero;
      infoWrite << "              'tria_family_" + to_string( tag ) + "'\t" <<  tag << "\t'tria_group_" + to_string( tag ) + "' " <<  endl;
    }
    infoWrite << "\n";
  }


  if( Lpoly.size()  ){
    infoWrite << " < polyhedra > \n";

    for (std::set < int > ::iterator it = Lpoly.begin(); it != Lpoly.end(); ++it) {
      int avoideZero = 0;
      if( * it == 0 ) avoideZero = 4000;
      int tag = * it + avoideZero;
      infoWrite << "              'poly_family_" + to_string( tag ) + "'\t" <<  tag << "\t'poly_group_" + to_string( tag ) + "' " <<  endl;
    }
    infoWrite << "\n";
  }

  if( Ltet.size()  ){
    infoWrite << " < tetrahedrons > \n";

    for (std::set < int > ::iterator it = Ltet.begin(); it != Ltet.end(); ++it) {
      int avoideZero = 0;
      if( * it == 0 ) avoideZero = 5000;
      int tag = * it + avoideZero;
      infoWrite << "              'tetra_family_" + to_string( tag ) + "'\t" <<  tag << "\t'tetra_group_" + to_string( tag ) + "' " <<  endl;
    }
    infoWrite << "\n";
  }



  infoWrite.close();

  return 0;
}


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
  mcIdType* elems3dFams = new mcIdType[Th.nt];                  // to store families  Tetra
  mcIdType* elems2dFams = new mcIdType[Th.nbe];                 // to store families  Tria

  std::set < int > UniqueLabelsPoint;                         // Store unique labels points    (NOT USED)
  std::set < int > UniqueLabelsTria;                          // Store unique labels triangles
  std::set < int > UniqueLabelsEdge;                          // Store unique labels edges     (NOT USED)
  std::set < int > UniqueLabelsPoly;                          // Store unique labels polygons  (NOT USED)
  std::set < int > UniqueLabelsTetra;                         // Store unique labels tetrahedra


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
    elems3dFams[i]     = Th[i].lab;
    UniqueLabelsTetra.insert(Th[i].lab);
  }

  //  get triangles //
  for (int i = 0; i < Th.nbe; i++) {
    medCellConn[count] = Th(Th.be(i)[0]) ; count++;
    medCellConn[count] = Th(Th.be(i)[1]) ; count++;
    medCellConn[count] = Th(Th.be(i)[2]) ; count++;
    elems2dFams[i]     = Th.be(i).lab;
    UniqueLabelsTria.insert(Th.be(i).lab);
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


  // set up  MEDFileUMesh for families and groups //
  MCAuto<MEDFileUMesh> finalMeshWithLabel = MEDFileUMesh::New();
  finalMeshWithLabel->setMeshAtLevel(0 ,medMesh3d);
  finalMeshWithLabel->setMeshAtLevel(-1,medMesh2d);


  // get families and groups //
  MCAuto < DataArrayIdType > fam3d = DataArrayIdType::New();
  MCAuto < DataArrayIdType > fam2d = DataArrayIdType::New();

  fam3d -> alloc(Th.nt, 1);
  fam2d -> alloc(Th.nbe, 1);

  std::copy(elems3dFams, elems3dFams + Th.nt,  fam3d -> getPointer());
  std::copy(elems2dFams, elems2dFams + Th.nbe, fam2d -> getPointer());

  finalMeshWithLabel -> setFamilyFieldArr(0, fam3d);
  finalMeshWithLabel -> setFamilyFieldArr(-1, fam2d);

  std::map < std::string, std::vector < std::string >> theGroups;
  std::map < std::string, mcIdType > theFamilies;

  for (std::set < int > ::iterator it = UniqueLabelsTetra.begin(); it != UniqueLabelsTetra.end(); ++it) {
    int avoideZero = 0;
    if( * it == 0 ) avoideZero = 5000;
    int tag = * it + avoideZero;
    theFamilies["tetra_family_" + to_string( tag ) + ""] = tag;
    theGroups["tetra_group_" + to_string( tag ) + ""].push_back("tetra_family_" + to_string( tag ) + "");
  }

  for (std::set < int > ::iterator it = UniqueLabelsTria.begin(); it != UniqueLabelsTria.end(); ++it) {
    int avoideZero = 0;
    if(* it == 0) avoideZero = 3000;
    int tag = * it + avoideZero;
    theFamilies["tria_family_" + to_string( tag ) + ""] = * it;
    theGroups["tria_group_" + to_string( * it) + ""].push_back("tria_family_" + to_string( tag ) + "");
  }

  finalMeshWithLabel -> setFamilyInfo(theFamilies);
  finalMeshWithLabel -> setGroupInfo(theGroups);

  // write mesh //
  finalMeshWithLabel -> write( * inputfile, 2);

  // write mesh information file //
  medMeshInfo( inputfile          , // std::string* const &filename,
               Th.nv              , // int Nnodes
               0                  , // int Npoly
               Th.nt              , // int Ntet
               Th.nbe             , // int Ntri
               0                  , // int Nseg
               UniqueLabelsPoint  , // std::set < int > Lnodes
               UniqueLabelsPoly   , // std::set < int > Lpoly
               UniqueLabelsTetra  , // std::set < int > Ltet
               UniqueLabelsTria   , // std::set < int > Ltri
               UniqueLabelsEdge     // std::set < int > Lseg
               );

/*
  // combine meshes 3d + 2d //
  std::vector<const MEDCouplingUMesh *> finalMesh;
  finalMesh.push_back(medMesh3d);
  finalMesh.push_back(medMesh2d);

  // write mesh //
  WriteUMeshes(*inputfile,finalMesh,true);
*/
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
  mcIdType* medCellConn = new mcIdType[Th.nt*3 +Th.neb*2];    // to store mesh elements (elements = Tria + Edges)
  mcIdType* elems2dFams = new mcIdType[Th.nt];                // to store families  Tria
  mcIdType* elems1dFams = new mcIdType[Th.neb];               // to store families  Edges

  std::set < int > UniqueLabelsPoint;                         // Store unique labels points    (NOT USED)
  std::set < int > UniqueLabelsTria;                          // Store unique labels triangles
  std::set < int > UniqueLabelsEdge;                          // Store unique labels edges
  std::set < int > UniqueLabelsPoly;                          // Store unique labels polygons  (NOT USED)
  std::set < int > UniqueLabelsTetra;                         // Store unique labels tetrahedra(NOT USED)

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
    elems2dFams[i]     = Th[i].lab;
    UniqueLabelsTria.insert(Th[i].lab);
  }

  //  get edges  //
  for (int i = 0; i < Th.neb; i++) {
    medCellConn[count] = Th(Th.be(i)[0]) ; count++;
    medCellConn[count] = Th(Th.be(i)[1]) ; count++;
    elems1dFams[i]     = Th.be(i).lab;
    UniqueLabelsEdge.insert(Th.be(i).lab);
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

  // set up  MEDFileUMesh for families and groups //
  MCAuto<MEDFileUMesh> finalMeshWithLabel = MEDFileUMesh::New();
  finalMeshWithLabel->setMeshAtLevel(0 ,medMesh2d);
  finalMeshWithLabel->setMeshAtLevel(-1,medMesh1d);


  // get families and groups //
  MCAuto < DataArrayIdType > fam2d = DataArrayIdType::New();
  MCAuto < DataArrayIdType > fam1d = DataArrayIdType::New();

  fam2d -> alloc(Th.nt, 1);
  fam1d -> alloc(Th.neb, 1);

  std::copy(elems2dFams, elems2dFams + Th.nt,  fam2d -> getPointer());
  std::copy(elems1dFams, elems1dFams + Th.neb, fam1d -> getPointer());

  finalMeshWithLabel -> setFamilyFieldArr(-1, fam1d);
  finalMeshWithLabel -> setFamilyFieldArr(0, fam2d);

  std::map < std::string, std::vector < std::string >> theGroups;
  std::map < std::string, mcIdType > theFamilies;

  for (std::set < int > ::iterator it = UniqueLabelsTria.begin(); it != UniqueLabelsTria.end(); ++it) {
    int avoideZero = 0;
    if(* it == 0) avoideZero = 3000;
    int tag = * it + avoideZero;
    theFamilies["tria_family_" + to_string( tag ) + ""] = tag;
    theGroups["tria_group_" + to_string( tag ) + ""].push_back("tria_family_" + to_string( tag ) + "");
  }

  for (std::set < int > ::iterator it = UniqueLabelsEdge.begin(); it != UniqueLabelsEdge.end(); ++it) {
    int avoideZero = 0;
    if(* it == 0) avoideZero = 2000;
    int tag = * it + avoideZero;
    theFamilies["edge_family_" + to_string( tag ) + ""] = * it;
    theGroups["edge_group_" + to_string( * it) + ""].push_back("edge_family_" + to_string( tag ) + "");
  }

  finalMeshWithLabel -> setFamilyInfo(theFamilies);
  finalMeshWithLabel -> setGroupInfo(theGroups);

  // write mesh //
  finalMeshWithLabel -> write( * inputfile, 2);

  // write mesh information file //
  medMeshInfo( inputfile          , // std::string* const &filename,
               Th.nv              , // int Nnodes
               0                  , // int Npoly
               0                  , // int Ntet
               Th.nt              , // int Ntri
               Th.neb             , // int Nseg
               UniqueLabelsPoint  , // std::set < int > Lnodes
               UniqueLabelsPoly   , // std::set < int > Lpoly
               UniqueLabelsTetra  , // std::set < int > Ltet
               UniqueLabelsTria   , // std::set < int > Ltri
               UniqueLabelsEdge     // std::set < int > Lseg
               );

/*
  // combine meshes 2d + 1d //
  std::vector<const MEDCouplingUMesh *> finalMesh;
  finalMesh.push_back(medMesh2d);
  finalMesh.push_back(medMesh1d);

  // write mesh //
  WriteUMeshes(*inputfile,finalMesh,true);
*/

  // free memory //
  medMesh1d  -> decrRef();
  medMesh2d  -> decrRef();
  myCoords   -> decrRef();
  delete[]     medNodeCoords;
  delete[]     medCellConn;
  delete[]     elems2dFams;
  delete[]     elems1dFams;

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
  mcIdType* elems2dFams = new mcIdType[Th.nt];                // to store families  Tria
  mcIdType* elems1dFams = new mcIdType[Th.nbe];               // to store families  Edges

  std::set < int > UniqueLabelsPoint;                         // Store unique labels points    (NOT USED)
  std::set < int > UniqueLabelsTria;                          // Store unique labels triangles
  std::set < int > UniqueLabelsEdge;                          // Store unique labels edges
  std::set < int > UniqueLabelsPoly;                          // Store unique labels polygons  (NOT USED)
  std::set < int > UniqueLabelsTetra;                         // Store unique labels tetrahedra(NOT USED)

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
    elems2dFams[i]     = Th[i].lab;
    UniqueLabelsTria.insert(Th[i].lab);
  }

  //  get edges  //
  for (int i = 0; i < Th.nbe; i++) {
    medCellConn[count] = Th(Th.be(i)[0]) ; count++;
    medCellConn[count] = Th(Th.be(i)[1]) ; count++;
    elems1dFams[i]     = Th.be(i).lab;
    UniqueLabelsEdge.insert(Th.be(i).lab);
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


  // set up  MEDFileUMesh for families and groups //
  MCAuto<MEDFileUMesh> finalMeshWithLabel = MEDFileUMesh::New();
  finalMeshWithLabel->setMeshAtLevel(0 ,medMesh2d);
  finalMeshWithLabel->setMeshAtLevel(-1,medMesh1d);

  // get families and groups //
  MCAuto < DataArrayIdType > fam2d = DataArrayIdType::New();
  MCAuto < DataArrayIdType > fam1d = DataArrayIdType::New();

  fam2d -> alloc(Th.nt, 1);
  fam1d -> alloc(Th.nbe, 1);

  std::copy(elems2dFams, elems2dFams + Th.nt,  fam2d -> getPointer());
  std::copy(elems1dFams, elems1dFams + Th.nbe, fam1d -> getPointer());

  finalMeshWithLabel -> setFamilyFieldArr(-1, fam1d);
  finalMeshWithLabel -> setFamilyFieldArr(0, fam2d);

  std::map < std::string, std::vector < std::string >> theGroups;
  std::map < std::string, mcIdType > theFamilies;

  for (std::set < int > ::iterator it = UniqueLabelsTria.begin(); it != UniqueLabelsTria.end(); ++it) {
    int avoideZero = 0;
    if(* it == 0) avoideZero = 3000;
    int tag = * it + avoideZero;
    theFamilies["tria_family_" + to_string( tag ) + ""] = tag;
    theGroups["tria_group_" + to_string( tag ) + ""].push_back("tria_family_" + to_string( tag ) + "");
  }

  for (std::set < int > ::iterator it = UniqueLabelsEdge.begin(); it != UniqueLabelsEdge.end(); ++it) {
    int avoideZero = 0;
    if(* it == 0) avoideZero = 2000;
    int tag = * it + avoideZero;
    theFamilies["edge_family_" + to_string( tag ) + ""] = * it;
    theGroups["edge_group_" + to_string( * it) + ""].push_back("edge_family_" + to_string( tag ) + "");
  }

  finalMeshWithLabel -> setFamilyInfo(theFamilies);
  finalMeshWithLabel -> setGroupInfo(theGroups);

  // write mesh //
  finalMeshWithLabel -> write( * inputfile, 2);

  // write mesh information file //
  medMeshInfo( inputfile          , // std::string* const &filename,
               Th.nv              , // int Nnodes
               0                  , // int Npoly
               0                  , // int Ntet
               Th.nt              , // int Ntri
               Th.nbe             , // int Nseg
               UniqueLabelsPoint  , // std::set < int > Lnodes
               UniqueLabelsPoly   , // std::set < int > Lpoly
               UniqueLabelsTetra  , // std::set < int > Ltet
               UniqueLabelsTria   , // std::set < int > Ltri
               UniqueLabelsEdge     // std::set < int > Lseg
               );

/*
  // combine meshes 3ds + 1d //
  std::vector<const MEDCouplingUMesh *> finalMesh;
  finalMesh.push_back(medMesh2d);
  finalMesh.push_back(medMesh1d);

  // write mesh //
  WriteUMeshes(*inputfile,finalMesh,true);
*/
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
  mcIdType* elems1dFams = new mcIdType[Th.nt];                // to store families  Edges

  std::set < int > UniqueLabelsPoint;                         // Store unique labels points    (NOT USED)
  std::set < int > UniqueLabelsTria;                          // Store unique labels triangles
  std::set < int > UniqueLabelsEdge;                          // Store unique labels edges
  std::set < int > UniqueLabelsPoly;                          // Store unique labels polygons  (NOT USED)
  std::set < int > UniqueLabelsTetra;                         // Store unique labels tetrahedra(NOT USED)

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
    elems1dFams[i]     = Th[i].lab;
    UniqueLabelsTria.insert(Th[i].lab);
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

  // set up  MEDFileUMesh for families and groups //
  MCAuto<MEDFileUMesh> finalMeshWithLabel = MEDFileUMesh::New();
  finalMeshWithLabel->setMeshAtLevel(0 ,medMesh1d);

  // get families and groups //
  MCAuto < DataArrayIdType > fam1d = DataArrayIdType::New();

  fam1d -> alloc(Th.nt, 1);

  std::copy(elems1dFams, elems1dFams + Th.nt,  fam1d -> getPointer());

  finalMeshWithLabel -> setFamilyFieldArr(0, fam1d);

  std::map < std::string, std::vector < std::string >> theGroups;
  std::map < std::string, mcIdType > theFamilies;

  for (std::set < int > ::iterator it = UniqueLabelsEdge.begin(); it != UniqueLabelsEdge.end(); ++it) {
    int avoideZero = 0;
    if(* it == 0) avoideZero = 2000;
    int tag = * it + avoideZero;
    theFamilies["edge_family_" + to_string( tag ) + ""] = * it;
    theGroups["edge_group_" + to_string( * it) + ""].push_back("edge_family_" + to_string( tag ) + "");
  }

  finalMeshWithLabel -> setFamilyInfo(theFamilies);
  finalMeshWithLabel -> setGroupInfo(theGroups);

  // write mesh //
  finalMeshWithLabel -> write( * inputfile, 2);

  // write mesh information file //
  medMeshInfo( inputfile          , // std::string* const &filename,
               Th.nv              , // int Nnodes
               0                  , // int Npoly
               0                  , // int Ntet
               0                  , // int Ntri
               Th.nt              , // int Nseg
               UniqueLabelsPoint  , // std::set < int > Lnodes
               UniqueLabelsPoly   , // std::set < int > Lpoly
               UniqueLabelsTetra  , // std::set < int > Ltet
               UniqueLabelsTria   , // std::set < int > Ltri
               UniqueLabelsEdge     // std::set < int > Lseg
               );


/*
  // write mesh //
  std::vector<const MEDCouplingUMesh *> finalMesh;
  finalMesh.push_back(medMesh1d);
  WriteUMeshes(*inputfile,finalMesh,true);
*/
  // free memory //
  medMesh1d  -> decrRef();
  myCoords   -> decrRef();
  delete[]     medNodeCoords;
  delete[]     medCellConn;

  return 0;
}
