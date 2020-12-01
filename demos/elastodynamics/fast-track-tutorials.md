# Elastodynamics Tutorials #



### Parallel 2D ###

Single Dirichlet condition (clamped end bar) and traction loading

```bash
PSD_PreProcess -dimension 2 -problem elastodynamics -dirichletconditions 1 \
-tractionconditions 1 -timediscretization newmark-beta
```

```bash
PSD_Solve Main.edp -mesh ./../Meshes/2D/bar-dynamic.msh -v 0
```





### Parallel 3D ###

Single Dirichlet condition (clamped end bar) and traction loading

```bash
PSD_PreProcess -dimension 3 -problem elastodynamics -dirichletconditions 1 \
-tractionconditions 1 -timediscretization newmark-beta
```

```bash
PSD_Solve Main.edp -mesh ./../Meshes/3D/bar-dynamic.msh -v 0
```



- *Optionally try using `-fastmethod` flag with `PSD_PreProcess` optimized solver*
- *Optionally try using `-timediscretization generalized-alpha` instead of `-timediscretization newmark-beta` to change time discretization scheme*
- *Add `-sequential` flag to `PSD_PreProcess` for sequential solver, but remember to use `PSD_Solve_Seq` instead of `PSD_Solve`*
