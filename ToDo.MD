# What is comping up

## [TODO] Distributed meshing for soil dynamics.
## [TODO] GFP single function for Energy decomposition
## [TODO] Strain Vectorization
## [TODO] Material tesor of damage problems
## [TODO] Tag Modification
## [TODO] Dynamic solver via $\epsilon(u):A:\epsilon(v)$
## [TODO] Introduce non-lineaity for dynamics
## [TODO] Newton--Raphsons for dynamics and phase-field
## [TODO] Higher order quadrature formulations
## [TODO] Extract point filed in MPI.

## [DONE] New variational formulations $\epsilon(u):A:\epsilon(v)$ instead of $\sigma(u):\epsilion(v)$
## [DONE] 2D/3D Quasistatic damage via GFP 
	- Idea is to take  Bruno/Giuseppe's serial solver and  parallelize the solver.
	- As EigenValue alaysis of each element is required to get the principal directions there is a need to implement c++ GFP macros. 
## [DONE] Update tesing in Make check
## [DONE] Better ParaView export for transient.

