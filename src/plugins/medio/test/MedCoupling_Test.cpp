/*****************************************************************************

         This file is a part of PDMT (Parallel Dual Meshing Tool)

     -------------------------------------------------------------------

     Author(s): Mohd Afeef Badri
     Email    : mohd-afeef.badri@cea.com
     Date     : 05/04/2022
     Comment  : The program test medcoupling for writing meshes

     -------------------------------------------------------------------

     PDMT a parallel  dual meshing tool uses   finite  element framework
     to convert a triangular / tetrahedral mesh into a  polyhedral  mesh.
     PDMT is distributed  in  the  hope that it  will be useful, HOWEVER
     WITHOUT ANY WARRANTY; or without  even  implied warranty of FITNESS
     FOR A PARTICULAR PURPOSE.

*******************************************************************************/

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

 
