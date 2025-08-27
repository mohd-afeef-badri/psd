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

lc = 8.0;
thickness=250.0;
loadpoint=30.0;
eps=1e-4;

Point(1) = {0.0 , 0.0 , 0.0 , lc};
Point(2) = {thickness , 0.0 , 0.0 , lc};
Point(3) = {thickness , thickness , 0.0 , lc};
Point(4) = {thickness+(thickness-loadpoint) , thickness, 0.0 , lc};
Point(5) = {thickness+(thickness), thickness, 0.0 , lc};
Point(6) = {thickness+(thickness), thickness+(thickness), 0.0 , lc};
Point(7) = {0., thickness+(thickness), 0.0 , lc};



Line(1) = {1, 2};
Line(2) = {2, 3};
Line(3) = {3, 4};
Line(4) = {4, 5};
Line(5) = {5, 6};
Line(6) = {6, 7};
Line(7) = {7, 1};

Curve Loop(1) = {7, 1, 2, 3, 4, 5, 6};
Plane Surface(1) = {1};

Point{4} In Surface {1};

Physical Surface("volume",3) = {1};
Physical Curve("bot",1) = {1};
Physical Curve("other",2) = {2, 3, 4, 5, 6, 7};
