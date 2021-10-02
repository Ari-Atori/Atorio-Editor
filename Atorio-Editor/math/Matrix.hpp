#ifndef ATORIO_MATRIX
#define ATORIO_MATRIX
#include "Vector.hpp"

class mat4 {
public:
	mat4 operator =(mat4 const &m);
	mat4 operator -();
	mat4 operator + (mat4 const &m);
	mat4 operator - (mat4 const &m);
	mat4 operator * (mat4 const &m);
	vec4 operator * (vec4 const &v);
	mat4 operator * (float f);
	mat4 operator / (float f);
	float& operator()(size_t col, size_t row) { return c[row][col]; }
	float operator()(size_t col, size_t row) const { return c[row][col];  }

	mat4 operator += (mat4 const &m) { *this = *this + m; return *this; }
	mat4 operator -= (mat4 const &m) { *this = *this - m; return *this; }
	mat4 operator *= (mat4 const &m) { *this = *this * m; return *this; }
	vec4 operator *= (vec4 const &v) { vec4 vr = *this * v; return vr; }
	mat4 operator *= (float f) { *this = *this * f; return *this; }
	mat4 operator /= (float f) { *this = *this / f; return *this; }

	float det();
	mat4 inverse();
	float c[4][4];
};

static const mat4 MAT4_ZERO = {{{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}};
static const mat4 MAT4_IDENTITY = {{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}}};

#endif
