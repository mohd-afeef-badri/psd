# PSD todo list: 


## [ONGOING] Hujeux soil law make it work with PSD
## [ONGOING] Nonlinear damage mechanics with nested matrices 



## [TODO] Couple damage and seismic solver
## [TODO] Better way to include Dirichlet via macro table
## [TODO] Including material properties as macros not real type
## [TODO] SNES interface for experimenting nonlinearity
## [TODO] Heterogeneous materials class of problems
## [TODO] Parallel interpolation on surface from volume
## [TODO] Distributed meshing interface for soil dynamics with top-ii-vol
## [TODO] Higher order quadrature formulations
## [TODO] Quadrature point based stress, strain variables  
## [TODO] Extract point filed in MPI



## [DONE] Hujeux soil law make it work with C++ 11
## [DONE] Strain Vectorization
## [DONE] Split & clearing done in Hujeux law
## [DONE] Newton--Raphsons for dynamics and phase-field
## [DONE] Introduce non-linearity for dynamics
## [DONE] GFP single function for Energy decomposition
## [DONE] Material tensor of damage problems
## [DONE] Tag Modification
## [DONE] Dynamic solver via $\epsilon(u):A:\epsilon(v)$
## [DONE] New variational formulations $\epsilon(u):A:\epsilon(v)$ instead of $\sigma(u):\epsilion(v)$
## [DONE] 2D/3D Quasistatic damage via GFP 
	- Idea is to take  Bruno/Giuseppe's serial solver and  parallelize the solver.
	- As EigenValue analysis of each element is required to get the principal directions there is a need to implement c++ GFP macros. 
## [DONE] Update testing in Make check
## [DONE] Better ParaView export for transient.

