## PSD todo list:



**Ongoing**
- [x] 



**Todo**

- [ ] Optimize interpolation via building of interpolation matrix

- [ ] Finish the documentation of Iwan 
- [ ] Build a tutorial on Iwan 
- [ ] Optimize the law of Iwan with the status
- [ ] Add more validation test 
- [ ] Hujeux soil law make it work with PSD
- [ ] Nonlinear damage mechanics with nested matrices 

- [ ] To add examples for -pointprobe flag in make check
- [ ] make check examples for time-discretization
- [ ] Optimize force calculation (matrix-vector type)
- [ ] Druker-Prager law for soil dynamics
- [ ] Couple damage and seismic solver
- [ ] Heterogeneous materials class of problems
- [ ] Parallel interpolation on surface from volume





**Done**

- [x] Raw string support for hpp files
- [x] Mfront integration of PSD (non-linear)
- [x] Include Medfile support

- [x] Mfront integration of PSD (non-linear)

- [x] PSD configures PETSc and FreeFEM

- [x] Mfront integration of PSD  linear-elasticity

- [x] Use max system procs for tests
- [x] Activate top-ii-vol version 1.3 for PSD

- [x] Install binaries and libraries in usr/bin and usr/include/psd
- [x] seperate precracked dirichlet flag

- [x] mesh flag for PSD_Solve
- [x] Distributed meshing interface for soil dynamics with top-ii-vol
- [x] Extract point field in MPI
- [x] Force calculation via matrix vector product
- [x] Fully commented control parameters file
- [x] Including material properties as macros not real type
- [x] Quadrature point based stress, strain variables  
- [x] Higher order quadrature formulations
- [x] Better way to include Dirichlet via macro table
- [x] Pseudo nonlinear procedure for solving linear problems with Newton-Raphsons
- [x] Hujeux soil law make it work with C++ 11
- [x] Strain Vectorization
- [x] Split & clearing done in Hujeux law
- [x] Newton--Raphsons for dynamics and phase-field
- [x] Introduce non-linearity for dynamics
- [x] GFP single function for Energy decomposition
- [x] Material tensor of damage problems
- [x] Tag Modification
- [x] Dynamic solver via $\varepsilon(u):A:\varepsilon(v)$
- [x] New variational formulations $\varepsilon(u):A:\varepsilon(v)$ instead of $\sigma(u): \varepsilon (v)$
- [x] 2D/3D Quasistatic damage via GFP 
  - Idea is to take  Bruno/Giuseppe's serial solver and  parallelize the solver.
  - As EigenValue analysis of each element is required to get the principal directions there is a need to implement c++ GFP macros. 
- [x] Update testing in Make check
- [x] Better ParaView export for transient.

