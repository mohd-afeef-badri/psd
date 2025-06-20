# 2D Linear Elasticity: Clamped Bar Pulled with Neumann (Traction) Force

A similar simulation to the previous tutorial is presented here. We showcase the 2D bar problem, where one end is clamped while the other end is pulled. As in the previous simulation, the body force is neglected. However, in this case, the pull on the non-clamped end is approximated using a Neumann (traction) force:

$$
\int_{\partial\Omega^h_{\text N}}(\mathbf t \cdot \mathbf{v}^h)
$$

To simulate the pull, we assume a traction vector  
$\mathbf{t} = [t_x, t_y] = [10^9, 0]$  
acting on the non-clamped right end of the bar. This means a force of $10^9$ units in the $x$-direction is applied. We use the same problem setup from tutorials 1 and 2: a bar 5 m in length and 1 m in width, made of a material with:

- density $\rho = 8 \times 10^3$
- Young’s modulus $E = 200 \times 10^9$
- Poisson’s ratio $\nu = 0.3$

---

## Step 1: Preprocessing

The first step in a `PSD` simulation is **preprocessing**. In this step, we specify the physics, boundary conditions, approximations, mesh, etc., to `PSD`.

In the terminal, `cd` into the folder:

<pre><code>cd /home/PSD-tutorials/linear-elasticity</code></pre>

Launch `PSD_PreProcess` with the following command:

<pre><code>PSD_PreProcess -problem linear-elasticity -dimension 2 -dirichletconditions 1 -tractionconditions 1 -postprocess u</code></pre>

> 💡 **Note**:  
> The command-line flag <code>-dirichletconditions 1</code> tells `PSD` that there is one Dirichlet boundary — the clamped end of the bar.  
> The flag <code>-tractionconditions 1</code> notifies `PSD` that there is one traction boundary — the pulled right end.

To apply the clamped boundary condition ($u_1 = 0,\ u_2 = 0$), set the following variables in <code>ControlParameters.edp</code>:

<pre><code>macro Dbc0On 2     //
macro Dbc0Ux 0.    //
macro Dbc0Uy 0.    //</code></pre>

The traction boundary conditions are defined in the same file:

<pre><code>macro Tbc0On 4     //
macro Tbc0Tx 1.e9  //</code></pre>

This applies the traction force $\mathbf{t} = [10^9, 0]$ to boundary label 4 (the right edge).  
To add a vertical traction component (e.g. $t_y = 100$), simply include:

<pre><code>macro Tbc0Ty 100.  //</code></pre>

---

## Step 2: Solving

Use 5 cores to solve the problem by running:

<pre><code>PSD_Solve -np 5 Main.edp -mesh ./../Meshes/2D/bar.msh -v 0</code></pre>

> 💡 **Note**:  
> This is the same command used in the previous bar problems, except here we use <code>-np 5</code> to solve in parallel using 5 cores.

The mesh file `bar.msh` is available in the `../Meshes/2D/` folder. It is a triangular mesh created with Gmsh.

> ⚠️ **Warning**:  
> This tutorial does **not** cover the meshing process in detail. You are free to use your own mesh, as long as it's in `.msh` (Gmsh version 2) or `.mesh` format. We recommend using Salome or Gmsh for mesh generation.

---

## Step 3: Postprocessing

Launch ParaView and open the `.pvd` file located in:

<pre><code>
PSD/Solver/VTUs_DATE_TIME/
</code></pre>

### Simulation Results

<div style="text-align: center;">
  <img src="https://github.com/user-attachments/assets/a5e842c5-5584-4c63-9211-6b4f73e6824b" width="300" style="margin-right: 20px; vertical-align: middle;" />
  <img src="https://github.com/user-attachments/assets/651b309a-9d7b-4304-99a2-12d3164fdd50" width="300" style="margin-left: 20px; vertical-align: middle;" />
</div>

**Figure:** Partitioned mesh (left) and 100× warped displacement field (right)

> 💡 **Note**:  
> Since 5 cores were used, the mesh was partitioned into 5 subdomains.  
> Unlike in the previous tutorial, the right end of the bar contracts in the $y$-direction. This behavior is expected because there is **no Dirichlet condition** at that end, allowing it to move laterally.
