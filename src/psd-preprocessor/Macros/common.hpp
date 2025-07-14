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
*                                                                                     *
* Comment: This support  file is responsible for generating the following macros      *
*            1) perfromRCMreordering - perform mesh level reverse Cuthill-Mackee      *
*            2) startProcedure       - macro to be  placed  before  starting any      *
*                                      procedure in PSD. Acts  as a  placeholder      *
*                                      if no timelogging (-timelog) is requested.     *
*                                      If timelogging this macro also prints the      *
*                                      time and a string message on scree.            *
*            3) endProcedure         - Idem to startProcedure,  but  used at the      *
*                                      end of a PSD procedure.                        *
*            4) remapping-macros     - many macros are proposed  to  uniform  the     *
*                                      names of functions in 2D and 3D.               *
*            5) loadfemesh           - load different the finite  element meshes      *
*                                      based on filename detect the meshloader.       *
*            6) checkemesh           - output error message if unsupported mesh       *
*                                      extension is detected.                         *
*                                                                                     *
*                                                                                     *
**************************************************************************************/



if(Sequential){

codeSnippet R""""(
//=============================================================================
//      ------- remapping Macros -------
// ---------------------------------------------------------------------------
// meshN     : Two/Three-dimensional problem mesh
// intN      : Two/Three-dimensional integral
// intN1     : One/Two-dimensional integral
// grad      : Two/Three-dimensional gradient
// DummyMesh : A unit cube/square mesh in 3D/2D
// readmeshN : Two/Three-dimensional mesh reading .mesh format
// gmshloadN : Two/Three-dimensional mesh reading .msh format
// vtkloadN  : Two/Three-dimensional mesh reading .vtk format
// loadmedmeshN : Two/Three-dimensional mesh reading .med format
//=============================================================================
)"""";

if(spc==3)
codeSnippet R""""(
  load "msh3"                         //
  macro meshN()mesh3                  //
  macro intN()int3d                   //
  macro intN1()int2d                  //
  macro loadmedmeshN()loadmedmesh3    //
  macro readmeshN()readmesh3          //
  macro gmshloadN()gmshload3          //
  macro vtkloadN()vtkload3            //
  macro DummyMesh()cube(1,1,1)        //
  macro grad(i)[dx(i),dy(i),dz(i)]    //
)"""";

if(spc==2)
codeSnippet R""""(
  macro meshN()mesh                   //
  macro intN()int2d                   //
  macro intN1()int1d                  //
  macro loadmedmeshN()loadmedmesh     //
  macro readmeshN()readmesh           //
  macro gmshloadN()gmshload           //
  macro vtkloadN()vtkload             //
  macro DummyMesh()square(1,1)        //
  macro grad(i) [dx(i),dy(i)]         //
)"""";
}else{

codeSnippet R""""(
//=============================================================================
//      ------- remapping Macros -------
// ---------------------------------------------------------------------------
// grad      : Two-dimensional gradient
// DummyMesh : A unit cube/square mesh in 3D/2D
// gmshloadN : Two-dimensional mesh reading .msh format
// vtkloadN  : Two-dimensional mesh reading .vtk format
// loadmedmeshN : Two/Three-dimensional mesh reading .med format
//=============================================================================
)"""";

if(spc==3)
codeSnippet R""""(
  macro loadmedmeshN()loadmedmesh3    //
  macro gmshloadN()gmshload3          //
  macro vtkloadN()vtkload3            //
  macro DummyMesh()cube(1,1,1)        //
  macro grad(i)[dx(i),dy(i),dz(i)]    //
)"""";

if(spc==2)
codeSnippet R""""(
  macro loadmedmeshN()loadmedmesh     //
  macro gmshloadN()gmshload           //
  macro vtkloadN()vtkload             //
  macro DummyMesh()square(1,1)        //
  macro grad(i) [dx(i),dy(i)]         //
)"""";

}

codeSnippet R""""(
//=============================================================================
//            ------ Start and End procedure macros  -------
// -------------------------------------------------------------------
//    Note these macros will print on screen a message at the start
//    and end of a procedure, and also print the time taken by that
//    procedure in seconds. However, -timelog flag needs to be used
//    for this macro, or else this macro will serve as a dummy macro.
// -------------------------------------------------------------------
//=============================================================================
)"""";


if(timelog){

if(!Sequential){

codeSnippet R""""(

//==============================================================================
// ------- startProcedure (string , real) -------
//==============================================================================

  macro startProcedure(str1,t0){
    mpiBarrier(mpiCommWorld);
    t0 = mpiWtime();
    if(mpirank==0)
    cout << "-->"+str1+" began....\n";
  }//

//==============================================================================
// ------- endProcedure (string , real) -------
//==============================================================================

  macro endProcedure(str1,t0){
    mpiBarrier(mpiCommWorld);
    if(mpirank==0)
    cout.scientific << "finished in [ "
                    << mpiWtime()-t0
                    << " ] seconds\n\n";
  }//

)"""";

}else{

codeSnippet R""""(

//==============================================================================
// ------- startProcedure (string , real) -------
//==============================================================================

  macro startProcedure(str1,t0){
    t0 = clock();
    cout << "-->"+str1+" began....\n";
  }//

//==============================================================================
// ------- endProcedure (string , real) -------
//==============================================================================

  macro endProcedure(str1,t0){
    cout.scientific << "finished in [ "
                    << clock()-t0
                    << " ] seconds\n\n";
  }//

)"""";

}

}

if(!timelog){

codeSnippet R""""(

//==============================================================================
// ------- startProcedure (string , real) is a DUMMY macro -------
//==============================================================================

  macro startProcedure(str1,t0)//

//==============================================================================
// ------- endProcedure (string , real) is a DUMMY macro  -------
//==============================================================================

  macro endProcedure(str1,t0)//

)"""";

}


codeSnippet R""""(

//=============================================================================
//            ------ Reverse Cuthill-Mackee macros  -------
// -------------------------------------------------------------------
//    Note this macros will perform mesh element renumberining based
//    on reverse Cuthill-Mackee algorithm. This is On by default  in
//    PSD. User can turn this off by using --useRCM  off | 0 |false.
//    For such a case this macro will serve as a dummy macro.
// -------------------------------------------------------------------
//=============================================================================

)"""";

if(RCM){

codeSnippet R""""(

//==============================================================================
// ------- perfromRCMreordering (meshObject)-------
//==============================================================================

  macro perfromRCMreordering(meshObject)
              meshObject = trunc(meshObject, 1, renum = 1);
  //

)"""";

}

if(!RCM){

codeSnippet R""""(

//==============================================================================
// ------- perfromRCMreordering (meshObject)  is a DUMMY macro  -------
//==============================================================================

  macro perfromRCMreordering(meshObject)//

)"""";

}

#ifdef MEDCOUPLING
codeSnippet R""""(

//=============================================================================
//            ------ load finite element mesh macro  -------
// -------------------------------------------------------------------
//    This macros will take in as an input the mesh name (string)
//    according to which it will load the finite element mesh.
// -------------------------------------------------------------------
//=============================================================================

macro loadfemesh(meshObject,meshName)

  if(meshName.find(".med") > -1){
    load "medio"; meshObject=loadmedmeshN(meshName, meshname = "Mesh_1");
  }
  if(meshName.find(".msh") > -1){
    load "gmsh";   meshObject = gmshloadN(meshName);
  }
  if(meshName.find(".mesh") > -1){
    meshObject = readmeshN(meshName);
  }
  if(meshName.find(".vtk") > -1){
    load "iovtk";  meshObject = vtkloadN(meshName);
  }
//

)"""";

#else

codeSnippet R""""(

//=============================================================================
//            ------ load finite element mesh macro  -------
// -------------------------------------------------------------------
//    This macros will take in as an input the mesh name (string)
//    according to which it will load the finite element mesh.
// -------------------------------------------------------------------
//=============================================================================

macro loadfemesh(meshObject,meshName)

  if(meshName.find(".msh") > -1){
    load "gmsh";   meshObject = gmshloadN(meshName);
  }
  if(meshName.find(".mesh") > -1){
    meshObject = readmeshN(meshName);
  }
  if(meshName.find(".vtk") > -1){
    load "iovtk";  meshObject = vtkloadN(meshName);
  }
//

)"""";
#endif

codeSnippet R""""(

//=============================================================================
//            ------ check mesh macro  -------
// -------------------------------------------------------------------
//    This macros will take in as an input the mesh name (string)
//    and check if this mesh format (extension) is compatible.
// -------------------------------------------------------------------
//=============================================================================

macro checkmesh(meshName)
{
  if( meshName.find(".mesh") == -1 &&
      meshName.find(".med")  == -1 &&
      meshName.find(".msh")  == -1 &&
      meshName.find(".vtk")  == -1
    ){
      cout << "  ****************** ERROR ********************* \n"
           << "                                                 \n"
           << "  PSD only accepts the following mesh formats    \n"
           << "     1) .msh   Gmsh's  .msh  format version 2    \n"
           << "     2) .mesh  INRIA's medit format              \n"
           << "     3) .vtk   VTK's unstructured mesh format    \n"
           << "     4) .med   SALOME's .med format (needs medio)\n"
           << "                                                 \n"
           << "  ****************** ERROR ********************* \n";
      exit(11111);
  }
}
//

)"""";

