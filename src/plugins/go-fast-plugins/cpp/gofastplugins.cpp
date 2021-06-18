/*****************************************************************************

         This file is a part of PSD (Parallel Structural Dynamics)

     -------------------------------------------------------------------

     Author(s): Mohd Afeef Badri
     Email    : mohd-afeef.badri@cea.com
     Date     : 2018‑05‑29

     -------------------------------------------------------------------

     PSD a parallel  finite  element framework  provides tools to  solve 
     multiple  solid-dynamic  problems; PSD is distributed  in  the hope 
     that it will be useful, but WITHOUT ANY WARRANTY; or  without  even  
     the implied warranty of  FITNESS  FOR  A  PARTICULAR  PURPOSE.

*******************************************************************************/


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

//=============================================================================
// --- Max of two vectors--
//=============================================================================

double GFPmaxintwoP1(KN<double> *const & f, KN<double> *const & f1)   
{
  long int nn = f->N();
  for(long int i=0; i<nn; i++) 
   {    
   *(f[0]+i)=max(*(f1[0]+i),*(f[0]+i));
   }
  return 0.0;
}

//=============================================================================
// --- Computation of eigenvalues and eigenvectors of a real symmetric matrix--
//=============================================================================

long lapack_dsyev (KNM<double> *const &A, KN<double> *const &vp, KNM<double> *const &vectp) 
{


	KNM<double> mat(*A)      ;   // cast matrix 
	KN<double>  w(1)         ;   // lapack variable 
	intblas     info         ,   // variable to fetch error 
	            lw   = -1    ;   // lapack variable     
	char        JOBZ = 'V'   ,   // 'V' means compute eigenvalues and vectors
	            UPLO = 'U'   ;   // 'U' means upper triangular
	intblas     n    = A->N();   // n is matrix order

  // http://www.netlib.org/lapack/explore-html/d2/d8a/group__double_s_yeigen_ga442c43fca5493590f8f26cf42fed4044.html#ga442c43fca5493590f8f26cf42fed4044
  // FUNCTION DSYEV( JOBZ, UPLO, N, A, LDA, W, WORK, LWORK, INFO )
  //  JOBZ    (input) CHARACTER*1
  //          = 'N':  Compute eigenvalues only;
  //          = 'V':  Compute eigenvalues and eigenvectors.
  //
  //  UPLO    (input) CHARACTER*1
  //          = 'U':  Upper triangle of A is stored;
  //          = 'L':  Lower triangle of A is stored.
  //
  //  N       (input) INTEGER
  //          The order of the matrix A.  N >= 0.
  //
  //  A       (input/output) DOUBLE PRECISION array, dimension (LDA, N)
  //          On entry, the symmetric matrix A.  If UPLO = 'U', the
  //          leading N-by-N upper triangular part of A contains the
  //          upper triangular part of the matrix A.  If UPLO = 'L',
  //          the leading N-by-N lower triangular part of A contains
  //          the lower triangular part of the matrix A.
  //          On exit, if JOBZ = 'V', then if INFO = 0, A contains the
  //          orthonormal eigenvectors of the matrix A.
  //          If JOBZ = 'N', then on exit the lower triangle (if UPLO='L')
  //          or the upper triangle (if UPLO='U') of A, including the
  //          diagonal, is destroyed.
  //
  //  LDA     (input) INTEGER
  //          The leading dimension of the array A.  LDA >= max(1,N).
  //
  //  W       (output) DOUBLE PRECISION array, dimension (N)
  //          If INFO = 0, the eigenvalues in ascending order.
  //
  //  WORK    (workspace/output) DOUBLE PRECISION array, dimension (MAX(1,LWORK))
  //          On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
  //
  //  LWORK   (input) INTEGER
  //          The length of the array WORK.  LWORK >= max(1,3*N-1).
  //          For optimal efficiency, LWORK >= (NB+2)*N,
  //          where NB is the blocksize for DSYTRD returned by ILAENV.
  //
  //          If LWORK = -1, then a workspace query is assumed; the routine
  //          only calculates the optimal size of the WORK array, returns
  //          this value as the first entry of the WORK array, and no error
  //          message related to LWORK is issued by XERBLA.
  //
  //  INFO    (output) INTEGER
  //          = 0:  successful exit
  //          < 0:  if INFO = -i, the i-th argument had an illegal value
  //          > 0:  if INFO = i, the algorithm failed to converge; i
  //                off-diagonal elements of an intermediate tridiagonal
  //                form did not converge to zero.
  //
   	     
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


//=============================================================================
// --- Computation of eigenvalues and eigenvectors of a real symmetric matrix--
//=============================================================================

long lapack_dsyevAlone (KNM<double> *const &A, KN<double> *const &vp) {


	KNM<double> mat(*A)      ;   // cast matrix 
	KN<double>  w(1)         ;   // lapack variable 
	intblas     info         ,   // variable to fetch error 
	            lw   = -1    ;   // lapack variable     
	char        JOBZ = 'N'   ,   // 'V' means compute eigenvalues and vectors
	            UPLO = 'U'   ;   // 'U' means upper triangular
	intblas     n    = A->N();   // n is matrix order
	
  // http://www.netlib.org/lapack/explore-html/d2/d8a/group__double_s_yeigen_ga442c43fca5493590f8f26cf42fed4044.html#ga442c43fca5493590f8f26cf42fed4044
  // FUNCTION DSYEV( JOBZ, UPLO, N, A, LDA, W, WORK, LWORK, INFO )
  //  JOBZ    (input) CHARACTER*1
  //          = 'N':  Compute eigenvalues only;
  //          = 'V':  Compute eigenvalues and eigenvectors.
  //
  //  UPLO    (input) CHARACTER*1
  //          = 'U':  Upper triangle of A is stored;
  //          = 'L':  Lower triangle of A is stored.
  //
  //  N       (input) INTEGER
  //          The order of the matrix A.  N >= 0.
  //
  //  A       (input/output) DOUBLE PRECISION array, dimension (LDA, N)
  //          On entry, the symmetric matrix A.  If UPLO = 'U', the
  //          leading N-by-N upper triangular part of A contains the
  //          upper triangular part of the matrix A.  If UPLO = 'L',
  //          the leading N-by-N lower triangular part of A contains
  //          the lower triangular part of the matrix A.
  //          On exit, if JOBZ = 'V', then if INFO = 0, A contains the
  //          orthonormal eigenvectors of the matrix A.
  //          If JOBZ = 'N', then on exit the lower triangle (if UPLO='L')
  //          or the upper triangle (if UPLO='U') of A, including the
  //          diagonal, is destroyed.
  //
  //  LDA     (input) INTEGER
  //          The leading dimension of the array A.  LDA >= max(1,N).
  //
  //  W       (output) DOUBLE PRECISION array, dimension (N)
  //          If INFO = 0, the eigenvalues in ascending order.
  //
  //  WORK    (workspace/output) DOUBLE PRECISION array, dimension (MAX(1,LWORK))
  //          On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
  //
  //  LWORK   (input) INTEGER
  //          The length of the array WORK.  LWORK >= max(1,3*N-1).
  //          For optimal efficiency, LWORK >= (NB+2)*N,
  //          where NB is the blocksize for DSYTRD returned by ILAENV.
  //
  //          If LWORK = -1, then a workspace query is assumed; the routine
  //          only calculates the optimal size of the WORK array, returns
  //          this value as the first entry of the WORK array, and no error
  //          message related to LWORK is issued by XERBLA.
  //
  //  INFO    (output) INTEGER
  //          = 0:  successful exit
  //          < 0:  if INFO = -i, the i-th argument had an illegal value
  //          > 0:  if INFO = i, the algorithm failed to converge; i
  //                off-diagonal elements of an intermediate tridiagonal
  //                form did not converge to zero.
  //
	
	dsyev_(&JOBZ, &UPLO, &n, mat, &n, *vp, w, &lw, &info);
	lw = w[0];
	w.resize(lw);
	
	dsyev_(&JOBZ, &UPLO, &n, mat, &n, *vp, w, &lw, &info);
	
	if (info < 0) {
		cout << " LAPACK ERROR  dsyev: the " << info << "-th argument had an illegal value." << endl;
	} else if (info > 0) {
		cout << " LAPACK ERROR  dsyev: the algorithm failed to converge." << endl;
	}

	return info;
}
  

//=============================================================================
// --- Update phase for dunamic solver --
//=============================================================================

template<class K>
class updatedynamic_Op : public E_F0mps {
    public:
        Expression du					  ;
        Expression uold					;
        Expression vold					;
        Expression aold					;
        Expression beta					;                
        Expression gamma				;
        Expression dt					  ;  
              
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


//=============================================================================
// --- Split the compressive and tensile energies and update history --
//=============================================================================

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
    double bet  = GetAny<double>((*beta)(stack))	;
    double gam  = GetAny<double>((*gamma)(stack))	;
    double ddt  = GetAny<double>((*dt)(stack))		;

    double anew						                        ;
    
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
        Expression exy				;
        Expression Hp					;
        Expression Hm					;                
        Expression Hout					;
        Expression Hout1				;
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
        		Expression param8		,
        		Expression param9		        		        				        		        		
        		) : 
        		ex     (param1)			, 
        		ey     (param2)			, 
        		exy    (param3)			,  
        		Hp     (param4)			,
        		Hm     (param5)			, 
        		Hout   (param6)			,
        		Hout1  (param7)			,
        		lambda (param8)			,
        		mu     (param9)	        		        				        		        		 
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
            				  t[7]->CastTo(args[7]),
            				  t[8]->CastTo(args[8])            				              				  
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
    KN<K>* out4 = GetAny<KN<K>*>((*Hout1)(stack))	;       
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
        out4->operator[](j) = min(out4->operator[](j),out2->operator[](j));
     }
          
    return 0L;
}


//=============================================================================
// ------- class for 2D/3D energy splitting function ---------
//=============================================================================
template<class K>
class SplitEnergy_Op : public E_F0mps {
    public:
        Expression epsilon	  ;          // Input 1 : strain vector
        Expression psiPlus		;          // Input 2 : tensile energy     
        Expression psiMinus		;          // Input 3 : compressible energy             
        Expression HPlus			;          // Input 4 : historic max of Input 2
        Expression HMinus			;          // Input 5 : historic min of Input 3
        Expression constants	;          // Input 6 : Lambda and mu as vector 
              
        static const int n_name_param = 0		;
        static basicAC_F0::name_and_type name_param[]	;
        Expression nargs[n_name_param]			;
        
        SplitEnergy_Op(const basicAC_F0& args		, 
        		Expression param1		, 
        		Expression param2		, 
        		Expression param3		, 
        		Expression param4		,
        		Expression param5		,
        		Expression param6		       		        				        		        		
        		) : 
        		epsilon     (param1)			, 
        		psiPlus     (param2)			, 
        		psiMinus    (param3)			,  
        		HPlus       (param4)			,
        		HMinus      (param5)			, 
        		constants   (param6)			        		        				        		        		 
        		{
            		args.SetNameParam(n_name_param	, 
            				  name_param	, 
            				  nargs
            				  )		;
        		}
        		
        AnyType operator()(Stack stack) const		;
};

template<class K>
basicAC_F0::name_and_type SplitEnergy_Op<K>::name_param[] = { };

template<class K>
class SplitEnergy : public OneOperator {
    public:
        SplitEnergy() : OneOperator(atype<long>()	, 
        			     atype<KN<K>*>()	, 
        			     atype<KN<K>*>()	, 
        			     atype<KN<K>*>()  ,
        			     atype<KN<K>*>()  ,
        			     atype<KN<K>*>()  ,
        			     atype<KN<K>*>() 	
        			     ) {}

        E_F0* code(const basicAC_F0& args) const {
            return new SplitEnergy_Op<K>(args, 
            				  t[0]->CastTo(args[0]), 
            				  t[1]->CastTo(args[1]), 
            				  t[2]->CastTo(args[2]), 
            				  t[3]->CastTo(args[3]),
            				  t[4]->CastTo(args[4]),
            				  t[5]->CastTo(args[5])           				              				  
            				  );
        }
};

template<class K>
AnyType SplitEnergy_Op<K>::operator()(Stack stack) const {
    KN<K>* Eps    = GetAny<KN<K>*>((*epsilon)(stack))		;
    KN<K>* pPlus  = GetAny<KN<K>*>((*psiPlus)(stack))		;
    KN<K>* pMinus = GetAny<KN<K>*>((*psiMinus)(stack))  ;
    KN<K>* Hp     = GetAny<KN<K>*>((*HPlus)(stack))		  ;
    KN<K>* Hm     = GetAny<KN<K>*>((*HMinus)(stack))		;
    KN<K>* Prpty  = GetAny<KN<K>*>((*constants)(stack))	; 

    // Extract Lambda & mu from property vector
    double lambda = Prpty->operator[](0);
    double mu     = Prpty->operator[](1); 
       
    // Get dimension of the problem 2 or 3 
    int problemDimension = Eps->n/Hp->n;
    problemDimension = problemDimension/3 + 1;
    
    KNM<double> Amat(problemDimension,problemDimension);
    KN<double>  eval(problemDimension);

    intblas n = problemDimension;
    char JOBZ = 'N', UPLO = 'U';
    intblas info, lw = -1;
    KN<double> w(1);
    dsyev_(&JOBZ, &UPLO, &n, Amat, &n, eval, w, &lw, &info);
    lw = w[0];
    w.resize(lw);

 //   int    probDimP1   = problemDimension + 1;  // BUG  BUG  BUG  BUG  BUG
	   
    if(problemDimension==2)
	    {
	    double d1,d2;      
	    	  
	    int indexEx, 
	        indexEy, 
	        indexExy; 
	        
      for(int j = 0; j < pPlus->n; ++j)
       {
        
  //      indexEx  = j*probDimP1;   // BUG  BUG  BUG  BUG  BUG
        indexEx  = j*3;  
        indexEy  = indexEx + 1;
        indexExy = indexEx + 2;

        pPlus->operator[](j) = max(0.,double(Eps->operator[](indexEx)+Eps->operator[](indexEy)));
        pPlus->operator[](j) = 0.5*lambda*pPlus->operator[](j)*pPlus->operator[](j);
                
        pMinus->operator[](j) = min(0.,double(Eps->operator[](indexEx)+Eps->operator[](indexEy)));
        pMinus->operator[](j) = 0.5*lambda*pMinus->operator[](j)*pMinus->operator[](j);        
               
        Amat(0,0)=Eps->operator[](indexEx); 
        Amat(0,1)=Eps->operator[](indexExy);
        Amat(1,1)=Eps->operator[](indexEy);
        
	      dsyev_(&JOBZ, &UPLO, &n, Amat, &n, eval, w, &lw, &info);

        d1=max(0.,eval[0]);
        d2=max(0.,eval[1]);
        pPlus->operator[](j) += mu*(d1*d1 + d2*d2);
        
        d1=min(0.,eval[0]);
        d2=min(0.,eval[1]);
        pMinus->operator[](j) += mu*(d1*d1 + d2*d2);
        
        Hp->operator[](j) = max(Hp->operator[](j),pPlus->operator[](j));
        Hm->operator[](j) = min(Hm->operator[](j),pMinus->operator[](j));         
       }
      }
    
    if(problemDimension==3)
	    {  
	    double d1,d2,d3;
	    int indexEx, 
	        indexEy, 
	        indexEz,
	        indexExy, 
	        indexExz, 	        	         
	        indexEyz; 
      for(int j = 0; j < pPlus->n; ++j)
       {
  
      //      indexEx  = j*probDimP1;   // BUG  BUG  BUG  BUG  BUG  
	      indexEx  = j*6; 
	      indexEy  = indexEx + 1;  
	      indexEz  = indexEx + 2; 
	      indexExy = indexEx + 3;
	      indexExz = indexEx + 4; 	        	         
	      indexEyz = indexEx + 5; 
	        
	                        
        pPlus->operator[](j) = max(0.,double(Eps->operator[](indexEx)+Eps->operator[](indexEy)+Eps->operator[](indexEz)));
        pPlus->operator[](j) = 0.5*lambda*pPlus->operator[](j)*pPlus->operator[](j);

        pMinus->operator[](j) = min(0.,double(Eps->operator[](indexEx)+Eps->operator[](indexEy)+Eps->operator[](indexEz)));
        pMinus->operator[](j) = 0.5*lambda*pMinus->operator[](j)*pMinus->operator[](j);
        
        Amat(0,0)=Eps->operator[](indexEx); 
        Amat(1,1)=Eps->operator[](indexEy);
        Amat(2,2)=Eps->operator[](indexEz);
        Amat(0,1)=Eps->operator[](indexExy);
        Amat(0,2)=Eps->operator[](indexExz);
        Amat(1,2)=Eps->operator[](indexEyz);
        
	      dsyev_(&JOBZ, &UPLO, &n, Amat, &n, eval, w, &lw, &info);

        d1=max(0.,eval[0]);
        d2=max(0.,eval[1]);
        d3=max(0.,eval[2]);

        pPlus->operator[](j) += mu*(d1*d1 + d2*d2 + d3*d3);
        
        d1=min(0.,eval[0]);
        d2=min(0.,eval[1]);
        d3=min(0.,eval[2]);

        pMinus->operator[](j) += mu*(d1*d1 + d2*d2 + d3*d3);
        

        Hp->operator[](j) = max(Hp->operator[](j),pPlus->operator[](j));
        Hm->operator[](j) = min(Hm->operator[](j),pMinus->operator[](j));         
       }
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
        Expression Hp					  ;
        Expression Hm					  ;                
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

    int tempindex=Ex->n/out1->n;
    int tempindex0 = tempindex;
    int tempcount=0; 
    tempindex = tempindex/3 + 1;
    double tmpeqStrain; 
    
    
    KNM<double> Amat(tempindex,tempindex)   ;		// Amat is infact strain matrix
    KN<double>  eval(tempindex)             ;		// To store eigenvalues
    intblas n = tempindex                   ;		// Blas integer
    char JOBZ = 'N', UPLO = 'U';			// Upper triangular
    intblas info, lw = -1;
    KN<double> w(1);
    dsyev_(&JOBZ, &UPLO, &n, Amat, &n, eval, w, &lw, &info);
    lw = w[0];
    w.resize(lw);
    

  
    for(int j = 0; j < out1->n; ++j){
        tempcount=0;
        for (int ii=0 ; ii<tempindex; ii++ ){
    	for (int jj=ii; jj<tempindex; jj++ ){
    		Amat(ii,jj)=Ex->operator[](tempindex0*j+(tempcount)) ;
    		tempcount++;
    	}}	    
   	 
    /*
        //--------------------------------------------------------------------------
        //  -------- OLD LOGIC -----------
        //--------------------------------------------------------------------------
        Amat(0,0)=Ex->operator[](3*j+0) ; 				// Strain xx
        Amat(0,1)=Ex->operator[](3*j+2);       				// Strain xy        
        Amat(1,1)=Ex->operator[](3*j+1) ;				// Strain yy 
   */
        
	dsyev_(&JOBZ, &UPLO, &n, Amat, &n, eval, w, &lw, &info);  // Calculate Eigenvalues--> eval	
	
	tmpeqStrain=0.;
	for (int ii=0 ; ii<tempindex; ii++ )
		tmpeqStrain += pow((max(0.,eval[ii])),2);
	tmpeqStrain=sqrt(tmpeqStrain);
    /*
        //--------------------------------------------------------------------------
        //  -------- OLD LOGIC -----------
        //--------------------------------------------------------------------------	
	tmpeqStrain=sqrt(pow((max(0.,eval[0])),2) + pow((max(0.,eval[1])),2))  ; 
    */	
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
  Global.Add("GFPSplitEnergy", "(", new SplitEnergy<double>);
  Global.Add("GFPMazarsDamageUpdate", "(", new MazarsDamageUpdate<double>);
  Global.Add("GFPmaxintwoFEfields","(",new OneOperator2_<double,KN<double>*, KN<double>*>(GFPmaxintwoP1));		
  Global.Add("GFPeigen", "(", new OneOperator3_<long, KNM<double> *, KN<double> *, KNM<double> *>(lapack_dsyev));
  Global.Add("GFPeigenAlone", "(", new OneOperator2_<long, KNM<double> *, KN<double> *>(lapack_dsyevAlone));  

}
LOADFUNC(InitFF)   
