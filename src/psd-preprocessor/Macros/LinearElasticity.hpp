/**************************************************************************************
*                                                                                     *
*           This file is a part of PSD project                                        *
*                                                                                     *
*       -------------------------------------------------------------------           *
*                                                                                     *
*       Copyright 2019-2025 CEA/DES                                                   *
*                                                                                     *
*       Licensed under the Apache License, Version 2.0  (the "License");              *
*       you may not use this file except in compliance with the License.              *
*       You may obtain a copy of the License at                                       *
*                                                                                     *
*           http://www.apache.org/licenses/LICENSE-2.0                                *
*                                                                                     *
*       Unless required by applicable law or agreed to in writing, software           *
*       distributed under the License is distributed on an  "AS IS"  BASIS,           *
*       WITHOUT  WARRANTIES  OR  CONDITIONS  OF  ANY  KIND,  either express           *
*       or implied. See  the License  for  the  specific language governing           *
*       permissions and limitations under the License.                                *
*                                                                                     *
*       -------------------------------------------------------------------           *
*                                                                                     *
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

 if(Model!="pseudo_nonlinear")
 writeIt
 "  macro Ux u  //                                                                \n"
 "  macro Uy u1 //                                                                \n";

 if(Model=="pseudo_nonlinear")
 writeIt
 "  macro Ux du  //                                                                \n"
 "  macro Uy du1 //                                                                \n";


 if(ParaViewPostProcess)
 writeIt
 "  macro PlotVec(i) [ i   ,                                                      \n"
 "                     i#1 ,                                                      \n"
 "                     0   ] //                                                   \n"
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


 if(!fastmethod && !useMfront)
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "//                 ------- operator definition macros  -------                 \n"
 "// --------------------------------------------------------------------------- \n"
 "// divergence(i) : divergence operator definition, given a displacement vector \n"
 "//                 'i' returns scalar value                                    \n"
 "// epsilon(i)    : symmetric strain tensor operator given  displacement vector \n"
 "//                 'i' returns strain  vector [Exx,Eyy,Ezz,Eyz,Exz,Exy]        \n"
 "// epsilonXMt(i,Mt) : given  displacement vector 'i' calculates strain X Mt i.e\n"
 "//                   Strain X material tensor                                  \n"
 "//=============================================================================\n"
 "                                                                               \n"
 "  macro divergence(i) (dx(i) + dy(i#1)) //                                     \n"
 "                                                                               \n"
 "  macro epsilon(i) [ dx(i)               ,                                     \n"
 "                     dy(i#1)             ,                                     \n"
 "                     (dy(i)+dx(i#1))   ] //                                    \n"
 "                                                                               \n"
 "                                                                               \n"
 "  macro epsilonXMt(u,Mt) [                                                     \n"
 "                                                                               \n"
 "               epsilon(u)[0]*Mt#11 + epsilon(u)[1]*Mt#12 + epsilon(u)[2]*Mt#13,\n"
 "               epsilon(u)[0]*Mt#12 + epsilon(u)[1]*Mt#22 + epsilon(u)[2]*Mt#23,\n"
 "               epsilon(u)[0]*Mt#13 + epsilon(u)[1]*Mt#23 + epsilon(u)[2]*Mt#33 \n"
 "                                                                               \n"
 "                        ] //                                                   \n"
 "                                                                               \n";

 if(!fastmethod && useMfront)
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "//                 ------- operator definition macros  -------                 \n"
 "// --------------------------------------------------------------------------- \n"
 "// divergence(i) : divergence operator definition, given a displacement vector \n"
 "//                 'i' returns scalar value                                    \n"
 "// epsilon(i)    : symmetric strain tensor operator given  displacement vector \n"
 "//                 'i' returns strain  vector [Exx,Eyy,Ezz,Eyz,Exz,Exy]        \n"
 "// epsilonXMt(i,Mt) : given  displacement vector 'i' calculates strain X Mt i.e\n"
 "//                   Strain X material tensor                                  \n"
 "//=============================================================================\n"
 "                                                                               \n"
 "  macro divergence(i) (dx(i) + dy(i#1)) //                                     \n"
 "                                                                               \n"
 "  macro epsilon(i) [ dx(i)               ,                                     \n"
 "                     dy(i#1)             ,                                     \n"
 "                     (dy(i)+dx(i#1))/SQ2  ] //                                 \n"
 "                                                                               \n"
 "                                                                               \n"
 "  macro epsilonXMt(u,Mt) [                                                     \n"
 "                                                                               \n"
 "               epsilon(u)[0]*Mt#11 + epsilon(u)[1]*Mt#12 + epsilon(u)[2]*Mt#13,\n"
 "               epsilon(u)[0]*Mt#12 + epsilon(u)[1]*Mt#22 + epsilon(u)[2]*Mt#23,\n"
 "               epsilon(u)[0]*Mt#13 + epsilon(u)[1]*Mt#23 + epsilon(u)[2]*Mt#33 \n"
 "                                                                               \n"
 "                        ] //                                                   \n"
 "                                                                               \n";


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

 if(Model!="pseudo_nonlinear")
 writeIt
 "  macro Ux u  //                                                               \n"
 "  macro Uy u1 //                                                               \n"
 "  macro Uz u2 //                                                               \n";

 if(Model=="pseudo_nonlinear")
 writeIt
 "  macro Ux du  //                                                              \n"
 "  macro Uy du1 //                                                              \n"
 "  macro Uz du2 //                                                              \n";

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

 if(!fastmethod && !useMfront)
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "//                 ------- operator definition macros  -------                 \n"
 "// --------------------------------------------------------------------------- \n"
 "// divergence(i) : divergence operator definition, given a displacement vector \n"
 "//                 'i' returns scalar value                                    \n"
 "// epsilon(i)    : symmetric strain tensor operator given  displacement vector \n"
 "//                 'i' returns strain  vector [Exx,Eyy,Ezz,Eyz,Exz,Exy]        \n"
 "// epsilonXMt(i,Mt) : given  displacement vector 'i' calculates strain X Mt i.e\n"
 "//                   Strain X material tensor                                  \n"
 "//=============================================================================\n"
 "                                                                               \n"
 "  macro divergence(i) ( dx( i ) + dy(i#1) + dz(i#2) )   //                     \n"
 "                                                                               \n"
 "  macro epsilon   (i) [ dx( i )           ,                                    \n"
 "                        dy(i#1)           ,                                    \n"
 "                        dz(i#2)           ,                                    \n"
 "                       (dz(i#1) + dy(i#2)),                                    \n"
 "                       (dz( i ) + dx(i#2)),                                    \n"
 "                       (dy( i ) + dx(i#1)) ]        //                         \n"
 "                                                                               \n"
 "                                                                               \n"
 "                                                                               \n"
 "  macro epsilonXMt(u,Mt) [                                                     \n"
 "                                                                               \n"
 "  epsilon(u)[0]*Mt#11 + epsilon(u)[1]*Mt#12 + epsilon(u)[2]*Mt#13 + epsilon(u)[3]*Mt#14 + epsilon(u)[4]*Mt#15 + epsilon(u)[5]*Mt#16, \n"
 "  epsilon(u)[0]*Mt#12 + epsilon(u)[1]*Mt#22 + epsilon(u)[2]*Mt#23 + epsilon(u)[3]*Mt#24 + epsilon(u)[4]*Mt#25 + epsilon(u)[5]*Mt#26, \n"
 "  epsilon(u)[0]*Mt#13 + epsilon(u)[1]*Mt#23 + epsilon(u)[2]*Mt#33 + epsilon(u)[3]*Mt#34 + epsilon(u)[4]*Mt#35 + epsilon(u)[5]*Mt#36, \n"
 "  epsilon(u)[0]*Mt#14 + epsilon(u)[1]*Mt#24 + epsilon(u)[2]*Mt#34 + epsilon(u)[3]*Mt#44 + epsilon(u)[4]*Mt#45 + epsilon(u)[5]*Mt#46, \n"
 "  epsilon(u)[0]*Mt#15 + epsilon(u)[1]*Mt#25 + epsilon(u)[2]*Mt#35 + epsilon(u)[3]*Mt#45 + epsilon(u)[4]*Mt#55 + epsilon(u)[5]*Mt#56, \n"
 "  epsilon(u)[0]*Mt#16 + epsilon(u)[1]*Mt#26 + epsilon(u)[2]*Mt#36 + epsilon(u)[3]*Mt#46 + epsilon(u)[4]*Mt#56 + epsilon(u)[5]*Mt#66  \n"
 "                                                                               \n"
 "                        ] //                                                   \n"
 "                                                                               \n";


 if(!fastmethod && useMfront)
 writeIt
 "                                                                               \n"
 "//=============================================================================\n"
 "//                 ------- operator definition macros  -------                 \n"
 "// --------------------------------------------------------------------------- \n"
 "// divergence(i) : divergence operator definition, given a displacement vector \n"
 "//                 'i' returns scalar value                                    \n"
 "// epsilon(i)    : symmetric strain tensor operator given  displacement vector \n"
 "//                 'i' returns strain  vector [Exx,Eyy,Ezz,Eyz,Exz,Exy]        \n"
 "// epsilonXMt(i,Mt) : given  displacement vector 'i' calculates strain X Mt i.e\n"
 "//                   Strain X material tensor                                  \n"
 "//=============================================================================\n"
 "                                                                               \n"
 "  macro divergence(i) ( dx( i ) + dy(i#1) + dz(i#2) )   //                     \n"
 "                                                                               \n"
 "  macro epsilon   (i) [ dx( i )           ,                                    \n"
 "                        dy(i#1)           ,                                    \n"
 "                        dz(i#2)           ,                                    \n"
 "                       (dy( i ) + dx(i#1))/SQ2 ,                               \n"
 "                       (dz( i ) + dx(i#2))/SQ2 ,                               \n"
 "                       (dz(i#1) + dy(i#2))/SQ2  ]        //                    \n"
 "                                                                               \n"
 "                                                                               \n"
 "                                                                               \n"
 "  macro epsilonXMt(u,Mt) [                                                     \n"
 "                                                                               \n"
 "  epsilon(u)[0]*Mt#11 + epsilon(u)[1]*Mt#12 + epsilon(u)[2]*Mt#13 + epsilon(u)[3]*Mt#14 + epsilon(u)[4]*Mt#15 + epsilon(u)[5]*Mt#16, \n"
 "  epsilon(u)[0]*Mt#12 + epsilon(u)[1]*Mt#22 + epsilon(u)[2]*Mt#23 + epsilon(u)[3]*Mt#24 + epsilon(u)[4]*Mt#25 + epsilon(u)[5]*Mt#26, \n"
 "  epsilon(u)[0]*Mt#13 + epsilon(u)[1]*Mt#23 + epsilon(u)[2]*Mt#33 + epsilon(u)[3]*Mt#34 + epsilon(u)[4]*Mt#35 + epsilon(u)[5]*Mt#36, \n"
 "  epsilon(u)[0]*Mt#14 + epsilon(u)[1]*Mt#24 + epsilon(u)[2]*Mt#34 + epsilon(u)[3]*Mt#44 + epsilon(u)[4]*Mt#45 + epsilon(u)[5]*Mt#46, \n"
 "  epsilon(u)[0]*Mt#15 + epsilon(u)[1]*Mt#25 + epsilon(u)[2]*Mt#35 + epsilon(u)[3]*Mt#45 + epsilon(u)[4]*Mt#55 + epsilon(u)[5]*Mt#56, \n"
 "  epsilon(u)[0]*Mt#16 + epsilon(u)[1]*Mt#26 + epsilon(u)[2]*Mt#36 + epsilon(u)[3]*Mt#46 + epsilon(u)[4]*Mt#56 + epsilon(u)[5]*Mt#66  \n"
 "                                                                               \n"
 "                        ] //                                                   \n"
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
