//+
//l  = 0.125; //ref3
//l  = 0.0625; //ref4
L =  500.; // length of the beam
D =  5.; // notch
Depth = 10.; // notch depth
H  = 100.; // height of the beam
L0 = 150.; // length on which the load is applied
Bc = 25.; // Supports
D0 = 20.; // Refine region

// r0 Refine = 2.
// r1 Refine = 5.
// r2 Refine = 10.
// r3 Refine = 15.

Refine = 20.; // 


// ref0 h = 10.
// ref1 h =  5.
// ref2 h =  2.5
// ref3 h =  1.25

h  = 10.  ; 

Point(1) = {-L/2, 0., 0.,h};
Point(2)  = {-L/2+Bc, 0., 0.,h};
Point(3)  = { -D/2., 0., 0.,h/Refine};
Point(4)  = { -D/2, Depth, 0.,h/Refine};
Point(5)  = {D/2, Depth, 0.,h/Refine};
Point(6)  = {D/2, 0, 0.,h/Refine};
Point(7)  = { -Bc+L/2, 0., 0.,h};
Point(8) = { L/2.,   0., 0.,h};

Point(9)  = {   L/2., H, 0.,h };
Point(10)  = {  L0/2., H, 0.,h};
Point(11)  = { -L0/2., H, 0.,h};
Point(12) =  {  -L/2., H, 0.,h};

Point(13)  = { -D0, 0., 0.,h/Refine};
Point(14)  = {D0, 0, 0.,h/Refine};
Point(15)  = {  D0, H, 0.,h/Refine};
Point(16)  = { -D0, H, 0.,h/Refine};

Point(17)  = { -D/2, H, 0.,h/Refine};
Point(18)  = {D/2, H, 0.,h/Refine};


//+
Line(1) = {1, 2};
//+
Line(14) = {2, 13};
//+
Line(2) = {13, 3};
//+
Line(3) = {3, 4};
//+
Line(5) = {4, 5};
//+
Line(6) = {5, 6};
//+
Line(15) = {6, 14};
//+
Line(7) = {14, 7};
//+
Line(8) = {7, 8};
//+
Line(9) = {8, 9};
//+
Line(10) = {9, 10};
//+
Line(16) = {10, 15};
//+
Line(17) = {15, 18};
//+
Line(20) = {18, 17};
//+
Line(21) = {17, 16};
//+
Line(11) = {16, 11};
//+
Line(12) = {11, 12};
//+
Line(13) = {12, 1};
//+
Line(18) = {13, 16};
//+
Line(19) = {14, 15};
//+
Line(22) = {4, 17};
//+
Line(23) = {5, 18};
//+



//Physical Curve(50) = {3, 5, 6, 15, 7, 8, 9, 10, 16, 17, 20, 21, 11, 12, 13, 1, 14, 2};
//Physical Surface(100) = {1};

Curve Loop(1) = {13, 1, 14, 2, 3, 22, 21, 11, 12};
Curve Loop(2) = {-22, 5, 23, 20};
Curve Loop(3) = {15, 7, 8, 9, 10, 16, 17, -23, 6};
//+


Plane Surface(1) = {1};
Plane Surface(2) = {2};
Plane Surface(3) = {3};

//Curve Loop(1) = {13, 1, 14, 18, 11, 12};
//+
//Plane Surface(1) = {1};
//+
//Curve Loop(2) = {-18, 2, 3, 5, 6, 15, 19, 17, 20, 21};
//+
//Plane Surface(2) = {2};
//+
//Curve Loop(3) = {-19, 7, 8, 9, 10, 16};
//+
//Plane Surface(3) = {3};

//Line {18} In Surface {2};
//Line {19} In Surface {2};
//Line {22} In Surface {2};
//Line {23} In Surface {2};
//+

//+
//Physical Curve(1) = {13, 1, 14, 2, 3, 5, 6, 15, 7, 8, 9, 10, 16, 17, 20, 21, 11, 12, 18, 19, 22, 23};
//+
Physical Surface(100) = {1,2,3};
//Physical Surface(100) = {1};
//+

//+
Transfinite Surface {2} = {4, 5, 18, 17} Alternated;
