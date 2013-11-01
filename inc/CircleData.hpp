
#ifndef CS378_PROJECT3_CIRCLE_DATA_HPP
#define CS378_PROJECT3_CIRCLE_DATA_HPP

#include <stddef.h>

namespace cs378 {
    struct CircleData {
        float *vertices;
        size_t num;
        
        void draw() const;
    };
    extern const CircleData Circle;
}

#endif
