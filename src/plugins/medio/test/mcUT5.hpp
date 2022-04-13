/*****************************************************************************

     This file is a part of PSD (Parallel Structural/Seismic/Solid dynamics)

     -------------------------------------------------------------------

     Author(s): Mohd Afeef Badri
     Email    : mohd-afeef.badri@cea.com
     Date     : 13/04/2022
     Comment  : The program test medcoupling for reading a  med  mesh
                and printing the stats around it, e.g., nodes, cells.
                This test is eventually  used as  building blocks for
                the PSD plugin medio.

     -------------------------------------------------------------------

     medio is PSD plugin intended to enable usage of med files within PSD.
     medio is distributed   in  the  hope that it  will be useful, HOWEVER
     WITHOUT ANY WARRANTY;  or  without  even  implied warranty of FITNESS
     FOR A PARTICULAR PURPOSE.

     -------------------------------------------------------------------

     Acknowledgements: Thanks to C. Bourcier for his advices and help
     with medCoupling.

*******************************************************************************/
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
