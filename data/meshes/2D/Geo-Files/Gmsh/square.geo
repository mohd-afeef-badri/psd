//-------- GMSH geo file to create a 2D square mesh -------//
//
//
// NOTE: Use the -format msh2 format to genrate the mesh

Point(1) = {0.0 , 0.0 , 0.0 , 1.0};
Point(2) = {1.0 , 0.0 , 0.0 , 1.0};
Point(3) = {1.0 , 1.0 , 0.0 , 1.0};
Point(4) = {0.0 , 1.0 , 0.0 , 1.0};

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
