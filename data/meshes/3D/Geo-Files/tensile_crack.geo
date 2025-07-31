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

ls=1/10.;
lengthBar=1.0;
HeightBar=1.0;
WidthtBar=1.0;
eps=1e-2;

Point(1) = {lengthBar, 0, 0, ls};
Point(2) = {0, 0, 0, ls};
Point(3) = {0, HeightBar, 0, ls};
Point(4) = {0, 0, WidthtBar, ls};
Point(5) = {0, HeightBar, WidthtBar, ls};
Point(6) = {lengthBar, HeightBar, WidthtBar, ls};
Point(7) = {lengthBar, 0, WidthtBar, ls};
Point(8) = {lengthBar, HeightBar, 0, ls};
Point(9) = {0, HeightBar/2+eps, 0, ls};
Point(10) = {0, HeightBar/2-eps, 0, ls};
Point(11) = {0, HeightBar/2+eps, WidthtBar, ls};
Point(12) = {0, HeightBar/2-eps, WidthtBar, ls};
Point(13) = {lengthBar/2, HeightBar/2, 0, ls};
Point(14) = {lengthBar/2, HeightBar/2, WidthtBar, ls};

//+
Line(1) = {4, 7};
//+
Line(2) = {7, 1};
//+
Line(3) = {1, 2};
//+
Line(4) = {2, 4};
//+
Line(5) = {7, 6};
//+
Line(6) = {6, 8};
//+
Line(7) = {8, 1};
//+
Line(8) = {8, 3};
//+
Line(9) = {3, 5};
//+
Line(10) = {5, 6};
//+
Line(11) = {5, 11};
//+
Line(12) = {11, 14};
//+
Line(13) = {14, 12};
//+
Line(14) = {12, 4};
//+
Line(15) = {3, 9};
//+
Line(16) = {9, 13};
//+
Line(17) = {13, 10};
//+
Line(18) = {10, 2};
//+
Line(19) = {13, 14};
//+
Line(20) = {12, 10};
//+
Line(21) = {11, 9};
//+
Curve Loop(1) = {6, 7, -2, 5};
//+
Plane Surface(1) = {1};
//+
Curve Loop(2) = {8, 9, 10, 6};
//+
Plane Surface(2) = {2};
//+
Curve Loop(3) = {2, 3, 4, 1};
//+
Plane Surface(3) = {3};
//+
Curve Loop(4) = {5, -10, 11, 12, 13, 14, 1};
//+
Plane Surface(4) = {4};
//+
Curve Loop(5) = {8, 15, 16, 17, 18, -3, -7};
//+
Plane Surface(5) = {5};
//+
Curve Loop(6) = {9, 11, 21, -15};
//+
Plane Surface(6) = {6};
//+
Curve Loop(7) = {14, -4, -18, -20};
//+
Plane Surface(7) = {7};
//+
Curve Loop(8) = {13, 20, -17, 19};
//+
Plane Surface(8) = {8};
//+
Curve Loop(9) = {12, -19, -16, -21};
//+
Plane Surface(9) = {9};
//+
Surface Loop(1) = {2, 5, 6, 4, 1, 3, 7, 8, 9};
//+
Volume(1) = {1};
//+
Physical Surface("bot-sur") = {3};
//+
Physical Surface("top-sur") = {2};
//+
Physical Surface("other-sur") = {1, 4, 5, 6, 7};
//+
Physical Surface("crack-sur") = {9, 8};
//+
Physical Volume("volumee") = {1};
