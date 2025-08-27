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
*                                                                                     *
* Comment: Use the -format msh2 format to genrate the mesh                            *
*                                                                                     *
**************************************************************************************/

lc = 2.5;
WidthPlate=65.0;
HeightPlate=120.0;
eps=1e-3;

Point(1) = {0.0 , 0.0 , 0.0 , lc};
Point(2) = {WidthPlate , 0.0 , 0.0 , lc};
Point(3) = {WidthPlate , HeightPlate , 0.0 , lc};
Point(4) = {0.0 , HeightPlate , 0.0 , lc};
Point(5) = {36.5 , 61, 0.0 , lc};
Point(6) = {36.5 , 51 , 0.0 , lc};
Point(7) = {36.5 , 41 , 0.0 , lc};
Point(8) = {0 , 65+eps , 0.0 , lc};
Point(9) = {0 , 65-eps , 0.0 , lc};
Point(10) = {10 , 65 , 0.0 , lc};

//+
Line(1) = {1, 2};
//+
Line(2) = {2, 3};
//+
Line(3) = {3, 4};
//+
Line(4) = {4, 8};
//+
Line(5) = {8, 10};
//+
Line(6) = {10, 9};
//+
Line(7) = {9, 1};
//+
Circle(8) = {7, 6, 5};
//+
Circle(9) = {5, 6, 7};
//+
Curve Loop(1) = {3, 4, 5, 6, 7, 1, 2};
//+
Curve Loop(2) = {8, 9};
//+
Plane Surface(1) = {1, 2};
//+
Physical Curve("bot") = {1};
//+
Physical Curve("top") = {3};
//+
Physical Curve("other") = {2, 4, 7};
//+
Physical Curve("mid") = {5,6};
//+
Physical Surface("sur") = {1};
//+
Physical Curve("notch") = {9, 8};
