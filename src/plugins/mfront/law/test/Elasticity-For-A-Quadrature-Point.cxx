// Test Elasticity //

#include <cmath>
#include <cstdlib>
#include <iostream>
#include "MGIS/Behaviour/State.hxx"
#include "MGIS/Behaviour/Behaviour.hxx"
#include "MGIS/Behaviour/BehaviourData.hxx"
#include "MGIS/Behaviour/Integrate.hxx"
  
int main(const int argc, const char* const* argv) {

  using namespace mgis;
  using namespace mgis::behaviour;
  
  std::cout << " ========================================== "<< std::endl;
  std::cout << "   TESTING LINEAR ELASTICITY MFront-MGIS    "<< std::endl;  
  std::cout << " ========================================== "<< std::endl;  
  std::cout << "   ----------------------- "<< std::endl;
  std::cout << std::endl;  
  
  

//------------------------------------------------------------
// Loading mfront created shared library
//------------------------------------------------------------  
  std::cout << "   ->  Loading Behaviour   "<< std::endl;
  std::cout << "       ....                "<< std::endl;          

  constexpr const auto h = Hypothesis::GENERALISEDPLANESTRAIN;
#ifdef __APPLE__
  const auto b = load("./../src/libBehaviour.dylib", "Elasticity", h);
#endif

#ifdef WIN32
  const auto b = load("./../src/libBehaviour.dll", "Elasticity", h);
#endif

#ifdef __linux__
  const auto b = load("./../src/libBehaviour.so", "Elasticity", h);
#endif  
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

  auto d = BehaviourData{b};
  auto v = make_view(d);
        
  std::cout << "       Done   "<< std::endl;
  std::cout << "   ----------------------- "<< std::endl;  
  std::cout << std::endl;    
//------------------------------------------------------------        



//------------------------------------------------------------
// setMaterialProperty 
//------------------------------------------------------------

  std::cout << "   ->  setMaterialProperty   "<< std::endl;
  std::cout << "       ....                      "<< std::endl;          

  setMaterialProperty(d.s1,"YoungModulus",150.0);
  setMaterialProperty(d.s1,"PoissonRatio",0.3);

  for (int i=0; i<b.mps.size(); i++)            
  std::cout << "         b.mps["<<i<<"].type =  "
            <<           getMaterialProperty(d.s1,"YoungModulus") << std::endl;
  double* ygs = getMaterialProperty(d.s1,"YoungModulus");

  std::cout << "         YoungModulus =  "
            <<           *ygs << std::endl;  
                    
  std::cout << "       Done   "<< std::endl;
  std::cout << "   ----------------------- "<< std::endl;  
  std::cout << std::endl;    
//------------------------------------------------------------ 

  
            
//------------------------------------------------------------
// Test behaviour data from Elasticity.mfront file
//------------------------------------------------------------
  std::cout << "   ->  Print behaviour data  "<< std::endl;

  std::cout << "         Time increment dt =  "
            <<           d.dt << std::endl;
  
  std::cout << "         Behaviour::nopts+1  "
            <<           Behaviour::nopts+1 << std::endl;

  std::cout << "         d.K[0] (Type of Stiffness matrix) "
            <<           d.K[0] << std::endl;

  std::cout << "       ....                      "<< std::endl;                                      
  std::cout << "       Done   "<< std::endl;
  std::cout << "   ----------------------- "<< std::endl;            
  std::cout << std::endl;    
//------------------------------------------------------------


//------------------------------------------------------------
// arbitary strain vector
//------------------------------------------------------------  
  std::cout << "   ->  Initilizing Strain vector   "<< std::endl;


  d.s1.gradients[0] = 1.;  //E11
  d.s1.gradients[1] = 1.;  //E22
  d.s1.gradients[2] = 0.;  //E33      
  d.s1.gradients[3] = 1.;  //E12

//  update(d);
  
  std::cout << "       ....                        "<< std::endl;                  
  std::cout << "       Done   "<< std::endl;
  std::cout << "   ----------------------- "<< std::endl;  
  std::cout << std::endl;    
//------------------------------------------------------------


//------------------------------------------------------------
// print stress vector
//------------------------------------------------------------  
  std::cout << "   ->  Print stress vector   "<< std::endl;

  std::cout << "         Sxx =  "
            <<           d.s1.thermodynamic_forces[0] << std::endl;
  std::cout << "         Syy =  "
            <<           d.s1.thermodynamic_forces[1] << std::endl;
  std::cout << "         Szz =  "
            <<           d.s1.thermodynamic_forces[2] << std::endl;
  std::cout << "         Sxy =  "
            <<           d.s1.thermodynamic_forces[3] << std::endl;
  
  std::cout << "       ....                        "<< std::endl;                  
  std::cout << "       Done   "<< std::endl;
  std::cout << "   ----------------------- "<< std::endl;  
  std::cout << std::endl;    
//------------------------------------------------------------
                          


//------------------------------------------------------------
// print gauss point stiffness matrix vector
//------------------------------------------------------------
  
  d.K[0] = 1.;  // Indicating that request stiffness matrix 
 
  std::cout << "   ->  Print stiffness matrix as vector "<< std::endl; 
  for (int i=0; i<16; i++)
    std::cout << "         d.K["<<i<<"] = "
              <<           d.K[i] << std::endl;
  
  std::cout << "       ....                        "<< std::endl;                  
  std::cout << "       Done   "<< std::endl;
  std::cout << "   ----------------------- "<< std::endl;  
  std::cout << std::endl;    
//------------------------------------------------------------ 
 
//------------------------------------------------------------
// Inntegrating the law
//------------------------------------------------------------  
  std::cout << "   ->  Inntegrating the law   "<< std::endl;

  integrate(v, b);
    
  std::cout << "       ....                        "<< std::endl;                  
  std::cout << "       Done   "<< std::endl;
  std::cout << "   ----------------------- "<< std::endl;  
  std::cout << std::endl;    
//------------------------------------------------------------
            

//------------------------------------------------------------
// print stress vector
//------------------------------------------------------------  
  std::cout << "   ->  Print stress vector after integration  "<< std::endl;

  std::cout << "         Sxx =  "
            <<           d.s1.thermodynamic_forces[0] << std::endl;
  std::cout << "         Syy =  "
            <<           d.s1.thermodynamic_forces[1] << std::endl;
  std::cout << "         Szz =  "
            <<           d.s1.thermodynamic_forces[2] << std::endl;
  std::cout << "         Sxy =  "
            <<           d.s1.thermodynamic_forces[3] << std::endl;
  
  std::cout << "       ....                        "<< std::endl;                  
  std::cout << "       Done   "<< std::endl;
  std::cout << "   ----------------------- "<< std::endl;  
  std::cout << std::endl;    
//------------------------------------------------------------            
 
//------------------------------------------------------------
// print gauss point stiffness matrix vector
//------------------------------------------------------------

  std::cout << "   ->  Print stiffness matrix as vector "<< std::endl; 
  for (int i=0; i<16; i++)
    std::cout << "         d.K["<<i<<"] = "
              <<           d.K[i] << std::endl;
  
  std::cout << "       ....                        "<< std::endl;                  
  std::cout << "       Done   "<< std::endl;
  std::cout << "   ----------------------- "<< std::endl;  
  std::cout << std::endl;    
//------------------------------------------------------------                          
                                 
  std::cout << " ========================================== "<< std::endl;
  std::cout << "              END OF PROGRAM                "<< std::endl;  
  std::cout << " ========================================== "<< std::endl;
  return 0; 
}
