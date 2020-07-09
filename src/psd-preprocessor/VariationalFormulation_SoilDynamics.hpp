//=================================================================================================
// ------ Building the VariationalFormulations.edp file ------ 
//=================================================================================================

write
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

if(spc==2)write
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

if(spc==3)write
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
                
write
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
