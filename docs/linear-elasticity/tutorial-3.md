# Multiple Dirichlet Conditions in Linear Elasticity (2D Clamped Bar)

To showcase the usage of linear elasticity with more than one Dirichlet condition, we discuss here a 2D bar which bends under its own load. The same problem from tutorials 1 and 2 is reused: a bar 5 m in length and 1 m in width, made of a material with density $\rho=8\times 10^3$, Young's modulus $E=200\times 10^9$, and Poisson's ratio $\nu=0.3$.

Contrary to tutorials 1 and 2, now **both ends** of the bar are clamped (i.e., two Dirichlet conditions instead of one).

## Step 1: Preprocessing

First step in a PSD simulation is preprocessing. At this step, you tell PSD what kind of physics, boundary conditions, approximations, and mesh you expect to solve.

In the terminal, `cd` to the folder `'/home/PSD-tutorials/linear-elasticity'`. Launch `PSD_PreProcess` with the command:

<pre><code>
PSD_PreProcess -problem linear_elasticity -dimension 2 -bodyforceconditions 1 \
-dirichletconditions 2 -postprocess u
</code></pre>

After `PSD_PreProcess` runs successfully, you should see many `.edp` files in your current folder.

**What do the arguments mean?**

- `-problem linear_elasticity` → solving linear elasticity
- `-dimension 2` → 2D simulation
- `-bodyforceconditions 1` → apply a body force on the domain
- `-dirichletconditions 2` → two Dirichlet borders
- `-postprocess u` → enable ParaView output

Since both problems (from tutorials 1 and 2) are essentially the same, the command is almost identical. The only difference is the added Dirichlet condition: `-dirichletconditions 2`.

To provide Dirichlet conditions for the left clamped end ($u_x=u_y=0$), in `ControlParameters.edp` set:

- `Dbc0On 2`
- `Dbc0Ux 0.`
- `Dbc0Uy 0.`

For the right clamped end, set:

- `Dbc1On 4`
- `Dbc1Ux 0.`
- `Dbc1Uy 0.`

Each of these corresponds to borders labeled `2` and `4` in the mesh `../Meshes/2D/bar.msh`.

Material and force properties in `ControlParameters.edp`:

- `E = 200.e9`
- `nu = 0.3`
- `Fbc0Fy -78480.0` (from $\rho g = 8 \times 10^3 \times (-9.81)$)

Specify the mesh via:

- `ThName = "../Meshes/2D/bar.msh"`
- `Fbc0On 1` to identify the volume tag

> 💡 **Note**: For this simple problem, the mesh `bar.msh` is provided in `../Meshes/2D/`. This is a triangular mesh created using Gmsh.

> 💡 **Note**: You may also generate your own meshes in `.msh` (version 2) or `.mesh` format using Salome or Gmsh.

## Step 2: Solving

Use 3 parallel processes to solve the 2D bar problem:

<pre><code>
PSD_Solve -np 3 Main.edp -mesh ./../Meshes/2D/bar.msh -v 0
</code></pre>

- `-np 3` → number of MPI processes
- `-mesh` → path to the mesh (can be omitted if set in `ControlParameters.edp`)
- `-v 0` → screen verbosity

`PSD_Solve` is a wrapper around `FreeFem++-mpi`.

> 💡 **Note**: PSD has been tested with up to 24,000 processes on Joliot-Curie (GENCI). But for this problem, a few are enough.

## Step 3: Postprocessing

PSD outputs ParaView-compatible files. After solving, open the `.pvd` file in the `VTUs_DATE_TIME` folder using ParaView.

You can visualize outputs like in the figure below:

![Partitioned mesh and displacement field](./Images/le-2d-bar-partitioned3.png)
![Clamped bar with deformed shape](./Images/le-2d-bar-clamped-ends.png)

**Figure**: The 2D clamped bar problem: partitioned mesh and displacement field visualization in ParaView.

You’re all done with the 2D linear elasticity simulation!

> 💡 **Note**: Try running the 3D version. Use `-dimension 3` in `PSD_PreProcess` and update the mesh and Dirichlet border labels accordingly in `ControlParameters.edp`.

## Redoing the Test on Jupiter and Moon

Imagine you wish to know how the test compares if performed on the Moon or Jupiter. Since gravity is the only force involved, try changing the gravitational constant.

- **Moon**: $g = 1.32$
- **Jupiter**: $g = 24.79$

In `ControlParameters.edp`, change the force term:

- For Moon: `Fbc0Fy -10560.0` ($8 \times 10^3 \times -1.32$)
- For Jupiter: `Fbc0Fy -198320.0` ($8 \times 10^3 \times -24.79$)

Then redo Step 2 (solving) and Step 3 (postprocessing).

Side-by-side visualization:

![Warped field on the Moon](./Images/le-2d-bar-moon.png)
![Warped field on Jupiter](./Images/le-2d-bar-Jupiter.png)

**Figure**: 2D clamped bar with 20000× warped displacement fields — Moon (left) and Jupiter (right).
