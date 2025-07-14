/**************************************************************************************
*                                                                                     *
*           This file is a part of PSD (Parallel Structural Dynamics)                 *
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
**************************************************************************************/
#include "stdafx.h"

extern const double	EPS, TOL;

extern long lapack_inv(double*, int);
extern int hardcoded_4Dinv(double**);
extern long lapack_test(double**, int);
using namespace std;

int main()
 {
  int nbtimes = 1000;
   
   cout <<
   "\n\n"
   "*==============================================================*\n"
   "*            test inverse function gauss                       *\n"
   "*  ----------------------------------------------------------  *\n"   
   "* void  gauss(double**, double*, double*, const int&);         *\n"
   "*==============================================================*\n"
   "\n\n"; 

    clock_t start, end;
    
    double A [4*4] = {
        1,1,1,-1,
        1,1,-1,1,
        1,-1,1,1,
        -1,1,1,1,
    };
       

   start = clock();
  for(int i=0; i<nbtimes; i++)
    lapack_inv(A, 4);
  end = clock();
  
  double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
    cout << "Time taken by LAPACK program is : " << fixed  
         << time_taken << setprecision(5); 
    cout << " sec " << endl; 
    
      
    printf("%f %f %f %f\n", A[0], A[1], A[2], A[3]);
    printf("%f %f %f %f\n", A[4], A[5], A[6], A[7]);
    printf("%f %f %f %f\n", A[8], A[9], A[10], A[11]);
    printf("%f %f %f %f\n", A[12], A[13], A[14], A[15]);    

    cout << "\n\n";
    
    
   // Allocating memory for array and elements
    double ** AA = new double*[4];
	for (int i = 0; i < 4; i++) {
    AA[i] = new double[4];
	}
        
   for (int i = 0; i < 4; i++) {
     for (int j = 0; j < 4; j++) {
         AA[i][j] = 1.;
     }
    }
    AA[0][3]=-1.;
    AA[1][2]=-1.;
    AA[2][1]=-1.;
    AA[3][0]=-1.; 

   start = clock();
   for(int i=0; i<nbtimes; i++)            
     hardcoded_4Dinv(AA);
   end = clock();  
 
    time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
    cout << "Time taken by HARDCORD program is : " << fixed  
         << time_taken << setprecision(5); 
    cout << " sec " << endl;      
    printf("%f %f %f %f\n", AA[0][0], AA[0][1], AA[0][2], AA[0][3]);
    printf("%f %f %f %f\n", AA[1][0], AA[1][1], AA[1][2], AA[1][3]);
    printf("%f %f %f %f\n", AA[2][0], AA[2][1], AA[2][2], AA[2][3]);
    printf("%f %f %f %f\n", AA[3][0], AA[3][1], AA[3][2], AA[3][3]);            


    cout << "\n\n";
    
    
    double ** BB = new double*[4];
    double * HB = new double[4];
    int nmec=4;
	for (int i = 0; i < 4; i++) {
    BB[i] = new double[4];
	}
        
   for (int i = 0; i < 4; i++) {
        HB[i]=i;
     for (int j = 0; j < 4; j++) {
         BB[i][j] = 1.;
     }
    }
    BB[0][3]=-1.;
    BB[1][2]=-1.;
    BB[2][1]=-1.;
    BB[3][0]=-1.;
    		
   start = clock();
   for(int i=0; i<nbtimes; i++) 	
		gauss(BB,HB,HB,nmec);
   end = clock(); 		

    time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
    cout << "Time taken by GAUSS program is : " << fixed  
         << time_taken << setprecision(5); 
    cout << " sec " << endl;      
    printf("%f %f %f %f\n", BB[0][0], BB[0][1], BB[0][2], BB[0][3]);
    printf("%f %f %f %f\n", BB[1][0], BB[1][1], BB[1][2], BB[1][3]);
    printf("%f %f %f %f\n", BB[2][0], BB[2][1], BB[2][2], BB[2][3]);
    printf("%f %f %f %f\n", BB[3][0], BB[3][1], BB[3][2], BB[3][3]); 			    

    cout << "\n\n";

    double ** CC = new double*[4];
	for (int i = 0; i < 4; i++) {
    CC[i] = new double[4];
	}
        
   for (int i = 0; i < 4; i++) {
     for (int j = 0; j < 4; j++) {
         CC[i][j] = 1.;
     }
    }
    CC[0][3]=-1.;
    CC[1][2]=-1.;
    CC[2][1]=-1.;
    CC[3][0]=-1.;
    		
   start = clock();
   for(int i=0; i<nbtimes; i++) 	
     lapack_test(CC, 4);  	
   end = clock(); 		

    time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
    cout << "Time taken by LAPACK 2 program is : " << fixed  
         << time_taken << setprecision(5); 
    cout << " sec " << endl;      
    printf("%f %f %f %f\n", CC[0][0], CC[0][1], CC[0][2], CC[0][3]);
    printf("%f %f %f %f\n", CC[1][0], CC[1][1], CC[1][2], CC[1][3]);
    printf("%f %f %f %f\n", CC[2][0], CC[2][1], CC[2][2], CC[2][3]);
    printf("%f %f %f %f\n", CC[3][0], CC[3][1], CC[3][2], CC[3][3]); 

   cout << "\nsuccess !!!!\n\n";
             
   return 0;
 }
