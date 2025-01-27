/*****************************************************************************

         This file is a part of PSD for building mesh

     -------------------------------------------------------------------

     Author(s): Mohd Afeef Badri
     Email    : mohd-afeef.badri@cea.fr
     Date     : 17-01-2025

     -------------------------------------------------------------------

     This file is distributed  in  the hope that it will be useful,
     but WITHOUT ANY WARRANTY; or without even the implied warranty
     of  FITNESS  FOR  A  PARTICULAR  PURPOSE.

     --------------------------------------------------------------------

     This is a Gmsh .geo file which produces a 3D sphere with box cut

     compile-run: gmsh -3  -format msh2 cube.geo

*******************************************************************************/


ls=1/5.;
lengthCube=1.0;

Point(1) = {lengthCube, 0, 0, ls};
Point(2) = {0, 0, 0, ls};
Point(3) = {0, 1, 0, ls};
Point(4) = {0, 0, 1, ls};
Point(5) = {0, 1, 1, ls};
Point(6) = {lengthCube, 1, 1, ls};
Point(7) = {lengthCube, 0, 1, ls};
Point(8) = {lengthCube, 1, 0, ls};

Line(1) = {5, 3};
Line(2) = {3, 8};
Line(3) = {8, 6};
Line(4) = {6, 5};
Line(5) = {5, 4};
Line(6) = {4, 2};
Line(7) = {2, 3};
Line(8) = {2, 1};
Line(9) = {1, 8};
Line(10) = {6, 7};
Line(11) = {1, 7};
Line(12) = {7, 4};
Line Loop(13) = {1, 2, 3, 4};
Plane Surface(14) = {13};
Line Loop(15) = {2, -9, -8, 7};
Plane Surface(16) = {15};
Line Loop(17) = {1, -7, -6, -5};
Plane Surface(18) = {17};
Line Loop(19) = {8, 11, 12, 6};
Plane Surface(20) = {19};
Line Loop(21) = {10, -11, 9, 3};
Plane Surface(22) = {21};
Line Loop(23) = {4, 5, -12, -10};
Plane Surface(24) = {23};
Surface Loop(25) = {18, 14, 16, 22, 24, 20};
Volume(26) = {25};


//-------------------------------------------
// Physical surfaces
//-------------------------------------------
Physical Surface("left-sur") = {18};
Physical Surface("right-sur") = {22};
Physical Surface("top-sur") = {14};
Physical Surface("bot-sur") = {20};
Physical Surface("front-sur") = {16};
Physical Surface("back-sur") = {24};

//-------------------------------------------
// Physical volume
//-------------------------------------------
Physical Volume("vol") = {26};
