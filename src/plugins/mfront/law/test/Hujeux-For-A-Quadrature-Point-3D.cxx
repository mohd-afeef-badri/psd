// Test Hujeux.mfront : a non-linear soil law	//
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "MGIS/Behaviour/State.hxx"
#include "MGIS/Behaviour/Behaviour.hxx"
#include "MGIS/Behaviour/BehaviourData.hxx"
#include "MGIS/Behaviour/Integrate.hxx"

void printLine(std::string s)
{
  std::cout << "  ";
  for (int i = 0; i < 45; i++)
    std::cout << s;
  std::cout << std::endl;
}


int main(const int argc, const char *const *argv)
{

  using namespace mgis;
  using namespace mgis::behaviour;

  using std::ifstream;
  using std::ofstream;
  
  bool verbos = true;

  printLine("=");
  std::cout << "   tesing Hujeux law MFront-MGIS              " << std::endl;
  printLine("=");

   	//------------------------------------------------------------
   	// Loading mfront created shared library
   	//------------------------------------------------------------
    printLine("-");
    std::cout << "   ->  Loading Behaviour   " << std::endl;
    constexpr
    const auto h = Hypothesis::TRIDIMENSIONAL;

#ifdef __APPLE__
    const auto b = load("./../../law/src/libBehaviour.dylib", "Hujeux", h); 
#endif

#ifdef WIN32
    const auto b = load("./../../law/src/libBehaviour.dll", "Hujeux", h);
#endif

#ifdef __linux__
    const auto b = load("./../../law/src/libBehaviour.so", "Hujeux", h);
#endif

    std::cout << "       Done   " << std::endl;
    printLine("-");

   	//------------------------------------------------------------
   	// Behaviour objects printing
   	//------------------------------------------------------------
    if (verbos)
    {

      std::cout << "         Parameters (params)  "<< std::endl;
      std::cout << "           b.params.size() =  " <<
        b.mps.size() << std::endl;
      for (int i = 0; i < b.params.size(); i++)
        std::cout << "             - params "<< i << " name :   \033[1;36m" << b.params[i] << "\033[0m" <<
        std::endl;

              std::cout << "   ->  Behaviour objects   " << std::endl;


      std::cout << "         Material Parameters (mps)  "<< std::endl;
      std::cout << "           b.mps.size() =  " <<
        b.mps.size() << std::endl;
      for (int i = 0; i < b.mps.size(); i++)
        std::cout << "             - mps "<< i << " name :   \033[1;36m" << b.mps[i].name << "\033[0m" <<
        std::endl;

      const auto n = getArraySize(b.isvs, b.hypothesis);

      std::cout << "         b.isvs size =  " <<
        n << std::endl;
      for (int i = 0; i < b.isvs.size(); i++)
        std::cout << "    internal state variables name :   \033[1;36m" << b.isvs[i].name << "\033[0m" <<
        "\t\tof type \033[1;36m" << "\033[0m" <<
        std::endl;

      for (int i = 0; i < b.esvs.size(); i++)
        std::cout << "    external state variables name :   \033[1;36m" << b.esvs[i].name << "\033[0m" <<
        "\t\tof type \033[1;36m" << "\033[0m" <<
        std::endl;

      std::cout << "         b.mps.size() =  " <<
        b.mps.size() << std::endl;
      for (int i = 0; i < b.mps.size(); i++)
        std::cout << "         b.mps[" << i << "].name =  " <<
        b.mps[i].name << std::endl;

      for (int i = 0; i < b.mps.size(); i++)
        std::cout << "         b.mps[" << i << "].type =  " <<
        b.mps[i].type << std::endl;

      std::cout << "         b.gradients[0].name =  " <<
        b.gradients[0].name << std::endl;
      std::cout << "         b.gradients[0].type =  " <<
        b.gradients[0].type << std::endl;
      std::cout << "         b.thermodynamic_forces.size() =  " <<
        b.thermodynamic_forces.size() << std::endl;
      std::cout << "         b.thermodynamic_forces[0].name =  " <<
        b.thermodynamic_forces[0].name << std::endl;

      std::cout << "       ....                " << std::endl;
      std::cout << "       Done   " << std::endl;
      std::cout << "   ----------------------- " << std::endl;
      std::cout << std::endl;
    }

   	//------------------------------------------------------------
   	// Creating a single point (integration point) behaviour data
   	//------------------------------------------------------------
    if (verbos)
    {
      std::cout << "   ->  Creating behaviour data and view   " << std::endl;
      std::cout << "       ....                      " << std::endl;
    }

    auto d = BehaviourData
    {
      b
    };
    auto v = make_view(d);

    if (verbos)
    {
      std::cout << "       Done   " << std::endl;
      std::cout << "   ----------------------- " << std::endl;
      std::cout << std::endl;
    }

   	//------------------------------------------------------------
   	//  strain vector loading
   	//------------------------------------------------------------
    printLine("-");
    std::cout << "   ->  Initilizing Strain vector   " << std::endl;


    d.s1.gradients[0] = 0;	//E11
    d.s1.gradients[1] = 0;	//E22
    d.s1.gradients[2] = 0;	//E33
    d.s1.gradients[3] = 1. / sqrt(2.) *4;	//E12
    d.s1.gradients[4] = 0;	//E13
    d.s1.gradients[5] = 0;	//E23

    std::cout << "       Done   " << std::endl;
    printLine("-");

   	//------------------------------------------------------------
   	// print stress vector
   	//------------------------------------------------------------
    if (verbos)
    {
      std::cout << "   ->  Print STRAIN vector   " << std::endl;

      std::cout << "         Exx =  " <<
        d.s1.gradients[0] << std::endl;
      std::cout << "         Eyy =  " <<
        d.s1.gradients[1] << std::endl;
      std::cout << "         Ezz =  " <<
        d.s1.gradients[2] << std::endl;
      std::cout << "         Exy =  " <<
        d.s1.gradients[3] << std::endl;
      std::cout << "         Exz =  " <<
        d.s1.gradients[4] << std::endl;
      std::cout << "         Eyz =  " <<
        d.s1.gradients[5] << std::endl;

      std::cout << "       ....                        " << std::endl;
      std::cout << "       Done   " << std::endl;
      std::cout << "   ----------------------- " << std::endl;
      std::cout << std::endl;
    }


   	//------------------------------------------------------------
   	// print stress vector
   	//------------------------------------------------------------
    if (verbos)
    {
      std::cout << "   ->  Print stress vector 0   " << std::endl;

      std::cout << "         Sxx =  " <<
        d.s0.thermodynamic_forces[0] << std::endl;
      std::cout << "         Syy =  " <<
        d.s0.thermodynamic_forces[1] << std::endl;
      std::cout << "         Szz =  " <<
        d.s0.thermodynamic_forces[2] << std::endl;
      std::cout << "         Sxy =  " <<
        d.s0.thermodynamic_forces[3] << std::endl;
      std::cout << "         Sxz =  " <<
        d.s0.thermodynamic_forces[4] << std::endl;
      std::cout << "         Syz =  " <<
        d.s0.thermodynamic_forces[5] << std::endl;

      std::cout << "       ....                        " << std::endl;
      std::cout << "       Done   " << std::endl;
      std::cout << "   ----------------------- " << std::endl;
      std::cout << std::endl;
    }

   	//------------------------------------------------------------
   	// print stress vector
   	//------------------------------------------------------------

    if (verbos)
    {
      std::cout << "   ->  Print STRAIN 0 vector   " << std::endl;

      std::cout << "         Exx =  " <<
        d.s0.gradients[0] << std::endl;
      std::cout << "         Eyy =  " <<
        d.s0.gradients[1] << std::endl;
      std::cout << "         Ezz =  " <<
        d.s0.gradients[2] << std::endl;
      std::cout << "         Exy =  " <<
        d.s0.gradients[3] << std::endl;
      std::cout << "         Exz =  " <<
        d.s0.gradients[4] << std::endl;
      std::cout << "         Eyz =  " <<
        d.s0.gradients[5] << std::endl;

      std::cout << "       ....                        " << std::endl;
      std::cout << "       Done   " << std::endl;
      std::cout << "   ----------------------- " << std::endl;
      std::cout << std::endl;
    }


  //------------------------------------------------------------
  // Inntegrating the law
  //------------------------------------------------------------
  printLine("-");
  std::cout << "   ->  Inntegrating the law   " << std::endl;



  ifstream EPsin;
  EPsin.open("fileEpsIn.data");

  ifstream EPsPSD;
  EPsPSD.open("in.data");

  bool psdTest = false;
  double dummy;

  ofstream SigOut;
  SigOut.open("fileSigOut.data");

  EPsin >> d.s0.gradients[3];
  for(int n=0; n < 201; n++){

    EPsin >> d.s1.gradients[3];
    integrate(v, b);
    update(d);
    SigOut <<  std::setprecision(32) << d.s1.thermodynamic_forces[3] << "\t" <<  d.s0.gradients[3] << std::endl;
  }


/*
    d.s1.gradients[3] = 6.28215e-05;
    integrate(v, b);
    update(d);

*/

    std::cout << "       Done   " << std::endl;
    printLine("-");

   	//------------------------------------------------------------
   	// MFRONT update
   	//-----------------------------------------------------------
      update(d);

   	//------------------------------------------------------------
   	// print stress vector
   	//------------------------------------------------------------
    if (verbos)
    {
      std::cout << "   ->  Print stress vector after integration  " << std::endl;

      std::cout << "         Sxx =  " <<
        d.s1.thermodynamic_forces[0] << std::endl;
      std::cout << "         Syy =  " <<
        d.s1.thermodynamic_forces[1] << std::endl;
      std::cout << "         Szz =  " <<
        d.s1.thermodynamic_forces[2] << std::endl;
      std::cout << "         Sxy =  " <<
        d.s1.thermodynamic_forces[3] << std::endl;
      std::cout << "         Sxz =  " <<
        d.s1.thermodynamic_forces[4] << std::endl;
      std::cout << "         Syz =  " <<
        d.s1.thermodynamic_forces[5] << std::endl;

      std::cout << "       ....                        " << std::endl;
      std::cout << "       Done   " << std::endl;
      std::cout << "   ----------------------- " << std::endl;
      std::cout << std::endl;
    }

  printLine("=");
  std::cout << "              END OF PROGRAM                " << std::endl;
  printLine("=");

  return 0;
}
