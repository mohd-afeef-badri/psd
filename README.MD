# ff++ solid mechanics solver #

Solid mechanics solver modules developed within DSL language FreeFem++. 


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





# Parallel ff++ solid mechanics solver #

## How to run the solver ? ##

The parallel solvers can be run on linux platforms and can be used with command line options  to control the solver.

### Step 1 ? ###

```
ff-mpirun -np 1 scriptGenerator.edp -v 0 -nw [OptionsA]

```

### Step 2 ? ###

```
ff-mpirun -np $NP scriptGenerator.edp -v 0 -nw [OptionsB]

```

## What is $NP ? ##

$NP are the number of processes that you will use for performing the simulation. 

## What is [OptionsA] ? ##

These are commandline flags/options that control your simulation. You can think of it as a way to talk to the solver.

## What all options do I have in [OptionsA] ? ##

Here is the list of options that are available. 

```
-dimension [int]		Accepts values 2 or 3. Use 3 if your problem is 3D. Default is 2 for 2D problem.
```
```
-partitioner [sting]		Mesh partitioner to be used. Options are "metis" "parmetis" "scotch" or "ptstoch".
```
```
-partitioner parmetis		Mesh partitioner is parmetis. Additional option active '-parmetis_worker [int]'.
```
```
-lagrange    [int]      	Lagrange order used for building FE space. 1 for P1 or 2 for P2. Defaut is P1. 
```
```
-plot        [bool]             Use -plot to activate plotting using medit. Default is false.
```
