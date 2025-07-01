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

PSD (Parallel Solid/Structural/Seismic Dynamics) is an open-source finite elements-based solid mechanics solver designed for High Performance Computing (HPC) simulations. The software provides capabilities for analyzing complex structural and seismic dynamics problems in both two and three dimensions. PSD supports both parallel and sequential computation modes, making it versatile for various computational requirements and resource availability. Through its PSD-MFRONT interface, the solver handles sophisticated non-linear material behaviors and constitutive laws, essential for realistic modeling of complex mechanical phenomena. The implementation of hybrid phase-field fracture mechanics enables detailed analysis of crack initiation and propagation in materials.

A distinguishing feature of PSD is its ability to handle large-scale earthquake simulations, particularly in fault-to-site analysis scenarios. This capability, combined with the solver's parallel architecture and advanced material modeling, makes it particularly suitable for comprehensive seismic risk assessment studies. The solver has demonstrated excellent scalability up to 24,000 cores, allowing it to tackle problems with over 5 billion unknowns, making it capable of resolving the multi-scale nature of seismic wave propagation from fault rupture to local site response.

# Statement of Need

Modern engineering challenges in structural and seismic analysis require sophisticated computational tools that can handle complex geometries and large-scale simulations efficiently. While several commercial solutions exist, there is a pressing need for open-source alternatives that can leverage high-performance computing resources while maintaining accessibility and flexibility. PSD addresses this need by providing:

- A robust finite element implementation for solid mechanics problems
- Support for both 2D and 3D unstructured meshes
- Parallel computing capabilities through PETSc integration
- A sequential solver option for smaller scale problems
- Compatibility with standard mesh formats (MEDIT)

# Implementation

PSD is implemented with a focus on computational efficiency and scalability. The software architecture separates the core finite element implementation from the parallel computing infrastructure, allowing for maintainable code and flexible deployment options. The parallel implementation leverages PETSc (Portable, Extensible Toolkit for Scientific Computation) for efficient distributed memory parallelization.

# Example Workflow overview

PSD enables the simulation of complex seismic wave propagation problems through a systematic workflow that combines efficient mesh handling, advanced time integration schemes, and sophisticated boundary conditions. Here, we present a typical workflow for simulating seismic wave propagation in soil medium with paraxial (absorbing) boundaries.

## Problem Description
Consider a two-dimensional soil domain $\Omega$ with paraxial absorbing boundaries on the left, right, and bottom edges. The governing equations for elastic wave propagation in the frequency domain are:

$$
\rho \frac{\partial^2 \mathbf{u}}{\partial t^2} = \nabla \cdot \boldsymbol{\sigma} + \mathbf{f} \quad \text{in } \Omega \times (0,T]
$$

where $\rho$ is the material density, $\mathbf{u}$ is the displacement field, $\boldsymbol{\sigma}$ is the Cauchy stress tensor, and $\mathbf{f}$ represents body forces. The constitutive relation for linear elastic material is:

$$
\boldsymbol{\sigma} = \lambda \text{tr}(\boldsymbol{\epsilon})\mathbf{I} + 2\mu\boldsymbol{\epsilon}
$$

with Lamé parameters $\lambda$ and $\mu$, and the strain tensor $\boldsymbol{\epsilon} = \frac{1}{2}(\nabla\mathbf{u} + \nabla\mathbf{u}^T)$.

## Paraxial Boundary Conditions
At the absorbing boundaries $\Gamma_P$, we implement paraxial elements to minimize wave reflections:

$$
\boldsymbol{\sigma} \cdot \mathbf{n} = \rho c_p(\mathbf{n} \otimes \mathbf{n})\frac{\partial \mathbf{u}}{\partial t} + \rho c_s(\mathbf{I} - \mathbf{n} \otimes \mathbf{n})\frac{\partial \mathbf{u}}{\partial t} \quad \text{on } \Gamma_P
$$

where $c_p$ and $c_s$ are the P-wave and S-wave velocities respectively, and $\mathbf{n}$ is the outward normal vector.

## Discretization and Solution Process

1. **Mesh Generation**:
   - Input: Geometry parameters and mesh refinement criteria
   - Supported formats: MEDIT (.mesh), Gmsh (.msh), SALOME (.med)
   - Output: Unstructured triangular (2D) or tetrahedral (3D) mesh

2. **Material Parameters**:
   For a typical soil medium:
   ```cpp
   real rho     = 2500.0;  // Density (kg/m³)
   real E       = 6.62e6;  // Young's modulus (Pa)
   real nu      = 0.45;    // Poisson's ratio
   real mu      = E/(2.*(1.+nu));
   real lambda  = E*nu/((1.+nu)*(1.-2.*nu));
   ```

3. **Time Integration**:
   Using the Newmark-β method with parameters:
   ```cpp
   real tmax  = 4.0;    // Total simulation time
   real dt    = 0.01;   // Time step
   real gamma = 0.5;    // Newmark parameter
   real beta  = 0.25;   // Newmark parameter
   ```

4. **Assembly and Solution**:
   - Mass matrix $\mathbf{M}$
   - Stiffness matrix $\mathbf{K}$
   - Damping matrix $\mathbf{C}$ for paraxial boundaries
   - Solution of the system at each time step:
     $$
     \mathbf{M}\ddot{\mathbf{u}} + \mathbf{C}\dot{\mathbf{u}} + \mathbf{K}\mathbf{u} = \mathbf{F}
     $$

5. **Post-processing**:
   - Output formats: .pvd, .vtu, .pvtu (ParaView)
   - Visualization of displacement, velocity, and acceleration fields
   - ASCII output for time history data

This workflow has been successfully applied to various earthquake engineering problems, from site response analysis to fault-rupture simulations, demonstrating PSD's capability in handling complex seismic wave propagation scenarios.



# Applications in Research


The software has been successfully applied to various problems in solid mechanics and structural dynamics, it has lead to following puublications:
- [@badri2024top]

# Demonstration

Figure 1 shows the fracture mechanics problem of brittle fracture in case of a porus medium @@. More than 80 Million DOF are solved for this problem on 5000 cores of French Joliot-Curie Cluster. 

Figure 2 shows a hypotheical earthquake simulation of Cararach region, performed with PSD. Here a billion DOF problem is solved wile using 24,000 MPI domains. 

Figure 3 shows fracture via isotropic and anisotropic eikonal non-local gradient (ENLG) damage models devloped.... 

# Documentation and Availability

PSD is openly available on GitHub at https://github.com/mohd-afeef-badri/psd under the Apache License, Version 2.0. The software includes documentation covering installation, usage, and example problems. The code is released under an open-source license to encourage community participation and further development.



# Acknowledgements

We acknowledge contributions......

# References

..................
