/*****************************************************************************

     This file is a part of PSD (Parallel Structural/Seismic/Solid dynamics)

     -------------------------------------------------------------------

     Author(s): Mohd Afeef Badri
     Email    : mohd-afeef.badri@cea.com
     Date     : 01/06/2022
     Comment  : The program collects functions needed by the medio

     -------------------------------------------------------------------

     medio is PSD plugin intended to enable usage of med files within PSD.
     medio is distributed   in  the  hope that it  will be useful, HOWEVER
     WITHOUT ANY WARRANTY;  or  without  even  implied warranty of FITNESS
     FOR A PARTICULAR PURPOSE.

*******************************************************************************/

//------------------------------------------------------------------------------
// getMedLabelsOnGroup: a function get the list (vector) of labels that corres-
//          pond to a group from med file. This function takes in two input st-
//          ing arguments mesh-name and group-name and return the labels that
//          can be used FreeFEM mesh object.
//------------------------------------------------------------------------------

template<typename R>
int getMedLabelsOnGroup( KN<R>* const &part, std::string* const &inputfile, std::string* const &groupName){

#ifdef DEBUG
  cout << "\n"
          "--------------------------------------\n"
          " getting label from med mesh \n"
          "--------------------------------------\n";
#endif

//---------------------------------------------------------------------------------
// read mesh in med
//---------------------------------------------------------------------------------

  MCAuto < MEDFileUMesh > finalMeshWithLabel = MEDFileUMesh::New(*inputfile);

//---------------------------------------------------------------------------------
// Get label list corresponding to boundary tag "groupName"
//---------------------------------------------------------------------------------

  std::vector<R> famIds = finalMeshWithLabel->getFamiliesIdsOnGroup(*groupName);
  part->resize(famIds.size());

  int iter=0;
  for (auto i: famIds){
    part[iter] = i;
    iter++;
    cout << " iter " << iter << " G tage "  << part[iter-1] << endl;
  }

  return 0;
}

/*
//std::vector<long int>
template<typename R>
KN<R>* getMedLabelsOnGroup(Stack stack, KN<R>* const &part, std::string* const &inputfile, std::string* const &groupName){

#ifdef DEBUG
  cout << "\n"
          "--------------------------------------\n"
          " getting label from med mesh \n"
          "--------------------------------------\n";
#endif

//---------------------------------------------------------------------------------
// read mesh in med
//---------------------------------------------------------------------------------

  MCAuto < MEDFileUMesh > finalMeshWithLabel = MEDFileUMesh::New(*inputfile);

//---------------------------------------------------------------------------------
// Get label list corresponding to boundary tag "groupName"
//---------------------------------------------------------------------------------

  std::vector<R> famIds = finalMeshWithLabel->getFamiliesIdsOnGroup(*groupName);
  KN<R> *pc = new KN< R >(famIds.size());
  part->resize(famIds.size());
  KN< R > &c = *pc;

  int iter=0;
  for (auto i: famIds){
    pc[iter] = i;
    iter++;
    cout << " iter " << iter << " G tage "  << c[iter-1] << endl;
  }

  return Add2StackOfPtr2FreeRC(stack, pc);
}
*/
