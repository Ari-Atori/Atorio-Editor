#include "Noise.hpp"
#include "Vector.hpp"

static uint64_t ulam(int64_t x, int64_t z) {
    if (x == 0 && z == 0)
        return 0;
    if (x > 0 && x >= z && z >= (1 - x))
        return (uint64_t) (2 * x * (2 * x - 1) - (x - z));
    if (x < 0 && (-x - 1) >= z && z >= x)
        return (uint64_t) (2 * x * (2 * x - 1) + (x - z));
    if (z > 0 && (z - 1) >= x && x >= -z)
        return (uint64_t) (4 * z * z - (z + x));
    else
        return (uint64_t) (4 * z * (z - 1) + (z + x));
}

Noise::Noise(uint64_t seed) {
    r.set_seed(seed);
}

static float fade(float t) {
	return t * t * t * (t * (t * 6 - 15) + 10);
}

static int fast_floor(float t) {
	return (int) t - ((int) t > t);
}

float Noise::grad(int ix, int iy, int iz, float x, float y, float z) {
    uint64_t c =  ((uint64_t) (2199023255552 * iy) + ulam(ix, iz));
	const float w = 1048576.0F;
    union { struct { uint64_t x : 21, y : 21, z : 21, w : 1; } s; uint64_t u; } u;
    u.u = r.c_next(c);
    V3 d = { x - ix, y - iy, z - iz };


	return d | V3::norm({u.s.x / w - 1.0F, u.s.y / w - 1.0F, u.s.z / w - 1.0F});
}

void Noise::set_seed(uint64_t seed) {
	r.set_seed(seed);
}

float Noise::sample(float x, float y, float z) {
    int x0 = fast_floor(x), y0 = fast_floor(y), z0 = fast_floor(z), x1 = x0 + 1, y1 = y0 + 1, z1 = z0 + 1;
    float sx = fade(x - x0), sy = fade(y - y0), sz = fade(z - z0);

    float n0, n1, ix0, ix1, iy0, iy1;

    n0 = grad(x0, y0, z0, x, y, z);
    n1 = grad(x1, y0, z0, x, y, z);
    ix0 = n0 + (n1 - n0) * sx;
    n0 = grad(x0, y1, z0, x, y, z);
    n1 = grad(x1, y1, z0, x, y, z);
    ix1 = n0 + (n1 - n0) * sx;
    iy0 = ix0 + (ix1 - ix0) * sy;
    n0 = grad(x0, y0, z1, x, y, z);
    n1 = grad(x1, y0, z1, x, y, z);
    ix0 = n0 + (n1 - n0) * sx;
    n0 = grad(x0, y1, z1, x, y, z);
    n1 = grad(x1, y1, z1, x, y, z);
    ix1 = n0 + (n1 - n0) * sx;
    iy1 = ix0 + (ix1 - ix0) * sy;
    return iy0 + (iy1 - iy0) * sz;
}

float Noise::octaves(float x, float y, float z, unsigned int octaves) {
	if (!octaves)
		return 0;
	float max = 0, d = 1, val = 0, freq = 1;

	for (unsigned int i = 0; i < octaves; ++i) {
		val += d * sample(freq * x, freq * y, freq * z);
		max += d;
		d *= 0.5;
		freq *= 2;
	}
	return val / max;
}
