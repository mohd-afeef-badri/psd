//=====================================================================================
// ------ Poisson problem for the LinearFormBuilderAndSolver.edp file ------
//=====================================================================================

if (!Sequential) {

  if (!adaptmesh) {
    codeSnippet R""""(

//==============================================================================
//  ------- Local Au=b assembly and solving -------
//==============================================================================

//--------------Assembly for bilinear--------------//

  startProcedure("matrix Assembly",t0);
  ALoc = varfPoisson(Vh,Vh,solver=CG,sym=1);
  endProcedure  ("matrix Assembly",t0);

//---------------Assembly for linear---------------//
                                                    
  startProcedure("RHS assembly",t0);
  b = varfPoisson(0,Vh);
  endProcedure  ("RHS assembly",t0);

//---------------PETSc Assembly---------------------//

  startProcedure("PETSc assembly",t0);
  A = ALoc ;
  endProcedure("PETSc assembly",t0);

//---------------PETSc solving---------------------//

  startProcedure("PETSc solving",t0);
  set(A,sparams =" -ksp_type cg -ksp_rtol 1e-9 ");
  u[] = A^-1*b;
  endProcedure("PETSc solving",t0);

)"""";

    if (debug)
      codeSnippet R""""(

//-------------Debug plotting------------------//
  macro viz(i)i//
  plotMPI(Th, u, P1,  viz, real, wait=0, cmm="u");

)"""";

    if (ParaViewPostProcess)
      codeSnippet R""""(

//==============================================================================
// -------Postprocess with paraview-------// 
//==============================================================================
                                              
  startProcedure("Paraview Postprocess",t0); 
  int[int] vtuorder=[1];                     // Solution export order 
  savevtk( "VTUs/Solution.vtu"  , 
            Th                  , 
            u                   , 
            order=vtuorder      , 
            dataname="U"  
         ); 
  endProcedure("Paraview Postprocess",t0); 

)"""";
  } else {
    if (spc == 3 && ParmmgMethod == "NULL")
      codeSnippet R""""(
for(int i = 0; i <= adaptIter; ++i) {

  startProcedure("matrix Assembly",t0);
  A = varfPoisson(Vh, Vh, tgv=-1);
  endProcedure("matrix Assembly", t0);

  startProcedure("RHS assembly",t0);
  PetscScalar[int] b = varfPoisson(0, Vh, tgv=-1);
  endProcedure("RHS assembly", t0);

  startProcedure("PETSc solving", t0);
  set(A, sparams = "-ksp_monitor -pc_type gamg");
  u[] = A^-1 * b;
  endProcedure("PETSc solving", t0);

  startProcedure("Adapt mesh init", t0);
  mesh3 ThParMmg;
  DmeshInitialize(ThParMmg);
  endProcedure("Adapt mesh init", t0);

  startProcedure("Metric calculation", t0);
  real[int] met = mshmet(Th, u, loptions=lloptions, doptions=ddoptions);
  endProcedure("Metric calculation", t0);

  startProcedure("Mesh adaption", t0);
  real[int] metParMmg;
  int[int][int] communicators;
  ParMmgCommunicatorsAndMetric(Th, met, ThParMmg, metParMmg, communicators);
  ThParMmg = parmmg3d(MmgParameters(ThParMmg, metParMmg, rt, verbosity),
              nodeCommunicators = communicators, niter = parMmgIter);
  endProcedure("Mesh adaption", t0);

  startProcedure("Distributed mesh reconstrt", t0);
  DmeshReconstruct(ThParMmg);
  endProcedure("Distributed mesh reconstrt", t0);

  startProcedure("Paraview Postprocess", t0);
  savevtk("VTUs/sol.vtu", Th, u, order = vtuorder, append = true, dataname="u");
  endProcedure("Paraview Postprocess", t0);

  startProcedure("Error check", t0);
  Vh diff = u - um;
  real l2err = sqrt(int3d(Th)(diff^2));
  endProcedure("Error check", t0);

  startProcedure("variable update", t0);
  DmeshCopy(ThParMmg, Th);
  Mat<PetscScalar> Adapt;
  MatCreate(Th, Adapt, P1);
  A = Adapt;
  u = 0.0;
  endProcedure("variable update", t0);
}
)"""";
    if (spc==3 && (ParmmgMethod == "partition_regrouping" || ParmmgMethod == "partition_automatic_regrouping"))
      codeSnippet R""""(
for(int i = 0; i <= adaptIter; ++i) {

  startProcedure("matrix Assembly",t0);
  A = varfPoisson(Vh, Vh, tgv=-1);
  endProcedure("matrix Assembly", t0);

  startProcedure("RHS assembly",t0);
  PetscScalar[int] b = varfPoisson(0, Vh, tgv=-1);
  endProcedure("RHS assembly", t0);

  startProcedure("PETSc solving", t0);
  set(A, sparams = "-ksp_monitor -pc_type gamg");
  u[] = A^-1 * b;
  endProcedure("PETSc solving", t0);

  startProcedure("Adapt mesh init", t0);
  mesh3 ThParMmg;
  DmeshInitialize(ThParMmg);
  endProcedure("Adapt mesh init", t0);

  startProcedure("Mesh grouping", t0);)"""";
    if (spc==3 && ParmmgMethod == "partition_automatic_regrouping")
      codeSnippet R""""(
  getNt(Th);)"""";
    if (spc==3 && (ParmmgMethod == "partition_regrouping" || ParmmgMethod == "partition_automatic_regrouping"))
      codeSnippet R""""(
  int div = mpisize / Pgroups;
  mpiComm commThGather(mpiCommWorld, (mpirank % div == 0 && mpirank / div < Pgroups) ? 0 : mpiUndefined, mpirank / div);
  mpiComm comm(mpiCommWorld, min(mpirank / div, Pgroups - 1), mpirank - div * min(mpirank / div, Pgroups - 1));

  macro ThGatherComm()commThGather//
  mesh3 ThGather;
  DmeshGather(Th, comm, ThGather);
  fespace VhGather(ThGather, P1);
  VhGather<PetscScalar> uGather;
  VecGather(Th, comm, ThGather, P1, u, uGather);
  macro ThGatherParMmgComm()commThGather//

  mesh3 ThGatherParMmg;
  DmeshInitialize(ThGatherParMmg);
  endProcedure("Mesh grouping", t0);

  startProcedure("Mesh adapt", t0);
  if((mpirank % div == 0 && mpirank / div < Pgroups) != 0)
  {
    real[int] met = mshmet(ThGather, uGather, loptions=lloptions, doptions=ddoptions);

    if(mpiSize(commThGather) > 1) {
      real[int] metParMmg;
      int[int][int] communicators;
      ParMmgCommunicatorsAndMetric(ThGather, met, ThGatherParMmg, metParMmg, communicators);
      ThGatherParMmg = parmmg3d(MmgParameters(ThGatherParMmg, metParMmg, rt, verbosity),
        nodeCommunicators = communicators, niter = parMmgIter, comm = commThGather);
    }
    else
    {
      ThGatherParMmg = mmg3d(MmgParameters(ThGather, met, rt, verbosity));
    }
  }
  endProcedure("Mesh adapt", t0);

  startProcedure("Mesh scatter", t0);
  DmeshScatter(ThGatherParMmg, comm, ThParMmg);
  endProcedure("Mesh scatter", t0);

  startProcedure("Paraview Postprocess", t0);
  savevtk("VTUs/sol.vtu", Th, u, order = vtuorder, append = true, dataname="u");
  endProcedure("Paraview Postprocess", t0);

  startProcedure("Error check", t0);
  Vh diff = u - um;
  real l2err = sqrt(int3d(Th)(diff^2));
  endProcedure("Error check", t0);

  startProcedure("variable update", t0);
  DmeshCopy(ThParMmg, Th);
  Mat<PetscScalar> Adapt;
  MatCreate(Th, Adapt, P1);
  A = Adapt;
  u = 0.0;
  endProcedure("variable update", t0);
}
    )"""";
  }

} //-- [if loop terminator] !Sequential ended --//

if (Sequential) {
  codeSnippet R""""(

//------ resize vectors x and b -------//

macro resizeVectors()

  x.resize(Vh.ndof);
  x = 0.;
  b.resize(Vh.ndof);
//


//-------- assemble martix A ---------//

macro assembleMatrixA()

  startProcedure("matrix assembly",t0); 
  A = varfPoisson(Vh,Vh,solver=CG,sym=1); 
  endProcedure  ("matrix assembly",t0);
//


//-------- assemble vector b ---------//

macro assembleVectorb()

  startProcedure("RHS assembly",t0); 
  b = varfPoisson(0,Vh); 
  endProcedure  ("RHS assembly",t0); 
//


//------- solve linear system -------//

macro solve()

  startProcedure("solving U",t0); 
  set(A,solver=CG,sym=1); 
  x = A^-1*b; 
  endProcedure  ("solving U",t0);
//


//------ get u (u = x = A^-1b) ------//

macro getU()

  Vh u;
  u[] = x;
//

)"""";

  codeSnippet R""""(

//--------- postprocessing ---------//

macro postprocess()
)"""";

  if (debug)
    codeSnippet R""""(

  /*--------------debug glut plotting---------------*/ 
   plot (u, wait=1, fill=1, value=1, cmm= "solution"); 
)"""";

  if (ParaViewPostProcess) {
    if (Sequential)
      codeSnippet R""""(


  /*------------Postprocess with ParaView----------*/

  startProcedure("Paraview Postprocess",t0); 
  savevtk( "VTUs/Solution-" + currentIter + ".vtu"   , 
            Th                       , 
            u                        , 
            order=vtuorder           , 
            dataname="U" 
         ); 
  endProcedure  ("Paraview Postprocess",t0);
)"""";
    else
      codeSnippet R""""(


  /*------------Postprocess with ParaView----------*/                                      

  system("mkdir -p VTUs/"); 

  startProcedure("Paraview Postprocess",t0); 
  savevtk( "VTUs/Solution.vtu"   , 
            Th                       , 
            u                        , 
            order=vtuorder           , 
            dataname="U"	     ,
	    append=true 
         ); 
  endProcedure  ("Paraview Postprocess",t0);
)"""";
  }

  codeSnippet R""""(
//
)"""";

  codeSnippet R""""(

macro solvePoisson

  resizeVectors;
  assembleMatrixA;
  assembleVectorb;
  solve;
  getU;
  postprocess;

//

)"""";

  if (adaptmesh) {

    codeSnippet R""""(

macro solvePoissonAndAdapt
  solvePoisson;
)"""";

    if (AdaptmeshMetricBackend == "freefem" && AdaptmeshBackend == "freefem") {
      codeSnippet R""""(
  Th = adaptmesh(Th,u, iso = adaptIso, err = adaptErr);
  adaptErr = adaptErr / adaptErrRate;
)"""";
    } else if (AdaptmeshBackend == "mmg") {
      if (spc == 2) {
	      if (AdaptmeshMetricBackend == "freefem")
        codeSnippet R""""(
  Vh dx2u, dy2u, dxdyu;
  adaptmesh(Th, u, err=adaptErr, iso=adaptIso, metric=[dx2u[], dy2u[], dxdyu[]], nomeshgeneration=true);
  adaptErr = adaptErr / adaptErrRate;

  real[int] met(Th.nv * 3);
  for (int k = 0; k < Th.nv; k++)
  {
       met[3*k] = dx2u[][k];
       met[3*k+1] = dy2u[][k];
       met[3*k+2] = dxdyu[][k];
  }
   
  Th = mmg2d(Th, metric = met, verbose=mmgVerbosityVal); 
)"""";
	      if (AdaptmeshMetricBackend == "mshmet")
        codeSnippet R""""(
  real[int] met = mshmet(Th, u, loptions=lloptions, doptions=ddoptions);
  Th = mmg2d(Th, metric = met, verbose=mmgVerbosityVal); 
)"""";
      } else if (spc == 3) {
        if (AdaptmeshMetricBackend == "mshmet")
          codeSnippet R""""(
  real[int] met = mshmet(Th, u, loptions=lloptions, doptions=ddoptions);
  Th = mmg3d(Th, metric=met, hgrad=hgradVal, hmin=hminVal, hmax=hmaxVal, hausd=hausdVal, mem=mmgMemory);
)"""";
        if (AdaptmeshMetricBackend == "freefem")
          codeSnippet R""""(
  cout << "ERROR ONLY MSHMET IS AVAILABLE FOR 3D METRIC" << endl;
  exit(999);
)"""";
      }
    }

    codeSnippet R""""(
//

//--------- solve and adapt mesh ------------//
// we apply the following algorithm
//
// for all i in 1:adaptIter
//   assemble A;
//   assemble b;
//   solve x = A^-1b;
//   u=x;
//   postprocess u;
//   adapt mesh with Hessian(u);
//
//-------------------------------------------//

for(int i=0; i < adaptIter; i++){
    solvePoissonAndAdapt;
    currentIter++;
}
)"""";

  } else {
    codeSnippet R""""(
 solvePoisson;
)"""";
  }
}
