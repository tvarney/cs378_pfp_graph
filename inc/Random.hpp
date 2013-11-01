
#ifndef CS378_PROJECT3_RANDOM_HPP
#define CS378_PROJECT3_RANDOM_HPP

#include <stdint.h>

namespace cs378 {
    class Random {
    public:
        virtual double nextUniform() = 0;
        virtual float nextFloat() = 0;
        virtual double nextDouble() = 0;
        virtual int8_t nextInt8() = 0;
        virtual int16_t nextInt16() = 0;
        virtual int32_t nextInt32() = 0;
        virtual int64_t nextInt64() = 0;
        
        virtual Random * copy() = 0;
    protected:
        virtual ~Random();
    };
    
    class RandomLCG : public Random {
    public:
        RandomLCG();
        RandomLCG(uint32_t seed);
        RandomLCG(const RandomLCG &source);
        virtual ~RandomLCG();
        
        virtual double nextUniform();
        virtual float nextFloat();
        virtual double nextDouble();
        virtual int8_t nextInt8();
        virtual int16_t nextInt16();
        virtual int32_t nextInt32();
        virtual int64_t nextInt64();
        
        virtual Random * copy();
    protected:
        uint64_t seed;
    };
    
    /* Uses three LCG style PRNGs to produce it's output stream.
     * The first two are used as the value streams, the third as a bit selector
     * between the two streams. Each LCG has different values for a and c,
     * and the each LCG swaps values after each random number is generated.
     * This should still be blazing fast, and only takes 24 bytes.
     * This PRNG works with a modulo value of 2^48.
     * 
     * S1(i+1) = (S2(i) * 412316905783 + 17) % 2^48
     * S2(i+1) = (S1(i) * 549755865917 + 19) % 2^48
     * M(i+1) = (M(i) * 206158430208 + 11) % 2^48
     * X(i+1) = ((S1(i+1) & M(i+1)) | (S2(i+1) & ~M(i+1))) >> 16
     */
    class RandomLCG2 : public Random {
        RandomLCG2();
        RandomLCG2(int32_t seed);
        RandomLCG2(const RandomLCG2 &source);
        virtual ~RandomLCG2();
        
        virtual double nextUniform();
        virtual float nextFloat();
        virtual double nextDouble();
        virtual int8_t nextInt8();
        virtual int16_t nextInt16();
        virtual int32_t nextInt32();
        virtual int64_t nextInt64();
        
        virtual Random * copy();
    protected:
        uint64_t seed[2];
        uint64_t selector;
    };
}

#endif
