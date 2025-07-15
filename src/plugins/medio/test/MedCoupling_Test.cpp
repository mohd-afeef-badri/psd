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
*       Comment  : The program test medcoupling for writing meshes                    *
*                                                                                     *
**************************************************************************************/

#include <iostream>

#include "MEDLoader.hxx"
#include "MEDLoaderBase.hxx"
#include "MEDCouplingUMesh.hxx"
#include "MEDCouplingFieldDouble.hxx"
#include "MEDCouplingFieldFloat.hxx"
#include "MEDCouplingMemArray.hxx"

#include "MEDFileData.hxx"

using namespace std;
using namespace MEDCoupling;

#include "mcUT1.hpp"
#include "mcUT2.hpp"
#include "mcUT3.hpp"
#include "mcUT4.hpp"
#include "mcUT5.hpp"
#include "mcUT6.hpp"
#include "mcUT7.hpp"

int main(){

int err = UnitTest1();
    err = UnitTest2();
    err = UnitTest3();
    err = UnitTest4();
    err = UnitTest5();
    err = UnitTest6();
    err = UnitTest7();
return 1;
}

 
