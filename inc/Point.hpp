
#ifndef CS378_PROJECT3_POINT_HPP
#define CS378_PROJECT3_POINT_HPP

#include "Vector.hpp"

namespace cs378 {
    struct Point {
        double x, y;
        
        Point();
        Point(double x, double y);
        Point(const Point &source);
        ~Point();
        
        Point operator+(const Vector rhs) const;
        Point operator-(const Vector rhs) const;
        Vector operator-(const Point rhs) const;
        
        Point & operator=(const Point rhs);
        Point & operator+=(const Vector rhs);
        Point & operator-=(const Vector rhs);
        
        static const Point Origin;
    };
    
    std::ostream & operator<<(std::ostream &out, const Point &p);
}

#endif
