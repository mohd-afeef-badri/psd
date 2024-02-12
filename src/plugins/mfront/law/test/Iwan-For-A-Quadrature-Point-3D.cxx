// Test Iwan : a non-linear soil law	//
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

  ifstream indata;
  indata.open("in.data");

  ofstream outdata;
  outdata.open("out.data");

  int steps = 2001;
  double *SigxyRef = new double[steps];
  double timeT,
  GammaExy,
  dummy;

  double *Stressbackup = new double[6];
  double *Strainbackup = new double[6];
  double *isvbackup = new double[118];

  for (int jj = 0; jj < 6; jj++)
    Stressbackup[jj] = 0.;

  for (int jj = 0; jj < 6; jj++)
    Strainbackup[jj] = 0.;

  for (int jj = 0; jj < 118; jj++)
    isvbackup[jj] = 0.;

  bool updateMFRONT = false;
  bool updatePSD = true;
  bool verbos = false;

  printLine("=");
  std::cout << "   tesing IWAN law MFront-MGIS              " << std::endl;
  printLine("=");

  for (int tt = 0; tt < steps; tt++)
  {
   	//------------------------------------------------------------
   	// Loading mfront created shared library
   	//------------------------------------------------------------
    if (!tt) printLine("-");
    if (!tt) std::cout << "   ->  Loading Behaviour   " << std::endl;
    constexpr
    const auto h = Hypothesis::TRIDIMENSIONAL;
#ifdef __APPLE__
    const auto b = load("./../src/libBehaviour.dylib", "Iwan", h);
#endif

#ifdef WIN32
    const auto b = load("./../src/libBehaviour.dll", "Iwan", h);
#endif

#ifdef __linux__
    const auto b = load("./../src/libBehaviour.so", "Iwan", h);
#endif
    if (!tt) std::cout << "       Done   " << std::endl;
    if (!tt) printLine("-");

   	//------------------------------------------------------------
   	// Behaviour objects printing
   	//------------------------------------------------------------
    if (verbos)
    {
      std::cout << "   ->  Behaviour objects   " << std::endl;

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
    if (!tt) printLine("-");
    if (!tt) std::cout << "   ->  Initilizing Strain vector   " << std::endl;

    indata >> timeT >> dummy >> GammaExy >> SigxyRef[tt];

    d.s1.gradients[0] = 0;	//E11
    d.s1.gradients[1] = 0;	//E22
    d.s1.gradients[2] = 0;	//E33
    d.s1.gradients[3] = 1. / sqrt(2.) *GammaExy;	//E12
    d.s1.gradients[4] = 0;	//E13
    d.s1.gradients[5] = 0;	//E23

    if (!tt) std::cout << "       Done   " << std::endl;
    if (!tt) printLine("-");

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
   	// PSD update
   	//-----------------------------------------------------------
    if (tt > 0)
      if (updatePSD)
      {
        for (int jj = 0; jj < 118; jj++)
          d.s0.internal_state_variables[jj] = isvbackup[jj];

        for (int jj = 0; jj < 6; jj++)
          d.s0.thermodynamic_forces[jj] = Stressbackup[jj];

        for (int jj = 0; jj < 6; jj++)
          d.s0.gradients[jj] = Strainbackup[jj];
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

    if (verbos)
      for (int jj = 0; jj < 118; jj++)
        std::cout << "BEFOR UPDATAE d.s0.internal_state_variables[" << jj << "]  " << d.s0.internal_state_variables[jj] << "  d.s1.internal_state_variables[" << jj << "]  " << d.s1.internal_state_variables[jj] << std::endl;

   	//------------------------------------------------------------
   	// Inntegrating the law
   	//------------------------------------------------------------
    if (!tt) printLine("-");
    if (!tt) std::cout << "   ->  Inntegrating the law   " << std::endl;
       	
    integrate(v, b);

    if (!tt) std::cout << "       Done   " << std::endl;
    if (!tt) printLine("-");
   	//------------------------------------------------------------
   	// MFRONT update
   	//-----------------------------------------------------------
    if (updateMFRONT)
      update(d);

   	//------------------------------------------------------------
   	// PSD update
   	//-----------------------------------------------------------

    if (updatePSD)
    {
      for (int jj = 0; jj < 6; jj++)
        Stressbackup[jj] = d.s1.thermodynamic_forces[jj];

      for (int jj = 0; jj < 6; jj++)
        Strainbackup[jj] = d.s1.gradients[jj];

      for (int jj = 0; jj < b.isvs.size(); jj++)
        isvbackup[jj] = d.s1.internal_state_variables[jj];
    }

    if (verbos)
      for (int jj = 0; jj < 118; jj++)
        std::cout << "AFTER UPDATAE d.s0.internal_state_variables[" << jj << "]  " << d.s0.internal_state_variables[jj] << "  d.s1.internal_state_variables[" << jj << "]  " << d.s1.internal_state_variables[jj] << std::endl;

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

   	//------------------------------------------------------------
   	// output file
   	//------------------------------------------------------------
    outdata << std::fixed << std::setprecision(16) << timeT << "  " << GammaExy << "  " << d.s1.thermodynamic_forces[3] / sqrt(2.) << "  " << SigxyRef[tt] << std::endl;
  }

  printLine("=");
  std::cout << "              END OF PROGRAM                " << std::endl;
  printLine("=");

  return 0;
}
