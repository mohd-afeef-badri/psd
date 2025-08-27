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
**************************************************************************************/

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
