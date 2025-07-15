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
*       Comment  : The program test medcoupling for writing a  med  mesh              *
*                  with only  one  single tetrahedral cell. This test is              *
*                  eventually used as building blocks for the PSD plugin              *
*                  medio.                                                             *
*                                                                                     *
**************************************************************************************/

int UnitTest3()
{

// Nodes  of  the  3D mesh
// i.e x,y,z coordinates
double meshNodes[12]={
// x          y     z
0.,0.,1.,
0.,0.,0.,
0.,1.,1.,
1.,1.,1.
};

int  nNodes      = (sizeof(meshNodes)/sizeof(meshNodes[0]))/3;
int  nNodesArray = (sizeof(meshNodes)/sizeof(meshNodes[0]))  ;

// Connectivity for the Cells
// of the 2D mesh
mcIdType cellConnectivity[48]={
0,1,2,3  // tetra
};

  // create mesh
  MEDCouplingUMesh *medMesh3d=MEDCouplingUMesh::New();

  // set basic attributes
  medMesh3d->setMeshDimension(3);          // dimension of the mesh
  medMesh3d->allocateCells(1);             // total number of cells
  medMesh3d->setName("TetrahedralMesh");   // name of mesh

  // add cells manually
  medMesh3d->insertNextCell(INTERP_KERNEL::NORM_TETRA4,4,cellConnectivity);
  medMesh3d->finishInsertingCells();

//---------------------------------------------------------------------------------
// 0D mesh creation i.e the nodes
//---------------------------------------------------------------------------------
  // add nodes
  DataArrayDouble *myCoords=DataArrayDouble::New();
  myCoords->alloc(nNodes,3);                  // tottal number of points
  myCoords->setInfoOnComponent(0,"x [m]");    // info attribute on x
  myCoords->setInfoOnComponent(1,"y [m]");    // info attribute on y
  myCoords->setInfoOnComponent(2,"z [m]");    // info attribute on z
  std::copy(meshNodes, meshNodes+nNodesArray, myCoords->getPointer());
  medMesh3d->setCoords(myCoords);
  myCoords->decrRef();

//---------------------------------------------------------------------------------
// wirte mesh in med and vtu formats
//---------------------------------------------------------------------------------
  WriteUMesh("mcUT3.med",medMesh3d,true);
  medMesh3d->writeVTK("mcUT3n.vtu");

  return 1;
}
