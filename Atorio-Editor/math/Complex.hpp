#ifndef ATORIO_COMPLEX
#define ATORIO_COMPLEX

#include <math.h>
#include "Vector.hpp"

class complex {
public:
	complex operator = (complex const &x) {this->i = x.i; this->r = x.r; return *this;}
	complex operator - () { return {-r, -i}; }
	complex operator ~ () { return {r, -i}; }

	complex operator + (complex const &x) { return {r + x.r, i + x.i}; }
	complex operator - (complex const &x) { return {r - x.r, i - x.i}; }
	complex operator * (complex const &x) { return {r*x.r - i*x.i, r*x.i + i*x.r}; }
 	complex operator / (complex const &x) { float C = x.r*x.r+x.i*x.i; complex q = { x.r / C,-x.i / C }; return *this * q; }
	complex operator * (float f) { return {r * f, i * f}; }
	complex operator / (float f) { return {r / f, i / f}; }

	complex operator += (complex const &x) { *this = *this + x; return *this; }
	complex operator -= (complex const &x) { *this = *this - x; return *this; }
	complex operator *= (complex const &x) { *this = *this * x; return *this; }
	complex operator /= (complex const &x) { *this = *this / x; return *this; }
	complex operator *= (float f) { *this = *this * f; return *this; }
	complex operator /= (float f) { *this = *this / f; return *this; }

	complex recip() { return ~(*this) / (r*r+i*i); }
	float arg() { return atan2(i, r); }
	float abs() { return hypot(r, i); }

	static complex exp(complex c) { float e = expf(c.r);  return  { cosf(c.i) * e, sinf(c.i) * e}; }
	static complex ln(complex c) { return  {log(c.abs()), c.arg()}; }
	static complex pow(complex x, complex y) { return exp(ln(x) * y); }
	static complex sqrt(complex c) { return exp(ln(c) * 0.5); }

	float r, i;
protected:
private:
};

#endif
