//=================================================================================================
// ------ Building the VariationalFormulations.edp file ------ 
//=================================================================================================

cout << " building VariationalFormulations.edp"; 

{ofstream  writevarfmatsolve("VariationalFormulations.edp");

writevarfmatsolve
<<"                                                                                                \n"
<<"/**************************Variational formulation******************************                \n"
<<"*                                                                              *                \n"
<<"* Note!!! This file is  generated  by  running  PSD PreProcessor  Do  not edit *                \n"
<<"*         in order to  control this  file please change flag arguments of  the *                \n"
<<"*         PSD_PreProcess, details of which are present in PSD_PreProcess or in *                \n"
<<"*         the README.MD file.                                                  *                \n"
<<"*                                                                              *                \n"
<<"*******************************************************************************/                \n"
<<"                                                                                                \n";

if(!nonlinear)if(!dynamic)if(!soildynamics)if(!quasistatic){writevarfmatsolve
<<"                                                                                                \n"
<<"//==============================================================================                \n"
<<"// -------Variation formulation linear elasticity-------                                        \n"
<<"//==============================================================================                \n"
<<"                                                                                                \n"
<<"                                                                                                \n"
<<"varf elast(def(u),def(v)) =                                                                     \n"
<<"                                                                                                \n";

if(fastmethod)writevarfmatsolve
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $+int_{\\Omega}(\\lambda:\\nabla(u).\\nabla(v))$                                        \n"
<<"    //  $+int_{\\Omega}(2\\mu(\\epsilon(u):\\epsilon(v)))$                                      \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      intN(Th,qforder=3)(                                                                       \n"
<<"                     lambda*divergence(u)*divergence(v)                                         \n"
<<"                   + 2.*mu*( epsilon(u)'*epsilon(v) )                                           \n";

if(!fastmethod)writevarfmatsolve
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $+int_{\\Omega}(\\epsilon(u):\\mathbbm(E):\\epsilon(v))$                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      intN(Th,qforder=3)(                                                                       \n"
<<"                     epsilon(u)'*Mt*epsilon(v)                                                  \n";

writevarfmatsolve
<<"                     )                                                                          \n";

if(bodyforce)writevarfmatsolve
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $+int_{\\Omega}(f.v)$                                                                   \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"     + intN(Th,qforder=2)(BF'*def(v))                                                           \n";


if(tractionconditions>=1)if(spc==2)
for(int i=0; i<tractionconditions; i++)
writevarfmatsolve
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $+int_{\\partial\\Omega_N}(T.v)$                                                        \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"     + intN1(Th,Tlabel["<<i<<"],qforder=2)(T(tx"<<i<<",ty"<<i<<")'*def(v))                      \n";

if(tractionconditions>=1)if(spc==3)
for(int i=0; i<tractionconditions; i++)
writevarfmatsolve
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $+int_{\\partial\\Omega_N}(T.v)$                                                        \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      + intN1(Th,Tlabel["<<i<<"],qforder=2)(T(tx"<<i<<",ty"<<i<<",tz"<<i<<")'*def(v))           \n";

if(spc==2)
for(int i=0; i<dirichletconditions; i++)
writevarfmatsolve
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"     + on( Dlabel["<<int(i)<<"],                                                                \n"
<<"             u  = Dvalue["<<int(i+1*i)<<"],                                                     \n"
<<"             u1 = Dvalue["<<int((i+1*i)+1)<<"]                                                  \n"
<<"         )                                                                                      \n"
<<"                                                                                                \n";

if(spc==3)
for(int i=0; i<dirichletconditions; i++)
writevarfmatsolve
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"     + on(Dlabel["<<int(i)<<"],                                                                 \n"
<<"             u  = Dvalue["<<int(i+2*i)<<"],                                                     \n"
<<"             u1 = Dvalue["<<int((i+2*i)+1)<<"],                                                 \n"
<<"             u2 = Dvalue["<<int((i+2*i)+2)<<"]                                                  \n"
<<"         )                                                                                      \n"
<<"                                                                                                \n";


writevarfmatsolve
<<";                                                                                               \n"
<<"                                                                                                \n";

}  //-- [if loop terminator] !nonlinear ended --//

if(nonlinear)if(!vectorial)if(!dynamic){writevarfmatsolve
<<"                                                                                                \n"
<<"//==============================================================================                \n"
<<"// -------Variation formulation hybrid phase-field (Staggered)-------                           \n"
<<"//==============================================================================                \n"
<<"                                                                                                \n"
<<" //-----------------------------                                                                \n"
<<" // Eq. 1 Linear momentum     //                                                                \n"
<<" //-----------------------------                                                                \n"
<<"                                                                                                \n"
<<" varf elast(def2(u),def2(v)) =                                                                  \n"
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    // $+int_{\\Omega}(((1-\\phi)^2+k)(\\epsilon(u):\\mathbbm(E):\\epsilon(v)))$                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      intN(Th,qforder=3)(                                                                       \n"
<<"         ((1 - phiold)*(1 - phiold) + 1e-6)*                                                    \n"
<<"         (lambda*divergence(u)*divergence(v)                                                    \n"
<<"         + 2.*mu*( epsilon(u)'*epsilon(v) ))                                                    \n"
<<"                        )                                                                       \n";

if(bodyforce)writevarfmatsolve
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    // $+int_{\\Omega}(f.v)$                                                                    \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      + intN(Th,qforder=2)(BF'*def2(v))    // Body force     (volumetric)                       \n";


//if(tractionbc)writevarfmatsolve
//<<"    + intN1(Th,Tlabel,qforder=2)(T'*def2(v))// Traction force (Neumann BC)                    \n";

if(tractionconditions>=1)if(spc==2)
for(int i=0; i<tractionconditions; i++)
writevarfmatsolve
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $+int_{\\partial\\Omega_N}(T.v)$                                                        \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      + intN1(Th,Tlabel["<<i<<"],qforder=2)(T(tx"<<i<<",ty"<<i<<")'*def2(v))                    \n";

if(tractionconditions>=1)if(spc==3)
for(int i=0; i<tractionconditions; i++)
writevarfmatsolve
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $+int_{\\partial\\Omega_N}(T.v)$                                                        \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      + intN1(Th,Tlabel["<<i<<"],qforder=2)(T(tx"<<i<<",ty"<<i<<",tz"<<i<<")'*def2(v))          \n";


if(dirichletbc){

if(spc==2)writevarfmatsolve
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      + on(Dlabel,u=Dvalue[0],u1=Dvalue[1])    // Displacement (Dirichlet)                      \n"
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      + on(2,u1=tr)                          // Displacement (Dirichlet)                        \n";

if(spc==3)writevarfmatsolve
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      + on(Dlabel,u=Dvalue[0],u1=Dvalue[1],u2=Dvalue[2])    // Displacement (Dirichlet)         \n"
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      + on(2,u1=tr)                                         // Displacement (Dirichlet)         \n";

}  //-- [if loop terminator] dirichletbc ended --//


writevarfmatsolve
<<";                                                                                               \n";

/************************OLD METHOD*************************************************
if(pipegnu)writevarfmatsolve
<<"                                                                                \n"
<<"varf elastNoDirc(def2(u),def2(v))                                               \n"
<<"    = intN(Th,qforder=3)(                                                       \n"
<<"            ((1 - phiold)*(1 - phiold) + 1e-6)*                                 \n"
<<"            (lambda*divergence(u)*divergence(v)                                 \n"
<<"            +2.*mu*( epsilon(u)'*epsilon(v) ))                                  \n"
<<"                );                                                              \n";
/************************OLD METHOD*************************************************/  


writevarfmatsolve
<<"                                                                                                \n"
<<" //-----------------------------                                                                \n"
<<" // Eq. 2 Helmothz           //                                                                 \n"
<<" //-----------------------------                                                                \n"
<<"                                                                                                \n"
<<"  varf phase(phi,q) =                                                                           \n"
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    // $+int_{\\Omega}(G_cl_0(\\nabl{\\phi}.\\nabla{q})+(G_c/l_0+2H^{+})\\phi q)$               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      intN(Th,qforder=3)(                                                                       \n"
<<"              (Gc*lo*(grad(phi)'*grad(q))) +                                                    \n"
<<(energydecomp  ? "\t\t\t  ( ((Gc/lo)  + 2.*H)*phi*q )\n"         : ""                             )
<<(!energydecomp ? "\t\t\t  ( ((Gc/lo)  + 2.*Hplus(u))*phi*q )\n"  : ""                             )
<<"                       )                                                                        \n"
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    // $+int_{\\Omega}((2H^{+}) q)$                                                             \n"
<<"    //--------------------------------------------------------------------------                \n"
<<(energydecomp  ? "\t+ intN(Th,qforder=2)(  2.*H*q  )\n"         : ""                              )
<<(!energydecomp ? "\t+ intN(Th,qforder=2)(  2.*Hplus(u)*q  )\n"  : ""                              )
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      + on(4,phi=1)             //  Cracked (Dirichlet)                                         \n"
<<";                                                                                               \n";

}  //-- [if loop terminator] nonlinear ended --//


if(nonlinear)if(vectorial)if(!dynamic)if(!soildynamics){writevarfmatsolve
<<"                                                                                                \n"
<<"//==============================================================================                \n"
<<"// -------Variation formulation hybrid phase-field (Vectorial)-------                           \n"
<<"//==============================================================================                \n"
<<"                                                                                                \n"
<<"varf elast(def(u),def(v)) =                                                                     \n"
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    // $+int_{\\Omega}(((1-\\phi)^2+k)(\\epsilon(u):\\mathbbm(E):\\epsilon(v)))$                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      intN(Th,qforder=3)(                                                                       \n"
<<"         ((1 - uold"<<spc<<")*(1 - uold"<<spc<<") + 1e-6)*                                      \n"
<<"         (lambda*divergence(u)*divergence(v)                                                    \n"
<<"         + 2.*mu*( epsilon(u)'*epsilon(v) ))                                                    \n"
<<"                                                                                                \n"
<<"                    +                                                                           \n"
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    // $+int_{\\Omega}(G_cl_0(\\nabl{\\phi}.\\nabla{q})+(G_c/l_0+2H^{+})\\phi q)$               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"         (Gc*lo*(grad(u"<<spc<<")'*grad(v"<<spc<<"))) +                                         \n";

if(!energydecomp)writevarfmatsolve
<<"\t\t\t( ((Gc/lo)  + 2.*Hplus(uold))*u"<<spc<<"*v"<<spc<<" )                                     \n";
if(energydecomp)writevarfmatsolve
<<"\t\t\t( ((Gc/lo)  + 2.*H)*u"<<spc<<"*v"<<spc<<" )                                               \n";

writevarfmatsolve
<<"                         )                                                                      \n";

if(!energydecomp)writevarfmatsolve
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    // $+int_{\\Omega}((2H^{+}) q)$                                                             \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      + intN(Th,qforder=2)(  2.*Hplus(uold)*v"<<spc<<"  )                                       \n";
if(energydecomp)writevarfmatsolve
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    // $+int_{\\Omega}((2H^{+}) q)$                                                             \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"\t+ intN(Th,qforder=2)(  2.*H*v"<<spc<<"  )                                                     \n";

/*
<<(!energydecomp  ? "\t\t\t( ((Gc/lo)  + 2.*Hplus(uold))*u"<<spc<<"*v"<<spc<<" )\n": ""             )
<<(energydecomp   ? "\t\t\t( ((Gc/lo)  + 2.*H)*u"<<spc<<"*v"<<spc<<" )\n"          : ""             )
<<(!energydecomp  ? "\t+ intN(Th,qforder=2)(  2.*Hplus(uold)*v"<<spc<<"  )\n": ""                   )
<<(energydecomp   ? "\t+ intN(Th,qforder=2)(  2.*H*v"<<spc<<"  )\n"          : ""                   )
*/

writevarfmatsolve
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    + on(4,u"<<spc<<" = 1)                          // Cracked (Dirichlet)                      \n";

if(dirichletbc){

if(spc==2)writevarfmatsolve
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    + on(Dlabel,u=Dvalue[0],u1=Dvalue[1])    // Displacement (Dirichlet)                        \n"
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    + on(2,u1=tr)                // Displacement (Dirichlet)                                    \n"
<<"                                                                                                \n";

if(spc==3)writevarfmatsolve
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    + on(Dlabel,u=Dvalue[0],u1=Dvalue[1]                                                        \n"
<<"                ,u2=Dvalue[2])    // Displacement (Dirichlet)                                   \n"
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    + on(2,u1=tr)                // Displacement (Dirichlet)                                    \n"
<<"                                                                                                \n";

}  //-- [if loop terminator] dirichletbc ended --//

writevarfmatsolve
<<";                                                                                               \n";

/************************OLD METHOD*************************************************
if(pipegnu)writevarfmatsolve
<<"                                                                                                \n"
<<"varf elastNoDirc([u,u1,u2],[v,v1,v2])                                                           \n"
<<"    = intN(Th,qforder=3)(                                                                       \n"
<<"            ((1 - uold2)*(1 - uold2) + 1e-6)*                                                   \n"
<<"            (lambda*divergence(u)*divergence(v)                                                 \n"
<<"            + 2.*mu*( epsilon(u)'*epsilon(v) ))                                                 \n"
<<"                );                                                                              \n";
/************************OLD METHOD*************************************************/  

}  //-- [if loop terminator] nonlinear vectorial ended --//


if(dynamic){writevarfmatsolve
<<"                                                                                                \n"
<<"//==============================================================================                \n"
<<"// -------Variation formulation dynamic linear-------                                           \n"
<<"//==============================================================================                \n"
<<"                                                                                                \n"
<<"varf elastodynamics( def(du) , def(v) )                                                         \n"
<<"                                                                                                \n"
<<"    = intN(Th,qforder=3)                                                                        \n"
<<"  (                                                                                             \n"
<<"      (def(du)'*def(v))*c[0]                                                                    \n"
<<"    + (divergence(du)*divergence(v))*c[1]                                                       \n"
<<"    + (epsilon(du)'*epsilon(v))*c[2]                                                            \n"
<<"  )                                                                                             \n"
<<"                                                                                                \n"
<<"    + intN(Th,qforder=2)                                                                        \n"
<<"  (                                                                                             \n"
<<"      (def(uold)'*def(v))*c[0]                                                                  \n"
<<"    + (def(vold)'*def(v))*c[3]                                                                  \n"
<<"    + (def(aold)'*def(v))*c[4]                                                                  \n"
<<"    - (divergence(uold)*divergence(v))*c[5]                                                     \n"
<<"    - (epsilon(uold)'*epsilon(v))*c[6]                                                          \n"
<<"    + (divergence(vold)*divergence(v))*c[7]                                                     \n"
<<"    + (divergence(aold)*divergence(v))*c[8]                                                     \n"
<<"    + (epsilon(vold)'*epsilon(v))*c[9]                                                          \n"
<<"    + (epsilon(aold)'*epsilon(v))*c[10]                                                         \n"
<<"  )                                                                                             \n"
<<"                                                                                                \n"
/************************OLD METHOD*************************************************
<<"    = intN(Th,qforder=3)                                                                        \n"
<<"  (                                                                                             \n"
<<"                                                                                                \n"
<<"   //  mass  matrix [M]du  //                                                                   \n"
<<"       rho*(1.-alpm)/(beta*dt*dt) *def(du)'*def(v)                                              \n"
<<"                                                                                                \n"
<<"   //  elastis [K]du       //                                                                   \n"
<<"     + lambda*(1.-alpf)*divergence(du)*divergence(v)                                            \n"
<<"     + 2.*mu*(1.-alpf)* epsilon(du)'*epsilon(v)                                                 \n"
<<"                                                                                                \n"
<<"   //  damping [C]du       //                                                                   \n"
<<"     + (etam*rho*gamma*(1-alpf)/(beta*dt)) *def(du)'*def(v)                                     \n"
<<"     + (etak*gamma*(1-alpf)/(beta*dt)*lambda)*(divergence(du)*divergence(v))                    \n"
<<"     + (etak*gamma*(1-alpf)/(beta*dt) * 2.*mu)*(epsilon(du)'*epsilon(v))                        \n"
<<"                                                                                                \n" 
<<"  )                                                                                             \n"
<<"                                                                                                \n"
<<"    + intN(Th,qforder=3)                                                                        \n"
<<"  (                                                                                             \n"
<<"                                                                                                \n"
<<"   //  mass  matrix [M]{uold+vold+aold}  //                                                     \n"
<<"     + (rho*(1.-alpm)/(beta*dt*dt))  *def(uold)'*def(v)                                         \n"
<<"     + (rho*(1.-alpm)/(beta*dt) )    *def(vold)'*def(v)                                         \n"
<<"     + (rho*(1.-alpm)*(1.-2.*beta)/2./beta)*def(aold)'*def(v)                                   \n"
<<"     - rho*(alpm)*def(aold)'*def(v)                                                             \n"
<<"                                                                                                \n"
<<"   //  elastis [K]{uold+vold+aold}       //                                                     \n"
<<"     - lambda*alpf*divergence(uold)*divergence(v)                                               \n"
<<"     - 2.*mu*alpf* epsilon(uold)'*epsilon(v)                                                    \n"
<<"                                                                                                \n"
<<"   //  damping E_m[M]{uold+vold+aold}    //                                                     \n"
<<"                                                                                                \n"
<<"     + etam*rho*gamma*(1.-alpf)/(dt*beta)*def(uold)'*def(v)                                     \n"
<<"     + etam*rho*(1-gamma*(1-alpf)/beta)*def(vold)'*def(v)                                       \n"
<<"     + etam*rho*dt*(1.-alpf)*(1.-gamma/(2*beta))*def(aold)'*def(v)                              \n"
<<"                                                                                                \n"
<<"   //  damping E_k[K]{uold+vold+aold}    //                                                     \n"
<<"                                                                                                \n"
<<"     + (etak*gamma*(1.-alpf)/(beta*dt)*lambda)*(divergence(uold)*divergence(v))                 \n"
<<"     + (etak*gamma*(1.-alpf)/(beta*dt)*2.*mu)*(epsilon(uold)'*epsilon(v))                       \n"
<<"     + (etak*(gamma*(1.-alpf)/beta)*lambda)*(divergence(vold)*divergence(v))                    \n"
<<"     + (etak*(gamma*(1.-alpf)/beta)*2.*mu)*(epsilon(vold)'*epsilon(v))                          \n"
<<"     - (etak*lambda)*(divergence(vold)*divergence(v))                                           \n"
<<"     - (etak*2.*mu)*(epsilon(vold)'*epsilon(v))                                                 \n"
<<"     - (etak*dt*(1.-alpf)*(1.-gamma)*lambda)*(divergence(aold)*divergence(v))                   \n"
<<"     - (etak*dt*(1.-alpf)*(1.-gamma)*2.*mu)*(epsilon(aold)'*epsilon(v))                         \n"
<<"+ (etak*dt*(1.-alpf)*(1.-2*beta)/2./beta*lambda)*(divergence(aold)*divergence(v))               \n"
<<"     + (etak*dt*(1.-alpf)*(1.-2*beta)/2./beta*2.*mu)*(epsilon(aold)'*epsilon(v))                \n"
<<"                                                                                                \n"
<<"  )                                                                                             \n"
/************************OLD METHOD*************************************************/  
<<"                                                                                                \n"
<<"    + intN1(Th,qforder=2,"<<labRface<<")                                                        \n"
<<"  (                                                                                             \n"
<<"     tr * v1                                           // Time dependent loading                \n"
<<"  )                                                                                             \n"
<<"                                                                                                \n"
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    + on                                                                                        \n"
<<"  (                                                                                             \n"
<<"         "<<labLface<<"        ,                        // Constrain  (Dirichlet)               \n"
<<"         du  = 0  ,                                                                             \n"
<<"         du1 = 0                                                                                \n"
<<"  )                                                                                             \n"
<<";                                                                                               \n"
<<"                                                                                                \n";

}  //-- [if loop terminator] dynamic Sequential ended --//



if(soildynamics){writevarfmatsolve
<<"                                                                                                \n"
<<"//==============================================================================                \n"
<<"// -------Variation formulation soil-dynamics -------                                           \n"
<<"//==============================================================================                \n"
<<"                                                                                                \n"
<<"varf elastodynamics( def(du) , def(v) )                                                         \n"
<<"                                                                                                \n"
<<"    = intN(Th,qforder=3)                                                                        \n"
<<"  (                                                                                             \n"
<<"      (def(du)'*def(v))*c[0]                                                                    \n"
<<"    + (divergence(du)*divergence(v))*c[1]                                                       \n"
<<"    + (epsilon(du)'*epsilon(v))*c[2]                                                            \n"
<<"  )                                                                                             \n"
<<"                                                                                                \n"
<<"    + intN(Th,qforder=2)                                                                        \n"
<<"  (                                                                                             \n"
<<"      (def(uold)'*def(v))*c[0]                                                                  \n"
<<"    + (def(vold)'*def(v))*c[3]                                                                  \n"
<<"    + (def(aold)'*def(v))*c[4]                                                                  \n"
<<"    - (divergence(uold)*divergence(v))*c[5]                                                     \n"
<<"    - (epsilon(uold)'*epsilon(v))*c[6]                                                          \n"
<<"  )                                                                                             \n"
<<"                                                                                                \n" 
<<"    + intN1(Th,qforder=3,PAlabels)                                                              \n"
<<"  (                                                                                             \n"
<<"      c[7]*(  PA0(du)'*def(v)  )                                                                \n" 
<<"  )                                                                                             \n"
<<"                                                                                                \n" 
<<"    + intN1(Th,qforder=2,PAlabels)                                                              \n"
<<"  (                                                                                             \n"
<<"      c[7]*(  PA0(uold)'*def(v)  )                                                              \n"
<<"    - c[8]*(  PA0(vold)'*def(v)  )                                                              \n" 
<<"    - c[9]*(  PA0(aold)'*def(v)  )                                                              \n" 
<<"  )                                                                                             \n";

if(spc==2)writevarfmatsolve
<<"                                                                                                \n" 
<<"    + intN1(Th,qforder=2,LoadLabels)                                                            \n"
<<"  (                                                                                             \n"
<<"     rho*(                                                                                      \n" 
<<"           (  cp*(N.x*N.x*0 + N.x*N.y*v1in)                                                     \n" 
<<"             +cs*((1.-N.x*N.x)*0 - N.x*N.y*v1in))*v                                             \n" 
<<"          +(  cp*(N.x*N.y*0 + N.y*N.y*v1in)                                                     \n" 
<<"             +cs*(- N.x*N.y*0+ (1.-N.y*N.y)*v1in ))*v1                                          \n" 
<<"          )                                                                                     \n" 
<<"  )                                                                                             \n";

if(spc==3)writevarfmatsolve
<<"                                                                                                \n" 
<<"    + intN1(Th,qforder=2,LoadLabels)                                                            \n"
<<"  (                                                                                             \n"
<<"     rho*(                                                                                      \n" 
<<"           (  cp*( N.x*N.x*0 + N.x*N.y*v1in + N.x*N.z*0)                                        \n" 
<<"             +cs*((1.-N.x*N.x)*0 - N.x*N.y*v1in - N.x*N.z*0))*v                                 \n" 
<<"          +(  cp*( N.x*N.y*0 + N.y*N.y*v1in + N.y*N.z*0)                                        \n" 
<<"             +cs*(-N.x*N.y*0 + (1.-N.y*N.y)*v1in - N.y*N.z*0))*v1                               \n" 
<<"          +(  cp*( N.x*N.z*0 + N.y*N.z*v1in + N.z*N.z*0)                                        \n" 
<<"             +cs*(-N.x*N.z*0 - N.z*N.y*v1in + (1.-N.z*N.z)*0))*v2                               \n"
<<"          )                                                                                     \n" 
<<"  )                                                                                             \n";
                
writevarfmatsolve
<<"                                                                                                \n" 
<<" /*  //---- uncomment if the load is not on paraxial border ----//                              \n" 
<<"                                                                                                \n" 
<<"    + intN1(Th,qforder=2,LoadLabels)                                                            \n"
<<"  (                                                                                             \n"
<<"     load1*v+load2*v1                                                                           \n"
<<"  )                                                                                             \n"
<<" */                                                                                             \n"
<<"                                                                                                \n" 
<<";                                                                                               \n" 
<<"                                                                                                \n";

}  //-- [if loop terminator] dynamic Sequential ended --//

if(quasistatic){writevarfmatsolve
<<"                                                                                                \n"
<<"//==============================================================================                \n"
<<"// -------Variation formulation linear-------                                                   \n"
<<"//==============================================================================                \n"
<<"                                                                                                \n"
<<"varf varIncr(def(du), def(v))                                                                   \n"
<<"    = intN(Th,qforder=3)(                                                                       \n"
<<"            (1-damage) * stress(du,lambdafield,mufield)' * epsilon(v)                           \n"
<<"                         )                                                                      \n"
<<"     - intN(Th,qforder=2)(                                                                      \n"
<<"                     (1-damage) * stress(u,lambdafield,mufield)' * epsilon(v)                   \n"
<<"                         )                                                                      \n";

if(bodyforce)writevarfmatsolve
<<"    + intN(Th,qforder=2)(BF'*def2(v))    // Body force     (volumetric)                         \n";

//if(tractionbc)writevarfmatsolve
//<<"    + intN1(Th,Tlabel,qforder=2)(T'*def2(v))// Traction force (Neumann BC)                    \n";

if(tractionconditions>=1)if(spc==2)
for(int i=0; i<tractionconditions; i++)
writevarfmatsolve
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $+int_{\\partial\\Omega_N}(T.v)$                                                        \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    + intN1(Th,Tlabel["<<i<<"],qforder=2)(T(tx"<<i<<",ty"<<i<<")'*def2(v))                      \n";

if(tractionconditions>=1)if(spc==3)
for(int i=0; i<tractionconditions; i++)
writevarfmatsolve
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $+int_{\\partial\\Omega_N}(T.v)$                                                        \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    + intN1(Th,Tlabel["<<i<<"],qforder=2)(T(tx"<<i<<",ty"<<i<<",tz"<<i<<")'*def2(v))            \n";


if(dirichletbc)if(spc==3)writevarfmatsolve
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    + on(2, du=duimp)                                                                           \n"
<<"    + on(1, du=0    )                                                                           \n"
<<"    + on(4, du1=0   )                                                                           \n"
<<"    + on(5, du2=0   ) ;                                                                         \n";

if(dirichletbc)if(spc==2)writevarfmatsolve
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    + on(4, du=duimp)                                                                           \n"
<<"    + on(2, du=0    )                                                                           \n"
<<"    + on(5, du1=0   ) ;                                                                         \n";

}  //-- [if loop terminator] dquasistatic ended --//

} //-- [ostream terminator]  varfmatsolve.edp closed --//

cout << " .................. Done \n";