
#include "Vector.hpp"
#include <cmath>

using namespace cs378;

Vector::Vector() : x(0), y(0) { }
Vector::Vector(double x, double y) : x(x), y(y) { }
Vector::Vector(const Vector &source) : x(source.x), y(source.y) { }
Vector::~Vector() { }

Vector Vector::operator+(const Vector rhs) const {
    return Vector(x + rhs.x, y + rhs.y);
}
Vector Vector::operator-(const Vector rhs) const {
    return Vector(x - rhs.x, y - rhs.y);
}
Vector Vector::operator*(double scalar) const {
    return Vector(x * scalar, y * scalar);
}
Vector Vector::operator/(double scalar) const {
    return Vector(x / scalar, y / scalar);
}

double Vector::operator%(const Vector rhs) const {
    return x * rhs.x + y * rhs.y;
}

Vector & Vector::operator=(const Vector rhs) {
    x = rhs.x;
    y = rhs.y;
    return *this;
}
Vector & Vector::operator+=(const Vector rhs) {
    return *this = *this + rhs;
}
Vector & Vector::operator-=(const Vector rhs) {
    return *this = *this - rhs;
}
Vector & Vector::operator*=(double scalar) {
    return *this = *this * scalar;
}
Vector & Vector::operator/=(double scalar) {
    return *this = *this / scalar;
}

Vector Vector::inverse() const {
    return Vector(1.0 / x, 1.0 / y);
}

Vector Vector::normalize() const {
    return *this / magnitude();
}
double Vector::magsquared() const {
    return x*x + y*y;
}
double Vector::magnitude() const {
    return std::sqrt(magsquared());
}

Vector cs378::operator*(double scalar, Vector rhs) {
    return rhs * scalar;
}

std::ostream & cs378::operator<<(std::ostream & out, const cs378::Vector & v) {
    return out << "<" << v.x << ", " << v.y << ">";
}
