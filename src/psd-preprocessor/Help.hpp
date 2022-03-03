//=================================================================================
// ------ Help message on the screen ------
//=================================================================================

 cout << R""""(

 ==============================================================================

                         --- Help on flags used for ---
                                 PSD_PreProcess

 ==============================================================================


  ----------------------------------------------------------------------------
           INTEGER type flags, these flags expect an integer value
  ----------------------------------------------------------------------------


   -dirichletpointconditions [int]     Number of Dirichlet points.
                                       Default 1.

   -bodyforceconditions      [int]     Number of regions in which body force
                                       is define.  Default 0.

   -dirichletconditions      [int]     Number of Dirichlet boundaries.
                                       Default 1.

   -tractionconditions       [int]     Number of Neumann or traction boundaries
                                       Default 1.

   -parmetis_worker          [int]     Number of workers for mesh partitioner
                                       parMETIS. Default MPI size.

   -dimension                [int]     Dimension of  problem. 2 for 2D 3 for 3D
                                       Default 2.

   -lagrange                 [int]     Lagrange order for building FE space.
                                       Option  1 for P1 or 2 for P2. Default 1.


  ----------------------------------------------------------------------------
           STRING type flags, these flags expect an string value
  ----------------------------------------------------------------------------


   -timediscretization [string]     Time discretization type. Use any either
                                    generalized_alpha | newmark_beta

   -nonlinearmethod    [string]     Nonlinear solving method type.
                                    Use Picard | Newton_Raphsons.

   -reactionforce      [string]     Reaction force calculation method.
                                    Use stress_based | variational_based.

   -doublecouple       [string]     Soildynamics  doublecouple boundary cond.
                                    Use  force_based | displacement_based.

   -partitioner        [string]     Mesh partitioner to be used.
                                    Use metis | scotch | parmetis.

   -postprocess        [string]     Indicate postprocessing quantity. Use one
                                    u | v | a | ua | uv | va | phi | uphi | uv

   -validation         [string]     To produce code for a validation test case.
                                    Use Iwan.

   -problem            [string]     Interested problem to be solved by PSD.
                                    linear_elasticity | damage | elastodynamic
                                    | soildynamics | elasto_plastic.

   -model              [string]     Model by which the problem is solved.
                                    Use hybrid_phase_field | pseudo_nonlinear
                                    | Mazar | von_mises


  ----------------------------------------------------------------------------
        BOOLEAN type flags, these flags are like activaction switches
  ----------------------------------------------------------------------------


   -help              [bool]     To activate helping message on the terminal.
                                 Default false.

   -plot              [bool]     To activate plotting routine.
                                 Default false.

   -debug             [bool]     To activate debug openGL plotting routine.
                                 Default false.

   -useGFP            [bool]     To activate use of GoFastPlugins.
                                 Default true/false.

   -timelog           [bool]     To setup time logging for various phases of
                                 solver. Default false.

   -useRCM            [bool]     To activate mesh level renumbering via
                                 Reverse Cuthill Mckee. Default false.

   -activeplot        [bool]     To activate realtime pipe plotting using
                                 GnuPlot. Default false.

   -useMfront         [bool]     To activate MFront interface for PSD, as a
                                 material libraray and behaviour controller.
                                 Default false.

   -bodyforce         [bool]     Activate volumetric source term (body force)
                                 Default false.

   -vectorial         [bool]     To generate vectorial space solver for
                                 nonlinear damage. Default false.

   -energydecomp      [bool]     To activate hybrid phase field energy
                                 splitting/decomposition. Default false.

   -sequential        [bool]     To generate a sequential PSD solver.
                                 Default false.

   -pointprobe        [bool]     To insert point probes for post processing.
                                 Default false.

   -top2vol-meshing   [bool]     Activate top-ii-vol point source meshing for
                                 soil-dynamics. Default false.

   -getenergies       [bool]     Activate routine for extraction of energies in
                                 elastodynamics and soildynamics.

   -constrainHPF      [bool]     Activate constrain condition for damage for
                                 the hybrid phase-field model.

   -getreactionforce  [bool]     Activate routine for extraction of reactions
                                 at surface.

   -plotreactionforce [bool]     Activate real time pipe plotting via GnuPlot
                                 Default false.

   -withmaterialtensor [bool]    Generate variational formulation that includes
                                 material tensor. Default false.

   -crackdirichletcondition [bool] Activate pre-cracked surface Dirichlet for
                                   the hybrid phase-field model. Default false


 ==============================================================================

                         --- Help on flags used for ---
                                    PSD_Solve

 ==============================================================================


  ----------------------------------------------------------------------------
           INTEGER type flags, these flags expect an integer value
  ----------------------------------------------------------------------------

   -np         [int]     Number of processes to use for parallelization
                         Default 2. Values  accepted 1 to infinity

   -v          [int]     Verbosity of the background FEM kernel. Default 1.
                         Set 0 for no output. Values  accepted 0 to infinity

   -split      [int]     Split uniformly the mesh. Default 1 = no splitting.
                         Use 2 to split once. Values  accepted 2 to 12.

   -ksp_max_it [int]     PETSc flag to choose  Krylov solver max iterations.
                         Default 1000.


  ----------------------------------------------------------------------------
        REAL type flags, these flags expect an floating point (real) value
  ----------------------------------------------------------------------------

   -ksp_atol  [real]     PETSc flag to set  absolute tolerance for the Krylov
                         solver convergence. Default 1e-5.

   -ksp_rtol  [real]     PETSc flag to set  relative tolerance for the Krylov
                         solver. Default 1e-5.

  ----------------------------------------------------------------------------
        BOOLEAN type flags, these flags are like activaction switches
  ----------------------------------------------------------------------------

   -wg        [bool]     To activate with graphics option for OpenGL graphics
                         Default false.

  ----------------------------------------------------------------------------
           STRING type flags, these flags expect an string value
  ----------------------------------------------------------------------------

   -mesh        [string]     Mesh file to be used. Either use .mesh or .msh
                             e.g., -mesh nameofmesh.mesh

   -ksp_type    [string]     PETSc flag to choose the Krylov solver. Default cg
                             Use cg | gmres | bicg | bicgstab.

   -pc_type     [string]     PETSc flag to choose preconditioner for the solver
                             Default bjacobi. Use jacobi | bjacobi | lu | gamg

   -sub_pc_type [string]     PETSc flag to choose sub preconditioner for solver
                             Default ilu. Use ilu | icc | lu | gamg .

 )"""";
