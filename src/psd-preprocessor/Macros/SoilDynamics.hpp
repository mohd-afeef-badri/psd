/**************************************************************************************
*                                                                                     *
* Author : Mohd Afeef BADRI                                                           *
* Email  : mohd-afeef.badri@cea.fr                                                    *
* Date   : 20/04/2020                                                                 *
* Type   : Support file                                                               *
*                                                                                     *
* Comment: This support  file is responsible for generating Macro.edp  which contains *
*           main macros compiletime/runtime for PSD solver.                           *
*                                                                                     *
**************************************************************************************/

writeHeader;

if(spc==2)
 {

 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "//                     ------- Essential Macros -------                        \n"
 "// --------------------------------------------------------------------------- \n";
 if(!Sequential)writeIt
 "// partitioner : mesh partitioner to be used use metis, parmetis, or scotch    \n"
 "// dimension   : dimension of the problem 2 or 3 for 2D or 3D                  \n";
 writeIt
 "// Ux, Uy      : x and y displacements                                         \n"
 "// Pk          : finite element space definition                               \n"
 "// def(i)      : to define a vectorial field                                   \n"
 "// init(i)     : to initialize a vectorial field                               \n"
 "//=============================================================================\n"
 "                                                                               \n";

 if(!Sequential)
 writeIt
 "  macro partitioner "<<Partitioner<<" //                                       \n"
 "  macro dimension 2 //                                                         \n";

 if(ParaViewPostProcess)
 writeIt
 "  macro PlotVec(i) [ i   ,                                                      \n"
 "                     i#1 ,                                                      \n"
 "                     0   ] //                                                   \n"
 "                                                                                \n";

 if(Model=="Hujeux")
 writeIt
 "                                                                                \n"
 "  macro Sk [ FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ] // Quadrature element space order 3                        \n"
 "                                                                                \n"
 "  macro defSh(i) [ i   ,                                                        \n"
 "                   i#1 ,                                                        \n"
 "                   i#2 ] // 3rd order Vect. field definition                    \n"
 "                                                                                \n"
 "  macro Ik [ FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ,                                                            \n"
 "             FEQF1 ] // Quadrature element space order 25                       \n"
 "                                                                                \n"
 "  macro defIh(i) [ i    ,                                                       \n"
 "                   i#1  ,                                                       \n"
 "                   i#2  ,                                                       \n"
 "                   i#3  ,                                                       \n"
 "                   i#4  ,                                                       \n"
 "                   i#5  ,                                                       \n"
 "                   i#6  ,                                                       \n"
 "                   i#7  ,                                                       \n"
 "                   i#8  ,                                                       \n"
 "                   i#9  ,                                                       \n"
 "                   i#10 ,                                                       \n"
 "                   i#11 ,                                                       \n"
 "                   i#12 ,                                                       \n"
 "                   i#13 ,                                                       \n"
 "                   i#14 ,                                                       \n"
 "                   i#15 ,                                                       \n"
 "                   i#16 ,                                                       \n"
 "                   i#17 ,                                                       \n"
 "                   i#18 ,                                                       \n"
 "                   i#19 ,                                                       \n"
 "                   i#20 ,                                                       \n"
 "                   i#21 ,                                                       \n"
 "                   i#22 ,                                                       \n"
 "                   i#23 ,                                                       \n"
 "                   i#24 ] // 25th order Vect. field definition                  \n"
 "                                                                                \n"
 "  macro calculateStress(i,j,lambdaVal,muVal)                                    \n"
 "     defSh(i) = [ lambdaVal*(dx(j)+dy(j#1))+2.*muVal*dx(j)   ,                  \n"
 "                  lambdaVal*(dx(j)+dy(j#1))+2.*muVal*dy(j#1) ,                  \n"
 "                  2.*muVal*(dx(j#1)+dy(j))                   ]; //              \n"
 "                                                                                \n"
 "  macro calculateStrain(i,j)                                                    \n"
 "     defSh(i) = [ dx(j)               ,                                         \n"
 "                  dy(j#1)             ,                                         \n"
 "                  0.5*(dx(j#1)+dy(j)) ];  //                                    \n"
 "                                                                                \n"
 "  macro Epsl(i) [ dx(i)              ,                                          \n"
 "                  dy(i#1)            ,                                          \n"
 "                  (dy(i)+dx(i#1))/2. ]   // Strain definition                   \n"
 "                                                                                \n";


 if(!vectorial)
  {

  writeIt
  "  macro Pk     [ P"<<lag<<" ,                                                  \n"
  "                 P"<<lag<<" ] //                                               \n"
  "                                                                               \n";

  writeIt
  "  macro def(i) [ i   ,                                                         \n"
  "                 i#1 ] //                                                      \n"
  "                                                                               \n";

  if(!Sequential)
  writeIt
  "  macro init(i) [ i ,                                                          \n"
  "                  i ] //                                                       \n"
  "                                                                               \n";

  }   //-- [if loop terminator] !vectorial ended --//

 if(fastmethod)
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "//                 ------- operator definition macros  -------                 \n"
 "// --------------------------------------------------------------------------- \n"
 "// divergence(i) : divergence operator definition, given a displacement vector \n"
 "//                 'i' returns scalar value                                    \n"
 "// epsilon(i)    : symmetric strain tensor operator given  displacement vector \n"
 "//                 'i' returns strain  vector [Exx,Eyy,Ezz,Eyz,Exz,Exy]        \n"
 "//=============================================================================\n"
 "                                                                               \n"
 "  macro divergence(i) (dx(i) + dy(i#1)) //                                     \n"
 "  macro epsilon(i) [ dx(i)               ,                                     \n"
 "                     dy(i#1)             ,                                     \n"
 "                     (dy(i)+dx(i#1))/SQ2 ] //                                  \n";

 if(tractionconditions>=1)
 {
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "//      ------- Neumann/Traction boundary condition Macros -------             \n"
 "// --------------------------------------------------------------------------- \n"
 "// NeumannBc'I' : will define the full Neumann boundary condition on border I  \n"
 "//=============================================================================\n";

 for(int i=0; i<tractionconditions; i++)
 writeIt
 "                                                                               \n"
 "  IFMACRO(Tbc"<<i<<"Tx) IFMACRO(!Tbc"<<i<<"Ty)                                 \n"
 "    NewMacro NeumannBc"<<i<<"() (Tbc"<<i<<"Tx)*v  EndMacro                     \n"
 "  ENDIFMACRO ENDIFMACRO                                                        \n"
 "                                                                               \n"
 "  IFMACRO(!Tbc"<<i<<"Tx) IFMACRO(Tbc"<<i<<"Ty)                                 \n"
 "    NewMacro NeumannBc"<<i<<"() (Tbc"<<i<<"Ty)*v1  EndMacro                    \n"
 "  ENDIFMACRO ENDIFMACRO                                                        \n"
 "                                                                               \n"
 "  IFMACRO(Tbc"<<i<<"Tx) IFMACRO(Tbc"<<i<<"Ty)                                  \n"
 "    NewMacro NeumannBc"<<i<<"() (Tbc"<<i<<"Tx)*v+(Tbc"<<i<<"Ty)*v1  EndMacro   \n"
 "  ENDIFMACRO ENDIFMACRO                                                        \n"
 "                                                                               \n";
 }

 if(dirichletconditions>=1)
 {
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "//         ------- Dirichlet boundary condition macros -------                 \n"
 "// --------------------------------------------------------------------------- \n"
 "// DirichletBc'I' : will define the full Dirichlet boundary condition on       \n"
 "//                  border I                                                   \n"
 "//=============================================================================\n";

 for(int i=0; i<dirichletconditions; i++)
 writeIt
 "                                                                               \n"
 "  IFMACRO(Dbc"<<i<<"Ux) IFMACRO(!Dbc"<<i<<"Uy)                                 \n"
 "    NewMacro DirichletBc"<<i<<"() Ux=Dbc"<<i<<"Ux  EndMacro                    \n"
 "  ENDIFMACRO ENDIFMACRO                                                        \n"
 "                                                                               \n"
 "  IFMACRO(!Dbc"<<i<<"Ux) IFMACRO(Dbc"<<i<<"Uy)                                 \n"
 "    NewMacro DirichletBc"<<i<<"() Uy=Dbc"<<i<<"Uy  EndMacro                    \n"
 "  ENDIFMACRO ENDIFMACRO                                                        \n"
 "                                                                               \n"
 "  IFMACRO(Dbc"<<i<<"Ux) IFMACRO(Dbc"<<i<<"Uy)                                  \n"
 "    NewMacro DirichletBc"<<i<<"() Ux=Dbc"<<i<<"Ux,Uy=Dbc"<<i<<"Uy  EndMacro    \n"
 "  ENDIFMACRO ENDIFMACRO                                                        \n"
 "                                                                               \n";
 }

 if(bodyforceconditions>=1)
 {
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "//      ------- volumetric bodyforce  conditions macro -------                 \n"
 "// --------------------------------------------------------------------------- \n"
 "// BodyforceBc'I' : will define the body force boundary condition on region I  \n"
 "//=============================================================================\n";

 for(int i=0; i<bodyforceconditions; i++)
 writeIt
 "                                                                               \n"
 "  IFMACRO(Fbc"<<i<<"Fx) IFMACRO(!Fbc"<<i<<"Fy)                                 \n"
 "    NewMacro BodyforceBc"<<i<<"() Fbc"<<i<<"Fx*v  EndMacro                     \n"
 "  ENDIFMACRO ENDIFMACRO                                                        \n"
 "                                                                               \n"
 "  IFMACRO(!Fbc"<<i<<"Fx) IFMACRO(Fbc"<<i<<"Fy)                                 \n"
 "    NewMacro BodyforceBc"<<i<<"() Fbc"<<i<<"Fy*v1  EndMacro                    \n"
 "  ENDIFMACRO ENDIFMACRO                                                        \n"
 "                                                                               \n"
 "  IFMACRO(Fbc"<<i<<"Fx) IFMACRO(Fbc"<<i<<"Fy)                                  \n"
 "    NewMacro BodyforceBc"<<i<<"() Fbc"<<i<<"Fx*v+Fbc"<<i<<"Fy*v1  EndMacro     \n"
 "  ENDIFMACRO ENDIFMACRO                                                        \n"
 "                                                                               \n";
 }

} //-- [if loop terminator] space==2 ended --//



if(spc==3){

 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "//                     ------- Essential Macros -------                        \n"
 "// --------------------------------------------------------------------------- \n";
 if(!Sequential)writeIt
 "// partitioner : mesh partitioner to be used use metis, parmetis, or scotch    \n"
 "// dimension   : dimension of the problem 2 or 3 for 2D or 3D                  \n";
 writeIt
 "// Ux, Uy      : x and y displacements                                         \n"
 "// Pk          : finite element space definition                               \n"
 "// def(i)      : to define a vectorial field of same order as Pk               \n"
 "// init(i)     : to initialize a vectorial field of same order as Pk           \n"
 "//=============================================================================\n"
 "                                                                               \n";

 if(!Sequential)
  writeIt
  "  macro partitioner "<<Partitioner<<" //                                      \n"
  "  macro dimension   3 //                                                      \n";

 if(ParaViewPostProcess)
  writeIt
  "  macro PlotVec(i) [ i   ,                                                      \n"
  "                     i#1 ,                                                      \n"
  "                     i#2 ] //                                                   \n"
  "                                                                                \n";

if(!vectorial){
  writeIt
  "  macro Pk [ P"<<lag<<" ,                                                     \n"
  "             P"<<lag<<" ,                                                     \n"
  "             P"<<lag<<" ] //                                                  \n"
  "                                                                              \n";
  writeIt
  "  macro def(i)  [i   ,                                                        \n"
  "                 i#1 ,                                                        \n"
  "                 i#2 ] //                                                     \n"
  "                                                                              \n";

if(!Sequential)
  writeIt
  "  macro init(i) [ i ,                                                         \n"
  "                  i ,                                                         \n"
  "                  i ] //                                                      \n"
  "                                                                              \n";

} //-- [if loop terminator] !vectorial ended --//


 if(fastmethod)
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "//                 ------- operator definition macros  -------                 \n"
 "// --------------------------------------------------------------------------- \n"
 "// divergence(i) : divergence operator definition, given a displacement vector \n"
 "//                 'i' returns scalar value                                    \n"
 "// epsilon(i)    : symmetric strain tensor operator given  displacement vector \n"
 "//                 'i' returns strain  vector [Exx,Eyy,Ezz,Eyz,Exz,Exy]        \n"
 "//=============================================================================\n"
 "                                                                               \n"
 "  macro divergence(i) ( dx( i ) + dy(i#1) + dz(i#2) )   //                     \n"
 "  macro epsilon   (i) [ dx( i ) , dy(i#1) , dz(i#2) ,                          \n"
 "                       (dz(i#1) + dy(i#2))/SQ2,                                \n"
 "                       (dz( i ) + dx(i#2))/SQ2,                                \n"
 "                       (dy( i ) + dx(i#1))/SQ2 ]        //                     \n"
 "                                                                               \n";

 if(tractionconditions>=1){
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "//      ------- Neumann/Traction boundary condition Macros -------             \n"
 "// --------------------------------------------------------------------------- \n"
 "// NeumannBc'I' : will define the full Neumann boundary condition on border I  \n"
 "//=============================================================================\n";

 for(int i=0; i<tractionconditions; i++)
 writeIt
 "                                                                                                   \n"
 "  IFMACRO(Tbc"<<i<<"Tx) IFMACRO(!Tbc"<<i<<"Ty) IFMACRO(!Tbc"<<i<<"Tz)                              \n"
 "    NewMacro NeumannBc"<<i<<"() (Tbc"<<i<<"Tx)*v  EndMacro                                         \n"
 "  ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                                                \n"
 "                                                                                                   \n"
 "  IFMACRO(!Tbc"<<i<<"Tx) IFMACRO(Tbc"<<i<<"Ty) IFMACRO(!Tbc"<<i<<"Tz)                              \n"
 "    NewMacro NeumannBc"<<i<<"() (Tbc"<<i<<"Ty)*v1  EndMacro                                        \n"
 "  ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                                                \n"
 "                                                                                                   \n"
 "  IFMACRO(!Tbc"<<i<<"Tx) IFMACRO(!Tbc"<<i<<"Ty) IFMACRO(Tbc"<<i<<"Tz)                              \n"
 "    NewMacro NeumannBc"<<i<<"() (Tbc"<<i<<"Tz)*v2  EndMacro                                        \n"
 "  ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                                                \n"
 "                                                                                                   \n"
 "  IFMACRO(Tbc"<<i<<"Tx) IFMACRO(Tbc"<<i<<"Ty) IFMACRO(!Tbc"<<i<<"Tz)                               \n"
 "    NewMacro NeumannBc"<<i<<"() (Tbc"<<i<<"Tx)*v + (Tbc"<<i<<"Ty)*v1  EndMacro                     \n"
 "  ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                                                \n"
 "                                                                                                   \n"
 "  IFMACRO(Tbc"<<i<<"Tx) IFMACRO(!Tbc"<<i<<"Ty) IFMACRO(Tbc"<<i<<"Tz)                               \n"
 "    NewMacro NeumannBc"<<i<<"() (Tbc"<<i<<"Tx)*v + (Tbc"<<i<<"Tz)*v2  EndMacro                     \n"
 "  ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                                                \n"
 "                                                                                                   \n"
 "  IFMACRO(!Tbc"<<i<<"Tx) IFMACRO(Tbc"<<i<<"Ty) IFMACRO(Tbc"<<i<<"Tz)                               \n"
 "    NewMacro NeumannBc"<<i<<"() (Tbc"<<i<<"Ty)*v1 +(Tbc"<<i<<"Tz)*v2  EndMacro                     \n"
 "  ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                                                \n"
 "                                                                                                   \n"
 "  IFMACRO(Tbc"<<i<<"Tx) IFMACRO(Tbc"<<i<<"Ty) IFMACRO(Tbc"<<i<<"Tz)                                \n"
 "    NewMacro NeumannBc"<<i<<"() (Tbc"<<i<<"Tx)*v + (Tbc"<<i<<"Ty)*v1 +(Tbc"<<i<<"Tz)*v2  EndMacro  \n"
 "  ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                                                \n";
 }


 if(dirichletconditions>=1)
 {
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "//         ------- Dirichlet boundary condition macros -------                 \n"
 "// --------------------------------------------------------------------------- \n"
 "// DirichletBc'I' : will define the full Dirichlet boundary condition on       \n"
 "//                  border I                                                   \n"
 "//=============================================================================\n";

 for(int i=0; i<dirichletconditions; i++)
 writeIt
 "                                                                                               \n"
 "  IFMACRO(Dbc"<<i<<"Ux) IFMACRO(!Dbc"<<i<<"Uy) IFMACRO(!Dbc"<<i<<"Uz)                          \n"
 "    NewMacro DirichletBc"<<i<<"() Ux=Dbc"<<i<<"Ux  EndMacro                                    \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n"
 "  IFMACRO(!Dbc"<<i<<"Ux) IFMACRO(Dbc"<<i<<"Uy) IFMACRO(!Dbc"<<i<<"Uz)                          \n"
 "    NewMacro DirichletBc"<<i<<"() Uy=Dbc"<<i<<"Uy  EndMacro                                    \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n"
 "  IFMACRO(!Dbc"<<i<<"Ux) IFMACRO(!Dbc"<<i<<"Uy) IFMACRO(Dbc"<<i<<"Uz)                          \n"
 "    NewMacro DirichletBc"<<i<<"() Uz=Dbc"<<i<<"Uz  EndMacro                                    \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n"
 "  IFMACRO(Dbc"<<i<<"Ux) IFMACRO(Dbc"<<i<<"Uy) IFMACRO(!Dbc"<<i<<"Uz)                           \n"
 "    NewMacro DirichletBc"<<i<<"() Ux=Dbc"<<i<<"Ux,Uy=Dbc"<<i<<"Uy  EndMacro                    \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n"
 "  IFMACRO(Dbc"<<i<<"Ux) IFMACRO(!Dbc"<<i<<"Uy) IFMACRO(Dbc"<<i<<"Uz)                           \n"
 "    NewMacro DirichletBc"<<i<<"() Ux=Dbc"<<i<<"Ux,Uz=Dbc"<<i<<"Uz  EndMacro                    \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n"
 "  IFMACRO(!Dbc"<<i<<"Ux) IFMACRO(Dbc"<<i<<"Uy) IFMACRO(Dbc"<<i<<"Uz)                           \n"
 "    NewMacro DirichletBc"<<i<<"() Uy=Dbc"<<i<<"Uy,Uz=Dbc"<<i<<"Uz  EndMacro                    \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n"
 "  IFMACRO(Dbc"<<i<<"Ux) IFMACRO(Dbc"<<i<<"Uy) IFMACRO(Dbc"<<i<<"Uz)                            \n"
 "    NewMacro DirichletBc"<<i<<"() Ux=Dbc"<<i<<"Ux,Uy=Dbc"<<i<<"Uy,Uz=Dbc"<<i<<"Uz  EndMacro    \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n";
 }


 if(bodyforceconditions>=1)
 {
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "//      ------- volumetric bodyforce  conditions macro -------                 \n"
 "// --------------------------------------------------------------------------- \n"
 "// BodyforceBc'I' : will define the body force boundary condition on region I  \n"
 "//=============================================================================\n";

 for(int i=0; i<bodyforceconditions; i++)
 writeIt
 "                                                                                               \n"
 "  IFMACRO(Fbc"<<i<<"Fx) IFMACRO(!Fbc"<<i<<"Fy) IFMACRO(!Fbc"<<i<<"Fz)                          \n"
 "    NewMacro BodyforceBc"<<i<<"() Fbc"<<i<<"Fx*v  EndMacro                                     \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n"
 "  IFMACRO(!Fbc"<<i<<"Fx) IFMACRO(Fbc"<<i<<"Fy) IFMACRO(!Fbc"<<i<<"Fz)                          \n"
 "    NewMacro BodyforceBc"<<i<<"() Fbc"<<i<<"Fy*v1  EndMacro                                    \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n"
 "  IFMACRO(!Fbc"<<i<<"Fx) IFMACRO(!Fbc"<<i<<"Fy) IFMACRO(Fbc"<<i<<"Fz)                          \n"
 "    NewMacro BodyforceBc"<<i<<"() Fbc"<<i<<"Fz*v2  EndMacro                                    \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n"
 "  IFMACRO(Fbc"<<i<<"Fx) IFMACRO(Fbc"<<i<<"Fy) IFMACRO(!Fbc"<<i<<"Fz)                           \n"
 "    NewMacro BodyforceBc"<<i<<"() Fbc"<<i<<"Fx*v+Fbc"<<i<<"Fy*v1  EndMacro                     \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n"
 "  IFMACRO(Fbc"<<i<<"Fx) IFMACRO(!Fbc"<<i<<"Fy) IFMACRO(Fbc"<<i<<"Fz)                           \n"
 "    NewMacro BodyforceBc"<<i<<"() Fbc"<<i<<"Fx*v+Fbc"<<i<<"Fz*v2  EndMacro                     \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n"
 "  IFMACRO(!Fbc"<<i<<"Fx) IFMACRO(Fbc"<<i<<"Fy) IFMACRO(Fbc"<<i<<"Fz)                           \n"
 "    NewMacro BodyforceBc"<<i<<"() Fbc"<<i<<"Fy*v1+Fbc"<<i<<"Fz*v2  EndMacro                    \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n"
 "  IFMACRO(Fbc"<<i<<"Fx) IFMACRO(Fbc"<<i<<"Fy) IFMACRO(Fbc"<<i<<"Fz)                            \n"
 "    NewMacro BodyforceBc"<<i<<"() Fbc"<<i<<"Fx*v+Fbc"<<i<<"Fy*v1+Fbc"<<i<<"Fz*v2  EndMacro     \n"
 "  ENDIFMACRO ENDIFMACRO ENDIFMACRO                                                             \n"
 "                                                                                               \n";
 }


} //-- [if loop terminator] space==3 ended --//



if(dirichletpointconditions<1 && Sequential && pointprobe)
 {
  writeIt
  "                                                                               \n"
  "//=============================================================================\n"
  "//            ------ point probe  Indicies macro  -------                      \n"
  "// -------------------------------------------------------------------         \n"
  "//  GetPointProbeIndicies is a  macro designed to  get the  point probe        \n"
  "//  indicies of the fi nite  element degree  of freedom that correspond        \n"
  "//  to the  point probe indices. The  macro  also  gives information of        \n"
  "//  the ranks holding the point probe points in the distributed mesh.          \n"
  "// -------------------------------------------------------------------         \n"
  "//  Inputs  : PnP                                                              \n"
  "//  Outputs : iProbe                                                           \n"
  "// -------------------------------------------------------------------         \n"
  "//  PnP : is the vector containing the point coordinates of the point          \n"
  "//        probe points.                                                        \n"
  "//  iProbe : is finite element degree of freedom vector of the  point          \n"
  "//        probe points.                                                        \n"
  "//=============================================================================\n";

  if(spc==2)
  writeIt
  "                                                                               \n"
  "  macro GetPointProbeIndicies(                                                 \n"
  "                                PnP,   iProbe                                  \n"
  "                             )                                                 \n"
  "    for (int i = 0; i < Th.nv; i++){                                           \n"
  "     for(int j=0; j < iProbe.n; j++)                                           \n"
  "        if(abs(Th(i).x-PnP(j,0))<.01 && abs(Th(i).y-PnP(j,1))<.01 )            \n"
  "          { iProbe[j]=i*2;  }                                                  \n"
  "     }//                                                                       \n";

  if(spc==3)
  writeIt
  "                                                                               \n"
  "  macro GetPointProbeIndicies(                                                 \n"
  "                                PnP,   iProbe                                  \n"
  "                             )                                                 \n"
  "    for (int i = 0; i < Th.nv; i++){                                           \n"
  "     for(int j=0; j < iProbe.n; j++)                                           \n"
  "        if( abs(Th(i).x-PnP(j,0))<.01 &&                                       \n"
  "            abs(Th(i).y-PnP(j,1))<.01 &&                                       \n"
  "            abs(Th(i).z-PnP(j,2))<.01    )                                     \n"
  "          { iProbe[j]=i*3;  }                                                  \n"
  "     }//                                                                       \n";

 }

if(dirichletpointconditions<1 && !Sequential  && pointprobe)
 {
  writeIt
  "                                                                               \n"
  "//=============================================================================\n"
  "//            ------ point probe  Indicies macro  -------                      \n"
  "// -------------------------------------------------------------------         \n"
  "//  GetPointProbeIndicies is a  macro designed to  get the  point probe        \n"
  "//  indicies of the fi nite  element degree  of freedom that correspond        \n"
  "//  to the  point probe indices. The  macro  also  gives information of        \n"
  "//  the ranks holding the point probe points in the distributed mesh.          \n"
  "// -------------------------------------------------------------------         \n"
  "//  Inputs  : PnP                                                              \n"
  "//  Outputs : iProbe, Prank                                                    \n"
  "// -------------------------------------------------------------------         \n"
  "//  PnP : is the vector containing the point coordinates of the point          \n"
  "//        probe points.                                                        \n"
  "//  iProbe : is finite element degree of freedom vector of the  point          \n"
  "//        probe points.                                                        \n"
  "//  Prank  : is rank of the MPI process that holds the finite element          \n"
  "//           degree of freedom of the  point probe points vector.              \n"
  "//=============================================================================\n";

  if(spc==2)
  writeIt
  "                                                                               \n"
  "  macro GetPointProbeIndicies(                                                 \n"
  "                                PnP,   iProbe, Prank                           \n"
  "                             )                                                 \n"
  "    for (int i = 0; i < Th.nv; i++){                                           \n"
  "     for(int j=0; j < iProbe.n; j++)                                           \n"
  "        if(abs(Th(i).x-PnP(j,0))<.01 && abs(Th(i).y-PnP(j,1))<.01 )            \n"
  "          { iProbe[j]=i*2; Prank[j]=mpirank; }                                 \n"
  "     }//                                                                       \n";


  if(spc==3)
  writeIt
  "                                                                               \n"
  "  macro GetPointProbeIndicies(                                                 \n"
  "                                PnP,   iProbe, Prank                           \n"
  "                             )                                                 \n"
  "    for (int i = 0; i < Th.nv; i++){                                           \n"
  "     for(int j=0; j < iProbe.n; j++)                                           \n"
  "        if( abs(Th(i).x-PnP(j,0))<.01 &&                                       \n"
  "            abs(Th(i).y-PnP(j,1))<.01 &&                                       \n"
  "            abs(Th(i).z-PnP(j,2))<.01    )                                     \n"
  "          { iProbe[j]=i*3; Prank[j]=mpirank; }                                 \n"
  "     }//                                                                       \n";

 }


if(dirichletpointconditions>=1)
 {
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "//                 ------- Point boundary condition macros -------             \n"
 "// --------------------------------------------------------------------------- \n"
 "// PointCoordinates : macro to define point x,y,z coordinates                  \n"
 "// GetPointIndiciesMpiRank : macro to get the finite element space index (PCi) \n"
 "//                         of vector of points PC and the MPIrank (mpirankPCi) \n"
 "//                         that holds the distributed chuck of mesh containing \n"
 "//                         points PC.                                          \n"
 "// ApplyPointBc(I) : will define the full point boundary condition on point I  \n"
 "//=============================================================================\n";

 if(spc==2){

 if(!pointprobe)
  writeIt
  "                                                                              \n"
  "  macro GetPointIndiciesMpiRank(PC, PCi, mpirankPCi)                          \n"
  "   for (int i = 0; i < Th.nv; i++){                                           \n"
  "     for(int j = 0; j < PC.n; j++){                                           \n"
  "       if(Th(i).x==PC(j,0) && Th(i).y==PC(j,1)){                              \n"
  "         PCi[j]=i; mpirankPCi[j]=mpirank;                                     \n"
  "       }                                                                      \n"
  "     }                                                                        \n"
  "   }                                                                          \n"
  "  //                                                                          \n";

 if(pointprobe)
  writeIt
  "                                                                              \n"
  "  macro GetPointIndiciesMpiRank(PC, PCi, mpirankPCi, PnP, iProbe, Prank)      \n"
  "   for (int i = 0; i < Th.nv; i++){                                           \n"
  "     for(int j = 0; j < PC.n; j++){                                           \n"
  "       if(Th(i).x==PC(j,0) && Th(i).y==PC(j,1)){                              \n"
  "         PCi[j]=i; mpirankPCi[j]=mpirank;                                     \n"
  "       }                                                                      \n"
  "     }                                                                        \n"
  "     for(int j=0; j < iProbe.n; j++){                                         \n"
  "        if(abs(Th(i).x-PnP(j,0))<.01 && abs(Th(i).y-PnP(j,1))<.01 ){          \n"
  "           iProbe[j]=i*2; Prank[j]=mpirank;                                   \n"
  "       }                                                                      \n"
  "     }                                                                        \n"
  "   }                                                                          \n"
  "  //                                                                          \n";

 for(int i=0; i<dirichletpointconditions; i++)
 writeIt
 "                                                                               \n"
 "  IFMACRO(!Pbc"<<i<<"Ux) IFMACRO(!Pbc"<<i<<"Uy)                                \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO                                                      \n"
 "                                                                               \n"
 "    IFMACRO(Pbc"<<i<<"Ux) IFMACRO(!Pbc"<<i<<"Uy)                               \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "         if(mpirank==mpirankPCi["<<i<<"]){                                     \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<",PCi["<<i<<"]*"<<Fdofs<<")=tgv;            \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"]= Pbc"<<i<<"Ux*tgv;}                      \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO                                                      \n"
 "                                                                               \n"
 "    IFMACRO(!Pbc"<<i<<"Ux) IFMACRO(Pbc"<<i<<"Uy)                               \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "         if(mpirank==mpirankPCi["<<i<<"]){                                     \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<"+1 , PCi["<<i<<"]*"<<Fdofs<<"+1)=tgv;      \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"+1]= Pbc"<<i<<"Uy*tgv;}                    \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO                                                      \n"
 "                                                                               \n"
 "    IFMACRO(Pbc"<<i<<"Ux) IFMACRO(Pbc"<<i<<"Uy)                                \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "         if(mpirank==mpirankPCi["<<i<<"]){                                     \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<"  ,PCi["<<i<<"]*"<<Fdofs<<"  )=tgv;        \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"  ] = Pbc"<<i<<"Ux*tgv;                    \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<"+1,PCi["<<i<<"]*"<<Fdofs<<"+1)=tgv;        \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"+1] = Pbc"<<i<<"Uy*tgv; }                  \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO                                                      \n"
 "                                                                               \n";
 }



 if(spc==3){

 if(!pointprobe)
 writeIt
 "                                                                               \n"
 "  macro GetPointIndiciesMpiRank(PC, PCi, mpirankPCi)                           \n"
 "   for (int i = 0; i < Th.nv; i++){                                            \n"
 "     for(int j = 0; j < PC.n; j++){                                            \n"
 "       if(Th(i).x==PC(j,0) && Th(i).y==PC(j,1) && Th(i).z==PC(j,2)){           \n"
 "         PCi[j]=i; mpirankPCi[j]=mpirank;                                      \n"
 "       }                                                                       \n"
 "     }                                                                         \n"
 "   }                                                                           \n"
 "  //                                                                           \n";

 if(pointprobe)
 writeIt
 "                                                                               \n"
 "  macro GetPointIndiciesMpiRank(PC, PCi, mpirankPCi, PnP, iProbe, Prank)       \n"
 "   for (int i = 0; i < Th.nv; i++){                                            \n"
 "     for(int j = 0; j < PC.n; j++){                                            \n"
 "       if(Th(i).x==PC(j,0) && Th(i).y==PC(j,1) && Th(i).z==PC(j,2)){           \n"
 "         PCi[j]=i; mpirankPCi[j]=mpirank;                                      \n"
 "       }                                                                       \n"
 "     }                                                                         \n"
 "     for(int j=0; j < iProbe.n; j++){                                          \n"
 "        if( abs(Th(i).x-PnP(j,0))<.01 &&                                       \n"
 "            abs(Th(i).y-PnP(j,1))<.01 &&                                       \n"
 "            abs(Th(i).z-PnP(j,2))<.01    ){                                    \n"
 "           iProbe[j]=i*3; Prank[j]=mpirank;                                    \n"
 "       }                                                                       \n"
 "     }                                                                         \n"
 "   }                                                                           \n"
 "  //                                                                           \n";

 for(int i=0; i<dirichletpointconditions; i++)
 writeIt
 "                                                                               \n"
 "  IFMACRO(!Pbc"<<i<<"Ux) IFMACRO(!Pbc"<<i<<"Uy) IFMACRO(!Pbc"<<i<<"Uz)         \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                          \n"
 "                                                                               \n"
 "    IFMACRO(Pbc"<<i<<"Ux) IFMACRO(!Pbc"<<i<<"Uy) IFMACRO(!Pbc"<<i<<"Uz)        \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "         if(mpirank==mpirankPCi["<<i<<"]){                                     \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<",PCi["<<i<<"]*"<<Fdofs<<")=tgv;            \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"]= Pbc"<<i<<"Ux*tgv;}                      \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                          \n"
 "                                                                               \n"
 "    IFMACRO(!Pbc"<<i<<"Ux) IFMACRO(Pbc"<<i<<"Uy) IFMACRO(!Pbc"<<i<<"Uz)        \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "         if(mpirank==mpirankPCi["<<i<<"]){                                     \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<"+1 , PCi["<<i<<"]*"<<Fdofs<<"+1)=tgv;      \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"+1]= Pbc"<<i<<"Uy*tgv;}                    \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                          \n"
 "                                                                               \n"
 "    IFMACRO(!Pbc"<<i<<"Ux) IFMACRO(!Pbc"<<i<<"Uy) IFMACRO(Pbc"<<i<<"Uz)        \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "         if(mpirank==mpirankPCi["<<i<<"]){                                     \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<"+2 , PCi["<<i<<"]*"<<Fdofs<<"+2)=tgv;      \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"+2]= Pbc"<<i<<"Uz*tgv;}                    \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                          \n"
 "                                                                               \n"
 "    IFMACRO(Pbc"<<i<<"Ux) IFMACRO(Pbc"<<i<<"Uy) IFMACRO(!Pbc"<<i<<"Uz)         \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "         if(mpirank==mpirankPCi["<<i<<"]){                                     \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<",PCi["<<i<<"]*"<<Fdofs<<")=tgv;            \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"]= Pbc"<<i<<"Ux*tgv;                       \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<"+1 , PCi["<<i<<"]*"<<Fdofs<<"+1)=tgv;      \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"+1]= Pbc"<<i<<"Uy*tgv;}                    \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                          \n"
 "                                                                               \n"
 "    IFMACRO(Pbc"<<i<<"Ux) IFMACRO(!Pbc"<<i<<"Uy) IFMACRO(Pbc"<<i<<"Uz)         \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "         if(mpirank==mpirankPCi["<<i<<"]){                                     \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<",PCi["<<i<<"]*"<<Fdofs<<")=tgv;            \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"]= Pbc"<<i<<"Ux*tgv;                       \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<"+2 , PCi["<<i<<"]*"<<Fdofs<<"+2)=tgv;      \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"+2]= Pbc"<<i<<"Uz*tgv;}                    \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                          \n"
 "                                                                               \n"
 "    IFMACRO(!Pbc"<<i<<"Ux) IFMACRO(Pbc"<<i<<"Uy) IFMACRO(Pbc"<<i<<"Uz)         \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "         if(mpirank==mpirankPCi["<<i<<"]){                                     \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<"+1 , PCi["<<i<<"]*"<<Fdofs<<"+1)=tgv;      \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"+1]= Pbc"<<i<<"Uy*tgv;                     \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<"+2 , PCi["<<i<<"]*"<<Fdofs<<"+2)=tgv;      \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"+2]= Pbc"<<i<<"Uz*tgv;}                    \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                          \n"
 "                                                                               \n"
 "    IFMACRO(Pbc"<<i<<"Ux) IFMACRO(Pbc"<<i<<"Uy) IFMACRO(Pbc"<<i<<"Uz)          \n"
 "      NewMacro  ApplyPointBc"<<i<<"(A,b)                                       \n"
 "         if(mpirank==mpirankPCi["<<i<<"]){                                     \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<"  ,PCi["<<i<<"]*"<<Fdofs<<"  )=tgv;        \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"  ] = Pbc"<<i<<"Ux*tgv;                    \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<"+1,PCi["<<i<<"]*"<<Fdofs<<"+1)=tgv;        \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"+1] = Pbc"<<i<<"Uy*tgv;                    \n"
 "          A(PCi["<<i<<"]*"<<Fdofs<<"+2,PCi["<<i<<"]*"<<Fdofs<<"+2)=tgv;        \n"
 "          b[PCi["<<i<<"]*"<<Fdofs<<"+2] = Pbc"<<i<<"Uz*tgv; }                  \n"
 "      EndMacro                                                                 \n"
 "    ENDIFMACRO ENDIFMACRO  ENDIFMACRO                                          \n"
 "                                                                               \n";
  }

} //-- [if loop terminator] pointbc ended --//

 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "//                 ------- update fields macros -------                        \n"
 "// --------------------------------------------------------------------------- \n"
 "// These macros are used to perform the update of u, v, a FE variables         \n"
 "//=============================================================================\n";


 if(!useGFP)
  writeIt
  "                                                                           \n"
  "                                                                           \n"
  "  macro updateVariables(du,uold,vold,aold,beta,gamma,dt){                  \n"
  "                                                                           \n"
  "    real aloc  ;                                                           \n"
  "                                                                           \n"
  "    for (int i=0; i< Vh.ndof; i++){                                        \n"
  "      aloc     =   (du[][i]-uold[][i]-dt*vold[][i])/beta/(dt*dt)           \n"
  "                  - (1.-2.*beta)/2./beta*aold[][i];                        \n"
  "      vold[][i] = vold[][i] + dt*((1.-gamma)*aold[][i] + gamma*aloc);      \n"
  "      aold[][i] = aloc;                                                    \n"
  "      uold[][i] = du[][i]    ;                                             \n"
  "    }                                                                      \n"
  "  }//                                                                      \n"
  "                                                                           \n";

  if(!useGFP)
  writeIt
  "                                                                           \n"
  "  macro updateFields(du,uold,vold,aold,beta,gamma,dt)                      \n"
  "     updateVariables(du,uold,vold,aold,beta,gamma,dt) //                   \n";

  if(useGFP)
  writeIt
  "                                                                           \n"
  "  macro updateFields(du,uold,vold,aold,beta,gamma,dt)                      \n"
  "     GFPUpdateDynamic(du#[],uold#[],vold#[],aold#[],beta,gamma,dt) //      \n";



  writeIt
  "                                                                           \n"
  "//----------------------Paraxial rotation macro--------------------------//\n"
  "                                                                           \n";

 if(spc==2)
  writeIt
  "  macro PA0(i)                                                               \n"
  "        [  cp*(N.x*N.x*i + N.x*N.y*i#1)                                      \n"
  "          +cs*( N.y*N.y*i - N.x*N.y*i#1) ,                                   \n"
  "                                                                             \n"
  "           cp*(N.x*N.y*i + N.y*N.y*i#1)                                      \n"
  "          +cs*(-N.x*N.y*i + N.x*N.x*i#1) ]//                                 \n"
  "                                                                             \n";


 if(spc==3)
  writeIt
  "  macro PA0(i)                                                               \n"
  "   [  cp*(N.x*N.x*i + N.x*N.y*i#1 + N.x*N.z*i#2)                             \n"
  "     +cs*( (1.-N.x*N.x)*i - N.x*N.y*i#1 - N.x*N.z*i#2)  ,                    \n"
  "                                                                             \n"
  "     cp*(N.x*N.y*i + N.y*N.y*i#1 + N.y*N.z*i#2)                              \n"
  "     +cs*(-N.x*N.y*i + (1.-N.y*N.y)*i#1 - N.y*N.z*i#2)  ,                    \n"
  "                                                                             \n"
  "     cp*(N.x*N.z*i + N.y*N.z*i#1 + N.z*N.z*i#2)                              \n"
  "     +cs*(-N.x*N.z*i - N.y*N.z*i#1 + (1.-N.z*N.z)*i#2) ]//                   \n"
  "                                                                             \n";

 if(Sequential)
  writeIt
  "                                                                                   \n"
  "//----------------------ParaView plotting macro--------------------------//        \n"
  "                                                                                   \n"
  "  macro exportBegin(name)                                                          \n"
  "    {ofstream pvd(name +\".pvd\");                                                 \n"
  "      pvd << \"<?xml version=\\\"1.0\\\"?>\\n\";                                   \n"
  "      pvd << \"<VTKFile type=\\\"Collection\\\" version=\\\"0.1\\\"\\n\";          \n"
  "      pvd << \"         byte_order=\\\"LittleEndian\\\"\\n\";                      \n"
  "      pvd << \"         compressor=\\\"vtkZLibDataCompressor\\\">\\n\";            \n"
  "      pvd << \"  <Collection>\\n\";                                                \n"
  "    }//                                                                            \n"
  "                                                                                   \n"
  "                                                                                   \n"
  "  macro exportEnd(name)                                                            \n"
  "    {ofstream pvd(name +\".pvd\", append);                                         \n"
  "    pvd << \"  </Collection>\\n\";                                                 \n"
  "    pvd << \"</VTKFile>\\n\";}                                                     \n"
  "    system(\"mv \"+name+\".pvd .\");                                               \n"
  "  //                                                                               \n"
  "                                                                                   \n"
  "                                                                                   \n"
  "  macro exportTimeStep(name, mesh, sol, forder, iterno, ts, nam )                  \n"
  "    savevtk(name+\"_\"+int(iterno)+\".vtu\",mesh,sol,order=forder,dataname=nam);   \n"
  "    ofstream pvd(name +\".pvd\", append);                                          \n"
  "      pvd << \"    <DataSet timestep=\\\"\" + real(ts) + \"\\\"\\n\";              \n"
  "      pvd << \"             file=\\\"\";                                           \n"
  "      pvd << name << \"_\" << int(iterno) << \".vtu\\\"/>\\n\";                    \n"
  "  //                                                                               \n"
  "                                                                                   \n";

  if(pointprobe && doublecouple=="unused"){
  writeIt
  "                                                                               \n"
  "//=============================================================================\n"
  "//            ------ point probe  Indicies macro  -------                      \n"
  "// -------------------------------------------------------------------         \n"
  "//  GetPointProbeIndicies is a  macro designed to  get the  point probe        \n"
  "//  indicies of the fi nite  element degree  of freedom that correspond        \n"
  "//  to the  point probe indices. The  macro  also  gives information of        \n"
  "//  the ranks holding the point probe points in the distributed mesh.          \n"
  "// -------------------------------------------------------------------         \n"
  "//  Inputs  : PnP                                                              \n"
  "//  Outputs : iProbe, Prank                                                    \n"
  "// -------------------------------------------------------------------         \n"
  "//  PnP : is the vector containing the point coordinates of the point          \n"
  "//        probe points.                                                        \n"
  "//  iProbe : is finite element degree of freedom vector of the  point          \n"
  "//        probe points.                                                        \n"
  "//  Prank  : is rank of the MPI process that holds the finite element          \n"
  "//           degree of freedom of the  point probe points vector.              \n"
  "//=============================================================================\n"
  "                                                                               \n";

  if(spc==2  && dirichletpointconditions<1)
  writeIt
  "                                                                               \n"
  "  macro GetPointProbeIndicies(                                                 \n"
  "                                PnP,   iProbe, Prank                           \n"
  "                             )                                                 \n"
  "    for (int i = 0; i < Th.nv; i++){                                           \n"
  "     for(int j=0; j < iProbe.n; j++)                                           \n"
  "        if(abs(Th(i).x-PnP(j,0))<.01 && abs(Th(i).y-PnP(j,1))<.01 )            \n"
  "          { iProbe[j]=i*2; Prank[j]=mpirank; }                                 \n"
  "     }//                                                                       \n";


  if(spc==3  && dirichletpointconditions<1)
  writeIt
  "                                                                               \n"
  "  macro GetPointProbeIndicies(                                                 \n"
  "                                PnP,   iProbe, Prank                           \n"
  "                               )                                               \n"
  "    for (int i = 0; i < Th.nv; i++){                                           \n"
  "     for(int j=0; j < iProbe.n; j++)                                           \n"
  "        if( abs(Th(i).x-PnP(j,0))<.01 &&                                       \n"
  "            abs(Th(i).y-PnP(j,1))<.01 &&                                       \n"
  "            abs(Th(i).z-PnP(j,2))<.01    )                                     \n"
  "          { iProbe[j]=i*3; Prank[j]=mpirank; }                                 \n"
  "     }//                                                                       \n";
  }


if(doublecouple=="displacement_based" || doublecouple=="force_based"){
  writeIt
  "                                                                               \n"
  "//=============================================================================\n"
  "//            ------ double couple  Indicies macro  -------                    \n"
  "// -------------------------------------------------------------------         \n"
  "//  GetDoubelCoupleIndicies is a  macro designed  to  get  the  double         \n"
  "//  couple finite element degree of freedom so that Dirichlet condition        \n"
  "//  can be applied easily by knowing these   indices. The  macro  also         \n"
  "//  gives information of the ranks holding the double couple points in         \n"
  "//  the distributed mesh.                                                      \n"
  "// -------------------------------------------------------------------         \n"
  "//  Inputs  : PnN, PnS, PnE, PnW                                               \n"
  "//  Outputs : iN, iS, iE, iW,  Nrank, Srank, Erank, Wrank                      \n"
  "// -------------------------------------------------------------------         \n"
  "//  PnN : is the vector containing the point coordinates of the North          \n"
  "//        point of the double couple. Same is true for PnS, PnE, PnW.          \n"
  "//  iN  : is finite element degree of freedom of the Northern  double          \n"
  "//        couple point. Same is true for iS, iE, iW.                           \n"
  "//  Nrank  : is rank of the MPI process that holds the finite element          \n"
  "//           degree of freedom of the  Northern  double couple point.          \n"
  "//           Same is true for Srank, Erank, Wrank.                             \n"
  "//=============================================================================\n"
  "                                                                               \n";

  if(spc==2 && !pointprobe)
  writeIt
  "                                                                               \n"
  "  macro GetDoubelCoupleIndicies(                                               \n"
  "                                PnN,   PnS,   PnE,   PnW,                      \n"
  "                                iN,    iS,    iE,    iW,                       \n"
  "                                Nrank, Srank, Erank, Wrank)                    \n"
  "    for (int i = 0; i < Th.nv; i++){                                           \n"
  "     if(Th(i).x==PnN[0] && Th(i).y==PnN[1])                                    \n"
  "       {iN=i*2; Nrank=mpirank; }                                               \n"
  "     if(Th(i).x==PnS[0] && Th(i).y==PnS[1])                                    \n"
  "       {iS=i*2; Srank=mpirank; }                                               \n"
  "     if(Th(i).x==PnE[0] && Th(i).y==PnE[1])                                    \n"
  "       {iE=i*2+1; Erank=mpirank; }                                             \n"
  "     if(Th(i).x==PnW[0] && Th(i).y==PnW[1])                                    \n"
  "       {iW=i*2+1; Wrank=mpirank; }                                             \n"
  "     }//                                                                       \n";

  if(spc==2 && pointprobe && dirichletpointconditions<1)
  writeIt
  "                                                                               \n"
  "  macro GetDoubelCoupleIndicies(                                               \n"
  "                                PnN,   PnS,   PnE,   PnW,                      \n"
  "                                iN,    iS,    iE,    iW,                       \n"
  "                                Nrank, Srank, Erank, Wrank,                    \n"
  "                                PnP,   iProbe, Prank                           \n"
  "                               )                                               \n"
  "    for (int i = 0; i < Th.nv; i++){                                           \n"
  "     if(Th(i).x==PnN[0] && Th(i).y==PnN[1])                                    \n"
  "       {iN=i*2; Nrank=mpirank; }                                               \n"
  "     if(Th(i).x==PnS[0] && Th(i).y==PnS[1])                                    \n"
  "       {iS=i*2; Srank=mpirank; }                                               \n"
  "     if(Th(i).x==PnE[0] && Th(i).y==PnE[1])                                    \n"
  "       {iE=i*2+1; Erank=mpirank; }                                             \n"
  "     if(Th(i).x==PnW[0] && Th(i).y==PnW[1])                                    \n"
  "       {iW=i*2+1; Wrank=mpirank; }                                             \n"
  "     for(int j=0; j < iProbe.n; j++)                                           \n"
  "        if(abs(Th(i).x-PnP(j,0))<.01 && abs(Th(i).y-PnP(j,1))<.01 )            \n"
  "          { iProbe[j]=i*2; Prank[j]=mpirank; }                                 \n"
  "     }//                                                                       \n";


  if(spc==3  && !pointprobe)
  writeIt
  "                                                                               \n"
  "  macro GetDoubelCoupleIndicies(                                               \n"
  "                                PnN,   PnS,   PnE,   PnW,                      \n"
  "                                iN,    iS,    iE,    iW,                       \n"
  "                                Nrank, Srank, Erank, Wrank)                    \n"
  "    for (int i = 0; i < Th.nv; i++){                                           \n"
  "     if(Th(i).x==PnN[0] && Th(i).y==PnN[1] && abs(Th(i).z-PnN[2])<.01)         \n"
  "       {iN=i*3; Nrank=mpirank;}                                                \n"
  "     if(Th(i).x==PnS[0] && Th(i).y==PnS[1] && abs(Th(i).z-PnS[2])<.01)         \n"
  "       {iS=i*3; Srank=mpirank;}                                                \n"
  "     if(Th(i).x==PnE[0] && Th(i).y==PnE[1] && abs(Th(i).z-PnE[2])<.01)         \n"
  "       {iE=i*3+2; Erank=mpirank;}                                              \n"
  "     if(Th(i).x==PnW[0] && Th(i).y==PnW[1] && abs(Th(i).z-PnW[2])<.01)         \n"
  "       {iW=i*3+2; Wrank=mpirank;}                                              \n"
  "     }//                                                                       \n";

  if(spc==3  && pointprobe && dirichletpointconditions<1)
  writeIt
  "                                                                               \n"
  "  macro GetDoubelCoupleIndicies(                                               \n"
  "                                PnN,   PnS,   PnE,   PnW,                      \n"
  "                                iN,    iS,    iE,    iW,                       \n"
  "                                Nrank, Srank, Erank, Wrank,                    \n"
  "                                PnP,   iProbe, Prank                           \n"
  "                               )                                               \n"
  "    for (int i = 0; i < Th.nv; i++){                                           \n"
  "     if(Th(i).x==PnN[0] && Th(i).y==PnN[1] && abs(Th(i).z-PnN[2])<.01)         \n"
  "       {iN=i*3; Nrank=mpirank;}                                                \n"
  "     if(Th(i).x==PnS[0] && Th(i).y==PnS[1] && abs(Th(i).z-PnS[2])<.01)         \n"
  "       {iS=i*3; Srank=mpirank;}                                                \n"
  "     if(Th(i).x==PnE[0] && Th(i).y==PnE[1] && abs(Th(i).z-PnE[2])<.01)         \n"
  "       {iE=i*3+2; Erank=mpirank;}                                              \n"
  "     if(Th(i).x==PnW[0] && Th(i).y==PnW[1] && abs(Th(i).z-PnW[2])<.01)         \n"
  "       {iW=i*3+2; Wrank=mpirank;}                                              \n"
  "     for(int j=0; j < iProbe.n; j++)                                           \n"
  "        if( abs(Th(i).x-PnP(j,0))<.01 &&                                       \n"
  "            abs(Th(i).y-PnP(j,1))<.01 &&                                       \n"
  "            abs(Th(i).z-PnP(j,2))<.01    )                                     \n"
  "          { iProbe[j]=i*3; Prank[j]=mpirank; }                                 \n"
  "     }//                                                                       \n";

if(doublecouple=="displacement_based")
  writeIt
  "                                                                               \n"
  "//=============================================================================\n"
  "//  ------ double couple Stiffness matrix penalization macro  -------          \n"
  "// -------------------------------------------------------------------         \n"
  "//  ApplyDoubleCoupleToA is a macro  designed  to  apply  the  double          \n"
  "//  couple Dirichlet boundary condition via penalization. This can be          \n"
  "//  applied easily by knowing the  finite element  degree of  freedom          \n"
  "//  that corresponds to these  indices, and the MPI rank that  holds           \n"
  "//  these degrees of freedom.                                                  \n"
  "// -------------------------------------------------------------------         \n"
  "//  A : is the stiffness matrix assembled from bilinear.                       \n"
  "//  iN  : is finite element degree of freedom of the Northern  double          \n"
  "//        couple point. Same is true for iS, iE, iW.                           \n"
  "//  Nrank  : is rank of the MPI process that holds the finite element          \n"
  "//           degree of freedom of the  Northern  double couple point.          \n"
  "//           Same is true for Srank, Erank, Wrank.                             \n"
  "//  tgv  : is the large penalization term tgv=1e30.                            \n"
  "//=============================================================================\n"
  "                                                                               \n"
  "  macro ApplyDoubleCoupleToA(A,iN,iS,iE,iW,Nrank,Srank,Erank,Wrank)            \n"
  "     if(mpirank==Nrank)                                                        \n"
  "       A(iN,iN)= tgv;                                                          \n"
  "     if(mpirank==Srank)                                                        \n"
  "       A(iS,iS)= tgv;                                                          \n"
  "     if(mpirank==Erank)                                                        \n"
  "       A(iE,iE)= tgv;                                                          \n"
  "     if(mpirank==Wrank)                                                        \n"
  "       A(iW,iW)= tgv;                                                          \n"
  "  //                                                                           \n"
  "                                                                               \n"
  "//=============================================================================\n"
  "//       ------ double couple RHS  macro  -------                              \n"
  "// -------------------------------------------------------------------         \n"
  "//  ApplyDoubleCoupleToRHS is a macro designed to  apply  the  double          \n"
  "//  couple Dirichlet boundary condition via penalization. This can be          \n"
  "//  applied easily by knowing the  finite element  degree of  freedom          \n"
  "//  that corresponds to these  indices, and the MPI rank that  holds           \n"
  "//  these degrees of freedom.                                                  \n"
  "// -------------------------------------------------------------------         \n"
  "//  RHS : is the right hand side vector  assembled from linear.                \n"
  "//  CondN  : is boundary condition displacement applied to the norther         \n"
  "//           point of the double couple. Same is true for Conds, CondW,        \n"
  "//           and CondE.                                                        \n"
  "//  iN  : is finite element degree of freedom of the Northern  double          \n"
  "//        couple point. Same is true for iS, iE, iW.                           \n"
  "//  Nrank  : is rank of the MPI process that holds the finite element          \n"
  "//           degree of freedom of the  Northern  double couple point.          \n"
  "//           Same is true for Srank, Erank, Wrank.                             \n"
  "//  tgv  : is the large penalization term tgv=1e30.                            \n"
  "//=============================================================================\n"
  "                                                                               \n"
  "  macro ApplyDoubleCoupleToRHS( RHS,                                           \n"
  "                                CondN,CondS,CondE,CondW,                       \n"
  "                                iN,   iS,   iE,   iW,                          \n"
  "                                Nrank,Srank,Erank,Wrank)                       \n"
  "     if(mpirank==Nrank)                                                        \n"
  "       RHS[iN]= CondN*tgv;                                                     \n"
  "     if(mpirank==Srank)                                                        \n"
  "       RHS[iS]= CondS*tgv;                                                     \n"
  "     if(mpirank==Erank)                                                        \n"
  "       RHS[iE]= CondE*tgv;                                                     \n"
  "     if(mpirank==Wrank)                                                        \n"
  "       RHS[iW]= CondW*tgv;                                                     \n"
  "  //                                                                           \n"
  "                                                                               \n";

if(doublecouple=="force_based")
  writeIt
  "                                                                               \n"
  "//=============================================================================\n"
  "//       ------ double couple RHS force macro  -------                         \n"
  "// -------------------------------------------------------------------         \n"
  "//  ApplyDoubleCoupleToRHS is a macro designed to  apply  the  double          \n"
  "//  couple Dirichlet boundary condition. This  can be  applied easily          \n"
  "//  by knowing the finite element degree of  freedom that corresponds          \n"
  "//  to these  indices, and the MPI rank that  holds these degrees of           \n"
  "//  freedom.                                                                   \n"
  "// -------------------------------------------------------------------         \n"
  "//  RHS : is the right hand side vector  assembled from linear.                \n"
  "//  CondN  : is boundary condition force applied to the norther point          \n"
  "//           of the double couple. Same is true for Conds, CondW, and          \n"
  "//           CondE.                                                            \n"
  "//  iN  : is finite element degree of freedom of the Northern  double          \n"
  "//        couple point. Same is true for iS, iE, iW.                           \n"
  "//  Nrank  : is rank of the MPI process that holds the finite element          \n"
  "//           degree of freedom of the  Northern  double couple point.          \n"
  "//           Same is true for Srank, Erank, Wrank.                             \n"
  "//=============================================================================\n"
  "                                                                               \n"
  "  macro ApplyDoubleCoupleToRHS( RHS,                                           \n"
  "                                CondN,CondS,CondE,CondW,                       \n"
  "                                iN,   iS,   iE,   iW,                          \n"
  "                                Nrank,Srank,Erank,Wrank)                       \n"
  "     if(mpirank==Nrank)                                                        \n"
  "       RHS[iN]= CondN;                                                         \n"
  "     if(mpirank==Srank)                                                        \n"
  "       RHS[iS]= CondS;                                                         \n"
  "     if(mpirank==Erank)                                                        \n"
  "       RHS[iE]= CondE;                                                         \n"
  "     if(mpirank==Wrank)                                                        \n"
  "       RHS[iW]= CondW;                                                         \n"
  "  //                                                                           \n"
  "                                                                               \n";
}  // if(doublecouple=="displacement_based" || doublecouple=="force_based") ENDED
