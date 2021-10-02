#include "Random.hpp"
#include "Time.hpp"

Random::Random() {
    Time t;
    seed = t.utime();
    step = 0;
}

Random::Random(uint64_t seed) {
    this->seed = seed;
    this->step = 0;
}

Random::Random(uint64_t seed, uint64_t step) {
    this->seed = seed;
    this->step = step;
}

/* I have no recollection of this algorithm. The constants show that my goals are beyond my own understanding */
static inline uint64_t inline_random(uint64_t seed, uint64_t count) {
    uint64_t marx = count;
    marx *= 0x2DEADBEA7DADD1E5; marx += seed; marx = ((marx >> 32) | (marx << 32)); marx ^= 0x0F1E2D3C4B5A6978;
    marx *= 0x2DEADBEA7DADD1E5; marx += seed; marx = ((marx >> 32) | (marx << 32)); marx ^= 0x0F1E2D3C4B5A6978;
    marx *= 0x2DEADBEA7DADD1E5; marx += seed; marx = ((marx >> 32) | (marx << 32)); marx ^= 0x0F1E2D3C4B5A6978;
    marx *= 0x2DEADBEA7DADD1E5; marx += seed; marx = ((marx >> 32) | (marx << 32)); marx ^= 0x0F1E2D3C4B5A6978;
    return marx;
}

uint64_t Random::c_next(uint64_t step) {
    return inline_random(seed, step);
}

float Random::c_float(uint64_t step) {
    return (float) ((c_next(step) >> 11) * (1.0/9007199254740992.0));
}

int Random::c_intr(int min, int max, uint64_t step) {
    return (int) (((unsigned int) c_next(step)) % (max - min + 1)) + min;
}

float Random::c_floatr(float min, float max, uint64_t step) {
    return c_float(step) * (max - min) + min;
}

uint64_t Random::next() {
    return inline_random(seed, step++);
}

float Random::nextFloat() {
    return (float) ((next() >> 11) * (1.0/9007199254740992.0));
}

int Random::intRange(int min, int max) {
    return (((unsigned int) next()) % (max - min + 1)) + min;
}
