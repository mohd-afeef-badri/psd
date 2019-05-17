#  PSD: a Parallel Structural Dynamics solver #

![markdownimage](/data/images/markdownimage.png)

PSD is a solid mechanics solver modules wrapped around [FreeFem++](https://freefem.org/) for discretization, and [PETSc](https://www.mcs.anl.gov/petsc/) for linear algebra/Preconditioning. PSD solver contains straightforward supports for *static* or *dynamic* simulations with *linear* mechanics and *nonlinear* mechanics problems. Besides these *hybrid-phase field fracture mechanics* models has also been incorporated within PSD. PSD uses sate-of-the art domain-decomposition paradigm for parallel computing and all solvers are  proven to scale quasi-optimally.

PSD works for two and three dimensional problems only. Unstructured meshes (triangular for 2D and tetrahedral for 2D) are supported in [MEDIT's](https://www.ljll.math.upmc.fr/frey/software.html) .mesh format or [Gmsh's](http://gmsh.info/) .msh format. PSD post processing is done via .vtk and .vtu files of the [ParaView](https://www.paraview.org/) platform. 



## Installation ##

PSD is built to work with Linux platforms.

**Dependencies** 
- automake
- FreeFemm++
- gmsh
- gnuplot	(optional)
- C++
- git

**Now that I have all the dependencies what next**
- Go ahead and grab the latest copy of PSD. The code is hosted on CEA's internal git [repository](https://codev-tuleap.intra.cea.fr/plugins/git/hpcseism/freefem?a=shortlog&hb=devel-dynamic).
```
git clone https://codev-tuleap.intra.cea.fr/plugins/git/hpcseism/freefem.git
```
- Autoconf PSD within the  cloned folder
```
autoreconf -i
```
- Configure  PSD within the  cloned folder
```
./configure 
```
*Note* `./configure` will install PSD in `$HOME/PSD` to change this directory use `--prefix=Your/Own/Path` with `./configure`.
- Build PSD
```
make FFINSTALLDIR=/usr/local/bin/ GMSH=~/usr/local/bin/gmsh
```
*Note* variable `FFINSTALLDIR` can be changed to the FreeFem++ local path if installed locally. Similarly variable `GMSH` can be changed for Gmsh.
- Install PSD
```
make install
```
Now you should have the solver at `$HOME/PSD`. To use the solver please go to `$HOME/PSD`.

## How to run the solver ? ##

The parallel/sequential solvers can be run on Linux platforms and can be used with command line options  to control the solver.

### Step 1 ? ###

```
ff-mpirun -np 1 SolverGenerator.edp -v 0 -nw [OptionsA]

```

### Step 2 ? ###
For parallel:
```
ff-mpirun -np **NP** Main.edp -v 0 -nw [OptionsB]

```
For sequential:
```
FreeFem++ Main.edp -v 0 -nw [OptionsB]

```

## What is $NP ? ##

**NP** is the number of processes that you will use for performing the simulation in parallel. 

## What is [OptionsA] ? ##

These are commandline flags/options that control your simulation. You can think of it as a way to talk to the solver.

## What all options do I have in [OptionsA] ? ##

Here is the list of options that are available.

- `-sequential	[bool]`	  To solve via a sequential solver. Default is false.

- `-help	[bool]`	 To activate helping message on the terminal. Recommended flag.

- `-pointbc	[bool]`	To activate Dirichlet boundary condition on point.

- `-dynamic	[bool]`	To activate dynamic solver.

- `-bodyforce	[bool]`	To activate volumetric source term (body force).

- `-dirichletbc	[bool]`	To activate Dirichlet boundary condition.

- `-tractionbc	[bool]`	To activate traction boundary condition (Neumann). 

- `-dimension	[int]`	Accepts values 2 or 3. Use 3 for 3D. and 2 for 2D problem.

- `-partitioner	[sting]` Mesh partitioner could be "metis" "parmetis" "scotch" or "ptstoch".

- `-lagrange	[int]`	Lagrange order used for FE spaces. 1 for P1 or 2 for P2. Defaut is P1. 

- `-plot	[bool]`	Use -plot to activate plotting using paraview. Default is false.

- `-pipegnu	[bool]`	Use to activate realtime pipe plotting using GnuPlot. Default is false.

