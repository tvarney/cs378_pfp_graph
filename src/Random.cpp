
#include "Random.hpp"

#include <time.h>

using namespace cs378;

Random::~Random() { }

RandomLCG::RandomLCG()
{
    seed = (25215167933 * time(NULL) + 13) & 0x0000FFFFFFFFFFFF;
}
RandomLCG::RandomLCG(uint32_t seed) {
    this->seed = (25214903917 * seed + 11) & 0x0000FFFFFFFFFFFF;
}
RandomLCG::RandomLCG(const RandomLCG &source) :
    seed(source.seed)
{ }
RandomLCG::~RandomLCG() { }

double RandomLCG::nextUniform() {
    return double((uint64_t)nextInt64()) / double((uint64_t)-1);
}
float RandomLCG::nextFloat() {
    nextInt32();
    return float(((int64_t)seed) - 140737488355328) / 140737488355327.0f;
}
double RandomLCG::nextDouble() {
    nextInt32();
    return double(((int64_t)seed) - 140737488355328) / 140737488355327.0;
}
int8_t RandomLCG::nextInt8() {
    return ((int8_t)(nextInt32() >> 24));
}
int16_t RandomLCG::nextInt16() {
    return ((int16_t)(nextInt32() >> 16));
}
int32_t RandomLCG::nextInt32() {
    seed = (25214903917 * seed + 11) & 0x0000FFFFFFFFFFFF;
    return seed >> 16;
}
int64_t RandomLCG::nextInt64() {
    return (int64_t)(((uint64_t)nextInt32()) << 32 | ((uint64_t)nextInt32()));
}

Random * RandomLCG::copy() {
    return new RandomLCG(*this);
}

RandomLCG2::RandomLCG2() {
    RandomLCG rcg(time(NULL));
    seed[0] = (rcg.nextInt64() ^ rcg.nextInt64()) + rcg.nextInt64();
    seed[1] = (rcg.nextInt64() ^ rcg.nextInt64()) + rcg.nextInt64();
    selector = (rcg.nextInt64() ^ rcg.nextInt64()) + rcg.nextInt64();
}
RandomLCG2::RandomLCG2(int32_t seed) {
    RandomLCG rcg(seed);
    this->seed[0] = (rcg.nextInt64() ^ rcg.nextInt64()) + rcg.nextInt64();
    this->seed[1] = (rcg.nextInt64() ^ rcg.nextInt64()) + rcg.nextInt64();
    selector = (rcg.nextInt64() ^ rcg.nextInt64()) + rcg.nextInt64();
}
RandomLCG2::RandomLCG2(const RandomLCG2 &source) {
    seed[0] = source.seed[0];
    seed[1] = source.seed[1];
    selector = source.selector;
}
RandomLCG2::~RandomLCG2() { }

double RandomLCG2::nextUniform() {
    return double((uint64_t)nextInt64()) / ((uint64_t)-1);
}
float RandomLCG2::nextFloat() {
    nextInt32(); /*< Permute the state */
    /* Get the equivalent of a int48_t from the seed, divide by 2^47 - 1 */
    return float(((int64_t)seed) - 140737488355328) / 140737488355327.0f;
}
double RandomLCG2::nextDouble() {
    nextInt32();
    /* Get the equivalent of a int48_t from the seed, divide by 2^47 - 1 */
    return double(((int64_t)seed) - 140737488355328) / 140737488355327.0;
}
int8_t RandomLCG2::nextInt8() {
    return nextInt32() >> 24;
}
int16_t RandomLCG2::nextInt16() {
    return nextInt32() >> 16;
}
int32_t RandomLCG2::nextInt32() {
    seed[0] = (seed[0] * 412316905783 + 17) & 0x0000FFFFFFFFFFFF;
    seed[1] = (seed[1] * 549755865917 + 19) & 0x0000FFFFFFFFFFFF;
    selector = (selector * 206158430208 + 11) & 0x0000FFFFFFFFFFFF;
    
    int32_t temp = seed[0];
    seed[0] = seed[1];
    seed[1] = temp;
    return ((seed[0] & selector) | (seed[1] & (~selector))) >> 16;
}
int64_t RandomLCG2::nextInt64() {
    return ((uint64_t)nextInt32()) << 32 | ((uint64_t)nextInt32());
}

Random * RandomLCG2::copy() {
    return new RandomLCG2(*this);
}
