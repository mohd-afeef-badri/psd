# Linear Elasticity Tutorial 2D bar problem clamped at one end wile being pulled at the other end (Dirichlet-Neumann-Point boundary conditions case)

Similar simulations as in the previous tutorial are presented in this section. We showcase the 2D bar problem simulation with one end clamped while being pulled at the other end. Contrary to the simulation in the previous tutorial, the clamped end restricts only $x$-direction movement, i.e., $u_x=0$. As before, body force is neglected. The pull at the non-clamped end is approximated with a Neumann force term: $\int_{\partial\Omega^h_{\text N}}(\mathbf t\cdot \mathbf{v}^h)$.

To simulate the pull, we assume a traction vector $\mathbf t=[t_x,t_y]=[10^9,0]$ acting on the non-clamped (right) end of the bar, i.e., a force of $10^9$ units in the $x$-direction. We use the same problem as in previous tutorials 1 and 2: a bar 5 m in length and 1 m in width, made of a material with density $\rho=8\times 10^3$, Young’s modulus $E=200\times 10^9$, and Poisson’s ratio $\nu=0.3$.

Here is how `PSD` simulation of this case can be performed.

## Step 1: Preprocessing

First step in a `PSD` simulation is preprocessing. At this step, you tell `PSD` what kind of physics, boundary conditions, approximations, mesh, etc., you expect to solve.

In the terminal, `cd` to the folder `/home/PSD-tutorials/linear-elasticity`. Launch `PSD_PreProcess` from the terminal with the following command:

<pre><code>PSD_PreProcess -problem linear_elasticity -dimension 2 -dirichletconditions 1 -tractionconditions 1 \
-dirichletpointconditions 1 -postprocess u
</code></pre>

> 💡 **Note**:  
> The additional flag `-dirichletpointconditions 1` notifies `PSD` that there is one Dirichlet point boundary condition.

Edit the `ControlParameters.edp` file to specify the desired point boundary conditions:
- Set `Pbc0Ux  0.` and `Pbc0Uy  0.` to enforce $u_x = 0$, $u_y = 0$.
- Set `PbcCord = [[0. , 0. ]];` to indicate the point at $(x, y) = (0, 0)$.

We also specified `-dirichletconditions 1`, meaning one Dirichlet boundary. To impose the Dirichlet condition ($u_x = 0$), set:
- `Dbc0On 2`
- `Dbc0Ux 0.`

in `ControlParameters.edp`.

`PSD` understands that label `2` refers to the mesh border on which the Dirichlet condition is applied.

## Step 2: Solving

Use 6 cores to solve this problem by running:

<pre><code>PSD_Solve -np 6 Main.edp -mesh ./../Meshes/2D/bar.msh -v 0
</code></pre>

> 💡 **Note**:  
> This is the same command used in previous tutorials, except now we include `-np 6` to use multiple processors.

The mesh file `bar.msh` is provided in the `../Meshes/2D/` folder. This is a triangular mesh produced with Gmsh.

> ⚠️ **Warning**:  
> Detailed meshing is outside the scope of this tutorial. However, users can generate their own meshes using tools like **Salome** or **Gmsh**, and provide them to `PSD` in `.msh` (version 2 recommended) or `.mesh` format.

## Step 3: Postprocessing

Launch ParaView and open the `.pvd` file located in the `PSD/Solver/VTUs_DATE_TIME` folder.


<div style="text-align: center;">
  <img src="https://github.com/user-attachments/assets/c5414d8b-0e3b-4c32-a7bf-daca0cddd25e" width="300" style="margin-right: 20px; vertical-align: middle;" />
  <img src="https://github.com/user-attachments/assets/d9af4fcf-5585-409a-9666-cd2c2c75a53c" width="300" style="margin-left: 20px; vertical-align: middle;" />
</div>

*Figure: Partitioned mesh (left) and 100X warped displacement field (right).*

> 💡 **Note**:  
> In the figure above, there are six subdomains in the partitioned mesh. As expected, the right and left ends of the bar contract in the $y$-direction, while the bar elongates in the $x$-direction due to the applied force.
