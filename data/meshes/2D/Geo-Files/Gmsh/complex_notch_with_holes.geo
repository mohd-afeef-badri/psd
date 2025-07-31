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

lc = 1.;
lc4PBC = lc/8.;       // length for point boundary conditions
lc4CrackTip = lc/10.;  // length for crack tip
lc4Holes = lc/1.;  // length for crack tip



// Body parameters //
heightBody = 80.0;
lenBody=62.5;

// Holes for BC parameters // 
radBChole=6.;
xCenterBChole=12.5;
yCenterBotBChole=15.;
yCenterTopBChole=65.;

// Holes in material  parameters //
radH1hole=3.; 
radH2hole=1.75; 
radH3hole=1.75;
xCenterholeH1=35.5;
yCenterholeH1=48.0; 
xCenterholeH2=40.5;
yCenterholeH2=42.0;
xCenterholeH3=38.5;
yCenterholeH3=35.0; 

// Notch parameter ptonts strat from top//
p1x=0.0;
p1y=48.0;
p2x=12.5;
p2y=48.0;
p3x=12.5;
p3y=43.25;
p4x=18.5;
p4y=48.0;
p5x=18.5;
p5y=43.25;
p6x=32.75;
p6y=43.25;
p7x=36;
p7y=40.;
p8x=32.75;   // center
p8y=40.;     //center
p9x=p6x;
p9y=p6y-6.5;
p10x=p5x;
p10y=p5y-6.5;
p11x=p4x;
p11y=32.;
p12x=p3x;
p12y=p5y-6.5;
p13x=p2x;
p13y=32.;
p14x=p1x;
p14y=32.;






//Corner points //
Point(newp) = {0.0 , 0.0 , 0.0 , lc};
Point(newp) = {lenBody , 0.0 , 0.0 , lc};
Point(newp) = {lenBody , heightBody , 0.0 , lc};
Point(newp) = {0.0 , heightBody , 0.0 , lc};

// Holes for BC // 
Point(newp) = {xCenterBChole , yCenterBotBChole-radBChole , 0.0 , lc4Holes}; //Hole Bot
Point(newp) = {xCenterBChole , yCenterBotBChole , 0.0 , lc4Holes};     //Hole Bot
Point(newp) = {xCenterBChole , yCenterBotBChole+radBChole , 0.0 , lc4Holes}; //Hole Bot

Point(newp) = {xCenterBChole , yCenterTopBChole-radBChole , 0.0 , lc4Holes}; //Hole Top
Point(newp) = {xCenterBChole , yCenterTopBChole , 0.0 , lc4Holes};     //Hole Top
Point(newp) = {xCenterBChole , yCenterTopBChole+radBChole , 0.0 , lc4Holes}; //Hole Top

// Holes in material //
Point(newp) = {xCenterholeH1 , yCenterholeH1-radH1hole , 0.0 , lc4Holes}; //Hole H1
Point(newp) = {xCenterholeH1 , yCenterholeH1 , 0.0 , lc4Holes};     //Hole H1
Point(newp) = {xCenterholeH1 , yCenterholeH1+radH1hole , 0.0 , lc4Holes}; //Hole H1

Point(newp) = {xCenterholeH2 , yCenterholeH2-radH2hole , 0.0 , lc4Holes}; //Hole H2
Point(newp) = {xCenterholeH2 , yCenterholeH2 , 0.0 , lc4Holes};     //Hole H2
Point(newp) = {xCenterholeH2 , yCenterholeH2+radH2hole , 0.0 , lc4Holes}; //Hole H2

Point(newp) = {xCenterholeH3 , yCenterholeH3-radH2hole , 0.0 , lc4Holes}; //Hole H3
Point(newp) = {xCenterholeH3 , yCenterholeH3 , 0.0 , lc4Holes};     //Hole H3
Point(newp) = {xCenterholeH3 , yCenterholeH3+radH2hole , 0.0 , lc4Holes}; //Hole H3

// Notch points from the top//

Point(newp) = {p1x , p1y , 0.0 , lc4Holes};
Point(newp) = {p2x , p2y , 0.0 , lc4Holes}; 
Point(newp) = {p3x , p3y , 0.0 , lc4Holes}; 
Point(newp) = {p4x , p4y , 0.0 , lc4Holes}; 
Point(newp) = {p5x , p5y , 0.0 , lc4Holes};
Point(newp) = {p6x , p6y , 0.0 , lc4Holes};
Point(newp) = {p7x , p7y , 0.0 , lc4Holes};
Point(newp) = {p8x , p8y , 0.0 , lc4Holes};
Point(newp) = {p9x , p9y , 0.0 , lc4Holes};
Point(newp) = {p10x , p10y , 0.0 , lc4Holes};
Point(newp) = {p11x , p11y , 0.0 , lc4Holes};
Point(newp) = {p12x , p12y , 0.0 , lc4Holes};
Point(newp) = {p13x , p13y , 0.0 , lc4Holes};
Point(newp) = {p14x , p14y , 0.0 , lc4Holes};
 

// Material border //
Line(1) = {1, 2};
//+
Line(2) = {2, 3};
//+
Line(3) = {3, 4};
//+
Line(4) = {4, 20};
//+
Line(5) = {20, 21};
//+
Line(6) = {21, 22};
//+
Line(7) = {22, 23};
//+
Line(8) = {23, 24};
//+
Line(9) = {24, 25};
//+
Line(10) = {28, 29};
//+
Line(11) = {29, 30};
//+
Line(12) = {30, 31};
//+
Line(13) = {31, 32};
//+
Line(14) = {32, 33};
//+
Line(15) = {33, 1};
//+
Circle(16) = {28, 27, 26};
//+
Circle(17) = {26, 27, 25};
//+


// Holes for BC //
Circle(18) = {5, 6, 7};
//+
Circle(19) = {7, 6, 5};
//+
Circle(20) = {8, 9, 10};
//+
Circle(21) = {10, 9, 8};
//+

// Holes in mesh 
Circle(22) = {17, 18, 19};
//+
Circle(23) = {19, 18, 17};
//+
Circle(24) = {14, 15, 16};
//+
Circle(25) = {16, 15, 14};
//+
Circle(26) = {11, 12, 13};
//+
Circle(27) = {13, 12, 11};




// MAterial plane 
Curve Loop(1) = {4, 5, 6, 7, 8, 9, -17, -16, 10, 11, 12, 13, 14, 15, 1, 2, 3};
//+
Curve Loop(2) = {20, 21};
//+
Curve Loop(3) = {18, 19};
//+
Curve Loop(4) = {22, 23};
//+
Curve Loop(5) = {24, 25};
//+
Curve Loop(6) = {26, 27};
//+
Plane Surface(1) = {1, 2, 3, 4, 5, 6};




//+
Physical Surface("vol") = {1};
//+
Physical Curve("top-bc") = {20, 21};
//+
Physical Curve("bot-bc") = {18, 19};
//+
Physical Curve("holes") = {27, 26, 25, 24, 23, 22};
//+
Physical Curve("mat-border") = {4, 5, 6, 7, 8, 9, 17, 16, 10, 11, 12, 13, 14, 15, 1, 2, 3};
