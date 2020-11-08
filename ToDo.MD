## PSD todo list:




**Ongoing**
-  mesh flag for PSD_Solve
-  Install binaries and libraries in usr/bin and usr/include/psd
-  Hujeux soil law make it work with PSD
-  Nonlinear damage mechanics with nested matrices 



**Todo**

-  To add examples for -mesh flag in make check

-  Probe flag for probing field values
-  make check examples for time-discretization
-  Optimize force calculation (matrix-vector type)
-  Druker-Prager law for soil dynamics
-  Couple damage and seismic solver
-  Heterogeneous materials class of problems
-  Parallel interpolation on surface from volume






**Done**
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
-  Dynamic solver via $\epsilon(u):A:\epsilon(v)$
-  New variational formulations $\epsilon(u):A:\epsilon(v)$ instead of $\sigma(u):\epsilion(v)$
-  2D/3D Quasistatic damage via GFP 
	- Idea is to take  Bruno/Giuseppe's serial solver and  parallelize the solver.
	- As EigenValue analysis of each element is required to get the principal directions there is a need to implement c++ GFP macros. 
-  Update testing in Make check
-  Better ParaView export for transient.

