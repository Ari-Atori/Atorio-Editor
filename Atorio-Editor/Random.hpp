#ifndef ATORIO_PRNG
#define ATORIO_PRNG

#include <stddef.h>
#include <stdint.h>

class Random {
public:
    Random();
    Random(uint64_t seed);
    Random(uint64_t seed, uint64_t step);
    virtual ~Random() {}

    inline void set_seed(uint64_t seed) { this->seed = seed; }

    uint64_t c_next(uint64_t step);
    float c_float(uint64_t step);
    int c_intr(int min, int max, uint64_t step);
    float c_floatr(float min, float max, uint64_t step);

    uint64_t next();
    float nextFloat();
    int intRange(int min, int max);
private:
    uint64_t seed, step;
};

#endif
