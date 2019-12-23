#pragma once

/**
   Courtesy Kevin Suffern.
*/

#include "../utilities/Point3D.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "Light.hpp"

class Point : public Light {
    protected:
        Point3D position;           // the position of the light source.

    public:
        // Constructors.
        Point();                                // set color to white (1, 1, 1).
        Point(float c);                         // set color to (c, c, c).
        Point(float r, float g, float b);       // set color to (r, g, b).
        Point(const RGBColor& c);               // set color to c.

        // Copy constructor and assignment operator.
        Point(const Point& rhs) = default;
        Point& operator=(const Point& rhs) = default;

        // Normalized direction vector from light source to hit Point.
        virtual Vector3D get_direction(const ShadeInfo& s) const;

        // Luminance from this light source at hit Point.
        virtual RGBColor L() const;

        // Set position of Point light source.
        void set_position(float c);                    // position at (c, c, c).
        void set_position(float x, float y, float z);  // position at (x, y, z).
        void set_position(const Point3D& p);           // position at p.
        void scale_radiance(const float b);

        // Destructor.
        virtual ~Point() = default;

        virtual bool in_shadow(const Ray& ray, const ShadeInfo& si) const override;

        void set_shadows(bool s);
};


