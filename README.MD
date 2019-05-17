#  PSD: a Parallel Structural Dynamics solver #

PSD is a solid mechanics solver modules wrapped around [FreeFem++](https://freefem.org/) for discretization, and [PETSc](https://www.mcs.anl.gov/petsc/) for linear algebra/Preconditioning. PSD solver contains straightforward supports for *static* or *dynamic* simulations with *linear* mechanics and *nonlinear* mechanics problems. Besides these *hybrid-phase field fracture mechanics* models has also been incorporated within PSD. PSD uses sate-of-the art domain-decomposition paradigm for parallel computing and all solvers are  proven to scale quasi-optimally. It also includes a squential solver which does not require [PETSc](https://www.mcs.anl.gov/petsc/) . 

PSD works for two and three dimensional problems only. Unstructured meshes (triangular for 2D and tetrahedral for 3D) are supported in [MEDIT's](https://www.ljll.math.upmc.fr/frey/software.html)  `.mesh` format or [Gmsh's](http://gmsh.info/) `.msh` format. PSD post processing is done via `.vtk` and `.vtu` files of the [ParaView](https://www.paraview.org/) platform. 

## Installation procedure ##

PSD is built to work with Linux platforms.

**Dependencies**  

- automake
- FreeFem++
- PETSc       (optional)
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
*Note*:   `./configure` will install PSD in `$HOME/PSD` to change this directory use `--prefix=Your/Own/Path` with `./configure`. 

- Build PSD

```
make FFINSTALLDIR=/usr/local/bin/ GMSH=~/usr/local/bin/gmsh
```
*Note* variable `FFINSTALLDIR` can be changed to the [FreeFem++](https://freefem.org/) local path if installed locally. Similarly variable `GMSH` can be changed for [Gmsh](http://gmsh.info/).

- Install PSD
```
make install
```
Now you should have the solver at `$HOME/PSD`. To use the solver please go to `$HOME/PSD`.

## Using procedure  ##

The parallel/sequential solvers can be run on Linux platforms and can be used with command line options  to control the solver. In order to make your choice of physics, command line options need to be typed right into the bash. 

To perform a simulation three steps are involed

**Step 1: Providing the mesh**  

A valid finite elemnt mesh needs to be provided to the solver. PSD accepts only  unstructured meshes: triangular for 2D and tetrahedral for 3D. These meshes need to be in  [MEDIT's](https://www.ljll.math.upmc.fr/frey/software.html)  `.mesh` format or [Gmsh's](http://gmsh.info/) `.msh` format. Once you have your mesh please copy the mesh to `Meshes` folder of your installed PSD directory. The 2D meshes need to be seperated by the 2D ones.

*Note:*  There is a native mesher `bmag` within [FreeFem++](https://freefem.org/) which could also be used. However, it can only be used to generate simple geometries. In this case no need to copy the mesh to the `Meshes` folder. 

**Step 2: Setting up the solver **  

Now that the mesh has been loaded. Its time to set up the solver. Open the `terminal` window at the location of the solver, i.e., `$HOME/PSD/Solver.` Then run the following command in the `terminal`.

```
FreeFem++ SolverGenerator.edp -v 0 -nw -help [Options-PSD]
```

Via the command line options you will embed the physics within the solver. This step generates a bunch of `.edp` files which are native to [FreeFem++](https://freefem.org/)  and additionally prints out instructions on what to do next. You then need to open and edit couple of these files via your favourite text editor, which could be `vim`, `gedit` ,`Notepad++`, etc.  To facilitate the edit process for your will have to go through the instructions printed on the terminal. 

**Step 3: Launching the solver**  

Now you are all set to run your simulation. To do so you will need to do the run the following in the `terminal`:

if you complied a parallel PSD version

```
ff-mpirun -np $N Main.edp -v 0 -nw
```
if you complied a sequential PSD version
```
FreeFem++ Main.edp -v 0 -nw
```

*Note*: in the parallel command **$N** is an `int` value, i.e., number of processes that you want to use for performing the simulation in parallel.

*Sit back and be amazed at the speed of the solver.* 

## [Options-PSD]  explained  ##

These are a set of commandline flags/options that control your simulation. You can think of it as a way to talk to the solver. Here is a table that lists out all the options that are available.

| Option         | Type      | Comment                                                      |
| -------------- | --------- | :----------------------------------------------------------- |
| `-help`        | `[bool]`  | To activate helping message on the terminal.  Recommended flag. |
| `-dimension`   | `[int]`   | Accepts values 2 or 3. Use 3 for 3D. and 2 for 2D problem.   |
| `-sequential`  | `[bool]`  | To solve via a sequential solver.   Default is false.        |
| `-lagrange`    | `[int]`   | Lagrange order used for FE spaces. 1 for P1 or 2 for P2. Defaut is P1. |
| `-dirichletbc` | `[bool]`  | To activate Dirichlet boundary condition.                    |
| `-bodyforce`   | `[bool]`  | To activate volumetric source term (body force).             |
| `-tractionbc`  | `[bool]`  | To activate traction boundary condition (Neumann).           |
| `-pointbc`     | `[bool]`  | To activate Dirichlet boundary condition on point.           |
| `-partitioner` | `[sting]` | Mesh partitioner could be "metis" "parmetis" "scotch" or "ptstoch". |
| `-dynamic`     | `[bool]`  | To activate dynamic solver.                                  |
| `-plot`        | `[bool]`  | Use -plot to activate plotting using paraview. Default is false. |
| `-pipegnu`     | `[bool]`  | Use to activate realtime pipe plotting using GnuPlot. Default is false. |

*To report bugs, issues, feature-requests contact:* 

- **mohd-afeef.badri@cea.fr**
- **mohd-afeef.badri@outlook.com**
- **mohd-afeef.badri@etu.univ-nantes.fr** 

