#ifndef LBB_MATH_NOISE
#define LBB_MATH_NOISE

#include "../Random.hpp"

class Noise {
public:
	Noise() {}
    Noise(uint64_t seed);
    virtual ~Noise() {}

	void set_seed(uint64_t seed);

    float sample(float x, float y, float z);
	float octaves(float x, float y, float z, unsigned int octaves);
private:
    float grad(int ix, int iy, int iz, float x, float y, float z);
    Random r;
};

#endif
