//=================================================================================================
// ------ Building the VariationalFormulations.edp file ------
//=================================================================================================


if(Model!="pseudo_nonlinear"){
 writeIt
 "                                                                                                \n"
 "//==============================================================================\\              \n"
 "//  **Variation formulation linear elasticity**                                 \\              \n"
 "//==============================================================================\\              \n"
 "                                                                                                \n"
 "varf elast(def(u),def(v)) =                                                                     \n"
 "                                                                                                \n";

if(fastmethod)
 writeIt
 "                                                                                                \n"
 "/*                                                                                              \n"
 "$$                                                                                              \n"
 "\\int_{\\Omega}(                                                                                \n"
 "                  (\\lambda:\\nabla(u).\\nabla(v))                                              \n"
 "                + (2\\mu(\\varepsilon(u):\\varepsilon(v)))                                      \n"
 "               )                                                                                \n"
 "$$                                                                                              \n"
 "*/                                                                                              \n"
 "                                                                                                \n"
 "      intN(Th,qforder=3)(                                                                       \n"
 "                     lambda*divergence(u)*divergence(v)                                         \n"
 "                   + 2.*mu*( epsilon(u)'*epsilon(v) )                                           \n";

if(!fastmethod)
 writeIt
 "                                                                                                \n"
 "/*                                                                                              \n"
 "$$                                                                                              \n"
 "\\int_{\\Omega}(                                                                                \n"
 "                 (\\epsilon(u):\\mathbbm(Mt):\\epsilon(v))                                      \n"
 "               )                                                                                \n"
 "$$                                                                                              \n"
 "*/                                                                                              \n"
 "                                                                                                \n"
 "      intN(Th,qforder=3)(                                                                       \n"
 "                       epsilonXMt(u,Mt)'*epsilon(v)                                             \n";

 writeIt
 "                     )                                                                          \n";

for(int i=0; i<bodyforceconditions; i++)
 writeIt
 "                                                                                                \n"
 "/*                                                                                              \n"
 "$$                                                                                              \n"
 "\\int_{\\Omega}( F \\cdot v )                                                                   \n"
 "$$                                                                                              \n"
 "*/                                                                                              \n"
 "                                                                                                \n"
 "     + intN(Th,Fbc"<<i<<"On,qforder=3)(BodyforceBc"<<i<<")                                      \n";

for(int i=0; i<tractionconditions; i++)
 writeIt
 "                                                                                                \n"
 "/*                                                                                              \n"
 "$$                                                                                              \n"
 "\\int_{\\partial\\Omega_N}( T \\cdot v )                                                        \n"
 "$$                                                                                              \n"
 "*/                                                                                              \n"
 "                                                                                                \n"
 "     + intN1(Th,Tbc"<<i<<"On,qforder=3)(NeumannBc"<<i<<")                                       \n";

for(int i=0; i<dirichletconditions; i++)
 writeIt
 "                                                                                                \n"
 "/*                                                                                              \n"
 "$$                                                                                              \n"
 "\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R                                         \n"
 "$$                                                                                              \n"
 "*/                                                                                              \n"
 "                                                                                                \n"
 "      + on (Dbc"<<i<<"On,DirichletBc"<<i<<")                                                    \n";
}


if(Model=="pseudo_nonlinear"){
 writeIt
 "                                                                                                \n"
 "//==============================================================================                \n"
 "// -------Variation formulation linear elasticity-------                                        \n"
 "//==============================================================================                \n"
 "                                                                                                \n"
 "                                                                                                \n"
 "varf elast(def(du),def(v)) =                                                                    \n"
 "                                                                                                \n";

if(fastmethod)
 writeIt
 "                                                                                                \n"
 "/*                                                                                              \n"
 "$$                                                                                              \n"
 "\\int_{\\Omega}(                                                                                \n"
 "                  (\\lambda:\\nabla(du).\\nabla(v))                                             \n"
 "                + (2\\mu(\\varepsilon(du):\\varepsilon(v)))                                     \n"
 "               )                                                                                \n"
 "$$                                                                                              \n"
 "*/                                                                                              \n"
 "                                                                                                \n"
 "      intN(Th,qforder=3)(                                                                       \n"
 "                     lambda*divergence(du)*divergence(v)                                        \n"
 "                   + 2.*mu*( epsilon(du)'*epsilon(v) )                                          \n"
 "                     )                                                                          \n"
 "                                                                                                \n"
 "                                                                                                \n"
 "/*                                                                                              \n"
 "$$                                                                                              \n"
 "-\\int_{\\Omega}(                                                                               \n"
 "                  (\\lambda:\\nabla(u).\\nabla(v))                                              \n"
 "                + (2\\mu(\\varepsilon(u):\\varepsilon(v)))                                      \n"
 "               )                                                                                \n"
 "$$                                                                                              \n"
 "*/                                                                                              \n"
 "                                                                                                \n"
 "     - intN(Th,qforder=2)(                                                                      \n"
 "                     lambda*divergence(u)*divergence(v)                                         \n"
 "                   + 2.*mu*( epsilon(u)'*epsilon(v) )                                           \n"
 "                     )                                                                          \n";

if(!fastmethod && !useMfront)
 writeIt
 "                                                                                                \n"
 "/*                                                                                              \n"
 "$$                                                                                              \n"
 "\\int_{\\Omega}(                                                                                \n"
 "                 (\\epsilon(du):\\mathbbm(Mt):\\epsilon(v))                                     \n"
 "               )                                                                                \n"
 "$$                                                                                              \n"
 "*/                                                                                              \n"
 "                                                                                                \n"
 "      intN(Th,qforder=3)(                                                                       \n"
 "                       epsilonXMt(du,Mt)'*epsilon(v)                                            \n"
 "                     )                                                                          \n"
 "                                                                                                \n"
 "/*                                                                                              \n"
 "$$                                                                                              \n"
 "\\int_{\\Omega}(                                                                                \n"
 "                 (\\epsilon(u):\\mathbbm(Mt):\\epsilon(v))                                      \n"
 "               )                                                                                \n"
 "$$                                                                                              \n"
 "*/                                                                                              \n"
 "                                                                                                \n"
 "     - intN(Th,qforder=2)(                                                                      \n"
 "                       epsilonXMt(u,Mt)'*epsilon(v)                                             \n"
 "                     )                                                                          \n";

if(!fastmethod && useMfront){
 writeIt
 "                                                                                                \n"
 "/*                                                                                              \n"
 "$$                                                                                              \n"
 "\\int_{\\Omega}(                                                                                \n"
 "                 (\\epsilon(du):\\mathbbm(Mt):\\epsilon(v))                                     \n"
 "               )                                                                                \n"
 "$$                                                                                              \n"
 "*/                                                                                              \n"
 "                                                                                                \n"
 "      intN(Th,qforder=3)(                                                                       \n"
 "                       epsilonXMt(du,Mt)'*epsilon(v)                                            \n"
 "                     )                                                                          \n"
 "                                                                                                \n";

 if(spc==2)
 writeIt
 "/*                                                                                              \n"
 "$$                                                                                              \n"
 "\\int_{\\Omega}(                                                                                \n"
 "                 (\\epsilon(u):\\mathbbm(Mt):\\epsilon(v))                                      \n"
 "               )                                                                                \n"
 "$$                                                                                              \n"
 "*/                                                                                              \n"
 "                                                                                                \n"
 "     - intN(Th,qforder=2)(                                                                      \n"
 "                       [Sig11, Sig22, Sig12]'*epsilon(v)                                        \n"
 "                     )                                                                          \n";

 if(spc==3)
 writeIt
 "/*                                                                                              \n"
 "$$                                                                                              \n"
 "\\int_{\\Omega}(                                                                                \n"
 "                 (\\epsilon(u):\\mathbbm(Mt):\\epsilon(v))                                      \n"
 "               )                                                                                \n"
 "$$                                                                                              \n"
 "*/                                                                                              \n"
 "                                                                                                \n"
 "     - intN(Th,qforder=2)(                                                                      \n"
 "                       [Sig11, Sig22, Sig33, Sig12, Sig13, Sig23]'*epsilon(v)                   \n"
 "                     )                                                                          \n";
}

for(int i=0; i<bodyforceconditions; i++)
 writeIt
 "                                                                                                \n"
 "/*                                                                                              \n"
 "$$                                                                                              \n"
 "\\int_{\\Omega}( F \\cdot v )                                                                   \n"
 "$$                                                                                              \n"
 "*/                                                                                              \n"
 "                                                                                                \n"
 "     + intN(Th,Fbc"<<i<<"On,qforder=3)(BodyforceBc"<<i<<")                                      \n";

for(int i=0; i<tractionconditions; i++)
 writeIt
 "                                                                                                \n"
 "/*                                                                                              \n"
 "$$                                                                                              \n"
 "\\int_{\\partial\\Omega_N}( T \\cdot v )                                                        \n"
 "$$                                                                                              \n"
 "*/                                                                                              \n"
 "                                                                                                \n"
 "     + intN1(Th,Tbc"<<i<<"On,qforder=3)(NeumannBc"<<i<<")                                       \n";

for(int i=0; i<dirichletconditions; i++)
 writeIt
 "                                                                                                \n"
 "/*                                                                                              \n"
 "$$                                                                                              \n"
 "\\forall x\\in\\partial\\Omega_D u=ug: ug\\to\\mathbb R                                         \n"
 "$$                                                                                              \n"
 "*/                                                                                              \n"
 "                                                                                                \n"
 "      + on (Dbc"<<i<<"On,DirichletBc"<<i<<")                                                    \n";
}

 writeIt
 ";                                                                                                \n"
  "                                                                                                \n";

