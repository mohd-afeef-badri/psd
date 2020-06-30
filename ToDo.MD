# What is comping up

## [TODO] Hujeux law split
## [TODO] Hejeux soil law make it work with C++ 11
## [TODO] Distributed meshing for soil dynamics.
## [TODO] Strain Vectorization
## [TODO] Introduce non-lineaity for dynamics
## [TODO] Newton--Raphsons for dynamics and phase-field
## [TODO] Higher order quadrature formulations
## [TODO] Extract point filed in MPI.


## [DONE] GFP single function for Energy decomposition
## [DONE] Material tesor of damage problems
## [DONE] Tag Modification
## [DONE] Dynamic solver via $\epsilon(u):A:\epsilon(v)$
## [DONE] New variational formulations $\epsilon(u):A:\epsilon(v)$ instead of $\sigma(u):\epsilion(v)$
## [DONE] 2D/3D Quasistatic damage via GFP 
	- Idea is to take  Bruno/Giuseppe's serial solver and  parallelize the solver.
	- As EigenValue alaysis of each element is required to get the principal directions there is a need to implement c++ GFP macros. 
## [DONE] Update tesing in Make check
## [DONE] Better ParaView export for transient.

