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

if(!top2vol)
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "// ------- Mesh parameters (Un-partitioned) -------                            \n"
 "// -------------------------------------------------------------------         \n"
 "//  ThName : Name of the .msh file in Meshses/2D or  Meshses/3D folder         \n"
 "//=============================================================================\n";

if(top2vol)
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "// ------- Mesh parameters (Un-partitioned) -------                            \n"
 "// -------------------------------------------------------------------         \n"
 "//  PcName : Name of the point cloud                                           \n"
 "//  PcNx   : Number of points in x in the point cloud                          \n"
 "//  PcNy   : Number of points in x in the point cloud                          \n"
 "//  PcNz   : Number of points in x in the point cloud                          \n"
 "//  Dptz   : Depth in z for the mesh produced by top-ii-vol                    \n"
 "//  PartX  : Number of partitions in x direction                               \n"
 "//  PartY  : Number of partitions in y direction                               \n"
 "//  PartZ  : Number of partitions in z direction                               \n"
 "// -------------------------------------------------------------------         \n"
 "// Note that make sure PartX*PartY*PartZ = mpisize                             \n"
 "//=============================================================================\n";

 if(doublecouple=="force_based" || doublecouple=="displacement_based" && !top2vol)
  writeIt
  "                                                                             \n"
  "  string ThName = \"../Meshes/"<<spc<<"D/soil_dc.msh\";                      \n";

 if(doublecouple=="unused" && !top2vol)
  writeIt
  "                                                                             \n"
  "  string ThName = \"../Meshes/"<<spc<<"D/soil.msh\";                         \n";

 if(top2vol)
  writeIt
  "                                                                             \n"
  "  string PcName = \"../Meshes/"<<spc<<"D/Point-Cloud\";                      \n"
  "  macro PcNx() 63 //                                                         \n"
  "  macro PcNy() 57 //                                                         \n"
  "  macro PcNz() 29 //                                                         \n"
  "  macro Dptz() -1920.0 //                                                    \n"
  "  macro PartX() 1 //                                                         \n"
  "  macro PartY() mpisize //                                                   \n"
  "  macro PartZ() 1 //                                                         \n"
  "                                                                             \n";

 if(doublecouple=="displacement_based" || doublecouple=="force_based" || top2vol)
  writeIt
  "                                                                              \n"
  "//============================================================================\n"
  "//                   ------- Soil parameters -------                          \n"
  "// -------------------------------------------------------------------        \n"
  "//  rho : density of soil                                                     \n"
  "//  cp, cs : Primary and secondary wave velocities                            \n"
  "//  mu, lambda : Lame parameter of the soil                                   \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  real rho  = 1800.0 ,                                                        \n"
  "       cs   = 2300.  ,                                                        \n"
  "       cp   = 4000.  ;                                                        \n"
  "                                                                              \n"
  "  real    mu     =  cs*cs*rho,                                                \n"
  "          lambda =  cp*cp*rho - 2*mu;                                         \n"
  "                                                                              \n";
 else
  writeIt
  "                                                                              \n"
  "//============================================================================\n"
  "//                   ------- Soil parameters -------                          \n"
  "// -------------------------------------------------------------------        \n"
  "//  rho : density of soil                                                     \n"
  "//  cp, cs : Primary and secondary wave velocities                            \n"
  "//  mu, lambda : Lame parameter of the soil                                   \n"
  "//  E, nu : Modulus of Elasticity and Poisson ratio of the soil               \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  real rho  = 2500.0 ;                                                       \n"
  "                                                                             \n"
  "  real    mu                                                                 \n"
  "         ,lambda                                                             \n"
  "         ;                                                                   \n"
  "                                                                             \n"
  "{                                                                            \n"
  "  real E  = 6.62e6  ,                                                        \n"
  "       nu = 0.45    ;                                                        \n"
  "                                                                             \n"
  "  mu     = E/(2.*(1.+nu))            ;                                       \n"
  "  lambda = E*nu/((1.+nu)*(1.-2.*nu)) ;                                       \n"
  "}                                                                            \n"
  "  real cs   = sqrt(mu/rho)               ,                                   \n"
  "       cp   = sqrt((lambda+(2.*mu))/rho) ;                                   \n";


 if(TimeDiscretization=="generalized_alpha")
  writeIt
  "                                                                              \n"
  "//============================================================================\n"
  "//           ------- Time discretization parameters -------                   \n"
  "// -------------------------------------------------------------------        \n"
  "//  alpm, alpf : Generalized-alpha scheme constants                           \n"
  "//  t, tmax, dt : Time parameters, time, maximum time, and time step          \n"
  "//  gamma, beta : Time discretization constants (Newmark-beta)                \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  real alpm = 0.2     ,                                                      \n"
  "       alpf = 0.4     ,                                                      \n"
  "       tmax = 4.0     ,                                                      \n"
  "       t    = 0.01    ,                                                      \n"
  "       dt   = 0.01    ;                                                      \n"
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
  "//  t, tmax, dt : Time parameters, time, maximum time, and time step          \n"
  "//  gamma, beta : Time discretization constants (Newmark-beta)                \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  real tmax = 4.0     ,                                                      \n"
  "       t    = 0.01    ,                                                      \n"
  "       dt   = 0.01    ;                                                      \n"
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
  "//  t, tmax, dt : Time parameters, time, maximum time, and time step          \n"
  "//  gamma : Time discretization constant                                      \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  real tmax = 4.0     ,                                                      \n"
  "       t    = 0.01    ,                                                      \n"
  "       dt   = 0.01    ,                                                      \n"
  "       gamma = 0.5    ;                                                      \n"
  "                                                                             \n";

 if(TimeDiscretization=="hht_alpha")
  writeIt
  "                                                                              \n"
  "//============================================================================\n"
  "//           ------- Time discretization parameters -------                   \n"
  "// -------------------------------------------------------------------        \n"
  "//  alpf : HHT-alpha scheme constant                                          \n"
  "//  t, tmax, dt : Time parameters, time, maximum time, and time step          \n"
  "//  gamma, beta : Time discretization constants (Newmark-beta)                \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  real alpf = 0.4     ,                                                      \n"
  "       tmax = 4.0     ,                                                      \n"
  "       t    = 0.01    ,                                                      \n"
  "       dt   = 0.01    ;                                                      \n"
  "                                                                             \n"
  "  real gamma = 0.5 + alpf                ,                                   \n"
  "       beta  = (1./4.)*(gamma+0.5)^2     ;                                   \n"
  "                                                                             \n";


 writeIt
 "                                                                              \n"
 "//============================================================================\n"
 "//        -------Paraxial boundary-condition parameters-------                \n"
 "// -------------------------------------------------------------------        \n"
 "// PAlabels : is the vector of surface mesh labels that participate as        \n"
 "//            absorbing boundaries (via paraxial elements)                    \n"
 "//============================================================================\n"
 "                                                                              \n";

 if(spc==2)
  writeIt
  "  int [int]   PAlabels = [ 2 ,      // Left-border label                     \n"
  "                           4 ,      // Right-border label                    \n"
  "                           5 ];     // Bottom-border label                   \n";


 if(spc==3 && !top2vol)
  writeIt
  "  int [int]   PAlabels = [1,2,4,5];                                          \n";

 if(spc==3 && top2vol)
  writeIt
  "  int [int]   PAlabels = [1,2,4,5,6];                                        \n";

 if(doublecouple=="unused"){
  writeIt
 "                                                                              \n"
  "//============================================================================\n"
  "//        -------Paraxial boundary load-------                                \n"
  "// -------------------------------------------------------------------        \n"
  "// v1in : is a time dependent sinusoidal loading function ( traction )        \n"
  "//        which exists for time (tt <= 1 sec)                                 \n"
  "// LoadLabels : is the vector of surface mesh labels to which external        \n"
  "//              force is applied to                                           \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  real tt;                                                                    \n";

  if(spc==2)
   writeIt
   "  func v1in = (tt <= 1.0 ? real(sin(tt*(2.*pi/1.0)))*(x>20&&x<30) : 0. );    \n"
   "                                                                             \n"
   "  int [int]   LoadLabels = [ 5 ];     // Bottom-border label                 \n"
   "                                                                             \n";

  if(spc==3 && !top2vol)
   writeIt
   "  func v1in = (                                                               \n"
   "                 tt <= 1.0  ?                                                 \n"
   "                  real( sin(tt*(2.*pi/1.0))) *                                \n"
   "                  (x>10.&&x<40.) * (z>10.&&z<40.)                             \n"
   "                 :                                                            \n"
   "                   0.                                                         \n"
   "               );                                                             \n"
   "                                                                              \n"
   "  int [int]   LoadLabels = [4];                                               \n";

  if(spc==3 && top2vol)
   writeIt
   "  func v1in = (                                                               \n"
   "                 tt <= 1.0  ?                                                 \n"
   "                  real( sin(tt*(2.*pi/1.0))) *                                \n"
   "                  (x>875481.&&x<875681.) * (y>160200.&&y<160400.)             \n"
   "                 :                                                            \n"
   "                   0.                                                         \n"
   "               );                                                             \n"
   "                                                                              \n"
   "  int [int]   LoadLabels = [6];                                               \n";
  }

 if(doublecouple=="displacement_based" || doublecouple=="force_based"){
 writeIt
 "                                                                              \n"
 "//============================================================================\n"
 "//     -------Parameters for double couple point source-------                \n"
 "// -------------------------------------------------------------------        \n"
 "// DcNorthPointCord : is the vector  containing  coordinates of the           \n"
 "//                double couple north point. Idiom nomenclature ap-           \n"
 "//                lies to the south, east, and west points.                   \n"
 "// DcNorthCondition : is the macro containing the applied condition           \n"
 "//                of the double couple north point.                           \n"
 "//============================================================================\n"
 "                                                                              \n";

 if(spc==2)
 writeIt
 "                                                                              \n"
 "   real [int]   DcNorthPointCord = [5.,5.1];                                  \n"
 "   real [int]   DcSouthPointCord = [5.,5.];                                   \n"
 "   real [int]   DcEastPointCord  = [5.05,5.05];                               \n"
 "   real [int]   DcWestPointCord  = [4.95,5.05];                               \n"
 "                                                                              \n";

 if(spc==3)
 writeIt
 "                                                                              \n"
 "   real [int]   DcNorthPointCord = [877421.00,162180.00, -1441.071429];       \n"
 "   real [int]   DcSouthPointCord = [877421.00,162180.00, -1600.714286];       \n"
 "   real [int]   DcEastPointCord  = [877341.00,162180.00, -1520.892857];       \n"
 "   real [int]   DcWestPointCord  = [877501.00,162180.00, -1520.892857];       \n"
 "                                                                              \n";
 }

 if(doublecouple=="displacement_based")
 writeIt
 "                                                                              \n"
 "   macro DcNorthCondition() -0.5*(1.+tanh(8*(t-0.2)))//                       \n"
 "   macro DcSouthCondition()  0.5*(1.+tanh(8*(t-0.2)))//                       \n"
 "   macro DcEastCondition()   0.5*(1.+tanh(8*(t-0.2)))//                       \n"
 "   macro DcWestCondition()  -0.5*(1.+tanh(8*(t-0.2)))//                       \n"
 "                                                                              \n"
 "                                                                              \n";

 if(doublecouple=="force_based")
 writeIt
 "                                                                              \n"
 "   macro DcNorthCondition() rho*64.*tanh(8*(t-0.2))*(1.-(tanh(8*(t-0.2)))^2)//\n"
 "   macro DcSouthCondition()-rho*64.*tanh(8*(t-0.2))*(1.-(tanh(8*(t-0.2)))^2)//\n"
 "   macro DcEastCondition() -rho*64.*tanh(8*(t-0.2))*(1.-(tanh(8*(t-0.2)))^2)//\n"
 "   macro DcWestCondition()  rho*64.*tanh(8*(t-0.2))*(1.-(tanh(8*(t-0.2)))^2)//\n"
 "                                                                              \n"
 "                                                                              \n";

 writeIt
 "                                                                              \n";

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
   "  macro  Tbc"<<i<<"On 4   //                                               \n"
   "  macro  Tbc"<<i<<"Tx 10. //                                               \n";


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

