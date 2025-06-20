# Sequential vs. Parallel Solver for 2D Linear Elasticity

Same problem of linear elasticity as in tutorial 1 -- 2D bar which bends under its own load --, is discussed here. The bar 5 m in length and 1 m in width, and is supposed to be made up of a material with density $\rho=8\times 10^3$, Young's modulus $E=200\times 10^9$, and Poisson's ratio $\nu=0.3$. To avoid text repetition, readers are encouraged to go ahead with this tutorial only after tutorial 1.

<div style="text-align: center; margin-bottom: 1em;">
  <img src="https://github.com/user-attachments/assets/a8453c65-6254-4d9c-a608-e6e2433dc4aa" width="300" />
</div>

As we will not use a parallel solver but a sequential one, naturally, this tutorial leads to a slower solver than the previous tutorial 1. So this tutorial is not for speed lovers, but rather for detailing the full capacity of PSD. Also, sequential solvers are easier to develop and understand — hence this tutorial.

As the problem remains the same as tutorial 1, simply add `-sequential` flag to `PSD_PreProcess` flags from tutorial 1 for a PSD sequential solver. The flag `-sequential` signifies the use of sequential PSD solver. So the workflow for the 2D problem would be:

<pre><code>
PSD_PreProcess -problem linear_elasticity -dimension 2 -bodyforceconditions 1 \
-dirichletconditions 1 -postprocess u -sequential
</code></pre>

Similar to tutorial 1, we solve the problem using the given mesh file `bar.msh`. However, now we need to use `PSD_Solve_Seq` instead of `PSD_Solve`, as such:

<pre><code>
PSD_Solve_Seq Main.edp -mesh ./../Meshes/2D/bar.msh -v 0
</code></pre>

> 💡 **Note**: Users are encouraged to try out the 3D problem with the sequential solver. Also, comparing the results from a sequential solver to those from a parallel solver can help verify that both lead to exactly the same results.

> 💡 **Note**: For this simple problem, the bar mesh (`bar.msh`) has been provided in `../Meshes/2D/` folder. This mesh is a triangular mesh produced with Gmsh. Detailing the meshing procedure is not the purpose of PSD tutorials.

> 💡 **Note**: Users can generate their own meshes and provide them to PSD in `.msh` (please use version 2) or `.mesh` format. We recommend using Salome or Gmsh meshers for creating your own geometry and meshing them.

## Comparing CPU Time

Naturally, since we are not using parallel PSD for solving, we lose the advantage of solving fast. To testify to this claim, checking solver timings can be helpful. PSD provides means to time-log your solver via the `-timelog` flag.

> 💡 **Note**: This flag prints the amount of time taken by each step of your solver directly in the terminal.

> ⚠️ **Warning**: Using `-timelog` makes the solver slower, as it involves `MPI_Barrier` routines for correctly timing each operation.

An example workflow of 2D solver (parallel) with time logging:

<pre><code>
PSD_PreProcess -problem linear_elasticity -dimension 2 -bodyforceconditions 1 \
-dirichletconditions 1 -postprocess u -timelog
</code></pre>

We solve the problem using four MPI processes, with the given mesh file `bar.msh`:

<pre><code>
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/2D/bar.msh -v 0
</code></pre>

<div style="text-align: center; margin-bottom: 1em;">
  <img src="https://github.com/user-attachments/assets/0760f40c-9632-4bc2-83ff-a019cd5c2ab7" width="300" />
</div>


*Figure: Time logging output produced for parallel run on 4 processes using `-timelog` flag. Take note of timings produced for different operations of the solver.*

Now let us repeat the procedure but this time using the sequential solver:

<pre><code>
PSD_PreProcess -problem linear_elasticity -dimension 2 -bodyforceconditions 1 \
-dirichletconditions 1 -postprocess u -timelog -sequential
</code></pre>

We solve the problem now in sequential mode, with the given mesh file `bar.msh`:

<pre><code>
PSD_Solve_Seq Main.edp -mesh ./../Meshes/2D/bar.msh -v 0
</code></pre>

> 💡 **Note**: You should now see timings that are higher in comparison to the parallel solver.

Approximately, for large meshes, using 4 MPI processes should lead to a solver that's around 4 times faster.
