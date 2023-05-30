# Changelog
PSD has been maturing and evolving with time, following subsections present the highlights of  some key changes made to each PSD version.

## Rolling release (2.6)

### Added

### Changed

### Removed

### Bug



## [2.5](https://gitlab.com/PsdSolver/psd_sources/-/tree/v2.5) - 2023-05-12

### Added

- PDMT - polyhedral dual meshing tool added to PSD, can be accessed via `load pdmt`
  - meshes can be outputted in `pvtu`, `vtu`, or `med` format

- `medio` now can save polyhedral meshes
- Hypre compilation for testing BoomerAMG
- Universal binary of SALOME 9.9.0 is shipped along, in order to build it look at `Makefile.am` in `ext`
- Additional geometries and meshes can now be performed with SALOME
- MED handled in a more robust way, one can used wither MEDCOUPLING or SALOME for MED support
- New compilation flags `--with-hdf5`  `--with-medfile` and
`--with-medcoupling` for MED support for `medio`
- New variable added for `PsdMfrontHandler()` function `mfrontExternalStateVariableVector`
- New anisotropic 2D and 3D damage laws compiled with mfront plugin for local and nonlocal problems
- New variables added to `PsdMfrontPrintBehaviourStats()` for printing new laws
- New file `TFEL_MatrixFunc.hxx` for computing the inverse of full 2D matrices in mfront plugin includes.
- New tests in `src/plugins/mfront/test/` for anisotropic damage laws
- Hujeux law added at C++-MFRONT-PSD level
- New configuration flag `--with-zipped_dependencies`, can be provided if the user decides to provide zipped files for dependencies and compile without Internet

### Changed

- Moved to FreeFEM 4.12
- Moved to PETSc 3.18.2
- Moved to MFRONT 4.0.0
- Moved to MGIS 2.0
- `load PSD-PETSc` replace by `load PETSc` (native PETSc module from FreeFEM)
- `load PSD-iovtk` replace by `load iovtk` (native iovtk module from FreeFEM)
-  Test 8 `src/plugins/mfront/test/` does iterations to test new anisotropic damage laws
-  old Test 8 for mfront laws becomes now Test_PrintStats

### Removed

- `PSD-PETSc` module removed
- `PSD-iovtk` module removed

### Bug
- Mfront-Mgis `PsdMfrontHandler()` Bug in updating internal variables from one step to another in 2D problems has been removed.



## [2.4](https://gitlab.com/PsdSolver/psd_sources/-/tree/v2.4) - 2022-07-20

### Added

- SALOME `.med` file support. For conversion on disk is done upon reading a `.med`
  - New `load "medio"` enables loading of medio library for PSD
  - Function `savemedmesh()` used for saving med file (see unit test `Test_1.edp`)
  - Function `loadmedmesh()` used for saving med file (see unit test `Test_2.edp`)
  - Function `getMedLabelsOnGroup()` used for getting the label tag for a group (see unit test `Test_2.edp`)
- Additional tests for Elastodynamics, Damage Mechanics.
- Additional validation tests in `tests/validation` folder.
- New argument `-getenergies` works in soildynamics and elastodynamics, can be used to get K.E, E.E, D.E, T.T.
- New flag `-activeplot` to activate Gnuplot plotting via piping, note this replaces the `-piegnu`.
- New flag `-validation` to produce validation test case code, for now only accepts `iwan`.
- Support for Dirichlet Point conditions in sequential for fracture mechanics.
  - New tests for checking point BC.
- New Iwan law for PSD-MFront coupling.
- PSD installation support for MacOS.
- New macro `perfromRCMreordering(meshObject)` to perform mesh level Reverse Cuthill-Mackee algo.
- New `PsdMfrontPrintBehaviourStats()` to probe the mfront file and know the input/output.
- New variables added for `PsdMfrontHandler()` function `mfrontStrainTensor, mfrontStateVariable, `.
- New variables added for `PsdMfrontHandler()` function `mfrontExternalStateVariableNames, mfrontExternalStateVariableValues, `.
- More unit tests for mfront plugin.
- New elasto-plastic von Mises non-linear model using mfornt. Via argument `-problem elasto_plastic` and `-model von_mises`
- New elasto-plastic tutorial.
- Ability to calculate reaction forces for linear-elasticity model (use `-getreactionforce -reactionforce .....`)
- New automake variable `--with-dependencies=yes` for installing all dependencies (FreeFEM, PETSc, Gmsh, MFRONT, MGIS)
- Dependencies can now be installed by PSD.

### Changed

- `startProcedure()` and `endProcedure()` macros replace `timerBegin()` and `timerEnd()` macros.

- Moved to FreeFEM 4.10
- Moved to PETSc 3.16.1
- MFRONT material handler has a new name: `mfrontElasticityHandler` is now `PsdMfrontHandler`

### Removed

- Removed the `-supercomp` argument, no longer needed.
- Removed the `-pipegnu` flag.

### Bug

- Bug in `-plotreactionforce` when used with stress-based method has been removed.

## [2.3](https://gitlab.com/PsdSolver/psd_sources/-/tree/v2.3) - 2021-09-13

### Added

- New argument `-useMfront` now activates the Mfront--PSD coupling.
- More tests for each plugin and physics, now added in their respective folders.
- Support for Mfront and Mgis interface for non-linear material laws
- New plugin `mfront` can now be loaded in PSD.
- `-withmaterialtensor` now uses Quadrature finite elements to build the material tensor.
- New variational formulation for handling Linear mechanics problems, Quadrature point wise material tensor is built.
- `pseudo_nonlinear` implementation of Linear Elasticity now works.
- New `Notes` section added in the source repo, to help with mathematical and algorithmic reasoning.

### Bug

- Bug in top-ii-vol meshing due to MPI communication removed.
- Bug in  `pseudo_nonlinear` model for Elastodynamics/soildynamics fixed.

## [2.2](https://gitlab.com/PsdSolver/psd_sources/-/tree/v2.2) - 2021-07-28
### Added

- New and more verbose tutorials on fracture mechanics, soil-dynamics.
- Fast and parallel post processing is now performed using `pvtu` files.
- New PETSc interface in plugins that supports pvtu output.
- Error mechanism to signify wrong PSD flags.

### Changed

- Flag values now donot contain hyphens '-' use underscore instead '_', e.g,
`linear-elasticity` is now `linear_elasticity`
- 4 CPU procs are now used for `make check`, user can control this by `make
check NP=USER_PROCS`.
- Moved to FreeFEM 4.9 and PETSc 3.15.0 .
- Moved to GitLab for hosting the repository.
- New checks for wrong flag. Now if wrong flag or values is entered PSD will give error.
- Boolean flags now also accept value 1|0|yes|no|on|off|true|false for turning on or off.

## [2.1](https://gitlab.com/PsdSolver/psd_sources/-/tree/v2.1) - 2021-01-27
### Added
- New accurate force calculations via matrix-vector product: new flag `-getreactionforce`.
- New flag `-reactionforce` variational-based | stress-based to get reaction force on a surface.
- New flag `-plotreactionforce` to activate real time pipe plotting using GnuPlot.
- More verbos info on `-help`
- New flag `-mesh` to provide the name of mesh to `PSD_Solve`.
- New flag `-probe` to postprocess FE variables at a point.
- New flag `-crackdirichletcondition` to include a pre-cracked Dirichlet in damage models.
- New tests for more advance top-ii-vol partitioning.
- New flag `-constrainHPF` to enable constrain conditions in hybrid phase-field (WIP).
- New developments in parallel interpolations.
- Tutorials added, use `make tutorials` to install

### Changed

- Moved to FreeFEM 4.7-1.
- Moved to PETSc 3.14.
- New version of top-ii-vol v 1.3 support for exascale computing (includes new 2D 3D partitioning)
- `-fastmethod`  now replaced by `-withmaterialtensor` (this is now inverse of `-fastmethod`)

### Removed
- Flag `-pipegnu` not supported for damage mechanics (to be further deprecated from elsto/soildynamics)

### Bugs removed

- Stain vector incorrect numbering in split function of GFP

   ( see hash  [5ec7b882494f71984d07f468b518ec886e942d32](https://codev-tuleap.intra.cea.fr/plugins/git/hpcseism/freefem?a=commit&h=5ec7b882494f71984d07f468b518ec886e942d32))

- Hybrid phase-field with constrain with wrong update

   (see has [20ebfbc3cc58b9f1407658543bf3b239e74bd089](https://codev-tuleap.intra.cea.fr/plugins/git/hpcseism/freefem?a=commit&h=20ebfbc3cc58b9f1407658543bf3b239e74bd089))



## [2.0](https://gitlab.com/PsdSolver/psd_sources/-/tree/v2.0) - 2020-08-18
### Added
- New processing via C++, `PSD_PreProcess` binary (MAJOR CHANGE).
- New solving via shell wrapper `PSD_Solve` instead of `FreeFem++` or `FreeFem++-mpi`.
- New examples of using the solver.
- New Pdf documentation containing tutorials, function definitions, verbos on PSD C++ library.
- New option `-nonlinearmethod` (Picard|Newton-Raphsons).
- New time discretization option `-timediscretization`.
- New point boundary conditions.
- New dummy city mesh and analysis 2D for soil dynamics.
- Automatic identification of FreeFEM and Gmsh during `./configure`.
- New flags for `--with-FreeFEM=` and `--with-Gmsh=` during `./configure`.
- New flag `-bodyforceconditions` [int] to include body force.
- New flag `-problem` linear-elasticity | damage | elastodynamics | soildynamics to define physics.
- New flag `-model` to set approximation for damage mechanics hybrid-phase-field | Mazar | pseudo-nonlinear | Hujeux.
- Better energy splitting included Hybrid phase-field compressibility vs tensile energy condition.
- Introduce boundary conditions via `-dirichletconditions` [int] flag.
- Introduce point boundary conditions via `-dirichletpointcondition` [int] flag.
- Introduce traction boundary conditions via `-tractionconditions` [int] flag.
- New folder `tests` containing unit-tests for modules.
- New Hujeux law (nonlinear soil law) interface using C++ class (Thanks to Evelyne Foerster).
- New pseudo-nonlinear model for solving elastodynamics and soildynamics with nonlinear Newton-Raphsons.
- Introduced double couple earthquake source boundary condition for soildynamics.
- New flag `-doublecouple` force-based | displacement-based   to use double couple source for soildynamics.
- New top-ii-vol parallel meshing via `-top2vol-meshing` flag (compatible with soildynamics).

### Changed
- Moved to FreeFEM 4.6.
- Moved to PETSc 13.13.
- Moved to C++ for preprocessing.
- Moved to shell wrapper PSD_Solve for solving.
- Changes to GFP energydecopostion plugin 'DecompEnergy_Op', now includes compressibility history.
- Replaced GFPDecompEnergy2D/GFPDecompEnergy3D by a generic 2D/3D function GFPSplitEnergy(Eps1[],PsiPlus[],PsiMinus[],HistPlus[],HistMinus[],par);.
- Postprocessing flag `-postprocess` options now support  `u` , `v`,  `a` , `uv`, `ua`, `av` or `uav`.

### Removed
- No more `FFINSTALLDIR` and `GMSH` variables during `make` and `make check`.
- No more `-plot` flag now handled by `-postprocess`.
- No more `-nonlinear` flag now handled by `-problem` and `-model`.
- No more `-bodyforce` flag now handled by an `int` valued `-bodyforceconditions`.
- No more `-dynamic` flag now handled by `-problem` and `-model`.
- No more `-soildynamic` flag now handled by `-problem` and `-model`.
- No more `-quasistatic` flag now handled by `-problem` and `-model`.
- No more `-dirichletbc` flag now handled by `-dirichletconditions`.

### Bugs removed
- Bug in 3D paraxial loading (see hash [8fcbe7390e526423cd24b5f0ab1c06899b36c67f](https://codev-tuleap.intra.cea.fr/plugins/git/hpcseism/freefem?a=blobdiff&h=f23846d41b3eee27b9f2c3b852b9c5e2f90080c5&hp=0af4cfcc1355b98cc09a94e42c8ec521c6c0bb00&hb=8fcbe7390e526423cd24b5f0ab1c06899b36c67f&f=src%2Fpsd-preprocessor%2FMacros.hpp))




## [1.8](https://gitlab.com/PsdSolver/psd_sources/-/tree/v1.8) - 2020-01-21
### Added
- New soil dynamic module `-soildynamics`
- New paraxial element support in 2D.
- New timeplotting support `-timepvd`
- New `-postprocess` option for postprocessing `u` , `v`,  `a` , or `uav`.

### Changed
- Moved to FreeFEM 4.4.2.
- Moved to PETSc 13.12.
- New simpler way of plotting `savevtk` in parallel with `append` flag for iterative solutions.
- VTU files get stored with a date and time stamp.
- New way of maintaining a logfile for all simulations (date,time,case,..) in `simulation-log.csv`.


## [1.7](https://gitlab.com/PsdSolver/psd_sources/-/tree/v1.7) - 2019-11-08
### Added
- New  mesh reordering via Reverse Cuthill-Mackee via `-useRCM`.
- New quasi-static parallel solver (Extension of B.Masseron & G.Rastiello sequential version).
- New GFP plugin for Mazar's damage update for 2D/3D problems `GFPMazarsDamageUpdate(...)`.
- New MPI plotting routine `plotJustMeshMPI()`.
- New option `-fastmethod` to switch back to default variational formulation.
- New  make flag for compiling on supercomputer.

### Changed
- Changed variational formulation now using $\epsilon(u):A:\epsilon(v)$.
- Using GFP becomes optional `-useGFP`.
- Better documentation via `.md` and `.html` files.
- Better plotting support for `PlotMPI()`.
- Moved to FreeFEM 4.4.


## [1.6](https://gitlab.com/PsdSolver/psd_sources/-/tree/v1.6) - 2019-06-11
### Added
- Dynamic linear solver in 2D and 3D  parallel/sequential.
- New finite element variable for partition of unity-- for fixing integrals.



### Changed
- Better documentation via `.md` and `.html` files.
- Correct quadrature order for faster computations.
- Major changes/splitting of `.script` files.

### Removed
- Removed the `BoundaryAndSourceConditions.script` merged with `ControlParameters.script`.

### Bugs
- Bug in integrals fixed.

## [1.5](https://gitlab.com/PsdSolver/psd_sources/-/tree/v1.5) - 2019-05-29
### Added
- Dynamic linear solver in 2D and 3D  sequential.
- New meshes for dynamics tests `bar-dynamic.msh`.
- Checking modules `make check`.
- Faster sparsity pattern calculations.

### Changed
- Better documentation via `.md` and `.html` files.
- Major restructuring of the codes.
- Moved to `automake` for solver installation.
- Mesh building via `make`.

### Removed
- Removed the manufactured solution codes.



## [1.4](https://gitlab.com/PsdSolver/psd_sources/-/tree/v1.4) - 2019-05-14
### Added
- Fully vectorial finite element solver for phase-field `-vectorial`.
- New `-supercomp` for avoiding xterm issues on super computers.
- New `MatViz()` function for matrix sparsity visualization.
- Introduced `GFP` plugin support (Go Fast Plugins).

### Changed
- Elastic energy decomposition is now optional `-energydecomp`.
- Force calculation using integrals (Thanks to G.Rastiello).

## [1.3](https://gitlab.com/PsdSolver/psd_sources/-/tree/v1.3) - 2019-04-08
### Added
- New meshes in 2D/3D`Notched-plate` , `square-crack`, etc.
- New fracture mechanics module.
- New `-nonlinear` flag to activate phase-field model for brittle fracture.
- New `-timelog` for time logging the solver.
- New `-pipegnu` for GNUplot piping.


### Changed
- Scripting now performed using `.script` files:
	- `BoundaryAndSourceConditions.script `
	- `LinearFormBuilderAndSolver.script  `
	- `Macros.script  `
	- `Main.script  `
	- `VariationalFormulation.script  `
	- ....
- Move to FreeFEM version 4.0.
- Move to PETSc version 3.11.

## [1.2](https://gitlab.com/PsdSolver/psd_sources/-/tree/v1.1) - 2019-03-18
### Added
- Support for Gmsh's `.msh`  or Medit's `.mesh` meshes in folder `Meshes`.
- Advance to 3D physics.
- New MPI based parallel solver linear elasticity.
- New approach for solver generation via scripting (PhD thesis MA Badri) with `scriptGenerator.edp`.
- Integrated Domain decomposition macro (PhD thesis MA Badri).
- Customized `.vtk` support for ParaView post-processing.
- New point boundary condition macro `pointbc(Real[int], fespace, matrix)`.
- New flags for communicating with the solver: `-dimension`, `-plot`, `-bodyforce`, `-lagrange`, etc.


### Changed
- More advance README.MD.
- Sequential solver now merged within scripting via flag `-sequential`.
- Move to FreeFEM version 3.62.
- Moved manufactured solutions to `validation-test` folder.


## [1.1](https://gitlab.com/PsdSolver/psd_sources/-/tree/v1.1) - 2019-03-04
### Added
- Initial FreeFEM files for sequential linear elasticity in 2D (case of constrained bar).
- More cases of manufactured solution for linear elasticity in 2D.
- Added README.MD for explaining the solver.
- ParaView plotting activated.

### Changed
- Moved to Tuleap git hosting from CEA.
- Separate folder of manufactured solutions and the linear elastic solver.
- Move to FreeFEM version 3.61.

## [1.0](https://gitlab.com/PsdSolver/psd_sources/-/tree/v1.0) - 2019-02-15
### Added
- Initial FreeFEM files  Method of manufactured solution for linear elasticity in 2D.

## Version git tags ##

| Version                                                     | Git tag                                  |
| ----------------------------------------------------------- | ---------------------------------------- |
| [1.0](https://gitlab.com/PsdSolver/psd_sources/-/tree/v1.0) | 8a8ecb2746b7da792073358c60df33bae647f788 |
| [1.1](https://gitlab.com/PsdSolver/psd_sources/-/tree/v1.1) | a667e6085ba1f92f8dd619bd40e18f85c593bc0a |
| [1.2](https://gitlab.com/PsdSolver/psd_sources/-/tree/v1.2) | e48b7b3a30c05ad4c343efa6a17fee386031f437 |
| [1.3](https://gitlab.com/PsdSolver/psd_sources/-/tree/v1.3) | 39f4324550365849852c5264b8d4535aae05e30d |
| [1.4](https://gitlab.com/PsdSolver/psd_sources/-/tree/v1.4) | f51f678630eb9b2fed355e5cedf976ce8b5fa341 |
| [1.5](https://gitlab.com/PsdSolver/psd_sources/-/tree/v1.5) | 07293ba09a69d3d6a16278220a0b4a7a9f318f96 |
| [1.6](https://gitlab.com/PsdSolver/psd_sources/-/tree/v1.6) | f359dd049fb1ddde376e8ad8e5177c663e430418 |
| [1.7](https://gitlab.com/PsdSolver/psd_sources/-/tree/v1.7) | aee9bfec868a70b3d9974d7692bc19f9739ab7dc |
| [1.8](https://gitlab.com/PsdSolver/psd_sources/-/tree/v1.8) | 2f26292636c7248133e31ae912ee58113de2ef71 |
| [2.0](https://gitlab.com/PsdSolver/psd_sources/-/tree/v2.0) | 1e1a4d7f10df30d106b52eba1c5caf69e8bc0f36 |
| [2.1](https://gitlab.com/PsdSolver/psd_sources/-/tree/v2.1) | 8b9d84f25aedbd684eb0f06cdd4ffbbf9a60a0e2 |
| [2.2](https://gitlab.com/PsdSolver/psd_sources/-/tree/v2.2) | 5e0368f990d505d3bf1960122cb99a23e08567b0 |
| [2.3](https://gitlab.com/PsdSolver/psd_sources/-/tree/v2.3) | 0744b19fbe7da6d523754092e92f3882b57f0760 |
| [2.4](https://gitlab.com/PsdSolver/psd_sources/-/tree/v2.4) | 3dea315606ab98b95d18b84fa0c3afa01acc6e54 |
