// General utilities for soil laws
// Developed by Evelyne FOERSTER - 2019

#include "stdafx.h"

//-----------------------------------------
// Fonctions generales
//-----------------------------------------

dvector convertToVector(const double* vec, const int& nval)
{
	dvector newvec;
	for (int i = 0; i < nval; i++) newvec.push_back(vec[i]);
	return newvec;
}

// Interpolation lineaire de la valeur val_y = y(x), avec x dans [x_before,x_after]
// et y dans [y_before,y_after]
/*double interpol(const double& y_before, const double& y_after,
	const double& x, const double& x_before, const double& x_after)
{
	if (fabs(x - x_after) < TOL) return y_after;
	if (fabs(x - x_before) < TOL || fabs(x_before - x_after) < TOL) return y_before;

	double	coef = (x - x_before) / (x_after - x_before),
		b = 1. - coef,
		val_y = y_before,
		yy = y_after;

	val_y *= b;
	yy *= coef;
	val_y += yy;
	if (fabs(val_y) < TOL) val_y = 0.;

	return val_y;
}

void AfficheMessage(const char* lpszText)
{
	cerr << lpszText;

#ifdef _WIN32
	time_t debut, fin;
	time(&debut);
	while (difftime(time(&fin), debut) < TempsPause);
#endif //_WIN32
}

string makelower(const char* str)
{
	if (!str) return "";

	int l = 0, n = (int)strlen(str);
	string news(str);
	char c;

	while (l < n)
	{
		c = news[l];
		if (!isdigit(c)) c = (char)tolower(c);
		news[l++] = c;
	}
	return news;
}
*/
//-----------------------------------------
// operation on vectors double (STL)
//-----------------------------------------

inline dvector operator-(const dvector& V, const dvector& W)
{
	dvector newv;
	auto iv = V.begin(), vend = V.end(),
		iw = W.begin(), wend = W.end();

	for (; iv != vend && iw != wend; iv++, iw++) newv.push_back(*iv - *iw);
	return newv;
}

inline dvector operator+(const dvector& V, const dvector& W)
{
	dvector newv;
	auto iv = V.begin(), vend = V.end(),
		iw = W.begin(), wend = W.end();

	for (; iv != vend && iw != wend; iv++, iw++) newv.push_back(*iv + *iw);
	return newv;
}

inline dvector operator+(const dvector& V, const double& x)
{
	dvector newv;
	auto iv = V.begin(), vend = V.end();

	for (; iv != vend; iv++) newv.push_back(*iv + x);
	return newv;
}

inline dvector operator-(const dvector& V, const double& x)
{
	dvector newv;
	auto iv = V.begin(), vend = V.end();

	for (; iv != vend; iv++) newv.push_back(*iv - x);
	return newv;
}

inline dvector operator+(const double& x, const dvector& V)
{
	return (V + x);
}

inline dvector operator-(const double& x, const dvector& V)
{
	dvector newv;
	auto iv = V.begin(), vend = V.end();

	for (; iv != vend; iv++) newv.push_back(x - *iv);
	return newv;
}

inline dvector operator/(const dvector& V, const double& x)
{
	auto vstart = V.begin(), vend = V.end(), iv = vstart;
	dvector newv;
	double ix = x;
	if (x < EPS) ix = EPS * signe(x);
	ix = 1 / ix;

	while (iv != vend)
	{
		newv.push_back(*iv * ix);
		iv++;
	}
	return newv;
}

inline dvector operator*(const dvector& V, const double& x)
{
	auto vstart = V.begin(), vend = V.end(), iv = vstart;
	dvector newv;

	while (iv != vend)
	{
		newv.push_back(*iv * x);
		iv++;
	}
	return newv;
}

inline dvector operator*(const double& x, const dvector& V)
{
	return (V * x);
}

// Scalar (dot) product
inline double dot(const dvector& V, const dvector& W)
{
	double init = 0.;
	return inner_product(V.begin(), V.end(), W.begin(), init);
}

// Euclidian norm
inline double norm(const dvector& V)
{
	return sqrt(dot(V,V));
}

// square Euclidian norm
/*inline double norm_sqr(const dvector& V)
{
	return dot(V, V);
}

// Euclidian distance
inline double dist(const dvector& V, const dvector& W)
{
	return norm(V - W);
}

inline double dist_sqr(const dvector& V, const dvector& W)
{
	return norm_sqr(V - W);
}

// Vectorial product
inline dvector vect_prod(const dvector& V, const dvector& W)
{
	dvector newv(3);
	newv[0] = V[1] * W[2] - V[2] * W[1];
	newv[1] = V[2] * W[0] - V[0] * W[2];
	newv[2] = V[0] * W[1] - V[1] * W[0];
	return newv;
}
*/
inline bool operator==(const dvector& V, const dvector& W)
{
	auto iv = V.begin(), vend = V.end(),
		iw = W.begin(), wend = W.end();

	for (; iv != vend && iw != wend; iv++, iw++)
	{
		if (fabs(*iv - *iw) > EPS) return false;
	}
	return true;
}

inline bool operator!=(const dvector& V, const dvector& W)
{
	return !(V == W);
}

/////////////////////////////////////////////////////////////////////////////
// Resolution of A.X = B, where A(n,n), X(n) and B(n)
// by gaussian elimination => inverse matrix stored in A, solution stored in x
//
void gauss(double** a, double* b, double* x, const int& n)
{
	double	r = 0., s = 0.;
	int		i = 0, j = 0, k = 0;

	for (k = 0; k < n - 1; k++)
	{
		for (i = k + 1; i < n; i++)
		{
			r = a[i][k] / a[k][k];
			for (j = k + 1; j < n; j++) a[i][j] -= r * a[k][j];
			b[i] -= r * b[k];
		}
	}

	x[n - 1] = b[n - 1] / a[n - 1][n - 1];

	for (k = n - 2; k >= 0; k--)
	{
		s = b[k];
		for (j = k + 1; j < n; j++) s -= a[k][j] * x[j];
		x[k] = s / a[k][k];
	}
}


/////////////////////////////////////////////////////////////////////////////
// General operations on Real2, Real3, etc. classes
//
/*---------------------------------------------------------------------------*/
inline Real2 operator+(const Real2& a, const Real2& b)
{
    return Real2(a.x+b.x,a.y+b.y);
}

/*---------------------------------------------------------------------------*/
inline Real2 operator*(const Real2& n, const double& b)
{
    return Real2(n.x * b, n.y * b);
}

/*---------------------------------------------------------------------------*/
inline Real2 operator/(const Real2& n, const double& b)
{
    Real2 newn;
    double ib = (fabs(b) >= EPS ? 1 / b : 1 / EPS);
    return Real2(n.x * ib,n.y * ib);
}

/*---------------------------------------------------------------------------*/
inline Real2 operator*(const double& b, const Real2& n)
{
    return Real2(n.x * b, n.y * b);
}
/*---------------------------------------------------------------------------*/
inline Real3 vec_prod(const Real3& v1, const Real3& v2)
{
    Real3 v;
    v.x = v1.y * v2.z - v1.z * v2.y;
    v.y = v2.x * v1.z - v2.z * v1.x;
    v.z = v1.x * v2.y - v1.y * v2.x;
    return v;
}

/*---------------------------------------------------------------------------*/
inline double dot(const Real3& v1, const Real3& v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

/*---------------------------------------------------------------------------*/
inline double norm_sqr(const Real3& v)
{
    return dot(v,v);
}

/*---------------------------------------------------------------------------*/
inline Real3 operator+(double sca, const Real3& vec)
{
    return Real3(vec.x + sca, vec.y + sca, vec.z + sca);
}

/*---------------------------------------------------------------------------*/
inline Real3 operator+(const Real3& vec, double sca)
{
    return (sca + vec);
}

/*---------------------------------------------------------------------------*/
inline Real3 operator-(double sca, const Real3& vec)
{
    return Real3(vec.x - sca, vec.y - sca, vec.z - sca);
}

/*---------------------------------------------------------------------------*/
inline Real3 operator-(const Real3& vec, double sca)
{
    return Real3(sca - vec.x, sca - vec.y, sca - vec.z);
}

/*---------------------------------------------------------------------------*/
inline Real3 operator*(double sca, const Real3& vec)
{
    return Real3(vec.x * sca, vec.y * sca, vec.z * sca);
}

/*---------------------------------------------------------------------------*/
inline Real3 operator*(const Real3& vec, double sca)
{
    return sca * vec;
}

/*---------------------------------------------------------------------------*/
inline Real3 operator/(const Real3& vec, double sca)
{
    return Real3(vec.x / sca, vec.y / sca, vec.z / sca);
}

/*---------------------------------------------------------------------------*/
inline bool operator<(const Real3& v1, const Real3& v2)
{
    if (v1.x == v2.x) {
        if (v1.y == v2.y)
            return v1.z < v2.z;
        else
            return v1.y < v2.y;
    }
    return (v1.x < v2.x);
}
/*---------------------------------------------------------------------------*/
inline Real3x3 operator*(double sca, const Real3x3& vec)
{
    return Real3x3(vec.x * sca, vec.y * sca, vec.z * sca);
}

/*---------------------------------------------------------------------------*/
inline Real3x3 operator*(const Real3x3& vec, double sca)
{
    return Real3x3(vec.x * sca, vec.y * sca, vec.z * sca);
}

/*---------------------------------------------------------------------------*/
inline Real3x3 operator/(const Real3x3& vec, double sca)
{
    return Real3x3(vec.x / sca, vec.y / sca, vec.z / sca);
}

/*---------------------------------------------------------------------------*/
inline bool operator<(const Real3x3& v1, const Real3x3& v2)
{
    if (v1.x == v2.x) {
        if (v1.y == v2.y)
            return v1.z < v2.z;
        else
            return v1.y < v2.y;
    }
    return (v1.x < v2.x);
}

/*---------------------------------------------------------------------------*/
inline Real3x3 tensor_prod(Real3 u,Real3 v)
{
    Real3x3 mat;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            mat[i][j] = u[i] * v[j];

    return mat;
}

/*---------------------------------------------------------------------------*/
inline Real3x3 matrix3x3Transpose(const Real3x3& m)
{
    return Real3x3::fromColumns(m.x.x, m.x.y, m.x.z,
                                m.y.x, m.y.y, m.y.z,
                                m.z.x, m.z.y, m.z.z);
}

/*---------------------------------------------------------------------------*/
inline Real3 matrix3x3GetDiagonal(Real3x3 mat)
{
    return Real3(mat[0][0], mat[1][1], mat[2][2]);
}

/*---------------------------------------------------------------------------*/
inline void matrix3x3SetDiagonal(Real3x3& mat, Real3 vec)
{
    mat[0][0] = vec[0];
    mat[1][1] = vec[1];
    mat[2][2] = vec[2];
}

/*---------------------------------------------------------------------------*/
inline Real3 matrix3x3GetSupOutdiagonal(Real3x3 mat)
{
    return Real3(mat[0][1], mat[0][2], mat[1][2]);
}

/*---------------------------------------------------------------------------*/
inline void matrix3x3SetSupOutdiagonal(Real3x3& mat, Real3 vec)
{
    mat[0][1] = vec[0];
    mat[0][2] = vec[1];
    mat[1][2] = vec[2];
}

/*---------------------------------------------------------------------------*/
inline Real3 matrix3x3GetLowOutdiagonal(Real3x3 mat)
{
    return Real3(mat[1][0], mat[2][0], mat[2][1]);
}

/*---------------------------------------------------------------------------*/
inline void matrix3x3SetLowOutdiagonal(Real3x3& mat, const Real3& vec)
{
    mat[1][0] = vec[0];
    mat[2][0] = vec[1];
    mat[2][1] = vec[2];
}

/*---------------------------------------------------------------------------*/
inline Real3x3 diagonalMatrix3x3(Real3x3 mat)
{
    Real3x3 newmat;
    newmat[0][0] = mat[0][0];
    newmat[1][1] = mat[1][1];
    newmat[2][2] = mat[2][2];
    return newmat;
}

/*---------------------------------------------------------------------------*/
inline Real3x3 outdiagonalMatrix3x3(const Real3x3& mat)
{
    return (mat - diagonalMatrix3x3(mat));
}

/*---------------------------------------------------------------------------*/
inline bool	matrix3x3IsSymmetric(const Real3x3& mat)
{
    Real3 matsup = matrix3x3GetSupOutdiagonal(mat);
    Real3 matlow = matrix3x3GetLowOutdiagonal(mat);

    return (matsup == matlow);
}

/*---------------------------------------------------------------------------*/
inline double trace(Real3x3 mat)
{
    return (mat[0][0] + mat[1][1] + mat[2][2]);
}

/*---------------------------------------------------------------------------*/
inline dvector convertMatrix3x3ToVector(Real3x3 mat)
{
    dvector vec(6);
    int i;

    for (i = 0; i < 3; i++) vec[i] = mat[i][i];
    for (i = 3; i < 5; i++) vec[i] = mat[0][i - 2];
    vec[5] = mat[1][2];
    return vec;
}

/*---------------------------------------------------------------------------*/
inline Real3x3 convertVectorToMatrix3x3(dvector vec)
{
    Real3x3 mat;
    int i;

    for (i = 0; i < 3; i++) mat[i][i] = vec[i];
    for (i = 3; i < 5; i++)
    {
        mat[0][i - 2] = vec[i];
        mat[i - 2][0] = vec[i];
    }
    mat[1][2] = mat[2][1] = vec[5];

    return mat;
}

/*---------------------------------------------------------------------------*/
inline double trace(Tensor2 t) {
    return (t.m_vec[0] + t.m_vec[1] + t.m_vec[2]);
}

/*---------------------------------------------------------------------------*/
inline Tensor2 operator+(const Tensor2& t1,const Tensor2& t2) {
    dvector vec = t1.m_vec + t2.m_vec;
    return Tensor2(vec);
}

/*---------------------------------------------------------------------------*/
inline bool operator==(const Tensor2& t1, const Tensor2& t2) {
    return (t1.m_vec == t2.m_vec);
}

/*---------------------------------------------------------------------------*/
inline bool operator!=(const Tensor2& t1, const Tensor2& t2) {
    return (t1.m_vec != t2.m_vec);
}

/*---------------------------------------------------------------------------*/
inline Tensor2 operator*(const Tensor2& t1,const double& x) {
    return Tensor2(t1.m_vec * x);
}



