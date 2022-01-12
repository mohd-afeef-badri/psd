## PSD todo list:



**Ongoing**
- Raw string support for hpp files
- Mfront integration of PSD (non-linear)
- Include Medfile support



**Todo**

- Optimize interpolation via building of interpolation matrix

-  Hujeux soil law make it work with PSD
-  Nonlinear damage mechanics with nested matrices 

-  To add examples for -pointprobe flag in make check
-  make check examples for time-discretization
-  Optimize force calculation (matrix-vector type)
-  Druker-Prager law for soil dynamics
-  Couple damage and seismic solver
-  Heterogeneous materials class of problems
-  Parallel interpolation on surface from volume





**Done**

- Mfront integration of PSD (non-linear)

- PSD configures PETSc and FreeFEM

- Mfront integration of PSD  linear-elasticity

- Use max system procs for tests
- Activate top-ii-vol version 1.3 for PSD

-  Install binaries and libraries in usr/bin and usr/include/psd
-  seperate precracked dirichlet flag

-  mesh flag for PSD_Solve
-  Distributed meshing interface for soil dynamics with top-ii-vol
-  Extract point field in MPI
-  Force calculation via matrix vector product
-  Fully commented control parameters file
-  Including material properties as macros not real type
-  Quadrature point based stress, strain variables  
-  Higher order quadrature formulations
-  Better way to include Dirichlet via macro table
-  Pseudo nonlinear procedure for solving linear problems with Newton-Raphsons
-  Hujeux soil law make it work with C++ 11
-  Strain Vectorization
-  Split & clearing done in Hujeux law
-  Newton--Raphsons for dynamics and phase-field
-  Introduce non-linearity for dynamics
-  GFP single function for Energy decomposition
-  Material tensor of damage problems
-  Tag Modification
-  Dynamic solver via $\varepsilon(u):A:\varepsilon(v)$
-  New variational formulations $\varepsilon(u):A:\varepsilon(v)$ instead of $\sigma(u): \varepsilon (v)$
-  2D/3D Quasistatic damage via GFP 
	- Idea is to take  Bruno/Giuseppe's serial solver and  parallelize the solver.
	- As EigenValue analysis of each element is required to get the principal directions there is a need to implement c++ GFP macros. 
-  Update testing in Make check
-  Better ParaView export for transient.

