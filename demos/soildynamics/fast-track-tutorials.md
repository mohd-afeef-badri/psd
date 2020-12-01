# Soildynamics Tutorials #



### Parallel 2D with 4 MPI processes ###

Single Dirichlet condition

```bash
PSD_PreProcess -dimension 2 -problem soildynamics -dirichletconditions 1 \
-timediscretization newmark-beta
```

```bash
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/2D/soil.msh -v 0
```





### Parallel 3D with 3 MPI processes ###

Single Dirichlet condition and Newmark-beta time discretization

```bash
PSD_PreProcess -dimension 3 -problem soildynamics -dirichletconditions 1 \
-timediscretization newmark-beta
```

```bash
PSD_Solve -np 3 Main.edp -mesh ./../Meshes/3D/soil.msh -v 0
```







### Parallel 2D with double couple with 2 MPI processes ###

Single Dirichlet via double couple and using GFP. Double couple is displacement based. 

```bash
PSD_PreProcess -dimension 2 -problem soildynamics -model linear \
-timediscretization newmark-beta -useGFP -doublecouple displacement-based
```

```bash
PSD_Solve -np 2 Main.edp -v 1 -ns -nw -mesh ./../Meshes/2D/soil-dc.msh
```

*try replacing `-doublecouple displacement-based` with `-doublecouple force-based` for double couple constructed by force based method*





### Parallel 3D with double couple with 4 MPI processes ###

Single Dirichlet via double couple and using GFP. Double couple is displacement based. 

```bash
PSD_PreProcess -dimension 3 -problem soildynamics -model linear \
-timediscretization newmark-beta -useGFP -doublecouple displacement-based
```

```bash
PSD_Solve -np 4 Main.edp -v 1 -ns -nw -mesh ./../Meshes/2D/soil-dc.msh
```

*try replacing `-doublecouple displacement-based` with `-doublecouple force-based` for double couple constructed by force based method*





### Parallel 3D with top-ii-vol meshing with 4 MPI processes ###

Single Dirichlet at the bottom and using GFP.

```bash
PSD_PreProcess -dimension 3 -problem soildynamics -model linear \
-timediscretization newmark-beta -useGFP -top2vol-meshing
```

```bash
PSD_Solve -np 4 Main.edp -v 0 -ns -nw 
```





### Parallel 3D with top-ii-vol meshing with 3 MPI processes ###

Single Dirichlet via double couple and using GFP. Double couple is displacement based. 

```bash
PSD_PreProcess -dimension 3 -problem soildynamics -model linear \
-timediscretization newmark-beta -useGFP -top2vol-meshing -doublecouple displacement-based
```

```bash
PSD_Solve -np 3 Main.edp -v 0 -ns -nw 
```

*try replacing `-doublecouple displacement-based` with `-doublecouple force-based` for double couple constructed by force based method*



- *Optionally try using `-fastmethod` flag with `PSD_PreProcess` optimized solver*
- *Optionally try using `-timediscretization generalized-alpha` instead of `-timediscretization newmark-beta` to change time discretization scheme*
- *Add `-sequential` flag to `PSD_PreProcess` for sequential solver, but remember to use `PSD_Solve_Seq` instead of `PSD_Solve`*
