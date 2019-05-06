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

double GFPadd( long no1,double no2)
{
  return no1+no2;
}
  
double GFPmaxintwoP1(KN<double> *const & f, KN<double> *const & f1)   
{
    long int nn = f->N();
    for(long int i=0; i<nn; i++) {    
      *(f[0]+i)=max(*(f1[0]+i),*(f[0]+i));
    }
  return 0.0;
}

  
static void InitFF()
{
  Global.Add("GFPadd","(",new OneOperator2<double, long,double>(GFPadd));
  Global.Add("GFPmaxintwoFEfields","(",new OneOperator2_<double,KN<double>*, KN<double>*>(GFPmaxintwoP1));		
  Global.Add("GFPeigen", "(", new OneOperator3_<long, KNM<double> *, KN<double> *, KNM<double> *>(lapack_dsyev));
  Global.Add("GFPeigenAlone", "(", new OneOperator2_<long, KNM<double> *, KN<double> *>(lapack_dsyevAlone));  

}
LOADFUNC(InitFF)   
