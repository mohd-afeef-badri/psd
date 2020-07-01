// General utilities for soil laws
// Developed by Evelyne FOERSTER - 2019

#ifndef _UTILS_H_
#define _UTILS_H_

#pragma once

#include <cmath>
#include <vector>
#include <iterator>

using namespace std;

typedef vector<double>	dvector;

extern void		gauss(double**, double*, double*, const int&);                         
extern dvector	operator-(const dvector&, const dvector&);
extern dvector	operator+(const dvector&, const dvector&);
extern dvector	operator+(const dvector&, const double&);
extern dvector	operator+(const double&, const dvector&);
extern dvector	operator-(const dvector&, const double&);
extern dvector	operator-(const double&, const dvector&);
extern dvector	operator/(const dvector&, const double&);
extern dvector	operator*(const dvector&, const double&);
extern dvector	operator*(const double&, const dvector&);
//extern dvector	vect_prod(const dvector&, const dvector&);
extern double	dot(const dvector&, const dvector&);
extern double	norm(const dvector&);
//extern double	norm_sqr(const dvector&);
//extern double	dist(const dvector&, const dvector&);
//extern double	dist_sqr(const dvector&, const dvector&);
//extern double	interpol(const double& /*val_before*/, const double& /*val_after*/,
//	const double& /*t*/, const double& /*t_before*/, const double& /*t_after*/);
extern bool		operator==(const dvector&, const dvector&);
extern bool		operator!=(const dvector&, const dvector&);
//extern void		AfficheMessage(const char*);
//extern string	makelower(const char*);

extern const double	EPS, TOL; //, TempsPause, facHour, facMin, facDay;             ///////// CHECK CEHCK 
extern char		szout[];
extern string	ferrlog;

template<class T> T min_(T a, T b) { return (a < b ? a : b); }
template<class T> T max_(T a, T b) { return (a > b ? a : b); }
template<class T> T signe(T a) { return (a >= 0 ? 1 : -1); } 
//////////////////////////////////////////////////////////////////////
//  class Real2: 2D real vector same as Real3 from Arcane
//
class Real2
{
public:
	double x;
	double y;

public:
	Real2();
	Real2(double, double);
	Real2(const Real2&);
    ~Real2() = default;

	Real2& operator=(const Real2&);
	Real2& operator= (double);

public:
	static Real2 null();
	static Real2 zero();
	static Real2 identity();

    double operator[](int) const;
    double& operator[](int);

	Real2 copy() const;
	Real2& reset();
	Real2& assign(double ax, double ay);
	Real2& assign(Real2);
	double norm_sqr() const;
	double norm() const;

	Real2& operator*=(double);
	Real2& operator/=(double);
	Real2& operator+=(const Real2&);
	Real2& operator-= (const Real2&);
	Real2& operator*= (const Real2&);
	Real2& operator/= (const Real2&);
	Real2 operator+(const Real2&) const;
	Real2 operator-(const Real2&) const;
	Real2 operator-() const;
	Real2 operator*(const Real2&) const;
	Real2 operator/(const Real2&) const;

	Real2& normalize();
	bool isNearlyZero() const;
	bool operator==(const Real2& b) const;
	bool operator!=(const Real2& b) const;
};
typedef vector<Real2> VecReal2;

/*---------------------------------------------------------------------------*/
extern Real2 operator+(const Real2&, const Real2&);
/*---------------------------------------------------------------------------*/
extern Real2 operator*(const Real2&, const double&);
/*---------------------------------------------------------------------------*/
extern Real2 operator/(const Real2&, const double&);
/*---------------------------------------------------------------------------*/
extern Real2 operator*(const double&, const Real2&);

//////////////////////////////////////////////////////////////////////
// class Real3: 3D real vector same as Real3 from Arcane
//
class Real3
{
public:
	double x;
	double y;
	double z;

public:
	Real3() { x = 0.0; y = 0.0; z = 0.0; }
	Real3(double ax, double ay, double az): x(ax),y(ay),z(az) {}
	Real3(const Real3& f) { x = f.x; y = f.y; z = f.z; }
	~Real3() = default;

    double operator[](int) const;
    double& operator[](int);

	Real3& operator=(const Real3&);
	Real3& operator= (double);

	static Real3 null();
	static Real3 zero();
	static Real3 identity();

	Real3 copy() const;
	Real3& reset();
	Real3& assign(double, double, double);
	Real3& assign(const Real3&);
	double norm_sqr() const;
	double norm() const;

	Real3& operator+=(double);
	Real3& operator-=(double);
	Real3& operator*=(double);
	Real3& operator/=(double);
	Real3& operator+= (const Real3&);
	Real3& operator-= (const Real3&);
	Real3& operator*= (const Real3&);
	Real3& operator/= (const Real3&);
	Real3 operator+(const Real3&) const;
	Real3 operator-(const Real3&) const;
	Real3 operator-() const;
	Real3 operator*(const Real3&) const;
	Real3 operator/(const Real3&) const;

	Real3& normalize();
	bool isNearlyZero() const;
	bool operator==(const Real3&) const;
	bool operator!=(const Real3&) const;
};
typedef vector<Real3> VecReal3;

/*---------------------------------------------------------------------------*/
extern Real3 vec_prod(const Real3&, const Real3&);
/*---------------------------------------------------------------------------*/
extern double dot(const Real3&, const Real3&);
/*---------------------------------------------------------------------------*/
extern double norm_sqr(const Real3&);
/*---------------------------------------------------------------------------*/
extern Real3 operator+(double, const Real3&);
/*---------------------------------------------------------------------------*/
extern Real3 operator+(const Real3&, double);
/*---------------------------------------------------------------------------*/
extern Real3 operator-(double, const Real3&);
/*---------------------------------------------------------------------------*/
extern Real3 operator-(const Real3&, double);
/*---------------------------------------------------------------------------*/
extern Real3 operator*(double, const Real3&);
/*---------------------------------------------------------------------------*/
extern Real3 operator*(const Real3&, double);
/*---------------------------------------------------------------------------*/
extern Real3 operator/(const Real3&, double);
/*---------------------------------------------------------------------------*/
extern bool operator<(const Real3&, const Real3&);

//////////////////////////////////////////////////////////////////////
// class Real3x3: Matrix 3x3 same as Real3x3 from Arcane
//
class Real3x3
{
public:
	Real3 x;//line 0
	Real3 y;//line 1
	Real3 z;//line 2

	Real3x3();
	Real3x3(const Real3&, const Real3&, const Real3&);
	Real3x3(const Real3x3&);
    ~Real3x3() = default;

public:
	Real3x3& operator=(const Real3x3&);
	Real3x3& operator= (double);

	static Real3x3 null();
	static Real3x3 zero();
	static Real3x3 identity();

	static Real3x3 fromColumns(double ax, double ay, double az, double bx, double by, double bz, double cx, double cy, double cz);
	static Real3x3 fromLines(double ax, double bx, double cx, double ay, double by, double cy, double az, double bz, double cz);

	Real3x3 copy() const;
	Real3x3& reset();
	Real3x3& assign(const Real3& ax, const Real3& ay, const Real3& az);
	Real3x3& assign(const Real3x3&);
	bool isNearlyZero() const;

	Real3x3& operator+=(const Real3&);
	Real3x3& operator-=(const Real3&);
	Real3x3& operator+=(const Real3x3&);
	Real3x3& operator-=(const Real3x3&);
	void operator*=(double);
	void operator/=(double);
	Real3x3 operator+(const Real3x3&) const;
	Real3x3 operator-(const Real3x3&) const;
	Real3x3 operator-() const;

	bool operator==(const Real3x3&) const;
	bool operator!=(const Real3x3&) const;
	Real3 operator[](int) const;
	Real3& operator[](int);
	double determinant() const;
};

/*---------------------------------------------------------------------------*/
extern Real3x3 operator*(double, const Real3x3&);
/*---------------------------------------------------------------------------*/
extern Real3x3 operator*(const Real3x3&, double);
/*---------------------------------------------------------------------------*/
extern Real3x3 operator/(const Real3x3&, double);
/*---------------------------------------------------------------------------*/
extern bool operator<(const Real3x3&, const Real3x3&);
/*---------------------------------------------------------------------------*/
extern Real3x3 tensor_prod(Real3, Real3);
/*---------------------------------------------------------------------------*/
extern Real3x3 matrix3x3Transpose(const Real3x3&);
/*---------------------------------------------------------------------------*/
extern Real3 matrix3x3GetDiagonal(Real3x3);
/*---------------------------------------------------------------------------*/
extern void matrix3x3SetDiagonal(Real3x3&, Real3);
/*---------------------------------------------------------------------------*/
extern Real3 matrix3x3GetSupOutdiagonal(Real3x3);
/*---------------------------------------------------------------------------*/
extern void matrix3x3SetSupOutdiagonal(Real3x3&, Real3);
/*---------------------------------------------------------------------------*/
extern Real3 matrix3x3GetLowOutdiagonal(Real3x3);
/*---------------------------------------------------------------------------*/
extern void matrix3x3SetLowOutdiagonal(Real3x3&, const Real3&);
/*---------------------------------------------------------------------------*/
extern Real3x3 diagonalMatrix3x3(Real3x3);
/*---------------------------------------------------------------------------*/
extern Real3x3 outdiagonalMatrix3x3(const Real3x3&);
/*---------------------------------------------------------------------------*/
extern bool	matrix3x3IsSymmetric(const Real3x3&);
/*---------------------------------------------------------------------------*/
extern double trace(Real3x3);

/*---------------------------------------------------------------------------*/
// This is used for operations on stress and strain tensors
// Converting Real3x3 into a dvector(6) as follows (assuming symmetric tensors only):
//  _           _
// | xx  xy  xz  |
// | xy  yy  yz  |
// | xz  yz  zz  | => transposed vector = [xx yy zz xy xz yz]
// |_           _|

extern dvector convertMatrix3x3ToVector(Real3x3);
/*---------------------------------------------------------------------------*/
// This is used for operations on stress and strain tensors
// Converting a dvector(6) into a Real3x3 matrix as follows (assuming symmetric tensors only):
//                                            _           _
//                                           | xx  xy  xz  |
// transposed vector = [xx yy zz xy xz yz] =>| yx  yy  yz  |
//                                           | xz  yz  zz  |
//                                           |_           _|

extern Real3x3 convertVectorToMatrix3x3(dvector);
//////////////////////////////////////////////////////////////////////////////////////
// class Tensor2: class for symmetric 2nd-order tensors (useful for stresses, strains)
// Storage in vectorial form (xx yy zz xy yz zx) 

class Tensor2
{
	// ***** ATTRIBUTES
public:
	dvector	m_vec; // xx yy zz xy yz zx

	// ***** CONSTRUCTORS & DESTRUCTOR
public:
	Tensor2();
	Tensor2(const Real3&,const Real3&);
	explicit Tensor2(const dvector&);
	explicit Tensor2(const Real3x3&);
	~Tensor2();

	explicit operator Real3x3() const;

	static Tensor2 identity();
	static Tensor2 null();
	static Tensor2 zero();

	// ***** IMPLEMENTATION METHODS
	void setVec(const Real3&, const Real3&);
	static int	get_index(const int&, const int&);
	
	double& operator()(const int&, const int&);

	double operator()(const int&, const int&) const;
	
	Tensor2& operator=(const Tensor2&);
	Tensor2& operator+=(const Tensor2&);
	Tensor2& operator-=(const Tensor2&);
	Tensor2& operator*=(const double&);
	Tensor2& operator/=(const double&);
	Tensor2& operator=(const Real3x3&);
	Tensor2& operator=(const dvector&);

	Real3	get_diagonal() const; // xx yy zz
	void	set_diagonal(const Real3&);
	
	Real3	get_outdiagonal() const; // xy xz yz
	void	set_outdiagonal(const Real3&);

	Real3x3 Matrix3x3() const;
};

/*---------------------------------------------------------------------------*/
extern double trace(Tensor2);
/*---------------------------------------------------------------------------*/
extern Tensor2 operator+(const Tensor2&,const Tensor2&);
/*---------------------------------------------------------------------------*/
extern bool operator==(const Tensor2&, const Tensor2&);
/*---------------------------------------------------------------------------*/
extern bool operator!=(const Tensor2&, const Tensor2&);
/*---------------------------------------------------------------------------*/
extern Tensor2 operator*(const Tensor2&,const double&);

#endif /* _UTILS_H_ */
