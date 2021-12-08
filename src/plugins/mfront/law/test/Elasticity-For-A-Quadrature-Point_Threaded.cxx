// Test Elasticity //

#include <cmath>
#include <cstdlib>
#include <iostream>
#include "MGIS/Behaviour/State.hxx"
#include "MGIS/Behaviour/Behaviour.hxx"
#include "MGIS/Behaviour/MaterialDataManager.hxx"
#include "MGIS/Behaviour/BehaviourData.hxx"                         ///////////////// SEEEEEEEEEEEEEEEEE
#include "MGIS/Behaviour/Integrate.hxx"

int main(const int argc, const char* const* argv) {

  using namespace mgis;
  using namespace mgis::behaviour;

  std::cout << " ========================================== "<< std::endl;
  std::cout << "   TESTING LINEAR ELASTICITY MFront-MGIS    "<< std::endl;
  std::cout << "       WITH OpenMP based parallelism        "<< std::endl;
  std::cout << " ========================================== "<< std::endl;
  std::cout << "   ----------------------- "<< std::endl;
  std::cout << std::endl;



//------------------------------------------------------------
// Loading mfront created shared library
//------------------------------------------------------------
  std::cout << "   ->  Loading Behaviour   "<< std::endl;
  std::cout << "       ....                "<< std::endl;

  constexpr const auto h = Hypothesis::GENERALISEDPLANESTRAIN;
  const auto b = load("./../src/libBehaviour.so", "Elasticity", h);

  std::cout << "       Done   "<< std::endl;
  std::cout << "   ----------------------- "<< std::endl;
  std::cout << std::endl;
//------------------------------------------------------------


//------------------------------------------------------------
// Behaviour objects printing
//------------------------------------------------------------

  std::cout << "   ->  Behaviour objects   "<< std::endl;

  const auto n = getArraySize(b.isvs,b.hypothesis);

  std::cout << "         b.isvs size =  "
            <<           n << std::endl;
  std::cout << "         b.mps.size() =  "
            <<           b.mps.size() << std::endl;
  for (int i=0; i<b.mps.size(); i++)
  std::cout << "         b.mps["<<i<<"].name =  "
            <<           b.mps[i].name << std::endl;

  for (int i=0; i<b.mps.size(); i++)
  std::cout << "         b.mps["<<i<<"].type =  "
            <<           b.mps[i].type << std::endl;

  std::cout << "         b.gradients[0].name =  "
            <<           b.gradients[0].name << std::endl;
  std::cout << "         b.gradients[0].type =  "
            <<           b.gradients[0].type << std::endl;
  std::cout << "         b.thermodynamic_forces.size() =  "
            <<           b.thermodynamic_forces.size() << std::endl;
  std::cout << "         b.thermodynamic_forces[0].name =  "
            <<           b.thermodynamic_forces[0].name << std::endl;

  std::cout << "       ....                "<< std::endl;
  std::cout << "       Done   "<< std::endl;
  std::cout << "   ----------------------- "<< std::endl;
  std::cout << std::endl;
//------------------------------------------------------------



//------------------------------------------------------------
// Test Material properties from Elasticity.mfront file
//------------------------------------------------------------
  std::cout << "   ->  Print Behaviour parameters  "<< std::endl;

  const auto Total_parameters = b.params.size();

  std::cout << "         Total Behaviour parameters "
            <<           Total_parameters << std::endl;

  for (int i=0; i<Total_parameters; i++)
    std::cout << "         Parameter " <<   i   << " is "
              <<           b.params[i] << " = "
              <<           getParameterDefaultValue<double>(b, b.params[i])
              << std::endl;


  std::cout << "       ....                "<< std::endl;
  std::cout << "       Done   "<< std::endl;
  std::cout << "   ----------------------- "<< std::endl;
  std::cout << std::endl;
//------------------------------------------------------------



//------------------------------------------------------------
// Creating a single point (integration point) behaviour data
//------------------------------------------------------------
  std::cout << "   ->  Creating behaviour data and view   "<< std::endl;
  std::cout << "       ....                      "<< std::endl;

  MaterialDataManager m{b, 3}; //auto d = BehaviourData{b};
  //auto v = make_view(d);

  std::cout << "       Done   "<< std::endl;
  std::cout << "   ----------------------- "<< std::endl;
  std::cout << std::endl;
//------------------------------------------------------------



//------------------------------------------------------------
// setMaterialProperty
//------------------------------------------------------------

  std::cout << "   ->  setMaterialProperty   "<< std::endl;
  std::cout << "       ....                      "<< std::endl;

  setMaterialProperty(m.s1,"YoungModulus",150.0);
  setMaterialProperty(m.s1,"PoissonRatio",0.3);
  m.s1.external_state_variables["Temperature"] = 293.15;
  update(m);

/*
  for (int i=0; i<b.mps.size(); i++)
  std::cout << "         b.mps["<<i<<"].type =  "
            <<           getMaterialProperty(m.s1,"YoungModulus") << std::endl;

  double* ygs = getMaterialProperty(m.s1,"YoungModulus");

  std::cout << "         YoungModulus =  "
            <<           *ygs << std::endl;
*/
  std::cout << "       Done   "<< std::endl;
  std::cout << "   ----------------------- "<< std::endl;
  std::cout << std::endl;

//------------------------------------------------------------



//------------------------------------------------------------
// Test behaviour data from Elasticity.mfront file
//------------------------------------------------------------
  std::cout << "   ->  Print behaviour data  "<< std::endl;

/*
  std::cout << "         Time increment dt =  "
            <<           m.dt << std::endl;
*/

  std::cout << "         Behaviour::nopts+1  "
            <<           Behaviour::nopts+1 << std::endl;

  std::cout << "         d.K[0] (Type of Stiffness matrix) "
            <<           m.K[0] << std::endl;

  std::cout << "       ....                      "<< std::endl;
  std::cout << "       Done   "<< std::endl;
  std::cout << "   ----------------------- "<< std::endl;
  std::cout << std::endl;
//------------------------------------------------------------


//------------------------------------------------------------
// arbitary strain vector
//------------------------------------------------------------
  std::cout << "   ->  Initilizing Strain vector   "<< std::endl;


/*
  m.s1.gradients[0] = 1.;  //E11
  m.s1.gradients[1] = 1.;  //E22
  m.s1.gradients[2] = 0.;  //E33
  m.s1.gradients[3] = 1.;  //E12
*/  
  
   for (size_type idx = 0 , index; idx != m.n; ++idx) 
   {
      index = idx * m.s1.gradients_stride;
      m.s1.gradients[ index ]      = 1.;
      m.s1.gradients[ index + 1]   = 1.;
      m.s1.gradients[ index + 2]   = 0.;
      m.s1.gradients[ index + 3]   = 1.;                
   }

  std::cout << "       ....                        "<< std::endl;
  std::cout << "       Done   "<< std::endl;
  std::cout << "   ----------------------- "<< std::endl;
  std::cout << std::endl;
//------------------------------------------------------------


//------------------------------------------------------------
// print stress vector
//------------------------------------------------------------
  std::cout << "   ->  Print stress vector   "<< std::endl;

// Method 1 //
  for (size_type idx = 0 , index; idx != m.n; ++idx  ) {
      index = idx * m.s1.thermodynamic_forces_stride;
      std::cout << "         Sigma_"<< index + 0 << " = " 
            <<           m.s1.thermodynamic_forces[ index + 0 ] << std::endl;
      std::cout << "         Sigma_"<< index + 1 << " = " 
            <<           m.s1.thermodynamic_forces[ index + 1 ] << std::endl;  
      std::cout << "         Sigma_"<< index + 2 << " = " 
            <<           m.s1.thermodynamic_forces[ index + 2 ] << std::endl;  
      std::cout << "         Sigma_"<< index + 3 << " = " 
            <<           m.s1.thermodynamic_forces[ index + 3 ] << std::endl;                                                  
  }

  for (size_type idx = 0 , index; idx != m.n; ++idx  ) {
      index = idx * m.s1.thermodynamic_forces_stride;
      for (index; index < (idx+1)*m.s1.thermodynamic_forces_stride; index++)
         std::cout << "         Sigma_"<< index  << " = " 
            <<           m.s1.thermodynamic_forces[ index ] << std::endl;                                                 
  }


/*
  std::cout << "         Sxx =  "
            <<           m.s1.thermodynamic_forces[0] << std::endl;
  std::cout << "         Syy =  "
            <<           m.s1.thermodynamic_forces[1] << std::endl;
  std::cout << "         Szz =  "
            <<           m.s1.thermodynamic_forces[2] << std::endl;
  std::cout << "         Sxy =  "
            <<           m.s1.thermodynamic_forces[3] << std::endl;
*/
  std::cout << "       ....                        "<< std::endl;
  std::cout << "       Done   "<< std::endl;
  std::cout << "   ----------------------- "<< std::endl;
  std::cout << std::endl;
//------------------------------------------------------------



//------------------------------------------------------------
// print gauss point stiffness matrix vector
//------------------------------------------------------------

  m.K[0] = 1.;  // Indicating that request stiffness matrix

  std::cout << "   ->  Print stiffness matrix as vector "<< std::endl;
  for (int i=0; i<16; i++)
    std::cout << "         d.K["<<i<<"] = "
              <<           m.K[i] << std::endl;

  std::cout << "       ....                        "<< std::endl;
  std::cout << "       Done   "<< std::endl;
  std::cout << "   ----------------------- "<< std::endl;
  std::cout << std::endl;
//------------------------------------------------------------

//------------------------------------------------------------
// Inntegrating the law
//------------------------------------------------------------
  std::cout << "   ->  Inntegrating the law   "<< std::endl;

/*
             mgis::behaviour::IntegrationType::PREDICTION_TANGENT_OPERATOR;
             mgis::behaviour::IntegrationType::PREDICTION_SECANT_OPERATOR;
             mgis::behaviour::IntegrationType::PREDICTION_ELASTIC_OPERATOR;
             mgis::behaviour::IntegrationType::INTEGRATION_NO_TANGENT_OPERATOR;
             mgis::behaviour::IntegrationType::INTEGRATION_ELASTIC_OPERATOR;
             mgis::behaviour::IntegrationType::INTEGRATION_SECANT_OPERATOR;
             mgis::behaviour::IntegrationType::INTEGRATION_TANGENT_OPERATOR;
             mgis::behaviour::IntegrationType::INTEGRATION_CONSITENT_TANGENT_OPERATOR;
             mgis::behaviour::IntegrationType::INTEGRATION_NO_TANGENT_OPERATOR;
*/  
  integrate(m, IntegrationType::INTEGRATION_TANGENT_OPERATOR,  .01, 0, m.n);

  std::cout << "       ....                        "<< std::endl;
  std::cout << "       Done   "<< std::endl;
  std::cout << "   ----------------------- "<< std::endl;
  std::cout << std::endl;
//------------------------------------------------------------


//------------------------------------------------------------
// print stress vector
//------------------------------------------------------------
  std::cout << "   ->  Print stress vector after integration  "<< std::endl;

/*

  std::cout << "       Gauss Point 1       " << std::endl;  
  std::cout << "         Sxx =  "
            <<           m.s1.thermodynamic_forces[0] << std::endl;
  std::cout << "         Syy =  "
            <<           m.s1.thermodynamic_forces[1] << std::endl;
  std::cout << "         Szz =  "
            <<           m.s1.thermodynamic_forces[2] << std::endl;
  std::cout << "         Sxy =  "
            <<           m.s1.thermodynamic_forces[3] << std::endl;
  std::cout << "       Gauss Point 2       " << std::endl;  
  std::cout << "         Sxx =  "
            <<           m.s1.thermodynamic_forces[4] << std::endl;
  std::cout << "         Syy =  "
            <<           m.s1.thermodynamic_forces[5] << std::endl;
  std::cout << "         Szz =  "
            <<           m.s1.thermodynamic_forces[6] << std::endl;
  std::cout << "         Sxy =  "
            <<           m.s1.thermodynamic_forces[7] << std::endl;
  std::cout << "       Gauss Point 3       " << std::endl;  
  std::cout << "         Sxx =  "
            <<           m.s1.thermodynamic_forces[8] << std::endl;
  std::cout << "         Syy =  "
            <<           m.s1.thermodynamic_forces[9] << std::endl;
  std::cout << "         Szz =  "
            <<           m.s1.thermodynamic_forces[10] << std::endl;
  std::cout << "         Sxy =  "
            <<           m.s1.thermodynamic_forces[11] << std::endl;
*/

  for( size_type idx = 0 , index; idx != m.n; ++idx ) 
  {
      std::cout << "        " << std::endl;   
      index = idx * m.s1.thermodynamic_forces_stride;
      for (index; index < (idx+1)*m.s1.thermodynamic_forces_stride; index++)
         std::cout << "       Sigma_"<< index  << " = " 
            <<           m.s1.thermodynamic_forces[ index ] << std::endl; 
  }
                                    
  std::cout << "       ....                        "<< std::endl;
  std::cout << "       Done   "<< std::endl;
  std::cout << "   ----------------------- "<< std::endl;
  std::cout << std::endl;
//------------------------------------------------------------

//------------------------------------------------------------
// print gauss point stiffness matrix vector
//------------------------------------------------------------
  
  std::cout << "   ->  Print stiffness matrix as vector "<< std::endl;
/*
  for (int i=0; i<16; i++)
    std::cout << "         m.K["<<i<<"] = "
              <<           m.K[i] << std::endl;
*/


  for( size_type idx = 0 , index; idx != m.n; ++idx ) {
      std::cout << "        " << std::endl; 
      index = idx * m.K_stride;
      for (index; index < (idx+1)*m.K_stride; index++)
         std::cout << "       K_"<< index  << " = " 
            <<           m.K[ index ] << std::endl;                                                 
  
  }
              
  std::cout << "       ....                        "<< std::endl;
  std::cout << "       Done   "<< std::endl;
  std::cout << "   ----------------------- "<< std::endl;
  std::cout << std::endl;
//------------------------------------------------------------

  std::cout << " ========================================== "<< std::endl;
  std::cout << "              END OF PROGRAM                "<< std::endl;
  std::cout << " ========================================== "<< std::endl;
  
 /**/
  return 0;
}
