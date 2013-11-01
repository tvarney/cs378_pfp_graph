
#ifndef CS378_PROJECT3_VECTOR_HPP
#define CS378_PROJECT3_VECTOR_HPP

#include <ostream>

namespace cs378 {
    struct Vector {
        double x, y;
        
        Vector();
        Vector(double x, double y);
        Vector(const Vector &source);
        ~Vector();
        
        Vector operator+(const Vector rhs) const;
        Vector operator-(const Vector rhs) const;
        Vector operator*(double scalar) const;
        Vector operator/(double scalar) const;
        double operator%(const Vector rhs) const;
        
        Vector & operator=(const Vector rhs);
        Vector & operator+=(const Vector rhs);
        Vector & operator-=(const Vector rhs);
        Vector & operator*=(double scalar);
        Vector & operator/=(double scalar);
        
        Vector inverse() const;
        Vector normalize() const;
        double magsquared() const;
        double magnitude() const;
    };
    
    Vector operator*(double scalar, Vector rhs);
    std::ostream & operator<<(std::ostream &out, const Vector &v);
}

#endif
