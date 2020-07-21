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

writeIt
"                                                                               \n"
"//=============================================================================\n"
"// ------- Mesh parameters (Un-partitioned) -------                            \n"
"//=============================================================================\n";


if(Prblm=="linear-elasticity")
 writeIt
 "                                                                              \n"
 "  string ThName = \"../Meshes/"<<spc<<"D/bar\";  // Mesh  name                \n";

if(Prblm=="damage" && Model=="hybrid-phase-field")
 writeIt
 "                                                                              \n"
 "  string ThName = \"../Meshes/"<<spc<<"D/tensile-crack\"; // Mesh  name       \n";

if(Prblm=="elastodynamics")
 writeIt
 "                                                                              \n"
 "  string ThName = \"../Meshes/"<<spc<<"D/bar-dynamic\"; // Mesh  name         \n";

if(Prblm=="damage" && Model=="Mazar")
 writeIt
 "                                                                              \n"
 "  string ThName = \"../Meshes/"<<spc<<"D/quasistatic\"; // Mesh  name         \n";

if(Prblm=="soildynamics")if(!doublecouple)
 writeIt
 "                                                                              \n"
 "  string ThName = \"../Meshes/"<<spc<<"D/soil\";       // Mesh  name          \n";

if(Prblm=="soildynamics")if(doublecouple)
 writeIt
 "                                                                              \n"
 "  string ThName = \"../Meshes/"<<spc<<"D/soil-dc\";       // Mesh  name       \n"; 




if(Prblm=="linear-elasticity")
 {
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "// ------- Material parameters -------                                         \n"
 "//=============================================================================\n"
 "                                                                               \n";

 if(fastmethod)
  writeIt
  "  real    mu                        // Lame parameter                         \n"
  "         ,lambda;                   // Lame parameter                         \n"
  "                                                                              \n"
  "{                                                                             \n"
  "  real E  = 200.e9  ,                // Modulus of Elasticity - [Pa]          \n"
  "       nu = 0.3     ;                // Poisson ratio - [-]                   \n"
  "                                                                              \n"
  "  mu     = E/(2.*(1.+nu))            ;                                        \n"
  "  lambda = E*nu/((1.+nu)*(1.-2.*nu)) ;                                        \n"
  "}                                                                             \n";

 if(!fastmethod)
  {
  writeIt
  "                                                                              \n"
  "  real a1,a2,a3        ;                // Building material tensor           \n"
  "{                                                                             \n"
  "  real E  = 200.e9     ,                // Modulus of Elasticity - [Pa]       \n"
  "       nu = 0.3        ;                // Poisson ratio - [-]                \n"
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
  "              [ 0  ,  0  , a3]]               // Material tensor              \n";
 
 if(spc==3)
  writeIt
  "                                                                              \n"
  "  macro Mt   [[ a1 ,  a2 , a2 , 0  , 0  , 0 ],                                \n"
  "              [ a2 ,  a1 , a2 , 0  , 0  , 0 ],                                \n"
  "              [ a2 ,  a2 , a1 , 0  , 0  , 0 ],                                \n"
  "              [ 0  ,  0  , 0  , a3 , 0  , 0 ],                                \n"
  "              [ 0  ,  0  , 0  , 0  , a3 , 0 ],                                \n"
  "              [ 0  ,  0  , 0  , 0  , 0  , a3]]// Material tensor              \n";
  }
 }




if(Prblm=="damage")
 {
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "// ------- Material parameters -------                                         \n"
 "//=============================================================================\n";

 if(Model=="Mazar")
  writeIt
  "                                                                              \n"
  "  real    mu                        // Lame parameter                         \n"
  "         ,lambda                    // Lame parameter                         \n"
  "         ,kappa0 = 1.e-4            // Damage initiation threshold            \n"
  "         ,kappac = 1.e-3            // Critical strain level                  \n"
  "         ;                                                                    \n"
  "                                                                              \n"
  "{                                                                             \n"
  "  real E  = 100.e6  ,              // Modulus of Elasticity - [Pa]            \n"
  "       nu = 0.2     ;              // Poisson ratio - [-]                     \n"
  "                                                                              \n"
  "  mu     = E/(2.*(1.+nu))            ;                                        \n"
  "  lambda = E*nu/((1.+nu)*(1.-2.*nu)) ;                                        \n"
  "}                                                                             \n"
  "                                                                              \n"
  "//============================================================================\n"
  "// ------- Solver parameters -------                                          \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  real tol      = 1.e-5 ;          // Tolerance of the NR procedure           \n"
  "                                                                              \n"
  "  int npas      = 2000  ,          // # of pseudo-time steps                  \n"
  "      iterMaxNR = 10    ;          // Max # of iterations for the NR loop     \n"
  "                                                                              \n"
  "//============================================================================\n"
  "// ------- Loading parameters -------                                         \n"
  "//============================================================================\n"
  "  real Duimp = 2.e-7,              // Imposed displacement variation          \n"
  "       duimp        ;              // Dummy Imposed displacement variation    \n";


 if(Model=="hybrid-phase-field")
  writeIt
  "                                                                              \n"
  "  real lambda = 121.15e3 ,                                                    \n"
  "       mu     = 80.77e3  ;                                                    \n"
  "                                                                              \n"
  "//============================================================================\n"
  "// ------- Nonlinear parameters -------                                       \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  real Gc    = 2.7  ,                                                         \n"
  "       lfac  = 2.0  ,                                                         \n"
  "       maxtr = 7e-3 ,                                                         \n"
  "       tr    = 1e-5 ,                                                         \n"
  "       dtr   = 1e-5 ,                                                         \n"
  "       lo           ;        // Calculated in OtherParameters.edp             \n";

 }



if(Prblm=="elastodynamics")
 {
 writeIt
 "                                                                              \n"
 "//============================================================================\n"
 "// ------- Material parameters -------                                        \n"
 "//============================================================================\n"
 "                                                                              \n"
 "  real lambda = 576.9230769  ,           // E=1000. & nu=0.3                  \n"
 "       mu     = 384.6153846  ;           // E=1000. & nu=0.3                  \n"
 "                                                                              \n"
 "//============================================================================\n"
 "// ------- Dynamic parameters -------                                         \n"
 "//============================================================================\n"
 "                                                                              \n";

 if(TimeDiscretization=="generalized-alpha")
  writeIt
  "  real rho  = 1.0  ,                                                         \n"
  "       etam = 0.01 ,                                                         \n"
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
  "  real rho  = 1.0  ,                                                         \n"
  "       etam = 0.01 ,                                                         \n"
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
  "  real rho  = 1.0  ,                                                         \n"
  "       etam = 0.01 ,                                                         \n"
  "       etak = 0.01 ,                                                         \n"
  "       tmax = 4.0  ,                                                         \n"
  "       t    = 0.08 ,                                                         \n"
  "       dt   = 0.08 ,                                                         \n"
  "       gamma = 0.5 ;                                                         \n"
  "                                                                             \n";

 if(TimeDiscretization=="hht-alpha")
  writeIt
  "  real rho  = 1.0  ,                                                         \n"
  "       etam = 0.01 ,                                                         \n"
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
 writeIt
 "                                                                              \n"
 "//============================================================================\n"
 "// ------- Soil parameters -------                                            \n"
 "//============================================================================\n"
 "                                                                              \n"
 "  real rho  = 2500.0 ;              // Density                                \n"
 "                                                                              \n"
 "  real    mu                        // Lame parameter                         \n"
 "         ,lambda                    // Lame parameter                         \n"
 "         ;                                                                    \n"
 "                                                                              \n"
 "{                                                                             \n"
 "  real E  = 6.62e6  ,                // Modulus of Elasticity - [Pa]          \n"
 "       nu = 0.45    ;                // Poisson ratio - [-]                   \n"
 "                                                                              \n"
 "  mu     = E/(2.*(1.+nu))            ;                                        \n"
 "  lambda = E*nu/((1.+nu)*(1.-2.*nu)) ;                                        \n"
 "}                                                                             \n"
 "  real cs   = sqrt(mu/rho)               ,                                    \n"
 "       cp   = sqrt((lambda+(2.*mu))/rho) ;                                    \n"
 "                                                                              \n"
 "//============================================================================\n"
 "// ------- Dynamic parameters -------                                         \n"
 "//============================================================================\n"
 "                                                                              \n";

 if(TimeDiscretization=="generalized-alpha")
  writeIt
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
  "  real tmax = 4.0     ,                                                      \n"
  "       t    = 0.01    ,                                                      \n"
  "       dt   = 0.01    ;                                                      \n"
  "                                                                             \n"
  "  real gamma = 0.5                       ,                                   \n"
  "       beta  = (1./4.)*(gamma+0.5)^2     ;                                   \n"
  "                                                                             \n";

 if(TimeDiscretization=="central-difference")
  writeIt
  "  real tmax = 4.0     ,                                                      \n"
  "       t    = 0.01    ,                                                      \n"
  "       dt   = 0.01    ,                                                      \n"
  "       gamma = 0.5    ;                                                      \n"
  "                                                                             \n";

 if(TimeDiscretization=="hht-alpha")
  writeIt
  "  real alpf = 0.4     ,                                                      \n"
  "       tmax = 4.0     ,                                                      \n"
  "       t    = 0.01    ,                                                      \n"
  "       dt   = 0.01    ;                                                      \n"
  "                                                                             \n"
  "  real gamma = 0.5 + alpf                ,                                   \n"
  "       beta  = (1./4.)*(gamma+0.5)^2     ;                                   \n"
  "                                                                             \n";


 writeIt
 "//============================================================================\n"
 "//        -------Paraxial boundary-condition parameters-------                \n"
 "// -------------------------------------------------------------------        \n"
 "// PAlabels : is the vector of surface mesh labels that participate as        \n"
 "//            absorbing boundaries (via paraxial elements)                    \n"
 "// LoadLabels : is the vector of surface mesh labels to which external        \n"
 "//              force is applied to                                           \n"
 "// v1in : is a time dependent sinusoidal loading function ( traction )        \n"
 "//        which exists for time (tt <= 1 sec)                                 \n"
 "//============================================================================\n"
 "                                                                              \n";

 if(spc==2)
  writeIt
  "  int [int]   PAlabels = [ 2 ,      // Left-border label                     \n"
  "                           4 ,      // Right-border label                    \n"
  "                           5 ];     // Bottom-border label                   \n"
  "                                                                             \n"
  "  int [int]   LoadLabels = [ 5      // Bottom-border label                   \n"
  "                              ];                                             \n"
  "  real tt;                                                                   \n"
  "  func v1in = (tt <= 1.0 ? real(sin(tt*(2.*pi/1.0)))*(x>20&&x<30) : 0. );    \n";

 if(spc==3)
  writeIt
  "  int [int]   PAlabels = [1,2,3,5];                                          \n"
  "  int [int]   LoadLabels = [4];                                              \n"
  "  real tt;                                                                   \n"
  "  func v1in = (tt <= 1.0 ? real(sin(tt*(2.*pi/1.0)))*(x>10&&x<40)*(z>10&&z<40) : 0. );\n"
  "                                                                               \n";

 if(doublecouple)
 writeIt
 "//============================================================================\n"
 "//     -------Parameters for double couple point source-------                \n"
 "// -------------------------------------------------------------------        \n"
 "// DcLabelNorth : is the label of the (line/surface) containing the           \n"
 "//                double couple north point. North point is  loaded           \n"
 "//                in x direction. Idiom nomenclature applies to the           \n"
 "//                south, east, and west points. (S/W loaded in z).            \n"
 "// DcNorthPointCord : is the vector  containing  coordinates of the           \n"
 "//                double couple north point. Idiom nomenclature ap-           \n" 
 "//                lies to the south, east, and west points.                   \n"
 "// DcNorthCondition : is the macro containing the applied condition           \n"
 "//                of the double couple north point.                           \n"     
 "//============================================================================\n"
 "                                                                              \n"
 "   int  DcLabelNorth = 6,                                                     \n"
 "        DcLabelSouth = 7,                                                     \n"
 "        DcLabelEast  = 7,                                                     \n"
 "        DcLabelWest  = 6;                                                     \n"  
 "                                                                              \n"
 "                                                                              \n" 
 "   int [int]   DcNorthPointCord = [5,6];                                      \n"
 "   int [int]   DcSouthPointCord = [5,5];                                      \n"
 "   int [int]   DcEastPointCord  = [5.5,5.5];                                  \n"
 "   int [int]   DcWestPointCord  = [4.5,5.5];                                  \n"     
 "                                                                              \n"
 "                                                                              \n"
 "   macro DcNorthCondition() 100.  //                                          \n"
 "   macro DcSouthCondition() 100.  //                                          \n"
 "   macro DcEastCondition()  100.  //                                          \n"
 "   macro DcWestCondition()  100.  //                                          \n"   
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
 "                                                                              \n"
 "  int [int]   Dlabel = ["<<labelDirichlet<<"\t// Label for Dirichlet border 0 \n";

 for(int i=1; i<dirichletconditions; i++)
  writeIt
  "                       ,"<<labelDirichlet<<"\t// Label Dirichlet border "<<i<<"\n";

 writeIt
 "                       ];                                                     \n"
 "                                                                              \n";


 if(spc==2)
  {
  writeIt
  "  real[int]   Dvalue = [ 0., 0.        // u1,u2 of Dirichlet border 0        \n";
  for(int i=1; i<dirichletconditions; i++)
   writeIt
   "                        ,0., 0.        // u1,u2 of Dirichlet border "<<i<<" \n";
  }

 if(spc==3)
  {
  writeIt
  "  real[int]   Dvalue = [ 0., 0., 0.  // u1,u2,u3 of Dirichlet border 0       \n";
  for(int i=1; i<dirichletconditions; i++)
   writeIt
   "                        ,0., 0., 0. // u1,u2,u3 of Dirichlet border "<<i<<" \n";
  }

 writeIt
 "                       ];                                                     \n"
 "                                                                              \n";
 }

if(dirichletpointconditions>=1)
 {
 writeIt
 "                                                                              \n"
 "//============================================================================\n"
 "// -------Dirichlet point boundary-condition parameters-------                \n"
 "//============================================================================\n"
 "                                                                              \n"
 "  int [int]   Dpointlab = ["<<labelDirichlet<<"\t// Labels containing point 0 \n";


 for(int i=1; i<dirichletpointconditions; i++)
  writeIt
  "                          ,"<<labelDirichlet<<"\t//  Labels containing point "<<i<<" \n";

 writeIt
 "                          ];                                                  \n"
 "                                                                              \n";


 if(spc==2)
 {
 writeIt
 "  real[int]   PnV = [ 0., 0., 0., 0. // [x, y, u1, u2] of point border 0      \n";
 for(int i=1; i<dirichletpointconditions; i++)
  writeIt
  "                     ,0., 0., 0., 0. // [x, y, u1, u2] of point border "<<i<<"\n";
 }

 if(spc==3)
 {
 writeIt
 "  real[int]   PnV = [ 0., 0., 0., 0., 0., 0.  // [x,y,z,u1,u2,u3] of point 0  \n";
 for(int i=1; i<dirichletpointconditions; i++)
  writeIt
  "                     ,0., 0., 0., 0., 0., 0. // [x,y,z,u1,u2,u3] of point "<<i<<" \n";
 }

 writeIt
 "                    ];                                                        \n"
 "                                                                              \n";
}


if(tractionconditions>=1)
 {
 writeIt
 "                                                                              \n"
 "//============================================================================\n"
 "// ------- Neumann/traction boundary-condition parameters -------             \n"
 "//============================================================================\n"
 "                                                                              \n"
 "  int [int]   Tlabel = [ 4             //  Label for traction border 1        \n";                     

 for(int i=1; i<tractionconditions; i++)
  writeIt
  "                        ,4             //  Label for traction border "<<i<<" \n";

 writeIt
 "                       ];                                                     \n"
 "                                                                              \n"
 "                                                                              \n";

 if(spc==2)
  {
  for(int i=0; i<tractionconditions; i++)
   writeIt
   "  real  tx"<<i<<"=0, ty"<<i<<"=10.;\t\t\t// Traction forces on label "<<i<<"\n";

  writeIt
  "                                                                             \n"
  "  macro T(i,j) [i,j]                        // Traction vector               \n"; 
  }


 if(spc==3)
  {
  for(int i=0; i<tractionconditions; i++)
   writeIt
   "  real tx"<<i<<"=0, ty"<<i<<"=0, tz"<<i<<"=0 ;// Component traction  on label "<<i<<" \n";

  writeIt
  "  macro T(i,j,k) [i,j,k]                // Three component traction forces   \n"; 
  }
 }

if(Prblm=="elastodynamics")
 writeIt
 "                                                                              \n"
 "//============================================================================\n"
 "// ------- Neumann boundary-condition parameters -------                      \n"
 "//============================================================================\n"
 "                                                                              \n"
 "  real tt;                                                                    \n"
 "  func tr = (tt <= 0.8 ? real(1.*tt/0.8) : 0. );    // tr is dynamic loading  \n"
 "                                                                              \n";


if(bodyforce)
 {
 writeIt
 "                                                                              \n"
 "//============================================================================\n"
 "// ------- Bodyforce  parameters -------                                      \n"
 "//============================================================================\n"
 "                                                                              \n"
 "  real f1 = 0.;                      // X component body forces               \n"
 "  real f2 = 8.e3*(-9.81);            // Y component body forces               \n";

 if(spc==2)
  writeIt
  "                                                                             \n"
  "  macro BF [f1,f2]                   // Two component body forces            \n"; 

 if(spc==3)
  writeIt
  "  real f3 = 0.;                      // Z component body forces              \n"
  "                                                                             \n"
  "  macro BF [f1,f2,f3]                // Three component body forces          \n"; 
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

