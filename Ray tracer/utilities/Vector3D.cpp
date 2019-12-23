#include <cmath>
#include <sstream>
#include "Point3D.hpp"
#include "Vector3D.hpp"

Vector3D::Vector3D():x(0), y(0), z(0) {}

Vector3D::Vector3D(double c):x(c), y(c), z(c) {}

Vector3D::Vector3D(double _x, double _y, double _z):x(_x), y(_y), z(_z) {}

Vector3D::Vector3D(const Point3D& p):x(p.x), y(p.y), z(p.z) {}

Vector3D& Vector3D::operator=(const Point3D& rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return (*this);
}

std::string Vector3D::to_string() const
{
    std::stringstream stream;
    stream << "(" << x << "," << y << "," << z << ")";
    return stream.str();
}

Vector3D Vector3D::operator-() const
{
    return Vector3D(-x, -y, -z);
}

Vector3D Vector3D::operator+(const Vector3D& v) const
{
    return Vector3D(x+v.x, y+v.y, z+v.z);
}

Vector3D& Vector3D::operator+=(const Vector3D& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    return (*this);
}

Vector3D Vector3D::operator-(const Vector3D& v) const
{
    return Vector3D(x-v.x, y-v.y, z-v.z);
}

Vector3D Vector3D::operator-=(const Vector3D& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return (*this);
}

Vector3D Vector3D::operator*(const double a) const
{
    return Vector3D(x*a, y*a, z*a);
}

Vector3D Vector3D::operator/(const double a) const
{
    return Vector3D(x/a, y/a, z/a);
}

void Vector3D::normalize()
{
    double len = Vector3D::length();
    this->x /= len;
    this->y /= len;
    this->z /= len;
}

double Vector3D::length() const
{
    return std::sqrt(Vector3D::len_squared());
}

double Vector3D::len_squared() const
{
    return (std::pow(x,2) + std::pow(y,2) + std::pow(z,2));
}

double Vector3D::operator*(const Vector3D& b) const
{
    return (x*b.x + y*b.y + z*b.z);
}

Vector3D Vector3D::operator^(const Vector3D& v) const
{
    return Vector3D((y*v.z)-(z*v.y), (z*v.x)-(x*v.z), (x*v.y)-(y*v.x));
}

float Vector3D::operator[](int idx) const
{
    switch (idx) {
      case 0:
        return x;
      case 1:
        return y;
    }
    return z;
}

Vector3D operator*(const double a, const Vector3D& v)
{
    return Vector3D(a*v.x, a*v.y, a*v.z);
}
