/*****************************************************************************
                                                                              
         This file is a part of PSD (Parallel Structural Dynamics)            
                                                                              
     -------------------------------------------------------------------      
                                                                              
     Author(s): Mohd Afeef Badri                                              
     Email    : mohd-afeef.badri@cea.fr                                       
     Date     : 2019‑05‑29                                                    
                                                                              
     -------------------------------------------------------------------      
                                                                              
     PSD a parallel  finite  element framework  provides tools to  solve      
     multiple  solid-dynamic  problems; PSD is distributed  in  the hope      
     that it will be useful, but WITHOUT ANY WARRANTY; or  without  even      
     the implied warranty of  FITNESS  FOR  A  PARTICULAR  PURPOSE. 
     
     --------------------------------------------------------------------
     
     This is a Gmsh .geo file which produces a 2D soildynamics mesh which
     includes four points for applying the point source.
     
     compile-run: gmsh -2 -format msh2  soil-dc.geo         
                                                                              
*******************************************************************************/

//==============================================================================
// ---- Soil box parameters ----
//==============================================================================

lcBox              = 10   ;         // Mesh size parameter
lengthSoil         = 5000.0  ;     // Length of soil box
HeightSoil         = 2000.0  ;     // Width of soil box
BoxBottomLeftXCord = 0.0   ;       // Bottom left x coordinate
BoxBottomLeftYCord = 0.0   ;       // Bottom left y coordinate

//==============================================================================
// ---- Double couple parameters ----
//==============================================================================

lcDC         = 10       ;     // Force arm length for double couple
DCSouthXCord = 100.0   ;    // South coordinate X 
DCSouthYCord = 100.0   ;    // South coordinate Y     

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
// ---- Building points ----
//==============================================================================

lcBD        = 10       ;     // Force arm length for double couple

buildingbaseleft  = 2750.;
buildingbaseright = 3250.;

Point(newp) = {buildingbaseleft , BoxBottomLeftYCord + HeightSoil , 0.0 , lcBD};  
Point(newp) = {buildingbaseright , BoxBottomLeftYCord + HeightSoil , 0.0 , lcBD};

buildingbaseheight = 20.;

Point(newp) = {buildingbaseleft , BoxBottomLeftYCord + HeightSoil+buildingbaseheight , 0.0 , lcBD};  
Point(newp) = {buildingbaseright , BoxBottomLeftYCord + HeightSoil+buildingbaseheight , 0.0 , lcBD};

buildingbotleft=2950.;
buildingbotright=3050.;


Point(newp) = {buildingbotleft , BoxBottomLeftYCord + HeightSoil+buildingbaseheight , 0.0 , lcBD};  
Point(newp) = {buildingbotright , BoxBottomLeftYCord + HeightSoil+buildingbaseheight , 0.0 , lcBD};

buildingwallthickness = 15.;

Point(newp) = {buildingbotleft + buildingwallthickness, BoxBottomLeftYCord + HeightSoil+buildingbaseheight , 0.0 , lcBD};  
Point(newp) = {buildingbotright - buildingwallthickness, BoxBottomLeftYCord + HeightSoil+buildingbaseheight , 0.0 , lcBD}; 

buildingheight= 50.;

Point(newp) = {buildingbotleft , BoxBottomLeftYCord + HeightSoil+buildingbaseheight + buildingheight, 0.0 , lcBD};  
Point(newp) = {buildingbotright , BoxBottomLeftYCord + HeightSoil+buildingbaseheight + buildingheight, 0.0 , lcBD};
Point(newp) = {buildingbotleft + buildingwallthickness, BoxBottomLeftYCord + HeightSoil+buildingbaseheight +buildingheight , 0.0 , lcBD};  
Point(newp) = {buildingbotright - buildingwallthickness, BoxBottomLeftYCord + HeightSoil+buildingbaseheight +buildingheight , 0.0 , lcBD}; 


Point(newp) = {buildingbotleft + (buildingbotright-buildingbotleft)/2, BoxBottomLeftYCord + HeightSoil+buildingbaseheight + buildingheight, 0.0 , lcBD};
Point(newp) = {buildingbotleft + (buildingbotright-buildingbotleft)/2, BoxBottomLeftYCord + HeightSoil+buildingbaseheight + buildingheight + (buildingbotright-buildingbotleft)/2, 0.0 , lcBD};
Point(newp) = {buildingbotleft + (buildingbotright-buildingbotleft)/2, BoxBottomLeftYCord + HeightSoil+buildingbaseheight + buildingheight + ((buildingbotright-buildingwallthickness)-(buildingbotleft+buildingwallthickness))/2, 0.0 , lcBD};


//==============================================================================
// ---- Build building ----
//==============================================================================
Line(1) = {10, 12};
//+
Line(2) = {12, 14};
//+
Line(3) = {14, 18};
//+
Circle(4) = {18, 21, 22};
//+
Circle(5) = {22, 21, 17};
//+
Line(6) = {17, 13};
//+
Line(7) = {13, 11};
//+
Line(8) = {11, 9};
//+
Line(9) = {9, 10};
//+
Line(10) = {15, 16};
//+
Line(11) = {16, 20};
//+
Circle(12) = {20, 21, 23};
//+
Circle(13) = {23, 21, 19};
//+
Line(14) = {19, 15};

//==============================================================================
// ---- Build box Lines ----
//==============================================================================


//+
Line(15) = {1, 2};
//+
Line(16) = {2, 3};
//+
Line(17) = {3, 10};
//+
Line(18) = {9, 4};
//+
Line(19) = {4, 1};


//==============================================================================
// ---- Double-couple Lines ----
//==============================================================================

//+
Line(20) = {7, 6};
//+
Line(21) = {5, 8};



//==============================================================================
// ---- Build box Surface ----
//==============================================================================

//+
Curve Loop(1) = {15, 16, 17, -9, 18, 19};
//+
Plane Surface(1) = {1};

//==============================================================================
// ---- Enforce double couple points and line in box surface ----
//==============================================================================

Point{5} In Surface {1};
Point{6} In Surface {1};
Point{7} In Surface {1};
Point{8} In Surface {1};
Line{20} In Surface {1};
Line{21} In Surface {1};


//==============================================================================
// ---- Building Surface ----
//==============================================================================
//+
Curve Loop(2) = {6, 7, 8, 9, 1, 2, 3, 4, 5};
//+
Curve Loop(3) = {10, 11, 12, 13, 14};
//+
Plane Surface(2) = {2, 3};


//==============================================================================
// ---- Physical surface/line tagging ----
//==============================================================================

Physical Curve("soil-bot") = {15};
//+
Physical Curve("soil-left") = {19};
//+
Physical Curve("soil-right") = {16};
//+
Physical Curve("soil-top") = {18, 17};
//+
Physical Curve("soil-building-interface") = {9};
//+
Physical Curve("building-base-left") = {8};
//+
Physical Curve("building-base-right") = {1};
//+
Physical Curve("building-base-top") = {7, 2};
//+
Physical Curve("building-walls") = {6, 14, 10, 11, 3, 4, 12, 13, 5};
//+
Physical Curve("fault-NW") = {20};
//+
Physical Curve("fault-SE") = {21};
//+
Physical Surface("soil") = {1};
//+
Physical Surface("building") = {2};
