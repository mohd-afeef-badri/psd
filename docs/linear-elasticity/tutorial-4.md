# 2D Linear Elasticity: Clamped Bar Pulled at One End

In this tutorial, we showcase the 2D bar simulation with one end clamped while being pulled at the other end. Body force is neglected, and the pull is modeled using a Dirichlet displacement \( u_1 = 1 \). Compared to the problems in **Tutorial 1** and **Tutorial 2**, the only difference is:

- **No body force is applied**, and  
- **An additional Dirichlet condition** is applied at the free end.

We consider the same setup:  
- A bar 5 m in length and 1 m in width  
- Material properties:  
  - Density: \( \rho = 8 \times 10^3 \, \text{kg/m}^3 \)  
  - Young’s modulus: \( E = 200 \times 10^9 \, \text{Pa} \)  
  - Poisson’s ratio: \( \nu = 0.3 \)

---

## Step 1: Preprocessing

First step is to tell PSD what kind of physics, boundary conditions, approximations, mesh, etc., are expected.

In the terminal, change to the tutorial folder:

<pre><code>
cd /home/PSD-tutorials/linear-elasticity
</code></pre>

Then launch the preprocessing tool:

<pre><code>
PSD_PreProcess -problem linear_elasticity -dimension 2 -dirichletconditions 2 -postprocess u
</code></pre>

### What do the arguments mean?

* `-problem linear_elasticity`: Solving a linear elasticity problem
* `-dimension 2`: 2D simulation
* `-dirichletconditions 2`: Two Dirichlet boundaries (clamped and pulled ends)
* `-postprocess u`: Generate postprocessing output for ParaView

> 🔍 Compared to previous tutorials, `-bodyforceconditions 1` is **omitted** here since no body force is applied.

### Define Dirichlet Conditions

In `ControlParameters.edp`, define the boundary conditions as:

* Clamped end (mesh label `2`):

<pre><code>
Dbc0On = 2;
Dbc0Ux = 0.;
Dbc0Uy = 0.;
</code></pre>

* Pulled end (mesh label `4`):

<pre><code>
Dbc1On = 4;
Dbc1Ux = 1.;
Dbc1Uy = 0.; // Optional: remove this line to allow vertical compression
</code></pre>

### Material Properties

Also in `ControlParameters.edp`, add:

<pre><code>
E = 200.e9;
nu = 0.3;
</code></pre>

Although body force is not used here, in general it would be set like this:

<pre><code>
Fbc0Fy = -78480.0; // = rho * g = 8e3 * -9.81
Fbc0On = 1;        // Volume tag where force applies
</code></pre>

### Mesh

Specify the mesh (if not passed during solving) in the same file:

<pre><code>
ThName = "../Meshes/2D/bar.msh";
</code></pre>

> ⚠️ The mesh file `bar.msh` (Gmsh v2 format) is in the `../Meshes/2D/` folder. You can generate your own using SALOME or Gmsh.

---

## Step 2: Solving

Since PSD is a **parallel solver**, we run it with 2 MPI processes:

<pre><code>
PSD_Solve -np 2 Main.edp -mesh ./../Meshes/2D/bar.msh -v 0
</code></pre>

* `-np 2`: Use 2 MPI processes
* `-mesh ./../Meshes/2D/bar.msh`: Provide the mesh
* `-v 0`: Set verbosity level
* `PSD_Solve`: Wrapper around `FreeFem++-mpi`

> 🧠 For large problems, you can increase the number of cores. PSD has been tested with up to **24,000 parallel processes** and problems with **billions of unknowns**.

---

## Step 3: Postprocessing

Once the solver finishes, you can visualize results in **ParaView**.

Open the `.pvd` file located in the output folder (e.g., `VTUs_DATE_TIME/`) using ParaView.

> 📊 From ParaView, you can visualize displacement, mesh partitions, and more (e.g., as in the figure below).

<div style="text-align: center;">
  <img src="https://github.com/user-attachments/assets/fdd2b873-bf86-48ca-abd7-9fae4e609bb0" width="300" style="margin-right: 20px; vertical-align: middle;" />
  <img src="https://github.com/user-attachments/assets/fec43b7b-b218-4fe3-8886-c55b8ecfaeda" width="300" style="margin-left: 20px; vertical-align: middle;" />
</div>
