/*****************************************************************************

     This file is a part of PSD (Parallel Structural/Seismic/Solid dynamics)

     -------------------------------------------------------------------

     Author(s): Mohd Afeef Badri
     Email    : mohd-afeef.badri@cea.com
     Date     : 01/06/2022
     Comment  : The program test medcoupling for reading a  med  mesh
                and given a name for the groups returns the family ids.

     -------------------------------------------------------------------

     medio is PSD plugin intended to enable usage of med files within PSD.
     medio is distributed   in  the  hope that it  will be useful, HOWEVER
     WITHOUT ANY WARRANTY;  or  without  even  implied warranty of FITNESS
     FOR A PARTICULAR PURPOSE.

     -------------------------------------------------------------------

     Acknowledgements: Thanks to C. Bourcier for his advices and help
     with medCoupling.

*******************************************************************************/
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
