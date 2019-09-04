# Changelog
All notable changes to PSD solver will be documented in this file.

## Unreleased
### Added
- New quasi-static parallel solver (Extension of B.Masseron & G.Rastiello sequential version).
- New GFP plugin for Mazar's damage update for 2D problems `GFPMazarsDamageUpdate(...)`.
- New MPI plotting routine `plotJustMeshMPI()`.

### Changed
- Better plotting support for `PlotMPI()`.
- Moved to FreeFEM 4.4.

## 1.2 - 2019-03-18
### Added
- Support for Gmsh's `.msh`  or Medit's `.mesh` meshes.
- Advance to 3D.
- New MPI based parallel solver linear elasticity.
- New approach for solver generation via scripting (PhD thesis MA Badri) with `scriptGenerator.edp`.
- Integrated Domain decomposition macro (PhD thesis MA Badri).
- Customized `.vtk` support for ParaView post-processing.
- New point boundary condition macro `pointbc(Real[int], fespace, matrix)`.
- New flags for communicating with the solver: `-dimension`, `-plot`, `-bodyforce`, `-lagrange`, etc.


### Changed
- More advance README.MD.
- Sequential solver now merged within scripting via flag `-sequential`.

### Removed
- Removed the manufactured solution codes.

## 1.1 - 2019-03-04
### Added
- New manufactured solution for linear elasticity in 2D.
- Added README.MD for explaining the solver.
- New test case of constrained bar in 2D.
- ParaView plotting activated.

### Changed
- Moved to Tuleap git hosting from CEA.

## 1.0 - 2019-02-15
### Added
- Initial FreeFEM files for sequential linear elasticity in 2D.
- Method of manufactured solution for linear elasticity in 2D.

## Version git tags ##

| Version    | Git tag                                 | 
| ---------- | ----------------------------------------|
| 1.0        |8a8ecb2746b7da792073358c60df33bae647f788 | 
| 1.1        |a667e6085ba1f92f8dd619bd40e18f85c593bc0a |
| 1.2        |e48b7b3a30c05ad4c343efa6a17fee386031f437 |
