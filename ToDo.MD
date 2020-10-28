# PSD todo list: 


## [ONGOING] Hujeux soil law make it work with PSD
## [ONGOING] Nonlinear damage mechanics with nested matrices 

## [TODO] make check examples for soildynamaics with doublecouple/top-ii-vol


## [TODO] Optimize force calculation (matrix-vector type)
## [TODO] Druker-Prager law for soil dynamics
## [TODO] Couple damage and seismic solver
## [TODO] Heterogeneous materials class of problems
## [TODO] Parallel interpolation on surface from volume

## [DONE] Distributed meshing interface for soil dynamics with top-ii-vol


## [DONE] Extract point field in MPI
## [DONE] Force calculation via matrix vector product
## [DONE] Fully commented control parameters file
## [DONE] Including material properties as macros not real type
## [DONE] Quadrature point based stress, strain variables  
## [DONE] Higher order quadrature formulations
## [DONE] Better way to include Dirichlet via macro table
## [DONE] Pseudo nonlinear procedure for solving linear problems with Newton-Raphsons
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

