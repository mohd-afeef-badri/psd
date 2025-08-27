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
*       Comment  : The program test medcoupling for reading a  med  mesh              *
*                  and printing the stats around it, e.g., nodes, cells.              *
*                  This test is eventually  used as  building blocks for              *
*                  the PSD plugin medio.                                              *
*                                                                                     *
**************************************************************************************/
int UnitTest5()
{

//---------------------------------------------------------------------------------
// read mesh in med
//---------------------------------------------------------------------------------

  MEDCouplingUMesh *mesh=ReadUMeshFromFile("mcUT3.med","TetrahedralMesh",0);
  cout << "done reading " << endl;
  cout << "\n\n " << endl;

  cout << " mesh->getSpaceDimension()" << mesh->getSpaceDimension()<< endl;
  cout << " mesh->getMeshDimension() " << mesh->getMeshDimension() << endl;
  cout << " mesh->getNumberOfCells() " << mesh->getNumberOfCells() << endl;
  cout << " mesh->getNumberOfNodes() " << mesh->getNumberOfNodes() << endl;
  cout << "\n\n " << endl;

  double *nodesRead ;
  nodesRead = mesh->getCoords()->getPointer();

  for (int i=0; i < mesh->getNumberOfNodes()*mesh->getMeshDimension(); i++)
    cout << " nodesRead["<<i<<"] " << nodesRead[i] << endl;
  cout << "\n\n " << endl;

  mcIdType *NodalConnectivity ;
  NodalConnectivity = mesh->getNodalConnectivity()->getPointer();
  for (int i=0; i < mesh->getNumberOfCells()*3+mesh->getNumberOfCells(); i++)
    cout << " NodalConnectivity["<<i<<"] " << NodalConnectivity[i] << endl;

  mcIdType *NodalConnectivityIndex ;
  NodalConnectivityIndex = mesh->getNodalConnectivityIndex()->getPointer();
  for (int i=0; i < mesh->getNumberOfCells()+1; i++)
    cout << " NodalConnectivityIndex["<<i<<"] " << NodalConnectivityIndex[i] << endl;

  mesh->decrRef();


  return 1;

}
