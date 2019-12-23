#include "Directional.hpp"
#include "../world/World.hpp"
#include "../geometry/Geometry.hpp"

Directional::Directional() : Light()
{}

Directional::Directional(float c) : Light(c)
{}

Directional::Directional(float r, float g, float b) : Light(r, g, b)
{}

Directional::Directional(const RGBColor& c) : Light(c)
{}

void Directional::set_direction(float x, float y, float z) {
    dir = Vector3D(x, y, z);
    dir.normalize();
}

void Directional::set_direction(const Vector3D& d) {
    dir = Vector3D(d);
    dir.normalize();
}

Vector3D Directional::get_direction(const ShadeInfo& s) const {
    return dir;     // shadeInfo isn't required in this
}

RGBColor Directional::L() const {
    return color;
}

bool Directional::in_shadow(const Ray& ray, const ShadeInfo& si) const {
    float t;
    int num_objects = si.w->geometry.size();
    Ray d(ray.o, dir);

    for (int i = 0; i < num_objects; i++)
        if (si.w->geometry[i]->shadow_hit(d, t) && t > 0.001)
            return true;
    return false;
}

void Directional::set_shadows(bool s) {
    shadows = s;
}
