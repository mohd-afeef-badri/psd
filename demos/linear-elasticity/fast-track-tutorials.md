#  Linear Elasticity Tutorials  #



### Parallel  2D linear-elasticity  ###

Single dirichlet condition (clamped end bar) and body force source term

```
PSD_PreProcess -dimension 2 -bodyforceconditions 1 -sequential -dirichletconditions 1
```

```
PSD_Solve  Main.edp  -mesh ./../Meshes/2D/bar.msh -v 0
```







### Parallel  3D linear-elasticity  ###

Single dirichlet condition (clamped end bar) and body force source term

```
PSD_PreProcess -dimension 3 -bodyforceconditions 1  -dirichletconditions 1
```

```
PSD_Solve  Main.edp  -mesh ./../Meshes/2D/bar.msh -v 0
```



- *Optionally try using `-fastmethod` flag with `PSD_PreProcess` for producing optimized codes*

- *Add `-sequential` flag to `PSD_PreProcess`  for sequential solver, but remember to use `PSD_Solve_Seq` instead of `PSD_Solve`*