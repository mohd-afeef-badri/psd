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
*     --------------------------------------------------------------------            *
*                                                                                     *
*     This file is intended for  providing an  interface  between PSD and             *
*     material laws for soil-dynamic calculations. The idea  is  that PSD             *
*     sends inputs: strain [vector], stress [vector],  internal-variables             *
*     [vector], and file-name-of-law-constants [string], these inputs are             *
*     processed and returned back as outputs.                                         *
*                                                                                     *
***************************************************************************************/


#include "ff++.hpp"
#include "./../hujeux-law-lib/utils.h"
#include "./../hujeux-law-lib/hujeux.h"

using namespace std;

//=============================================================================
// --- HujeuxSoilLaw class interface for PSD ---
//=============================================================================

template<class K>
class HujeuxSoilLaw_Op : public E_F0mps 
 {

  public:            
    static const int n_name_param = 4		;
    static basicAC_F0::name_and_type name_param[]	;
    Expression nargs[n_name_param]			;
        
    HujeuxSoilLaw_Op(const basicAC_F0& args) 
     {
      args.SetNameParam(n_name_param, name_param, nargs);
     }
        		
    AnyType operator()(Stack stack) const		;
 };

template<class K>
basicAC_F0::name_and_type HujeuxSoilLaw_Op<K>::name_param[] = 
 { 
    {"ParamaterFile"    , &typeid(string*)},
    {"stressVector"     , &typeid(KN<K>*)},
    {"strainVector"     , &typeid(KN<K>*)},            
    {"InternalVariables", &typeid(KN<K>*)}        
 };

template<class K>
class HujeuxSoilLaw : public OneOperator 
 {
  public:
    HujeuxSoilLaw() : OneOperator(atype<long>()) {}

    E_F0* code(const basicAC_F0& args) const 
     {
      return new HujeuxSoilLaw_Op<K>(args);
     }
 };


template<class K>
AnyType HujeuxSoilLaw_Op<K>::operator()(Stack stack) const 
 {
    
  string* paramFileName = nargs[0] ? GetAny<string*>((*nargs[0])(stack)) : NULL;  // file name containing law parameters  
  KN<K>*  sigPSD    = nargs[1] ? GetAny<KN<K>*>((*nargs[1])(stack))  : NULL	;     // PSD stress vector for all gauss points 
  KN<K>*  epsPSD    = nargs[2] ? GetAny<KN<K>*>((*nargs[2])(stack))  : NULL	;     // PSD starin vector for all gauss points   
  KN<K>*  hisVarPSD = nargs[3] ? GetAny<KN<K>*>((*nargs[3])(stack))  : NULL	;     // PSD history variable vector for all gauss points 


#ifdef DEBUG
  cout << "\n Entering class HujeuxSoilLaw  soil-laws.cpp\n"
          " Input parameters :\n"
          "            paramFileName = "  << *paramFileName 
       << endl;
       
  if(paramFileName == NULL) 
     cout << "******Error in class HujeuxSoilLaw_Op*******"
             "                                            "
             "      ParamaterFile cannot be empty         " 
             "********************************************"
          << endl;       
#endif

//----------------------------------------------------------
//  HujeuxLaw class tests : simple shear on one material point 
//---------------------------------------------------------- 
    
  HujeuxLaw PSDobject;                      // Creating PSDobject    
  PSDobject.readParameters(*paramFileName); // Read paramerts for HujeuxLaw    

  auto   PI     = acos(-1.),
         t      = 0.;  
  double freq   = 5., 
         dt     = 0.001,
         xmax   = 0.001,                     //0.1% strains max
         dx     = 0., 
         x      = 0.,
         tpeak  = asin(1) / (2 * PI * freq),
         fact   = tpeak/dt,
         faceps = 100.,
         facsig = 1.e-3;
  int	   npi    = (int)(fact),              // number of steps per 1/4 cycle
         ncyc   = 1,                        // only one loading cycle for this 1st test (to be increased later if everything works fine)
         npas   = 4 * ncyc * npi;

  Tensor2 sig(Real3( (*sigPSD)[0], (*sigPSD)[1], (*sigPSD)[2] ), 
              Real3::zero()                                 
             ),                                     // effective stress tensor for current step
          eps,	                                    // strain tensor for current step
          epsp,                                     // plastic strain tensor for current step
          deps,                                     // strain tensor increment
          dsig;                                     // effective stress tensor increment
          
          
  dvector *histab = new dvector(NHISTHUJ);
  for(int i = 0; i < NHISTHUJ; i++) 
    (*histab)[i] = (*hisVarPSD)[i];
     
     
  filebuf fichout;
  fichout.open("Hujeuxresults.output", ios::out);
  ostream os(&fichout);
  os.setf(ios::left);
  os.precision(8);
  os << "#Simple shear test on a material point";
  os << string("\n#gamxy[%]\tgampxy[%]\tsigxy[kPa]\tpmean[kPa]\tepsv[%]\tepsvp[%]") << "\n";
  os << setw(15) << "0." << setw(15) << "0." << setw(15) << "0.";
  os << setw(15) << -sigPSD->operator[](0) * facsig << setw(15) << "0." << setw(15) << "0." << "\n";

  PSDobject.initState(sig, histab);

  bool is_converge = true;

  for (int i = 0; i < npas; i++)
   {
    auto x0  = xmax * sin(2 * PI * freq * t);
    t += dt;
    auto x   = xmax * sin(2 * PI * freq * t);
    if (fabs(x0) < EPS) x0 = 0.;
    if (fabs(x) < EPS)  x  = 0.;
    dx = x - x0;

    eps.m_vec[3]  = 2 * x;                        //epsxy = 2*gamxy
    deps.m_vec[3] = 2 * dx;

    PSDobject.ComputeStress(histab,sig, eps, epsp, dsig, deps, is_converge);

    auto gamxy  =  eps.m_vec[3]  * faceps / 2.;   // [%]
    auto gampxy =  epsp.m_vec[3] * faceps / 2.;   // [%]
    auto sigxy  =  sig.m_vec[3]  * facsig     ;   // [kPa]
    auto pmean  = -trace(sig)    * facsig / 3.;   // [kPa]
    auto epsv   =  trace(eps)    * faceps;        // [%]
    auto epsvp  =  trace(epsp)   * faceps;        // [%]

    if(i==0)cout << "\nprinting step results in Hujeuxresults.ouput...\n";
    os << setw(15) << gamxy << setw(15) << gampxy << setw(15) << sigxy;
    os << setw(15) << pmean << setw(15) << epsv << setw(15) << epsvp << "\n";
   }
     fichout.close();
    
  return 0L;
}

static void InitFF()
{
  Global.Add("PSDHujeuxSoilLaw", "(", new HujeuxSoilLaw<double>);
}
LOADFUNC(InitFF)   
