
#include "Point.hpp"

using namespace cs378;

const Point Point::Origin;

Point::Point() : x(0), y(0) { }
Point::Point(double x, double y) : x(x), y(y) { }
Point::Point(const Point &source) : x(source.x), y(source.y) { }
Point::~Point() { }

Point Point::operator+(const Vector rhs) const {
    return Point(x + rhs.x, y + rhs.y);
}
Point Point::operator-(const Vector rhs) const {
    return Point(x - rhs.x, y - rhs.y);
}
Vector Point::operator-(const Point rhs) const {
    return Vector(x - rhs.x, y - rhs.y);
}

Point & Point::operator=(const Point rhs) {
    x = rhs.x;
    y = rhs.y;
    return *this;
}
Point & Point::operator+=(const Vector rhs) {
    return *this = *this + rhs;
}
Point & Point::operator-=(const Vector rhs) {
    return *this = *this - rhs;
}

std::ostream & cs378::operator<<(std::ostream & out, const cs378::Point & p) {
    return out << "(" << p.x << ", " << p.y << ")";
}
