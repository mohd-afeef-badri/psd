## Tutorial 1
### Tensile Cracking of a Pre-Cracked Plate (2D PSD Example)

> 💡 **Note**: This document details tutorials from the *fracture mechanics* module of PSD.

A two-dimensional test is introduced. The problem of interest is a typical single-notch square plate cracking test under tensile loading. A unit square with a pre-existing crack is clamped at the bottom with $u_1 = u_2 = 0$ (first boundary condition), and is loaded quasi-statically on its top surface with $u_2 = u_2 + \Delta u_2$ until the crack propagates through its walls. Thus, two Dirichlet conditions are applied: one on the top and one on the bottom border.

<div style="text-align: center;">
  <img src="_images/fracture-mechanics/square-notch.png" width="25%" alt="Domain of the single notch square cracking problem under tensile loading.">
</div>

*Figure: Domain of the single notch square cracking problem under tensile loading.*

To model this test, PSD provides a hybrid phase-field modelling technique. We use ParaView to post-process displacement $u$ and phase-field $d$ for visualising the cracking process. A PSD simulation consists of two steps, the first being the `PSD_PreProcess`:

<pre><code>PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field \
-dirichletconditions 2 -postprocess ud
</code></pre>

> 💡 **Note**: Explanation of flags:
>
> - This is a two-dimensional problem, so we use the flag `-dimension 2`.
> - The problem falls under damage mechanics, hence `-problem damage`.
> - We solve it using hybrid phase-field modelling: `-model hybrid_phase_field`.
> - There are two Dirichlet conditions: `-dirichletconditions 2`.
> - Post-processing is done for displacement $u$ and phase-field $d$ using `-postprocess ud`.

Once the preprocessing step is done, we solve the problem using four MPI processes with the given mesh file `tensile-crack.msh`. This is step two of the PSD simulation: `PSD_Solve`.

<pre><code>PSD_Solve -np 4 Main.edp -mesh ./../Meshes/2D/tensile-crack.msh -v 0
</code></pre>

<p align="center">
  <img src="_images/fracture-mechanics/u0.png" width="24%">
  <img src="_images/fracture-mechanics/u1.png" width="24%">
  <img src="_images/fracture-mechanics/u2.png" width="24%">
  <img src="_images/fracture-mechanics/u3.png" width="24%">
</p>

<p align="center">
  <img src="_images/fracture-mechanics/u4.png" width="24%">
  <img src="_images/fracture-mechanics/u5.png" width="24%">
  <img src="_images/fracture-mechanics/u6.png" width="24%">
  <img src="_images/fracture-mechanics/u7.png" width="24%">
</p> 

*Figure: Finite element displacement visualised for the 2D problem using ParaView at different timesteps. Time progresses left to right and top to bottom.*

<p align="center">
  <img src="_images/fracture-mechanics/d0000.png" width="24%">
  <img src="_images/fracture-mechanics/d0010.png" width="24%">
  <img src="_images/fracture-mechanics/d0020.png" width="24%">
  <img src="_images/fracture-mechanics/d0030.png" width="24%">
</p>

<p align="center">
  <img src="_images/fracture-mechanics/d0040.png" width="24%">
  <img src="_images/fracture-mechanics/d0050.png" width="24%">
  <img src="_images/fracture-mechanics/d0060.png" width="24%">
  <img src="_images/fracture-mechanics/d0069.png" width="24%">
</p>

*Figure: Finite element damage visualised for the 2D problem using ParaView at different timesteps. Time progresses left to right and top to bottom.*

Figures above show the finite element displacement and damage fields, which allow us to visualise the progression of cracking in the square plate.

<div style="text-align: center;">
  <img src="_images/fracture-mechanics/terminal1.png" width="50%" alt="Terminal output during simulation run.">
</div>

*Figure: Applied traction, non-linear iterations, and residual printed in the terminal.*

During the simulation, the terminal displays the traction updates, non-linear iterations to convergence at each time step, and the residuals of $u$ and $d$. Refer to the figure above for a sample output.

To construct your own test case, try editing the `ControlParameters.edp` file.

## Tutorial 2
### Tensile Cracking of a Pre-Cracked Cube: A 3D Example of the PSD Parallel Solver

A three-dimensional test, analogous to its two-dimensional counterpart introduced earlier, is used here as a tutorial example. The problem of interest involves a unit cube undergoing extrusion along the $z$-axis. Cracking is initiated and propagated under tensile loading. 

The cube has a pre-existing crack and is clamped at the bottom 
$$u_1=u_2=u_3=0.$$ 
A quasi-static displacement is applied on the top surface 
$$u_2 = u_2 + \Delta u_2$$ 
until the crack propagates through the walls. There are two Dirichlet conditions—one on the bottom and one on the top surface.

Just like in the 2D case, PSD's hybrid phase-field modelling technique is employed. We use ParaView post-processing to visualize the displacement field $u$ and the phase-field $d$ during the cracking process. A PSD simulation involves two steps.

### Step 1: Preprocessing

A preprocessing step is run with:

<pre><code>PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field  \
-dirichletconditions 2 -postprocess ud
</code></pre>

Notice that the flags are nearly identical to the 2D example, except for the additional <code>-dimension 3</code> flag, which indicates a three-dimensional problem.

### Step 2: Solving

After preprocessing, we solve the problem using MPI with the mesh file <code>tensile-crack.msh</code>:

<pre><code>PSD_Solve -np 3 Main.edp -mesh ./../Meshes/3D/tensile-crack.msh -v 0
</code></pre>

### Results and Visualization

### Displacement Field

<p align="center">
  <img src="_images/fracture-mechanics/u3d0.png" width="24%" alt="u3d0">
  <img src="_images/fracture-mechanics/u3d1.png" width="24%" alt="u3d1">
  <img src="_images/fracture-mechanics/u3d2.png" width="24%" alt="u3d2">
  <img src="_images/fracture-mechanics/u3d3.png" width="24%" alt="u3d3">
</p>

*Figure: Finite element displacement visualized for the 3D problem in ParaView at different timesteps (quasi-static simulation). Time progresses from left to right in a row and top to bottom across rows.*

### Damage Field

<p align="center">
  <img src="_images/fracture-mechanics/d3d0.png" width="24%" alt="d3d0">
  <img src="_images/fracture-mechanics/d3d1.png" width="24%" alt="d3d1">
  <img src="_images/fracture-mechanics/d3d2.png" width="24%" alt="d3d2">
  <img src="_images/fracture-mechanics/d3d3.png" width="24%" alt="d3d3">
</p> 

*Figure: Finite element damage visualized for the 3D problem in ParaView at different timesteps (quasi-static simulation). Time progresses from left to right in a row and top to bottom across rows.*

> 💡 **Note**: Figures above present the evolution of both displacement and damage fields, enabling a clear visualization of crack propagation in the cubic specimen.

### Additional Remarks

A PSD simulation is a two-step process, with step one being the inline code `PSD_PreProcess` and step two as `PSD_Solve`.

> ⚠️ **Warning**: Ensure the mesh file is correctly referenced and that MPI is configured properly on your system.

## Tutorial 3
### Parallel 2D tensile cracking and calculate-plotting reaction-force

> 💡 **Note**: This document presents concise tutorials for the **fracture mechanics** module of PSD. The aim is to provide a practical starting point for users and developers rather than exhaustive documentation.

In solid mechanics, quantities of interest often include plots such as **reaction force on a surface** versus the applied displacement. These outputs are frequently used in experimental validations.

PSD provides routines for calculating the reaction force on a surface and also allows live (runtime) plotting of these results.

Imagine a 2D tensile cracking test case. To observe the **reaction force vs. applied displacement**, two extra flags must be used during the preprocessing step with `PSD_PreProcess`:

> `-getreactionforce`

> `-reactionforce stress_based`

<pre><code>
PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field \
-dirichletconditions 2 -getreactionforce -reactionforce stress_based
</code></pre>

* The `-getreactionforce` flag tells PSD to include the routines for reaction force computation.
* The `-reactionforce stress_based` method calculates the force using the stress integral in the $y$ direction:

$$
F_y = \int_{\partial\Omega_{\text{top}}} \sigma_y
$$

> 💡 **Note**: An alternative method is `-reactionforce variational_based`, which is more accurate but slower. It uses matrix-vector multiplication:
>
 $$
 \{F_x, F_y\} = \mathbf{A} \{u_1, u_2\}
 $$

Run the simulation using `PSD_Solve` with the appropriate mesh and number of processes:

<pre><code>
PSD_Solve -np 4 Main.edp -mesh ./../Meshes/2D/tensile-crack.msh -v 0
</code></pre>

While the solver runs, a file named `force.data` will be created containing both the **reaction force** and **applied traction**.

You can then plot `force.data` to analyze how $F\_y$ and $F\_x$ evolve with $\Delta u\_2$. In this file:

* 1st column: loading $\Delta u\_2$
* 2nd column: $F\_x$
* 3rd column: $F\_y$

<div style="text-align: center;">
  <img src="_images/fracture-mechanics/plot-fd.png" width="60%" alt="Plot of Applied Traction vs Force in Y Direction">
</div>

*Figure: Applied traction vs. force in the y direction.*

> ⚠️ **Warning**: Ensure the output file `force.data` is correctly written before plotting; incomplete simulations might yield corrupted files.

If you have **GnuPlot** configured with PSD, you can enable **live plotting** of the force-displacement curve using the flag `-plotreactionforce` during preprocessing.


<div style="text-align: center;">
  <img src="_images/fracture-mechanics/gp0.png" width="32%" alt="Live Gnuplot 1">
  <img src="_images/fracture-mechanics/gp1.png" width="32%" alt="Live Gnuplot 2">
  <img src="_images/fracture-mechanics/gp2.png" width="32%" alt="Live Gnuplot 3">
</div>

*Figure: Live plotting of traction vs. force using PSD and GnuPlot.*

### Parallel 3D and Reaction Force Calculation

To extend the same analysis to a **3D tensile cracking case**, use:

<pre><code>
PSD_PreProcess -dimension 3 -problem damage -model hybrid_phase_field \
-dirichletconditions 2 -getreactionforce -reactionforce stress_based
</code></pre>

And then solve using:

<pre><code>
PSD_Solve -np 3 Main.edp -mesh ./../Meshes/3D/tensile-crack.msh -v 0
</code></pre>


> 💡 **Note**: Replace `<code>` elements above with appropriate `.edp` scripts and meshes relevant to your problem domain. The plotting routines are compatible with most GnuPlot-enabled systems.


## Tutorial 4
### Fracture mechanics Tutorials - L-shape cracking


<div style="text-align: center;">
  <img src="_images/fracture-mechanics/fm-geometry.png" width="30%" alt="Geometry of the L-shaped test used in this tutorial.">
</div>

*Figure: Geometry of the L-shaped test used in this tutorial.*

### Preprocessing

You can either solve the problem using vectorial approach (recommended) or using staggered approach. To generate the solver, use one of the following.

**Generation of solver (vectorial)**

<pre><code>
PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field \
-dirichletconditions 1 -dirichletpointconditions 1 -debug -postprocess ud \
-energydecomp -constrainHPF -vectorial -getreactionforce -plotreactionforce \
-reactionforce variational_based
</code></pre>

**Generating solver (staggered)**

<pre><code>
PSD_PreProcess -dimension 2 -problem damage -model hybrid_phase_field \
-dirichletconditions 1 -dirichletpointconditions 1 -debug -postprocess ud \
-energydecomp -constrainHPF -getreactionforce -plotreactionforce \
-reactionforce variational_based
</code></pre>

### Edit Cycle

#### Edit `ControlParameter.edp`

- Update physical parameter, change:

<pre><code>
  real lambda = 121.15e3 ,
       mu     = 80.77e3  ,
       Gc     = 2.7      ;
</code></pre>

to

<pre><code>
  real lambda = 6.16e3 ,
       mu     = 10.95e3 ,
       Gc     = 8.9e-2  ;
</code></pre>

- Update solver parameter, change:

<pre><code>
  real lfac  = 2.0  ,
       maxtr = 7e-3 ,
       tr    = 1e-5 ,
       dtr   = 1e-5 ,
       lo           ;
</code></pre>

to

<pre><code>
  real lfac  = 2.0  ,
       maxtr = 1    ,
       tr    = 1e-2 ,
       dtr   = 1e-2 ,
       lo           ;
</code></pre>

- Enter the correct point boundary condition, change:

<pre><code>
  real[int,int] PbcCord = [
//-------------------- [  x  , y  ] --------------------//
                       [  0. , 0. ]    // point 0
//------------------------------------------------------//
                      ];

   macro Pbc0Ux  -0. //
   macro Pbc0Uy  -0. //
</code></pre>

to

<pre><code>
  real[int,int] PbcCord = [
//-------------------- [  x  , y  ] --------------------//
                       [  470., 250. ]    // point 0
//------------------------------------------------------//
                      ]
;
   macro Pbc0Uy  tr //
</code></pre>

#### Edit `LinearFormBuilderAndSolver.edp`

- To postprocess correct reaction forces for **vectorial solver**, change:

<pre><code>
  for(int i=0; i < Th.nv; i++){
     if(abs(Th(i).y-1.)<.000001){
        forcetotx = forcetotx + F[][i*3]*DP[i*3];
        forcetoty = forcetoty + F[][i*3+1]*DP[i*3+1];
     }
  }
</code></pre>

to

<pre><code>
  if(mpirank==mpirankPCi[0]){
     forcetotx = forcetotx + F[][PCi[0]*3+0]*DP[PCi[0]*3+0];
     forcetoty = forcetoty + F[][PCi[0]*3+1]*DP[PCi[0]*3+1];
  }
</code></pre>

- To postprocess correct reaction forces for **staggered solver**, change:

<pre><code>
  for(int i=0; i < Th.nv; i++){
     if(abs(Th(i).y-1.)<.000001){
        forcetotx = forcetotx + F[][i*2]*DP[i*2];
        forcetoty = forcetoty + F[][i*2+1]*DP[i*2+1];
     }
  }
</code></pre>

to

<pre><code>
  if(mpirank==mpirankPCi[0]){
     forcetotx = forcetotx + F[][PCi[0]*2+0]*DP[PCi[0]*2+0];
     forcetoty = forcetoty + F[][PCi[0]*2+1]*DP[PCi[0]*2+1];
  }
</code></pre>

- To include cyclic loading, change:

<pre><code>
  //-----------------updating traction----------------//

  tr += dtr;
</code></pre>

to

<pre><code>
  //-----------------updating traction----------------//

  if(iterout<50)
     tr += dtr;
  if(iterout>=51 && iterout<110)
     tr -= dtr;
  if(iterout>=111)
     tr += dtr;
</code></pre>

<div style="text-align: center;">
  <img src="_images/fracture-mechanics/fm-mesh.png" width="30%" alt="Finite element mesh of the L-shaped test.">
</div>

*Figure: Finite element mesh of the L-shaped test.*

### Solving

Irrespective of whether vectorial or staggered mode is used, solve the problem using `PSD_Solve`:

<pre><code>
PSD_Solve -np 4 Main.edp -wg -v 0 -mesh ./../Meshes/2D/L-shaped-crack.msh
</code></pre>

### Postprocessing

Use ParaView to post-process results.


<div style="text-align: center;">
  <img src="_images/fracture-mechanics/fm-d1.png" width="30%" alt="Crack initiation">
  <img src="_images/fracture-mechanics/fm-d2.png" width="30%" alt="Crack movement">
  <img src="_images/fracture-mechanics/fm-d3.png" width="30%" alt="Crack development">
</div>

*Figure: Finite element solution showing crack initiation, movement, and development.*

On your screen, the force-displacement curve which plots `force.data` should look something like this:

<div style="text-align: center;">
  <img src="_images/fracture-mechanics/fm-force-displacement.png" width="50%" alt="Force-displacement curve with cyclic loading.">
</div>

*Figure: Force-displacement curve with cyclic loading.*
