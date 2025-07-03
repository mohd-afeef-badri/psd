---
title: '`PSD`: A Parallel Finite Element Solver for Solid/Structural/Seismic Dynamics'
tags:
  - finite elements
  - parallel computing
  - seismic analysis
  - fracture mechanics
  - HPC
authors:
  - name: Mohd Afeef Badri
    orcid: 0000-0002-4646-8309
    affiliation: "1"
affiliations:
 - name: CEA  DES, Université Paris-Saclay, 91191, Gif-sur-Yvette, France
   index: 1
date: 3 July 2025
bibliography: paper.bib
---

# Summary

`PSD` (Parallel Solid/Structural/Seismic Dynamics) is an open-source finite element solver designed for high-performance computing applications in earthquake physics and structural dynamics. `PSD` addresses the computational challenges of large-scale seismic simulations by providing an integrated platform for analyzing complex structural and seismic dynamics problems in both two and three dimensions, with particular emphasis on fault-to-site analysis scenarios.

Built upon `FreeFEM`  [@MR3043640]  for finite element discretization and `PETSc` [@balay2019petsc] for scalable linear system solving, `PSD` integrates sophisticated material modeling through its dedicated  `Mfront` [@helfer2015],[@helfer2020] interface.   This architecture enables the handling of complex non-linear material behaviors and constitutive laws essential for realistic mechanical phenomena modeling.   `PSD` includes a purpose-built `MPI I/O`-based mesher-partitioner, `top-ii-vol` [@badri2024top], tailored for large-scale earthquake simulations. Further, there is implementation of hybrid phase-field fracture mechanics [@ambati2015review] enables detailed analysis of crack initiation and propagation in materials, these types of simulations are treated at other end of the complete simulation chain for earthquake simulations to structure assessment.

A distinguishing feature of `PSD` is its ability to handle large-scale earthquake simulations, particularly in fault-to-site analysis scenarios. This capability, combined with the solver's parallel architecture and advanced material modeling, makes it particularly suitable for comprehensive seismic risk assessment studies. The solver has demonstrated excellent scalability up to 24,000 cores, allowing it to tackle problems with over 5 billion unknowns, making it capable of resolving the multi-scale nature of seismic wave propagation from fault rupture to local site response.

# Statement of Need

Seismic hazard assessment and earthquake engineering require computational tools capable of simulating wave propagation across multiple spatial scales, from fault rupture (kilometers) to local site response (meters), while maintaining sufficient resolution for engineering applications. Existing commercial solutions often lack the computational scalability required for regional-scale earthquake simulations, while open-source alternatives typically address only specific aspects of the seismic simulation workflow.

Current computational challenges in earthquake simulation include: (1) the need for billion-scale degree-of-freedom problems to capture realistic fault-to-site scenarios [@hori2018application], (2) integration of complex material behaviors including fracture mechanics for damage assessment, and (3) efficient mesh generation and partitioning for irregular geological domains often constructed directly from digital elevation maps (DEM). While tools like `OpenSees`[@mckenna2011opensees] excel in structural analysis and `SPECFEM3D` [@Peter_Forward_and_adjoint_2011] addresses seismic wave propagation. It is of interest  to have an open-source solution with integrated platform addressing the complete fault-to-site simulation workflow with HPC scalability.

`PSD` tries to fills this gap by providing a unified computational framework that combines earthquake source modeling, wave propagation simulation, and structural damage assessment within a single scalable solver. The software's integration of advanced meshing capabilities (`top-ii-vol`), sophisticated material modeling (`Mfront` interface), and fracture mechanics positions it uniquely for comprehensive seismic risk assessment applications requiring both regional-scale wave propagation and local structural response analysis.

# Example Workflow for Earthquake

The following workflow demonstrates `PSD`'s approach to a fundamental earthquake simulation problem: seismic wave propagation in a three-dimensional soil domain with absorbing boundaries. This example illustrates the software's key capabilities including automated distributed mesh generation (combined meshing-partitioning), advanced time integration, and sophisticated boundary condition handling.

**Mathematical Presentation:** `PSD` solves the elastodynamic wave equation using finite element discretization with Newmark-β time integration. The implementation incorporates paraxial absorbing boundaries [@modaressi1994paraxial] to prevent artificial wave reflections, essential for realistic earthquake simulations.

For a 3D soil domain $\Omega \subset \mathbb{R}^3$ bounded by boundaries $\partial\Omega \subset \mathbb{R}^3$ and with paraxial absorbing boundaries $\partial \Omega_{\text{P}} \subset \partial \Omega$, the finite element variational formulation solved in `PSD` reads:

$$
\begin{aligned} &\text{Find}~\mathbf{u}\in \mathcal{V}~\text{such~that}~\forall~t\in[0,t_{\text{max}}], \forall\mathbf{v}\in \mathcal{V}:\\&  \int_{\Omega} \left( \frac{\rho}{\beta \Delta t^2}    \mathbf{u} \cdot \mathbf{v} + 
   \left( \boldsymbol{\sigma}(\mathbf{u}) : \boldsymbol{\varepsilon}(\mathbf{u}) \right)  \right) +    \int_{\partial\Omega_{\text{P}}}    \frac{\rho \gamma}{\beta \Delta t}    \left(\boldsymbol{\mathcal{P}} \mathbf{u} \right) \cdot \mathbf{v}  = \\  &
  \quad \quad\int_{\Omega} \frac{\rho}{\beta} \left( \frac{1}{\Delta t^2} \mathbf{u}_{\text{old}} \cdot \mathbf{v}  + \frac{1}{\Delta t} \dot{\mathbf{u}}_{\text{old}} \cdot \mathbf{v}  +  \left( \frac{1}{2} - \beta \right) \ddot{\mathbf{u}}_{\text{old}} \cdot \mathbf{v}\right) + \\  &  
 \quad \quad\int_{\partial\Omega_{\text{P}}}  \left(    \frac{\rho \gamma}{\beta \Delta t}   \left( \boldsymbol{\mathcal{P}} \mathbf{u}_{\text{old}}  \right)\cdot \mathbf{v} +    \left( \frac{\rho\gamma}{\beta} - \rho \right) \left( \boldsymbol{\mathcal{P}} \dot{\mathbf{u}}_{\text{old}}\right) \cdot \mathbf{v}  +    \left(  \frac{\rho \gamma \Delta t}{2\beta} -\rho \Delta t \right)\left( \boldsymbol{\mathcal{P}} \ddot{\mathbf{u}}_{\text{old}} \right) \cdot \mathbf{v}\right).     \end{aligned}
$$

Here:

- $(\mathbf{u}, \mathbf{v}) : \Omega \to \mathbb{R}^3$ are the finite element trial (unknown displacement) and test functions, respectively, in finite element space $\mathcal{V}$, both defined over the volumetric domain $\Omega$;

- $(\mathbf{u}_{\text{old}}, \dot{\mathbf{u}}_{\text{old}}, \ddot{\mathbf{u}}_{\text{old}}) : \Omega \to \mathbb{R}^3$ represent the previously computed displacement, velocity, and acceleration fields, respectively, defined over $\Omega$;

- $(\boldsymbol{\sigma}(\mathbf{u}), \boldsymbol{\varepsilon}(\mathbf{v})): \Omega \to \mathbb{R}^{3 \times 3}$ represent the Cauchy stress and strain tensors, respectively, both rank-2 tensor fields;

- $(\rho, \gamma, \beta, \Delta t) \in \mathbb{R}$ are scalar parameters corresponding to soil density ($\rho$) and Newmark-$\beta$ time discretization parameters;

- $\boldsymbol{\mathcal{P}} : \partial \Omega_{\text{P}} \to \mathbb{R}^{3 \times 3}$ is a direction-dependent impedance tensor enforcing paraxial absorbing boundary conditions on the boundary $\partial \Omega_{\text{P}}$. It is defined as

  
  $$
  \boldsymbol{\mathcal{P}} = c_{\text{p}}\, \mathbf{n} \otimes \mathbf{n} + c_{\text{s}} \left( \mathbf{I} - \mathbf{n} \otimes \mathbf{n} \right),
  $$

  ​	

  where, $\mathbf{n} : \partial \Omega_{\text{P}} \to \mathbb{R}^3$ is the outward unit normal vector on the boundary, $\mathbf{I} \in \mathbb{R}^{3 \times 3}$ is the identity tensor, $(c_{\text{p}}, c_{\text{s}} \in \mathbb{R})$ are scalar parameters corresponding to the P-wave and S-wave wave velocities in the soil.

Finally, seismic loading to the equation is applied via a double-couple source, where the seismic moment tensor $\mathbf{M}$ is constructed based on fault slip parameters such as the slip angle and rake. This moment tensor is discretized by imposing equivalent Dirichlet displacement conditions at four orthogonal points within the domain—representing the north, south, east, and west couples or more commonly known as double couple. Formally, for points $\{\mathbf{x}_i\}_{i=0}^4 \in \Omega$, the displacement boundary conditions are given by $\mathbf{u}(\mathbf{x}_i, t) = \mathbf{d}_i(t) = \mathbf{f}(\mathbf{M}, t),$ where $\mathbf{f}(\mathbf{M}, t)$ maps the moment tensor $\mathbf{M}$ and its time evolution into displacement time histories $\mathbf{d}_i(t)$ at each point, thus effectively reproducing the seismic moment release and the characteristic wave radiation pattern generated by fault slip.

The `PSD` workflow begins with automated code generation through the `PSD_PreProcess` utility, which generates problem-specific finite element code based on user specifications. This approach ensures computational efficiency while maintaining flexibility for different problem configurations.

Sample preprocessing command:
```
PSD_PreProcess -dimension 3 -problem soildynamics -timediscretization newmark_beta \
-useGFP -top2vol-meshing -postprocess uav
```

Material parameters are specified through ASCII configuration files, with typical values for soil properties including density and wave velocities corresponding to standard engineering geology classifications:
```
  real rho  = 1800.0 ,  // Density (kg/m³)
       cs   = 2300.  ,  // S-wave welocity (m/s)
       cp   = 4000.  ;  // P-wave welocity (m/s)
```

Time discretization parameters follow established earthquake engineering practices, with time steps chosen to satisfy numerical stability requirements for wave propagation:

```
  real tmax = 4.0     ,    // Total simulation time
       t    = 0.01    ,    // Initial time
       dt   = 0.01    ;    // Time step

  real gamma = 0.5                       ,
       beta  = (1./4.)*(gamma+0.5)^2     ;
```

The simulation is executed using the parallel solver with the specified number of `MPI` processes:

```
PSD_Solve -np 6144 Main.edp #6144 MPI-domains are used
```

Results such as those presented in figure \ref{fig:example1} can be obtained by launching `PSD` simulation. These results corresponds to seismic wave propagation for hypothetical earthquake. These simulations are then used for risk assessments of potential sites of interest for engineering. 

# Demonstration

Figure \ref{fig:example1} presents a regional-scale earthquake simulation of the Cadarache region (50 km × 50 km) performed with `PSD`, as detailed in [@badri2024top]. This simulation demonstrates `PSD`'s capability for large-scale seismic wave propagation modeling, involving over one billion degrees of freedom distributed across 6144 `MPI` domains. The displacement fields shown at four time intervals illustrate wave propagation patterns characteristic of earthquake scenarios, with computational complexity approaching operational seismic hazard assessment requirements.

 ![Regional-scale earthquake simulation of the Cadarache region (50 km × 50 km) demonstrating `PSD`'s capability for large-scale seismic wave propagation modeling. \label{fig:example1}](./images/earthquake.png){width=80%}

Figure \ref{fig:example2} demonstrates `PSD`'s fracture mechanics capabilities through a brittle fracture simulation within a perforated medium, as presented in [@badri2021preconditioning]. This simulation involves more than 64 million degrees of freedom solved across 1008 MPI domains on the French Joliot-Curie supercomputer, illustrating the software's capability for detailed damage assessment applications that complement regional-scale earthquake simulations.



![Crack propagation for a perforated medium, simulation performed with `PSD`.\label{fig:example2}](./images/fracture.png){width=80%}

These demonstrations represent significant computational achievements in earthquake simulation, with problem sizes approaching operational seismic hazard assessment requirements. The Cadarache region simulation scale demonstrates `PSD`'s applicability to real-world earthquake engineering problems, while the fracture mechanics example illustrates the software's capability for detailed damage assessment applications.

Additional applications demonstrate `PSD`'s versatility for advanced fracture mechanics research, including eikonal non-local gradient damage model implementations [@nogueira2023numerical],[@nogueira2024differential], which further extend the software's capabilities for comprehensive structural analysis applications.

# Documentation and Availability

`PSD` is distributed under the Apache License, Version 2.0, ensuring broad accessibility for research and educational applications. `PSD`'s repository at  https://github.com/mohd-afeef-badri/psd  includes comprehensive documentation covering cross-platform installation procedures (based on `Autotools`), usage examples, and validation test cases. Continuous integration testing, via GitHub Actions,  ensures software reliability across different computing environments, while the modular architecture facilitates community contributions and ongoing development.

# Acknowledgements

This work is supported by the French Alternative Energies and Atomic Energy Commission (CEA) via SIMU and SEISM projects under the GEN2&3 and PICI2 program funding. The authors thank TGCC, France for granting access to the Joliot-Curie supercomputer under the GENDEN quota. This research was initially funded by PTC HPCSEISM at CEA during the period 2018-2021.

# References
