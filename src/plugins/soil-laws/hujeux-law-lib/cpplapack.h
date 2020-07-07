#ifndef __CPPLAPACK_H
#define __CPPLAPACK_H

#ifdef __cplusplus
extern "C" {
#endif
/* Subroutine */ int dgetrf_(integer *m, integer *n, doublereal *a, integer *lda, integer *ipiv,
                             integer *info);
/* Subroutine */ int dgetri_(integer *n, doublereal *a, integer *lda, integer *ipiv,
                             doublereal *work, integer *lwork, integer *info);                             
#ifdef __cplusplus
}
#endif

#endif /* __CLAPACK_H */
