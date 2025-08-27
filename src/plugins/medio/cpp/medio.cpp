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

#include "ff++.hpp"

#include "MEDLoader.hxx"
#include "MEDFileData.hxx"
using namespace MEDCoupling;

#include "medioSaveMedMesh.hpp"
#include "medioLoadMedMesh.hpp"
#include "medioGetGroupLabel.hpp"
#include "medio.hpp"

using namespace std;
using namespace Fem2D;

static void InitFF()
{


  Global.Add("savemedmesh", "(", new OneOperator2_< int,  pmesh3, std::string* >(savemedmesh));
  Global.Add("savemedmesh", "(", new OneOperator2_< int,  pmesh,  std::string* >(savemedmesh));
  Global.Add("savemedmesh", "(", new OneOperator2_< int,  pmeshS, std::string* >(savemedmesh));
  Global.Add("savemedmesh", "(", new OneOperator2_< int,  pmeshL, std::string* >(savemedmesh));
//Global.Add("getMedLabelsOnGroup", "(", new OneOperator3s_< KN< long > *,  KN< long > *, std::string*, std::string* >(getMedLabelsOnGroup)); // also needs // #include "AFunction_ext.hpp" 
  Global.Add("getMedLabelsOnGroup", "(", new OneOperator3_< int, KN< long > *, std::string*, std::string* >(getMedLabelsOnGroup));
  Global.Add("loadmedmesh", "(", new medloader);
  Global.Add("loadmedmesh3", "(", new medloader3);
  Global.Add("loadmedmeshS", "(", new medloaderS);
  Global.Add("loadmedmeshL", "(", new medloaderL);
}
LOADFUNC(InitFF)
