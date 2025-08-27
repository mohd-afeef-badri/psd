---
title: '`PSD`: Parallel finite element Solver for continuum Dynamics'
tags:
  - finite elements
  - parallel computing
  - earthquake simulation
  - fracture mechanics
  - HPC
authors:
  - name: Mohd Afeef Badri
    orcid: 0000-0002-4646-8309
    corresponding: true
    affiliation: "1"
  - name: Giuseppe Rastiello
    orcid: 0000-0003-2970-6755
    affiliation: "2"
  - name: Evelyne Foerster
    orcid: 0000-0002-5222-2823
    affiliation: "3"
affiliations:
 - name: Université Paris-Saclay, CEA, Service de Génie Logiciel pour la Simulation (SGLS), 91191, Gif-sur-Yvette, France
   index: 1
 - name: Université Paris-Saclay, CEA,  Service d'Études Mécaniques et Thermiques (SEMT), 91191, Gif-sur-Yvette, France
   index: 2
 - name: Université Paris-Saclay, CEA,  Département de Modélisation des Systèmes et Structures (DM2S), 91191, Gif-sur-Yvette, France
   index: 3
date: 27 August 2025
bibliography: paper.bib
---

# Summary

`PSD` (Parallel finite element Solver for continuum Dynamics) is an open-source finite element solver designed for high-performance computing simulations in earthquake mechanics and structural dynamics. `PSD` addresses the computational challenges of large-scale seismic simulations by providing an integrated platform for analyzing complex structural and seismic dynamics problems in both two and three dimensions.

Built upon `FreeFEM`  [@MR3043640]  for finite element discretization and `PETSc` [@balay2019petsc] for scalable linear system solving, `PSD` integrates sophisticated material modeling through its dedicated  `Mfront` [@helfer2015],[@helfer2020] interface.   This architecture enables the handling of complex material behaviors thanks to non-linear constitutive laws essential for realistic mechanical phenomena modeling.   `PSD` includes a purpose-built `MPI I/O`-based mesher-partitioner, `top-ii-vol` [@badri2024top], tailored for large-scale earthquake simulations. Further, hybrid phase-field fracture mechanics [@ambati2015review] is implemented, which enables detailed analysis of crack initiation and propagation in materials. These types of simulations are treated at the other end of the complete simulation chain from the earthquake source to the structure assessment.

A distinguishing feature of `PSD` is its ability to handle large-scale earthquake simulations ($\mathcal{O}(10^9)$), particularly in fault-to-site analysis scenarios. This capability, combined with the solver's parallel architecture and advanced material modeling, makes it particularly suitable for comprehensive seismic risk assessment studies. The solver exhibits excellent scalability on tens of thousands of `MPI` processes, enabling simulations with billions of unknowns on large scale supercomputers. This allows it to accurately capture the multiscale features of seismic wave propagation and consequences—from fault to local site response.

# Statement of Need

Seismic risk assessment require computational tools capable of simulating wave propagation across multiple spatial scales, from fault (kilometers away) to local site response (meters), while ensuring sufficient accuracy for earthquake engineering analyses. Existing commercial solutions often lack the computational scalability required for integrated regional to local scale earthquake simulations, while open-source alternatives typically address only specific aspects of the seismic simulation workflow.

Current computational challenges in earthquake simulation include: (1) the need for billions of degrees-of-freedom to capture realistic fault-to-site scenarios [@hori2018application], [@cui2013physics] (2) integration of complex non-linear material behaviors and damage assessment (fracture propagation), and (3) efficient mesh generation and partitioning for irregular geological domains often constructed directly from digital elevation models. Tools like `OpenSees`[@mckenna2011opensees] excel in local site response analysis (soils and structures) based on the finite element method (FEM) and `SPECFEM3D` [@Peter_Forward_and_adjoint_2011] or `SEM3D` [@Fares2022sem3d] address seismic wave propagation using the spectral element method. However, it is of interest  to have an open-source integrated platform addressing the complete fault-to-site simulation workflow with HPC scalability.

`PSD` fills this gap by providing a unified computational framework that combines earthquake source modeling, wave propagation simulation, and structural damage assessment within a single scalable FEM solver.  `PDS`'s integration of advanced meshing-partitioning capabilities (`top-ii-vol`), sophisticated material modeling (`Mfront` interface), and fracture mechanics positions it uniquely for comprehensive seismic risk assessment needs requiring both regional-scale wave propagation and local site response including structural analysis.

# `PSD` Features and Architecture

`PSD` provides a comprehensive suite of physics modules addressing diverse computational mechanics applications around earthquake simulations. It includes dedicated modules for linear elasticity, elastodynamics, fracture mechanics, soildynamics [^soildynamics], and elasto-plasticity, making it suitable for applications ranging from static structural analysis to dynamic earthquake simulation and material damage assessment. The `Mfront` interface significantly enhances this versatility by enabling users to implement custom non-linear material models that can be integrated into any of these physics modules, extending `PSD`'s applicability beyond the built-in constitutive laws.

`PSD` adopts a layered architecture that separates mathematical formulation from computational implementation while maintaining high performance through strategic integration with `FreeFEM` for finite element discretization, `PETSc` for scalable linear algebra, and `Mfront` for sophisticated material modeling. `PSD` follows a code generation approach where users specify problem configurations through command-line options, and the software automatically generates optimized code tailored to specific physics, dimensionality, and boundary conditions. This design enables computational efficiency while preserving flexibility for diverse solid mechanics applications across the available physics modules.

The parallel computing architecture in `PSD` employs domain decomposition strategies which enable distribute memory parallelization which are optimized for large-scale FEM simulation [@dolean2015introduction]. `PSD` has demonstrated scalability up to 24,000 cores and capability for handling problems with over 5 billion unknowns for earthquakes. The integration with the `top-ii-vol` meshing tool provides efficient on the fly mesh generation and partitioning specifically designed for earthquake simulation geometries, eliminating traditional bottlenecks associated with sequential meshing approaches.

Each of `PSD` 's module undergoes comprehensive validation and verification testing to ensure numerical accuracy and reliability across its diverse physics modules. The validation framework includes cross-comparison with established numerical codes, comparison with experimental results, and verification against manufactured analytical solutions. Some of the validation results covering all physics modules are documented and publicly available at [https://mohd-afeef-badri.github.io/psd/validation](https://mohd-afeef-badri.github.io/psd/validation), providing users with confidence in the `PSD`'s accuracy for their specific applications.

[^soildynamics]: The *soildynamics* module builds upon the elastodynamics module by incorporating specialized tools essential for earthquake modeling, such as paraxial (absorbing) boundary conditions, double-couple source mechanisms, point-cloud meshing-partitioning algorithm, etc.

# Example Workflow for Earthquake Simulation in PSD

The following workflow demonstrates `PSD`'s soildynamic module through a fundamental earthquake simulation problem: seismic wave propagation in a three-dimensional soil domain with absorbing boundaries. This example illustrates one of `PSD`'s specialized physics modules among others, the aim here is to briefly illustrate `PSD`'s key capabilities including automated distributed mesh generation (combined meshing-partitioning), advanced time integration, and sophisticated boundary condition handling.

**Mathematical Presentation:** PSD solves the elastodynamic wave equation using finite element discretization with Newmark-$\beta$ time integration[^1]. The implementation incorporates paraxial absorbing boundaries [@modaressi1994paraxial] to prevent artificial wave reflections, essential for realistic earthquake simulations, and seismic source excitations with double-couple theory [@benz1987kinematic].

For a 3D soil domain $\Omega \subset \mathbb{R}^3$ bounded by boundaries $\partial\Omega \subset \mathbb{R}^3$ and with paraxial absorbing boundaries $\partial \Omega_{\text{P}} \subset \partial \Omega$, the finite element variational formulation solved in `PSD` reads:

$$
\begin{aligned} &\text{Find}~\mathbf{u}\in \mathcal{V}~\text{such~that}~\forall~t\in[0,t_{\text{max}}], \forall\mathbf{v}\in \mathcal{V}:\\&  \int_{\Omega} \left( \frac{\rho}{\beta \Delta t^2}    \mathbf{u} \cdot \mathbf{v} + 
   \left( \boldsymbol{\sigma}(\mathbf{u}) : \boldsymbol{\varepsilon}(\mathbf{v}) \right)  \right) +    \int_{\partial\Omega_{\text{P}}}    \frac{\rho \gamma}{\beta \Delta t}    \left(\boldsymbol{\mathcal{P}} \mathbf{u} \right) \cdot \mathbf{v}  = \\  &
  \quad \quad\int_{\Omega} \frac{\rho}{\beta} \left( \frac{1}{\Delta t^2} \mathbf{u}_{\text{old}} \cdot \mathbf{v}  + \frac{1}{\Delta t} \dot{\mathbf{u}}_{\text{old}} \cdot \mathbf{v}  +  \left( \frac{1}{2} - \beta \right) \ddot{\mathbf{u}}_{\text{old}} \cdot \mathbf{v}\right) + \\  &  
 \quad \quad\int_{\partial\Omega_{\text{P}}}  \left(    \frac{\rho \gamma}{\beta \Delta t}   \left( \boldsymbol{\mathcal{P}} \mathbf{u}_{\text{old}}  \right)\cdot \mathbf{v} +    \left( \frac{\rho\gamma}{\beta} - \rho \right) \left( \boldsymbol{\mathcal{P}} \dot{\mathbf{u}}_{\text{old}}\right) \cdot \mathbf{v}  +    \left(  \frac{\rho \gamma \Delta t}{2\beta} -\rho \Delta t \right)\left( \boldsymbol{\mathcal{P}} \ddot{\mathbf{u}}_{\text{old}} \right) \cdot \mathbf{v}\right).     \end{aligned}
$$

Here:

- $(\mathbf{u}, \mathbf{v}) : \Omega \to \mathbb{R}^3$ are the finite element trial (unknown displacement) and test functions, respectively, in finite element space $\mathcal{V}$ (linear closed subspace of $[H^1(\Omega)]^3$), both defined over the volumetric domain $\Omega$;

- $(\mathbf{u}_{\text{old}}, \dot{\mathbf{u}}_{\text{old}}, \ddot{\mathbf{u}}_{\text{old}}) : \Omega \to \mathbb{R}^3$ represent respectively the displacement, velocity, and acceleration fields computed at previous time step and defined over $\Omega$;

- $(\boldsymbol{\sigma}(\mathbf{u}), \boldsymbol{\varepsilon}(\mathbf{v})): \Omega \to \mathbb{R}^{3 \times 3}$ represent the Cauchy stress and strain tensors, respectively, both rank-2 tensor fields;

- $(\rho, \gamma, \beta, t, t_{\text{max}}, \Delta t) \in \mathbb{R}$ are scalar parameters corresponding to soil density ($\rho$),  Newmark-$\beta$ time discretization parameters ($\gamma,\beta$), and time variables ($t,t_{\max},\Delta t$);

- $\boldsymbol{\mathcal{P}} : \partial \Omega_{\text{P}} \to \mathbb{R}^{3 \times 3}$ is a direction-dependent impedance tensor enforcing paraxial absorbing boundary conditions on the boundary $\partial \Omega_{\text{P}}$. It is defined as

  $$
  \boldsymbol{\mathcal{P}} = c_{\text{p}}\, \mathbf{n} \otimes \mathbf{n} + c_{\text{s}} \left( \mathbf{I} - \mathbf{n} \otimes \mathbf{n} \right),
  $$

  where, $\mathbf{n} : \partial \Omega_{\text{P}} \to \mathbb{R}^3$ is the outward unit normal vector on the boundary, $\mathbf{I} \in \mathbb{R}^{3 \times 3}$ is the identity $2^{nd}$-order tensor, $(c_{\text{p}}, c_{\text{s}} \in \mathbb{R})$ are scalar parameters corresponding to the P-wave and S-wave wave velocities in the soil.

Finally, seismic excitation is applied via a double-couple point source, where the seismic moment tensor $\mathbf{M}$ is obtained from on common seismic source features (fault dip, rake and strike). This moment tensor is applied by imposing equivalent displacements (e.g., Dirichlet conditions) at four points located to the north, south, east and west from the source point within the domain $\Omega$. Formally, for points $\{\mathbf{x}_i\}_{i=0}^4 \in \Omega$, the imposed displacement conditions are given by $\mathbf{u}(\mathbf{x}_i, t) = \mathbf{d}_i(t) = \mathbf{f}(\mathbf{M}, t),$ where $\mathbf{f}(\mathbf{M}, t)$ maps the moment tensor $\mathbf{M}$ and its time evolution into displacement time histories $\mathbf{d}_i(t)$ at each point, thus effectively reproducing the seismic moment release and the characteristic wave radiation pattern generated by fault slip.

**Workflow**: The `PSD` workflow begins with automated code generation through the `PSD_PreProcess` utility, which generates problem-specific finite element code based on user specifications. This approach ensures computational efficiency while maintaining flexibility for different problem configurations.

Sample preprocessing command:

```
PSD_PreProcess -problem soildynamics -dimension 3 -top2vol-meshing \
-timediscretization newmark_beta  -postprocess uav
```

Material parameters are then specified through `ASCII` configuration file, with typical values for soil properties including density and wave velocities corresponding to standard engineering geology classifications:

```
  real rho  = 1800.0 ,  // Density (kg/m³)
       cs   = 2300.0 ,  // S-wave velocity (m/s)
       cp   = 4000.0 ;  // P-wave velocity (m/s)
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

Results such as those presented in Figure \ref{fig:example1} can be obtained by launching `PSD` simulation. These results corresponds to seismic wave propagation for hypothetical earthquake. These simulations are then used for risk assessments of potential sites of interest for engineering.

# Demonstration

Figure \ref{fig:example1} presents a regional-scale earthquake simulation of the French Cadarache region (50 km × 50 km) performed with `PSD`, as detailed in [@badri2024top]. This simulation demonstrates `PSD`'s capability for large-scale seismic wave propagation modeling, involving over one billion degrees of freedom distributed across 6144 `MPI` domains. The displacement fields shown at four time intervals illustrate wave propagation patterns characteristic of earthquake scenarios, with computational complexity approaching operational seismic hazard assessment requirements.

 ![Regional-scale earthquake simulation of the French Cadarache region (50 km × 50 km) demonstrating `PSD`'s capability for large-scale seismic wave propagation modeling. \label{fig:example1}](./images/earthquake.png){width=80%}

Figure \ref{fig:example2} demonstrates `PSD`'s fracture mechanics capabilities through a brittle fracture simulation within a perforated medium, as presented in [@badri2021preconditioning]. This simulation involves more than 64 million degrees of freedom solved across 1008 MPI domains on the French Joliot-Curie supercomputer, illustrating the software's capability for detailed damage assessment applications that complement regional-scale earthquake simulations.

![Crack propagation for a perforated medium, simulation performed with `PSD`.\label{fig:example2}](./images/fracture.png){width=80%}

These demonstrations represent significant computational achievements in earthquake simulation, with problem sizes nearing those required for operational seismic hazard and risk assessment. The simulation of the Cadarache region in France demonstrates `PSD`'s applicability to real-world earthquake engineering problems, while the fracture mechanics example illustrates the software's capability for detailed damage assessment applications.

Additional applications demonstrate `PSD`'s versatility for advanced fracture mechanics research, including eikonal non-local gradient damage model implementations [@nogueira2023numerical],[@nogueira2024differential], which further extend the software's capabilities for comprehensive structural analysis.

# Documentation and Availability

`PSD` is distributed under the Apache License, Version 2.0, ensuring broad accessibility for research and educational applications. `PSD`'s repository at  [https://github.com/mohd-afeef-badri/psd](https://github.com/mohd-afeef-badri/psd)  includes comprehensive documentation covering cross-platform installation procedures (based on `Autotools`), usage examples, and validation test cases. Continuous integration testing, via GitHub Actions,  ensures software reliability across different computing environments, while the modular architecture facilitates community contributions and ongoing development.

# Acknowledgements

This work is supported by the French Alternative Energies and Atomic Energy Commission (CEA) through the GEN2&3 program funding. The authors gratefully acknowledge TGCC, France, for providing access to the Joliot-Curie supercomputer under the GENDEN computing quota. This research was initially funded by the PTC HPCSEISM program at CEA during the 2018–2021 period.

The authors also acknowledge key contributors to the PSD solver: Dr. Breno Ribeiro Nogueira for his Ph.D. work on the fracture mechanics module via the `MFront` interface, Dr. Reine Fares for integrating Iwan non-linear soil behavior model via the `Mfront` interface, and Rania Saadi for enabling the parallel mesh adaptation kernel.

# References

[^1]: PSD implements the generalized-$\alpha$  time discretization method [@Chung], which encompasses several classical time integration schemes as special cases depending on the parameter selection: central difference, HHT (Hilber-Hughes-Taylor) [@hilber1977improved], and Newmark-$\beta$ methods.
