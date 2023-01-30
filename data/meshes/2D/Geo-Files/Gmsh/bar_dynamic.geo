//--2d dynamic bar--//

lc = 1.0/91.0;
lengthBar=1.0;
heightBar=0.1;

Point(1) = {0.0 , 0.0 , 0.0 , lc};
Point(2) = {lengthBar , 0.0 , 0.0 , lc};
Point(3) = {lengthBar , heightBar , 0.0 , lc};
Point(4) = {0.0 , heightBar , 0.0 , lc};

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
