/*****************************************************************************

         This file is a part of PSD (Parallel Structural Dynamics)

     -------------------------------------------------------------------

     Author(s): Mohd Afeef Badri
     Email    : mohd-afeef.badri@cea.com
     Date     : 2021‑08‑18

     -------------------------------------------------------------------

     PSD a parallel  finite  element framework  provides tools to  solve
     multiple  solid-dynamic  problems; PSD is distributed  in  the hope
     that it will be useful, but WITHOUT ANY WARRANTY; or  without  even
     the implied warranty of  FITNESS  FOR  A  PARTICULAR  PURPOSE.

*******************************************************************************/

template<class K>
class PsdMfrontHandler_Op : public E_F0mps {
  public:
    Expression behaviourName                          ;

    static const int n_name_param = 11                 ;
    static basicAC_F0::name_and_type name_param[]     ;
    Expression nargs[n_name_param]                    ;

    PsdMfrontHandler_Op(const basicAC_F0& args ,
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
basicAC_F0::name_and_type PsdMfrontHandler_Op<K>::name_param[] =
{
  {"mfrontBehaviourHypothesis"         , &typeid(std::string*)},
  {"mfrontPropertyNames"               , &typeid(std::string*)},
  {"mfrontPropertyValues"              , &typeid(KN<K>*)      },
  {"mfrontExternalStateVariableNames"  , &typeid(std::string*)},
  {"mfrontExternalStateVariableValues" , &typeid(KN<K>*)      },
  {"mfrontMaterialTensor"              , &typeid(KN<K>*)      },
  {"mfrontStrainTensor"                , &typeid(KN<K>*)      },
  {"mfrontStressTensor"                , &typeid(KN<K>*)      },
  {"mfrontStateVariable"               , &typeid(KN<K>*)      },
  {"mfrontPreviousStrainTensor"        , &typeid(KN<K>*)      },
  {"mfrontExternalStateVariableVector" , &typeid(KN<K>*)      }  
};

template<class K>
class PsdMfrontHandler : public OneOperator {
  public:
    PsdMfrontHandler() : OneOperator(atype<long>()    ,
        atype<string*>()
        ) {}

    E_F0* code(const basicAC_F0& args) const {
      return new PsdMfrontHandler_Op<K>(args,
          t[0]->CastTo(args[0])
          );
    }
};

template<class K>
AnyType PsdMfrontHandler_Op<K>::operator()(Stack stack) const {

  //const auto muMfront = mgis::real{GetAny<double>((*mu)(stack))};

  const string* mfrontBehaviourName = GetAny<string*>((*behaviourName)(stack));

  string* mfrontBehaviourHypothesis         = nargs[0] ? GetAny<std::string*>((*nargs[0])(stack)) : NULL;
  string* mfrontPropertyNames               = nargs[1] ? GetAny<std::string*>((*nargs[1])(stack)) : NULL;
  KN<K>*  mfrontPropertyValues              = nargs[2] ? GetAny<KN<K>*>((*nargs[2])(stack))       : NULL;
  string* mfrontExternalStateVariableNames  = nargs[3] ? GetAny<std::string*>((*nargs[3])(stack)) : NULL;
  KN<K>* mfrontExternalStateVariableValues  = nargs[4] ? GetAny<KN<K>*>((*nargs[4])(stack))       : NULL;
  KN<K>* mfrontMaterialTensor               = nargs[5] ? GetAny<KN<K>*>((*nargs[5])(stack))       : NULL;
  KN<K>* mfrontStrainTensor                 = nargs[6] ? GetAny<KN<K>*>((*nargs[6])(stack))       : NULL;
  KN<K>* mfrontStressTensor                 = nargs[7] ? GetAny<KN<K>*>((*nargs[7])(stack))       : NULL;
  KN<K>* mfrontStateVariable                = nargs[8] ? GetAny<KN<K>*>((*nargs[8])(stack))       : NULL;
  KN<K>* mfrontPreviousStrainTensor         = nargs[9] ? GetAny<KN<K>*>((*nargs[9])(stack))       : NULL;
  KN<K>* mfrontExternalStateVariableVector  = nargs[10] ? GetAny<KN<K>*>((*nargs[10])(stack))     : NULL;

  if(mfrontBehaviourName!=NULL && verbosity)
    cout << " \n"
         << " \033[1;36m Message MFront mfrontBehaviourName       :: \033[0m " << *mfrontBehaviourName
         << " \n"
         << endl;

  if(mfrontBehaviourHypothesis!=NULL && verbosity)
    cout << " \n"
         << " \033[1;36m Message MFront mfrontBehaviourHypothesis :: \033[0m " << *mfrontBehaviourHypothesis
         << " \n"
         << endl;


  if( mfrontBehaviourHypothesis != NULL &&
      ( *mfrontBehaviourHypothesis != "GENERALISEDPLANESTRAIN" &&
        *mfrontBehaviourHypothesis != "PLANESTRAIN"            &&
        *mfrontBehaviourHypothesis != "TRIDIMENSIONAL"
      )
    )
  {
    cout
    <<"===================================================================\n"
      " \033[1;31m ** ERROR DETECTED  **                           \033[0m\n"
      "===================================================================\n"
      " WRONG hypothesis was provided by user. Please consider               \n"
      " filling in the \033[1;34m mfrontBehaviourHypothesis \033[0m argument \n"
      " in PsdMfrontHandler(...) function. Example                           \n"
      "   \033[1;34m PsdMfrontHandler( mfrontBehaviourHypothesis = \"GENERALISEDPLANESTRAIN\", .... ) \033[0m\n"
      "   \033[1;34m PsdMfrontHandler( mfrontBehaviourHypothesis = \"PLANESTRAIN\", .... )            \033[0m\n"
      "   \033[1;34m PsdMfrontHandler( mfrontBehaviourHypothesis = \"TRIDIMENSIONAL\", .... )         \033[0m\n"
      "===================================================================\n"
    << endl;

    exit(1);
  }


  if( mfrontBehaviourHypothesis!=NULL)
{

  //------------------------------------------------
  // Set hypothesis for MGIS
  //-----------------------------------------------
  if(verbosity)
      cout << " \n"
           << " \033[1;36m Message MFront :: Creating Hypothesis :: \033[0m " << *mfrontBehaviourHypothesis
           << " \n"
           << endl;

  mgis::behaviour::Hypothesis h;

  if(*mfrontBehaviourHypothesis=="GENERALISEDPLANESTRAIN")
     h = Hypothesis::GENERALISEDPLANESTRAIN;

  if(*mfrontBehaviourHypothesis=="PLANESTRAIN")
    h = Hypothesis::PLANESTRAIN;

  if(*mfrontBehaviourHypothesis=="TRIDIMENSIONAL")
     h = Hypothesis::TRIDIMENSIONAL;

  //------------------------------------------------
  // Create behaviour/data/view for MGIS
  //------------------------------------------------
  if(verbosity)
      cout << " \n"
           << " \033[1;36m Message MFront :: Loading  Behaviour  ::     \033[0m " << *mfrontBehaviourName   << "\n"
           << " \033[1;36m                :: Creating BehaviourData     \033[0m "                           << "\n"
           << " \033[1;36m                :: Creating BehaviourDataView \033[0m "                           << "\n"
           << " \n"
           << endl;

  const auto b = load(MFRONT_SHARED_LIBRARY_LOCATION, *mfrontBehaviourName , h);
  auto d = BehaviourData{b};
  auto v = make_view(d);


    //----------------------------------------------
    // Get information about total internal state variables
    //----------------------------------------------
  int componentsIsvs = 0;
  if(b.isvs.size() > 0){

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
  }
  //------------------------------------------------
  // Assigning Properties for MGIS
  //-----------------------------------------------

  if( b.mps.size() > 0){


    if( mfrontPropertyNames  == NULL || mfrontPropertyValues == NULL || mfrontPropertyValues->n < b.mps.size() ){
       cout <<
       "===================================================================\n"
       " \033[1;31m ** ERROR DETECTED  **                           \033[0m\n"
       "===================================================================\n"
       " mfrontPropertyNames and/or  mfrontPropertyValues wrong. Please consider \n"
       " filling in  \033[1;34mmfrontPropertyNames\033[0m   and   \033[1;34mmfrontPropertyValues\033[0m  arguments\n"
       " correctly in the in PsdMfrontHandler(...) function. For example,\n"
       "   \033[1;34m PsdMfrontHandler( ..., mfrontPropertyNames = \"YoungModulus PoissonRatio\", mfrontPropertyValues = [1e9, 0.3], .... )\033[0m\n"
       " \n\n"
       " Mfront law expects : \n"
       << endl;

       for( int i=0; i<b.mps.size(); i++)
         cout << "  Material property :   "<<  b.mps[i].name << " of type " <<  b.mps[i].type << endl;

       cout <<"===================================================================\n" << endl;

       exit(1);
    }
    else {
        istringstream iss( *mfrontPropertyNames);
        string s; int j =0;
        while ( getline( iss, s, ' ' ) )
        {
          setMaterialProperty(d.s1,s.c_str(),mfrontPropertyValues->operator[](j));
          j++;
        }

        if(j != b.mps.size())
        {
          cout <<
            "===================================================================\n"
            " \033[1;31m ** ERROR DETECTED  ** \033[0m\n"
            "===================================================================\n"
            " mfrontPropertyNames are wrong. Please consider \n"
            " filling in  \033[1;34mmfrontPropertyNames\033[0m argument\n"
            " correctly in the in PsdMfrontHandler(...) function. For example,\n"
            "   \033[1;34m PsdMfrontHandler( ..., mfrontPropertyNames = \"YoungModulus PoissonRatio\", .... )\033[0m\n"
            " \n                                                                \n"
            " Mfront law expects :                                              \n" << endl;

          for (int i=0; i<b.mps.size(); i++)
            cout << "  Material property names :   " <<  b.mps[i].name << endl;

          cout << "===================================================================\n" << endl;

          exit(1);
        }

    }

    if( verbosity ){
       cout << " \033[1;36m Message MFront :: Following Material Properties Detected :: \033[0m " << endl;
       for (int i=0; i<b.mps.size(); i++)
          {
            double* ygs = getMaterialProperty(d.s1, b.mps[i].name);
            cout <<" \033[1;36m    " <<  b.mps[i].name << "  =  \033[0m" <<  *ygs << endl;
           }
        cout  << " \n" << endl;
    }

  }

  //------------------------------------------------
  // Assigning External state variables for MGIS
  //-----------------------------------------------

  if( b.esvs.size() > 0 && mfrontExternalStateVariableVector == NULL && mfrontExternalStateVariableValues != NULL){


    if( mfrontExternalStateVariableNames  == NULL || mfrontExternalStateVariableValues == NULL ||
        mfrontExternalStateVariableValues->n < b.esvs.size() || mfrontExternalStateVariableValues->n > b.esvs.size() ){
       cout <<
       "===================================================================\n"
       " \033[1;31m ** ERROR DETECTED  ** \033[0m\n"
       "===================================================================\n"
       " mfrontExternalStateVariableNames and/or  mfrontExternalStateVariableValues wrong. Please consider \n"
       " filling in  \033[1;34mmfrontExternalStateVariableNames\033[0m   and   \033[1;34mmfrontExternalStateVariableValues\033[0m  arguments\n"
       " correctly in the in PsdMfrontHandler(...) function. For example,\n"
       "   \033[1;34m PsdMfrontHandler( ..., mfrontExternalStateVariableNames = \"Temperature\", 34mmfrontExternalStateVariableValues = [273.1], .... )\033[0m\n"
       " \n\n"
       " Mfront law expects : \n"
       << endl;

       for( int i=0; i<b.esvs.size(); i++)
         cout << "  External state variable :   "<<  b.esvs[i].name << " of type " <<  MaterialPropertyKind(b.esvs[i].type) << endl;

       cout <<"===================================================================\n" << endl;

       exit(1);
    }
    else {
        istringstream iss( *mfrontExternalStateVariableNames);
        string s; int j =0;
        while ( getline( iss, s, ' ' ) )
        {
          setExternalStateVariable(d.s1,s.c_str(),mfrontExternalStateVariableValues->operator[](j));
          j++;
        }

        if(j != b.esvs.size())
        {
          cout <<
            "===================================================================\n"
            " \033[1;31m ** ERROR DETECTED  ** \033[0m\n"
            "===================================================================\n"
            " mfrontExternalStateVariableNames are wrong. Please consider \n"
            " filling in  \033[1;34mmfrontExternalStateVariableNames\033[0m argument\n"
            " correctly in the in PsdMfrontHandler(...) function. For example,\n"
            "   \033[1;34m PsdMfrontHandler( ..., mfrontExternalStateVariableNames = \"Temperature\", .... )\033[0m\n"
            " \n                                                                \n"
            " Mfront law expects :                                              \n" << endl;

          for (int i=0; i<b.esvs.size(); i++)
            cout << "  External state names :   " <<  b.esvs[i].name << endl;

          cout << "===================================================================\n" << endl;

          exit(1);
        }

    }

    if( verbosity ){
       cout << " \033[1;36m Message MFront :: Following External state variables Detected :: \033[0m " << endl;
       for (int i=0; i<b.esvs.size(); i++)
          {
            double* ygs = getExternalStateVariable(d.s1, b.esvs[i].name);
            cout <<" \033[1;36m    " <<  b.esvs[i].name << "  =  \033[0m" <<  *ygs << endl;
           }
        cout  << " \n" << endl;
    }

  }



  // --------------------------------------------------------------- //
  // ---------------------- 2D PROBLEM ----------------------------- //
  // --------------------------------------------------------------- //

    if(*mfrontBehaviourHypothesis=="GENERALISEDPLANESTRAIN" || *mfrontBehaviourHypothesis=="PLANESTRAIN")
    {
        if ( mfrontMaterialTensor != NULL && mfrontStrainTensor == NULL )
        {
          if(verbosity)
            cout << " \033[1;36m Message MFront :: Calculating Material Tensor   \033[0m \n"
                 << " \033[1;36m                :: Performing Mfront Integration \033[0m \n"
                 << endl;

          int totalCells =  mfrontMaterialTensor->n / 18;
          int indexMtTensor ;
          for (int i = 0; i < totalCells; i++)
          {
            indexMtTensor  = i*18;                 // 6 - components of sym. material tensor and 3 quadrature points per element 3*6= 18
            d.K[0] = 1.;                           // Request MFront for updating the stiffness
            integrate(v, b);                       // Perform integration
            MacroGetStifness2D(indexMtTensor);     // See file typedefinitions.hxx gets Material tensor 6 components for 2D
          }
        }


        if ( mfrontMaterialTensor == NULL && mfrontStrainTensor != NULL  && mfrontStateVariable == NULL  )
        {
          if(verbosity)
            cout << " \033[1;36m Message MFront :: Calculating Stress Tensor     \033[0m \n"
                 << " \033[1;36m                :: Performing Mfront Integration \033[0m \n"
                 << endl;

          int totalCells =  mfrontStrainTensor->n / 9;
          int indexEx;

          for (int i = 0; i < totalCells; i++)
          {
            indexEx  = i*9;

            MacroSetGradient2D(indexEx);  // See file typedefinitions.hxx sets (E11, E22, E33, E12)
            integrate(v, b);
            MacroGetSress2D(indexEx);     // See file typedefinitions.hxx gets (S11, S22, S12)

          }
        }


        if ( mfrontMaterialTensor == NULL && mfrontStrainTensor != NULL  && mfrontStateVariable != NULL )
        {
          if(verbosity)
            cout << " \033[1;36m Message MFront :: Calculating Stress Tensor         \033[0m \n"
                 << " \033[1;36m                :: Updating Internal state variables \033[0m \n"
                 << " \033[1;36m                :: Performing Mfront Integration     \033[0m \n"
                 << endl;

          int totalCells =  mfrontStrainTensor->n / 9;
          int totalIsv = componentsIsvs;
          int indexIsv = totalIsv * 3;
          int indexEx;

          for (int i = 0; i < totalCells; i++){
            indexEx  = i*9;               // 3 - components of sym. strain/stress tensor and 3 quadrature points per element 3*3= 9
            MacroSetGradient2D(indexEx);  // See file typedefinitions.hxx sets (E11, E22, E33, E12)
            integrate(v, b);              // Perform integration
            MacroGetSress2D(indexEx);     // See file typedefinitions.hxx gets (S11, S22, S12)

            for(int jj = 0; jj < totalIsv; jj++){
              mfrontStateVariable->operator[](i*indexIsv+(3*jj))       = d.s1.internal_state_variables[jj];
              mfrontStateVariable->operator[](i*indexIsv+(3*jj+1))     = d.s1.internal_state_variables[jj];
              mfrontStateVariable->operator[](i*indexIsv+(3*jj+2))     = d.s1.internal_state_variables[jj];
            }
          }
        }

        if ( mfrontMaterialTensor != NULL && mfrontStrainTensor != NULL   && mfrontStateVariable == NULL  )
        {
          if(verbosity)
            cout << " \033[1;36m Message MFront :: Calculating Material Tensor   \033[0m \n"
                 << " \033[1;36m                :: Calculating Stress Tensor     \033[0m \n"
                 << " \033[1;36m                :: Performing Mfront Integration \033[0m \n"
                 << endl;

          int totalCells =  mfrontMaterialTensor->n / 18;
          int indexEx       ;
          int indexMtTensor ;

          for (int i = 0; i < totalCells; i++){
            indexEx  = i*9;                       // 3 - components of sym. strain/stress tensor and 3 quadrature points per element 3*3= 9
            MacroSetGradient2D(indexEx);          // See file typedefinitions.hxx sets (E11, E22, E33, E12)
            d.K[0] = 1.;                          // Request MFront for updating the stiffness
            integrate(v, b);                      // Perform integration
            MacroGetSress2D(indexEx);             // See file typedefinitions.hxx gets (S11, S22, S12)
            indexMtTensor  = i*18;                // 6 - components of sym. material tensor and 3 quadrature points per element 3*6= 18
            MacroGetStifness2D(indexMtTensor);    // See file typedefinitions.hxx gets Material tensor 6 components for 2D
          }
        }

        if ( mfrontMaterialTensor != NULL && mfrontStrainTensor != NULL   && mfrontStateVariable != NULL  )
        {
          if(verbosity)
            cout << " \033[1;36m Message MFront :: Calculating Material Tensor       \033[0m \n"
                 << " \033[1;36m                :: Updating Internal state variables \033[0m \n"
                 << " \033[1;36m                :: Calculating Stress Tensor         \033[0m \n"
                 << " \033[1;36m                :: Performing Mfront Integration     \033[0m \n"
                 << endl;

          int totalCells =  mfrontMaterialTensor->n / 18;
          int totalIsv = componentsIsvs;
          int indexIsv = totalIsv * 3;
          int indexEx       ;
          int indexMtTensor ;

          for (int i = 0; i < totalCells; i++)
          {
            
            for(int jj = 0; jj < totalIsv; jj++){
             d.s0.internal_state_variables[jj] =  mfrontStateVariable->operator[](i*indexIsv+(3*jj)) ;
            }
            

            indexEx  = i*9;                        // 3 - components of sym. strain/stress tensor and 3 quadrature points per element 3*3= 9
            MacroSetGradient2D(indexEx);           // See file typedefinitions.hxx sets (E11, E22, E33, E12)
            d.K[0] = 1.;                           // Request MFront for updating the stiffness
            integrate(v, b);                       // Perform integration
            MacroGetSress2D(indexEx);              // See file typedefinitions.hxx gets (S11, S22, S12)
            indexMtTensor  = i*18;                 // 6 - components of sym. material tensor and 3 quadrature points per element 3*6= 18
            MacroGetStifness2D(indexMtTensor);     // See file typedefinitions.hxx gets Material tensor 6 components for 2D
            
            for(int jj = 0; jj < totalIsv; jj++){
              mfrontStateVariable->operator[](i*indexIsv+(3*jj))       = d.s1.internal_state_variables[jj];
              mfrontStateVariable->operator[](i*indexIsv+(3*jj+1))     = d.s1.internal_state_variables[jj];
              mfrontStateVariable->operator[](i*indexIsv+(3*jj+2))     = d.s1.internal_state_variables[jj];
            }
          }
        }
        
        if ( mfrontMaterialTensor != NULL && mfrontStrainTensor != NULL   && mfrontStateVariable != NULL &&  mfrontExternalStateVariableVector != NULL )
        {
          if(verbosity)
            cout << " \033[1;36m Message MFront :: Calculating Material Tensor       \033[0m \n"
                 << " \033[1;36m                :: Updating Internal state variables \033[0m \n"
                 << " \033[1;36m                :: Calculating Stress Tensor         \033[0m \n"
                 << " \033[1;36m                :: Performing Mfront Integration     \033[0m \n"
                 << endl;

          int totalCells =  mfrontMaterialTensor->n / 18;
          int totalIsv = componentsIsvs;
          int indexIsv = totalIsv * 3;
          int indexExtVar = 3*b.esvs.size(); //Number of external state variables and 3 quadrature points
          int indexEx       ;
          int indexMtTensor ;

          for (int i = 0; i < totalCells; i++)
          {
            
            for(int jj = 0; jj < totalIsv; jj++){
             d.s0.internal_state_variables[jj] =  mfrontStateVariable->operator[](i*indexIsv+(3*jj)) ;
            }
            
            //Set external state variable field
            //////
            istringstream iss( *mfrontExternalStateVariableNames);
            string s;
            int ii =0;
            while ( getline( iss, s, ' ' ) )
            {
             setExternalStateVariable(d.s0,s.c_str(),mfrontExternalStateVariableValues->operator[](i*indexExtVar+(3*ii)));
             ii++;
            }
            //////
            
            if(ii != b.esvs.size())
            {
          	cout <<
            	"===================================================================\n"
            	" \033[1;31m ** ERROR DETECTED  ** \033[0m\n"
            	"===================================================================\n"
            	" mfrontExternalStateVariableNames or mfrontExternalStateVariableVector are wrong. Please consider \n"
            	" filling in  \033[1;34mmfrontExternalStateVariableNames\033[0m argument\n"
            	" correctly in the in PsdMfrontHandler(...) function. For example,\n"
            	"   \033[1;34m PsdMfrontHandler( ..., mfrontExternalStateVariableNames = \"Temperature\", 34mmfrontExternalStateVariableVector = ExT[], .... )\033[0m\n"
      		" \n\n"
            	" \n                                                                \n"
            	" Mfront law expects :                                              \n" << endl;

          	for (int k=0; k<b.esvs.size(); k++)
            		cout << "  External state variable :   "<<  b.esvs[k].name << " of type " <<  MaterialPropertyKind(b.esvs[k].type) << endl;
            		cout << "  mfrontExternalStateVariableVector needs to be filled with fields.   "  << endl;

          		cout << "===================================================================\n" << endl;

            exit(1);
            }

            indexEx  = i*9;                        // 3 - components of sym. strain/stress tensor and 3 quadrature points per element 3*3= 9
            MacroSetGradient2D(indexEx);           // See file typedefinitions.hxx sets (E11, E22, E33, E12)
            d.K[0] = 1.;                           // Request MFront for updating the stiffness
            integrate(v, b);                       // Perform integration
            MacroGetSress2D(indexEx);              // See file typedefinitions.hxx gets (S11, S22, S12)
            indexMtTensor  = i*18;                 // 6 - components of sym. material tensor and 3 quadrature points per element 3*6= 18
            MacroGetStifness2D(indexMtTensor);     // See file typedefinitions.hxx gets Material tensor 6 components for 2D
            
            for(int jj = 0; jj < totalIsv; jj++){
              mfrontStateVariable->operator[](i*indexIsv+(3*jj))       = d.s1.internal_state_variables[jj];
              mfrontStateVariable->operator[](i*indexIsv+(3*jj+1))     = d.s1.internal_state_variables[jj];
              mfrontStateVariable->operator[](i*indexIsv+(3*jj+2))     = d.s1.internal_state_variables[jj];
            }
          }
        }

    }


    // --------------------------------------------------------------- //
    // ---------------------- 3D PROBLEM ----------------------------- //
    // --------------------------------------------------------------- //


    if(*mfrontBehaviourHypothesis=="TRIDIMENSIONAL")
    {
        if ( mfrontMaterialTensor != NULL && mfrontStrainTensor == NULL   && mfrontStateVariable == NULL  )
        {
          if (verbosity)
            cout << " \033[1;36m Message MFront :: Calculating Material Tensor   \033[0m \n"
                 << " \033[1;36m                :: Performing Mfront Integration \033[0m \n"
                 << endl;

          int totalCells =  mfrontMaterialTensor->n / 84;
          int indexMtTensor ;
//          cout << "THREADS MAX "<< omp_get_max_threads() <<endl;
//          omp_set_num_threads(omp_get_max_threads());
          
          for (int i = 0; i < totalCells; i++)
          {
            indexMtTensor  = i*84;  // 21 - components of sym. material tensor and 4 quadrature points per element 4*6= 84
            d.K[0] = 1.;
            integrate(v, b);
	    MacroGetStifness3D(indexMtTensor);

          }
        }


        if ( mfrontMaterialTensor != NULL && mfrontStrainTensor == NULL   && mfrontStateVariable != NULL  )
        {
          if (verbosity)
            cout << " \033[1;36m Message MFront :: Calculating Material Tensor      \033[0m \n"
                 << " \033[1;36m                :: Updating internal state variable \033[0m \n"
                 << " \033[1;36m                :: Performing Mfront Integration    \033[0m \n"
                 << endl;

          int totalCells =  mfrontMaterialTensor->n / 84;
          int totalIsv = componentsIsvs;
          int indexIsv = totalIsv * 3;
          int indexMtTensor ;
          for (int i = 0; i < totalCells; i++)
          {
            indexMtTensor  = i*84;  // 21 - components of sym. material tensor and 4 quadrature points per element 4*6= 84
            d.K[0] = 1.;
            integrate(v, b);
	    MacroGetStifness3D(indexMtTensor);

           for(int jj = 0; jj < totalIsv; jj++){
             mfrontStateVariable->operator[](i*indexIsv+(3*jj))       = d.s1.internal_state_variables[jj];
             mfrontStateVariable->operator[](i*indexIsv+(3*jj+1))     = d.s1.internal_state_variables[jj];
             mfrontStateVariable->operator[](i*indexIsv+(3*jj+2))     = d.s1.internal_state_variables[jj];
           }

          }
        }


        if ( mfrontMaterialTensor == NULL && mfrontStrainTensor != NULL   && mfrontStateVariable == NULL   )
        {
          if (verbosity)
          {
            cout << " \033[1;36m Message MFront :: Calculating Stress Tensor   \033[0m   \n"
              << " \033[1;36m                :: Performing Mfront Integration \033[0m \n"
              << endl;
          }

          int totalCells =  mfrontStrainTensor->n / 24;
          int indexEx;

          for (int i = 0; i < totalCells; i++)
          {
            indexEx  = i*24;
 	    MacroSetGradient3D(indexEx);
            integrate(v, b);
            MacroGetSress3D(indexEx);
          }
        }

        if ( mfrontMaterialTensor == NULL && mfrontStrainTensor != NULL   && mfrontStateVariable != NULL  && mfrontPreviousStrainTensor ==  NULL    )
        {
          if(verbosity)
            cout << " \033[1;36m Message MFront :: Calculating Stress Tensor        \033[0m \n"
                 << " \033[1;36m                :: Updating internal state variable \033[0m \n"
                 << " \033[1;36m                :: Performing Mfront Integration    \033[0m \n"
                 << endl;

          int totalCells =  mfrontStrainTensor->n / 24;
          int totalIsv = componentsIsvs;
          int indexIsv = totalIsv * 4;
          int indexEx;
          
          for (int i = 0; i < totalCells; i++)
          {
          
                     
            indexEx  = i*24         ;  
 	    MacroSetGradient3D(indexEx);
            integrate(v, b); 
            MacroGetSress3D(indexEx);

           for(int jj = 0; jj <  totalIsv; jj++){
             mfrontStateVariable->operator[](i*indexIsv+(4*jj))       = d.s1.internal_state_variables[jj];
             mfrontStateVariable->operator[](i*indexIsv+(4*jj+1))     = d.s1.internal_state_variables[jj];
             mfrontStateVariable->operator[](i*indexIsv+(4*jj+2))     = d.s1.internal_state_variables[jj];
             mfrontStateVariable->operator[](i*indexIsv+(4*jj+3))     = d.s1.internal_state_variables[jj];             
           }

          }
        }

        if ( mfrontMaterialTensor == NULL && mfrontStrainTensor != NULL   && mfrontStateVariable != NULL  && mfrontPreviousStrainTensor !=  NULL )
        {
          if(verbosity)
            cout << " \033[1;36m Message MFront :: Calculating Stress Tensor        \033[0m \n"
                 << " \033[1;36m                :: Updating internal state variable \033[0m \n"
                 << " \033[1;36m                :: Performing Mfront Integration    \033[0m \n"
                 << endl;

          int totalCells =  mfrontStrainTensor->n / 24;
          int totalIsv = componentsIsvs;
          int indexIsv = totalIsv * 4;
          int indexEx;
          
          for (int i = 0; i < totalCells; i++)
          {
          
                     
            indexEx  = i*24         ;
 	  
            for(int jj = 0; jj < totalIsv; jj++){
             d.s0.internal_state_variables[jj] =  mfrontStateVariable->operator[](i*indexIsv+(4*jj)) ;
           }
           	  
 	    MacroSetGradient3D(indexEx);
 	    MacroGetInitialSress3D(indexEx);
 	    MacroSetInitialGradient3D(indexEx);
            integrate(v, b); 
            MacroGetSress3D(indexEx);

           for(int jj = 0; jj <  totalIsv; jj++){
             mfrontStateVariable->operator[](i*indexIsv+(4*jj))       = d.s1.internal_state_variables[jj];
             mfrontStateVariable->operator[](i*indexIsv+(4*jj+1))     = d.s1.internal_state_variables[jj];
             mfrontStateVariable->operator[](i*indexIsv+(4*jj+2))     = d.s1.internal_state_variables[jj];
             mfrontStateVariable->operator[](i*indexIsv+(4*jj+3))     = d.s1.internal_state_variables[jj];             
           }

          }
        }

        if ( mfrontMaterialTensor != NULL && mfrontStrainTensor != NULL   && mfrontStateVariable == NULL    )
        {
          if(verbosity)
            cout << " \033[1;36m Message MFront :: Calculating Material Tensor   \033[0m \n"
                 << " \033[1;36m                :: Calculating Stress Tensor     \033[0m \n"
                 << " \033[1;36m                :: Performing Mfront Integration \033[0m \n"
                 << endl;

          int totalCells =  mfrontMaterialTensor->n / 84;
          int indexEx       ;
          int indexMtTensor ;

          for (int i = 0; i < totalCells; i++)
          {
            indexEx  = i*24         ;  // 6 - components of sym. strain/stress tensor and 4 quadrature points per element 6*4= 24
 	    MacroSetGradient3D(indexEx);
            d.K[0] = 1.;
            integrate(v, b);
            MacroGetSress3D(indexEx);
            indexMtTensor  = i*84;
	    MacroGetStifness3D(indexMtTensor);
          }
        }

        if ( mfrontMaterialTensor != NULL && mfrontStrainTensor != NULL   && mfrontStateVariable != NULL   && mfrontPreviousStrainTensor ==  NULL        )
        {
         if(verbosity)
            cout << " \033[1;36m Message MFront :: Calculating Material Tensor      \033[0m \n"
                 << " \033[1;36m                :: Calculating Stress Tensor        \033[0m \n"
                 << " \033[1;36m                :: Updating internal state variable \033[0m \n"
                 << " \033[1;36m                :: Performing Mfront Integration    \033[0m \n"
                 << endl;

          int totalCells =  mfrontMaterialTensor->n / 84;
          int totalIsv = componentsIsvs;
          int indexIsv = totalIsv * 4;
          int indexEx       ;
          int indexMtTensor ;

          for (int i = 0; i < totalCells; i++)
          {

            indexEx  = i*24         ;          // 6 - components of sym. strain/stress tensor and 4 quadrature points per element 6*4= 24
 	    MacroSetGradient3D(indexEx);
            d.K[0] = 1.;
            integrate(v, b);
            MacroGetSress3D(indexEx);
            indexMtTensor  = i*84;
	    MacroGetStifness3D(indexMtTensor);

           for(int jj = 0; jj <  totalIsv; jj++){
             mfrontStateVariable->operator[](i*indexIsv+(4*jj))       = d.s1.internal_state_variables[jj];
             mfrontStateVariable->operator[](i*indexIsv+(4*jj+1))     = d.s1.internal_state_variables[jj];
             mfrontStateVariable->operator[](i*indexIsv+(4*jj+2))     = d.s1.internal_state_variables[jj];
             mfrontStateVariable->operator[](i*indexIsv+(4*jj+3))     = d.s1.internal_state_variables[jj];             
           }

          }
        }

        if ( mfrontMaterialTensor != NULL && mfrontStrainTensor != NULL   && mfrontStateVariable != NULL   && mfrontPreviousStrainTensor !=  NULL        )
        {
         if(verbosity)
            cout << " \033[1;36m Message MFront :: Calculating Material Tensor      \033[0m \n"
                 << " \033[1;36m                :: Calculating Stress Tensor        \033[0m \n"
                 << " \033[1;36m                :: Updating internal state variable \033[0m \n"
                 << " \033[1;36m                :: Performing Mfront Integration    \033[0m \n"
                 << endl;

          int totalCells =  mfrontMaterialTensor->n / 84;
          int totalIsv = componentsIsvs;
          int indexIsv = totalIsv * 4;
          int indexEx       ;
          int indexMtTensor ;
          

          for (int i = 0; i < totalCells; i++)
          {

            indexEx  = i*24         ;
 	  
            for(int jj = 0; jj < totalIsv; jj++){
             d.s0.internal_state_variables[jj] =  mfrontStateVariable->operator[](i*indexIsv+(4*jj)) ;
           }
           	  
 	    MacroSetGradient3D(indexEx);
 	    MacroGetInitialSress3D(indexEx);
 	    MacroSetInitialGradient3D(indexEx);
            d.K[0] = 1.; 	    
            integrate(v, b); 
            MacroGetSress3D(indexEx);
            indexMtTensor  = i*84;
	    MacroGetStifness3D(indexMtTensor);

           for(int jj = 0; jj <  totalIsv; jj++){
             mfrontStateVariable->operator[](i*indexIsv+(4*jj))       = d.s1.internal_state_variables[jj];
             mfrontStateVariable->operator[](i*indexIsv+(4*jj+1))     = d.s1.internal_state_variables[jj];
             mfrontStateVariable->operator[](i*indexIsv+(4*jj+2))     = d.s1.internal_state_variables[jj];
             mfrontStateVariable->operator[](i*indexIsv+(4*jj+3))     = d.s1.internal_state_variables[jj];             
           }

          }
        }

        if ( mfrontMaterialTensor != NULL && mfrontStrainTensor != NULL   && mfrontStateVariable != NULL   && mfrontPreviousStrainTensor !=  NULL  && mfrontExternalStateVariableVector != NULL)
        {
         if(verbosity)
            cout << " \033[1;36m Message MFront :: Calculating Material Tensor      \033[0m \n"
                 << " \033[1;36m                :: Calculating Stress Tensor        \033[0m \n"
                 << " \033[1;36m                :: Updating internal state variable \033[0m \n"
                 << " \033[1;36m                :: Performing Mfront Integration    \033[0m \n"
                 << endl;

          int totalCells =  mfrontMaterialTensor->n / 84;
          int totalIsv = componentsIsvs;
          int indexIsv = totalIsv * 4;
          int indexExtVar = 4*b.esvs.size(); //Number of external state variables and 4 quadrature points
          int indexEx       ;
          int indexMtTensor ;
          

          for (int i = 0; i < totalCells; i++)
          {

            indexEx  = i*24         ;
 	  
            for(int jj = 0; jj < totalIsv; jj++){
             d.s0.internal_state_variables[jj] =  mfrontStateVariable->operator[](i*indexIsv+(4*jj)) ;
            }

            //Set external state variable field
            //////
            istringstream iss( *mfrontExternalStateVariableNames);
            string s;
            int ii =0;
            while ( getline( iss, s, ' ' ) )
            {
             setExternalStateVariable(d.s0,s.c_str(),mfrontExternalStateVariableValues->operator[](i*indexExtVar+(4*ii)));
             ii++;
            }
            //////
            
            if(ii != b.esvs.size())
            {
          	cout <<
            	"===================================================================\n"
            	" \033[1;31m ** ERROR DETECTED  ** \033[0m\n"
            	"===================================================================\n"
            	" mfrontExternalStateVariableNames or mfrontExternalStateVariableVector are wrong. Please consider \n"
            	" filling in  \033[1;34mmfrontExternalStateVariableNames\033[0m argument\n"
            	" correctly in the in PsdMfrontHandler(...) function. For example,\n"
            	"   \033[1;34m PsdMfrontHandler( ..., mfrontExternalStateVariableNames = \"Temperature\", 34mmfrontExternalStateVariableVector = ExT[], .... )\033[0m\n"
      		" \n\n"
            	" \n                                                                \n"
            	" Mfront law expects :                                              \n" << endl;

          	for (int k=0; k<b.esvs.size(); k++)
            		cout << "  External state variable :   "<<  b.esvs[k].name << " of type " <<  MaterialPropertyKind(b.esvs[k].type) << endl;
            		cout << "  mfrontExternalStateVariableVector needs to be filled with fields.   "  << endl;

          		cout << "===================================================================\n" << endl;

            exit(1);
            }
           	  
 	    MacroSetGradient3D(indexEx);
            MacroGetInitialSress3D(indexEx);
            MacroSetInitialGradient3D(indexEx);
            d.K[0] = 1.; 	    
            integrate(v, b); 
            MacroGetSress3D(indexEx);
            indexMtTensor  = i*84;
            MacroGetStifness3D(indexMtTensor);

           for(int jj = 0; jj <  totalIsv; jj++){
             mfrontStateVariable->operator[](i*indexIsv+(4*jj))       = d.s1.internal_state_variables[jj];
             mfrontStateVariable->operator[](i*indexIsv+(4*jj+1))     = d.s1.internal_state_variables[jj];
             mfrontStateVariable->operator[](i*indexIsv+(4*jj+2))     = d.s1.internal_state_variables[jj];
             mfrontStateVariable->operator[](i*indexIsv+(4*jj+3))     = d.s1.internal_state_variables[jj];             
           }

          }
        }
        
    }
    //update(d);
}
  return 0L;
}
