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

cout << " building ControlParameters.edp";

{ofstream  write("ControlParameters.edp");

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
 "//  PcNx : Number of points in x in the point cloud                            \n"
 "//  PcNy : Number of points in x in the point cloud                            \n"
 "//  PcNz : Number of points in x in the point cloud                            \n"
 "//  Dptz : Depth in z for the mesh produced by top-ii-vol                      \n"
 "//=============================================================================\n";

if(Prblm=="linear-elasticity")
 writeIt
 "                                                                              \n"
 "  string ThName = \"../Meshes/"<<spc<<"D/bar\";                               \n";

if(Prblm=="damage" && Model=="hybrid-phase-field")
 writeIt
 "                                                                              \n"
 "  string ThName = \"../Meshes/"<<spc<<"D/tensile-crack\";                     \n";

if(Prblm=="elastodynamics")
 writeIt
 "                                                                              \n"
 "  string ThName = \"../Meshes/"<<spc<<"D/bar-dynamic\";                       \n";

if(Prblm=="damage" && Model=="Mazar")
 writeIt
 "                                                                              \n"
 "  string ThName = \"../Meshes/"<<spc<<"D/quasistatic\";                       \n";

if(Prblm=="soildynamics")
 {
 if(doublecouple=="force-based" || doublecouple=="displacement-based" && !top2vol)
  writeIt
  "                                                                             \n"
  "  string ThName = \"../Meshes/"<<spc<<"D/soil-dc\";                          \n";
 if(doublecouple=="unused" && !top2vol)
  writeIt
  "                                                                             \n"
  "  string ThName = \"../Meshes/"<<spc<<"D/soil\";                             \n";
 if(top2vol)
  writeIt
  "                                                                             \n"
  "  string PcName = \"../Meshes/"<<spc<<"D/Point-Cloud\";                      \n"
  "  macro PcNx() 63 //                                                         \n"
  "  macro PcNy() 57 //                                                         \n"
  "  macro PcNz() 29 //                                                         \n"
  "  macro Dptz() -1920.0 //                                                    \n"
  "                                                                             \n";
 }




if(Prblm=="linear-elasticity")
 {


 if(fastmethod)
  writeIt
  "                                                                              \n"
  "//============================================================================\n"
  "//                   ------- Material parameters -------                      \n"
  "// -------------------------------------------------------------------        \n"
  "//  mu, lambda : Lame parameter of the material                               \n"
  "//  E, nu : Modulus of Elasticity and Poisson ratio of the material           \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  real    mu                                                                  \n"
  "         ,lambda;                                                             \n"
  "                                                                              \n"
  "{                                                                             \n"
  "  real E  = 200.e9  ,                                                         \n"
  "       nu = 0.3     ;                                                         \n"
  "                                                                              \n"
  "  mu     = E/(2.*(1.+nu))            ;                                        \n"
  "  lambda = E*nu/((1.+nu)*(1.-2.*nu)) ;                                        \n"
  "}                                                                             \n";

 if(!fastmethod)
  {
  writeIt
  "                                                                              \n"
  "//============================================================================\n"
  "//              ------- Building material tensor-------                       \n"
  "// -------------------------------------------------------------------        \n"
  "//  mu, lambda : Lame parameter of the material                               \n"
  "//  E, nu : Modulus of Elasticity and Poisson ratio of the material           \n"
  "//  Mt : Material tensor                                                      \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  real a1,a2,a3        ;                                                      \n"
  "{                                                                             \n"
  "  real E  = 200.e9     ,                                                      \n"
  "       nu = 0.3        ;                                                      \n"
  "                                                                              \n"
  "       a1 = E*(1.-nu)/((1.+nu)*(1.-2.*nu))   ;                                \n"
  "       a2 = a1*nu/(1.-nu)                    ;                                \n"
  "       a3 = E/(2*(1.+nu))                    ;                                \n"
  "}                                                                             \n";

 if(spc==2)
  writeIt
  "                                                                              \n"
  "  macro Mt   [[ a1 ,  a2 , 0 ],                                               \n"
  "              [ a2 ,  a1 , 0 ],                                               \n"
  "              [ 0  ,  0  , a3]]//                                             \n";

 if(spc==3)
  writeIt
  "                                                                              \n"
  "  macro Mt   [[ a1 ,  a2 , a2 , 0  , 0  , 0 ],                                \n"
  "              [ a2 ,  a1 , a2 , 0  , 0  , 0 ],                                \n"
  "              [ a2 ,  a2 , a1 , 0  , 0  , 0 ],                                \n"
  "              [ 0  ,  0  , 0  , a3 , 0  , 0 ],                                \n"
  "              [ 0  ,  0  , 0  , 0  , a3 , 0 ],                                \n"
  "              [ 0  ,  0  , 0  , 0  , 0  , a3]]//                              \n";
  }
 }




if(Prblm=="damage")
 {

 if(Model=="Mazar")
  writeIt
 "                                                                              \n"
 "//============================================================================\n"
 "//                   ------- Material parameters -------                      \n"
 "// -------------------------------------------------------------------        \n"
 "//  mu, lambda : Lame parameter of the Material                               \n"
 "//  E, nu : Modulus of Elasticity and Poisson ratio of the Material           \n"
 "//  kappa0 : Damage initiation threshold of the Material                      \n"
 "//  kappac :  Critical strain level of the Material                           \n"
 "//============================================================================\n"
  "                                                                              \n"
  "  real    mu                                                                  \n"
  "         ,lambda                                                              \n"
  "         ,kappa0 = 1.e-4                                                      \n"
  "         ,kappac = 1.e-3                                                      \n"
  "         ;                                                                    \n"
  "                                                                              \n"
  "{                                                                             \n"
  "  real E  = 100.e6  ,                                                         \n"
  "       nu = 0.2     ;                                                         \n"
  "                                                                              \n"
  "  mu     = E/(2.*(1.+nu))            ;                                        \n"
  "  lambda = E*nu/((1.+nu)*(1.-2.*nu)) ;                                        \n"
  "}                                                                             \n"
  "                                                                              \n"
  "//============================================================================\n"
  "//                  ------- Solver parameters -------                         \n"
  "// -------------------------------------------------------------------        \n"
  "//  tol : Tolerance of the Newton-Raphsons procedure                          \n"
  "//  npas : # of pseudo-time steps                                             \n"
  "//  iterMaxNR : Max # of iterations for the NR loop                           \n"
  "//  Duimp :  Imposed displacement variation                                   \n"
  "//  duimp :  Dummy Imposed displacement variation                             \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  real tol      = 1.e-5 ;                                                     \n"
  "                                                                              \n"
  "  int npas      = 2000  ,                                                     \n"
  "      iterMaxNR = 10    ;                                                     \n"
  "                                                                              \n"
  "  real Duimp = 2.e-7,                                                         \n"
  "       duimp        ;                                                         \n";


 if(Model=="hybrid-phase-field")
  writeIt
 "                                                                              \n"
 "//============================================================================\n"
 "//                   ------- Material parameters -------                      \n"
 "// -------------------------------------------------------------------        \n"
 "//  mu, lambda : Lame parameter of the material                               \n"
 "//  Gc : Material fracture toughness                                          \n"
 "//  kappa0 : Damage initiation threshold of the Material                      \n"
 "//  kappac :  Critical strain level of the Material                           \n"
 "//============================================================================\n"
  "                                                                              \n"
  "  real lambda = 121.15e3 ,                                                    \n"
  "       mu     = 80.77e3  ,                                                    \n"
  "       Gc     = 2.7      ;                                                    \n"
  "                                                                              \n"
  "//============================================================================\n"
  "//                  ------- Solver parameters -------                         \n"
  "// -------------------------------------------------------------------        \n"
  "//  lfac : # of cells within which fracture diffusion occurs                  \n"
  "//  maxtr : Maximum traction force applied                                    \n"
  "//  tr : Traction force applied                                               \n"
  "//  dtr :  Change in traction force between two pseudo-time steps             \n"
  "//  lo :  Mesh dependent lateral fracture length                              \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  real lfac  = 2.0  ,                                                         \n"
  "       maxtr = 7e-3 ,                                                         \n"
  "       tr    = 1e-5 ,                                                         \n"
  "       dtr   = 1e-5 ,                                                         \n"
  "       lo           ;                                                         \n";

 }



if(Prblm=="elastodynamics")
 {
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

 if(TimeDiscretization=="generalized-alpha")
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

 if(TimeDiscretization=="newmark-beta")
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

 if(TimeDiscretization=="central-difference")
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

 if(TimeDiscretization=="hht-alpha")
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

}


if(Prblm=="soildynamics")
 {


 if(doublecouple=="displacement-based" || doublecouple=="force-based" || top2vol)
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


 if(TimeDiscretization=="generalized-alpha")
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

 if(TimeDiscretization=="newmark-beta")
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

 if(TimeDiscretization=="central-difference")
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

 if(TimeDiscretization=="hht-alpha")
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
  "  int [int]   PAlabels = [1,2,3,5];                                          \n";

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
   "                  (x>10.&&x<40.) * (y>10.&&y<40.)                             \n"
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

 if(doublecouple=="displacement-based" || doublecouple=="force-based"){
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

 if(doublecouple=="displacement-based")
 writeIt
 "                                                                              \n"
 "   macro DcNorthCondition() -0.5*(1.+tanh(8*(t-0.2)))//                       \n"
 "   macro DcSouthCondition()  0.5*(1.+tanh(8*(t-0.2)))//                       \n"
 "   macro DcEastCondition()   0.5*(1.+tanh(8*(t-0.2)))//                       \n"
 "   macro DcWestCondition()  -0.5*(1.+tanh(8*(t-0.2)))//                       \n"
 "                                                                              \n"
 "                                                                              \n";

 if(doublecouple=="force-based")
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
 }

if(dirichletconditions>=1)
 {
 writeIt
 "                                                                              \n"
 "//============================================================================\n"
 "// -------Dirichlet boundary-condition parameters-------                      \n"
 "//============================================================================\n"
 "                                                                              \n";

 int trickLoop = 1;
 if(Prblm=="damage") trickLoop = 2;

 if(spc==2)
 writeIt
 "                                                                              \n"
 " //------------NAME------------LABEL----CONDITION(S)-----//                   \n"
 "   macro  DirichletBorder0       "<<labelDirichlet<<",      Ux=0, Uy=0      //\n";
 for(int i=trickLoop; i<dirichletconditions; i++)
  writeIt
 "   macro  DirichletBorder"<<i<<"       "<<labelDirichlet<<",      Ux=0, Uy=0      //\n";

 if(spc==3)
 writeIt
 "                                                                              \n"
 " //------------NAME------------LABEL----CONDITION(S)-----//                   \n"
 "   macro  DirichletBorder0       "<<labelDirichlet<<",      Ux=0, Uy=0, Uz=0//\n";
 for(int i=trickLoop; i<dirichletconditions; i++)
  writeIt
 "   macro  DirichletBorder"<<i<<"       "<<labelDirichlet<<",      Ux=0, Uy=0, Uz=0//\n";

 if(Prblm=="damage" && Model=="hybrid-phase-field")
 writeIt
 "   macro  DirichletBorder1       2,      Uy=tr           //                   \n"
 " //macro  DirichletBorder2       33,     Ux=1, Uy=12     //                   \n"
 " //macro  DirichletBorder3       1,2,3   Ux=0            //                   \n"
 " //macro  DirichletBorder4       1,2,3   Ux=x + y*(x<1.) //                   \n"
 "                                                                              \n";
 else
 writeIt
 " //macro  DirichletBorder1       1,2     Ux=1, Uy=0      //                   \n"
 " //macro  DirichletBorder2       33,     Ux=1, Uy=12     //                   \n"
 " //macro  DirichletBorder3       1,2,3   Ux=0            //                   \n"
 " //macro  DirichletBorder4       1,2,3   Ux=x + y*(x<1.) //                   \n"
 "                                                                              \n";
 }



if(dirichletpointconditions>=1)
 {
 writeIt
 "                                                                              \n"
 "//============================================================================\n"
 "//       -------Dirichlet point boundary-condition parameters-------          \n"
 "// -------------------------------------------------------------------------- \n"
 "// PC : short for point coordinates is the table  containing coordinates of   \n"
 "//      the  points for which boundary-condition is to be applied             \n"
 "// PC(I)Ux  : is x displacement value of the point I. Similar logic applies   \n"
 "//            to PC(I)Uy, PC(I)Uz                                             \n"
 "// -------------------------------------------------------------------------- \n"
 "// NOTE: either the macro PC(I)Ux or PC(I)Uy or PC(I)Uz should be commented   \n"
 "//       if the user does not wish to apply restriction on that  particular   \n"
 "//       displacement direction (let it free)                                 \n"                               
 "//============================================================================\n"
 "                                                                              \n"
 "  real[int,int] PC = [                                                        \n"; 

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
 "   macro PC"<<i<<"Ux  -0. //                                                  \n"
 "   macro PC"<<i<<"Uy  -0. //                                                  \n" 
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
 "   macro PC"<<i<<"Ux  -0. //                                                  \n"
 "   macro PC"<<i<<"Uy  -0. //                                                  \n" 
 "   macro PC"<<i<<"Uz  -0. //                                                  \n"  
 "                                                                              \n"; 
  
 }
}


if(tractionconditions>=1)
 {
 writeIt
 "                                                                              \n"
 "//============================================================================\n"
 "// ------- Neumann/traction boundary-condition parameters -------             \n"
 "// -------------------------------------------------------------------        \n"
 "// Tb        : acronym for traction border                                    \n" 
 "// Labs      : acronym for traction labels                                    \n"  
 "// Tb(I)Labs : is/are the  surface  labels tags (integers) to which           \n"
 "//             traction boundary conditions is to be applied.                 \n"
 "// Tb(I)Tx   : is the x component of traction forces on the surface           \n"
 "//             border (I) denoted by  label Tb(I)Labs.                        \n"
 "// -------------------------------------------------------------------------- \n"
 "// NOTE: either the macro Tb(I)Tx or Tb(I)Ty or Tb(I)Tz should be commented   \n"
 "//       or deleted  if  the  user  does not wish to apply traction on that   \n"
 "//       particular  direction (let it free)                                  \n" 
 "//============================================================================\n"
 "                                                                              \n";

 if(spc==2)if(Prblm!="elastodynamics")
  for(int i=0; i<tractionconditions; i++)
   writeIt
   "  macro  Tb"<<i<<"Labs 4   //                                             \n"   
   "  macro  Tb"<<i<<"Tx   10. //                                             \n"
   "//macro  Tb"<<i<<"Ty   0.  //                                             \n";

  if(Prblm=="elastodynamics")
  for(int i=0; i<tractionconditions; i++)
   writeIt
   "  macro  Tb"<<i<<"Labs 4   //                                             \n"   
   "  macro  Tb"<<i<<"Ty   tt/0.8*(tt <= 0.8)+ 0.*(tt > 0.8) //               \n";

 if(spc==3)if(Prblm!="elastodynamics")
  for(int i=0; i<tractionconditions; i++)
   writeIt
   "  macro  Tb"<<i<<"Labs 4   //                                             \n"   
   "  macro  Tb"<<i<<"Tx   10. //                                             \n"
   "//macro  Tb"<<i<<"Ty   10. //                                             \n"
   "//macro  Tb"<<i<<"Tz   0   //                                             \n";     
 }

if(bodyforce)
 {
 writeIt
 "                                                                              \n"
 "//============================================================================\n"
 "//        ------- volumetric bodyforce  parameters -------                    \n"
 "// -------------------------------------------------------------------        \n"
 "// fx, fy, fz : are the components of body force in x, y, and z axis.         \n"
 "//              Note that these can be finite element fields as well.         \n"
 "//============================================================================\n"
 "                                                                              \n"
 "  macro fx  0.         //                                                     \n"
 "  macro fy  -78480.0   //  {/rho*g=8.e3*(-9.81)=-78480.0}                     \n";
 if(spc==3)
  writeIt
  "  macro fz  0.       //                                                      \n"
  "                                                                             \n";
 }

writeIt
"                                                                               \n"
"//=============================================================================\n"
"// ------- Solver control parameters -------                                   \n"
"//=============================================================================\n"
"                 // TO DO                                                      \n"
"                                                                               \n";

} //-- [ostream terminator]  ControlParameters.edp closed --//

cout << " ........................ Done \n";

