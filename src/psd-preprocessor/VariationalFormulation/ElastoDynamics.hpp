//=================================================================================================
// ------ Building the VariationalFormulations.edp file ------
//=================================================================================================


 writeIt
 "                                                                                                \n"
 "//==============================================================================\\              \n"
 "//  **Variation formulation elastodynamic linear**                              \\              \n"
 "//==============================================================================\\              \n"
 "                                                                                                \n"
 "varf elastodynamics( def(du) , def(v) )                                                         \n"
 "                                                                                                \n"
 "/*                                                                                              \n"
 "$$                                                                                              \n"
 "\\int_{\\Omega}(                                                                                \n"
 "                    (du \\cdot v) c_0                                                           \n"
 "                  + (\\nabla \\cdot du  \\nabla \\cdot v) c_1                                   \n"
 "                  + (\\varepsilon(du) : \\varepsilon(v) ) c_2                                   \n"
 "               )                                                                                \n"
 "$$                                                                                              \n"
 "*/                                                                                              \n"
 "                                                                                                \n"
 "    = intN(Th,qforder=3)                                                                        \n"
 "  (                                                                                             \n"
 "      (def(du)'*def(v))*c[0]                                                                    \n"
 "    + (divergence(du)*divergence(v))*c[1]                                                       \n"
 "    + (epsilon(du)'*epsilon(v))*c[2]                                                            \n"
 "  )                                                                                             \n"
 "                                                                                                \n"
 "/*                                                                                              \n"
 "$$                                                                                              \n"
 "\\int_{\\Omega}(                                                                                \n"
 "                    (U \\cdot v) c_0                                                            \n"
 "                  + (V \\cdot v) c_3                                                            \n"
 "                  + (A \\cdot v) c_4                                                            \n"
 "                  - (\\nabla \\cdot U  \\nabla \\cdot v) c_5                                    \n"
 "                  - (\\varepsilon(U) : \\varepsilon(v) ) c_6                                    \n"
 "                  - (\\nabla \\cdot V  \\nabla \\cdot v) c_7                                    \n"
 "                  - (\\varepsilon(V) : \\varepsilon(v) ) c_8                                    \n"
 "                  - (\\nabla \\cdot A  \\nabla \\cdot v) c_9                                    \n"
 "                  - (\\varepsilon(A) : \\varepsilon(v) ) c_{10}                                 \n"
 "               )                                                                                \n"
 "$$                                                                                              \n"
 "*/                                                                                              \n"
 "                                                                                                \n"
 "    + intN(Th,qforder=3)                                                                        \n"
 "  (                                                                                             \n"
 "      (def(uold)'*def(v))*c[0]                                                                  \n"
 "    + (def(vold)'*def(v))*c[3]                                                                  \n"
 "    + (def(aold)'*def(v))*c[4]                                                                  \n"
 "    - (divergence(uold)*divergence(v))*c[5]                                                     \n"
 "    - (epsilon(uold)'*epsilon(v))*c[6]                                                          \n"
 "    + (divergence(vold)*divergence(v))*c[7]                                                     \n"
 "    + (divergence(aold)*divergence(v))*c[8]                                                     \n"
 "    + (epsilon(vold)'*epsilon(v))*c[9]                                                          \n"
 "    + (epsilon(aold)'*epsilon(v))*c[10]                                                         \n"
 "  )                                                                                             \n"
 "                                                                                                \n";
/************************OLD METHOD*************************************************
 "    = intN(Th,qforder=3)                                                                        \n"
 "  (                                                                                             \n"
 "                                                                                                \n"
 "   //  mass  matrix [M]du  //                                                                   \n"
 "       rho*(1.-alpm)/(beta*dt*dt) *def(du)'*def(v)                                              \n"
 "                                                                                                \n"
 "   //  elastis [K]du       //                                                                   \n"
 "     + lambda*(1.-alpf)*divergence(du)*divergence(v)                                            \n"
 "     + 2.*mu*(1.-alpf)* epsilon(du)'*epsilon(v)                                                 \n"
 "                                                                                                \n"
 "   //  damping [C]du       //                                                                   \n"
 "     + (etam*rho*gamma*(1-alpf)/(beta*dt)) *def(du)'*def(v)                                     \n"
 "     + (etak*gamma*(1-alpf)/(beta*dt)*lambda)*(divergence(du)*divergence(v))                    \n"
 "     + (etak*gamma*(1-alpf)/(beta*dt) * 2.*mu)*(epsilon(du)'*epsilon(v))                        \n"
 "                                                                                                \n"
 "  )                                                                                             \n"
 "                                                                                                \n"
 "    + intN(Th,qforder=3)                                                                        \n"
 "  (                                                                                             \n"
 "                                                                                                \n"
 "   //  mass  matrix [M]{uold+vold+aold}  //                                                     \n"
 "     + (rho*(1.-alpm)/(beta*dt*dt))  *def(uold)'*def(v)                                         \n"
 "     + (rho*(1.-alpm)/(beta*dt) )    *def(vold)'*def(v)                                         \n"
 "     + (rho*(1.-alpm)*(1.-2.*beta)/2./beta)*def(aold)'*def(v)                                   \n"
 "     - rho*(alpm)*def(aold)'*def(v)                                                             \n"
 "                                                                                                \n"
 "   //  elastis [K]{uold+vold+aold}       //                                                     \n"
 "     - lambda*alpf*divergence(uold)*divergence(v)                                               \n"
 "     - 2.*mu*alpf* epsilon(uold)'*epsilon(v)                                                    \n"
 "                                                                                                \n"
 "   //  damping E_m[M]{uold+vold+aold}    //                                                     \n"
 "                                                                                                \n"
 "     + etam*rho*gamma*(1.-alpf)/(dt*beta)*def(uold)'*def(v)                                     \n"
 "     + etam*rho*(1-gamma*(1-alpf)/beta)*def(vold)'*def(v)                                       \n"
 "     + etam*rho*dt*(1.-alpf)*(1.-gamma/(2*beta))*def(aold)'*def(v)                              \n"
 "                                                                                                \n"
 "   //  damping E_k[K]{uold+vold+aold}    //                                                     \n"
 "                                                                                                \n"
 "     + (etak*gamma*(1.-alpf)/(beta*dt)*lambda)*(divergence(uold)*divergence(v))                 \n"
 "     + (etak*gamma*(1.-alpf)/(beta*dt)*2.*mu)*(epsilon(uold)'*epsilon(v))                       \n"
 "     + (etak*(gamma*(1.-alpf)/beta)*lambda)*(divergence(vold)*divergence(v))                    \n"
 "     + (etak*(gamma*(1.-alpf)/beta)*2.*mu)*(epsilon(vold)'*epsilon(v))                          \n"
 "     - (etak*lambda)*(divergence(vold)*divergence(v))                                           \n"
 "     - (etak*2.*mu)*(epsilon(vold)'*epsilon(v))                                                 \n"
 "     - (etak*dt*(1.-alpf)*(1.-gamma)*lambda)*(divergence(aold)*divergence(v))                   \n"
 "     - (etak*dt*(1.-alpf)*(1.-gamma)*2.*mu)*(epsilon(aold)'*epsilon(v))                         \n"
 "+ (etak*dt*(1.-alpf)*(1.-2*beta)/2./beta*lambda)*(divergence(aold)*divergence(v))               \n"
 "     + (etak*dt*(1.-alpf)*(1.-2*beta)/2./beta*2.*mu)*(epsilon(aold)'*epsilon(v))                \n"
 "                                                                                                \n"
 "  )                                                                                             \n"
/************************OLD METHOD*************************************************/

if(Model=="pseudo_nonlinear")
 writeIt
 "                                                                                                \n"
 "                                                                                                \n"
 "/*                                                                                              \n"
 "$$                                                                                              \n"
 "\\int_{\\Omega}(                                                                                \n"
 "                    (u_{nl} \\cdot v) c_0                                                       \n"
 "                  + (\\nabla \\cdot u_{nl}  \\nabla \\cdot v) c_1                               \n"
 "                  + (\\varepsilon(u_{nl}) : \\varepsilon(v) ) c_2                               \n"
 "               )                                                                                \n"
 "$$                                                                                              \n"
 "*/                                                                                              \n"
 "                                                                                                \n"
 "    - intN(Th,qforder=3)                                                                        \n"
 "  (                                                                                             \n"
 "      (def(uNL)'*def(v))*c[0]                                                                   \n"
 "    + (divergence(uNL)*divergence(v))*c[1]                                                      \n"
 "    + (epsilon(uNL)'*epsilon(v))*c[2]                                                           \n"
 "  )                                                                                             \n"
 "                                                                                                \n";

if(tractionconditions>=1)
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


 writeIt
 ";                                                                                               \n"
 "                                                                                                \n";