// General utilities for soil laws
// Developed by Evelyne FOERSTER - 2019

#include "stdafx.h"
//#include "utils.h"

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
double interpol(const double& y_before, const double& y_after,
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
inline double norm_sqr(const dvector& V)
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

inline bool operator==(const dvector& V, const dvector& W)
{
	dvector::const_iterator iv = V.begin(), vend = V.end(),
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
