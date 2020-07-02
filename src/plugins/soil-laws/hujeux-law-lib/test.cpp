/*****************************************************************************

         This file is a part of PSD (Parallel Structural Dynamics)

     -------------------------------------------------------------------

     Author(s): Mohd Afeef Badri, Evelyne Foerster
     Email    : mohd-afeef.badri@cea.fr 
     Date     : 2018‑06‑01

     -------------------------------------------------------------------

     PSD a parallel  finite  element framework  provides tools to  solve 
     multiple  solid-dynamic  problems; PSD is distributed  in  the hope 
     that it will be useful, but WITHOUT ANY WARRANTY; or  without  even  
     the implied warranty of  FITNESS  FOR  A  PARTICULAR  PURPOSE.
     
     --------------------------------------------------------------------
     
     This file allows testing hejeux and utils libraries, any  function
     defined in  hejeux.cpp or utils.cpp can be tested here. To compile 
     1. with intel complier
     
       icpc -c ocpp -std=c++11 -fpic; 
       icpc -c hujeux.cpp -DDEBUG -std=c++11 -fpic
       icpc -c test.cpp -std=c++11
       icpc -o hujeux-utils-tester utils.o hujeux.cpp test.cpp -std=c++11
       
     2. with GNU compiler
     
       g++ -c ocpp -std=c++11 -fpic; 
       g++ -c hujeux.cpp -DDEBUG -std=c++11 -fpic
       g++ -c test.cpp -std=c++11
       g++ -o hujeux-utils-tester utils.o hujeux.cpp test.cpp  -std=c++11   

*******************************************************************************/

#include "stdafx.h"

using namespace std;

int main()
 {
   cout << "  hujeux-utils-tester started ...." << endl;
   
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
              
      DO.readParameters("ok.in");

   cout << "\nsuccess !!!!\n\n";
 
 
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
   return 0;
 }
