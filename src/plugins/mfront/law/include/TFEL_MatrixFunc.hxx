#ifndef FLOISEAU_TFEL_MATRIXFUNC
#define FLOISEAU_TFEL_MATRIXFUNC 1

#include <cmath>

namespace tfel::math::extensions {
    /*
     * To improve this function: https://sourceforge.net/p/tfel/discussion/mechanicalbeahviours/thread/6abe71fe/
     * This is needed for desmorat20152d behaviour law
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
}

#endif /* FLOISEAU_TFEL_MATRIXFUNC */
