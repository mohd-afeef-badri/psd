---
title: '`PSD`: Parallel Finite Element Solver for Continuum Dynamics'
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

`PSD` (Parallel finite element Solver for continuum Dynamics) is an open-source finite element method (FEM) solver designed for high-performance computing simulations in continuum dynamics with a special focus on earthquake mechanics. It enables integrated fault-to-site seismic simulations by combining advanced material modeling, scalable parallelism, and purpose-built meshing-partitioning tools.

Built on `FreeFEM` [@MR3043640] for FEM discretization and `PETSc` [@balay2019petsc] for scalable linear solvers, `PSD` integrates non-linear material modeling through its `MFront` [@helfer2015] interface for realistic simulations. Its custom `MPI I/O`-based mesher–partitioner, `top-ii-vol` [@badri2024top], enables efficient on-the-fly mesh generation and partitioning for earthquake geometries, removing sequential meshing bottlenecks. On the structural side, hybrid phase-field fracture mechanics [@ambati2015review] for crack analysis is implemented. This spans the full simulation chain from earthquake source to structural assessment.

A key feature of `PSD` is its ability to perform fault-to-site earthquake simulations with billions of degrees of freedom, scaling efficiently on tens of thousands of `MPI`-processes, making it suitable for comprehensive seismic risk assessment.

# Statement of Need

Seismic risk assessment requires tools that can simulate wave propagation across multiple scales, from faults (kilometers away) to local site response (meters), with sufficient accuracy. Commercial software often lacks the scalability needed for regional simulations, while open-source alternatives typically focus on specific parts of the seismic workflow.

Current computational challenges in earthquake simulation include: (1) handling billions of degrees-of-freedom to capture realistic fault-to-site scenarios [@hori2018application],[@cui2013physics], (2) integrating complex non-linear material behaviors and damage assessment for solids and structures, and (3) efficiently generating and partitioning large meshes for irregular geological domains derived from digital elevation models. FEM tools like `OpenSees`[@mckenna2011opensees] excel in local-site response, while `SPECFEM3D` [@Peter_Forward_and_adjoint_2011] and `SEM3D` [@touhami2022sem3d] address wave propagation using spectral elements. An open-source platform covering the full fault-to-site workflow with HPC scalability remains highly desirable.

`PSD` tries to fill this gap by providing a unified framework that combines earthquake wave propagation simulation and structural mechanics assessment  within a single scalable FEM solver.  `PDS`'s integration of advanced meshing-partitioning capabilities, sophisticated material modeling, and fracture mechanics positions it uniquely for comprehensive seismic risk assessment needs requiring both regional-scale wave propagation and local site response, including structural analysis.

# Features and Architecture

`PSD` offers a range of physics modules designed for earthquake simulations, including linear elasticity, elastodynamics, fracture mechanics, soildynamics [^soildynamics], and elasto-plasticity. Its versatility is further enhanced by the `Mfront` interface, which allows users to implement custom non-linear material models, that can be seamlessly integrated into any of these modules expanding their capabilities beyond its built-in constitutive laws. Additionally, comprehensive verification and validation campaigns for all `PSD` modules, with results cross-compared against reference codes, experimental data, and analytical benchmarks, ensuring transparency and reproducibility (see [validation page](https://mohd-afeef-badri.github.io/psd/validation)).

`PSD` adopts a layered architecture that separates mathematical formulation from computational implementation while maintaining high performance through strategic integration. It follows a code generation approach where users specify problem configurations through command-line options, and the it automatically generates optimized code tailored to specific physics, dimensionality, and boundary conditions. This design enables computational efficiency while preserving flexibility for diverse applications across the available physics modules.

The parallel computing architecture in `PSD` employs domain decomposition strategies that enable distributed memory parallelization which are optimized for large-scale FEM simulation [@dolean2015introduction]. `PSD` has demonstrated scalability up to 24,000 cores and capability for handling problems with over 5 billion unknowns for earthquakes. 

[^soildynamics]: The *soildynamics* module builds upon the *elastodynamics* module by adding tools essential for earthquake modeling, such as paraxial boundary conditions, double-couple source mechanisms, point-cloud meshing-partitioning, etc.

# Example Workflow

A representative application illustrates `PSD`'s soildynamics module for 3D wave propagation in an elastic domain with paraxial absorbing boundaries [@modaressi1994paraxial] and double-couple point sources [@benz1987kinematic]. This example illustrates one of `PSD`'s specialized physics modules, among others. The aim here is to briefly illustrate `PSD`'s key capabilities, including automated distributed mesh generation, advanced time integration, and sophisticated boundary condition handling.

**Mathematical Presentation:** `PSD` solves the elastodynamic wave equation using FEM discretization with Newmark-$\beta$ time integration. For a domain $\Omega \subset \mathbb{R}^3$ and with paraxial absorbing boundaries $\partial \Omega_{\text{P}} \subset \partial \Omega$, the FEM weak form reads:
$$
\begin{aligned} &\text{Find}~\mathbf{u}\in \mathcal{U}~\text{such~that}~\forall~t\in[0,t_{\text{max}}], \forall\mathbf{v}\in \mathcal{V}:\\&  \int_{\Omega} \left( \frac{\rho}{\beta \Delta t^2}    \mathbf{u} \cdot \mathbf{v} + 
    \boldsymbol{\sigma}(\mathbf{u}) : \boldsymbol{\varepsilon}(\mathbf{v}) \right) +    \int_{\partial\Omega_{\text{P}}}    \frac{\rho \gamma}{\beta \Delta t}    \mathbf{u} \cdot \boldsymbol{\mathbf{P}} \cdot \mathbf{v}  = \\  &
  \quad \quad\int_{\Omega} \frac{\rho}{\beta} \left( \frac{1}{\Delta t^2} \mathbf{u}_{\text{old}} \cdot \mathbf{v}  + \frac{1}{\Delta t} \dot{\mathbf{u}}_{\text{old}} \cdot \mathbf{v}  +  \left( \frac{1}{2} - \beta \right) \ddot{\mathbf{u}}_{\text{old}} \cdot \mathbf{v}\right) + \\  &  
 \quad \quad\int_{\partial\Omega_{\text{P}}}  \left(    \frac{\rho \gamma}{\beta \Delta t}    \mathbf{u}_{\text{old}} \cdot \boldsymbol{\mathbf{P}} \cdot \mathbf{v} +    \left( \frac{\rho\gamma}{\beta} - \rho \right) \dot{\mathbf{u}}_{\text{old}} \cdot \boldsymbol{\mathbf{P}}  \cdot \mathbf{v}  +    \left(  \frac{\rho \gamma \Delta t}{2\beta} -\rho \Delta t \right) \ddot{\mathbf{u}}_{\text{old}} \cdot \boldsymbol{\mathbf{P}}  \cdot \mathbf{v}\right).     \end{aligned}
$$

Here, $(\mathbf{u}, \mathbf{v})$ are the FEM trial and test functions, respectively, defined in FEM linear closed space. $(\mathcal{U},\mathcal{V})$ defined in $\left[H^1(\Omega)\right]^3$, for further details see `PSD`'s soildynamics [documentation](https://mohd-afeef-badri.github.io/psd/#/soildynamics).

**Execution Workflow**: `PSD` begins with automated code generation through the `PSD_PreProcess` utility, which generates problem-specific FEM code based on user specifications.

```
PSD_PreProcess -problem soildynamics -dimension 3 -top2vol-meshing \
-timediscretization newmark_beta  -postprocess uav
```

Typical soil properties and time-integration parameters are included:
```
  real rho  = 1800.0 ,  // Density
       cs   = 2300.0 ,  // S-wave velocity
       cp   = 4000.0 ;  // P-wave velocity

  real tmax = 20.0    ,  // Total time
       t    = 0.001   ,  // Initial time
       dt   = 0.001   ;  // Time step
```

The simulation is executed using the parallel solver with the specified number of `MPI`-processes:

```
PSD_Solve -np 6144 Main.edp
```

Results such as those presented in Figure \ref{fig:example1} can be obtained.

# Demonstration

Figure \ref{fig:example1} presents a regional-scale earthquake simulation of the Cadarache region in France (50 km × 50 km) performed with `PSD` [@badri2024top], comprising over one billion degrees of freedom distributed across 6144 `MPI`-domains on a 540-million-element mesh with 10 m resolution.

 ![Earthquake simulation of the French Cadarache region showing displacement magnitude at four time steps. \label{fig:example1}](./images/earthquake.png){width=72%}

Figure \ref{fig:example2} demonstrates fracture mechanics capabilities through quasi-static brittle fracture simulation in a perforated medium [@badri2021preconditioning], involving more than 64 million degrees of freedom across 1008 `MPI`-domains, illustrating detailed damage assessment capabilities.

![Crack propagation for a perforated medium.\label{fig:example2}](./images/fracture.png){width=72%}

These demonstrations represent significant computational achievements, with problem sizes approaching those required for seismic hazard and risk assessment. The Cadarache region simulation underscores `PSD`'s applicability to real-world earthquake engineering, while the fracture mechanics case illustrates its capability for detailed damage analysis. Further applications, including eikonal non-local gradient damage models [@nogueira2023numerical],[@nogueira2024eikonal], highlight `PSD`'s versatility and its potential for comprehensive structural and fracture mechanics research.

# Acknowledgements

This work is supported by the French Alternative Energies and Atomic Energy Commission (CEA) through the GEN2&3 program. G. Rastiello was also supported by the SEISM Institute (France). The authors thank Dr. Breno Ribeiro Nogueira for advanced fracture module, Dr. Reine Fares for nonlinear soil modeling, and Rania Saadi for the parallel mesh adaptation kernel.

# References
