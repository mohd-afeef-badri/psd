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

//////////////////////////////////////////////////////////////////////
// class Real2: 2D real vector same as Real3 from Arcane
//
Real2::Real2() { x = 0.0; y = 0.0; }
Real2::Real2(double ax, double ay) : x(ax), y(ay) {}
Real2::Real2(const Real2& f) { x = f.x; y = f.y; }

double Real2::operator[](int i) const {
    if (i < 0 || i >= 2) throw std::out_of_range("Vector indices out of range");
    return (&x)[i];
}

double& Real2::operator[](int i) {
    if (i < 0 || i >= 2) throw std::out_of_range("Vector indices out of range");
    return (&x)[i];
}

Real2& Real2::operator=(const Real2& f) {
    x = f.x; y = f.y;
    return (*this);
}

Real2& Real2::operator= (double v) {
    x = y = v; return (*this);
}

Real2 Real2::null() { return Real2(0., 0.); }
Real2 Real2::zero() { return Real2(0., 0.); }
Real2 Real2::identity() { return Real2(1., 1.); }

Real2 Real2::copy() const { return (*this); }
Real2& Real2::reset() { x = y = 0.; return (*this); }
Real2& Real2::assign(double ax, double ay) { x = ax; y = ay; return (*this); }
Real2& Real2::assign(Real2 f) { x = f.x; y = f.y; return (*this); }
double Real2::norm_sqr() const { return x * x + y * y; }
double Real2::norm() const { return sqrt(norm_sqr()); }

Real2& Real2::operator*= (double b) { x *= b; y *= b; return (*this); }
Real2& Real2::operator/= (double b) { x /= b; y /= b; return (*this); }
Real2& Real2::operator+= (const Real2& b) { x += b.x; y += b.y; return (*this); }
Real2& Real2::operator-= (const Real2& b) { x -= b.x; y -= b.y; return (*this); }
Real2& Real2::operator*= (const Real2& b) { x *= b.x; y *= b.y; return (*this); }
Real2& Real2::operator/= (const Real2& b) { x /= b.x; y /= b.y; return (*this); }
Real2 Real2::operator+(const Real2& b)  const { return Real2(x + b.x, y + b.y); }
Real2 Real2::operator-(const Real2& b)  const { return Real2(x - b.x, y - b.y); }
Real2 Real2::operator-() const { return Real2(-x, -y); }
Real2 Real2::operator*(const Real2& b) const { return Real2(x * b.x, y * b.y); }
Real2 Real2::operator/(const Real2& b) const { return Real2(x / b.x, y / b.y); }

Real2& Real2::normalize() {
    double d = norm();
    if (fabs(d) >= EPS)
        operator/=(d);
    return (*this);
}

bool Real2::isNearlyZero() const
{
    static double eps = 1.e-10;
    return (fabs(x) < eps && fabs(y) < eps);
}

bool Real2::operator==(const Real2& b) const { return (x == b.x && y == b.y); }
bool Real2::operator!=(const Real2& b) const { return !operator==(b); }

//////////////////////////////////////////////////////////////////////
// class Real3: 3D real vector same as Real3 from Arcane
//
Real3::Real3() { x = 0.0; y = 0.0; z = 0.0; }
Real3::Real3(double ax, double ay, double az): x(ax),y(ay),z(az) {}
Real3::Real3(const Real3& f) { x = f.x; y = f.y; z = f.z; }

double Real3::operator[](int i) const
{
    if (i < 0 || i >= 3) throw std::out_of_range("Vector indices out of range");
    return (&x)[i];
}

double& Real3::operator[](int i)
{
    if (i < 0 || i >= 3) throw std::out_of_range("Vector indices out of range");
    return (&x)[i];
}

Real3& Real3::operator=(const Real3& f) { x = f.x; y = f.y; z = f.z; return (*this); }
Real3& Real3::operator= (double v) { x = y = z = v; return (*this); }
Real3 Real3::null() { return Real3(0., 0., 0.); }
Real3 Real3::zero() { return Real3(0., 0., 0.); }
Real3 Real3::identity() { return Real3(1., 1., 1.); }
Real3 Real3::copy() const { return (*this); }
Real3& Real3::reset() { x = y = z = 0.; return (*this); }
Real3& Real3::assign(double ax, double ay, double az) { x = ax; y = ay; z = az; return (*this); }
Real3& Real3::assign(const Real3& f) { x = f.x; y = f.y; z = f.z; return (*this); }
double Real3::norm_sqr() const { return x * x + y * y + z * z; }
double Real3::norm() const { return sqrt(norm_sqr()); }

Real3& Real3::operator+=(double b) { x += b;     y += b;     z += b;     return (*this); }
Real3& Real3::operator-=(double b) { x -= b;     y -= b;     z -= b;     return (*this); }
Real3& Real3::operator*=(double b) { x *= b;     y *= b;     z *= b;     return (*this); }
Real3& Real3::operator/=(double b) { x /= b;     y /= b;     z /= b;     return (*this); }
Real3& Real3::operator+= (const Real3& b) { x += b.x; y += b.y; z += b.z; return (*this); }
Real3& Real3::operator-= (const Real3& b) { x -= b.x; y -= b.y; z -= b.z; return (*this); }
Real3& Real3::operator*= (const Real3& b) { x *= b.x; y *= b.y; z *= b.z; return (*this); }
Real3& Real3::operator/= (const Real3& b) { x /= b.x; y /= b.y; z /= b.z; return (*this); }
Real3 Real3::operator+  (const Real3& b)  const { return Real3(x + b.x, y + b.y, z + b.z); }
Real3 Real3::operator-  (const Real3& b)  const { return Real3(x - b.x, y - b.y, z - b.z); }
Real3 Real3::operator-() const { return Real3(-x, -y, -z); }
Real3 Real3::operator*(const Real3& b) const { return Real3(x * b.x, y * b.y, z * b.z); }
Real3 Real3::operator/(const Real3& b) const { return Real3(x / b.x, y / b.y, z / b.z); }

Real3& Real3::normalize()
{
    double d = norm();
    if (fabs(d) >= EPS)
        operator/=(d);
    return (*this);
}

bool Real3::isNearlyZero() const
{
    static double eps = 1.e-10;
    return (fabs(x) < eps && fabs(y) < eps && fabs(z) < eps);
}

bool Real3::operator==(const Real3& b) const { return (x == b.x && y == b.y && z == b.z); }
bool Real3::operator!=(const Real3& b) const { return !operator==(b); }

//////////////////////////////////////////////////////////////////////
// class Real3x3: Matrix 3x3 same as Real3x3 from Arcane
//

Real3x3::Real3x3(): x(Real3::zero()), y(Real3::zero()), z(Real3::zero()) {}
Real3x3::Real3x3(const Real3& ax, const Real3& ay, const Real3& az): x(ax), y(ay), z(az) {}
Real3x3::Real3x3(const Real3x3& f): x(f.x), y(f.y), z(f.z) {}

Real3x3& Real3x3::operator=(const Real3x3& f) { x = f.x; y = f.y; z = f.z; return (*this); }
Real3x3& Real3x3::operator= (double v) { x = y = z = v; return (*this); }

Real3x3 Real3x3::null() { return Real3x3(); }
Real3x3 Real3x3::zero() { return Real3x3(); }
Real3x3 Real3x3::identity() { return Real3x3(Real3(1.0, 0.0, 0.0), Real3(0.0, 1.0, 0.0), Real3(0.0, 0.0, 1.0)); }

Real3x3 Real3x3::fromColumns(double ax, double ay, double az, double bx, double by, double bz, double cx, double cy, double cz)
{
    return Real3x3(Real3(ax, bx, cx), Real3(ay, by, cy), Real3(az, bz, cz));
}

Real3x3 Real3x3::fromLines(double ax, double bx, double cx, double ay, double by, double cy, double az, double bz, double cz)
{
    return Real3x3(Real3(ax, bx, cx), Real3(ay, by, cy), Real3(az, bz, cz));
}

Real3x3 Real3x3::copy() const { return (*this); }

Real3x3& Real3x3::reset() { *this = zero(); return (*this); }

Real3x3& Real3x3::assign(const Real3& ax, const Real3& ay, const Real3& az)
{
    x = ax; y = ay; z = az; return (*this);
}

Real3x3& Real3x3::assign(const Real3x3& f)
{
    x = f.x; y = f.y; z = f.z; return (*this);
}

bool Real3x3::isNearlyZero() const
{
    return (x.isNearlyZero() && y.isNearlyZero() && z.isNearlyZero());
}

Real3x3& Real3x3::operator+=(const Real3& b) { x += b; y += b; z += b; return (*this); }
Real3x3& Real3x3::operator-=(const Real3& b) { x -= b; y -= b; z -= b; return (*this); }
Real3x3& Real3x3::operator+= (const Real3x3& b) { x += b.x; y += b.y; z += b.z; return (*this); }
Real3x3& Real3x3::operator-= (const Real3x3& b) { x -= b.x; y -= b.y; z -= b.z; return (*this); }
void Real3x3::operator*= (double b) { x *= b; y *= b; z *= b; }
void Real3x3::operator/= (double b) { x /= b; y /= b; z /= b; }
Real3x3 Real3x3::operator+(const Real3x3& b)  const { return Real3x3(x + b.x, y + b.y, z + b.z); }
Real3x3 Real3x3::operator-(const Real3x3& b)  const { return Real3x3(x - b.x, y - b.y, z - b.z); }
Real3x3 Real3x3::operator-() const { return Real3x3(-x, -y, -z); }

bool Real3x3::operator==(const Real3x3& b) const { return  x == b.x && y == b.y && z == b.z; }
bool Real3x3::operator!=(const Real3x3& b) const { return !operator==(b); }

Real3 Real3x3::operator[](int i) const
{
    if (i < 0 || i >= 3) throw std::out_of_range("Matrix indices out of range");
    return (&x)[i];
}

Real3& Real3x3::operator[](int i)
{
    if (i < 0 || i >= 3) throw std::out_of_range("Matrix indices out of range");
    return (&x)[i];
}

double Real3x3::determinant() const
{
    return (x.x * (y.y * z.z - y.z * z.y)
            + x.y * (y.z * z.x - y.x * z.z)
            + x.z * (y.x * z.y - y.y * z.x));
}

//////////////////////////////////////////////////////////////////////////////////////
// class Tensor2: class for symmetric 2nd-order tensors (useful for stresses, strains)
// Storage in vectorial form (xx yy zz xy yz zx)

Tensor2::Tensor2() { m_vec.resize(6, 0.); }
Tensor2::Tensor2(const Real3& d,const Real3& s) { setVec(d, s); }

Tensor2::Tensor2(const dvector& vec) {
    m_vec.assign(vec.begin(), vec.end());
}

Tensor2::Tensor2(const Real3x3& mat)	{
    if (!matrix3x3IsSymmetric(mat)) throw std::out_of_range("Matrix is not symmetric");
    Real3 d = matrix3x3GetDiagonal(mat);
    Real3 s = matrix3x3GetSupOutdiagonal(mat);
    setVec(d, s);
}

Tensor2::~Tensor2() { m_vec.clear(); }

Tensor2::operator Real3x3() const { return convertVectorToMatrix3x3(m_vec); }

Tensor2 Tensor2::identity() { return Tensor2(Real3::identity(), Real3::zero()); }
Tensor2 Tensor2::null() { return Tensor2(); }
Tensor2 Tensor2::zero() { return Tensor2(); }

// ***** IMPLEMENTATION METHODS
void Tensor2::setVec(const Real3& d, const Real3& s) {

    m_vec.resize(6, 0.);
    int i = 0;

    for (; i < 3; i++) m_vec[i] = d[i]; // xx yy zz
    for (; i < 6; i++) m_vec[i] = s[i-3]; // xy xz yz
}
int	Tensor2::get_index(const int& i, const int& j) {

    if (i < 0 || i >= 3 || j < 0 || j >= 3) throw std::out_of_range("Matrix indices out of range");
    if (j == i) return i;

    int ij = 0, nrow = 3;

    if (j > i) ij = (i + 1) * (2 * nrow - i) / 2 + j - i - 1;
    else ij = (j + 1) * (2 * nrow - j) / 2 + i - j - 1;
    return ij;
}

double& Tensor2::operator()(const int& i, const int& j)
{
    int ij = get_index(i, j);
    return m_vec[ij];
}

double Tensor2::operator()(const int& i, const int& j) const
{
    int ij = get_index(i, j);
    return m_vec[ij];
}

Tensor2& Tensor2::operator=(const Tensor2& mat)
{
    m_vec.clear();
    m_vec.assign(mat.m_vec.begin(), mat.m_vec.end());
    return (*this);
}

Tensor2& Tensor2::operator+=(const Tensor2& mat)
{
    m_vec = m_vec + mat.m_vec;
    return (*this);
}

Tensor2& Tensor2::operator-=(const Tensor2& mat)
{
    m_vec = m_vec - mat.m_vec;
    return (*this);
}

Tensor2& Tensor2::operator*=(const double& x)
{
    m_vec = x * m_vec;
    return (*this);
}

Tensor2& Tensor2::operator/=(const double& x)
{
    double ix = x;
    if (x < EPS) ix = EPS * signe(x);
    ix = 1 / ix;
    m_vec = m_vec * ix;
    return (*this);
}

Tensor2& Tensor2::operator=(const Real3x3& mat)
{
    if (!matrix3x3IsSymmetric(mat)) throw std::out_of_range("Matrix is not symmetric");
    Real3 d = matrix3x3GetDiagonal(mat);
    Real3 s = matrix3x3GetSupOutdiagonal(mat);
    setVec(d, s);
    return (*this);
}

Tensor2& Tensor2::operator=(const dvector& vec)
{
    if (vec.size() != 6) throw std::out_of_range("Vector size should be less equal to 6");
    m_vec.clear();
    m_vec.assign(vec.begin(), vec.end());
    return (*this);
}

Real3 Tensor2::get_diagonal() const { return Real3(m_vec[0], m_vec[1], m_vec[2]); } // xx yy zz
void Tensor2::set_diagonal(const Real3& d) { for (int i = 0; i < 3; i++) m_vec[i] = d[i]; }

Real3 Tensor2::get_outdiagonal() const { return Real3(m_vec[3], m_vec[4], m_vec[5]); } // xy xz yz
void Tensor2::set_outdiagonal(const Real3& s) { for (int i = 3; i < 6; i++) m_vec[i] = s[i-3]; }

Real3x3 Tensor2::Matrix3x3() const
{
    Real3x3 mat;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) mat[i][j] = (*this)(i, j);

    return mat;
}

/////////////////////////////////////////////////////////////////////////////
// General operations on Real2, Real3, Real3x3, Tensor2 classes
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



