
#ifndef CS354_GENERIC_GEOMETRY_HPP
#define CS354_GENERIC_GEOMETRY_HPP

#include "Matrix.hpp"
#include "Point3.hpp"
#include "Vector3.hpp"

namespace cs354 {
    template <typename T>
    Vector<T> operator-(const Point<T> rhs, const Point<T> lhs) {
        return Vector<T>(rhs.x - lhs.x, rhs.y - lhs.y, rhs.z - lhs.z);
    }
    template <typename T>
    Point<T> operator+(const Point<T> rhs, const Vector<T> lhs) {
        return Point<T>(rhs.x + lhs.x, rhs.y + lhs.y, rhs.z + lhs.z);
    }
    template <typename T>
    Point<T> operator+(const Vector<T> rhs, const Point<T> lhs) {
        return Point<T>(rhs.x + lhs.x, rhs.y + lhs.y, rhs.z + lhs.z);
    }
    
    template <typename T>
    Vector<T> operator*(const Matrix<T> &rhs, const Vector<T> lhs) {
        return Vector<T>(lhs);
    }
    template <typename T>
    Point<T> operator*(const Matrix<T> &rhs, const Point<T> lhs) {
        return Point<T>(lhs);
    }
}

#endif
