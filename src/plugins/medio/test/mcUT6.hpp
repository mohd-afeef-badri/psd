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
*       Comment  : The program test medcoupling for reading polygon mesh              *
*                  ew boundary lines and printing  the  families.  These              *
*                  tests are eventually used as building blocks for  the              *
*                  PSD plugin medio.                                                  *
*                                                                                     *
**************************************************************************************/
int UnitTest6()
{

cout << "//-----------------------------------------------------------------//\n"
        "// Starting Unit Test 6\n"
        "//-----------------------------------------------------------------//\n";

//---------------------------------------------------------------------------------
// read mesh in medfile mesh
//---------------------------------------------------------------------------------

  MCAuto < MEDFileUMesh > finalMeshWithLabel = MEDFileUMesh::New("mcUT4.med");
  const DataArrayIdType * famIds  = finalMeshWithLabel->getFamilyFieldAtLevel(0);
  const DataArrayIdType * famIds1d  = finalMeshWithLabel->getFamilyFieldAtLevel(-1);

  for (int i=0; i < famIds->getNumberOfTuples(); i++)
    cout << " cell_family " << famIds->getIJ(i,0) << endl;

  for (int i=0; i < famIds1d->getNumberOfTuples(); i++)
    cout << " boundary_family " << famIds1d->getIJ(i,0) << endl;

  return 1;

}
