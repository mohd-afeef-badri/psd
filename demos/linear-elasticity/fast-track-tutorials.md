#  Linear Elasticity Tutorials  #



<img src="./2d-bar.png" alt="2d-bar" style="zoom:50%;" />

### Parallel  2D linear-elasticity  ###

Single dirichlet condition (clamped end bar) and body force source term

```
PSD_PreProcess -dimension 2 -bodyforceconditions 1  -dirichletconditions 1
```

```
PSD_Solve -np 4 Main.edp  -mesh ./../Meshes/2D/bar.msh -v 0
```

<img src="./2d-bar-partioned.png" alt="2d-bar-partioned" style="zoom:50%;" />

<img src="./2d-bar-results.png" alt="2d-bar-results" style="zoom:50%;" />

### Parallel  3D linear-elasticity  ###

Single dirichlet condition (clamped end bar) and body force source term

```
PSD_PreProcess -dimension 3 -bodyforceconditions 1  -dirichletconditions 1
```

```
PSD_Solve -np 4 Main.edp  -mesh ./../Meshes/3D/bar.msh -v 0
```



<img src="./3d-bar-clamped-ends.png" alt="3d-bar-clamped-ends" style="zoom: 80%;" />

<img src="./3d-bar-clamped-pulled-partioned.png" alt="3d-bar-clamped-pulled-partioned" style="zoom:80%;" />

- *Optionally try using `-fastmethod` flag with `PSD_PreProcess` for producing optimized codes*
- *Add `-sequential` flag to `PSD_PreProcess`  for sequential solver, but remember to use `PSD_Solve_Seq` instead of `PSD_Solve` and no `-np` flag*
