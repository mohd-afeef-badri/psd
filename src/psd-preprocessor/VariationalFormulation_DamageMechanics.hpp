//=================================================================================================
// ------ Building the VariationalFormulations.edp file ------
//=================================================================================================


if(Model=="hybrid-phase-field" && NonLinearMethod=="Picard")
if(!vectorial){write
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

if(bodyforce)write
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    // $+int_{\\Omega}(f.v)$                                                                    \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      + intN(Th,qforder=3)(BF'*def2(v))    // Body force     (volumetric)                       \n";


//if(tractionbc)write
//<<"    + intN1(Th,Tlabel,qforder=3)(T'*def2(v))// Traction force (Neumann BC)                    \n";

if(tractionconditions>=1)if(spc==2)
for(int i=0; i<tractionconditions; i++)
write
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $+int_{\\partial\\Omega_N}(T.v)$                                                        \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      + intN1(Th,Tlabel["<<i<<"],qforder=3)(T(tx"<<i<<",ty"<<i<<")'*def2(v))                    \n";

if(tractionconditions>=1)if(spc==3)
for(int i=0; i<tractionconditions; i++)
write
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $+int_{\\partial\\Omega_N}(T.v)$                                                        \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      + intN1(Th,Tlabel["<<i<<"],qforder=3)(T(tx"<<i<<",ty"<<i<<",tz"<<i<<")'*def2(v))          \n";


if(dirichletbc){

for(int i=0; i<dirichletconditions; i++)
write
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      + on (DirichletBorder"<<i<<")                                                             \n";

}  //-- [if loop terminator] dirichletbc ended --//

write
<<";                                                                                               \n";

/************************OLD METHOD*************************************************
if(pipegnu)write
<<"                                                                                \n"
<<"varf elastNoDirc(def2(u),def2(v))                                               \n"
<<"    = intN(Th,qforder=3)(                                                       \n"
<<"            ((1 - phiold)*(1 - phiold) + 1e-6)*                                 \n"
<<"            (lambda*divergence(u)*divergence(v)                                 \n"
<<"            +2.*mu*( epsilon(u)'*epsilon(v) ))                                  \n"
<<"                );                                                              \n";
/************************OLD METHOD*************************************************/


write
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
<<(energydecomp  ? "\t\t\t  ( ((Gc/lo)  + 2.*HistPlus)*phi*q )\n"         : ""                      )
<<(!energydecomp ? "\t\t\t  ( ((Gc/lo)  + 2.*Hplus(u))*phi*q )\n"  : ""                             )
<<"                       )                                                                        \n"
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    // $+int_{\\Omega}((2H^{+}) q)$                                                             \n"
<<"    //--------------------------------------------------------------------------                \n"
<<(energydecomp  ? "\t+ intN(Th,qforder=3)(  2.*HistPlus*q  )\n"         : ""                       )
<<(!energydecomp ? "\t+ intN(Th,qforder=3)(  2.*Hplus(u)*q  )\n"  : ""                              )
<<"                                                                                                \n";

write
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      + on(4,phi=1)             //  Cracked (Dirichlet)                                         \n";

write
<<";                                                                                               \n";

}  //-- [if loop terminator] hybrid-phase-field picard non-vectorial ended --//



if(Model=="hybrid-phase-field" && NonLinearMethod=="Newton-Raphson")
if(!vectorial){write
<<"                                                                                                \n"
<<"//==============================================================================                \n"
<<"// ---Variation formulation hybrid phase-field (Staggered Newton-Raphsons)----                  \n"
<<"//==============================================================================                \n"
<<"                                                                                                \n"
<<"  real TractionIn = tr;                                                                         \n"
<<"  real PhiCracked = 1.;                                                                         \n"
<<"                                                                                                \n"
<<" //-----------------------------                                                                \n"
<<" // Eq. 1 Linear momentum     //                                                                \n"
<<" //-----------------------------                                                                \n"
<<"                                                                                                \n"
<<" varf elast(def2(du),def2(v)) =                                                                 \n"
<<"                                                                                                \n"
<<"                           //--- Bilinear(K_uu ) ---//                                          \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    // $+int_{\\Omega}(((1-\\phi)^2+k)(\\epsilon(du):\\mathbbm(E):\\epsilon(v)))$               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      intN(Th,qforder=3)(                                                                       \n"
<<"         ((1 - phi)*(1 - phi) + 1e-6)*                                                          \n"
<<"         (lambda*divergence(du)*divergence(v)                                                   \n"
<<"         + 2.*mu*( epsilon(du)'*epsilon(v) ))                                                   \n"
<<"                        )                                                                       \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"                                                                                                \n"
<<"                           //--- Linear(K_ud) ---//                                             \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    // $+int_{\\Omega}( 2(1-\\phi)(\\epsilon(u):\\epsilon(v))phi$                               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"     + intN(Th,qforder=3)(                                                                      \n"
<<"         2.*(1 - phi)*( epsilon(u)'*epsilon(v) )* phi                                           \n"
<<"                        )                                                                       \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"                                                                                                \n"
<<"                           //--- Linear(b_u) ---//                                              \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    // $+int_{\\Omega}(((1-\\phi)^2+k)(\\epsilon(u):\\mathbbm(E):\\epsilon(v)))$                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"     - intN(Th,qforder=3)(                                                                      \n"
<<"         ((1 - phi)*(1 - phi))*                                                                 \n"
<<"         (lambda*divergence(u)*divergence(v)                                                    \n"
<<"         + 2.*mu*( epsilon(u)'*epsilon(v) ))                                                    \n"
<<"                        )                                                                       \n"
<<"    //--------------------------------------------------------------------------                \n";

if(bodyforce)write
<<"                                                                                                \n"
<<"                           //--- Linear(b_u) ---//                                              \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    // $+int_{\\Omega}(f.v)$                                                                    \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      + intN(Th,qforder=3)(BF'*def2(v))    // Body force     (volumetric)                       \n";

if(tractionconditions>=1)if(spc==2)
for(int i=0; i<tractionconditions; i++)
write
<<"                                                                                                \n"
<<"                           //--- Linear(b_u) ---//                                              \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $+int_{\\partial\\Omega_N}(T.v)$                                                        \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      + intN1(Th,Tlabel["<<i<<"],qforder=3)(T(tx"<<i<<",ty"<<i<<")'*def2(v))                    \n";

if(tractionconditions>=1)if(spc==3)
for(int i=0; i<tractionconditions; i++)
write
<<"                                                                                                \n"
<<"                           //--- Linear(b_u) ---//                                              \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $+int_{\\partial\\Omega_N}(T.v)$                                                        \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      + intN1(Th,Tlabel["<<i<<"],qforder=3)(T(tx"<<i<<",ty"<<i<<",tz"<<i<<")'*def2(v))          \n";


if(dirichletbc){

if(spc==2)write
<<"                                                                                                \n"
<<"                             //--- Dirichlet ---//                                              \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      + on(Dlabel,du=Dvalue[0],du1=Dvalue[1])                                                   \n"
<<"                                                                                                \n"
<<"                             //--- Dirichlet ---//                                              \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      + on(2,du1=TractionIn)                 // Displacement (Dirichlet)                        \n";

if(spc==3)write
<<"                                                                                                \n"
<<"                             //--- Dirichlet ---//                                              \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      + on(Dlabel,du=Dvalue[0],du1=Dvalue[1],du2=Dvalue[2])                                     \n"
<<"                                                                                                \n"
<<"                             //--- Dirichlet ---//                                              \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      + on(2,du1=TractionIn)                                                                    \n";

}  //-- [if loop terminator] dirichletbc ended --//


write
<<";                                                                                               \n";

write
<<"                                                                                                \n"
<<" //-----------------------------                                                                \n"
<<" // Eq. 2 Helmothz           //                                                                 \n"
<<" //-----------------------------                                                                \n"
<<"                                                                                                \n"
<<"  varf phase(dphi,q) =                                                                          \n"
<<"                                                                                                \n"
<<"                           //--- Bilinear(K_dd ) ---//                                          \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    // $+int_{\\Omega}(G_cl_0(\\nabl{\\dphi}.\\nabla{q})+(G_c/l_0+2H^{+})\\dphi q)$             \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      intN(Th,qforder=3)(                                                                       \n"
<<"              (Gc*lo*(grad(dphi)'*grad(q))) +                                                   \n"
<<(energydecomp  ? "\t\t\t  ( ((Gc/lo)  + 2.*HistPlus)*dphi*q )\n"         : ""                     )
<<(!energydecomp ? "\t\t\t  ( ((Gc/lo)  + 2.*Hplus(u))*dphi*q )\n"  : ""                            )
<<"                       )                                                                        \n"
<<"                                                                                                \n"
<<"                           //--- Linear(K_du ) ---//                                            \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    // $+int_{\\Omega}((2H^{+}(i-\\phi)) q)$                                                    \n"
<<"    //--------------------------------------------------------------------------                \n"
<<(energydecomp  ? "\t+ intN(Th,qforder=3)(  2.*HistPlus*(1-phi)*q  )\n"         : ""               )
<<(!energydecomp ? "\t+ intN(Th,qforder=3)(  2.*Hplus(u)*(1-phi)*q  )\n"  : ""                      )
<<"                                                                                                \n"
<<"                           //--- Linear(b_d ) ---//                                             \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    // $+int_{\\Omega}(G_cl_0(\\nabl{\\phi}.\\nabla{q})+(G_c/l_0+2H^{+})\\phi q)$               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      - intN(Th,qforder=3)(                                                                     \n"
<<"              (Gc*lo*(grad(phi)'*grad(q))) +                                                    \n"
<<(energydecomp  ? "\t\t\t  ( ((Gc/lo)  /*+ 2.*HistPlus*/)*phi*q )\n"         : ""                  )
<<(!energydecomp ? "\t\t\t  ( ((Gc/lo)  /*+ 2.*Hplus(u)*/)*phi*q )\n"  : ""                         )
<<"                       )                                                                        \n"
<<"                                                                                                \n";

write
<<"                                                                                                \n"
<<"                             //--- Dirichlet ---//                                              \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      + on(4,dphi=PhiCracked)                                                                   \n";


write
<<";                                                                                               \n";

}  //-- [if loop terminator] hybrid-phase-field Newton-Raphsons non-vectorial ended --//


if(Prblm=="damage" && Model=="hybrid-phase-field")
if(vectorial){write
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

if(!energydecomp)write
<<"\t\t\t( ((Gc/lo)  + 2.*Hplus(uold))*u"<<spc<<"*v"<<spc<<" )                                     \n";
if(energydecomp)write
<<"\t\t\t( ((Gc/lo)  + 2.*HistPlus)*u"<<spc<<"*v"<<spc<<" )                                        \n";

write
<<"                         )                                                                      \n";

if(!energydecomp)write
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    // $+int_{\\Omega}((2H^{+}) q)$                                                             \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      + intN(Th,qforder=3)(  2.*Hplus(uold)*v"<<spc<<"  )                                       \n";
if(energydecomp)write
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    // $+int_{\\Omega}((2H^{+}) q)$                                                             \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"\t+ intN(Th,qforder=3)(  2.*HistPlus*v"<<spc<<"  )                                              \n";

/*
<<(!energydecomp  ? "\t\t\t( ((Gc/lo)  + 2.*Hplus(uold))*u"<<spc<<"*v"<<spc<<" )\n": ""             )
<<(energydecomp   ? "\t\t\t( ((Gc/lo)  + 2.*H)*u"<<spc<<"*v"<<spc<<" )\n"          : ""             )
<<(!energydecomp  ? "\t+ intN(Th,qforder=3)(  2.*Hplus(uold)*v"<<spc<<"  )\n": ""                   )
<<(energydecomp   ? "\t+ intN(Th,qforder=3)(  2.*H*v"<<spc<<"  )\n"          : ""                   )
*/

write
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    + on(4,u"<<spc<<" = 1)                          // Cracked (Dirichlet)                      \n";

if(dirichletbc){

for(int i=0; i<dirichletconditions; i++)
write
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"      + on (DirichletBorder"<<i<<")                                                             \n";

}  //-- [if loop terminator] dirichletbc ended --//

write
<<";                                                                                               \n";

/************************OLD METHOD*************************************************
if(pipegnu)write
<<"                                                                                                \n"
<<"varf elastNoDirc([u,u1,u2],[v,v1,v2])                                                           \n"
<<"    = intN(Th,qforder=3)(                                                                       \n"
<<"            ((1 - uold2)*(1 - uold2) + 1e-6)*                                                   \n"
<<"            (lambda*divergence(u)*divergence(v)                                                 \n"
<<"            + 2.*mu*( epsilon(u)'*epsilon(v) ))                                                 \n"
<<"                );                                                                              \n";
/************************OLD METHOD*************************************************/

}  //-- [if loop terminator] hybrid-phase-field picard vectorial ended --//

if(Model=="Mazar"){write
<<"                                                                                                \n"
<<"//==============================================================================                \n"
<<"// -------Variation formulation linear-------                                                   \n"
<<"//==============================================================================                \n"
<<"                                                                                                \n"
<<"varf varIncr(def(du), def(v))                                                                   \n"
<<"    = intN(Th,qforder=3)(                                                                       \n"
<<"            (1-damage) * stress(du,lambdafield,mufield)' * epsilon(v)                           \n"
<<"                         )                                                                      \n"
<<"     - intN(Th,qforder=3)(                                                                      \n"
<<"                     (1-damage) * stress(u,lambdafield,mufield)' * epsilon(v)                   \n"
<<"                         )                                                                      \n";

if(bodyforce)write
<<"    + intN(Th,qforder=3)(BF'*def2(v))    // Body force     (volumetric)                         \n";

//if(tractionbc)write
//<<"    + intN1(Th,Tlabel,qforder=3)(T'*def2(v))// Traction force (Neumann BC)                    \n";

if(tractionconditions>=1)if(spc==2)
for(int i=0; i<tractionconditions; i++)
write
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $+int_{\\partial\\Omega_N}(T.v)$                                                        \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    + intN1(Th,Tlabel["<<i<<"],qforder=3)(T(tx"<<i<<",ty"<<i<<")'*def2(v))                      \n";

if(tractionconditions>=1)if(spc==3)
for(int i=0; i<tractionconditions; i++)
write
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $+int_{\\partial\\Omega_N}(T.v)$                                                        \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    + intN1(Th,Tlabel["<<i<<"],qforder=3)(T(tx"<<i<<",ty"<<i<<",tz"<<i<<")'*def2(v))            \n";


if(dirichletbc)if(spc==3)write
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    + on(1, du=0    )                                                                           \n"
<<"    + on(2, du=duimp)                                                                           \n"
<<"    + on(4, du1=0   )                                                                           \n"
<<"    + on(5, du2=0   )                                                                           \n";

if(dirichletbc)if(spc==2)write
<<"                                                                                                \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
<<"    //--------------------------------------------------------------------------                \n"
<<"    + on(2, du=0    )                                                                           \n"
<<"    + on(4, du=duimp)                                                                           \n"
<<"    + on(5, du1=0   )                                                                           \n";

write
<<";                                                                                               \n"
<<"                                                                                                \n";

}  //-- [if loop terminator] quasistatic ended --//
