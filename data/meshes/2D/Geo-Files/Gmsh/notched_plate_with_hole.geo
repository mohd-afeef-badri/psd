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
Point(11) = {20, 20, 0, 1.0};
//+
Point(12) = {20, 100, 0, 1.0};
//+
Point(13) = {20, 25, 0, 1.0};
//+
Point(14) = {20, 15, 0, 1.0};
//+
Point(15) = {20, 105, 0, 1.0};
//+
Point(16) = {20, 95, 0, 1.0};
//+
Circle(10) = {13, 11, 14};
//+
Circle(11) = {14, 11, 13};
//+
Circle(12) = {15, 12, 16};
//+
Circle(13) = {16, 12, 15};
//+
Curve Loop(1) = {3, 4, 5, 6, 7, 1, 2};
//+
Curve Loop(2) = {13, 12};
//+
Curve Loop(3) = {9, 8};
//+
Curve Loop(4) = {11, 10};
//+
Plane Surface(1) = {1, 2, 3, 4};
//+
Physical Surface("vol") = {1};
//+
Physical Curve("top-hole") = {12, 13};
//+
Physical Curve("bot-hole") = {10, 11};
//+
Physical Curve("crack") = {5,6};
//+
Physical Curve("other") = {4, 7, 1, 2, 3};
//+
Physical Curve("hole") = {8, 9};
