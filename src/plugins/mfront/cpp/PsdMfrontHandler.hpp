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

    static const int n_name_param = 6                 ;
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
  {"mfrontBehaviourHypothesis" , &typeid(std::string*)},
  {"mfrontPropertyNames"       , &typeid(std::string*)},
  {"mfrontPropertyValues"      , &typeid(KN<K>*)      },
  {"mfrontMaterialTensor"      , &typeid(KN<K>*)      },
  {"mfrontStrainTensor"        , &typeid(KN<K>*)      },
  {"mfrontStressTensor"        , &typeid(KN<K>*)      }
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

  string* mfrontBehaviourHypothesis  = nargs[0] ? GetAny<std::string*>((*nargs[0])(stack)) : NULL;
  string* mfrontPropertyNames        = nargs[1] ? GetAny<std::string*>((*nargs[1])(stack)) : NULL;
  KN<K>* mfrontPropertyValues        = nargs[2] ? GetAny<KN<K>*>((*nargs[2])(stack))       : NULL;
  KN<K>* mfrontMaterialTensor        = nargs[3] ? GetAny<KN<K>*>((*nargs[3])(stack))       : NULL;
  KN<K>* mfrontStrainTensor          = nargs[4] ? GetAny<KN<K>*>((*nargs[4])(stack))       : NULL;
  KN<K>* mfrontStressTensor          = nargs[5] ? GetAny<KN<K>*>((*nargs[5])(stack))       : NULL;


  if( mfrontBehaviourName!=NULL && verbosity)
  {
    cout << " \n"
      " \033[1;36m Message MFront mfrontBehaviourName       :: \033[0m " << *mfrontBehaviourName
      << " \n" << endl;
  }

  if( mfrontBehaviourHypothesis!=NULL && verbosity)
  {
    cout << " \n"
      " \033[1;36m Message MFront mfrontBehaviourHypothesis :: \033[0m " << *mfrontBehaviourHypothesis  << "\n"
      << " \n" << endl;
  }

  if( mfrontBehaviourHypothesis != NULL &&
      ( *mfrontBehaviourHypothesis != "GENERALISEDPLANESTRAIN" &&
        *mfrontBehaviourHypothesis != "PLANESTRAIN"            &&
        *mfrontBehaviourHypothesis != "TRIDIMENSIONAL"           )
    )
  {
    cout <<"===================================================================\n"
      " \033[1;31m ** ERROR DETECTED  ** \033[0m\n"
      "===================================================================\n"
      " WRONG hypothesis was provided by user. Please consider \n"
      " filling in the \033[1;34m mfrontBehaviourHypothesis \033[0m argument \n"
      " in PsdMfrontHandler(...) function. Example   \n"
      "   \033[1;34m PsdMfrontHandler( mfrontBehaviourHypothesis = \"GENERALISEDPLANESTRAIN\", .... )\033[0m\n"
      "   \033[1;34m PsdMfrontHandler( mfrontBehaviourHypothesis = \"PLANESTRAIN\", .... )\033[0m\n"
      "   \033[1;34m PsdMfrontHandler( mfrontBehaviourHypothesis = \"TRIDIMENSIONAL\", .... )\033[0m\n"
      "===================================================================\n" << endl;

    exit(1);
  }
  /**/
  if( mfrontBehaviourHypothesis!=NULL)
  {
    if(*mfrontBehaviourHypothesis=="GENERALISEDPLANESTRAIN" || *mfrontBehaviourHypothesis=="PLANESTRAIN")
    {
      if(verbosity)
      {
        cout << " \n"
          " \033[1;36m Message MFront :: Creating Hypothesis :: \033[0m " << *mfrontBehaviourHypothesis  << "\n"
          " \033[1;36m                :: Loading  Behaviour  :: \033[0m " << *mfrontBehaviourName        << "\n"
          " \033[1;36m                :: Creating BehaviourData \033[0m "                                << "\n"
          " \033[1;36m                :: Creating BehaviourDataView \033[0m "                            << "\n"
          << " \n" << endl;
      }

      constexpr const auto h = Hypothesis::GENERALISEDPLANESTRAIN;
      const auto b = load("/usr/lib/libBehaviour.so", *mfrontBehaviourName , h);

      auto d = BehaviourData{b};
      auto v = make_view(d);

      if( b.mps.size() > 0
          && ( mfrontPropertyNames  == NULL || mfrontPropertyValues == NULL || mfrontPropertyValues->n < b.mps.size() )
        )
      {
        cout <<
          "===================================================================\n"
          " \033[1;31m ** ERROR DETECTED  ** \033[0m\n"
          "===================================================================\n"
          " mfrontPropertyNames and/or  mfrontPropertyValues wrong. Please consider \n"
          " filling in  \033[1;34mmfrontPropertyNames\033[0m   and   \033[1;34mmfrontPropertyValues\033[0m  arguments\n"
          " correctly in the in PsdMfrontHandler(...) function. For example,\n"
          "   \033[1;34m PsdMfrontHandler( ..., mfrontPropertyNames = \"YoungModulus PoissonRatio\", mfrontPropertyValues = [1e9, 0.3], .... )\033[0m\n"
          " \n\n"
          " Mfront law expects : \n"
          << endl;

        for (int i=0; i<b.mps.size(); i++)
          std::cout << "  Material property :   " <<  b.mps[i].name
            << " of type " <<  b.mps[i].type <<
            std::endl;

        cout <<"===================================================================\n" << endl;

        exit(1);
      }
      else
      {
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
        else
        {
          if (verbosity)
          {
            cout << " \033[1;36m Message MFront :: Following Material Properties Detected :: \033[0m " << endl;
            for (int i=0; i<b.mps.size(); i++)
            {
              double* ygs = getMaterialProperty(d.s1, b.mps[i].name);
              cout <<" \033[1;36m    " <<  b.mps[i].name << "  =  \033[0m" <<  *ygs << endl;
            }
            cout  << " \n" << endl;
          }
        }

        if ( mfrontMaterialTensor != NULL && mfrontStrainTensor == NULL )
        {
          if (verbosity)
          {
            cout << " \033[1;36m Message MFront :: Calculating Material Tensor   \033[0m \n"
              << " \033[1;36m                :: Performing Mfront Integration \033[0m \n"
              << endl;
          }

          int totalGaussPoints =  mfrontMaterialTensor->n / 18;
          int indexMtTensor ;
          for (int i = 0; i < totalGaussPoints; i++)
          {
            indexMtTensor  = i*18;  // 6 - components of sym. material tensor and 3 quadrature points per element 3*6= 18

            d.K[0] = 1.;
            integrate(v, b);

            mfrontMaterialTensor->operator[](indexMtTensor)    = d.K[0];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +1) = d.K[0];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +2) = d.K[0];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor+3) = d.K[1];  //  Mt_12 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+4) = d.K[1];  //  Mt_12 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+5) = d.K[1];  //  Mt_12 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor+6) = d.K[3];  //  Mt_13 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+7) = d.K[3];  //  Mt_13 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+8) = d.K[3];  //  Mt_13 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor+9)  = d.K[5];  //  Mt_22 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+10) = d.K[5];  //  Mt_22 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+11) = d.K[5];  //  Mt_22 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor+12) = d.K[7];  //  Mt_23 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+13) = d.K[7];  //  Mt_23 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+14) = d.K[7];  //  Mt_23 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor+15) = d.K[15]/*2*/;  //  Mt_33 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+16) = d.K[15]/*2*/;  //  Mt_33 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+17) = d.K[15]/*2*/;  //  Mt_33 Quadrature point 1 (3 Quad points per tria)

          }
        }

        if ( mfrontMaterialTensor == NULL && mfrontStrainTensor != NULL )
        {
          if (verbosity)
          {
            cout << " \033[1;36m Message MFront :: Calculating Stress Tensor   \033[0m   \n"
              << " \033[1;36m                :: Performing Mfront Integration \033[0m \n"
              << endl;
          }

          int totalGaussPoints =  mfrontStrainTensor->n / 9;
          int indexEx;

          for (int i = 0; i < totalGaussPoints; i++)
          {
            indexEx  = i*9         ;

            d.s1.gradients[0] = mfrontStrainTensor->operator[](indexEx)  ;  //E11
            d.s1.gradients[1] = mfrontStrainTensor->operator[](indexEx+3);  //E22
            d.s1.gradients[2] = 0.                                       ;  //E33
            d.s1.gradients[3] = mfrontStrainTensor->operator[](indexEx+6);  //E22

            integrate(v, b);

            mfrontStressTensor->operator[](indexEx)    = d.s1.thermodynamic_forces[0]; // sig_xx
            mfrontStressTensor->operator[](indexEx+1)  = d.s1.thermodynamic_forces[0]; // sig_xx
            mfrontStressTensor->operator[](indexEx+2)  = d.s1.thermodynamic_forces[0]; // sig_xx

            mfrontStressTensor->operator[](indexEx+3)  = d.s1.thermodynamic_forces[1]; // sig_yy
            mfrontStressTensor->operator[](indexEx+4)  = d.s1.thermodynamic_forces[1]; // sig_yy
            mfrontStressTensor->operator[](indexEx+5)  = d.s1.thermodynamic_forces[1]; // sig_yy

            mfrontStressTensor->operator[](indexEx+6)  = d.s1.thermodynamic_forces[3]; // sig_xy
            mfrontStressTensor->operator[](indexEx+7)  = d.s1.thermodynamic_forces[3]; // sig_xy
            mfrontStressTensor->operator[](indexEx+8)  = d.s1.thermodynamic_forces[3]; // sig_xy

          }
        }

        if ( mfrontMaterialTensor != NULL && mfrontStrainTensor != NULL )
        {
          if (verbosity)
          {
            cout << " \033[1;36m Message MFront :: Calculating Material Tensor   \033[0m \n"
              << " \033[1;36m                :: Calculating Stress Tensor     \033[0m \n"
              << " \033[1;36m                :: Performing Mfront Integration \033[0m \n"
              << endl;
          }

          int totalGaussPoints =  mfrontMaterialTensor->n / 18;
          int indexEx       ;
          int indexMtTensor ;

          for (int i = 0; i < totalGaussPoints; i++)
          {

            indexEx  = i*9         ;  // 3 - components of sym. strain/stress tensor and 3 quadrature points per element 3*3= 9

            d.s1.gradients[0] = mfrontStrainTensor->operator[](indexEx)  ;  //E11
            d.s1.gradients[1] = mfrontStrainTensor->operator[](indexEx+3);  //E22
            d.s1.gradients[2] = 0.                                       ;  //E33
            d.s1.gradients[3] = mfrontStrainTensor->operator[](indexEx+6);  //E22

            d.K[0] = 1.;
            integrate(v, b);

            mfrontStressTensor->operator[](indexEx)    = d.s1.thermodynamic_forces[0]; // sig_xx
            mfrontStressTensor->operator[](indexEx+1)  = d.s1.thermodynamic_forces[0]; // sig_xx
            mfrontStressTensor->operator[](indexEx+2)  = d.s1.thermodynamic_forces[0]; // sig_xx

            mfrontStressTensor->operator[](indexEx+3)  = d.s1.thermodynamic_forces[1]; // sig_yy
            mfrontStressTensor->operator[](indexEx+4)  = d.s1.thermodynamic_forces[1]; // sig_yy
            mfrontStressTensor->operator[](indexEx+5)  = d.s1.thermodynamic_forces[1]; // sig_yy

            mfrontStressTensor->operator[](indexEx+6)  = d.s1.thermodynamic_forces[3]; // sig_xy
            mfrontStressTensor->operator[](indexEx+7)  = d.s1.thermodynamic_forces[3]; // sig_xy
            mfrontStressTensor->operator[](indexEx+8)  = d.s1.thermodynamic_forces[3]; // sig_xy

            indexMtTensor  = i*18;  // 6 - components of sym. material tensor and 3 quadrature points per element 3*6= 18

            mfrontMaterialTensor->operator[](indexMtTensor)    = d.K[0];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +1) = d.K[0];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +2) = d.K[0];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor+3) = d.K[1];  //  Mt_12 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+4) = d.K[1];  //  Mt_12 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+5) = d.K[1];  //  Mt_12 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor+6) = d.K[3];  //  Mt_13 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+7) = d.K[3];  //  Mt_13 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+8) = d.K[3];  //  Mt_13 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor+9)  = d.K[5];  //  Mt_22 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+10) = d.K[5];  //  Mt_22 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+11) = d.K[5];  //  Mt_22 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor+12) = d.K[7];  //  Mt_23 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+13) = d.K[7];  //  Mt_23 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+14) = d.K[7];  //  Mt_23 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor+15) = d.K[15]/*2*/;  //  Mt_33 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+16) = d.K[15]/*2*/;  //  Mt_33 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor+17) = d.K[15]/*2*/;  //  Mt_33 Quadrature point 1 (3 Quad points per tria)
          }
        }
      }

    }
    
    
    // --------------------------------------------------------------- //
    // ---------------------- 3D PROBLEM ----------------------------- //
    // --------------------------------------------------------------- //
    
        
    if(*mfrontBehaviourHypothesis=="TRIDIMENSIONAL")
    {
      if(verbosity)
      {
        cout << " \n"
          " \033[1;36m Message MFront :: Creating Hypothesis :: \033[0m " << *mfrontBehaviourHypothesis  << "\n"
          " \033[1;36m                :: Loading  Behaviour  :: \033[0m " << *mfrontBehaviourName        << "\n"
          " \033[1;36m                :: Creating BehaviourData \033[0m "                                << "\n"
          " \033[1;36m                :: Creating BehaviourDataView \033[0m "                            << "\n"
          << " \n" << endl;
      }
      
      constexpr const auto h = Hypothesis::TRIDIMENSIONAL;
      const auto b = load("/usr/lib/libBehaviour.so", *mfrontBehaviourName , h);

      auto d = BehaviourData{b};
      auto v = make_view(d);

      if( b.mps.size() > 0
          && ( mfrontPropertyNames  == NULL || mfrontPropertyValues == NULL || mfrontPropertyValues->n < b.mps.size() )
        )
      {
        cout <<
          "===================================================================\n"
          " \033[1;31m ** ERROR DETECTED  ** \033[0m\n"
          "===================================================================\n"
          " mfrontPropertyNames and/or  mfrontPropertyValues wrong. Please consider \n"
          " filling in  \033[1;34mmfrontPropertyNames\033[0m   and   \033[1;34mmfrontPropertyValues\033[0m  arguments\n"
          " correctly in the in PsdMfrontHandler(...) function. For example,\n"
          "   \033[1;34m PsdMfrontHandler( ..., mfrontPropertyNames = \"YoungModulus PoissonRatio\", mfrontPropertyValues = [1e9, 0.3], .... )\033[0m\n"
          " \n\n"
          " Mfront law expects : \n"
          << endl;

        for (int i=0; i<b.mps.size(); i++)
          std::cout << "  Material property :   " <<  b.mps[i].name
            << " of type " <<  b.mps[i].type <<
            std::endl;

        cout <<"===================================================================\n" << endl;

        exit(1);
      }
      else
      {
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
        else
        {
          if (verbosity)
          {
            cout << " \033[1;36m Message MFront :: Following Material Properties Detected :: \033[0m " << endl;
            for (int i=0; i<b.mps.size(); i++)
            {
              double* ygs = getMaterialProperty(d.s1, b.mps[i].name);
              cout <<" \033[1;36m    " <<  b.mps[i].name << "  =  \033[0m" <<  *ygs << endl;
            }
            cout  << " \n" << endl;
          }
        }

        if ( mfrontMaterialTensor != NULL && mfrontStrainTensor == NULL )
        {
          if (verbosity)
          {
            cout << " \033[1;36m Message MFront :: Calculating Material Tensor   \033[0m \n"
              << " \033[1;36m                :: Performing Mfront Integration \033[0m \n"
              << endl;
          }

          int totalGaussPoints =  mfrontMaterialTensor->n / 84;
          int indexMtTensor ;
          for (int i = 0; i < totalGaussPoints; i++)
          {
            indexMtTensor  = i*84;  // 21 - components of sym. material tensor and 4 quadrature points per element 4*6= 84

            d.K[0] = 1.;
            integrate(v, b);
            
            
            //------------ row 1 - 6 components -------------------//
  
            mfrontMaterialTensor->operator[](indexMtTensor +0 ) = d.K[0];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +1 ) = d.K[0];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +2 ) = d.K[0];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +3 ) = d.K[0];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor +4 ) = d.K[1];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +5 ) = d.K[1];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +6 ) = d.K[1];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +7 ) = d.K[1];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)                
                               
            mfrontMaterialTensor->operator[](indexMtTensor +8 ) = d.K[2];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +9) = d.K[2];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +10) = d.K[2];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +11) = d.K[2];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor +12) = d.K[3];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +13) = d.K[3];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +14) = d.K[3];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +15) = d.K[3];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor +16) = d.K[4];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +17) = d.K[4];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +18) = d.K[4];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +19) = d.K[4];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor +20) = d.K[5];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +21) = d.K[5];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +22) = d.K[5];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +23) = d.K[5];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)  
                                                   

            //------------ row 2 - 5 components -------------------//


            mfrontMaterialTensor->operator[](indexMtTensor +24) = d.K[7];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +25) = d.K[7];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +26) = d.K[7];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +27) = d.K[7];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor +28) = d.K[8];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +29) = d.K[8];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +30) = d.K[8];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +31) = d.K[8];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            
            mfrontMaterialTensor->operator[](indexMtTensor +32) = d.K[9];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +33) = d.K[9];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +34) = d.K[9];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +35) = d.K[9];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            
            mfrontMaterialTensor->operator[](indexMtTensor +36) = d.K[10];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +37) = d.K[10];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +38) = d.K[10];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +39) = d.K[10];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)                                   

            mfrontMaterialTensor->operator[](indexMtTensor +40) = d.K[11];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +41) = d.K[11];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +42) = d.K[11];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +43) = d.K[11];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            //------------ row 3 - 4 components -------------------//


            mfrontMaterialTensor->operator[](indexMtTensor +44) = d.K[14];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +45) = d.K[14];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +46) = d.K[14];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +47) = d.K[14];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            
            mfrontMaterialTensor->operator[](indexMtTensor +48) = d.K[15];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +49) = d.K[15];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +50) = d.K[15];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +51) = d.K[15];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            
            mfrontMaterialTensor->operator[](indexMtTensor +52) = d.K[16];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +53) = d.K[16];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +54) = d.K[16];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +55) = d.K[16];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            
            mfrontMaterialTensor->operator[](indexMtTensor +56) = d.K[17];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +57) = d.K[17];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +58) = d.K[17];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +59) = d.K[17];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            
            //------------ row 4 - 3 components -------------------//
                                   
            mfrontMaterialTensor->operator[](indexMtTensor +60) = d.K[21];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +61) = d.K[21];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +62) = d.K[21];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +63) = d.K[21];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor +64) = d.K[22];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +65) = d.K[22];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +66) = d.K[22];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +67) = d.K[22];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            
            mfrontMaterialTensor->operator[](indexMtTensor +68) = d.K[23];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +69) = d.K[23];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +70) = d.K[23];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +71) = d.K[23];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
                        

            //------------ row 5 - 2 components -------------------// 
            
            mfrontMaterialTensor->operator[](indexMtTensor +72) = d.K[28];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +73) = d.K[28];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +74) = d.K[28];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +75) = d.K[28];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            
            mfrontMaterialTensor->operator[](indexMtTensor +76) = d.K[29];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +77) = d.K[29];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +78) = d.K[29];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +79) = d.K[29];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            //------------ row 6 - 1 component -------------------// 

            mfrontMaterialTensor->operator[](indexMtTensor +80) = d.K[35];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +81) = d.K[35];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +82) = d.K[35];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +83) = d.K[35];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
                                                                                                                      
          }
        }

        if ( mfrontMaterialTensor == NULL && mfrontStrainTensor != NULL )
        {
          if (verbosity)
          {
            cout << " \033[1;36m Message MFront :: Calculating Stress Tensor   \033[0m   \n"
              << " \033[1;36m                :: Performing Mfront Integration \033[0m \n"
              << endl;
          }

          int totalGaussPoints =  mfrontStrainTensor->n / 24;
          int indexEx;

          for (int i = 0; i < totalGaussPoints; i++)
          {
            indexEx  = i*24         ;

            d.s1.gradients[0] = mfrontStrainTensor->operator[](indexEx)  ;  //E11
            d.s1.gradients[1] = mfrontStrainTensor->operator[](indexEx+4);  //E22
            d.s1.gradients[2] = mfrontStrainTensor->operator[](indexEx+8);  //E33
            d.s1.gradients[3] = mfrontStrainTensor->operator[](indexEx+12); //E12
            d.s1.gradients[4] = mfrontStrainTensor->operator[](indexEx+16); //E13
            d.s1.gradients[5] = mfrontStrainTensor->operator[](indexEx+20); //E23                        
            

            integrate(v, b);

            mfrontStressTensor->operator[](indexEx)    = d.s1.thermodynamic_forces[0]; // sig_xx
            mfrontStressTensor->operator[](indexEx+1)  = d.s1.thermodynamic_forces[0]; // sig_xx
            mfrontStressTensor->operator[](indexEx+2)  = d.s1.thermodynamic_forces[0]; // sig_xx
            mfrontStressTensor->operator[](indexEx+3)  = d.s1.thermodynamic_forces[0]; // sig_xx

            mfrontStressTensor->operator[](indexEx+4)  = d.s1.thermodynamic_forces[1]; // sig_yy
            mfrontStressTensor->operator[](indexEx+5)  = d.s1.thermodynamic_forces[1]; // sig_yy
            mfrontStressTensor->operator[](indexEx+6)  = d.s1.thermodynamic_forces[1]; // sig_yy
            mfrontStressTensor->operator[](indexEx+7)  = d.s1.thermodynamic_forces[1]; // sig_yy

            mfrontStressTensor->operator[](indexEx+8)  = d.s1.thermodynamic_forces[2];  // sig_zz
            mfrontStressTensor->operator[](indexEx+9)  = d.s1.thermodynamic_forces[2];  // sig_zz
            mfrontStressTensor->operator[](indexEx+10)  = d.s1.thermodynamic_forces[2]; // sig_zz
            mfrontStressTensor->operator[](indexEx+11)  = d.s1.thermodynamic_forces[2]; // sig_zz            
            
            mfrontStressTensor->operator[](indexEx+12)  = d.s1.thermodynamic_forces[3]; // sig_xy
            mfrontStressTensor->operator[](indexEx+13)  = d.s1.thermodynamic_forces[3]; // sig_xy
            mfrontStressTensor->operator[](indexEx+14)  = d.s1.thermodynamic_forces[3]; // sig_xy
            mfrontStressTensor->operator[](indexEx+15)  = d.s1.thermodynamic_forces[3]; // sig_xy
            
            mfrontStressTensor->operator[](indexEx+16)  = d.s1.thermodynamic_forces[4]; // sig_xz
            mfrontStressTensor->operator[](indexEx+17)  = d.s1.thermodynamic_forces[4]; // sig_xz
            mfrontStressTensor->operator[](indexEx+18)  = d.s1.thermodynamic_forces[4]; // sig_xz
            mfrontStressTensor->operator[](indexEx+19)  = d.s1.thermodynamic_forces[4]; // sig_xz            

            mfrontStressTensor->operator[](indexEx+20)  = d.s1.thermodynamic_forces[5]; // sig_yz
            mfrontStressTensor->operator[](indexEx+21)  = d.s1.thermodynamic_forces[5]; // sig_yz
            mfrontStressTensor->operator[](indexEx+22)  = d.s1.thermodynamic_forces[5]; // sig_yz
            mfrontStressTensor->operator[](indexEx+23)  = d.s1.thermodynamic_forces[5]; // sig_yz             
            
          }
        }

        if ( mfrontMaterialTensor != NULL && mfrontStrainTensor != NULL )
        {
          if (verbosity)
          {
            cout << " \033[1;36m Message MFront :: Calculating Material Tensor   \033[0m \n"
              << " \033[1;36m                :: Calculating Stress Tensor     \033[0m \n"
              << " \033[1;36m                :: Performing Mfront Integration \033[0m \n"
              << endl;
          }

          int totalGaussPoints =  mfrontMaterialTensor->n / 84;
          int indexEx       ;
          int indexMtTensor ;

          for (int i = 0; i < totalGaussPoints; i++)
          {

            indexEx  = i*24         ;  // 6 - components of sym. strain/stress tensor and 4 quadrature points per element 6*4= 24

            d.s1.gradients[0] = mfrontStrainTensor->operator[](indexEx)  ;  //E11
            d.s1.gradients[1] = mfrontStrainTensor->operator[](indexEx+4);  //E22
            d.s1.gradients[2] = mfrontStrainTensor->operator[](indexEx+8);  //E33
            d.s1.gradients[3] = mfrontStrainTensor->operator[](indexEx+12); //E12
            d.s1.gradients[4] = mfrontStrainTensor->operator[](indexEx+16); //E13
            d.s1.gradients[5] = mfrontStrainTensor->operator[](indexEx+20); //E23 

            d.K[0] = 1.;
            integrate(v, b);

            mfrontStressTensor->operator[](indexEx)    = d.s1.thermodynamic_forces[0]; // sig_xx
            mfrontStressTensor->operator[](indexEx+1)  = d.s1.thermodynamic_forces[0]; // sig_xx
            mfrontStressTensor->operator[](indexEx+2)  = d.s1.thermodynamic_forces[0]; // sig_xx
            mfrontStressTensor->operator[](indexEx+3)  = d.s1.thermodynamic_forces[0]; // sig_xx

            mfrontStressTensor->operator[](indexEx+4)  = d.s1.thermodynamic_forces[1]; // sig_yy
            mfrontStressTensor->operator[](indexEx+5)  = d.s1.thermodynamic_forces[1]; // sig_yy
            mfrontStressTensor->operator[](indexEx+6)  = d.s1.thermodynamic_forces[1]; // sig_yy
            mfrontStressTensor->operator[](indexEx+7)  = d.s1.thermodynamic_forces[1]; // sig_yy

            mfrontStressTensor->operator[](indexEx+8)  = d.s1.thermodynamic_forces[2];  // sig_zz
            mfrontStressTensor->operator[](indexEx+9)  = d.s1.thermodynamic_forces[2];  // sig_zz
            mfrontStressTensor->operator[](indexEx+10)  = d.s1.thermodynamic_forces[2]; // sig_zz
            mfrontStressTensor->operator[](indexEx+11)  = d.s1.thermodynamic_forces[2]; // sig_zz            
            
            mfrontStressTensor->operator[](indexEx+12)  = d.s1.thermodynamic_forces[3]; // sig_xy
            mfrontStressTensor->operator[](indexEx+13)  = d.s1.thermodynamic_forces[3]; // sig_xy
            mfrontStressTensor->operator[](indexEx+14)  = d.s1.thermodynamic_forces[3]; // sig_xy
            mfrontStressTensor->operator[](indexEx+15)  = d.s1.thermodynamic_forces[3]; // sig_xy
            
            mfrontStressTensor->operator[](indexEx+16)  = d.s1.thermodynamic_forces[4]; // sig_xz
            mfrontStressTensor->operator[](indexEx+17)  = d.s1.thermodynamic_forces[4]; // sig_xz
            mfrontStressTensor->operator[](indexEx+18)  = d.s1.thermodynamic_forces[4]; // sig_xz
            mfrontStressTensor->operator[](indexEx+19)  = d.s1.thermodynamic_forces[4]; // sig_xz            

            mfrontStressTensor->operator[](indexEx+20)  = d.s1.thermodynamic_forces[5]; // sig_yz
            mfrontStressTensor->operator[](indexEx+21)  = d.s1.thermodynamic_forces[5]; // sig_yz
            mfrontStressTensor->operator[](indexEx+22)  = d.s1.thermodynamic_forces[5]; // sig_yz
            mfrontStressTensor->operator[](indexEx+23)  = d.s1.thermodynamic_forces[5]; // sig_yz 

            indexMtTensor  = i*84;  // 6 - components of sym. material tensor and 3 quadrature points per element 3*6= 18

                //------------ row 1 - 6 components -------------------//
  
            mfrontMaterialTensor->operator[](indexMtTensor +0 ) = d.K[0];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +1 ) = d.K[0];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +2 ) = d.K[0];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +3 ) = d.K[0];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            
            mfrontMaterialTensor->operator[](indexMtTensor +4 ) = d.K[1];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +5 ) = d.K[1];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +6 ) = d.K[1];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +7 ) = d.K[1];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor +8 ) = d.K[2];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +9) = d.K[2];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +10) = d.K[2];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +11) = d.K[2];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor +12) = d.K[3];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +13) = d.K[3];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +14) = d.K[3];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +15) = d.K[3];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor +16) = d.K[4];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +17) = d.K[4];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +18) = d.K[4];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +19) = d.K[4];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor +20) = d.K[5];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +21) = d.K[5];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +22) = d.K[5];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +23) = d.K[5];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)  
                                                   

            //------------ row 2 - 5 components -------------------//


            mfrontMaterialTensor->operator[](indexMtTensor +24) = d.K[7];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +25) = d.K[7];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +26) = d.K[7];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +27) = d.K[7];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor +28) = d.K[8];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +29) = d.K[8];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +30) = d.K[8];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +31) = d.K[8];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            
            mfrontMaterialTensor->operator[](indexMtTensor +32) = d.K[9];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +33) = d.K[9];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +34) = d.K[9];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +35) = d.K[9];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            
            mfrontMaterialTensor->operator[](indexMtTensor +36) = d.K[10];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +37) = d.K[10];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +38) = d.K[10];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +39) = d.K[10];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)                                   

            mfrontMaterialTensor->operator[](indexMtTensor +40) = d.K[11];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +41) = d.K[11];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +42) = d.K[11];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +43) = d.K[11];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            //------------ row 3 - 4 components -------------------//


            mfrontMaterialTensor->operator[](indexMtTensor +44) = d.K[14];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +45) = d.K[14];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +46) = d.K[14];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +47) = d.K[14];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            
            mfrontMaterialTensor->operator[](indexMtTensor +48) = d.K[15];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +49) = d.K[15];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +50) = d.K[15];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +51) = d.K[15];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            
            mfrontMaterialTensor->operator[](indexMtTensor +52) = d.K[16];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +53) = d.K[16];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +54) = d.K[16];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +55) = d.K[16];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            
            mfrontMaterialTensor->operator[](indexMtTensor +56) = d.K[17];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +57) = d.K[17];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +58) = d.K[17];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +59) = d.K[17];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            
            //------------ row 4 - 3 components -------------------//
                                   
            mfrontMaterialTensor->operator[](indexMtTensor +60) = d.K[21];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +61) = d.K[21];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +62) = d.K[21];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +63) = d.K[21];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            mfrontMaterialTensor->operator[](indexMtTensor +64) = d.K[22];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +65) = d.K[22];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +66) = d.K[22];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +67) = d.K[22];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            
            mfrontMaterialTensor->operator[](indexMtTensor +68) = d.K[23];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +69) = d.K[23];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +70) = d.K[23];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +71) = d.K[23];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
                        

            //------------ row 5 - 2 components -------------------// 
            
            mfrontMaterialTensor->operator[](indexMtTensor +72) = d.K[28];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +73) = d.K[28];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +74) = d.K[28];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +75) = d.K[28];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            
            mfrontMaterialTensor->operator[](indexMtTensor +76) = d.K[29];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +77) = d.K[29];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +78) = d.K[29];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +79) = d.K[29];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)

            //------------ row 6 - 1 component -------------------// 

            mfrontMaterialTensor->operator[](indexMtTensor +80) = d.K[35];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +81) = d.K[35];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +82) = d.K[35];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
            mfrontMaterialTensor->operator[](indexMtTensor +83) = d.K[35];  //  Mt_11 Quadrature point 1 (3 Quad points per tria)
          }
        }
      }

    }
  }
  return 0L;
}
