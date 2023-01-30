//-------- GMSH geo file to create a L-shaped crack specimen -------//
//
//
// NOTE: Use the -format msh2 format to genrate the mesh

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
