//=====================================================================================
// ------ Poisson problem for the LinearFormBuilderAndSolver.edp file ------
//=====================================================================================


if(!Sequential){

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

if(debug)
codeSnippet R""""(

//-------------Debug plotting------------------//
  macro viz(i)i//
  plotMPI(Th, u, P1,  viz, real, wait=0, cmm="u");

)"""";

if(ParaViewPostProcess)
codeSnippet R""""(

//==============================================================================
// -------Postprocess with paraview-------// 
//==============================================================================
  if(mpirank==0)
    system("mkdir -p VTUs/"); 
  mpiBarrier(mpiCommWorld); 
                                              
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

}  //-- [if loop terminator] !Sequential ended --//



if(Sequential){
codeSnippet R""""(

//------ resize vectors x and b -------//

macro resizeVectors()

  x.resize(Vh.ndof);
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

if(debug)
codeSnippet R""""(

  /*--------------debug glut plotting---------------*/ 
   plot (u, wait=1, fill=1, value=1, cmm= "solution"); 
)"""";

if(ParaViewPostProcess)
codeSnippet R""""(


  /*------------Postprocess with ParaView----------*/                                      

  system("mkdir -p VTUs/"); 

  startProcedure("Paraview Postprocess",t0); 
  savevtk( "VTUs/Solution-" + currentIter + ".vtu"   , 
            Th                       , 
            u                        , 
            order=vtuorder           , 
            dataname="U" 
         ); 
  endProcedure  ("Paraview Postprocess",t0);
)"""";

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

if(adaptmesh){
codeSnippet R""""(

macro solvePoissonAndAdapt
  solvePoisson;
)"""";

if(AdaptmeshBackend=="FreeFEM"){
codeSnippet R""""(
  Th = adaptmesh(Th,u, iso = adaptIso);
)"""";
}
else if (AdaptmeshBackend=="mmg"){
codeSnippet R""""(
  Th = adaptmesh(Th,u, iso = adaptmeshisotropy);
)"""";
}
else if (AdaptmeshBackend=="parmmg"){
codeSnippet R""""(
  cout << "ERROR PARMMG DOES NOT WORK WITH SEQUENTIAL SOLVER "<< endl;
  exit(1111);
)"""";
}
else {
codeSnippet R""""(
  cout << " Wrong value for -adaptmesh_backend " << endl;
  exit(11111);
)"""";

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
    postprocess;
    currentIter++;
}
)"""";
}
else{

codeSnippet R""""(
 solvePoisson;
)"""";
}

}  //-- [if loop terminator] Sequential liniear elasticity ended --//
