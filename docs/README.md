# Introduction

PSD, acronym for *P*arallel finite element *S*olver for continuum *D*ynamics, is a finite elements-based solid mechanics solver with capabilities of performing High Performance Computing (HPC) simulations with billions of unknowns. The kernel of PSD is wrapped around [FreeFEM](https://freefem.org/) for finite element discretization, and [PETSc](https://www.mcs.anl.gov/petsc/) for linear algebra/Preconditioning. PSD solver contains straightforward supports for *static* or *dynamic* simulations with *linear*  and *nonlinear* solid mechanics problems. Besides these [*hybrid-phase field fracture mechanics*](https://link.springer.com/article/10.1007/s00466-014-1109-y) models have also been incorporated within PSD. For dynamics the [*genralized-$\alpha$ model*](https://hal.archives-ouvertes.fr/hal-00345290/document)  for time discretization is used, this models enable straightforward use of Newmark-$\beta$, central difference, or Hilber-Hughes-Taylor (HHT) as time discretization. PSD uses sate-of-the art domain-decomposition paradigm via [*vectorial finite elements*](https://www.sciencedirect.com/science/article/pii/S0022407317309597) for parallel computing and all solvers are  proven to scale quasi-optimally. PSD has proven scalabilty uptill 24,000 cores with largest problem solved containing over 5 Billion unknowns.

<div style="text-align: center;">
  <img src="https://github.com/user-attachments/assets/fe09ddd1-11b5-43de-b320-9bc0f1225d52" width="50%" alt="Displacement field at time step 0">
</div>

Besides the parallel suite, PSD also includes a sequential solver which does not require [PETSc](https://www.mcs.anl.gov/petsc/).

PSD works for two and three dimensional problems only. Unstructured meshes (triangular for 2D and tetrahedral for 3D) are supported in [MEDIT&#39;s](https://www.ljll.math.upmc.fr/frey/software.html)  `.mesh` format, [Gmsh&#39;s](http://gmsh.info/) `.msh` format, [SALOME&#39;s](https://www.salome-platform.org/) `.med` format. PSD post processing is done via `.pvd` ,`.vtk`, `pvtu`, and `.vtu` files of the [ParaView](https://www.paraview.org/) platform.

Here are some simulation examples performed with PSD.
