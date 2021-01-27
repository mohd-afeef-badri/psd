//-------- GMSH geo file to create a 20x8 mm^2 with crack -------//
//
//
// NOTE: Use the -format msh2 format to genrate the mesh

lc = 1.;
lc4PBC = lc/8.;       // length for point boundary conditions
lc4CrackTip = lc/10.;  // length for crack tip
lc4Holes = lc/4.;  // length for crack tip

dia=1.;

heightBody = 8.0;
lenBody=20.;
lenCrack=4.0;
heightCrack=1.0;
lenLeftBc=1.0;
lenRightBc=19.0;
lenTopBc=10.0;
LengthHCenter=6.0;      // Hole Length from left
HeightH1Center=2.75;     // Hole 1 height bottom
HeightH2Center=4.75;     // Hole 2 height bottom
HeightH3Center=6.75;     // Hole 3 height bottom
eps=1e-2;
rad= dia/2.;


//Corner points //
Point(1) = {0.0 , 0.0 , 0.0 , lc};
Point(2) = {lenBody , 0.0 , 0.0 , lc};
Point(3) = {lenBody , heightBody , 0.0 , lc};
Point(4) = {0.0 , heightBody , 0.0 , lc};

// Boundy Cond Points //
Point(5) = {lenLeftBc , 0.0 , 0.0 , lc4PBC};
Point(6) = {lenRightBc , 0.0 , 0.0 , lc4PBC};
Point(7) = {lenTopBc , heightBody , 0.0 , lc4PBC};

// Crack Points //
Point(8) = {lenCrack-eps , 0.0 , 0.0 , lc};
Point(9) = {lenCrack+eps , 0.0 , 0.0 , lc};
Point(10) = {lenCrack , heightCrack , 0.0 , lc4CrackTip};


// Holes  Points (for circle) //
Point(11) = {LengthHCenter , HeightH1Center-rad , 0.0 , lc4Holes}; //Hole 1
Point(12) = {LengthHCenter , HeightH1Center , 0.0 , lc4Holes};     //Hole 1
Point(13) = {LengthHCenter , HeightH1Center+rad , 0.0 , lc4Holes}; //Hole 1

Point(14) = {LengthHCenter , HeightH2Center-rad , 0.0 , lc4Holes}; //Hole 2
Point(15) = {LengthHCenter , HeightH2Center , 0.0 , lc4Holes};     //Hole 2
Point(16) = {LengthHCenter , HeightH2Center+rad , 0.0 , lc4Holes}; //Hole 2

Point(17) = {LengthHCenter , HeightH3Center-rad , 0.0 , lc4Holes}; //Hole 2
Point(18) = {LengthHCenter , HeightH3Center , 0.0 , lc4Holes};     //Hole 2
Point(19) = {LengthHCenter , HeightH3Center+rad , 0.0 , lc4Holes}; //Hole 2

// Lines material boundary //
Line(1) = {1, 5};
Line(2) = {5, 8};
Line(3) = {8, 10};      // Crack
Line(4) = {10, 9};      // Crack
Line(5) = {9, 6};
Line(6) = {6, 2};
Line(7) = {2, 3};
Line(8) = {3, 7};
Line(9) = {7, 4};
Line(10) = {4, 1};

// holes boundary //
Circle(11) = {11, 12, 13}; //Hole 1
Circle(12) = {13, 12, 11}; //Hole 1

Circle(13) = {14, 15, 16}; //Hole 2
Circle(14) = {16, 15, 14}; //Hole 2

Circle(15) = {17, 18, 19}; //Hole 3
Circle(16) = {19, 18, 17}; //Hole 3

// Material surface //
Curve Loop(1) = {10, 1, 2, 3, 4, 5, 6, 7, 8, 9};
Curve Loop(2) = {12, 11};
Curve Loop(3) = {14, 13};
Curve Loop(4) = {16, 15};
Plane Surface(1) = {1, 2, 3, 4};

// Physical surfaces
//+
Physical Surface("material") = {1};
Physical Curve("crack") = {3,4};
Physical Curve("other-sur") = {10, 1, 2, 5, 6, 7, 8, 9};
Physical Curve("hole-sur") = {16, 15, 14, 13, 12, 11};
