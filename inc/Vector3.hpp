
#ifndef CS354_GENERIC_VECTOR3_HPP
#define CS354_GENERIC_VECTOR3_HPP

#include <cmath>
#include <ostream>

namespace cs354 {
    template <typename T>
    struct Vector3 {
        T x, y, z;
        
        Vector3() { }
        Vector3(T x, T y, T z) : x(x), y(y), z(z) { }
        Vector3(const T data[3]) :
            x((T)data[0]), y((T)data[1]), z((T)data[2])
        { }
        Vector3(const Vector3<T> &source) :
            x(source.x), y(source.y), z(source.z)
        { }
        ~Vector3() { }
        
        T & operator[](unsigned int i) {
            switch(i) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            }
        }
        const T & operator[](unsigned int i) const {
            switch(i) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            }
        }
        Vector3<T> operator+() const {
            return Vector3<T>(*this);
        }
        Vector3<T> operator-() const {
            return Vector3<T>(-x, -y, -z);
        }
        Vector3<T> operator+(const Vector3 &rhs) const {
            return Vector3<T>(x + rhs.x, y + rhs.y, z + rhs.z);
        }
        Vector3<T> operator-(const Vector3 &rhs) const {
            return Vector3<T>(x - rhs.x, y - rhs.y, z + rhs.z);
        }
        Vector3<T> operator*(const Vector3 &rhs) const {
            return Vector3<T>(y * rhs.z - z * rhs.y, x * rhs.z - z * rhs.x,
                             x * rhs.y - y * rhs.x);
        }
        Vector3<T> operator/(const Vector3 &rhs) const {
            return Vector3<T>(y / rhs.z - z / rhs.y, x / rhs.z - z / rhs.x,
                             x / rhs.y - y / rhs.x);
        }
        Vector3<T> operator*(T scalar) const {
            return Vector3<T>(x*scalar, y*scalar, z*scalar);
        }
        Vector3<T> operator/(T scalar) const {
            return Vector3<T>(x/scalar, y/scalar, z/scalar);
        }
        
        Vector3<T> inverse() const {
            return Vector3<T>(((T)1.0)/x, ((T)1.0)/y, ((T)1.0)/z);
        }
        Vector3<T> normalize() const {
            return *this / magnitude();
        }
        Vector3<T> shuffle(int xs, int ys, int zs) const {
            return Vector3<T>((*this)[xs], (*this)[ys], (*this)[zs]);
        }
        
        T dot(const Vector3 &rhs) const {
            return x*rhs.x + y*rhs.y + z*rhs.z;
        }
        T magsquared() const {
            return x*x + y*y + z*z;
        }
        T magnitude() const {
            return std::sqrt(magsquared());
        }
        
        Vector3<T> & operator=(const Vector3<T> &rhs) {
            x = rhs.x;
            y = rhs.y;
            z = rhs.z;
            return *this;
        }
        Vector3<T> & operator+=(const Vector3<T> &rhs) {
            return *this = *this + rhs;
        }
        Vector3<T> & operator-=(const Vector3<T> &rhs) {
            return *this = *this - rhs;
        }
        Vector3<T> & operator*=(const Vector3<T> &rhs) {
            return *this = *this * rhs;
        }
        Vector3<T> & operator/=(const Vector3<T> &rhs) {
            return *this = *this / rhs;
        }
        Vector3<T> & operator*=(T scalar) {
            return *this = *this * scalar;
        }
        Vector3<T> & operator/=(T scalar) {
            return *this = *this / scalar;
        }
    };
    
    typedef Vector3<double> Vector3d;
    typedef Vector3<float> Vector3f;
    
    template <typename T>
    std::ostream & operator<<(std::ostream &out, const Vector3<T> &vec) {
        out << "<" << vec.x << ", " << vec.y << ", " <<
            vec.z << ">";
        return out;
    }
}

#endif
