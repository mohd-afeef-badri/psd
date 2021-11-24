/**************************************************************************************
*                                                                                     *
* Author:  Mohd Afeef BADRI                                                           *
* Date:    22/11/2021                                                                 *
* Type:    Gmsh geometry file                                                         *
*                                                                                     *
* Compile: gmsh quater_cylinder.geo -format msh2                                      *
*                                                                                     *
* Comment: The intended geometry is a quater of a cylinder in 2D it reduces tp quater *
*          of a circular shell. The internal and external radius of the shell is  Ri  *
*          and Re. We use `-format msh2` as a Gmsh argument to output .msh file   in  *
*          in version 2 format.                                                       *
*                                                                                     *
**************************************************************************************/

Ri = 1.;
Re = 1.3;
d = 0.03;

Point(0) = {0, 0, 0, d};
Point(1) = {Ri, 0, 0, d};
Point(2) = {Re, 0, 0, d};
Point(3) = {0, Re, 0, d};
Point(4) = {0, Ri, 0, d};
Line(1) = {1, 2};

Circle(2) = {2, 0, 3};
Line(3) = {3, 4};
Circle(4) = {4, 0, 1};
Line Loop(5) = {4, 1, 2, 3};
Plane Surface(6) = {5};

Physical Line(1) = {1};
Physical Line(2) = {2};
Physical Line(3) = {3};
Physical Line(4) = {4};
Physical Surface(1) = {6};
