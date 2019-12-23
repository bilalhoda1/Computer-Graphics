#pragma once

/**
   Courtesy Kevin Suffern.
*/

#include "../utilities/RGBColor.hpp"

class Vector3D;
class ShadeInfo;
class Ray;

class Light {
    protected:
        RGBColor color;     // the light's color.
        float ls;           // luminance
        bool shadows;       // casts shadows or not

    public:
        // Constructors.
        Light();                                 // set color to white (1, 1, 1).
        Light(float c);                          // set color to (c, c, c).
        Light(float r, float g, float b);        // set color to (r, g, b).
        Light(const RGBColor& c);                // set color to c

        // Copy constructor and assignment operator.
        Light(const Light& rhs) = default;
        Light& operator=(const Light& rhs) = default;

        // Normalized direction vector from light source to hit point.
        virtual Vector3D get_direction(const ShadeInfo& s) const = 0;

        // Luminance from this light source at hit point.
        virtual RGBColor L() const = 0;

        // Set color.
        void set_color(const float c);              // to (c, c, c)
        void set_color(float r, float g, float b);  // to (r, g, b).
        void set_color(const RGBColor& c);     // to c.

        // Destructor.
        virtual ~Light() = default;

        bool casts_shadows() const;
        virtual bool in_shadow(const Ray& ray, const ShadeInfo& si) const = 0;
};
