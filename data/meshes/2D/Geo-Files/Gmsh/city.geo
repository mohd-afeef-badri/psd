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

lc = .5;
lengthCity=50.0;
SoilDepth=-15.0;

buildingbase0=1.;
buildingbase1=2.;
buildingbase2=3.;

//--------- Bounding box ----------------------//
Point(1) = {0.0 , 0.0 , 0.0 , lc};
Point(2) = {lengthCity , 0.0 , 0.0 , lc};
Point(3) = {lengthCity , SoilDepth , 0.0 , lc};
Point(4) = {0.0 , SoilDepth , 0.0 , lc};

//--------- City -----------------------------//

Point(newp) = {10.0 , 0.0 , 0.0 , lc};
Point(newp) = {10.0 + buildingbase0, 0.0 , 0.0 , lc};
Point(newp) = {10.0 , 2.0 , 0.0 , lc};
Point(newp) = {10.0 + buildingbase0, 2.0 , 0.0 , lc};

Point(newp) = {12.0 , 0.0 , 0.0 , lc};
Point(newp) = {12.0 + buildingbase1, 0.0 , 0.0 , lc};
Point(newp) = {12.0 , 4.0 , 0.0 , lc};
Point(newp) = {12.0 + buildingbase1, 4.0 , 0.0 , lc};

//Point(newp) = {14.0 , 0.0 , 0.0 , lc};
//Point(newp) = {14.0 + buildingbase0, 0.0 , 0.0 , lc};

Point(newp) = {16.0 , 0.0 , 0.0 , lc};
Point(newp) = {16.0 + buildingbase2, 0.0 , 0.0 , lc};
Point(newp) = {16.0 , 8.0 , 0.0 , lc};
Point(newp) = {16.0 + buildingbase2, 8.0 , 0.0 , lc};
Point(newp) = {17.5 , 9.5 , 0.0 , lc};

Point(newp) = {19.5 , 0.0 , 0.0 , lc};
Point(newp) = {19.0 + buildingbase1, 0.0 , 0.0 , lc};
Point(newp) = {19.5 , 1.0 , 0.0 , lc};
Point(newp) = {19.0 + buildingbase1, 1.0 , 0.0 , lc};

Point(newp) = {21.5 , 0.0 , 0.0 , lc};
Point(newp) = {21.5 + buildingbase0, 0.0 , 0.0 , lc};
Point(newp) = {21.5 , 1.0 , 0.0 , lc};
Point(newp) = {21.5 + buildingbase0, 1.0 , 0.0 , lc};

Point(newp) = {24.0 , 0.0 , 0.0 , lc};
Point(newp) = {24.0 + buildingbase2, 0.0 , 0.0 , lc};
Point(newp) = {24.0 , 6.0 , 0.0 , lc};
Point(newp) = {24.0 + buildingbase2, 6.0 , 0.0 , lc};

Point(newp) = {27.5 , 0.0 , 0.0 , lc};
Point(newp) = {27.5 + buildingbase1, 0.0 , 0.0 , lc};
Point(newp) = {27.5 , 5.0 , 0.0 , lc};
Point(newp) = {27.5 + buildingbase1, 5.0 , 0.0 , lc};
Point(newp) = {28.5, 7.0 , 0.0 , lc};

Point(newp) = {32.0 , 0.0 , 0.0 , lc};
Point(newp) = {32.0 + buildingbase0, 0.0 , 0.0 , lc};
Point(newp) = {32.0 , 3.0 , 0.0 , lc};
Point(newp) = {32.0 + buildingbase0, 3.0 , 0.0 , lc};

Point(newp) = {34.0 , 0.0 , 0.0 , lc};
Point(newp) = {34.0 + buildingbase0, 0.0 , 0.0 , lc};
Point(newp) = {34.0 , 2.0 , 0.0 , lc};
Point(newp) = {34.0 + buildingbase0,2.0 , 0.0 , lc};

Point(newp) = {37.0 , 0.0 , 0.0 , lc};
Point(newp) = {37.0 + buildingbase1, 0.0 , 0.0 , lc};
Point(newp) = {37.0 , 3.0 , 0.0 , lc};
Point(newp) = {37.0 + buildingbase1, 3.0 , 0.0 , lc};
Point(newp) = {38.0 , 4.0 , 0.0 , lc};

Point(newp) = {39.5 , 0.0 , 0.0 , lc};
Point(newp) = {39.5 + buildingbase0, 0.0 , 0.0 , lc};
Point(newp) = {39.5 , 1.0 , 0.0 , lc};
Point(newp) = {39.5 + buildingbase0, 1.0 , 0.0 , lc};

/*
Line(1) = {1 , 2};
Line(2) = {2 , 3};
Line(3) = {3 , 4};
Line(4) = {4 , 1};
//+
Curve Loop(1) = {4, 1, 2, 3};
//+
Plane Surface(1) = {1};
//+
Physical Surface("volume") = {1};
//+
Physical Curve("surface-left") = {4};
//+
Physical Curve("surface-top") = {3};
//+
Physical Curve("surface-right") = {2};
//+
Physical Curve("surface-bottom") = {1};
*/


//+------- Soil-lines +---------------//
Line(1) = {4, 3};
//+
Line(2) = {3, 2};
//+
Line(3) = {2, 49};
//+
Line(4) = {4, 1};
//+
Line(5) = {1, 5};
//+
Line(6) = {6, 9};
//+
Line(7) = {10, 13};
//+
Line(8) = {14, 18};
//+
Line(9) = {19, 22};
//+
Line(10) = {23, 26};
//+
Line(11) = {27, 30};
//+
Line(12) = {31, 35};
//+
Line(13) = {36, 39};
//+
Line(14) = {40, 43};
//+
Line(15) = {44, 48};






//+---------------- Building lines -------------//
Line(16) = {5, 7};
//+
Line(17) = {8, 7};
//+
Line(18) = {8, 6};
//+
Line(19) = {6, 5};
//+
Line(20) = {9, 11};
//+
Line(21) = {11, 12};
//+
Line(22) = {12, 10};
//+
Line(23) = {10, 9};
//+
Line(24) = {13, 15};
//+
Line(25) = {15, 17};
//+
Line(26) = {17, 16};
//+
Line(27) = {16, 14};
//+
Line(28) = {14, 13};
//+
Line(29) = {18, 20};
//+
Line(30) = {20, 21};
//+
Line(31) = {21, 19};
//+
Line(32) = {19, 18};
//+
Line(33) = {22, 24};
//+
Line(34) = {25, 24};
//+
Line(35) = {25, 23};
//+
Line(36) = {23, 22};
//+
Line(37) = {26, 28};
//+
Line(38) = {28, 29};
//+
Line(39) = {29, 27};
//+
Line(40) = {30, 32};
//+
Line(41) = {32, 34};
//+
Line(42) = {34, 33};
//+
Line(43) = {33, 31};
//+
Line(44) = {31, 30};
//+
Line(45) = {35, 37};
//+
Line(46) = {37, 38};
//+
Line(47) = {38, 36};
//+
Line(48) = {36, 35};
//+
Line(49) = {39, 41};
//+
Line(50) = {41, 42};
//+
Line(51) = {42, 40};
//+
Line(52) = {40, 39};
//+
Line(53) = {43, 45};
//+
Line(54) = {45, 47};
//+
Line(55) = {47, 46};
//+
Line(56) = {46, 44};
//+
Line(57) = {44, 43};
//+
Line(58) = {48, 50};
//+
Line(59) = {50, 51};
//+
Line(60) = {51, 49};
//+
Line(61) = {49, 48};
//+
Line(62) = {27, 26};



//+----------------Soil volume ------------------------//
Curve Loop(1) = {5, -19, 6, -23, 7, -28, 8, -32, 9, -36, 10, -62, 11, -44, 12, -48, 13, -52, 14, -57, 15, -61, -3, -2, -1, 4};
//+
Plane Surface(1) = {1};
//+
Physical Surface("soil-volume") = {1};


//+---------------------- City Volume -------------+//
Curve Loop(2) = {16, -17, 18, 19};
//+
Plane Surface(2) = {2};
//+
Curve Loop(3) = {20, 21, 22, 23};
//+
Plane Surface(3) = {3};
//+
Curve Loop(4) = {24, 25, 26, 27, 28};
//+
Plane Surface(4) = {4};
//+
Curve Loop(5) = {29, 30, 31, 32};
//+
Plane Surface(5) = {5};
//+
Curve Loop(6) = {33, -34, 35, 36};
//+
Plane Surface(6) = {6};
//+
Curve Loop(7) = {37, 38, 39, 62};
//+
Plane Surface(7) = {7};
//+
Curve Loop(8) = {40, 41, 42, 43, 44};
//+
Plane Surface(8) = {8};
//+
Curve Loop(9) = {45, 46, 47, 48};
//+
Plane Surface(9) = {9};
//+
Curve Loop(10) = {49, 50, 51, 52};
//+
Plane Surface(10) = {10};
//+
Curve Loop(11) = {53, 54, 55, 56, 57};
//+
Plane Surface(11) = {11};
//+
Curve Loop(12) = {58, 59, 60, 61};
//+
Plane Surface(12) = {12};
//+
Physical Surface("city-volume") = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};





//+------------------ Paraxial tags -----------------+//
Physical Curve("paraxial-bot") = {1};
//+
Physical Curve("paraxial-left") = {4};
//+
Physical Curve("paraxial-right") = {2};


//+------------------ soil top tags -----------------+//
Physical Curve("soil-surface") = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 3};




//+------------------ building surface tags -----------------+//
Physical Curve("building-surface") = {16, 17, 18, 20, 21, 22, 24, 25, 26, 27, 29, 30, 31, 33, 34, 35, 37, 38, 39, 40, 41, 42, 43, 45, 46, 47, 49, 50, 51, 53, 54, 55, 56, 58, 59, 60};
