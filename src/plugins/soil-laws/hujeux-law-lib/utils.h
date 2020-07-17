// General utilities for soil laws
// Developed by Evelyne FOERSTER - 2019

#ifndef _UTILS_H_
#define _UTILS_H_

#pragma once

#include <cmath>
#include <vector>
#include <iterator>

using namespace std;

#ifdef _WIN32
typedef long double Real;
#else
typedef double Real;
#endif

//typedef vector<double>	dvector;
typedef vector<Real>	dvector;

//extern void		gauss(double**, double*, double*, const int&);
extern void		gauss(Real**, Real*, Real*, const int&);
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
extern Real	dot(const dvector&, const dvector&);
extern Real	norm(const dvector&);
//extern double	norm_sqr(const dvector&);
//extern double	dist(const dvector&, const dvector&);
//extern double	dist_sqr(const dvector&, const dvector&);
//extern double	interpol(const double& /*val_before*/, const double& /*val_after*/,
//	const double& /*t*/, const double& /*t_before*/, const double& /*t_after*/);
extern bool		operator==(const dvector&, const dvector&);
extern bool		operator!=(const dvector&, const dvector&);
//extern void		AfficheMessage(const char*);
//extern string	makelower(const char*);

extern const Real	EPS, RAD;
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
	Real x;
    Real y;

public:
	Real2();
	Real2(Real, Real);
	Real2(const Real2&);
    ~Real2() = default;

	Real2& operator=(const Real2&);
	Real2& operator= (Real);

public:
	static Real2 null();
	static Real2 zero();
	static Real2 identity();

    Real operator[](int) const;
    Real& operator[](int);

	Real2 copy() const;
	Real2& reset();
	Real2& assign(Real ax, Real ay);
	Real2& assign(const Real2&);
    Real norm_sqr() const;
    Real norm() const;

	Real2& operator*=(Real);
	Real2& operator/=(Real);
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

/*---------------------------------------------------------------------------*/
	friend Real2 operator/(const Real2&, const Real&);
/*---------------------------------------------------------------------------*/
	friend Real2 operator*(const Real2&, const Real&);
/*---------------------------------------------------------------------------*/
    friend Real2 operator+(const Real2&, const Real2&);
/*---------------------------------------------------------------------------*/
    friend Real2 operator*(const Real&, const Real2&);
};
typedef vector<Real2> VecReal2;

//////////////////////////////////////////////////////////////////////
// class Real3: 3D real vector same as Real3 from Arcane
//
class Real3x3;

class Real3
{
public:
    Real x;
    Real y;
    Real z;

public:
	Real3();
	Real3(Real ax, Real ay, Real az);
	Real3(const Real3&);
	~Real3() = default;

    Real operator[](int) const;
    Real& operator[](int);

	Real3& operator=(const Real3&);
	Real3& operator= (Real);

	static Real3 null();
	static Real3 zero();
	static Real3 identity();

	Real3 copy() const;
	Real3& reset();
	Real3& assign(Real, Real, Real);
	Real3& assign(const Real3&);
    Real norm_sqr() const;
    Real norm() const;

	Real3& operator+=(Real);
	Real3& operator-=(Real);
	Real3& operator*=(Real);
	Real3& operator/=(Real);
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

/*---------------------------------------------------------------------------*/
    friend Real3 vec_prod(const Real3&, const Real3&);
/*---------------------------------------------------------------------------*/
    friend Real dot(const Real3&, const Real3&);
/*---------------------------------------------------------------------------*/
    friend Real norm_sqr(const Real3&);
/*---------------------------------------------------------------------------*/
    friend Real3 operator+(const Real&, const Real3&);
/*---------------------------------------------------------------------------*/
    friend Real3 operator+(const Real3&, const Real&);
/*---------------------------------------------------------------------------*/
    friend Real3 operator-(const Real&, const Real3&);
/*---------------------------------------------------------------------------*/
    friend Real3 operator-(const Real3&, const Real&);
/*---------------------------------------------------------------------------*/
    friend Real3 operator*(const Real&, const Real3&);
/*---------------------------------------------------------------------------*/
    friend Real3 operator*(const Real3&, const Real&);
/*---------------------------------------------------------------------------*/
    friend Real3x3 tensor_prod(Real3, Real3);
/*---------------------------------------------------------------------------*/
    friend Real3 operator/(const Real3&, const Real&);
/*---------------------------------------------------------------------------*/
    friend bool operator<(const Real3&, const Real3&);
};
typedef vector<Real3> VecReal3;

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
	Real3x3& operator= (const Real&);

	static Real3x3 null();
	static Real3x3 zero();
	static Real3x3 identity();

	static Real3x3 fromColumns(Real ax, Real ay, Real az, Real bx, Real by, Real bz, Real cx, Real cy, Real cz);
	static Real3x3 fromLines(Real ax, Real bx, Real cx, Real ay, Real by, Real cy, Real az, Real bz, Real cz);

	Real3x3 copy() const;
	Real3x3& reset();
	Real3x3& assign(const Real3& ax, const Real3& ay, const Real3& az);
	Real3x3& assign(const Real3x3&);
	bool isNearlyZero() const;

	Real3x3& operator+=(const Real3&);
	Real3x3& operator-=(const Real3&);
	Real3x3& operator+=(const Real3x3&);
	Real3x3& operator-=(const Real3x3&);
	void operator*=(const Real&);
	void operator/=(const Real&);
	Real3x3 operator+(const Real3x3&) const;
	Real3x3 operator-(const Real3x3&) const;
	Real3x3 operator-() const;
	
	bool operator==(const Real3x3&) const;
	bool operator!=(const Real3x3&) const;
	Real3 operator[](int) const;
	Real3& operator[](int);
    Real determinant() const;

/*---------------------------------------------------------------------------*/
    friend Real3x3 operator*(const Real&, const Real3x3&);
/*---------------------------------------------------------------------------*/
    friend Real3x3 operator*(const Real3x3&, const Real&);
/*---------------------------------------------------------------------------*/
    friend Real3x3 operator/(const Real3x3&, const Real&);
/*---------------------------------------------------------------------------*/
    friend bool operator<(const Real3x3&, const Real3x3&);
/*---------------------------------------------------------------------------*/
    friend Real3x3 matrix3x3Transpose(const Real3x3&);
/*---------------------------------------------------------------------------*/
    friend Real3 matrix3x3GetDiagonal(const Real3x3&);
/*---------------------------------------------------------------------------*/
    friend void matrix3x3SetDiagonal(Real3x3&, const Real3&);
/*---------------------------------------------------------------------------*/
    friend Real3 matrix3x3GetSupOutdiagonal(const Real3x3&);
/*---------------------------------------------------------------------------*/
    friend void matrix3x3SetSupOutdiagonal(Real3x3&, const Real3&);
/*---------------------------------------------------------------------------*/
    friend Real3 matrix3x3GetLowOutdiagonal(const Real3x3&);
/*---------------------------------------------------------------------------*/
    friend void matrix3x3SetLowOutdiagonal(Real3x3&, const Real3&);
/*---------------------------------------------------------------------------*/
    friend Real3x3 diagonalMatrix3x3(const Real3x3&);
/*---------------------------------------------------------------------------*/
    friend Real3x3 outdiagonalMatrix3x3(const Real3x3&);
/*---------------------------------------------------------------------------*/
    friend bool	matrix3x3IsSymmetric(const Real3x3&);
/*---------------------------------------------------------------------------*/
    friend Real trace(const Real3x3&);

/*---------------------------------------------------------------------------*/
// This is used for operations on stress and strain tensors
// Converting Real3x3 into a dvector(6) as follows (assuming symmetric tensors only):
//  _           _
// | xx  xy  xz  |
// | xy  yy  yz  |
// | xz  yz  zz  | => transposed vector = [xx yy zz xy xz yz]
// |_           _|

    friend  dvector convertMatrix3x3ToVector(const Real3x3&);

/*---------------------------------------------------------------------------*/
// This is used for operations on stress and strain tensors
// Converting a dvector(6) into a Real3x3 matrix as follows (assuming symmetric tensors only):
//                                            _           _
//                                           | xx  xy  xz  |
// transposed vector = [xx yy zz xy xz yz] =>| yx  yy  yz  |
//                                           | xz  yz  zz  |
//                                           |_           _|

    friend Real3x3 convertVectorToMatrix3x3(const dvector&);
};

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

    Real& operator()(const int&, const int&);

    Real operator()(const int&, const int&) const;
	
	Tensor2& operator=(const Tensor2&);
	Tensor2& operator+=(const Tensor2&);
	Tensor2& operator-=(const Tensor2&);
	Tensor2& operator*=(const Real&);
	Tensor2& operator/=(const Real&);
	Tensor2& operator=(const Real3x3&);
	Tensor2& operator=(const dvector&);
	
	Real3	get_diagonal() const; // xx yy zz
	void	set_diagonal(const Real3&);
	
	Real3	get_outdiagonal() const; // xy xz yz
	void	set_outdiagonal(const Real3&);

	Real3x3 Matrix3x3() const;

/*---------------------------------------------------------------------------*/
    friend Real trace(const Tensor2&);
/*---------------------------------------------------------------------------*/
    friend Tensor2 operator+(const Tensor2&, const Tensor2&);
/*---------------------------------------------------------------------------*/
    friend bool operator==(const Tensor2&, const Tensor2&);
/*---------------------------------------------------------------------------*/
    friend bool operator!=(const Tensor2&, const Tensor2&);
/*---------------------------------------------------------------------------*/
    friend Tensor2 operator*(const Tensor2&, const Real&);
/*---------------------------------------------------------------------------*/
    friend Tensor2 operator*(const Real&, const Tensor2&);
};


#endif /* _UTILS_H_ */
