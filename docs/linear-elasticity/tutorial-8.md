# 3D  mechanical piece (Dirichlet-Neumann case) with complex mesh

So far, we have focused on bar simulations, which are relatively simple. The meshes for these cases were pre-provided. Now, we consider a **3D simulation of a mechanical piece**, shown in the figure below.

The left (small) hole is fixed: $u_1=u_2=u_3=0$, while a traction force $t_x = 10^9$ is applied to the large hole.

You can obtain the CAD geometry (the Gmsh `.geo` file) from your local Gmsh installation at `gmsh/share/doc/gmsh/demos/simple_geo/piece.geo`. To generate the mesh `piece.msh`, run:

<pre><code>gmsh -3 piece.geo -format msh2
</code></pre>

Now the PSD simulation can proceed.


<div style="text-align: center; margin-bottom: 1em;">
  <img src="https://github.com/user-attachments/assets/9707d85c-05bb-48db-9ba2-e38684e2985f" width="300" />
</div>
*Figure: 3D mechanical piece.*

## Step 1: Preprocessing

Place the mesh `piece.msh` in a folder of your choice (assume `psd-complex-simulation`). Open a terminal in this folder and run:

<pre><code>PSD_PreProcess  -problem linear-elasticity -dimension 3 -dirichletconditions 1 -tractionconditions 1 -postprocess u
</code></pre>

This sets one Dirichlet condition (small hole) and one traction condition (large hole). The file `piece.msh` assigns label `4` to the Dirichlet border and `3` to the traction border.

To apply boundary conditions, in `ControlParameters.edp`:

- Dirichlet:`Dbc0On 4`, `Dbc0Ux 0.`, `Dbc0Uy 0.`, `Dbc0Uz 0.`
- Traction:
  `Tbc0On 3`, `Tbc0Ty -1.e9`

This corresponds to traction vector $\mathbf{t} = [0., 10^9, 0.]$.

Use steel material properties in `ControlParameters.edp`:

- `real E = 200.e9;`
- `real nu = 0.3;`

## Step 2: Solving

Use 2 cores:

<pre><code>PSD_Solve -np 2 Main.edp -mesh ./piece.msh
</code></pre>

## Step 3: Postprocessing

Launch ParaView and open the `.pvd` file in `PSD/Solver/VTUs_DATE_TIME`.

<div style="text-align: center; margin-bottom: 1em;">
  <img src="https://github.com/user-attachments/assets/bc0b1de7-bd6d-4c04-bb9b-517a8ccbd1f9" width="300" />
  <img src="https://github.com/user-attachments/assets/c33dfdd7-cea1-4376-95a2-f45e16e7b700" width="300" />
</div>

*Figure: Mechanical piece test results. Partitioned mesh (left) and warped displacement field (right).*

## Redoing the Test with Different Conditions

<div style="text-align: center; margin-bottom: 1em;">
  <img src="https://github.com/user-attachments/assets/0ae6ccce-0013-439d-a177-d9fc1b6b547c" width="300" />
</div>

*Figure: Mechanical piece test results: `real tx0 = 1.e9, ty0 = 0, tz0 = 0.;`*

<div style="text-align: center; margin-bottom: 1em;">
  <img src="https://github.com/user-attachments/assets/ccc3fea7-405e-48d2-b37a-484bd4666fcc" width="300" />
</div>

*Figure: Mechanical piece test results: `real tx0 = 1.e9, ty0 = 0, tz0 = 0.;`*
