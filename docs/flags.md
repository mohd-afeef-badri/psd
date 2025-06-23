## Flags for `PSD_PreProcess`

The `PSD_PreProcess`  is a TUI-based application, hence it heavily relies on command line flags for user interaction. These flags become a medium of communication between the user and the PSD solver. Three types of flags can be used:

- `int` type: these are integer type flags which expect an integer argument,  
- `string` type: these flags expect a string argument, and  
- `bool` type: these are boolean type flags with no argument.


### Integer flags

<table>
  <thead>
    <tr>
      <th>Flag</th>
      <th>Description</th>
      <th>Default</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><code>-dirichletpointconditions</code></td>
      <td>Number of Dirichlet points.</td>
      <td><code>0</code></td>
    </tr>
    <tr>
      <td><code>-dirichletconditions</code></td>
      <td>Number of Dirichlet boundaries.</td>
      <td><code>0</code></td>
    </tr>
    <tr>
      <td><code>-bodyforceconditions</code></td>
      <td>Number of regions to which body force is applied.</td>
      <td><code>0</code></td>
    </tr>
    <tr>
      <td><code>-tractionconditions</code></td>
      <td>Number of Neumann/traction boundaries.</td>
      <td><code>0</code></td>
    </tr>
    <tr>
      <td><code>-dimension</code></td>
      <td>Dimension of problem. 2 for 2D, 3 for 3D.</td>
      <td><code>2</code></td>
    </tr>
    <tr>
      <td><code>-lagrange</code></td>
      <td>Lagrange order used for building FE space.</td>
      <td><code>1</code> (P1)</td>
    </tr>
  </tbody>
</table>


### String flags

<table>
  <thead>
    <tr>
      <th>Flag</th>
      <th>Description</th>
      <th>Possible values</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><code>-timediscretization</code></td>
      <td>Time discretization type.</td>
      <td><code>generalized_alpha</code> | <code>newmark_beta</code> | <code>hht_alpha</code> | <code>central_difference</code></td>
    </tr>
    <tr>
      <td><code>-nonlinearmethod</code></td>
      <td>Nonlinear method type.</td>
      <td><code>Picard</code> | <code>Newton_Raphsons</code></td>
    </tr>
    <tr>
      <td><code>-partitioner</code></td>
      <td>Mesh partitioner.</td>
      <td><code>metis</code> | <code>scotch</code> | <code>parmetis</code></td>
    </tr>
    <tr>
      <td><code>-postprocess</code></td>
      <td>Indicate postprocessing quantity.</td>
      <td><code>u</code> | <code>v</code> | <code>a</code> | <code>phi</code> | <code>uphi</code> | <code>uva</code></td>
    </tr>
    <tr>
      <td><code>-doublecouple</code></td>
      <td>Soil dynamics double couple boundary condition.</td>
      <td><code>force_based</code> | <code>displacement_based</code></td>
    </tr>
    <tr>
      <td><code>-reactionforce</code></td>
      <td>Reaction force calculation method.</td>
      <td><code>stress_based</code> | <code>variational_based</code></td>
    </tr>
    <tr>
      <td><code>-problem</code></td>
      <td>Interested problem.</td>
      <td><code>linear_elasticity</code> | <code>damage</code> | <code>elastodynamics</code> | <code>soildynamics</code> | <code>elasto_plastic</code></td>
    </tr>
    <tr>
      <td><code>-model</code></td>
      <td>Interested model.</td>
      <td><code>hybrid_phase_field</code> | <code>Mazar</code> | <code>pseudo_nonlinear</code></td>
    </tr>
  </tbody>
</table>


### Bool flags

<table>
  <thead>
    <tr>
      <th>Flag</th>
      <th>Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><code>-help</code></td>
      <td>Helping message on the terminal.</td>
    </tr>
    <tr>
      <td><code>-debug</code></td>
      <td>OpenGL plotting routine for displaying solution.</td>
    </tr>
    <tr>
      <td><code>-useGFP</code></td>
      <td>Activate use of GoFastPlugins, a suite of C++ plugins.</td>
    </tr>
    <tr>
      <td><code>-timelog</code></td>
      <td>Setup time logging for various phases of the solver.</td>
    </tr>
    <tr>
      <td><code>-useRCM</code></td>
      <td>Mesh level renumbering via Reverse Cuthill Mckee.</td>
    </tr>
    <tr>
      <td><code>-useMfront</code></td>
      <td>Activate MFront interface for PSD.</td>
    </tr>
    <tr>
      <td><code>-vectorial</code></td>
      <td>Generate vectorial space solver for non-linear.</td>
    </tr>
    <tr>
      <td><code>-sequential</code></td>
      <td>Generate a sequential PSD solver.</td>
    </tr>
    <tr>
      <td><code>-pointprobe</code></td>
      <td>Setup a point probe to record variables.</td>
    </tr>
    <tr>
      <td><code>-energydecomp</code></td>
      <td>Hybrid phase-field energy decomposition.</td>
    </tr>
    <tr>
      <td><code>-constrainHPF</code></td>
      <td>Use constrain condition in hybrid phase-field model.</td>
    </tr>
    <tr>
      <td><code>-top2vol-meshing</code></td>
      <td>top-ii-vol point source meshing for soil-dynamics.</td>
    </tr>
    <tr>
      <td><code>-getreactionforce</code></td>
      <td>Extraction reactions at surface.</td>
    </tr>
    <tr>
      <td><code>-plotreactionforce</code></td>
      <td>Live pipe plotting using GnuPlot.</td>
    </tr>
    <tr>
      <td><code>-withmaterialtensor</code></td>
      <td>Use material tensor to build stiffness matrix.</td>
    </tr>
    <tr>
      <td><code>-crackdirichletcondition</code></td>
      <td>Activate pre-cracked surface Dirichlet for damage mechanics.</td>
    </tr>
  </tbody>
</table>


## Flags for `PSD_Solve`

Just like `PSD_PreProcess`, the solver in PSD, `PSD_Solve`, also relies heavily on command line flags for user interaction. These flags become a medium of communication between the user and the PSD solver. Three types of flags can be used:

1. **`int` type:** these are integer type flags which expect an integer argument,  
2. **`string` type:** these flags expect a string argument, and  
3. **`bool` type:** these are boolean type flags with no argument.


### Integer flags

<table>
  <thead>
    <tr>
      <th>Flag</th>
      <th>Description</th>
      <th>Default</th>
      <th>Accepted values</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><code>-np</code></td>
      <td>Number of processes.</td>
      <td>2</td>
      <td>1 to ∞</td>
    </tr>
    <tr>
      <td><code>-v</code></td>
      <td>FreeFEM flag verbosity of the background FEM kernel.</td>
      <td>1</td>
      <td>0 to 1000 (0 for no output)</td>
    </tr>
    <tr>
      <td><code>-split</code></td>
      <td>Flag to split uniformly the mesh.</td>
      <td>1 (no splitting)</td>
      <td>2 to 12 (2 = split once)</td>
    </tr>
    <tr>
      <td><code>-ksp_max_it</code></td>
      <td>PETSc flag to choose Krylov solver max iterations.</td>
      <td>1000</td>
      <td>—</td>
    </tr>
    <tr>
      <td><code>-parmetis_worker</code></td>
      <td>Active when mesh partitioner is parmetis.</td>
      <td>—</td>
      <td>—</td>
    </tr>
  </tbody>
</table>


### Real  flags

<table>
  <thead>
    <tr>
      <th>Flag</th>
      <th>Description</th>
      <th>Default</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><code>-ksp_atol</code></td>
      <td>PETSc flag to set absolute tolerance for Krylov solver convergence.</td>
      <td>1e-5</td>
    </tr>
    <tr>
      <td><code>-ksp_rtol</code></td>
      <td>PETSc flag to set relative tolerance for Krylov solver.</td>
      <td>1e-5</td>
    </tr>
  </tbody>
</table>

### String  flags

<table>
  <thead>
    <tr>
      <th>Flag</th>
      <th>Description</th>
      <th>Example / Possible values</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><code>-mesh</code></td>
      <td>Mesh file to be used. Either `.mesh` or `.msh` format.</td>
      <td><code>-mesh nameofmesh.mesh</code></td>
    </tr>
    <tr>
      <td><code>-ksp_type</code></td>
      <td>PETSc flag to choose the Krylov solver.</td>
      <td><code>cg</code> (default) | <code>gmres</code> | <code>bicg</code> | <code>bicgstab</code></td>
    </tr>
    <tr>
      <td><code>-pc_type</code></td>
      <td>PETSc flag to choose preconditioner for the solver.</td>
      <td><code>bjacobi</code> (default) | <code>jacobi</code> | <code>lu</code> | <code>gamg</code></td>
    </tr>
    <tr>
      <td><code>-sub_pc_type</code></td>
      <td>PETSc flag to choose sub preconditioner for solver.</td>
      <td><code>ilu</code> (default) | <code>icc</code> | <code>lu</code> | <code>gamg</code></td>
    </tr>
  </tbody>
</table>

### Bool  flags

<table>
  <thead>
    <tr>
      <th>Flag</th>
      <th>Description</th>
      <th>Default</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td><code>-wg</code></td>
      <td>FreeFEM flag to activate with graphics option for OpenGL graphics.</td>
      <td>false</td>
    </tr>
    <tr>
      <td><code>-nw</code></td>
      <td>FreeFEM flag to activate no windows output on screen.</td>
      <td>false</td>
    </tr>
    <tr>
      <td><code>-ns</code></td>
      <td>FreeFEM flag to activate no script output on screen.</td>
      <td>false</td>
    </tr>
  </tbody>
</table>

## Flags physics-wise

| **Flag Type**   | **Linear Elasticity**                                                                                                                                                                    | **Damage Mechanics**                                                                                                                                                                        | **Elastodynamics**                                                                                                                                                                       | **Soildynamics**                                                                                                                                                                         |
| --------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **INT TYPE**    | -dirichletpointconditions<br>-dirichletconditions<br>-bodyforceconditions<br>-tractionconditions<br>-parmetis\_worker<br>-ksp\_max\_it<br>-dimension<br>-lagrange<br>-split<br>-np<br>-v | -dirichletpointconditions<br>-dirichletconditions<br>-bodyforceconditions<br>-tractionconditions<br>-parmetis\_worker<br>-ksp\_max\_it<br>-dimension<br>-lagrange<br>-split<br>-np<br>-v    | -dirichletpointconditions<br>-dirichletconditions<br>-bodyforceconditions<br>-tractionconditions<br>-parmetis\_worker<br>-ksp\_max\_it<br>-dimension<br>-lagrange<br>-split<br>-np<br>-v | -dirichletpointconditions<br>-dirichletconditions<br>-bodyforceconditions<br>-tractionconditions<br>-parmetis\_worker<br>-ksp\_max\_it<br>-dimension<br>-lagrange<br>-split<br>-np<br>-v |
| **REAL TYPE**   | -ksp\_rtol<br>-ksp\_atol                                                                                                                                                                 | -ksp\_rtol<br>-ksp\_atol                                                                                                                                                                    | -ksp\_rtol<br>-ksp\_atol                                                                                                                                                                 | -ksp\_rtol<br>-ksp\_atol                                                                                                                                                                 |
| **STRING TYPE** | -partitioner<br>-postprocess<br>-sub\_pc\_type<br>-ksp\_type<br>-pc\_type<br>-problem<br>-mesh                                                                                           | -nonlinearmethod<br>-reactionforce<br>-partitioner<br>-postprocess<br>-sub\_pc\_type<br>-ksp\_type<br>-pc\_type<br>-problem<br>-mesh<br>-model                                              | -timediscretization<br>-partitioner<br>-postprocess<br>-sub\_pc\_type<br>-ksp\_type<br>-pc\_type<br>-problem<br>-mesh<br>-model                                                          | -doublecouple<br>-postprocess<br>-partitioner<br>-sub\_pc\_type<br>-ksp\_type<br>-pc\_type<br>-problem<br>-mesh<br>-model                                                                |
| **BOOL TYPE**   | -withmaterialtensor<br>-sequential<br>-timelog<br>-useGFP<br>-useRCM<br>-debug<br>-help<br>-wg<br>-nw<br>-ns                                                                             | -crackdirichletcondition<br>-plotreactionforce<br>-getreactionforce<br>-energydecomp<br>-sequential<br>-vectorial<br>-timelog<br>-useGFP<br>-useRCM<br>-debug<br>-help<br>-wg<br>-nw<br>-ns | -sequential<br>-timelog<br>-useGFP<br>-useRCM<br>-debug<br>-help<br>-wg<br>-nw<br>-ns                                                                                                    | -top2vol-meshing<br>-sequential<br>-timelog<br>-useGFP<br>-useRCM<br>-debug<br>-help<br>-wg<br>-nw<br>-ns                                                                                |
