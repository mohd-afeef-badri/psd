---
title: 'PSD: A Parallel Finite Element Solver for Solid/Structural/Seismic Dynamics'
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
date: 1 July 2025
bibliography: paper.bib
---

# Summary

PSD (Parallel Solid/Structural/Seismic Dynamics) is an open-source finite elements-based solver designed for High Performance Computing (HPC) targeting earthquake physics and simulations around. The focus is on high-fidelity simulations,   PSD provides capabilities for analyzing complex structural and seismic dynamics problems in both two and three dimensions. Since these simulations are provided under one roof, this facilitates multi-physics couplings between these equations.

PSD is built on top of FreeFEM  [@MR3043640] and PETSc [@balay2019petsc], which form its finite element backend and linear system solving backend, respectively. Additionally, PSD has dedicated  interface with Mfront [@helfer2015],[@helfer2020]  via which, the solver handles sophisticated non-linear material behaviors and constitutive laws, essential for realistic modeling of complex mechanical phenomena.  PSD has a dedicated combined  mesher-partitioner —top-ii-vol [@badri2024top]— for earthquake problems based on MPI I/O. Further, there is implementation of hybrid phase-field fracture mechanics [@ambati2015review] enables detailed analysis of crack initiation and propagation in materials, these types of simulations are treated at other end of the complete simulation chain for earthquake simulations to structure assessment.

A distinguishing feature of PSD is its ability to handle large-scale earthquake simulations, particularly in fault-to-site analysis scenarios. This capability, combined with the solver's parallel architecture and advanced material modeling, makes it particularly suitable for comprehensive seismic risk assessment studies. The solver has demonstrated excellent scalability up to 24,000 cores, allowing it to tackle problems with over 5 billion unknowns, making it capable of resolving the multi-scale nature of seismic wave propagation from fault rupture to local site response.

# Statement of Need

Modern engineering challenges in structural and seismic analysis require sophisticated computational tools that can handle complex geometries and large-scale simulations efficiently. While several commercial solutions exist, there is a pressing need for open-source alternatives that can leverage high-performance computing resources while maintaining accessibility and flexibility.

PSD is implemented with a focus on computational efficiency and scalability. The software architecture separates the core finite element implementation from the parallel computing infrastructure, allowing for maintainable code and flexible deployment options.

# Example Workflow for Earthquake

PSD enables the simulation of complex seismic wave propagation problems through a systematic workflow that combines efficient mesh-partitioning  handling, advanced time integration schemes, and sophisticated boundary conditions. Here, we present a typical workflow for simulating seismic wave propagation in soil medium with paraxial (absorbing) boundaries.

For a three-dimensional soil domain $\Omega \subset \mathbb{R}^3$ bounded by boundaries $\partial\Omega \subset \mathbb{R}^3$ and with paraxial absorbing boundaries $\partial \Omega_{\text{P}} \subset \partial \Omega$, the finite element variational formulation solved in PSD reads:

$$
\begin{aligned} &\text{Find}~\mathbf{u}\in \mathcal{V}~\text{such~that}~\forall~t\in[0,t_{\text{max}}]:\\&  \int_{\Omega} \left( \frac{\rho}{\beta \Delta t^2}    \mathbf{u} \cdot \mathbf{v} + 
   \left( \boldsymbol{\sigma}(\mathbf{u}) : \boldsymbol{\varepsilon}(\mathbf{u}) \right)  \right) +    \int_{\partial\Omega_{\text{P}}}    \frac{\rho \gamma}{\beta \Delta t}    \left(\boldsymbol{\mathcal{P}} \mathbf{u} \right) \cdot \mathbf{v}  = \\  &
  \quad \quad\int_{\Omega} \frac{\rho}{\beta} \left( \frac{1}{\Delta t^2} \mathbf{u}_{\text{old}} \cdot \mathbf{v}  + \frac{1}{\Delta t} \dot{\mathbf{u}}_{\text{old}} \cdot \mathbf{v}  +  \left( \frac{1}{2} - \beta \right) \ddot{\mathbf{u}}_{\text{old}} \cdot \mathbf{v}\right) + \\  &  
 \quad \quad\int_{\partial\Omega_{\text{P}}}  \left(    \frac{\rho \gamma}{\beta \Delta t}   \left( \boldsymbol{\mathcal{P}} \mathbf{u}_{\text{old}}  \right)\cdot \mathbf{v} +    \left( \frac{\rho\gamma}{\beta} - \rho \right) \left( \boldsymbol{\mathcal{P}} \dot{\mathbf{u}}_{\text{old}}\right) \cdot \mathbf{v}  +    \left(  \frac{\rho \gamma \Delta t}{2\beta} -\rho \Delta t \right)\left( \boldsymbol{\mathcal{P}} \ddot{\mathbf{u}}_{\text{old}} \right) \cdot \mathbf{v}\right)\quad\forall\mathbf{v}\in \mathcal{V}.     \end{aligned}
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

A key achievement here is that such a simulation starts in PSD by inputting the DEM point-cloud, and PSD via top-ii-vol plugin builds distributed mesh which combines meshing-partitioning step. This is a key advantage, as in earthquakes meshing and partitioning  forms a bottle next as meshes with $\mathcal{O}(10^9)$ are needed to be build and partitioned which is not a trivial task.

A PSD simulation starts by automatic code generation, via `PSD_Preprocess`, for instance for earthquake simulation the following needs to be launched
```
PSD_PreProcess -dimension 3 -problem soildynamics -timediscretization newmark_beta \
-useGFP -top2vol-meshing -postprocess uav
```

Next parameters are setup in the ASCII files, for instance the material and time-discretization paramters: 
```
//============================================================================
//                   ------- Soil parameters -------
// -------------------------------------------------------------------
//  rho : density of soil
//  cp, cs : Primary and secondary wave velocities
//============================================================================
  real rho  = 1800.0 ,  // Density (kg/m³)
       cs   = 2300.  ,  // S-wave welocity (m/s)
       cp   = 4000.  ;  // P-wave welocity (m/s)
```

```
//============================================================================
//           ------- Time discretization parameters -------
// -------------------------------------------------------------------
//  t, tmax, dt : Time parameters, time, maximum time, and time step
//  gamma, beta : Time discretization constants (Newmark-beta)
//============================================================================

  real tmax = 4.0     ,    // Total simulation time
       t    = 0.01    ,    // Initial time
       dt   = 0.01    ;    // Time step

  real gamma = 0.5                       ,
       beta  = (1./4.)*(gamma+0.5)^2     ;
```

Once done, the solver is launched, for instance with 8 MPI processes.

```
PSD_Solve -np 8 Main.edp
```

Results such as those presented in figure \ref{fig:example1} can be obtained by launching PSD simulation. These results corresponds to seismic wave propagation for hypothetical earthquake. These simulations are then used for risk assessments of potential sites of interest for engineering. 

# Applications in Research


The software has been successfully applied to various problems in solid mechanics and structural dynamics, it has lead to following publications:
- [@badri2024top]
- [@badri2021preconditioning]

# Demonstration

Figure \ref{fig:example1} shows a hypothetical earthquake simulation of Cadarache region (50 Km $\times$ 50 Km), performed with PSD, presented in [@badri2024top]. Here more than one billion DOF problem is solved wile using 6144 MPI domains.

 ![regional-scale earthquake simulation of Cadarache region in France. The FEM displacement field is shown for four different times starting from top left.\label{fig:example1}](./images/earthquake.png)

Figure \ref{fig:example2} shows a fracture mechanics problem of brittle fracture  within a perforated medium performed with PDS as presented in [@badri2021preconditioning]. For this simulation, more than 64 Million DOF are solved for this problem on 1008 MPI domains of French Joliot-Curie supercomputer. 



![crack propagation for a perforated medium.\label{fig:example2}](./images/fracture.png)

# Documentation and Availability

PSD is released under an open-source license to encourage community participation and further development.  It is available on  GitHub at https://github.com/mohd-afeef-badri/psd under the Apache License, Version 2.0, with automatic CI for testing. The solver includes documentation covering installation, usage, and example problems.

# Acknowledgements

We acknowledge contributions......



