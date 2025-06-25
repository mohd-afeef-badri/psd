## Tutorial 1
### Parallel 2D Elastodynamic Simulations with PSD

> 💡 **Note**: These tutorials aim to kick-start usage of the elastodynamics module in PSD. They are concise by design and intended for users or developers with some familiarity with the software.

The problem of interest involves a clamped-end bar with a single Dirichlet boundary condition and traction loading. The simulation uses Newmark-$\beta$ time discretization. Postprocessing is performed for displacement, acceleration, and velocity ($u$, $a$, $v$).

<pre><code>PSD_PreProcess -dimension 2 -problem elastodynamics -dirichletconditions 1 -tractionconditions 1 \
-timediscretization newmark_beta -postprocess uav
</code></pre>

Once the preprocessing step is complete, solve the problem using two MPI processes and the given mesh file `(...bar_dynamic.msh)`.

<pre><code>PSD_Solve -np 2 Main.edp -mesh ./../Meshes/2D/bar_dynamic.msh -v 0
</code></pre>

<figure style="text-align: center;">
  <img src="_images/elastodynamics/ed-u0.png" width="18%" alt="Displacement field at time step 0" style="margin-right: 1%;">
  <img src="_images/elastodynamics/ed-u2.png" width="18%" alt="Displacement field at time step 2" style="margin-right: 1%;">
  <img src="_images/elastodynamics/ed-u3.png" width="18%" alt="Displacement field at time step 3" style="margin-right: 1%;">
  <img src="_images/elastodynamics/ed-u4.png" width="18%" alt="Displacement field at time step 4" style="margin-right: 1%;">
  <img src="_images/elastodynamics/ed-u5.png" width="18%" alt="Displacement field at time step 5">
  <figcaption><em>Figure: Finite element displacement field on warped mesh shown at different time steps.</em></figcaption>
</figure>

Use ParaView to postprocess the output files found in the `(...VTUs...)` folder. From this, visualizations like those shown above can be generated.

## Tutorial 2
### Parallel 3D Elastodynamic Simulations with PSD

> 💡 **Note**: These tutorials aim to kick-start usage of the elastodynamics module in PSD. They are concise by design and intended for users or developers with some familiarity with the software.

The problem of interest involves a clamped-end bar with a single Dirichlet boundary condition and traction loading. This example uses Newmark-$\beta$ time discretization. Postprocessing is intended for displacement, acceleration, and velocity ($u$, $a$, $v$).

<pre><code>PSD_PreProcess -dimension 3 -problem elastodynamics -dirichletconditions 1 -tractionconditions 1 \
-timediscretization newmark_beta
</code></pre>

Once the preprocessing step is completed, solve the problem using four MPI processes and the given mesh file `(...bar_dynamic.msh)`.

<pre><code>PSD_Solve -np 4 Main.edp -mesh ./../Meshes/3D/bar_dynamic.msh -v 0
</code></pre>


## Tutorial 3
### Sequential PSD Elastodynamic Simulations

> 💡 **Note**: These tutorials aim to kick-start usage of the elastodynamics module in PSD. They are concise by design and intended for users or developers with some familiarity with the software.

To run the same problems described earlier in **sequential mode**, add `(...-sequential)` to the `(...PSD_PreProcess)` command. Additionally, use `(...PSD_Solve_Seq)` instead of `(...PSD_Solve)`.

The workflow for the **2D problem** becomes:

<pre><code>PSD_PreProcess -dimension 2 -problem elastodynamics -dirichletconditions 1 -tractionconditions 1 \
-timediscretization newmark_beta -postprocess uav -sequential
</code></pre>

Once preprocessing is complete, solve the problem using the given mesh file `(...bar_dynamic.msh)`:

<pre><code>PSD_Solve_Seq -np 2 Main.edp -mesh ./../Meshes/2D/bar_dynamic.msh -v 0
</code></pre>

> ⚠️ **Warning**: Even in sequential mode, the `-np` flag may be required for compatibility but typically has no effect on parallelism.

You can similarly try out the **3D problem** by following the same workflow with `-dimension 3` and the appropriate mesh file.

## Tutorial 4
### Different Time Discretizations for Elastodynamic Simulations

> 💡 **Note**: These tutorials aim to kick-start usage of the elastodynamics module in PSD. They are concise by design and intended for users or developers with some familiarity with the software.

PSD offers different time discretization techniques for solving time-dependent problems. Instead of the Newmark-$\beta$ scheme, you can switch to a more advanced **Generalized-$\alpha$** scheme.

This is done by specifying the option `(...-timediscretization generalized_alpha)` in the preprocessing step. For example, for a **2D problem**, use:

<pre><code>PSD_PreProcess -dimension 2 -problem elastodynamics -dirichletconditions 1 -tractionconditions 1 \
-timediscretization generalized_alpha -postprocess uav
</code></pre>

After preprocessing, solve the problem using **three MPI processes** with the mesh file `(...bar_dynamic.msh)`:

<pre><code>PSD_Solve -np 3 Main.edp -mesh ./../Meshes/2D/bar_dynamic.msh -v 0
</code></pre>

You can similarly try out the **3D problem** by using `-dimension 3` and the appropriate 3D mesh.


## Tutorial 5
### Timelogging Elastodynamic Simulations


> 💡 **Note**: These tutorials aim to kick-start usage of the elastodynamics module in PSD. They are concise by design and intended for users or developers with some familiarity with the software.

---

PSD provides a way to log timing information from your solver via the `-timelog` flag. This enables the solver to report the time taken by different operations in each time step.  

⚠️ **Warning**: Using this feature may slow down your simulation, as it involves `MPI_Barrier` operations to measure timings accurately.


### 🛠 Example Workflow: 2D Solver with Time Logging

Run the preprocessing step with the `-timelog` flag:

<pre><code>PSD_PreProcess -dimension 2 -problem elastodynamics -dirichletconditions 1 -tractionconditions 1 \
-timediscretization newmark_beta -postprocess uav -timelog
</code></pre>

Then solve the problem using two MPI processes with the provided 2D mesh file:

<pre><code>PSD_Solve -np 2 Main.edp -mesh ./../Meshes/2D/bar_dynamic.msh -v 0
</code></pre>


### ⏱️ Example Output

<figure style="text-align: center;">
  <img src="_images/elastodynamics/ed-time-par.png" width="40%" alt="Time logging output produced for parallel run on 2 processes">
  <figcaption><em>Figure: Time logging output produced for parallel run on 2 processes.</em></figcaption>
</figure>


A similar time log is produced for the sequential solver:

<figure style="text-align: center;">
  <img src="_images/elastodynamics/ed-time-seq.png" width="40%" alt="Time logging output produced for parallel run on 2 processes">
  <figcaption><em>Figure: Time logging output produced for parallel run on 2 processes.</em></figcaption>
</figure>



### 🔍 Notes

- Compare the runtimes: The parallel solver takes ~**1.5 seconds**, while the sequential run takes ~**3.3 seconds**, indicating a **2x speedup** when using 2 MPI processes.
- The timing report includes the breakdown of solver phases, but only for the **final time step**.

Use these logs to analyze performance bottlenecks and compare scalability between sequential and parallel executions.
