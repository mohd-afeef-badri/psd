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
class mfrontElasticityHandler_Op : public E_F0mps {
    public:
        Expression behaviourName        		;

        static const int n_name_param = 6		;
        static basicAC_F0::name_and_type name_param[]	;
        Expression nargs[n_name_param]			;
        
        mfrontElasticityHandler_Op(const basicAC_F0& args   ,
        		Expression param1                   				
        		) :
        		behaviourName     (param1)
        		{
            		args.SetNameParam( n_name_param	,
            				   name_param	,
            				   nargs
            				 )		;
        		}
        AnyType operator()(Stack stack) const		;
};

template<class K>
basicAC_F0::name_and_type mfrontElasticityHandler_Op<K>::name_param[] =
{
    {"mfrontBehaviourHypothesis" , &typeid(std::string*)},
    {"mfrontPropertyNames"       , &typeid(std::string*)},
    {"mfrontPropertyValues"      , &typeid(KN<K>*)      },
    {"mfrontMaterialTensor"      , &typeid(KN<K>*)      },
    {"mfrontStrainTensor"        , &typeid(KN<K>*)      },
    {"mfrontStressTensor"        , &typeid(KN<K>*)      }
};

template<class K>
class mfrontElasticityHandler : public OneOperator {
    public:
        mfrontElasticityHandler() : OneOperator(atype<long>()	,
        			     atype<string*>()
        			     ) {}

        E_F0* code(const basicAC_F0& args) const {
            return new mfrontElasticityHandler_Op<K>(args,
            				  t[0]->CastTo(args[0])
            				  );
        }
};

template<class K>
AnyType mfrontElasticityHandler_Op<K>::operator()(Stack stack) const {

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
            " in mfrontElasticityHandler(...) function. Example   \n"
            "   \033[1;34m mfrontElasticityHandler( mfrontBehaviourHypothesis = \"GENERALISEDPLANESTRAIN\", .... )\033[0m\n"
            "   \033[1;34m mfrontElasticityHandler( mfrontBehaviourHypothesis = \"PLANESTRAIN\", .... )\033[0m\n"
            "   \033[1;34m mfrontElasticityHandler( mfrontBehaviourHypothesis = \"TRIDIMENSIONAL\", .... )\033[0m\n"
            "===================================================================\n" << endl;
            
     exit(1);
    }
/**/
   if( mfrontBehaviourHypothesis!=NULL){
   

   if(*mfrontBehaviourHypothesis=="GENERALISEDPLANESTRAIN")
    {
     if (verbosity)
      {
       cout << " \n" 
               " \033[1;36m Message MFront :: Creating Hypothesis :: \033[0m " << *mfrontBehaviourHypothesis  << "\n"
               " \033[1;36m                :: Loading  Behaviour  :: \033[0m " << *mfrontBehaviourName        << "\n"
               " \033[1;36m                :: Creating BehaviourData \033[0m "                                << "\n" 
               " \033[1;36m                :: Creating BehaviourDataView \033[0m "                            << "\n"                                      
            << " \n" << endl;
      }
        
     constexpr const auto h = Hypothesis::GENERALISEDPLANESTRAIN;
     const auto b = load("./../law/elasticity/src/libBehaviour.so", *mfrontBehaviourName , h);
     
     auto d = BehaviourData{b};
     auto v = make_view(d);

     if ( b.mps.size() > 0 
          && ( mfrontPropertyNames  == NULL || mfrontPropertyValues == NULL || mfrontPropertyValues->n < b.mps.size() )
     )
      {
       cout <<
            "===================================================================\n"
            " \033[1;31m ** ERROR DETECTED  ** \033[0m\n"
            "===================================================================\n"
            " mfrontPropertyNames and/or  mfrontPropertyValues wrong. Please consider \n"
            " filling in  \033[1;34mmfrontPropertyNames\033[0m   and   \033[1;34mmfrontPropertyValues\033[0m  arguments\n"
            " correctly in the in mfrontElasticityHandler(...) function. For example,\n"
            "   \033[1;34m mfrontElasticityHandler( ..., mfrontPropertyNames = \"YoungModulus PoissonRatio\", mfrontPropertyValues = [1e9, 0.3], .... )\033[0m\n"
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
            " correctly in the in mfrontElasticityHandler(...) function. For example,\n"
            "   \033[1;34m mfrontElasticityHandler( ..., mfrontPropertyNames = \"YoungModulus PoissonRatio\", .... )\033[0m\n"
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
           
           d.K[0] = 1.;
           integrate(v, b);
           
           int totalGaussPoints =  mfrontMaterialTensor->n / 6;      
           int indexMt11, indexMt12, indexMt13, indexMt22, indexMt23, indexMt33;
           for (int i = 0; i < totalGaussPoints; i++)
            {    
             indexMt11  = i*6          ;
             indexMt12  = indexMt11 + 1;
             indexMt13  = indexMt11 + 2;
             indexMt22  = indexMt11 + 3;
             indexMt23  = indexMt11 + 4;
             indexMt33  = indexMt11 + 5;
    
             mfrontMaterialTensor->operator[](indexMt11)=d.K[0];
             mfrontMaterialTensor->operator[](indexMt12)=d.K[1];
             mfrontMaterialTensor->operator[](indexMt13)=d.K[3];
             mfrontMaterialTensor->operator[](indexMt22)=d.K[5];
             mfrontMaterialTensor->operator[](indexMt23)=d.K[7];
             mfrontMaterialTensor->operator[](indexMt33)=d.K[15]/2;
            }                  
         }

       if ( mfrontMaterialTensor == NULL && mfrontStrainTensor != NULL )
         {
          if (verbosity)
           {
            cout << " \033[1;36m Message MFront :: Calculating Stress Tensor   \033[0m \n"
                 << " \033[1;36m                :: Performing Mfront Integration \033[0m \n" 
                 << endl;                      
           }
           
           int totalGaussPoints =  mfrontStrainTensor->n / 3;      
           int indexEx, indexEy, indexExy;
           
           for (int i = 0; i < totalGaussPoints; i++)
            {    
             indexEx  = i*3         ;
             indexEy  = indexEx + 1 ;
             indexExy = indexEx + 2 ;
                           
             d.s1.gradients[0] = mfrontStrainTensor->operator[](indexEx);  //E11
             d.s1.gradients[1] = mfrontStrainTensor->operator[](indexEy);  //E22
             d.s1.gradients[2] = 0.                                     ;  //E33
             d.s1.gradients[3] = mfrontStrainTensor->operator[](indexExy); //E12
             
             integrate(v, b);
                          
                          
             mfrontStressTensor->operator[](indexEx)  = d.s1.thermodynamic_forces[0]; // sig_xx 
             mfrontStressTensor->operator[](indexEy)  = d.s1.thermodynamic_forces[1]; // sig_yy               
             mfrontStressTensor->operator[](indexExy) = d.s1.thermodynamic_forces[3]; // sig_xy
                          
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
           
           int totalGaussPoints =  mfrontStrainTensor->n / 3;      
           int indexEx, indexEy, indexExy;
           int indexMt11, indexMt12, indexMt13, indexMt22, indexMt23, indexMt33;  
                    
           for (int i = 0; i < totalGaussPoints; i++)
            {
               
             indexEx  = i*3         ;
             indexEy  = indexEx + 1 ;
             indexExy = indexEx + 2 ;
    
             d.s1.gradients[0] = mfrontStrainTensor->operator[](indexEx);  //E11
             d.s1.gradients[1] = mfrontStrainTensor->operator[](indexEy);  //E22
             d.s1.gradients[2] = 0.                                     ;  //E33
             d.s1.gradients[3] = mfrontStrainTensor->operator[](indexExy); //E12           

             d.K[0] = 1.;
             integrate(v, b);
                          
             mfrontStressTensor->operator[](indexEx)  = d.s1.thermodynamic_forces[0]; // sig_xx 
             mfrontStressTensor->operator[](indexEy)  = d.s1.thermodynamic_forces[1]; // sig_yy               
             mfrontStressTensor->operator[](indexExy) = d.s1.thermodynamic_forces[3]; // sig_xy 
             
             
             indexMt11  = i*6          ;
             indexMt12  = indexMt11 + 1;
             indexMt13  = indexMt11 + 2;
             indexMt22  = indexMt11 + 3;
             indexMt23  = indexMt11 + 4;
             indexMt33  = indexMt11 + 5;
    
             mfrontMaterialTensor->operator[](indexMt11)=d.K[0];
             mfrontMaterialTensor->operator[](indexMt12)=d.K[1];
             mfrontMaterialTensor->operator[](indexMt13)=d.K[3];
             mfrontMaterialTensor->operator[](indexMt22)=d.K[5];
             mfrontMaterialTensor->operator[](indexMt23)=d.K[7];
             mfrontMaterialTensor->operator[](indexMt33)=d.K[15]/2;             
            }                  
         }
      }
      
    }
    }
    return 0L;
}
