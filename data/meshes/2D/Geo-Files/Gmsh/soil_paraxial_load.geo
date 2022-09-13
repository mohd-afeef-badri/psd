//-------- GMSH geo file to create a 2D bar mesh -------//
//
//
// NOTE: Use the -format msh2 format to genrate the mesh

lc = 1.;
lengthBar=50.0;
HeightBar=50.0;

BotBcLeftPnt = 20.0;
BotBcRigtPnt = 30.0;

Point(1) = {0.0 , 0.0 , 0.0 , lc};
Point(2) = {lengthBar , 0.0 , 0.0 , lc};
Point(3) = {lengthBar , HeightBar , 0.0 , lc};
Point(4) = {0.0 , HeightBar , 0.0 , lc};
Point(5) = {BotBcLeftPnt , 0.0 , 0.0 , lc};
Point(6) = {BotBcRigtPnt , 0.0 , 0.0 , lc};

Line(1) = {1 , 5};
Line(2) = {5 , 6};
Line(3) = {6 , 2};
Line(4) = {2 , 3};
Line(5) = {3 , 4};
Line(6) = {4 , 1};

Curve Loop(1) = {6, 1, 2, 3, 4, 5};


Plane Surface(1) = {1};


Physical Surface("volume",1) = {1};


Physical Curve("surface-left",2) = {6};
Physical Curve("surface-top",3) = {5};
Physical Curve("surface-right",4) = {4};
Physical Curve("surface-bottom-bc",5) = {2};
Physical Curve("surface-bottom",6) = {1,3};

