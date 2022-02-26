/**************************************************************************************
*                                                                                     *
* Author : Mohd Afeef BADRI                                                           *
* Email  : mohd-afeef.badri@cea.fr                                                    *
* Date   : 20/04/2020                                                                 *
* Type   : Support file                                                               *
*                                                                                     *
* Comment: This support  file is  responsible for generating  ControlParameters.edp   *
*          which contain main solver control parameters of PSD.                       *
*                                                                                     *
**************************************************************************************/

writeHeader;

 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "// ------- Mesh parameters (Un-partitioned) -------                            \n"
 "// -------------------------------------------------------------------         \n"
 "//  ThName : Name of the .msh file in Meshses/2D or  Meshses/3D folder         \n"
 "//=============================================================================\n";

 writeIt
 "                                                                              \n"
 "  string ThName = \"../Meshes/"<<spc<<"D/bar-dynamic.msh\";                   \n";

 writeIt
 "                                                                              \n"
 "//============================================================================\n"
 "//                   ------- Material parameters -------                      \n"
 "// -------------------------------------------------------------------        \n"
 "//  rho : density of Material                                                 \n"
 "//  mu, lambda : Lame parameter of the Material                               \n"
 "//  E, nu : Modulus of Elasticity and Poisson ratio of the Material           \n"
 "//============================================================================\n"
 "                                                                              \n"
 "  real rho    = 1.0          ,                                                \n"
 "       lambda = 576.9230769  ,           // E=1000. & nu=0.3                  \n"
 "       mu     = 384.6153846  ;           // E=1000. & nu=0.3                  \n"
 "                                                                              \n";

 if(TimeDiscretization=="generalized_alpha")
  writeIt
  "                                                                              \n"
  "//============================================================================\n"
  "//           ------- Time discretization parameters -------                   \n"
  "// -------------------------------------------------------------------        \n"
  "//  alpm, alpf : Generalized-alpha scheme constants                           \n"
  "//  etam, etak : damping parameters                                           \n"
  "//  t, tmax, dt : Time parameters, time, maximum time, and time step          \n"
  "//  gamma, beta : Time discretization constants (Newmark-beta)                \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  real etam = 0.01 ,                                                         \n"
  "       etak = 0.01 ,                                                         \n"
  "       alpm = 0.2  ,                                                         \n"
  "       alpf = 0.4  ,                                                         \n"
  "       tmax = 4.0  ,                                                         \n"
  "       t    = 0.08 ,                                                         \n"
  "       dt   = 0.08 ;                                                         \n"
  "                                                                             \n"
  "  real gamma = 0.5 + alpf - alpm         ,                                   \n"
  "       beta  = (1./4.)*(gamma+0.5)^2     ;                                   \n"
  "                                                                             \n";

 if(TimeDiscretization=="newmark_beta")
  writeIt
  "                                                                              \n"
  "//============================================================================\n"
  "//           ------- Time discretization parameters -------                   \n"
  "// -------------------------------------------------------------------        \n"
  "//  etam, etak : damping parameters                                           \n"
  "//  t, tmax, dt : Time parameters, time, maximum time, and time step          \n"
  "//  gamma, beta : Time discretization constants (Newmark-beta)                \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  real etam = 0.01 ,                                                         \n"
  "       etak = 0.01 ,                                                         \n"
  "       tmax = 4.0  ,                                                         \n"
  "       t    = 0.08 ,                                                         \n"
  "       dt   = 0.08 ;                                                         \n"
  "                                                                             \n"
  "  real gamma = 0.5                       ,                                   \n"
  "       beta  = (1./4.)*(gamma+0.5)^2     ;                                   \n"
  "                                                                             \n";

 if(TimeDiscretization=="central_difference")
  writeIt
  "                                                                              \n"
  "//============================================================================\n"
  "//           ------- Time discretization parameters -------                   \n"
  "// -------------------------------------------------------------------        \n"
  "//  etam, etak : damping parameters                                           \n"
  "//  t, tmax, dt : Time parameters, time, maximum time, and time step          \n"
  "//  gamma : Time discretization constant                                      \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  real etam = 0.01 ,                                                         \n"
  "       etak = 0.01 ,                                                         \n"
  "       tmax = 4.0  ,                                                         \n"
  "       t    = 0.08 ,                                                         \n"
  "       dt   = 0.08 ,                                                         \n"
  "       gamma = 0.5 ;                                                         \n"
  "                                                                             \n";

 if(TimeDiscretization=="hht_alpha")
  writeIt
  "                                                                              \n"
  "//============================================================================\n"
  "//           ------- Time discretization parameters -------                   \n"
  "// -------------------------------------------------------------------        \n"
  "//  alpf : HHT-alpha scheme constant                                          \n"
  "//  etam, etak : damping parameters                                           \n"
  "//  t, tmax, dt : Time parameters, time, maximum time, and time step          \n"
  "//  gamma, beta : Time discretization constants (Newmark-beta)                \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  real etam = 0.01 ,                                                         \n"
  "       etak = 0.01 ,                                                         \n"
  "       alpf = 0.4  ,                                                         \n"
  "       tmax = 4.0  ,                                                         \n"
  "       t    = 0.08 ,                                                         \n"
  "       dt   = 0.08 ;                                                         \n"
  "                                                                             \n"
  "  real gamma = 0.5 + alpf                ,                                   \n"
  "       beta  = (1./4.)*(gamma+0.5)^2     ;                                   \n"
  "                                                                             \n";

if(dirichletconditions>=1)
 {
 writeIt
 "                                                                              \n"
 "//============================================================================\n"
 "//        ------- Dirichlet boundary-condition parameters -------             \n"
 "// ---------------------------------------------------------------------------\n"
 "// Dbc       : acronym for Dirichlet boundary condition                       \n"
 "// Dbc(I)On  : is/are the  surface labels tags (integer list) on to which     \n"
 "//             Dirichlet boundary conditions is to be applied.                \n"
 "// Dbc(I)Ux  : is the x component of Dirichlet displacement on the surface    \n"
 "//             border (I) denoted by label(s) Dbc(I)On in the mesh.           \n"
 "// -------------------------------------------------------------------------- \n"
 "// NOTE: either macro Dbc(I)Ux or Dbc(I)Uy or Dbc(I)Uz should  be commented   \n"
 "//       or deleted if the user does not wish to apply Dirichlet  condition   \n"
 "//       on that particular  direction (let it free)                          \n"
 "//============================================================================\n"
 "                                                                              \n";

 if(spc==2)
  for(int i=0; i<dirichletconditions; i++)
   writeIt
   "  macro  Dbc"<<i<<"On "<<labelDirichlet<<"   //                            \n"
   "  macro  Dbc"<<i<<"Ux 0.  //                                               \n"
   "  macro  Dbc"<<i<<"Uy 0.  //                                               \n";

 if(spc==3)
  for(int i=0; i<dirichletconditions; i++)
   writeIt
   "  macro  Dbc"<<i<<"On "<<labelDirichlet<<"   //                            \n"
   "  macro  Dbc"<<i<<"Ux 0. //                                                \n"
   "  macro  Dbc"<<i<<"Uy 0. //                                                \n"
   "  macro  Dbc"<<i<<"Uz 0. //                                                \n";
}


if(dirichletpointconditions>=1)
 {
 writeIt
 "                                                                              \n"
 "//============================================================================\n"
 "//       -------Dirichlet point boundary-condition parameters-------          \n"
 "// -------------------------------------------------------------------------- \n"
 "// Pbc       : acronym for point boundary condition                           \n"
 "// PbcCord   : is the table  containing coordinates of the points for which   \n"
 "//             point  boundary condition(s) is to be applied                  \n"
 "// Pbc(I)Ux : is x displacement value of the point I. Similar logic applies   \n"
 "//            to PC(I)Uy, PC(I)Uz                                             \n"
 "// -------------------------------------------------------------------------- \n"
 "// NOTE: either the macro PC(I)Ux or PC(I)Uy or PC(I)Uz should be commented   \n"
 "//       if the user does not wish to apply restriction on that  particular   \n"
 "//       displacement direction (let it free)                                 \n"
 "//============================================================================\n"
 "                                                                              \n"
 "  real[int,int] PbcCord = [                                                   \n";

 if(spc==2){
 writeIt
 "//-------------------- [  x  , y  ] --------------------//                   \n";
 for(int i=0; i<dirichletpointconditions; i++)
 writeIt
 "                       [  0. , 0. ]    // point "<<i<<"                       \n";

 writeIt
 "//------------------------------------------------------//                    \n"
 "                      ];                                                      \n";

 for(int i=0; i<dirichletpointconditions; i++)
 writeIt
 "                                                                              \n"
 "   macro Pbc"<<i<<"Ux  -0. //                                                 \n"
 "   macro Pbc"<<i<<"Uy  -0. //                                                 \n"
 "                                                                              \n";
 }

 if(spc==3){
 writeIt
 "//-------------------- [  x  , y  , z  ]--------------------//                \n";
 for(int i=0; i<dirichletpointconditions; i++)
 writeIt
 "                       [  0. , 0. , 0. ]    // point "<<i<<"                  \n";
 writeIt
 "//----------------------------------------------------------//                \n"
 "                      ];                                                      \n";

 for(int i=0; i<dirichletpointconditions; i++)
 writeIt
 "                                                                              \n"
 "   macro Pbc"<<i<<"Ux  -0. //                                                 \n"
 "   macro Pbc"<<i<<"Uy  -0. //                                                 \n"
 "   macro Pbc"<<i<<"Uz  -0. //                                                 \n"
 "                                                                              \n";

 }
}


if(tractionconditions>=1)
 {
 writeIt
 "                                                                              \n"
 "//============================================================================\n"
 "// ------- Neumann/traction boundary-condition parameters -------             \n"
 "// ---------------------------------------------------------------------------\n"
 "// Tbc       : acronym for traction boundary condition                        \n"
 "// Tbc(I)On  : is/are the  surface labels tags (integer list) on to which     \n"
 "//             traction boundary conditions is to be applied.                 \n"
 "// Tbc(I)Tx  : is the x component of traction forces on the surface           \n"
 "//             border (I) denoted by label(s) Tb(I)On in the mesh.            \n"
 "// -------------------------------------------------------------------------- \n"
 "// NOTE: either macro Tbc(I)Tx or Tbc(I)Ty or Tbc(I)Tz should  be commented   \n"
 "//       or deleted  if  the  user  does not wish to apply traction on that   \n"
 "//       particular  direction (let it free)                                  \n"
 "//============================================================================\n"
 "                                                                              \n";
  for(int i=0; i<tractionconditions; i++)
   writeIt
   "  macro  Tbc"<<i<<"On  4   //                                              \n"
   "  macro  Tbc"<<i<<"Ty  tt/0.8*(tt <= 0.8)+ 0.*(tt > 0.8) //                \n";

 }


if(bodyforceconditions>=1)
 {
 writeIt
 "                                                                              \n"
 "//============================================================================\n"
 "//        ------- volumetric bodyforce  parameters -------                    \n"
 "// ---------------------------------------------------------------------------\n"
 "// Fbc       : acronym for  force boundary condition (body force)             \n"
 "// Fbc(I)On  : is/are the  volume  labels tags (integer list) on to which     \n"
 "//             force boundary conditions is to be applied.                    \n"
 "// Fbc(I)Fx  : is the x  component of body force  acting in the volume (I)    \n"
 "//             denoted by label(s) Fbc(I)On in the mesh.                      \n"
 "// -------------------------------------------------------------------------- \n"
 "// NOTE: either macro Fbc(I)Fx or Fbc(I)Fy or Fbc(I)Fz should  be commented   \n"
 "//       or deleted if the user  does not wish to apply body force in  that   \n"
 "//       particular  direction (let it free)                                  \n"
 "//============================================================================\n"
 "                                                                              \n";

  for(int i=0; i<bodyforceconditions; i++)
   writeIt
   "  macro  Fbc"<<i<<"On "<<labelBodyForce<<"   //                             \n"
   "  macro  Fbc"<<i<<"Fy -78480.0 // {rho*g=8.e3*(-9.81)=-78480.0}             \n";
 }


if(pointprobe){
 writeIt
 "                                                                              \n"
 "//============================================================================\n"
 "//        ------- Parameters for point probe -------                          \n"
 "// ---------------------------------------------------------------------------\n"
 "// ProbePointCord : list of coordinates for the probe  [x,y] for 2D and       \n"
 "//                  [x,y,z] for 3D problems                                   \n"
 "//============================================================================\n"
 "                                                                              \n"
 "  real [int,int]   ProbePointCord  =                                          \n"
 "                                     [                                        \n"
 "                                                                              \n";

 if(spc==2)
 writeIt
 "//                                      [ x    ,  y  ]                        \n"
 "                                        [ 1.   ,  2. ],                       \n"
 "                                        [ 2.   ,  5. ]                        \n";

 if(spc==3)
 writeIt
 "//                                      [ x    ,  y    ,  z  ]                \n"
 "                                        [ 1.   ,  2.   ,  5. ],               \n"
 "                                        [ 2.   ,  5.   ,  6. ]                \n";

 writeIt
 "                                                                              \n"
 "                                     ];                                       \n";
}

writeIt
"                                                                               \n"
"//=============================================================================\n"
"// ------- Solver control parameters -------                                   \n"
"//=============================================================================\n"
"                 // TO DO                                                      \n"
"                                                                               \n";

