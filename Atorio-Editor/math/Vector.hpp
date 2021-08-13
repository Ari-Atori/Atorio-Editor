#ifndef ATORIO_VECTOR
#define ATORIO_VECTOR

#include <math.h>

class vec2 {
public:
	vec2 operator = (vec2 const &v) {this->x = v.x; this->y = v.y; return *this;}
	vec2 operator - () { return {-x, -y}; }

	vec2 operator + (vec2 const &v) { return {x+v.x, y+v.y}; }
	vec2 operator - (vec2 const &v) { return {x-v.x, y-v.y}; }
	vec2 operator * (vec2 const &v) { return {x*v.x, y*v.y}; }
	vec2 operator / (vec2 const &v) { return {x/v.x, y/v.y}; }
	vec2 operator * (float f) { return {x*f, y*f}; }
	vec2 operator / (float f) { return {x/f, y/f}; }

	vec2 operator += (vec2 const &v) { *this = *this + v; return *this; }
	vec2 operator -= (vec2 const &v) { *this = *this - v; return *this; }
	vec2 operator *= (vec2 const &v) { *this = *this * v; return *this; }
	vec2 operator /= (vec2 const &v) { *this = *this / v; return *this; }
	vec2 operator *= (float f) { *this = *this * f; return *this; }
	vec2 operator /= (float f) { *this = *this / f; return *this; }

	float operator | (vec2 const &v) {return x*v.x + y*v.y;}
	float operator ^ (vec2 const &v) {return x*v.y - y*v.x;}

	float mag() {
		return sqrtf(x*x + y*y);
	}

	static vec2 norm(vec2 v) {
		return v / sqrtf(v.x*v.x + v.y*v.y);
	}

	static vec2 lerp(vec2 p1, vec2 p2, float f) {
		return p1 + (p2 - p1) * f;
	}

	float x, y;
};

class vec3 {
public:
	vec3 operator = (vec3 const &v) {this->x = v.x; this->y = v.y; this->z = v.z; return *this;}
	vec3 operator - () { return {-x, -y, -z}; }

	vec3 operator + (vec3 const &v) { return {x+v.x, y+v.y, z+v.z}; }
	vec3 operator - (vec3 const &v) { return {x-v.x, y-v.y, z-v.z}; }
	vec3 operator * (vec3 const &v) { return {x*v.x, y*v.y, z*v.z}; }
	vec3 operator / (vec3 const &v) { return {x/v.x, y/v.y, z/v.z}; }
	vec3 operator * (float f) { return {x*f, y*f, z*f}; }
	vec3 operator / (float f) { return {x/f, y/f, z/f}; }

	vec3 operator += (vec3 const &v) { *this = *this + v; return *this; }
	vec3 operator -= (vec3 const &v) { *this = *this - v; return *this; }
	vec3 operator *= (vec3 const &v) { *this = *this * v; return *this; }
	vec3 operator /= (vec3 const &v) { *this = *this / v; return *this; }
	vec3 operator *= (float f) { *this = *this * f; return *this; }
	vec3 operator /= (float f) { *this = *this / f; return *this; }

	float operator | (vec3 const &v) {return x*v.x + y*v.y + z*v.z;}
	vec3 operator ^ (vec3 const &v) {return {y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x}; }

	float mag() {
		return sqrtf(x*x + y*y + z*z);
	}

	static vec3 norm(vec3 v) {
		return v / sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
	}

	static vec3 lerp(vec3 p1, vec3 p2, float f) {
		return p1 + (p2 - p1) * f;
	}

	float x, y, z;
};

class vec4 {
public:
	vec4 operator = (vec4 const &v) {this->x = v.x; this->y = v.y; this->z = v.z; this->w = v.w; return *this;}
	vec4 operator - () { return {-x, -y, -z, -w}; }

	vec4 operator + (vec4 const &v) { return {x+v.x, y+v.y, z+v.z, w+v.w}; }
	vec4 operator - (vec4 const &v) { return {x-v.x, y-v.y, z-v.z, w-v.w}; }
	vec4 operator * (vec4 const &v) { return {x*v.x, y*v.y, z*v.z, w*v.w}; }
	vec4 operator / (vec4 const &v) { return {x/v.x, y/v.y, z/v.z, w/v.w}; }
	vec4 operator * (float f) { return {x*f, y*f, z*f, w*f}; }
	vec4 operator / (float f) { return {x/f, y/f, z/f, w/f}; }

	vec4 operator += (vec4 const &v) { *this = *this + v; return *this; }
	vec4 operator -= (vec4 const &v) { *this = *this - v; return *this; }
	vec4 operator *= (vec4 const &v) { *this = *this * v; return *this; }
	vec4 operator /= (vec4 const &v) { *this = *this / v; return *this; }
	vec4 operator *= (float f) { *this = *this * f; return *this; }
	vec4 operator /= (float f) { *this = *this / f; return *this; }

	float operator | (vec4 const &v) {return x*v.x + y*v.y + z*v.z + w*v.w;}

	float mag() {
		return sqrtf(x*x + y*y + z*z + w*w);
	}

	static vec4 norm(vec4 v) {
		return v / sqrtf(v.x*v.x + v.y*v.y + v.z*v.z + v.w*v.w);
	}

	static vec4 lerp(vec4 p1, vec4 p2, float f) {
		return p1 + (p2 - p1) * f;
	}

	float x, y, z, w;
};

#endif
