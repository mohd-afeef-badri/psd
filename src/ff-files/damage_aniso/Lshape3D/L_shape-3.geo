//-------- GMSH geo file to create a L mesh in 3D -------//

ls=50.;
baselength=250.0;
basewidth=100.0;
baseheight=500.0;
toplength=500.0;
Lheight=250.0;
Lwidth=250.0;
decalage = 0.;
refine = 10.;
deltacrack=70.;

Point(newp) = {0, 0, 0, ls};
Point(newp) = {baselength, 0, 0, ls};
Point(newp) = {0, basewidth, 0, ls};
Point(newp) = {baselength, basewidth, 0, ls};
Point(newp) = {0, 0, baseheight, ls};
Point(newp) = {0, basewidth, baseheight, ls};
Point(newp) = {toplength, 0, baseheight, ls};
Point(newp) = {toplength, basewidth, baseheight, ls};
Point(newp) = {toplength, 0, Lheight, ls};
Point(newp) = {toplength, basewidth, Lheight, ls};
Point(newp) = {Lwidth, 0, Lheight, ls/refine};
Point(newp) = {Lwidth, basewidth, Lheight, ls/refine};
Point(newp) = {Lwidth+(Lwidth-30.), 0, Lheight, ls};
Point(newp) = {Lwidth+(Lwidth-30.), basewidth, Lheight, ls};

//refine points
Point(newp) = {Lwidth-decalage, basewidth-decalage, Lheight-(deltacrack/3.), ls/(refine)};
Point(newp) = {Lwidth-decalage, 0+decalage, Lheight-(deltacrack/3.), ls/(refine)};

Point(newp) = {0+decalage, 0+decalage, Lheight-(deltacrack/3.), ls/(refine)};
Point(newp) = {0+decalage, basewidth-decalage, Lheight-(deltacrack/3.), ls/(refine)};
Point(newp) = {0+decalage, 0+decalage, Lheight+deltacrack, ls/(refine)};
Point(newp) = {0+decalage, basewidth-decalage, Lheight+deltacrack, ls/(refine)};


Point(newp) = {Lwidth-decalage, 0+decalage, Lheight+deltacrack, ls/(refine)};
Point(newp) = {Lwidth-decalage, basewidth-decalage, Lheight+deltacrack, ls/(refine)};

//+
Line(1) = {1, 3};
//+
Line(2) = {3, 4};
//+
Line(3) = {4, 2};
//+
Line(4) = {2, 1};
//+
Line(5) = {1, 17};
//+
Line(6) = {5, 6};
//+
Line(7) = {6, 20};
//+
Line(8) = {6, 8};
//+
Line(9) = {8, 7};
//+
Line(10) = {7, 5};
//+
Line(11) = {8, 10};
//+
Line(12) = {10, 9};
//+
Line(13) = {9, 7};
//+
Line(14) = {9, 13};
//+
Line(15) = {13, 14};
//+
Line(16) = {14, 10};
//+
Line(17) = {13, 11};
//+
Line(18) = {11, 12};
//+
Line(19) = {12, 14};
//+
Line(20) = {2, 16};
//+
Line(21) = {12, 15};
//+
Line(22) = {15, 4};
//+
Line(23) = {16, 11};
//
Line(24) = {17, 19};
//
Line(25) = {18, 3};
//
Line(26) = {19, 5};
//
Line(27) = {20, 18};
//
// Lines refine in Volume
Line(28) = {22, 21};
//Lines refine in Surface
Line(29) = {16, 17};
//
Line(30) = {19, 21};
//
Line(31) = {11, 21};
//
Line(32) = {17, 18};
//
Line(33) = {19, 20};
//
Line(34) = {20, 22};
//
Line(35) = {22, 12};
//
Line(36) = {15, 18};
//
Curve Loop(1) = {5, 24, 26, -10, -13, 14, 17, -23, -20, 4};
//+
Plane Surface(1) = {1};
//+
Point{21} In Surface {1};
//
Line{29} In Surface {1};
//
Line{30} In Surface {1};
//
Line{31} In Surface {1};
//
Curve Loop(2) = {8, 11, -16, -19, 21, 22, -2, -25, -27, -7};
//+
Plane Surface(2) = {2};
//+
Point{22} In Surface {2};
//
Line{34} In Surface {2};
//
Line{35} In Surface {2};
//
Line{36} In Surface {2};
//
Curve Loop(3) = {8, 9, 10, 6};
//+
Plane Surface(3) = {3};
//+
Curve Loop(4) = {6, 7, 27, 25, -1, 5, 24, 26};
//+
Plane Surface(4) = {4};
//+
Line{32} In Surface {4};
//
Line{33} In Surface {4};
Curve Loop(5) = {2, 3, 4, 1};
//+
Plane Surface(5) = {5};
//+
Curve Loop(6) = {18, 21, 22, 3, 20, 23};
//+
Plane Surface(6) = {6};
//+
Curve Loop(7) = {19, -15, 17, 18};
//+
Plane Surface(7) = {7};
//+
Curve Loop(8) = {12, 14, 15, 16};
//+
Plane Surface(8) = {8};
//+
Curve Loop(9) = {9, -13, -12, -11};
//+
Plane Surface(9) = {9};
//+
Surface Loop(1) = {1, 4, 3, 2, 9, 8, 7, 6, 5};
//+
Volume(1) = {1};
//+
Line{28} In Volume {1};
//
Physical Volume("vol") = {1};
//+
Physical Surface("bot") = {5};
//+
Physical Surface("bc") = {8};
//+
Physical Surface("other") = {1, 7, 9, 3, 2, 6, 4};
