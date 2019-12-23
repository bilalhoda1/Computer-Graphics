#include <sstream>
#include "Ray.hpp"

Ray::Ray():o(0, 0, 0), d(0, 0, 0), w(1) {}

Ray::Ray(const Point3D& origin, const Vector3D& dir):o(origin), d(dir), w(1) {}

std::string Ray::to_string() const
{
    std::stringstream stream;
    stream << "origin point: (" << o.x << "," << o.y << "," << o.z << ")" << '\n';
    stream << "direction vector: (" << d.x << "," << d.y << "," << d.z << ")";
    return stream.str();
}
