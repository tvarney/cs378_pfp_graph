
#ifndef CS354_GENERIC_POINT_HPP
#define CS354_GENERIC_POINT_HPP

#include <ostream>
#include "Vector3.hpp"

namespace cs354 {
    template <typename T>
    struct Point3 {
        T x, y, z;
        
        Point3() { }
        Point3(T x, T y, T z) : x(x), y(y), z(z) { }
        Point3(T data[3]) : x(data[0]), y(data[1]), z(data[2]) { }
        Point3(const Point3<T> &source) :
            x(source.x), y(source.y), z(source.z)
        { }
        ~Point3() { }
        
        Point3<T> operator+(const Vector3<T> rhs) const {
            return Point3<T>(x + rhs.x, y + rhs.y, z + rhs.z);
        }
        Point3<T> operator-(const Vector3<T> rhs) const {
            return Point3<T>(x - rhs.x, y - rhs.y, z - rhs.z);
        }
        Vector3<T> operator-(const Point3<T> rhs) const {
            return Vector3<T>(x - rhs.x, y - rhs.y, z - rhs.z);
        }
        
        Point3<T> & operator=(const Point3<T> rhs) {
            x = rhs.x;
            y = rhs.y;
            z = rhs.z;
            return *this;
        }
        
        Point3<T> & operator+=(const Vector3<T> rhs) {
            return *this = *this + rhs;
        }
        Point3<T> & operator-=(const Vector3<T> rhs) {
            return *this = *this - rhs;
        }
        
        static const Point3<T> Origin;
    };
    
    template <typename T>
    const Point3<T> Point3<T>::Origin(0, 0, 0);
    
    typedef Point3<float> Point3f;
    typedef Point3<double> Point3d;
    typedef Point3<int> Point3i;
    typedef Point3<unsigned int> Point3ui;
    
    template <typename T>
    std::ostream & operator<<(std::ostream &out, Point3<T> &rhs) {
        out << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
        return out;
    }
}

#endif
