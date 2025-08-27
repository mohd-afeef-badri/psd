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

lc = 1.0/4.0;
lengthBar=1.0;
eps=1e-4;

Point(1) = {0.0 , 0.0 , 0.0 , lc};
Point(2) = {lengthBar , 0.0 , 0.0 , lc};
Point(3) = {lengthBar , 1.0 , 0.0 , lc};
Point(4) = {0.0 , 1.0 , 0.0 , lc};
Point(5) = {0.0 , 0.5+eps , 0.0 , lc};
Point(6) = {0.0 , 0.5-eps , 0.0 , lc};
Point(7) = {0.5 , 0.5 , 0.0 , lc/2};
//+
Line(1) = {1, 2};
//+
Line(2) = {2, 3};
//+
Line(3) = {3, 4};
//+
Line(4) = {4, 5};
//+
Line(5) = {5, 7};
//+
Line(6) = {7, 6};
//+
Line(7) = {6, 1};
//+
Curve Loop(1) = {3, 4, 5, 6, 7, 1, 2};
//+
Plane Surface(1) = {1};
//+
Physical Curve("bot") = {1};
//+
Physical Curve("top") = {3};
//+
Physical Curve("other") = {2, 4, 7};
//+
Physical Curve("mid") = {6, 5};
//+
Physical Surface("sur") = {1};
