//=================================================================================================
// ------ Building the VariationalFormulations.edp file ------
//=================================================================================================


if(Model=="hybrid_phase_field" && NonLinearMethod=="Picard")
if(!vectorial){

 if(!constrainHPF)
 writeIt
 "                                                                                                \n"
 "//==============================================================================                \n"
 "// -------Variation formulation hybrid phase-field (Staggered)-------                           \n"
 "//==============================================================================                \n"
 "                                                                                                \n"
 " //-----------------------------                                                                \n"
 " // Eq. 1 Linear momentum     //                                                                \n"
 " //-----------------------------                                                                \n"
 "                                                                                                \n"
 " varf elast(def2(u),def2(v)) =                                                                  \n"
 "                                                                                                \n"
 "    //--------------------------------------------------------------------------                \n"
 "    // $+int_{\\Omega}(((1-\\phi)^2+k)(\\epsilon(u):\\mathbbm(E):\\epsilon(v)))$                \n"
 "    //--------------------------------------------------------------------------                \n"
 "      intN(Th,qforder=3)(                                                                       \n"
 "         ((1 - phiold)*(1 - phiold) + 1e-6)*                                                    \n"
 "         (lambda*divergence(u)*divergence(v)                                                    \n"
 "         + 2.*mu*( epsilon(u)'*epsilon(v) ))                                                    \n"
 "                        )                                                                       \n";
 

 if(constrainHPF)
 writeIt
 "                                                                                                \n"
 "//==============================================================================                \n"
 "// -------Variation formulation hybrid phase-field (Staggered)-------                           \n"
 "//==============================================================================                \n"
 "                                                                                                \n"
 " //-----------------------------                                                                \n"
 " // Eq. 1 Linear momentum     //                                                                \n"
 " //-----------------------------                                                                \n"
 "                                                                                                \n"
 " varf elast(def2(u),def2(v)) =                                                                  \n"
 "                                                                                                \n"
 "    //--------------------------------------------------------------------------                \n"
 "    // $+int_{\\Omega}(((1-\\phi)^2+k)(\\epsilon(u):\\mathbbm(E):\\epsilon(v)))$                \n"
 "    //--------------------------------------------------------------------------                \n"
 "      intN(Th,qforder=3)(                                                                       \n"
 "         ((1 - phip)*(1 - phip) + 1e-6)*                                                        \n"
 "         (lambda*divergence(u)*divergence(v)                                                    \n"
 "         + 2.*mu*( epsilon(u)'*epsilon(v) ))                                                    \n"
 "                        )                                                                       \n"; 

for(int i=0; i<bodyforceconditions; i++)
 writeIt
 "                                                                                                \n"
 "    //--------------------------------------------------------------------------                \n"
 "    //  $+int_{\\Omega}(f.v)$                                                                   \n"
 "    //--------------------------------------------------------------------------                \n"
 "     + intN(Th,Fbc"<<i<<"On,qforder=3)(BodyforceBc"<<i<<")                                      \n";

if(tractionconditions>=1)
for(int i=0; i<tractionconditions; i++)
 writeIt
 "                                                                                                \n"
 "    //--------------------------------------------------------------------------                \n"
 "    //  $+int_{\\partial\\Omega_N}(T.v)$                                                        \n"
 "    //--------------------------------------------------------------------------                \n"
 "     + intN1(Th,Tbc"<<i<<"On,qforder=3)(NeumannBc"<<i<<")                                       \n";


if(dirichletbc){

for(int i=0; i<dirichletconditions; i++)
 writeIt
 "                                                                                                \n"
 "    //--------------------------------------------------------------------------                \n"
 "    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
 "    //--------------------------------------------------------------------------                \n"
 "      + on (Dbc"<<i<<"On,DirichletBc"<<i<<")                                                    \n";

}  //-- [if loop terminator] dirichletbc ended --//


 writeIt
 ";                                                                                               \n";

/************************OLD METHOD*************************************************
if(pipegnu)
 writeIt
 "                                                                                \n"
 "varf elastNoDirc(def2(u),def2(v))                                               \n"
 "    = intN(Th,qforder=3)(                                                       \n"
 "            ((1 - phiold)*(1 - phiold) + 1e-6)*                                 \n"
 "            (lambda*divergence(u)*divergence(v)                                 \n"
 "            +2.*mu*( epsilon(u)'*epsilon(v) ))                                  \n"
 "                );                                                              \n";
/************************OLD METHOD*************************************************/



 writeIt
 "                                                                                                \n"
 " //-----------------------------                                                                \n"
 " // Eq. 2 Helmothz           //                                                                 \n"
 " //-----------------------------                                                                \n"
 "                                                                                                \n"
 "  varf phase(phi,q) =                                                                           \n"
 "                                                                                                \n"
 "    //--------------------------------------------------------------------------                \n"
 "    // $+int_{\\Omega}(G_cl_0(\\nabl{\\phi}.\\nabla{q})+(G_c/l_0+2H^{+})\\phi q)$               \n"
 "    //--------------------------------------------------------------------------                \n"
 "      intN(Th,qforder=3)(                                                                       \n"
 "              (Gc*lo*(grad(phi)'*grad(q))) +                                                    \n"
<<(energydecomp  ? "\t\t\t  ( ((Gc/lo)  + 2.*HistPlus)*phi*q )\n"         : ""                    )
<<(!energydecomp ? "\t\t\t  ( ((Gc/lo)  + 2.*Hplus(u))*phi*q )\n"  : ""                           )<<
 "                       )                                                                        \n"
 "                                                                                                \n"
 "    //--------------------------------------------------------------------------                \n"
 "    // $+int_{\\Omega}((2H^{+}) q)$                                                             \n"
 "    //--------------------------------------------------------------------------                \n"
<<(energydecomp  ? "\t+ intN(Th,qforder=3)(  2.*HistPlus*q  )\n"         : ""                     )
<<(!energydecomp ? "\t+ intN(Th,qforder=3)(  2.*Hplus(u)*q  )\n"  : ""                            )<<
 "                                                                                                \n";

 if(precracked)
 writeIt
 "                                                                                                \n"
 "    //--------------------------------------------------------------------------                \n"
 "    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
 "    //--------------------------------------------------------------------------                \n"
 "      + on(DbcCrackOn,phi=1)             //  Cracked (Dirichlet)                                \n";


 writeIt
 ";                                                                                               \n";

}  //-- [if loop terminator] hybrid_phase_field picard non-vectorial ended --//



if(Model=="hybrid_phase_field" && NonLinearMethod=="Newton-Raphson")
if(!vectorial){
 writeIt
 "                                                                                                \n"
 "//==============================================================================                \n"
 "// ---Variation formulation hybrid phase-field (Staggered Newton-Raphsons)----                  \n"
 "//==============================================================================                \n"
 "                                                                                                \n"
 "  real TractionIn = tr;                                                                         \n"
 "  real PhiCracked = 1.;                                                                         \n"
 "                                                                                                \n"
 " //-----------------------------                                                                \n"
 " // Eq. 1 Linear momentum     //                                                                \n"
 " //-----------------------------                                                                \n"
 "                                                                                                \n"
 " varf elast(def2(du),def2(v)) =                                                                 \n"
 "                                                                                                \n"
 "                           //--- Bilinear(K_uu ) ---//                                          \n"
 "    //--------------------------------------------------------------------------                \n"
 "    // $+int_{\\Omega}(((1-\\phi)^2+k)(\\epsilon(du):\\mathbbm(E):\\epsilon(v)))$               \n"
 "    //--------------------------------------------------------------------------                \n"
 "      intN(Th,qforder=3)(                                                                       \n"
 "         ((1 - phi)*(1 - phi) + 1e-6)*                                                          \n"
 "         (lambda*divergence(du)*divergence(v)                                                   \n"
 "         + 2.*mu*( epsilon(du)'*epsilon(v) ))                                                   \n"
 "                        )                                                                       \n"
 "    //--------------------------------------------------------------------------                \n"
 "                                                                                                \n"
 "                           //--- Linear(K_ud) ---//                                             \n"
 "    //--------------------------------------------------------------------------                \n"
 "    // $+int_{\\Omega}( 2(1-\\phi)(\\epsilon(u):\\epsilon(v))phi$                               \n"
 "    //--------------------------------------------------------------------------                \n"
 "     + intN(Th,qforder=3)(                                                                      \n"
 "         2.*(1 - phi)*( epsilon(u)'*epsilon(v) )* phi                                           \n"
 "                        )                                                                       \n"
 "    //--------------------------------------------------------------------------                \n"
 "                                                                                                \n"
 "                           //--- Linear(b_u) ---//                                              \n"
 "    //--------------------------------------------------------------------------                \n"
 "    // $+int_{\\Omega}(((1-\\phi)^2+k)(\\epsilon(u):\\mathbbm(E):\\epsilon(v)))$                \n"
 "    //--------------------------------------------------------------------------                \n"
 "     - intN(Th,qforder=3)(                                                                      \n"
 "         ((1 - phi)*(1 - phi))*                                                                 \n"
 "         (lambda*divergence(u)*divergence(v)                                                    \n"
 "         + 2.*mu*( epsilon(u)'*epsilon(v) ))                                                    \n"
 "                        )                                                                       \n"
 "    //--------------------------------------------------------------------------                \n";

for(int i=0; i<bodyforceconditions; i++)
 writeIt
 "                                                                                                \n"
 "                           //--- Linear(b_u) ---//                                              \n" 
 "    //--------------------------------------------------------------------------                \n"
 "    //  $+int_{\\Omega}(f.v)$                                                                   \n"
 "    //--------------------------------------------------------------------------                \n"
 "     + intN(Th,Fbc"<<i<<"On,qforder=3)(BodyforceBc"<<i<<")                                      \n";

if(tractionconditions>=1)
for(int i=0; i<tractionconditions; i++)
 writeIt
 "                                                                                                \n"
 "                           //--- Linear(b_u) ---//                                              \n"
 "    //--------------------------------------------------------------------------                \n"
 "    //  $+int_{\\partial\\Omega_N}(T.v)$                                                        \n"
 "    //--------------------------------------------------------------------------                \n"
 "     + intN1(Th,Tbc"<<i<<"On,qforder=3)(NeumannBc"<<i<<")                                       \n";


if(dirichletbc){

if(spc==2)
 writeIt
 "                                                                                                \n"
 "                             //--- Dirichlet ---//                                              \n"
 "    //--------------------------------------------------------------------------                \n"
 "    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
 "    //--------------------------------------------------------------------------                \n"
 "      + on(Dlabel,du=Dvalue[0],du1=Dvalue[1])                                                   \n"
 "                                                                                                \n"
 "                             //--- Dirichlet ---//                                              \n"
 "    //--------------------------------------------------------------------------                \n"
 "    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
 "    //--------------------------------------------------------------------------                \n"
 "      + on(2,du1=TractionIn)                 // Displacement (Dirichlet)                        \n";

if(spc==3)
 writeIt
 "                                                                                                \n"
 "                             //--- Dirichlet ---//                                              \n"
 "    //--------------------------------------------------------------------------                \n"
 "    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
 "    //--------------------------------------------------------------------------                \n"
 "      + on(Dlabel,du=Dvalue[0],du1=Dvalue[1],du2=Dvalue[2])                                     \n"
 "                                                                                                \n"
 "                             //--- Dirichlet ---//                                              \n"
 "    //--------------------------------------------------------------------------                \n"
 "    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
 "    //--------------------------------------------------------------------------                \n"
 "      + on(2,du1=TractionIn)                                                                    \n";

}  //-- [if loop terminator] dirichletbc ended --//



 writeIt
 ";                                                                                               \n";


 writeIt
 "                                                                                                \n"
 " //-----------------------------                                                                \n"
 " // Eq. 2 Helmothz           //                                                                 \n"
 " //-----------------------------                                                                \n"
 "                                                                                                \n"
 "  varf phase(dphi,q) =                                                                          \n"
 "                                                                                                \n"
 "                           //--- Bilinear(K_dd ) ---//                                          \n"
 "    //--------------------------------------------------------------------------                \n"
 "    // $+int_{\\Omega}(G_cl_0(\\nabl{\\dphi}.\\nabla{q})+(G_c/l_0+2H^{+})\\dphi q)$             \n"
 "    //--------------------------------------------------------------------------                \n"
 "      intN(Th,qforder=3)(                                                                       \n"
 "              (Gc*lo*(grad(dphi)'*grad(q))) +                                                   \n"
<<(energydecomp  ? "\t\t\t  ( ((Gc/lo)  + 2.*HistPlus)*dphi*q )\n"         : ""                   )
<<(!energydecomp ? "\t\t\t  ( ((Gc/lo)  + 2.*Hplus(u))*dphi*q )\n"  : ""                          )<<
 "                       )                                                                        \n"
 "                                                                                                \n"
 "                           //--- Linear(K_du ) ---//                                            \n"
 "    //--------------------------------------------------------------------------                \n"
 "    // $+int_{\\Omega}((2H^{+}(i-\\phi)) q)$                                                    \n"
 "    //--------------------------------------------------------------------------                \n"
<<(energydecomp  ? "\t+ intN(Th,qforder=3)(  2.*HistPlus*(1-phi)*q  )\n"         : ""             )
<<(!energydecomp ? "\t+ intN(Th,qforder=3)(  2.*Hplus(u)*(1-phi)*q  )\n"  : ""                    )<<
 "                                                                                                \n"
 "                           //--- Linear(b_d ) ---//                                             \n"
 "    //--------------------------------------------------------------------------                \n"
 "    // $+int_{\\Omega}(G_cl_0(\\nabl{\\phi}.\\nabla{q})+(G_c/l_0+2H^{+})\\phi q)$               \n"
 "    //--------------------------------------------------------------------------                \n"
 "      - intN(Th,qforder=3)(                                                                     \n"
 "              (Gc*lo*(grad(phi)'*grad(q))) +                                                    \n"
<<(energydecomp  ? "\t\t\t  ( ((Gc/lo)  /*+ 2.*HistPlus*/)*phi*q )\n"         : ""                )
<<(!energydecomp ? "\t\t\t  ( ((Gc/lo)  /*+ 2.*Hplus(u)*/)*phi*q )\n"  : ""                       )<<
 "                       )                                                                        \n"
 "                                                                                                \n";

 if(precracked)
 writeIt
 "                                                                                                \n"
 "                             //--- Dirichlet ---//                                              \n"
 "    //--------------------------------------------------------------------------                \n"
 "    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
 "    //--------------------------------------------------------------------------                \n"
 "      + on(DbcCrackOn,dphi=PhiCracked)                                                          \n";



 writeIt
 ";                                                                                               \n";

}  //-- [if loop terminator] hybrid_phase_field Newton-Raphsons non-vectorial ended --//


if(Model=="hybrid_phase_field" && vectorial){
 writeIt
 "                                                                                                \n"
 "//==============================================================================                \n"
 "// -------Variation formulation hybrid phase-field (Vectorial)-------                           \n"
 "//==============================================================================                \n"
 "                                                                                                \n";

 if(!constrainHPF) 
 writeIt 
 "varf elast(def(u),def(v)) =                                                                     \n"
 "                                                                                                \n"
 "    //--------------------------------------------------------------------------                \n"
 "    // $+int_{\\Omega}(((1-\\phi)^2+k)(\\epsilon(u):\\mathbbm(E):\\epsilon(v)))$                \n"
 "    //--------------------------------------------------------------------------                \n"
 "      intN(Th,qforder=3)(                                                                       \n"
 "         ((1 - uold"<<spc<<")*(1 - uold"<<spc<<") + 1e-6)*                                      \n"
 "         (lambda*divergence(u)*divergence(v)                                                    \n"
 "         + 2.*mu*( epsilon(u)'*epsilon(v) ))                                                    \n"; 

 if(constrainHPF) 
 writeIt 
 "varf elast(def2(u),def2(v)) =                                                                   \n"
 "                                                                                                \n"
 "    //--------------------------------------------------------------------------                \n"
 "    // $+int_{\\Omega}(((1-\\phi)^2+k)(\\epsilon(u):\\mathbbm(E):\\epsilon(v)))$                \n"
 "    //--------------------------------------------------------------------------                \n"
 "      intN(Th,qforder=3)(                                                                       \n"
 "         ((1 - up"<<spc<<")*(1 - up"<<spc<<") + 1e-6)*                                          \n"
 "         (lambda*divergence(u)*divergence(v)                                                    \n"
 "         + 2.*mu*( epsilon(u)'*epsilon(v) ))                                                    \n"; 
 
 writeIt 
 "                                                                                                \n"
 "                    +                                                                           \n"
 "                                                                                                \n"
 "    //--------------------------------------------------------------------------                \n"
 "    // $+int_{\\Omega}(G_cl_0(\\nabl{\\phi}.\\nabla{q})+(G_c/l_0+2H^{+})\\phi q)$               \n"
 "    //--------------------------------------------------------------------------                \n"
 "         (Gc*lo*(grad(u"<<spc<<")'*grad(v"<<spc<<"))) +                                         \n";


if(!energydecomp)
 writeIt
 "\t\t\t( ((Gc/lo)  + 2.*Hplus(uold))*u"<<spc<<"*v"<<spc<<" )                                     \n";
if(energydecomp)
 writeIt
 "\t\t\t( ((Gc/lo)  + 2.*HistPlus)*u"<<spc<<"*v"<<spc<<" )                                        \n";


 writeIt
 "                         )                                                                      \n";

if(!energydecomp)
 writeIt
 "                                                                                                \n"
 "    //--------------------------------------------------------------------------                \n"
 "    // $+int_{\\Omega}((2H^{+}) q)$                                                             \n"
 "    //--------------------------------------------------------------------------                \n"
 "      + intN(Th,qforder=3)(  2.*Hplus(uold)*v"<<spc<<"  )                                       \n";
if(energydecomp)
 writeIt
 "                                                                                                \n"
 "    //--------------------------------------------------------------------------                \n"
 "    // $+int_{\\Omega}((2H^{+}) q)$                                                             \n"
 "    //--------------------------------------------------------------------------                \n"
 "\t+ intN(Th,qforder=3)(  2.*HistPlus*v"<<spc<<"  )                                              \n";

/*
<<(!energydecomp  ? "\t\t\t( ((Gc/lo)  + 2.*Hplus(uold))*u"<<spc<<"*v"<<spc<<" )\n": ""           )<<
<<(energydecomp   ? "\t\t\t( ((Gc/lo)  + 2.*H)*u"<<spc<<"*v"<<spc<<" )\n"          : ""           )<<
<<(!energydecomp  ? "\t+ intN(Th,qforder=3)(  2.*Hplus(uold)*v"<<spc<<"  )\n": ""                 )<<
<<(energydecomp   ? "\t+ intN(Th,qforder=3)(  2.*H*v"<<spc<<"  )\n"          : ""                 )<<
*/

 if(precracked)
 writeIt
 "                                                                                                \n"
 "    //--------------------------------------------------------------------------                \n"
 "    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
 "    //--------------------------------------------------------------------------                \n"
 "    + on(DbcCrackOn,u"<<spc<<" = 1)                          // Cracked (Dirichlet)             \n";

if(dirichletbc){

for(int i=0; i<dirichletconditions; i++)
 writeIt
 "                                                                                                \n"
 "    //--------------------------------------------------------------------------                \n"
 "    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
 "    //--------------------------------------------------------------------------                \n"
 "      + on (Dbc"<<i<<"On,DirichletBc"<<i<<")                                                    \n";

}  //-- [if loop terminator] dirichletbc ended --//


 writeIt
 ";                                                                                               \n";

/************************OLD METHOD*************************************************
if(pipegnu)
 writeIt
 "                                                                                                \n"
<<"varf elastNoDirc([u,u1,u2],[v,v1,v2])                                                           \n"
<<"    = intN(Th,qforder=3)(                                                                       \n"
<<"            ((1 - uold2)*(1 - uold2) + 1e-6)*                                                   \n"
<<"            (lambda*divergence(u)*divergence(v)                                                 \n"
<<"            + 2.*mu*( epsilon(u)'*epsilon(v) ))                                                 \n"
<<"                );                                                                              \n";
/************************OLD METHOD*************************************************/

}  //-- [if loop terminator] hybrid_phase_field picard vectorial ended --//

if(Model=="Mazar"){
 writeIt
 "                                                                                                \n"
 "//==============================================================================                \n"
 "// -------Variation formulation linear-------                                                   \n"
 "//==============================================================================                \n"
 "                                                                                                \n"
 "varf varIncr(def(du), def(v))                                                                   \n"
 "    = intN(Th,qforder=3)(                                                                       \n"
 "            (1-damage) * stress(du,lambdafield,mufield)' * epsilon(v)                           \n"
 "                         )                                                                      \n"
 "     - intN(Th,qforder=3)(                                                                      \n"
 "                     (1-damage) * stress(u,lambdafield,mufield)' * epsilon(v)                   \n"
 "                         )                                                                      \n";
 
 for(int i=0; i<bodyforceconditions; i++)
 writeIt
 "                                                                                                \n"
 "    //--------------------------------------------------------------------------                \n"
 "    //  $+int_{\\Omega}(f.v)$                                                                   \n"
 "    //--------------------------------------------------------------------------                \n"
 "     + intN(Th,Fbc"<<i<<"On,qforder=3)(BodyforceBc"<<i<<")                                      \n";

if(tractionconditions>=1)
for(int i=0; i<tractionconditions; i++)
 writeIt
 "                                                                                                \n"
 "    //--------------------------------------------------------------------------                \n"
 "    //  $+int_{\\partial\\Omega_N}(T.v)$                                                        \n"
 "    //--------------------------------------------------------------------------                \n"
 "     + intN1(Th,Tbc"<<i<<"On,qforder=3)(NeumannBc"<<i<<")                                       \n";


if(dirichletbc)if(spc==3)
 writeIt
 "                                                                                                \n"
 "    //--------------------------------------------------------------------------                \n"
 "    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
 "    //--------------------------------------------------------------------------                \n"
 "    + on(1, du=0    )                                                                           \n"
 "    + on(2, du=duimp)                                                                           \n"
 "    + on(4, du1=0   )                                                                           \n"
 "    + on(5, du2=0   )                                                                           \n";

if(dirichletbc)if(spc==2)
 writeIt
 "                                                                                                \n"
 "    //--------------------------------------------------------------------------                \n"
 "    //  $\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R$                               \n"
 "    //--------------------------------------------------------------------------                \n"
 "    + on(2, du=0    )                                                                           \n"
 "    + on(4, du=duimp)                                                                           \n"
 "    + on(5, du1=0   )                                                                           \n";


 writeIt
 ";                                                                                               \n"
 "                                                                                                \n";

}  //-- [if loop terminator] quasistatic ended --//

if(reactionforce && vectorial)
{
 writeIt
 "                                                                                                \n"
 "//==============================================================================                \n"
 "// -------Variation formulation for calculating force -------                                   \n"
 "//==============================================================================                \n"
 "                                                                                                \n";

 if(!constrainHPF)  
 writeIt
 "varf varfForce(def(u),def(v)) =                                                                 \n"
 "                                                                                                \n";

 if(constrainHPF)  
 writeIt
 "varf varfForce(def2(u),def2(v)) =                                                               \n"
 "                                                                                                \n";
  
 writeIt
 "    //--------------------------------------------------------------------------                \n"
 "    // $+int_{\\Omega}((\\epsilon(u):\\mathbbm(E):\\epsilon(v)))$                               \n"
 "    //--------------------------------------------------------------------------                \n"
 "      intN(Th,qforder=3)(                                                                       \n"
 "         (lambda*divergence(u)*divergence(v)                                                    \n"
 "         + 2.*mu*( epsilon(u)'*epsilon(v) )))                                                   \n"
 ";                                                                                               \n";
}

if(reactionforce && !vectorial)
{
 writeIt
 "                                                                                                \n"
 "//==============================================================================                \n"
 "// -------Variation formulation for calculating force -------                                   \n"
 "//==============================================================================                \n"
 "                                                                                                \n"
 "varf varfForce(def2(u),def2(v)) =                                                               \n"
 "                                                                                                \n"
 "    //--------------------------------------------------------------------------                \n"
 "    // $+int_{\\Omega}((\\epsilon(u):\\mathbbm(E):\\epsilon(v)))$                               \n"
 "    //--------------------------------------------------------------------------                \n"
 "      intN(Th,qforder=3)(                                                                       \n"
 "         (lambda*divergence(u)*divergence(v)                                                    \n"
 "         + 2.*mu*( epsilon(u)'*epsilon(v) )))                                                   \n"
 ";                                                                                               \n";
}

