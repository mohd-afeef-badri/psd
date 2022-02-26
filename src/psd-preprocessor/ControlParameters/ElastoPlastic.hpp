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
 "  string ThName = \"../Meshes/"<<spc<<"D/quater_cylinder.msh\";               \n";

  writeIt
  "                                                                              \n"
  "//============================================================================\n"
  "//                   ------- Material parameters -------                      \n"
  "// -------------------------------------------------------------------        \n"
  "//  E, nu : Modulus of Elasticity and Poisson ratio of the material           \n"
  "//  sig0  : Yield strength of the material                                    \n"
  "//  Et    : Tangent modulus of the material                                   \n"
  "//  H     : Hardening modulus of the material                                 \n"
  "//  PropertyNames : String of material property names (space seperated)       \n"
  "//                  that are provided to Mfront.                              \n"
  "//  PropertyValues : Values of material properties provided to Mfront         \n"
  "//                                                                            \n"
  "// -------------------------------------------------------------------        \n"
  "//  NOTE:     Please note that PropertyNames should be the same as            \n"
  "//            as in the Elasticity.mfront file                                \n"
  "// -------------------------------------------------------------------        \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  real E    = 70.e3       ,                                                   \n"
  "       nu   = 0.3         ,                                                   \n"
  "       sig0 = 250.        ,                                                   \n"
  "       Et   = E/100.      ,                                                   \n"
  "       H    = E*Et/(E-Et) ;                                                   \n"
  "                                                                              \n"
  "                                                                              \n"
  "  real Re   = 1.3         ,  // external radius geometry                      \n"
  "       Ri   = 1.0         ;  // internal radius geometry                      \n"
  "                                                                              \n"
  "                                                                              \n"
  "  real Qlim = 2./sqrt(3.)*log(Re/Ri)*sig0; //  Limiting pressure              \n"
  "                                                                              \n"
  "                                                                              \n"
  "  string    MaterialBehaviour   = \"IsotropicLinearHardeningPlasticity\";     \n";

  if(spc==2)writeIt
  "  string    MaterialHypothesis  = \"GENERALISEDPLANESTRAIN\";                 \n";

  if(spc==3)writeIt
  "  string    MaterialHypothesis  = \"TRIDIMENSIONAL\";                         \n";

  writeIt
  "  string    PropertyNames       = \"YoungModulus PoissonRatio HardeningSlope YieldStrength\";\n"
  "  real[int] PropertyValues      = [ E, nu , H, sig0 ];                        \n"
  "                                                                              \n"
  "                                                                              \n"
  "//============================================================================\n"
  "//                   ------- Algorithmic parameters -------                   \n"
  "// -------------------------------------------------------------------        \n"
  "//  NrEpsCon : Newton-Raphsons Convergence epsilon                            \n"
  "//  NrMaxItr : Newton-Raphsons maximum iterations                             \n"
  "//  TlMaxItr : Number of time steps for quasi-time discretization             \n"
  "//                                                                            \n"
  "// -------------------------------------------------------------------        \n"
  "//  NOTE:     Please note that PropertyNames should be the same as            \n"
  "//            as in the Elasticity.mfront file                                \n"
  "// -------------------------------------------------------------------        \n"
  "//============================================================================\n"
  "                                                                              \n"
  "  macro EpsNrCon  ()   1.e-8       //                                         \n"
  "  macro NrMaxItr  ()   200         //                                         \n"
  "  macro TlMaxItr  ()   20          //                                         \n";

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

  writeIt
  "  real tl;       // Traction load to be updated in time loop                \n";
  for(int i=0; i<tractionconditions; i++)
   writeIt
   "  macro  Tbc"<<i<<"On  4           //                                      \n"
   "  macro  Tbc"<<i<<"Tx  Qlim*tl*N.x //                                      \n"
   "  macro  Tbc"<<i<<"Ty  Qlim*tl*N.y //                                      \n";

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

