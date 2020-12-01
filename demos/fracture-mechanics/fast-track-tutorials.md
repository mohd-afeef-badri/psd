# Fracture mechanics Tutorials #


### Parallel 2D with 4 MPI processes ###

```bash
PSD_PreProcess -dimension 2 -problem damage -model hybrid-phase-field \
-dirichletconditions 2
```

```bash
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/2D/tensile-crack.msh -v 0
```




### Parallel 3D with 3 MPI processes ###

```bash
PSD_PreProcess -dimension 3 -problem damage -model hybrid-phase-field \
-dirichletconditions 2
```

```bash
PSD_Solve -np 3 Main.edp -mesh ./../Meshes/3D/tensile-crack.msh -v 0
```





### Parallel 2D with 4 MPI processes and calculate reactionforce ###

```bash
PSD_PreProcess -dimension 2 -problem damage -model hybrid-phase-field \
-dirichletconditions 2 -getreactionforce -reactionforce stress-based
```

```bash
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/2D/tensile-crack.msh -v 0
```





### Parallel 3D with 3 MPI processes and calculate reactionforce ###

```bash
PSD_PreProcess -dimension 3 -problem damage -model hybrid-phase-field \
-dirichletconditions 2 -getreactionforce -reactionforce stress-based
```

```bash
PSD_Solve -np 3 Main.edp -mesh ./../Meshes/3D/tensile-crack.msh -v 0
```

- *Optionally try changing `-reactionforce stress-based` to `-reactionforce variational-based` for changing the method to extract reaction force, note that stress based method is way faster*

- *Optionally try using  `-useGFP` flag with `PSD_PreProcess` optimized solver*

- *Add `-sequential` flag to `PSD_PreProcess` for sequential solver, but remember to use `PSD_Solve_Seq` instead of `PSD_Solve`*

### ADVANCE USER ###

- *try the `-vectorial` flag for vectorial finite element method*
- *try the `-energydecomp` flag for using split of tensile energy*
- *try using `-constrainHPF` flag for using the constrain condition in hybrid phase field model*
