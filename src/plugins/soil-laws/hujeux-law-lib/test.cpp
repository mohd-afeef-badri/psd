/**************************************************************************************
*                                                                                     *
*           This file is a part of PSD project                                        *
*                                                                                     *
*       -------------------------------------------------------------------           *
*                                                                                     *
*       Copyright 2019-2025 CEA/DES                                                   *
*                                                                                     *
*       Licensed under the Apache License, Version 2.0  (the "License");              *
*       you may not use this file except in compliance with the License.              *
*       You may obtain a copy of the License at                                       *
*                                                                                     *
*           http://www.apache.org/licenses/LICENSE-2.0                                *
*                                                                                     *
*       Unless required by applicable law or agreed to in writing, software           *
*       distributed under the License is distributed on an  "AS IS"  BASIS,           *
*       WITHOUT  WARRANTIES  OR  CONDITIONS  OF  ANY  KIND,  either express           *
*       or implied. See  the License  for  the  specific language governing           *
*       permissions and limitations under the License.                                *
*                                                                                     *
*       -------------------------------------------------------------------           *
*                                                                                     *

     This file allows testing hejeux and utils libraries, any  function
     defined in  hejeux.cpp or utils.cpp can be tested here. To compile
     1. with intel complier

       icpc -c utils.cpp  -O3 -finline-functions -std=c++11 -fpic
       icpc -c hujeux.cpp  -O3 -finline-functions -DDEBUG -std=c++11 -fpic
       icpc -c test.cpp  -O2 -finline-functions -std=c++11
       icpc -O2 -o hujeux-utils-tester utils.o hujeux.o test.o  -std=c++11

     2. with GNU compiler

       g++ -c utils.cpp  -O3 -finline-functions -std=c++11 -fpic
       g++ -c hujeux.cpp  -O3 -finline-functions -DDEBUG -std=c++11 -fpic
       g++ -c test.cpp  -O2 -finline-functions -std=c++11
       g++ -O2 -o hujeux-utils-tester utils.o hujeux.o test.o  -std=c++11

*******************************************************************************/

#include "stdafx.h"

using namespace std;

int main()
 {

   cout <<
   "//----------------------------------------------------------\n"
   "// Tensor2 class test check create Objects called N1, N2 \n"
   "//----------------------------------------------------------\n";

      Tensor2 N1, N2(Real3(1,1,1),Real3(1,1,1));

    cout << "\nsuccess !!!!\n\n";

   cout <<
   "//----------------------------------------------------------\n"
   "// Tensor2 class test check cout 0th element of N1, N2 \n"
   "//----------------------------------------------------------\n";

      cout << "  N2.m_vec[0] = " << N2.m_vec[0] << endl;
      cout << "  N1.m_vec[0] = " << N1.m_vec[0] << endl;

    cout << "\nsuccess !!!!\n\n";

    cout <<
   "//----------------------------------------------------------\n"
   "// Tensor2 class test check operator '=' with N1 = N2 \n"
   "//----------------------------------------------------------\n";

      N1 = N2;

   cout << "\nsuccess !!!!\n\n";

   cout <<
   "//----------------------------------------------------------\n"
   "// Tensor2 class test check cout 0th element of N1, N2 \n"
   "//----------------------------------------------------------\n";

      cout << "  N2.m_vec[0] = " << N2.m_vec[0] << endl;
      cout << "  N1.m_vec[0] = " << N1.m_vec[0] << endl;

    cout << "\nsuccess !!!!\n\n";

   cout <<
   "//----------------------------------------------------------\n"
   "// Tensor2 class test check cout trace of N3                \n"
   "//----------------------------------------------------------\n";

      Tensor2 N3(Real3(1,2,3),Real3(4,5,6));

      double ExactTrace = N3.m_vec[0] + N3.m_vec[1] + N3.m_vec[2];
      double CalcuTrace = N3.m_vec[0] + N3.m_vec[1] + N3.m_vec[2];

      cout << "\n  Trace exact is "     <<  ExactTrace
           << "  function for trace " <<  trace(N3)
           << endl;

    cout << "\nsuccess !!!!\n\n";

   cout <<
   "//----------------------------------------------------------\n"
   "// Tensor2 class test check Tensor2::zero()                 \n"
   "//----------------------------------------------------------\n";

      Tensor2 N4;
      N4 = Tensor2::zero();

      cout << "  N4.m_vec[0] = " << N4.m_vec[0] << endl;
      cout << "  N4.m_vec[0] = " << N4.m_vec[0] << endl;

    cout << "\nsuccess !!!!\n\n";


   cout <<
   "//----------------------------------------------------------\n"
   "// Tensor2 class test bool operator ==                      \n"
   "//----------------------------------------------------------\n";

      Tensor2 N5;
      N5 = Tensor2::zero();

      Tensor2 N6;
      N6 = Tensor2::identity();

      if(N5==N4)
        cout << "Bool operator == for Tensor2 works as N5==N4 \n";
      if(N5==N6)
         cout << "Bool operator == for Tensor2 as N5!=N6 \n";

      cout << "  N5.m_vec[0] = " << N5.m_vec[0] << endl;
      cout << "  N5.m_vec[0] = " << N5.m_vec[1] << endl;

    cout << "\nsuccess !!!!\n\n";


   cout <<
   "//----------------------------------------------------------\n"
   "// Tensor2 class test bool operator +=                      \n"
   "//----------------------------------------------------------\n";

      Tensor2 N7;
      N7 = Tensor2::identity();

      Tensor2 N8;
      N8 = Tensor2::identity();

      N8 += N7;
      N8 += N7;

      cout << "  N8.m_vec[0] = " << N8.m_vec[0] << endl;
      cout << "  N8.m_vec[0] = " << N8.m_vec[1] << endl;

    cout << "\nsuccess !!!!\n\n";


   cout <<
   "//----------------------------------------------------------\n"
   "// Tensor2 class test check norm(Tensor2.m_vec)             \n"
   "//----------------------------------------------------------\n";

      Tensor2 N9;
      N9 = Tensor2::identity();

      double testNormTensor2 = norm(N9.m_vec);

    cout << "\nsuccess !!!!\n\n";


   cout <<
   "//----------------------------------------------------------\n"
   "// Real3x3 class test check object creation R1						  \n"
   "//----------------------------------------------------------\n";

      Real3x3 R1;

    cout << "\nsuccess !!!!\n\n";

   cout <<
   "//----------------------------------------------------------\n"
   "// Real3x3 class test  creation R2 = Real3x3::identity();		\n"
   "//----------------------------------------------------------\n";

      Real3x3 R2;

      R2 = Real3x3::identity();

      cout << "  R2.x[0] = " << R2.x[0] << endl;
      cout << "  R2.x[1] = " << R2.x[1] << endl;
      cout << "  R2.x[2] = " << R2.x[2] << endl;
      cout << "  R2.y[0] = " << R2.y[0] << endl;
      cout << "  R2.y[1] = " << R2.y[1] << endl;
      cout << "  R2.y[2] = " << R2.y[2] << endl;
      cout << "  R2.z[0] = " << R2.z[0] << endl;
      cout << "  R2.z[1] = " << R2.z[1] << endl;
      cout << "  R2.z[2] = " << R2.z[2] << endl;

    cout << "\nsuccess !!!!\n\n";

   cout <<
   "//----------------------------------------------------------\n"
   "// Real3x3 class test operator '*' creation of R3= 33.*R2;		\n"
   "//----------------------------------------------------------\n";

      Real3x3 R3;

      R3 = 33.*Real3x3::identity();

      cout << "  R3.x[0] = " << R3.x[0] << endl;
      cout << "  R3.x[1] = " << R3.x[1] << endl;
      cout << "  R3.x[2] = " << R3.x[2] << endl;
      cout << "  R3.y[0] = " << R3.y[0] << endl;
      cout << "  R3.y[1] = " << R3.y[1] << endl;
      cout << "  R3.y[2] = " << R3.y[2] << endl;
      cout << "  R3.z[0] = " << R3.z[0] << endl;
      cout << "  R3.z[1] = " << R3.z[1] << endl;
      cout << "  R3.z[2] = " << R3.z[2] << endl;

    cout << "\nsuccess !!!!\n\n";

    cout <<
      "//----------------------------------------------------------\n"
      "// HujeuxLaw class test  create a Dummy Object called DO    \n"
      "//----------------------------------------------------------\n";

     HujeuxLaw DO;

     cout << "\nsuccess !!!!\n\n";

    cout <<
      "//----------------------------------------------------------\n"
      "// HujeuxLaw class test  check .readParameters for DO       \n"
      "//----------------------------------------------------------\n";

//     DO.readParameters("./../../../../test/load/Hujeuxparam.input");
     DO.readParameters("Hujeuxparam.input");

     cout << "\nsuccess !!!!\n\n";

     cout <<
          "//----------------------------------------------------------\n"
          "// HujeuxLaw class tests : simple shear on one material point ;\n"
          "//----------------------------------------------------------\n";

     auto   PI = acos(-1.);
     double	freq = 5., dt = 0.001, pc0 = -50.e3,
        	xmax = 0.001,//0.1% strains max
            dx = 0., x = 0.,
            tpeak = asin(1) / (2 * PI * freq),
            fact = tpeak/dt,faceps = 100.,facsig = 1.e-3;
     int	npi = (int)(fact), // number of steps per 1/4 cycle
            ncyc = 1,// only one loading cycle for this 1st test (to be increased later if everything works fine)
            npas = 4 * ncyc * npi;

     dvector *histab = new dvector(NHISTHUJ);
     for(int i = 0; i < NHISTHUJ; i++) (*histab)[i] = 0.;

     filebuf fichout;
//    fichout.open("./../../../../test/load/Hujeuxresults.output", ios::out);
     fichout.open("Hujeuxresults.output", ios::out);
     ostream os(&fichout);
     os.setf(std::ios::left);
     os.precision(8);
     os << "#Simple shear test on a material point";
     os << string("\n#t[s]\tgamxy[%]\tgampxy[%]\tsigxy[kPa]\tpmean[kPa]\tepsv[%]\tepsvp[%]") << endl;

     Tensor2 sig(Real3(pc0, pc0,pc0), Real3::zero()),// effective stress tensor for current step
             eps,	// strain tensor for current step
             epsp,// plastic strain tensor for current step
             deps,// strain tensor increment
             dsig;// effective stress tensor increment

     // saving order: gamxy[%]  gampxy[%]  sigxy[kPa] pmean[kPa] epsv[%]  epsvp[%]
     os << setw(15) << "0." << setw(15) << "0." << setw(15) << "0." << setw(15) << "0.";
     os << setw(15) << -pc0 * facsig << setw(15) << "0." << setw(15) << "0." << endl;

//     DO.initHistory(histab);
     if (DO.initState(sig, histab))
     {
         cout << "\nStop: Hujeux initialization failed!!\n";
         return -1;
     }


   //ofstream zzz("fileEpsIn.data");
     ofstream sss("fileSigOutRef.data");

     ifstream EPsin;
     EPsin.open("fileEpsIn.data");

     EPsin >> eps.m_vec[3]   ;
     bool is_converge = true;
     auto t = 0.;
     for (int i = 0; i < npas; i++)
     {
         auto x0 = xmax * sin(2 * PI * freq * t);
         t += dt;
         auto x = xmax * sin(2 * PI * freq * t);
         if (fabs(x0) < EPS) x0 = 0.;
         if (fabs(x) < EPS) x = 0.;
         dx = x - x0;

         // x = gamxy, dx = dgamxy
         //eps.m_vec[3] = 2 * x;//epsxy = 2*gamxy

         EPsin >> eps.m_vec[3]   ;
         deps.m_vec[3] = 2. * dx ;
         //EPsin >> deps.m_vec[3]   ;

         for(int j = 0; j < 6; j++)
            cout <<  std::setprecision(16) << " INITIAL  sig.m_vec[" << j <<"] " << sig.m_vec[j] << endl;
         for(int j = 0; j < 6; j++)
            cout << " INITIAL  dsig.m_vec[" << j <<"] " << dsig.m_vec[j] << endl;
         for(int j = 0; j < 6; j++)
            cout << " INITIAL  eps.m_vec[" << j <<"] " << eps.m_vec[j] << endl;

         //zzz  <<  std::setprecision(16) << eps.m_vec[3] << endl;

         for(int j = 0; j < 6; j++)
            cout << " INITIAL  deps.m_vec[" << j <<"] " << deps.m_vec[j] << endl;
         for(int j = 0; j < 6; j++)
            cout <<" INITIAL  epsp.m_vec[" << j <<"] " << epsp.m_vec[j] << endl;
         for(int j = 0; j < NHISTHUJ; j++)
            cout << " INITIAL (*histab)[" << j <<"] " << (*histab)[j] << endl;;


         DO.ComputeStress(histab,sig, eps, epsp, dsig, deps,is_converge);

         // saving order: gamxy[%]  gampxy[%]  sigxy[kPa] pmean[kPa] epsv[%]  epsvp[%]
         auto gamxy = eps.m_vec[3] * faceps / 2.; // in %
         auto gampxy = epsp.m_vec[3] * faceps / 2.; // in %
         auto sigxy = sig.m_vec[3] * facsig; // in kPa
         auto pmean = -trace(sig) / 3. * facsig; // in kPa
         auto epsv = trace(eps) * faceps;// in %
         auto epsvp = trace(epsp) * faceps; // in %

         for(int j = 0; j < 6; j++)
            cout << " FINAL sig.m_vec[" << j <<"] " << sig.m_vec[j] << endl;
         for(int j = 0; j < 6; j++)
            cout << " FINAL dsig.m_vec[" << j <<"] " << dsig.m_vec[j] << endl;
         for(int j = 0; j < 6; j++)
            cout << " FINAL  eps.m_vec[" << j <<"] " << eps.m_vec[j] << endl;
         for(int j = 0; j < 6; j++)
            cout << " FINAL  deps.m_vec[" << j <<"] " << deps.m_vec[j] << endl;
         for(int j = 0; j < 6; j++)
            cout << " FINAL  epsp.m_vec[" << j <<"] " << epsp.m_vec[j] << endl;
         for(int j = 0; j < NHISTHUJ; j++)
            cout << " FINAL (*histab)[" << j <<"] " << (*histab)[j] << endl;;

          sss <<  std::setprecision(32) << sig.m_vec[3] << endl;


         cout << "\n\n";
         os << setw(15) << t << setw(15) << gamxy << setw(15) << gampxy << setw(15) << sigxy;
         os << setw(15) << pmean << setw(15) << epsv << setw(15) << epsvp << endl;

         //eps.m_vec[3] = deps.m_vec[3];
     }
     fichout.close();

     cout << "\n\nhistab-evp       =" << (*histab)[0] << endl;
     cout << "histab-ray[0][0] = " << (*histab)[1] << endl;
     cout << "histab-ray[0][1] = " << (*histab)[2] << endl;
     cout << "histab-ray[1][0] = " << (*histab)[3] << endl;
     cout << "histab-ray[1][1] = " << (*histab)[4] << endl;
     cout << "histab-ray[2][0] = " << (*histab)[5] << endl;
     cout << "histab-ray[2][1] = " << (*histab)[6] << endl;
     cout << "histab-ray[3][0] = " << (*histab)[7] << endl;
     cout << "histab-ray[3][1] = " << (*histab)[8] << endl;

     cout << "\nsuccess !!!!\n\n";
     return 0;
 }
