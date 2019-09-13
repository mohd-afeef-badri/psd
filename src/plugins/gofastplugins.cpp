/****************************************************************************/
/* This file is part of FreeFem++.                                          */
/*                                                                          */
/* FreeFem++ is free software: you can redistribute it and/or modify        */
/* it under the terms of the GNU Lesser General Public License as           */
/* published by the Free Software Foundation, either version 3 of           */
/* the License, or (at your option) any later version.                      */
/*                                                                          */
/* FreeFem++ is distributed in the hope that it will be useful,             */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of           */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            */
/* GNU Lesser General Public License for more details.                      */
/*                                                                          */
/* You should have received a copy of the GNU Lesser General Public License */
/* along with FreeFem++. If not, see <http://www.gnu.org/licenses/>.        */
/****************************************************************************/

// SUMMARY : GoFastPlugins.cpp contains plugins to perform fast computations
// LICENSE : LGPLv3
// ORG     : CEA, Saclay, FRANCE
// AUTHORS : Mohf Afeef BADRI
// E-MAIL  : afeef.badri@gmail.com
//-- GoFastPlugins for FreeFem++ --//

#include <iostream>
#include <math.h>

#include "ff++.hpp"
#include "RNM.hpp"
#include "AFunction.hpp"
#include "AFunction_ext.hpp"
using namespace Fem2D;

using namespace std;

#ifdef __LP64__
typedef int intblas;
typedef int integer;
#else
typedef long intblas;
typedef long integer;
#endif

typedef integer logical;
typedef float LAPACK_real;
typedef double doublereal;
typedef logical (*L_fp)();
typedef integer ftnlen;
typedef complex<float> LAPACK_complex;
typedef complex<double> doublecomplex;
typedef void VOID;
#define complex LAPACK_complex
#define real LAPACK_real

#include "clapack.h"
#undef real
#undef complex


// (computation of the eigenvalues and eigenvectors of a real symmetric matrix)
long lapack_dsyev (KNM<double> *const &A, KN<double> *const &vp, KNM<double> *const &vectp) {

	intblas n = A->N();
	
	//ERROR CHECK//
	/*
	ffassert(A->M() == n);
	ffassert(vectp->N() == n);
	ffassert(vectp->M() == n);
	ffassert(vp->N() == n);
	*/
	
	
	KNM<double> mat(*A);
	intblas info, lw = -1;
	KN<double> w(1);
	char JOBZ = 'V', UPLO = 'U';
	dsyev_(&JOBZ, &UPLO, &n, mat, &n, *vp, w, &lw, &info);
	lw = w[0];
	w.resize(lw);
	dsyev_(&JOBZ, &UPLO, &n, mat, &n, *vp, w, &lw, &info);
	
	if (info < 0) {
		cout << " LAPACK ERROR  dsyev: the " << info << "-th argument had an illegal value." << endl;
	} else if (info > 0) {
		cout << " LAPACK ERROR  dsyev: the algorithm failed to converge." << endl;
	} else if (info == 0) {
		*vectp = mat;
	}

	return info;
}

// http://www.netlib.org/lapack/explore-html/d2/d8a/group__double_s_yeigen_ga442c43fca5493590f8f26cf42fed4044.html#ga442c43fca5493590f8f26cf42fed4044
// (computation of the eigenvalues and eigenvectors of a real symmetric matrix)
long lapack_dsyevAlone (KNM<double> *const &A, KN<double> *const &vp) {

	intblas n = A->N();
	
	//ERROR CHECK//
	/*
	ffassert(A->M() == n);
	ffassert(vectp->N() == n);
	ffassert(vectp->M() == n);
	ffassert(vp->N() == n);
	*/
	
	
	KNM<double> mat(*A);
	intblas info, lw = -1;
	KN<double> w(1);
	char JOBZ = 'N', UPLO = 'U';
	dsyev_(&JOBZ, &UPLO, &n, mat, &n, *vp, w, &lw, &info);
	lw = w[0];
	w.resize(lw);
	dsyev_(&JOBZ, &UPLO, &n, mat, &n, *vp, w, &lw, &info);
	
	if (info < 0) {
		cout << " LAPACK ERROR  dsyev: the " << info << "-th argument had an illegal value." << endl;
	} else if (info > 0) {
		cout << " LAPACK ERROR  dsyev: the algorithm failed to converge." << endl;
	} /*else if (info == 0) {
		cout << " LAPACK ERROR  dsyev: Done!!!!." << endl;
		//*vectp = mat;
	}*/

	return info;
}

long lapack_zheev (KNM<Complex> *const &A, KN<double> *const &vp, KNM<Complex> *const &vectp) {

	intblas n = A->N();

	//ERROR CHECK//
	/*
	ffassert(A->M() == n);
	ffassert(vectp->N() == n);
	ffassert(vectp->M() == n);
	ffassert(vp->N() == n);
	*/
	
	
	KNM<Complex> mat(*A);
	intblas info, lw = -1;
	KN<Complex> w(1);
	KN<double> rw(max(1, int(3 * n - 2)));
	char JOBZ = 'V', UPLO = 'U';
	zheev_(&JOBZ, &UPLO, &n, mat, &n, *vp, w, &lw, rw, &info);
	lw = w[0].real();
	w.resize(lw);
	zheev_(&JOBZ, &UPLO, &n, mat, &n, *vp, w, &lw, rw, &info);
	
	
	if (info < 0) {
		cout << " LAPACK ERROR  zheev: the " << info << "-th argument had an illegal value." << endl;
	} else if (info > 0) {
		cout << "  LAPACK ERROR zheev: the algorithm failed to converge." << endl;
	} else if (info == 0) {
		*vectp = mat;
	}

	return info;
}

  
double GFPmaxintwoP1(KN<double> *const & f, KN<double> *const & f1)   
{
    long int nn = f->N();
    for(long int i=0; i<nn; i++) {    
      *(f[0]+i)=max(*(f1[0]+i),*(f[0]+i));
    }
  return 0.0;
}


template<class K>
class updatedynamic_Op : public E_F0mps {
    public:
        Expression du					;
        Expression uold					;
        Expression vold					;
        Expression aold					;
        Expression beta					;                
        Expression gamma				;
        Expression dt					;  
              
        static const int n_name_param = 0		;
        static basicAC_F0::name_and_type name_param[]	;
        Expression nargs[n_name_param]			;
        
        updatedynamic_Op(const basicAC_F0& args		, 
        		Expression param1		, 
        		Expression param2		, 
        		Expression param3		, 
        		Expression param4		,
        		Expression param5		,
        		Expression param6		,
        		Expression param7		
        		) : 
        		du     (param1)			, 
        		uold   (param2)			, 
        		vold   (param3)			,  
        		aold   (param4)			,
        		beta   (param5)			, 
        		gamma  (param6)			,
        		dt     (param7)			
        		{
            		args.SetNameParam(n_name_param	, 
            				  name_param	, 
            				  nargs
            				  )		;
        		}
        		
        AnyType operator()(Stack stack) const		;
};

template<class K>
basicAC_F0::name_and_type updatedynamic_Op<K>::name_param[] = { };


template<class K>
class updatedynamic : public OneOperator {
    public:
        updatedynamic() : OneOperator(atype<long>()	, 
        			     atype<KN<K>*>()	, 
        			     atype<KN<K>*>()	, 
        			     atype<KN<K>*>()	, 
        			     atype<KN<K>*>()    ,
        			     atype<double>()	,
        			     atype<double>()	,        			     
        			     atype<double>()  
        			     ) {}

        E_F0* code(const basicAC_F0& args) const {
            return new updatedynamic_Op<K>(args, 
            				  t[0]->CastTo(args[0]), 
            				  t[1]->CastTo(args[1]), 
            				  t[2]->CastTo(args[2]), 
            				  t[3]->CastTo(args[3]),
            				  t[4]->CastTo(args[4]),
            				  t[5]->CastTo(args[5]),
            				  t[6]->CastTo(args[6])           				              				  
            				  );
        }
};


template<class K>
AnyType updatedynamic_Op<K>::operator()(Stack stack) const {
    KN<K>* vec1 = GetAny<KN<K>*>((*du)(stack))		;
    KN<K>* vec2 = GetAny<KN<K>*>((*uold)(stack))	;
    KN<K>* vec3 = GetAny<KN<K>*>((*vold)(stack))	;
    KN<K>* vec4 = GetAny<KN<K>*>((*aold)(stack))	;        
    double bet   = GetAny<double>((*beta)(stack))	;
    double gam  = GetAny<double>((*gamma)(stack))	;
    double ddt  = GetAny<double>((*dt)(stack))		;

    double anew						;
    
    for(int j = 0; j < vec1->n; ++j){           
      anew = (vec1->operator[](j)-vec2->operator[](j)-ddt*vec3->operator[](j))/bet/(ddt*ddt) - (1.-2.*bet)/2./bet*vec4->operator[](j);        
      vec3->operator[](j) = vec3->operator[](j) + ddt*((1.-gam)*vec4->operator[](j) + gam*anew);    
      vec4->operator[](j)= anew;						   
      vec2->operator[](j)= vec1->operator[](j);	       
     }     
    return 0L;
}

template<class K>
class DecompEnergy_Op : public E_F0mps {
    public:
        Expression ex					;
        Expression ey					;
        Expression exy					;
        Expression Hp					;
        Expression Hm					;                
        Expression Hout					;
        Expression lambda				;  
        Expression mu					;                    
              
        static const int n_name_param = 0		;
        static basicAC_F0::name_and_type name_param[]	;
        Expression nargs[n_name_param]			;
        
        DecompEnergy_Op(const basicAC_F0& args		, 
        		Expression param1		, 
        		Expression param2		, 
        		Expression param3		, 
        		Expression param4		,
        		Expression param5		,
        		Expression param6		,
        		Expression param7		,
        		Expression param8		        		        				        		        		
        		) : 
        		ex     (param1)			, 
        		ey     (param2)			, 
        		exy    (param3)			,  
        		Hp     (param4)			,
        		Hm     (param5)			, 
        		Hout   (param6)			,
        		lambda (param7)			,
        		mu     (param8)	        		        				        		        		 
        		{
            		args.SetNameParam(n_name_param	, 
            				  name_param	, 
            				  nargs
            				  )		;
        		}
        		
        AnyType operator()(Stack stack) const		;
};

template<class K>
basicAC_F0::name_and_type DecompEnergy_Op<K>::name_param[] = { };

template<class K>
class DecompEnergy : public OneOperator {
    public:
        DecompEnergy() : OneOperator(atype<long>()	, 
        			     atype<KN<K>*>()	, 
        			     atype<KN<K>*>()	, 
        			     atype<KN<K>*>()	, 
        			     atype<KN<K>*>()    ,
        			     atype<KN<K>*>()    ,
        			     atype<KN<K>*>() 	,
        			     atype<double>()	,
        			     atype<double>()  
        			     ) {}

        E_F0* code(const basicAC_F0& args) const {
            return new DecompEnergy_Op<K>(args, 
            				  t[0]->CastTo(args[0]), 
            				  t[1]->CastTo(args[1]), 
            				  t[2]->CastTo(args[2]), 
            				  t[3]->CastTo(args[3]),
            				  t[4]->CastTo(args[4]),
            				  t[5]->CastTo(args[5]),
            				  t[6]->CastTo(args[6]),
            				  t[7]->CastTo(args[7])            				              				  
            				  );
        }
};

template<class K>
AnyType DecompEnergy_Op<K>::operator()(Stack stack) const {
    KN<K>* in1  = GetAny<KN<K>*>((*ex)(stack))		;
    KN<K>* in2  = GetAny<KN<K>*>((*ey)(stack))		;
    KN<K>* in3  = GetAny<KN<K>*>((*exy)(stack))		;
    KN<K>* out1 = GetAny<KN<K>*>((*Hp)(stack))		;
    KN<K>* out2 = GetAny<KN<K>*>((*Hm)(stack))		;
    KN<K>* out3 = GetAny<KN<K>*>((*Hout)(stack))	;        
    double lm   = GetAny<double>((*lambda)(stack))	;
    double muw  = GetAny<double>((*mu)(stack))		;

    KNM<double> Amat(2,2);
    KN<double>  eval(2);
    double d1,d2;

    intblas n = 2;
    char JOBZ = 'N', UPLO = 'U';
    intblas info, lw = -1;
    KN<double> w(1);
    dsyev_(&JOBZ, &UPLO, &n, Amat, &n, eval, w, &lw, &info);
    lw = w[0];
    w.resize(lw);
	    
    for(int j = 0; j < in1->n; ++j){
        out1->operator[](j) = max(0.,double(in1->operator[](j)+in2->operator[](j)));
        out1->operator[](j) = 0.5*lm*out1->operator[](j)*out1->operator[](j);
        out2->operator[](j) = min(0.,double(in1->operator[](j)+in2->operator[](j)));
        out2->operator[](j) = 0.5*lm*out2->operator[](j)*out2->operator[](j);
        Amat(0,0)=in1->operator[](j); 
        Amat(0,1)=in3->operator[](j);
        Amat(1,1)=in2->operator[](j);
	dsyev_(&JOBZ, &UPLO, &n, Amat, &n, eval, w, &lw, &info);
        //lapack_dsyevAlone (&Amat, &eval);
        d1=max(0.,eval[0]);
        d2=max(0.,eval[1]);
        out1->operator[](j) += muw*(d1*d1 + d2*d2);
        d1=min(0.,eval[0]);
        d2=min(0.,eval[1]);
        out2->operator[](j) += muw*(d1*d1 + d2*d2);
        out3->operator[](j) = max(out3->operator[](j),out1->operator[](j));
     }     
    return 0L;
}






template<class K>
class DecompEnergy3_Op : public E_F0mps {
    public:
        Expression exx					;
        Expression eyy					;
        Expression ezz					;        
        Expression exy					;
        Expression exz					;
        Expression eyz					;
        Expression Hp					;
        Expression Hm					;                
        Expression Hout					;
        Expression prpty				;  
              
        static const int n_name_param = 0		;
        static basicAC_F0::name_and_type name_param[]	;
        Expression nargs[n_name_param]			;
        
        DecompEnergy3_Op(const basicAC_F0& args		, 
        		Expression param1		, 
        		Expression param2		, 
        		Expression param3		, 
        		Expression param4		,
        		Expression param5		,
        		Expression param6		,
        		Expression param7		,
        		Expression param8		,
        		Expression param9		,
        		Expression param10		
        		) : 
        		exx    (param1)			, 
        		eyy    (param2)			, 
        		ezz    (param3)			,
        		exy    (param4)			, 
        		exz    (param5)			, 
        		eyz    (param6)			,         		  
        		Hp     (param7)			,
        		Hm     (param8)			, 
        		Hout   (param9)			,
        		prpty  (param10)		
        		{
            		args.SetNameParam(n_name_param	, 
            				  name_param	, 
            				  nargs
            				  )		;
        		}
        		
        AnyType operator()(Stack stack) const		;
};

template<class K>
basicAC_F0::name_and_type DecompEnergy3_Op<K>::name_param[] = { };

template<class K>
class DecompEnergy3 : public OneOperator {
    public:
        DecompEnergy3() : OneOperator(atype<long>()	, 
        			     atype<KN<K>*>()	, 
        			     atype<KN<K>*>()	, 
        			     atype<KN<K>*>()	, 
        			     atype<KN<K>*>()    ,
        			     atype<KN<K>*>()    ,
        			     atype<KN<K>*>() 	,
        			     atype<KN<K>*>()    ,
        			     atype<KN<K>*>()    ,
        			     atype<KN<K>*>() 	,        			     
        			     atype<KN<K>*>() 	        			     
        			     ) {}

        E_F0* code(const basicAC_F0& args) const {
            return new DecompEnergy3_Op<K>(args, 
            				  t[0]->CastTo(args[0]), 
            				  t[1]->CastTo(args[1]), 
            				  t[2]->CastTo(args[2]), 
            				  t[3]->CastTo(args[3]),
            				  t[4]->CastTo(args[4]),
            				  t[5]->CastTo(args[5]),
            				  t[6]->CastTo(args[6]),
            				  t[7]->CastTo(args[7]),
            				  t[8]->CastTo(args[8]),
            				  t[9]->CastTo(args[9])				  
            				  );
        }
};

template<class K>
AnyType DecompEnergy3_Op<K>::operator()(Stack stack) const {
    KN<K>* in1  = GetAny<KN<K>*>((*exx)(stack))		;
    KN<K>* in2  = GetAny<KN<K>*>((*eyy)(stack))		;
    KN<K>* in3  = GetAny<KN<K>*>((*ezz)(stack))		;
    KN<K>* in4  = GetAny<KN<K>*>((*exy)(stack))		;
    KN<K>* in5  = GetAny<KN<K>*>((*exz)(stack))		;
    KN<K>* in6  = GetAny<KN<K>*>((*eyz)(stack))		;    
    KN<K>* out1 = GetAny<KN<K>*>((*Hp)(stack))		;
    KN<K>* out2 = GetAny<KN<K>*>((*Hm)(stack))		;
    KN<K>* out3 = GetAny<KN<K>*>((*Hout)(stack))	;
    KN<K>* par = GetAny<KN<K>*>((*prpty)(stack))	;                    

    KNM<double> Amat(3,3);
    KN<double>  eval(3);
    double d1,d2,d3;
    double lm=par->operator[](0);
    double muw=par->operator[](1);

    intblas n = 3;
    char JOBZ = 'N', UPLO = 'U';
    intblas info, lw = -1;
    KN<double> w(1);
    dsyev_(&JOBZ, &UPLO, &n, Amat, &n, eval, w, &lw, &info);
    lw = w[0];
    w.resize(lw);
	    
    for(int j = 0; j < in1->n; ++j){
        out1->operator[](j) = max( 0. , double(in1->operator[](j)+in2->operator[](j)+in3->operator[](j)) );
        out1->operator[](j) = 0.5*lm*out1->operator[](j)*out1->operator[](j);
        out2->operator[](j) = min( 0. , double(in1->operator[](j)+in2->operator[](j)+in3->operator[](j)) );
        out2->operator[](j) = 0.5*lm*out2->operator[](j)*out2->operator[](j);
        Amat(0,0)=in1->operator[](j); 
        Amat(1,1)=in2->operator[](j);
        Amat(2,2)=in3->operator[](j);
        Amat(0,1)=in4->operator[](j);
        Amat(0,2)=in5->operator[](j);
        Amat(1,2)=in6->operator[](j);                                
	dsyev_(&JOBZ, &UPLO, &n, Amat, &n, eval, w, &lw, &info);
        //lapack_dsyevAlone (&Amat, &eval);
        d1=max(0.,eval[0]);
        d2=max(0.,eval[1]);
        d3=max(0.,eval[2]);
        out1->operator[](j) += muw*(d1*d1 + d2*d2 + d3*d3);
        d1=min(0.,eval[0]);
        d2=min(0.,eval[1]);
        d3=min(0.,eval[2]);
        out2->operator[](j) += muw*(d1*d1 + d2*d2 + d3*d3);
        out3->operator[](j) = max(out3->operator[](j),out1->operator[](j));
     }     
    return 0L;
}

template<class K>
class MazarsDamageUpdate_Op : public E_F0mps {
    public:
        Expression St					;
        Expression intvar				;
        Expression damage				;                
        Expression kappa0				;
        Expression kappaC				;  
              
        static const int n_name_param = 0		;
        static basicAC_F0::name_and_type name_param[]	;
        Expression nargs[n_name_param]			;
        
        MazarsDamageUpdate_Op(const basicAC_F0& args	, 
        		Expression param1		, 
        		Expression param2		, 
        		Expression param3		, 
        		Expression param4		,
        		Expression param5		        		        				        		        		
        		) : 
        		St     (param1)			, 
        		intvar (param2)			,
        		damage (param3)			, 
        		kappa0 (param4)			,
        		kappaC (param5)			
        		{
            		args.SetNameParam(n_name_param	, 
            				  name_param	, 
            				  nargs
            				  )		;
        		}
        		
        AnyType operator()(Stack stack) const		;
};

template<class K>
basicAC_F0::name_and_type MazarsDamageUpdate_Op<K>::name_param[] = { };

template<class K>
class MazarsDamageUpdate : public OneOperator {
    public:
        MazarsDamageUpdate() : OneOperator(atype<long>(), 
        			     atype<KN<K>*>()	, 
        			     atype<KN<K>*>()	, 
        			     atype<KN<K>*>()	, 
        			     atype<double>()	,
        			     atype<double>() 	        			     
        			     ) {}

        E_F0* code(const basicAC_F0& args) const {
            return new MazarsDamageUpdate_Op<K>(args, 
            				  t[0]->CastTo(args[0]), 
            				  t[1]->CastTo(args[1]), 
            				  t[2]->CastTo(args[2]), 
            				  t[3]->CastTo(args[3]),
            				  t[4]->CastTo(args[4])		  
            				  );
        }
};

template<class K>
AnyType MazarsDamageUpdate_Op<K>::operator()(Stack stack) const {
    KN<K>* Ex   = GetAny<KN<K>*>((*St)(stack))		;
    KN<K>* out1 = GetAny<KN<K>*>((*intvar)(stack))	;
    KN<K>* out2 = GetAny<KN<K>*>((*damage)(stack))	;
    double K0   = GetAny<double>((*kappa0)(stack))	;
    double Kc   = GetAny<double>((*kappaC)(stack))	;

/* 
//--------------------------------------------------------------------------------------------------
//      --------------- NO LAPACK WORKING METHOD -------------------------
//--------------------------------------------------------------------------------------------------
    double tmp1,tmp2,tmpep1,tmpep2,tmpeqStrain;
           
    for(int j = 0; j < Ex->n; ++j){
       tmp1=Ex->operator[](j)+Ey->operator[](j);
       tmp2=sqrt(pow((Ex->operator[](j)-Ey->operator[](j)),2)+4.*pow((Exy->operator[](j)),2));
       tmpep1=0.5*(tmp1+tmp2); tmpep2=0.5*(tmp1-tmp2);
       tmpeqStrain=sqrt(pow((max(0.,tmpep1)),2) + pow((max(0.,tmpep2)),2))  ;       
       out1->operator[](j) = (out1->operator[](j) < tmpeqStrain ? tmpeqStrain : out1->operator[](j));
       out2->operator[](j) = 1.-(K0/out1->operator[](j))*exp(-(out1->operator[](j)-K0)/(Kc-K0));       
       out2->operator[](j) = floor(100000.*out2->operator[](j))/100000. ;       
     }     
    return 0L;
*/    

    
    double tmpeqStrain;
    
    KNM<double> Amat(2,2)   ;				// Amat is infact strain matrix
    KN<double>  eval(2)     ;				// To store eigenvalues
    intblas n = 2;					// Blas integer
    char JOBZ = 'N', UPLO = 'U';			// Upper triangular
    intblas info, lw = -1;
    KN<double> w(1);
    dsyev_(&JOBZ, &UPLO, &n, Amat, &n, eval, w, &lw, &info);
    lw = w[0];
    w.resize(lw);
  
    for(int j = 0; j < out1->n; ++j){
        Amat(0,0)=Ex->operator[](3*j+0) ; 				// Strain xx
        Amat(1,1)=Ex->operator[](3*j+1) ;				// Strain yy 
        Amat(0,1)=Ex->operator[](3*j+2);       			// Strain xy
        
	dsyev_(&JOBZ, &UPLO, &n, Amat, &n, eval, w, &lw, &info);  // Calculate Eigenvalues--> eval	
	
	tmpeqStrain=sqrt(pow((max(0.,eval[0])),2) + pow((max(0.,eval[1])),2))  ; 
        out1->operator[](j) = (out1->operator[](j) < tmpeqStrain ? tmpeqStrain : out1->operator[](j));	
        out2->operator[](j) = 1.-(K0/out1->operator[](j))*exp(-(out1->operator[](j)-K0)/(Kc-K0));       
        out2->operator[](j) = floor(100000.*out2->operator[](j))/100000. ;
    }
         
    return 0L;       
}


 
static void InitFF()
{
  Global.Add("GFPUpdateDynamic", "(", new updatedynamic<double>);
  Global.Add("GFPDecompEnergy3D", "(", new DecompEnergy3<double>);
  Global.Add("GFPDecompEnergy2D", "(", new DecompEnergy<double>);
  Global.Add("GFPMazarsDamageUpdate", "(", new MazarsDamageUpdate<double>);
  Global.Add("GFPmaxintwoFEfields","(",new OneOperator2_<double,KN<double>*, KN<double>*>(GFPmaxintwoP1));		
  Global.Add("GFPeigen", "(", new OneOperator3_<long, KNM<double> *, KN<double> *, KNM<double> *>(lapack_dsyev));
  Global.Add("GFPeigenAlone", "(", new OneOperator2_<long, KNM<double> *, KN<double> *>(lapack_dsyevAlone));  

}
LOADFUNC(InitFF)   
