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
**************************************************************************************/

string MaterialPropertyKind( int in )
{
     string out;
     if( in == 0 )
       out = "SCALAR";
     if( in == 1 )
       out = "VECTOR";
     if( in == 2 )
       out = "STENSOR";
     return out;
}

template<class K>
class PsdMfrontStats_Op : public E_F0mps {
  public:
    Expression behaviourName                          ;

    static const int n_name_param = 1                 ;
    static basicAC_F0::name_and_type name_param[]     ;
    Expression nargs[n_name_param]                    ;

    PsdMfrontStats_Op(const basicAC_F0& args ,
        Expression param1
        ) :
      behaviourName     (param1)
  {
    args.SetNameParam( n_name_param       ,
        name_param            ,
        nargs
        )                     ;
  }
    AnyType operator()(Stack stack) const ;
};

template<class K>
basicAC_F0::name_and_type PsdMfrontStats_Op<K>::name_param[] =
{
  {"mfrontBehaviourHypothesis"         , &typeid(std::string*)}
};

template<class K>
class PsdMfrontStats : public OneOperator {
  public:
    PsdMfrontStats() : OneOperator(atype<long>()    ,
        atype<string*>()
        ) {}

    E_F0* code(const basicAC_F0& args) const {
      return new PsdMfrontStats_Op<K>(args,
          t[0]->CastTo(args[0])
          );
    }
};

template<class K>
AnyType PsdMfrontStats_Op<K>::operator()(Stack stack) const {

  const string* mfrontBehaviourName         = GetAny<string*>((*behaviourName)(stack) );
  string* mfrontBehaviourHypothesis         = nargs[0] ? GetAny<std::string*>((*nargs[0])(stack) ) : NULL;

  cout << "\n\033[1;31m*********************************************************************************************\033[0m\n"
       << "\033[1;31m                   PSD-MFront Behaviour Stats                                      \033[0m"
       << "\n\033[1;31m*********************************************************************************************\033[0m\n"
       << "\n         This is a probing mechanisim that helps understad the inputs and the outputs"
       << "\n         that are expected by a .mfront law to be coupled with PSD. The porpose is to"
       << "\n         print a verbose information on the screen (see below). Note  that  only laws"
       << "\n         that have been precompiled with PSD will work."
       << "\n"
       << "\n         According to the inputs provided PsdMfrontPrintBehaviourStats() the following"
       << "\n         stats are generated"
       << "\n"
       << "\n\033[1;31m---------------------------------------------------------------------------------------------\033[0m\n"
       << "## Material Behaviour [INPUT] ##"
       << "\n\033[1;31m---------------------------------------------------------------------------------------------\033[0m\n"
       << "\n"
       << "\033[1;35m Choosen MFront Behaviour Name :: \033[0m \033[1;36m" << *mfrontBehaviourName
       << "\033[0m\n" 
       << "\n List of acceptable Behaviours"
       << "\n    - \"Elasticity\"                           # linear-elasticty problems"
       << "\n    - \"HelloWorld\"                           # dummy law for testing MFRONT-PSD"
       << "\n    - \"HujeuxECP1985\"                        # soil-dynamics non-linear problems"
       << "\n    - \"IsotropicLinearHardeningPlasticity\"   # Von Mises elasto-plastic problem"
       << "\n    - \"Iwan\"                                 # soil-dynamics non-linear problems"
       << "\n    - \"desmorat20152d\"                       # local full 2D anisotropic damage"
       << "\n    - \"desmorat20152dnonlocal\"               # nonlocal full 2D anisotropic damage"
       << "\n    - \"desmorat3Dnonlocal\"                  # nonlocal 3D anisotropic damage"
       << "\n"
       << "\n\033[1;31m---------------------------------------------------------------------------------------------\033[0m\n"
       << "## Material Hypothesis [INPUT] ##"
       << "\n\033[1;31m---------------------------------------------------------------------------------------------\033[0m\n"
       << "\n"
       << "\033[1;35m Choosen MFront Behaviour Hypothesis :: \033[0m \033[1;36m" << *mfrontBehaviourHypothesis
       << "\033[0m\n"
       << "\n List of acceptable Hypothesis"
       << "\n    - \"GENERALISEDPLANESTRAIN\"  # for a 2D problem"
       << "\n    - \"PLANESTRAIN\"             # for a 2D problem"
       << "\n    - \"TRIDIMENSIONAL\"          # for a 3D problem"
       << "## NOTICE THAT full 2D model should be used for anisotropic damage ##"
       <<
   endl;
 
   mgis::behaviour::Hypothesis h;

   if(*mfrontBehaviourHypothesis=="GENERALISEDPLANESTRAIN")
     h = Hypothesis::GENERALISEDPLANESTRAIN;

   if(*mfrontBehaviourHypothesis=="PLANESTRAIN")
     h = Hypothesis::PLANESTRAIN;

   if(*mfrontBehaviourHypothesis=="TRIDIMENSIONAL")
     h = Hypothesis::TRIDIMENSIONAL;

   const auto b = load(MFRONT_SHARED_LIBRARY_LOCATION, *mfrontBehaviourName , h);

   if(b.params.size() > 0){

       cout
       << "\n\033[1;31m---------------------------------------------------------------------------------------------\033[0m\n"
       << "## Parameters [INPUT] ##"
       << "\n\033[1;31m---------------------------------------------------------------------------------------------\033[0m\n"
       << "\n"
       << "\033[1;35m The chosen MFront behaviour expects the following Parameters \033[0m"
       << "\n"
       <<
       endl;

       for (int i=0; i < b.params.size(); i++)
           cout << "    Parameters name :   \033[1;36m" <<  b.params[i] << "\033[0m"
                << "\tof value \033[1;36m" <<  getParameterDefaultValue<double>(b, b.params[i])   << "\033[0m" <<
            endl;
   }

   if( b.mps.size() > 0){

       cout
       << "\n\033[1;31m---------------------------------------------------------------------------------------------\033[0m\n"
       << "## Material Properties [INPUT] ##"
       << "\n\033[1;31m---------------------------------------------------------------------------------------------\033[0m\n"
       << "\n"
       << "\033[1;35m The chosen MFront behaviour expects the following material properties \033[0m"
       << "\n"
       <<
       endl;

       for (int i=0; i < b.mps.size(); i++)
           cout << "    Material property name :   \033[1;36m" <<  b.mps[i].name << "\033[0m"
                << "\tof type \033[1;36m" <<  MaterialPropertyKind(b.mps[i].type)  << "\033[0m" <<
            endl;


       if (verbosity){
       int componentsMps = 0;

       if (*mfrontBehaviourHypothesis=="GENERALISEDPLANESTRAIN" || *mfrontBehaviourHypothesis=="PLANESTRAIN"){
          for (int i=0; i < b.mps.size(); i++){
             if(b.mps[i].type == 0) componentsMps += 1;
             if(b.mps[i].type == 1) componentsMps += 1;
             if(b.mps[i].type == 2) componentsMps += 4;
          }
       }

       if (*mfrontBehaviourHypothesis=="TRIDIMENSIONAL"){
          for (int i=0; i < b.mps.size(); i++){
             if(b.mps[i].type == 0) componentsMps += 1;
             if(b.mps[i].type == 1) componentsMps += 1;
             if(b.mps[i].type == 2) componentsMps += 6;
          }
       }

       cout
       << "\n\033[1;35m To provide infomation about material properties in your PSD-MFront code  \033[0m"
       << "\n\033[1;35m create a "<< componentsMps <<" component string variable (space seperated) for denoting the    \033[0m"
       << "\n\033[1;35m the names of the material properties and a "<< componentsMps <<" component  vector variable   \033[0m"
       << "\n\033[1;35m for denoting values of material  properties in ControlParameters.edp file.   \033[0m"
       << "\n"
       << "\n\033[1;36m"
       << "              string       PropertyNames = \"";

       for (int i=0; i < componentsMps; i++){
           if(i < componentsMps-1)
             cout << "" <<  b.mps[i].name <<" ";
           else
             cout << "" <<  b.mps[i].name <<"\";\033[0m";
       }

       cout
       << "\n"
       << "\n\033[1;36m"
       << "              real[int]    PropertyValues = [";

       for (int i=0; i < componentsMps; i++){
           if(i < componentsMps-1)
             cout << " " <<  MaterialPropertyKind(b.mps[i].type) <<",";
           else
             cout << " " <<  MaterialPropertyKind(b.mps[i].type) <<" ];\033[0m";
       }

       cout
       << "\n"
       << "\n\033[1;35m This information can then be provided to the PsdMfrontHandler(...) function   \033[0m"
       << "\n"
       << "\n\033[1;36m"
       << "              PsdMfrontHandler( ...., mfrontPropertyNames  = PropertyNames,               "
       << "\n                                    mfrontPropertyValues = PropertyValues, ....);\033[0m"
       << "\n"
       << "\n\033[1;35m MFront will provide you the material properties for the chosen behaviour.    \033[0m"
       << "\n";
       }
   }

   if( b.esvs.size() > 0){

       cout
       << "\n\033[1;31m---------------------------------------------------------------------------------------------\033[0m\n"
       << "## Material external state variables [INPUT] ##"
       << "\n\033[1;31m---------------------------------------------------------------------------------------------\033[0m\n"
       << "\n"
       << "\033[1;35m The chosen MFront behaviour expects the following external state variables \033[0m"
       << "\n"
       <<
       endl;

       for (int i=0; i < b.esvs.size(); i++)
           cout << "    external state variables name :   \033[1;36m" <<  b.esvs[i].name << "\033[0m"
                << "\tof type \033[1;36m" <<  MaterialPropertyKind(b.esvs[i].type)  << "\033[0m" <<
            endl;

       if (verbosity){
       int componentsEsvs = 0;

       if (*mfrontBehaviourHypothesis=="GENERALISEDPLANESTRAIN" || *mfrontBehaviourHypothesis=="PLANESTRAIN"){
          for (int i=0; i < b.esvs.size(); i++){
             if(b.esvs[i].type == 0) componentsEsvs += 1;
             if(b.esvs[i].type == 1) componentsEsvs += 1;
             if(b.esvs[i].type == 2) componentsEsvs += 4;
          }
       }

       if (*mfrontBehaviourHypothesis=="TRIDIMENSIONAL"){
          for (int i=0; i < b.esvs.size(); i++){
             if(b.esvs[i].type == 0) componentsEsvs += 1;
             if(b.esvs[i].type == 1) componentsEsvs += 1;
             if(b.esvs[i].type == 2) componentsEsvs += 6;
          }
       }


       
       if (*mfrontBehaviourName != "desmorat20152dnonlocal" && *mfrontBehaviourName != "desmorat3Dnonlocal" ){
       	       
       	       cout
	       << "\n\033[1;35m To provide infomation about external state variables in  your PSD-MFront code  \033[0m"
	       << "\n\033[1;35m create a  "<< componentsEsvs <<" component string variable (space seperated) for denoting the names \033[0m"
	       << "\n\033[1;35m of the external state variables and a "<< componentsEsvs <<" component vector variable for denoting \033[0m"
	       << "\n\033[1;35m the values of the external state variables  in ControlParameters.edp file.   \033[0m"
	       << "\n"
	       << "\n\033[1;36m"
	       << "              string       ExternalStateVariablesNames = \"";

	       for (int i=0; i < componentsEsvs; i++){
		   if(i < componentsEsvs-1)
		     cout << "" <<  b.esvs[i].name <<" ";
		   else
		     cout << "" <<  b.esvs[i].name <<"\";\033[0m";
	       }
       	       
       	       
	       cout
	       << "\n"
	       << "\n\033[1;36m"
	       << "              real[int]    ExternalStateVariablesValues = [";

	       for (int i=0; i < componentsEsvs; i++){
		   if(i < componentsEsvs-1)
		     cout << " " <<  MaterialPropertyKind(b.esvs[i].type) <<",";
		   else
		     cout << " " <<  MaterialPropertyKind(b.esvs[i].type) <<" ];\033[0m";
	       }

	       cout
	       << "\n"
	       << "\n\033[1;35m This information can then be provided to the PsdMfrontHandler(....) function   \033[0m"
	       << "\n"
	       << "\n\033[1;36m"
	       << "              PsdMfrontHandler( ...., mfrontExternalStateVariableNames  = ExternalStateVariablesNames,               "
	       << "\n                                    mfrontExternalStateVariableValues = ExternalStateVariablesValues, ....);\033[0m"
	       << "\n"
	       << "\n\033[1;35m MFront will provide you the external state variables for the chosen behaviour.    \033[0m"
	       << "\n";
        }//if not nonlocal laws
	else {
	
	       cout
	       << "\n\033[1;35m To provide infomation about external state variables in  your PSD-MFront code  \033[0m"
	       << "\n\033[1;35m create a  "<< componentsEsvs <<" component string variable (space seperated) for denoting the names \033[0m"
	       << "\n\033[1;35m of the external state variables and a "<< componentsEsvs <<" component vector variable for denoting \033[0m"
	       << "\n\033[1;35m the values of the external state variables.   \033[0m"
	        << "\n"
	       << "\n\033[1;36m"
	       << "              string       ExternalStateVariablesNames = \"";

	       for (int i=0; i < componentsEsvs; i++){
		   if(i < componentsEsvs-1)
		     cout << "" <<  b.esvs[i].name <<" ";
		   else
		     cout << "" <<  b.esvs[i].name <<"\";\033[0m";
	       }
	       
	       cout
	       << "\n\033[1;35m To provide infomation about external state variables in your PSD-MFront code  \033[0m"
	       << "\n\033[1;35m create a  "<< componentsEsvs <<" component vector variable in vectorial Quadrature finite element  \033[0m"
	       << "\n\033[1;35m space ('Sh2') for external state variables in FemParameters.edp file.  \033[0m"
	       << "\n"
	       << "\n\033[1;36m"
	       << "		Sh2 [ExtT,ExtEpsnl];";
	       
	       cout
	       << "\n"
	       << "\n\033[1;35m Create P0 fields temperature and epsnlP0 and then : 			 \033[0m"
	        << "\n"
	       << "\n\033[1;36m"
	       << "		[ExtT,ExtEpsnl] = [Tempera,epsnlP0];"
	       << "\n";
	      
	       cout
	       << "\n"
	       << "\n\033[1;35m This information can then be provided to the PsdMfrontHandler(....) function   \033[0m"
	       << "\n"
	       << "\n\033[1;36m"
	       << "              PsdMfrontHandler( ...., mfrontExternalStateVariableNames  = ExternalStateVariablesNames,               " 
	       << "\n 					 mfrontExternalStateVariableVector = ExtT[], ....);\033[0m"
	       << "\n"
	       << "\n\033[1;35m step. Please note that by using ExtT[] we reference the full vector of external   \033[0m"
	       << "\n\033[1;35m state variables, this is just a programming pratice that may be confusing.       \033[0m"
	       << "\n";
	}// else nonlocal laws
      
      
        }//if verbosity
   }

   if( b.isvs.size() > 0){

       cout
       << "\n\033[1;31m---------------------------------------------------------------------------------------------\033[0m\n"
       << "## Material internal state variables  [OUTPUT] ##"
       << "\n\033[1;31m---------------------------------------------------------------------------------------------\033[0m\n"
       << "\n"
       << "\033[1;35m The chosen MFront behaviour expects the following internal state variables \033[0m"
       << "\n"
       <<
       endl;

       for (int i=0; i < b.isvs.size(); i++)
           cout << "    internal state variables name :   \033[1;36m" <<  b.isvs[i].name << "\033[0m"
                << "\t\tof type \033[1;36m" <<  MaterialPropertyKind(b.isvs[i].type)  << "\033[0m" <<
            endl;

       if (verbosity){
       int componentsIsvs = 0;

       if (*mfrontBehaviourHypothesis=="GENERALISEDPLANESTRAIN" || *mfrontBehaviourHypothesis=="PLANESTRAIN"){
          for (int i=0; i < b.isvs.size(); i++){
             if(b.isvs[i].type == 0) componentsIsvs += 1;
             if(b.isvs[i].type == 1) componentsIsvs += 1;
             if(b.isvs[i].type == 2) componentsIsvs += 4;
          }
       }

       if (*mfrontBehaviourHypothesis=="TRIDIMENSIONAL"){
          for (int i=0; i < b.isvs.size(); i++){
             if(b.isvs[i].type == 0) componentsIsvs += 1;
             if(b.isvs[i].type == 1) componentsIsvs += 1;
             if(b.isvs[i].type == 2) componentsIsvs += 6;
          }
       }

       cout
       << "\n\033[1;35m To provide infomation about internal state variables in your PSD-MFront code  \033[0m"
       << "\n\033[1;35m create a  "<< componentsIsvs <<" component vector variable in vectorial Quadrature finite element  \033[0m"
       << "\n\033[1;35m space ('Ih') for internal state variables in FemParameters.edp file.  \033[0m"
       << "\n"
       << "\n\033[1;36m"
       << "              Ih [";

       for (int i=0; i < componentsIsvs; i++){
           if(i < componentsIsvs-1)
             cout << " Isv" <<  i <<",";
           else
             cout << " Isv" <<  i <<" ];\033[0m";
       }

       cout
       << "\n"
       << "\n\033[1;35m This information can then be provided to the PsdMfrontHandler(....) function   \033[0m"
       << "\n"
       << "\n\033[1;36m"
       << "              PsdMfrontHandler( ...., mfrontStateVariable = Isv1[], ....);\033[0m"
       << "\n"
       << "\n\033[1;35m MFront will provide you the internal state variables at the end of integration   \033[0m"
       << "\n\033[1;35m step. Please note that by using Isv1[] we refernce the full vector of internal   \033[0m"
       << "\n\033[1;35m state variables, this is just a programming pratice that may be confusing.       \033[0m"
       << "\n";
       }
   }

   if( b.gradients.size() > 0){

       cout
       << "\n\033[1;31m---------------------------------------------------------------------------------------------\033[0m\n"
       << "## Material gradients input  [INPUT] ##"
       << "\n\033[1;31m---------------------------------------------------------------------------------------------\033[0m\n"
       << "\n"
       << "\033[1;35m The chosen MFront behaviour expects the following gradients \033[0m"
       << "\n"
       <<
       endl;

       for (int i=0; i < b.gradients.size(); i++)
           cout << "    gradient name :   \033[1;36m" <<  b.gradients[i].name << "\033[0m"
                << "\tof type \033[1;36m" <<  MaterialPropertyKind(b.gradients[i].type)  << "\033[0m" <<
            endl;

       if (verbosity){
       int componentsGrad = 0;

       if (*mfrontBehaviourHypothesis=="GENERALISEDPLANESTRAIN" || *mfrontBehaviourHypothesis=="PLANESTRAIN")
             componentsGrad += 3;

       if (*mfrontBehaviourHypothesis=="TRIDIMENSIONAL")
             componentsGrad += 6;

       cout
       << "\n\033[1;35m To provide infomation about internal "<<MaterialPropertyKind(b.gradients[0].type)<<" state  in your PSD-MFront code  \033[0m"
       << "\n\033[1;35m create a  "<< componentsGrad <<" component vector variable in vectorial Quadrature finite element  \033[0m"
       << "\n\033[1;35m space ('Sh') for "<<MaterialPropertyKind(b.gradients[0].type)<<" variables in FemParameters.edp file.  \033[0m"
       << "\n"
       << "\n\033[1;36m"
       << "              Sh [";

       for (int i=0; i < componentsGrad; i++){
           if(i < componentsGrad-1)
             cout << " Eps" <<  i <<",";
           else
             cout << " Eps" <<  i <<" ];\033[0m";
       }

       cout
       << "\n"
       << "\n\033[1;35m This information can then be provided to the PsdMfrontHandler(....) function   \033[0m"
       << "\n"
       << "\n\033[1;36m"
       << "              PsdMfrontHandler( ...., mfrontStrainTensor = Eps1[], ....);\033[0m"
       << "\n"
       << "\n\033[1;35m MFront will provide you the "<<MaterialPropertyKind(b.gradients[0].type)<<" state for the integration   \033[0m"
       << "\n\033[1;35m step. Please note that by using Eps1[] we refernce the full vector of "<<MaterialPropertyKind(b.gradients[0].type)<<"   \033[0m"
       << "\n\033[1;35m variables, this is just a programming pratice that may be confusing.       \033[0m"
       << "\n";
       }

   }
   
   if( b.thermodynamic_forces.size() > 0){

       cout
       << "\n\033[1;31m---------------------------------------------------------------------------------------------\033[0m\n"
       << "## Material thermodynamic forces input  [OUTPUT] ##"
       << "\n\033[1;31m---------------------------------------------------------------------------------------------\033[0m\n"
       << "\n"
       << "\033[1;35m The chosen MFront behaviour expects the following thermodynamic forces \033[0m"
       << "\n"
       <<
       endl;

       for (int i=0; i < b.thermodynamic_forces.size(); i++)
           cout << "    thermodynamic forces name :   \033[1;36m" <<  b.thermodynamic_forces[i].name << "\033[0m"
                << "\tof type \033[1;36m" <<  MaterialPropertyKind(b.thermodynamic_forces[i].type)  << "\033[0m" <<
            endl;

       if (verbosity){
       int componentsGrad = 0;

       if (*mfrontBehaviourHypothesis=="GENERALISEDPLANESTRAIN" || *mfrontBehaviourHypothesis=="PLANESTRAIN")
             componentsGrad += 3;

       if (*mfrontBehaviourHypothesis=="TRIDIMENSIONAL")
             componentsGrad += 6;

       cout
       << "\n\033[1;35m To provide infomation about internal "<<MaterialPropertyKind(b.thermodynamic_forces[0].type)<<" state  in your PSD-MFront code  \033[0m"
       << "\n\033[1;35m create a  "<< componentsGrad <<" component vector variable in vectorial Quadrature finite element  \033[0m"
       << "\n\033[1;35m space ('Sh') for "<<MaterialPropertyKind(b.thermodynamic_forces[0].type)<<" variables in FemParameters.edp file.  \033[0m"
       << "\n"
       << "\n\033[1;36m"
       << "              Sh [";

       for (int i=0; i < componentsGrad; i++){
           if(i < componentsGrad-1)
             cout << " Sig" <<  i <<",";
           else
             cout << " Sig" <<  i <<" ];\033[0m";
       }

       cout
       << "\n"
       << "\n\033[1;35m This information can then be provided to the PsdMfrontHandler(....) function   \033[0m"
       << "\n"
       << "\n\033[1;36m"
       << "              PsdMfrontHandler( ...., mfrontStressTensor = Sig1[], ....);\033[0m"
       << "\n"
       << "\n\033[1;35m MFront will provide you the "<<MaterialPropertyKind(b.thermodynamic_forces[0].type)<<" state at the end of integration   \033[0m"
       << "\n\033[1;35m step. Please note that by using Sig1[] we refernce the full vector of "<<MaterialPropertyKind(b.thermodynamic_forces[0].type)<<"   \033[0m"
       << "\n\033[1;35m variables, this is just a programming pratice that may be confusing.       \033[0m"
       << "\n";
       }

   }   

  cout << "\n\033[1;31m*****************************************END*************************************************\033[0m\n"
       <<
  endl;

  return 0L;
}
