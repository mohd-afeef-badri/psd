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
* Comment: This is a Gmsh .geo file which produces a 2D soildynamics mesh which       *
*          includes four points for applying the point source.                        *
*          compile-run: gmsh -2 -format msh2  soil-dc.geo                             *
*                                                                                     *
**************************************************************************************/

//==============================================================================
// ---- Soil box parameters ----
//==============================================================================

lcBox              = 0.2   ;       // Mesh size parameter
lengthSoil         = 50.0  ;       // Length of soil box
HeightSoil         = 50.0  ;       // Width of soil box
BoxBottomLeftXCord = 0.0   ;       // Bottom left x coordinate
BoxBottomLeftYCord = 0.0   ;       // Bottom left y coordinate

//==============================================================================
// ---- Double couple parameters ----
//==============================================================================

lcDC         = .1    ;    // Force arm length for double couple
DCSouthXCord = 5.0   ;    // South coordinate X 
DCSouthYCord = 5.0   ;    // South coordinate Y     

//==============================================================================
// ---- Build box points ----
//==============================================================================

Point(1) = {BoxBottomLeftXCord , BoxBottomLeftYCord , 0.0 , lcBox};
Point(2) = {BoxBottomLeftXCord + lengthSoil , BoxBottomLeftYCord , 0.0 , lcBox};
Point(3) = {BoxBottomLeftXCord + lengthSoil , BoxBottomLeftYCord + HeightSoil , 0.0 , lcBox};
Point(4) = {BoxBottomLeftXCord , BoxBottomLeftYCord + HeightSoil , 0.0 , lcBox};

//==============================================================================
// ---- Double-couple points ----
//==============================================================================

Point(5) = {DCSouthXCord , DCSouthYCord , 0.0 , lcDC};                  // South 
Point(6) = {DCSouthXCord , DCSouthYCord + lcDC, 0.0 , lcDC};            // North
Point(7) = {DCSouthXCord - lcDC/2 , DCSouthYCord + lcDC/2, 0.0 , lcDC}; // West
Point(8) = {DCSouthXCord + lcDC/2 , DCSouthYCord + lcDC/2, 0.0 , lcDC}; // East

//==============================================================================
// ---- Build box Lines ----
//==============================================================================

Line(1) = {1 , 2};
Line(2) = {2 , 3};
Line(3) = {3 , 4};
Line(4) = {4 , 1};

//==============================================================================
// ---- Double-couple Lines ----
//==============================================================================

Line(5) = {6, 7};
Line(6) = {8, 5};

//==============================================================================
// ---- Build box Surface ----
//==============================================================================

Curve Loop(1) = {4, 1, 2, 3};
Plane Surface(1) = {1};

//==============================================================================
// ---- Enforce double couple points and line in box surface ----
//==============================================================================

Point{5} In Surface {1};
Point{6} In Surface {1};
Point{7} In Surface {1};
Point{8} In Surface {1};
Line{5} In Surface {1};
Line{6} In Surface {1};

//==============================================================================
// ---- Physical surface/line tagging ----
//==============================================================================

Physical Surface("volume") = {1};
Physical Curve("surface-left") = {4};
Physical Curve("surface-top") = {3};
Physical Curve("surface-right") = {2};
Physical Curve("surface-bottom") = {1};
Physical Curve("fault1") = {5};
Physical Curve("fault2") = {6};
