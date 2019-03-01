# Solvers with: ff++ solvers #

Solid mechanics solver modules developed within DSL language FreeFem++ (ff++). For more information on the FreeFem++ (ff++) please see [ff++](https://www.freefem.org). 


## Command line arguments ##

The sequential solvers can be run on linux/windows platforms and can be used with command line options  to control the solver.

### How to run the solver ? ###

```
FreeFem++ main.edp -v 0 -nw [Options]
```

Options:
```
-nx [int]				Controls the mesh size (total border nodes in x).
```
```
-ny [int]				Controls the mesh size (total border nodes in y).
```
```
-r [real]				Controls the radius of circle.
```
```
-ex [real]				Convert square mesh to a rectangular one via elongation in x.
```
```
-ey [real]				Convert square mesh to a rectangular one via elongation in y.
```
```
-s [int]				Splitting a triangle within the mesh in four.
```
