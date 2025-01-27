/*****************************************************************************

     This file is a part of PSD (Parallel Structural/Seismic/Solid dynamics)

     -------------------------------------------------------------------

     Author(s): Mohd Afeef Badri
     Email    : mohd-afeef.badri@cea.com
     Date     : 05/04/2022
     Comment  : The program test medcoupling for writing polygon mesh
                with polygon elements  without  border elements. This
                test  is  eventually used as building blocks for  the
                PSD plugin medio.

     -------------------------------------------------------------------

     medio is PSD plugin intended to enable usage of med files within PSD.
     medio is distributed   in  the  hope that it  will be useful, HOWEVER
     WITHOUT ANY WARRANTY;  or  without  even  implied warranty of FITNESS
     FOR A PARTICULAR PURPOSE.

     -------------------------------------------------------------------

     Acknowledgements: Thanks to C. Bourcier for his advices and help
     with medCoupling.

*******************************************************************************/

int UnitTest1()
{

// Nodes  of  the  2D mesh
// i.e x and y coordinates
double meshNodes[48]={
// x          y
0.333333 ,0.166667,
0.166667 ,0.333333,
0.833333 ,0.166667,
0.666667 ,0.333333,
0.333333 ,0.666667,
0.166667 ,0.833333,
0.833333 ,0.666667,
0.666667 ,0.833333,
0	 ,0,
0.5	 ,0,
1	 ,0,
0	 ,0.5,
1	 ,0.5,
0	 ,1,
0.5	 ,1,
1	 ,1,
0.25	 ,0,
0.75	 ,0,
1	 ,0.25,
1	 ,0.75,
0.25	 ,1,
0.75	 ,1,
0	 ,0.25,
0	 ,0.75
};

int  nNodes      = (sizeof(meshNodes)/sizeof(meshNodes[0]))/2;
int  nNodesArray = (sizeof(meshNodes)/sizeof(meshNodes[0]))  ;

// Connectivity for the Cells
// of the 2D mesh
mcIdType cellConnectivity[48]={
16, 0,  1,  22, 8,         // polygon
16, 9,  17, 2,  3,  0,     // polygon
17, 10, 18, 2,             // polygon
22, 1,  4,  5,  23, 11,    // polygon
0 ,3 , 6  ,7 , 4, 1,       // polygon
2 ,18, 12 ,19, 6, 3,       // polygon
23,5,  20 ,13,             // polygon
4 ,7 , 21 ,14 ,20, 5,      // polygon
6 ,19, 15 ,21, 7           // polygon
};

  // create mesh
  MEDCouplingUMesh *medMesh2d=MEDCouplingUMesh::New();

  // set basic attributes
  medMesh2d->setMeshDimension(2);           // dimension of the mesh
  medMesh2d->allocateCells(10);             // total number of cells
  medMesh2d->setName("PolyMesh");           // name of mesh

  // add cells manually
  medMesh2d->insertNextCell(INTERP_KERNEL::NORM_POLYGON,5,cellConnectivity);
  medMesh2d->insertNextCell(INTERP_KERNEL::NORM_POLYGON,6,cellConnectivity+5);
  medMesh2d->insertNextCell(INTERP_KERNEL::NORM_POLYGON,4,cellConnectivity+11);
  medMesh2d->insertNextCell(INTERP_KERNEL::NORM_POLYGON,6,cellConnectivity+15);
  medMesh2d->insertNextCell(INTERP_KERNEL::NORM_POLYGON,6,cellConnectivity+21);
  medMesh2d->insertNextCell(INTERP_KERNEL::NORM_POLYGON,6,cellConnectivity+27);
  medMesh2d->insertNextCell(INTERP_KERNEL::NORM_POLYGON,4,cellConnectivity+33);
  medMesh2d->insertNextCell(INTERP_KERNEL::NORM_POLYGON,6,cellConnectivity+37);
  medMesh2d->insertNextCell(INTERP_KERNEL::NORM_POLYGON,5,cellConnectivity+43);
  medMesh2d->finishInsertingCells();

//---------------------------------------------------------------------------------
// 0D mesh creation i.e the nodes
//---------------------------------------------------------------------------------
  // add nodes
  DataArrayDouble *myCoords=DataArrayDouble::New();
  myCoords->alloc(nNodes,2);                  // tottal number of points
  myCoords->setInfoOnComponent(0,"x [m]");    // info attribute on x
  myCoords->setInfoOnComponent(1,"y [m]");    // info attribute on y
  std::copy(meshNodes, meshNodes+nNodesArray, myCoords->getPointer());
  medMesh2d->setCoords(myCoords);
  myCoords->decrRef();

//---------------------------------------------------------------------------------
// wirte mesh in med and vtu formats
//---------------------------------------------------------------------------------
  WriteUMesh("mcUT1.med",medMesh2d,true);
  medMesh2d->writeVTK("mcUT1.vtu");

  return 1;
}

