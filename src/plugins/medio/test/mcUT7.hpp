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
*       Comment  : The program test medcoupling for reading a  med  mesh              *
*                  and given a name for the groups returns the family ids.            *
*                                                                                     *
**************************************************************************************/
int UnitTest7()
{


cout << "//-----------------------------------------------------------------//\n"
        "// Starting Unit Test 7\n"
        "//-----------------------------------------------------------------//\n";

//---------------------------------------------------------------------------------
// read mesh in med
//---------------------------------------------------------------------------------

  MCAuto < MEDFileUMesh > finalMeshWithLabel = MEDFileUMesh::New("mcUT4.med");

  cout << "done reading mcUT4.med " << endl;
  cout << "\n\n " << endl;

//---------------------------------------------------------------------------------
// Get label list corresponding to boundary tag
//---------------------------------------------------------------------------------

  std::vector<long int> famIdsPruned = finalMeshWithLabel->getFamiliesIdsOnGroup("boundary"); 
  for (auto i: famIdsPruned)
    cout << " famIdsPruned - boundary  " << i << endl;

//---------------------------------------------------------------------------------
// Get label list corresponding to zone_3 tag
//---------------------------------------------------------------------------------
  std::vector<long int> famIdsPruned1 = finalMeshWithLabel->getFamiliesIdsOnGroup("zone_3");
  for (auto i: famIdsPruned1)
    cout << " famIdsPruned - zone_3  " << i << endl;  

  return 1;

}
