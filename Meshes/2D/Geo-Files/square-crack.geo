//-------- GMSH geo file to create a 1x1 square with crack -------//
//
//
// NOTE: Use the -format msh2 format to genrate the mesh

lc = 1.0/31.0;
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
