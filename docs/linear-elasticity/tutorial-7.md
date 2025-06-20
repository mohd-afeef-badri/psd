# 3D Clamped Bar with Vertical Traction

In this section, we present a 3D simulation of a clamped bar using `PSD`. One end of the bar is clamped, and a vertical traction is applied at the non-clamped end. This setup is similar to previous tutorials but extended to three dimensions. The material properties remain unchanged, and a vertical traction of $t_y = -10^9$ units is applied at the free end.

We use the same bar geometry from Tutorials 1 and 2, now in 3D:  
- Length: 5 m  
- Width: 1 m  
- Height: 1 m  

The material is characterized by:  
- Density $\rho = 8 \times 10^3$  
- Young’s modulus $E = 200 \times 10^9$  
- Poisson’s ratio $\nu = 0.3$

---

## Step 1: Preprocessing

The first step in a `PSD` simulation is **preprocessing**. Here, you specify the physics, boundary conditions, approximations, mesh, etc.

In the terminal, `cd` to the folder:

`...`
<pre><code>(...)</code></pre>

Launch `PSD_PreProcess` by running:

<pre><code>PSD_PreProcess  -problem linear_elasticity -dimension 3 -dirichletconditions 1 -tractionconditions 1 -postprocess u</code></pre>

> 💡 **Note**:  
> The flag <code>-dirichletconditions 1</code> tells `PSD` that there is one Dirichlet boundary — the clamped end.  
> The flag <code>-dimension 3</code> sets the simulation to 3D.  
> The flag <code>-tractionconditions 1</code> tells `PSD` to apply one traction boundary — the loaded end.

To apply the Dirichlet condition ($u_x = 0,\ u_y = 0,\ u_z = 0$), edit `ControlParameters.edp` and set:

<pre><code>Dbc0On 1
Dbc0Ux 0.
Dbc0Uy 0.
Dbc0Uz 0.</code></pre>

Here, `1` is the mesh label of the clamped surface.

To apply the traction condition at the free end with $\mathbf{t} = [t_x, t_y, t_z] = [0., -10^9, 0.]$, set:

<pre><code>Tbc0On 2
Tbc0Ty -1.e9</code></pre>

Mesh label `2` corresponds to the surface where the traction is applied.

---

## Step 2: Solving

To solve the problem using 4 cores, run the following command:

<pre><code>PSD_Solve -np 4 Main.edp  -mesh ./../Meshes/3D/bar.msh -v 0</code></pre>

> 💡 **Note**:  
> This is the same command used in the earlier tutorials, now applied in a 3D setting.

> ⚠️ **Warning**:  
> The file <code>bar.msh</code> is located in the <code>../Meshes/3D/</code> directory.  
> This is a tetrahedral mesh generated with Gmsh. Mesh generation is not covered in this tutorial.  
> You may create your own meshes using Gmsh or Salome. Please ensure the format is either <code>.msh</code> (Gmsh version 2) or <code>.mesh</code>.

---

## Step 3: Postprocessing

Open ParaView and load the `.pvd` file found in:

```
PSD/Solver/VTUs_DATE_TIME/
```

### Simulation Results

![Clamped 3D Bar](./Images/3d-bar-clamped-ends.png)
![3D Bar Pulled and Partitioned](./Images/3d-bar-clamped-pulled-partioned.png)

**Figure:** 3D bar results. Partitioned mesh (left) and 0.5× warped displacement field (right)

> 💡 **Note**:  
> Since 4 cores were used, the domain was partitioned into 4 subdomains, as visible in the left image above.
