//=================================================================================================
// ------ Building the VariationalFormulations.edp file ------
//=================================================================================================

writeIt
"                                                                                                \n"
"//==============================================================================                \n"
"// -------Variation formulation soil-dynamics -------                                           \n"
"//==============================================================================                \n"
"                                                                                                \n"
"varf soildynamics( def(du) , def(v) )                                                           \n"
"                                                                                                \n"
"    = intN(Th,qforder=3)                                                                        \n"
"  (                                                                                             \n"
"      (def(du)'*def(v))*c[0]                                                                    \n"
"    + (divergence(du)*divergence(v))*c[1]                                                       \n"
"    + (epsilon(du)'*epsilon(v))*c[2]                                                            \n"
"  )                                                                                             \n"
"                                                                                                \n"
"    + intN(Th,qforder=3)                                                                        \n"
"  (                                                                                             \n"
"      (def(uold)'*def(v))*c[0]                                                                  \n"
"    + (def(vold)'*def(v))*c[3]                                                                  \n"
"    + (def(aold)'*def(v))*c[4]                                                                  \n";

if(TimeDiscretization=="generalized_alpha" || TimeDiscretization=="hht_alpha")
 writeIt
 "    - (divergence(uold)*divergence(v))*c[5]                                                    \n"
 "    - (epsilon(uold)'*epsilon(v))*c[6]                                                         \n";

writeIt
"  )                                                                                             \n"
"                                                                                                \n"
"    + intN1(Th,qforder=3,PAlabels)                                                              \n"
"  (                                                                                             \n"
"      c[7]*(  PA0(du)'*def(v)  )                                                                \n"
"  )                                                                                             \n"
"                                                                                                \n"
"    + intN1(Th,qforder=3,PAlabels)                                                              \n"
"  (                                                                                             \n"
"      c[7]*(  PA0(uold)'*def(v)  )                                                              \n"
"    - c[8]*(  PA0(vold)'*def(v)  )                                                              \n"
"    - c[9]*(  PA0(aold)'*def(v)  )                                                              \n"
"  )                                                                                             \n";

if(doublecouple=="unused"){
 writeIt
 "                                                                                               \n";
 if(spc==2)
 writeIt
 "                                                                                               \n"
 "    + intN1(Th,qforder=3,LoadLabels)                                                           \n"
 "  (                                                                                            \n"
 "     rho*(                                                                                     \n"
 "           (  cp*(N.x*N.y*v1in)                                                                \n"
 "             +cs*(- N.x*N.y*v1in))*v                                                           \n"
 "          +(  cp*(N.y*N.y*v1in)                                                                \n"
 "             +cs*((1.-N.y*N.y)*v1in ))*v1                                                      \n"
 "          )                                                                                    \n"
 "  )                                                                                            \n"
 "                                                                                               \n"
 " /*   + intN1(Th,qforder=3,LoadLabels)                                                         \n"
 "  (                                                                                            \n"
 "     rho*(                                                                                     \n"
 "           (  cp*(N.x*N.x*0 + N.x*N.y*v1in)                                                    \n"
 "             +cs*((1.-N.x*N.x)*0 - N.x*N.y*v1in))*v                                            \n"
 "          +(  cp*(N.x*N.y*0 + N.y*N.y*v1in)                                                    \n"
 "             +cs*(- N.x*N.y*0+ (1.-N.y*N.y)*v1in ))*v1                                         \n"
 "          )                                                                                    \n"
 "  ) */                                                                                         \n";

 if(spc==3)
 writeIt
 "                                                                                                \n"
 "    + intN1(Th,qforder=3,LoadLabels)                                                            \n"
 "  (                                                                                             \n"
 "     rho*(                                                                                      \n"
 "           (  cp*( N.x*N.y*v1in)                                                                \n"
 "             +cs*(- N.x*N.y*v1in))*v                                                            \n"
 "          +(  cp*(  N.y*N.y*v1in )                                                              \n"
 "             +cs*( (1.-N.y*N.y)*v1in ))*v1                                                      \n"
 "          +(  cp*(  N.y*N.z*v1in )                                                              \n"
 "             +cs*( - N.z*N.y*v1in))*v2                                                          \n"
 "          )                                                                                     \n"
 "  )                                                                                             \n"
 "                                                                                                \n"
 "/*    + intN1(Th,qforder=3,LoadLabels)                                                          \n"
 "  (                                                                                             \n"
 "     rho*(                                                                                      \n"
 "           (  cp*( N.x*N.x*0 + N.x*N.y*v1in + N.x*N.z*0)                                        \n"
 "             +cs*((1.-N.x*N.x)*0 - N.x*N.y*v1in - N.x*N.z*0))*v                                 \n"
 "          +(  cp*( N.x*N.y*0 + N.y*N.y*v1in + N.y*N.z*0)                                        \n"
 "             +cs*(-N.x*N.y*0 + (1.-N.y*N.y)*v1in - N.y*N.z*0))*v1                               \n"
 "          +(  cp*( N.x*N.z*0 + N.y*N.z*v1in + N.z*N.z*0)                                        \n"
 "             +cs*(-N.x*N.z*0 - N.z*N.y*v1in + (1.-N.z*N.z)*0))*v2                               \n"
 "          )                                                                                     \n"
 "  )*/                                                                                           \n";
}

if(Model=="pseudo_nonlinear")
 writeIt
 "                                                                                                \n"
 "    - intN(Th,qforder=3)                                                                        \n"
 "  (                                                                                             \n"
 "      (def(uNL)'*def(v))*c[0]                                                                   \n"
 "    + (divergence(uNL)*divergence(v))*c[1]                                                      \n"
 "    + (epsilon(uNL)'*epsilon(v))*c[2]                                                           \n"
 "  )                                                                                             \n"
 "                                                                                                \n"
 "                                                                                                \n"
 "    - intN1(Th,qforder=3,PAlabels)                                                              \n"
 "  (                                                                                             \n"
 "      c[7]*(  PA0(uNL)'*def(v)  )                                                               \n"
 "  )                                                                                             \n"
 "                                                                                                \n";

if(Model=="Hujeux")
 writeIt
 "                                                                                                \n"
 "    - intN(Th,qforder=3)                                                                        \n"
 "  (                                                                                             \n"
 "      (def(uNL)'*def(v))*c[0]                                                                   \n"
 "      +  defSh(Sig) ' * Epsl(v)                                                                  \n"
 "   /*+ (divergence(uNL)*divergence(v))*c[1]                                                     \n"
 "     + (epsilon(uNL)'*epsilon(v))*c[2] */                                                       \n"
 "  )                                                                                             \n"
 "                                                                                                \n"
 "                                                                                                \n"
 "    - intN1(Th,qforder=3,PAlabels)                                                              \n"
 "  (                                                                                             \n"
 "      c[7]*(  PA0(uNL)'*def(v)  )                                                               \n"
 "  )                                                                                             \n"
 "                                                                                                \n";


 writeIt
 "                                                                                                \n"
 " /*  //---- uncomment if the load is not on paraxial border ----//                              \n"
 "                                                                                                \n"
 "    + intN1(Th,qforder=3,LoadLabels)                                                            \n"
 "  (                                                                                             \n"
 "     load1*v+load2*v1                                                                           \n"
 "  )                                                                                             \n"
 " */                                                                                             \n"
 "                                                                                                \n"
 ";                                                                                               \n"
 "                                                                                                \n";

if(Model=="Hujeux")
 writeIt
 "                                                                                                \n"
 "//==============================================================================                \n"
 "// --Variation formulation soil-dynamics (static solve before dynamics) -------                 \n"
 "//==============================================================================                \n"
 "                                                                                                \n"
 "varf staticElasticity( def(du) , def(v) ) =                                                     \n"
 "                                                                                                \n"
 "    //--------------------------------------------------------------------------                \n"
 "    //  $+int_{\\Omega}(\\lambda:\\nabla(u).\\nabla(v))$                                        \n"
 "    //  $+int_{\\Omega}(2\\mu(\\epsilon(u):\\epsilon(v)))$                                      \n"
 "    //--------------------------------------------------------------------------                \n"
 "    intN(Th,qforder=3)                                                                          \n"
 "  (                                                                                             \n"
 "      (divergence(du)*divergence(v))*lambda                                                     \n"
 "    + (epsilon(du)'*epsilon(v))*2.*mu                                                           \n"
 "  )                                                                                             \n"
 "                                                                                                \n"
 "    //--------------------------------------------------------------------------                \n"
 "    //  $+int_{\\Omega}(\\rho g v1)$                                                            \n"
 "    //--------------------------------------------------------------------------                \n"
 "     + intN(Th,qforder=3)(rho*9.81*v1)                                                          \n"
 "                                                                                                \n"
 ";                                                                                               \n"
 "                                                                                                \n";
