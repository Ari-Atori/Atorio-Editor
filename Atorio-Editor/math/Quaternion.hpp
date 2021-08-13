#ifndef ATORIO_QUATERNION
#define ATORIO_QUATERNION

#include "Vector.hpp"

class quat {
public:
	quat operator = (quat const &q) {this->x = q.x; this->y = q.y; this->z = q.z; this->w = q.w; return *this;}
	quat operator - () { return {-x, -y, -z, -w}; }
	quat operator ~ () { return {-x, -y, -z, w}; }

	quat operator + (quat const &q) { return {x+q.x, y+q.y, z+q.z, w+q.w}; }
	quat operator - (quat const &q) { return {x-q.x, y-q.y, z-q.z, w-q.w}; }
	quat operator * (quat const &q) { return {w*q.x + x*q.w + y*q.z - z*q.y, w*q.y - x*q.z + y*q.w + z*q.x, w*q.z + x*q.y - y*q.x + z*q.w, w*q.w - x*q.x - y*q.y - z*q.z}; }
	quat operator / (quat const& q) { float C = M::rsqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w); quat r = {-q.x * C * C, -q.y * C * C, -q.z * C * C, q.w* C* C }; return (*this) * r; }
	quat operator * (float f) { return {x*f, y*f, z*f, w*f}; }
	quat operator / (float f) { return {x/f, y/f, z/f, w/f}; }

	quat operator += (quat const &q) { *this = *this + q; return *this; }
	quat operator -= (quat const &q) { *this = *this - q; return *this; }
	quat operator *= (quat const &q) { *this = *this * q; return *this; }
	quat operator /= (quat const &q) { *this = *this / q; return *this; }
	quat operator *= (float f) { *this = *this * f; return *this; }
	quat operator /= (float f) { *this = *this / f; return *this; }

	float operator |(quat const &q) {return x*q.x + y*q.y + z*q.z + w*q.w;}

	float mag() {
		return sqrtf(x*x + y*y + z*z + w*w);
	}

	static quat norm(quat q) {
		return q / sqrtf(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
	}

	quat recip() {
		return ~(norm(*this)) / sqrtf(x*x + y*y + z*z + w*w);
	}

	static quat lerp(quat q1, quat q2, float f) {
		return q1 + (q2 - q1) * f;
	}

	static quat slerp(quat q1, quat q2, float f) {
		q1 = quat::norm(q1);
		q2 = quat::norm(q2);
		float d = q1 | q2;
		if (d < 0.0F) {
			q2 =-q2;
			d = -d;
		}

		float t0 = acosf(d), t = t0 * f;
		float st0 = sinf(t0), st = sinf(t);

		float s1 = cosf(t) - d * st / st0, s2 = st / st0;
    	return (q1 * s1) + (q2 * s2);
	}

	static quat V3a(V3 r, float a) {
		r = V3::norm(r);
		float c = cosf(a * 0.5F), s = sinf(a * 0.5F);
		return {r.x * s, r.y * s, r.z * s, c};
	}

	float x, y, z, w;
};

#endif
