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
//#include <stdio.h>
//#include "utils.h"
//#include "hujeux.h"

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
    
   return 0;
 }
