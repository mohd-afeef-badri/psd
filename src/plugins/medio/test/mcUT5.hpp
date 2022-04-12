/*****************************************************************************

         This file is a part of PDMT (Parallel Dual Meshing Tool)

     -------------------------------------------------------------------

     Author(s): Mohd Afeef Badri
     Email    : mohd-afeef.badri@cea.com
     Date     : 05/04/2022
     Comment  : The program test medcoupling for writing polygon with
                few boundary lines and groups and famalies

     -------------------------------------------------------------------

     PDMT a parallel  dual meshing tool uses   finite  element framework
     to convert a triangular / tetrahedral mesh into a  polyhedral  mesh.
     PDMT is distributed  in  the  hope that it  will be useful, HOWEVER
     WITHOUT ANY WARRANTY; or without  even  implied warranty of FITNESS
     FOR A PARTICULAR PURPOSE.

*******************************************************************************/
int UnitTest5()
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
  medMesh3d->setName("TetraMesh");          // name of mesh

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
  WriteUMesh("mcUT5.med",medMesh3d,true);
  medMesh3d->writeVTK("mcUT5.vtu");

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
