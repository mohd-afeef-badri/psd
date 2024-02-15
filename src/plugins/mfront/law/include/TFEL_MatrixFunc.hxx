#ifndef FLOISEAU_TFEL_MATRIXFUNC
#define FLOISEAU_TFEL_MATRIXFUNC 1

#include <cmath>

namespace tfel::math::extensions {
    /*
     * To improve this function: https://sourceforge.net/p/tfel/discussion/mechanicalbeahviours/thread/6abe71fe/
     * This is needed for desmorat20152d, desmorat20152dnonlocal, desmoratplanestressDelta behaviour laws
     * Implemented by Flavien Loiseau, ENS Paris-Saclay
     * flavien.loiseau@ens-paris-saclay.fr
     * Integrated with mfront and PSD by Breno Ribeiro Nogueira, ENS Paris-Saclay
     * bribeiro@ens-paris-saclay.fr 
     */

    template <typename real>
    stensor<2u,real> myInvert(const stensor<2u, real> &A) {
        // Make a local copy of A
        stensor<2u,real> ls(A);
        // Declare and compute eigenvalues and eigenvectors
        tvector<3u,real> vp;
        tmatrix<3u,3u,real> m;
        ls.computeEigenVectors(vp,m);
        // Compute eigentensors
        stensor<2u,real> n0,n1,n2;
        stensor<2u,real>::computeEigenTensors(n0,n1,n2,m);
        // Add terms associated to each eigenvalues
        if (vp(2) > 0.) {
            stensor<2u,real> func_A =
                1./vp(0) * n0 +
                1./vp(1) * n1 +
                1./vp(2) * n2;
            // Return the tensor
            return func_A;
        } else if (vp(1) > 0.) {
            stensor<2u,real> func_A =
                1./vp(0) * n0 +
                1./vp(1) * n1;
            // Return the tensor
            return func_A;
        } else if (vp(0)>0.) {
            stensor<2u,real> func_A =
                1./vp(0) * n0;
            // Return the tensor
            return func_A;
        } else {
            stensor<2u,real> func_A = 0. * n0;
            // Return the tensor
            return func_A;
        }

    }
    
    template <typename real>
    stensor<2u, real> compute_damage(const stensor<2u, real> &HD, 
    				     const real & alpha, const real & beta){
    	
    	// Make a local copy of HD
    	stensor<2u, real> ls(HD);
    	// Declare and compute eigenvalues and eigenvectors
    	tvector<3u, real> vp;
    	tmatrix<3u,3u, real> m;
    	ls.computeEigenVectors(vp,m);
    	//Compute eigentensors
    	stensor<2u, real> n0, n1, n2;
    	stensor<2u, real>::computeEigenTensors(n0, n1, n2, m);
    	// Add terms associated to each eigenvalues
    	real pi = 3.141592653589793;
    	stensor<2u, real> func_HD = (2./pi)*atan(pow(fabs(vp(0))/beta, alpha))*n0 +
    				    (2./pi)*atan(pow(fabs(vp(1))/beta, alpha))*n1 +
    				    (2./pi)*atan(pow(fabs(vp(2))/beta, alpha))*n2;
    	return func_HD;
    				     
    }

    template <typename real>
    stensor<2u, real> compute_ladeveze(const stensor<2u, real> &HD, 
    				     const real & puissance){
    	
    	// Make a local copy of HD
    	stensor<2u, real> ls(HD);
    	// Declare and compute eigenvalues and eigenvectors
    	tvector<3u, real> vp;
    	tmatrix<3u,3u, real> m;
    	ls.computeEigenVectors(vp,m);
    	//Compute eigentensors
    	stensor<2u, real> n0, n1, n2;
    	stensor<2u, real>::computeEigenTensors(n0, n1, n2, m);
    	// Add terms associated to each eigenvalues
    	real pi = 3.141592653589793;
    	stensor<2u, real> func_HD = (pow(fabs(vp(0)), puissance))*n0 +
    				    (pow(fabs(vp(1)), puissance))*n1 +
    				    (pow(fabs(vp(2)), puissance))*n2;
    	return func_HD;
    				     
    }

    template <typename real>
    stensor<2u, real> compute_damage_ln(const stensor<2u, real> &HD, 
    				     const real & alpha, const real & beta){
    	
    	// Make a local copy of HD
    	stensor<2u, real> ls(HD);
    	// Declare and compute eigenvalues and eigenvectors
    	tvector<3u, real> vp;
    	tmatrix<3u,3u, real> m;
    	ls.computeEigenVectors(vp,m);
    	//Compute eigentensors
    	stensor<2u, real> n0, n1, n2;
    	stensor<2u, real>::computeEigenTensors(n0, n1, n2, m);
    	// Add terms associated to each eigenvalues
    	stensor<2u, real> func_HD = (1-exp(-beta*pow(vp(0), alpha)))*n0 +
    				    (1-exp(-beta*pow(vp(1), alpha)))*n1 +
    				    (1-exp(-beta*pow(vp(2), alpha)))*n2;
    	return func_HD;
    				     
    }
}

#endif /* FLOISEAU_TFEL_MATRIXFUNC */
