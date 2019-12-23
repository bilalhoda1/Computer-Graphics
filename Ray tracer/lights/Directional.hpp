#pragma once

/**
   Courtesy Kevin Suffern.
*/

#include "../utilities/Vector3D.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "Light.hpp"

class Directional : public Light {
    protected:
        Vector3D dir;       // the direction of emitted light, stored as a unit vector.

    public:
        // Constructors.
        Directional();                           // set color to white (1, 1, 1).
        Directional(float c);                    // set color to (c, c, c).
        Directional(float r, float g, float b);  // set color to (r, g, b).
        Directional(const RGBColor& c);          // set color to c.

        // Copy constructor and assignment operator.
        Directional(const Directional& rhs) = default;
        Directional& operator=(const Directional& rhs) = default;

        // Normalized direction vector from light source to hit point.
        virtual Vector3D get_direction(const ShadeInfo& s) const;
        virtual bool in_shadow(const Ray& ray, const ShadeInfo& si) const override;

        // Luminance from this light source at hit point.
        virtual RGBColor L() const;

        // Set light direction.
        void set_direction(const Vector3D& d);
        void set_direction(float x, float y, float z);

        // Destructor.
        virtual ~Directional() = default;

        void set_shadows(bool s);
};
