#A parallel/sequential ff++ solid mechanics solver #

Solid mechanics solver modules wrapped around FreeFem++ for discretization, and PETSc for linear algebra/Preconditioning. 

## How to run the solver ? ##

The parallel/sequential solvers can be run on linux platforms and can be used with command line options  to control the solver.

### Step 1 ? ###

```
ff-mpirun -np 1 SolverGenerator.edp -v 0 -nw [OptionsA]

```

### Step 2 ? ###
For parallel:
```
ff-mpirun -np $NP Main.edp -v 0 -nw [OptionsB]

```
For sequential:
```
FreeFem++ Main.edp -v 0 -nw [OptionsB]

```

## What is $NP ? ##

$NP are the number of processes that you will use for performing the simulation in parallel. 

## What is [OptionsA] ? ##

These are commandline flags/options that control your simulation. You can think of it as a way to talk to the solver.

## What all options do I have in [OptionsA] ? ##

Here is the list of options that are available.
```
-sequential	[bool]		To solve via a sequential solver. Default is false.
``` 
```
-help		[bool]		To activate helping message on the terminal. Recommended flag ON by default.
```
```
-pointbc	[bool]		To activate Dirichlet boundary condition on point.
``` 
``` 
-dynamic	[bool]		To activate dynamic solver.
``` 
``` 
-bodyforce	[bool]		To activate volumetric source term (body force).
``` 
```
-dirichletbc	[bool]		To activate Dirichlet boundary condition.
``` 
```
-tractionbc	[bool]		To activate traction boundary condition (Neumann). 
```
```
-dimension	[int]		Accepts values 2 or 3. Use 3 if your problem is 3D. Default is 2 for 2D problem.
```
```
-partitioner	[sting]		Mesh partitioner to be used. Options are "metis" "parmetis" "scotch" or "ptstoch".
```
```
-partitioner	parmetis	Mesh partitioner is parmetis. Additional option active '-parmetis_worker [int]'.
```
```
-lagrange	[int]		Lagrange order used for building FE space. 1 for P1 or 2 for P2. Defaut is P1. 
```
```
-plot		[bool]		Use -plot to activate plotting using paraview. Default is false.
```
```
-pipegnu	[bool]		Use -pipegnu to activate realtime pipe plotting using GnuPlot. Default is false.
```
