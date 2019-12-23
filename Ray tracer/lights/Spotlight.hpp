#pragma once

/**
   Courtesy Kevin Suffern.
*/

#include "../utilities/Vector3D.hpp"
#include "Point.hpp"

class Spotlight : public Point {
    private:
        Vector3D dir;  // the direction of emitted light, stored as a unit vector.
        float theta;   // the angle of the spotlight, in radians.

    public:
        // Constructors.
        Spotlight();                                 // set color to white (1, 1, 1).
        Spotlight(float c);                          // set color to (c, c, c).
        Spotlight(float r, float g, float b);        // set color to (r, g, b).
        Spotlight(const RGBColor& c);                // set color to c.

        // Copy constructor and assignment operator.
        Spotlight(const Spotlight& rhs) = default;
        Spotlight& operator=(const Spotlight& rhs) = default;

        // Luminance from this light source at hit point.
        virtual RGBColor L() const;

        // Normalized direction vector from light source to hit point.
        virtual Vector3D get_direction(const ShadeInfo& s) const;

        // Set spotlight position and angle.
        void set_theta(float t);  // set theta to t which must be in radians.

        // Set light direction. Supplied direction must be normalized for storing.
        void set_direction(float c);                    // to (c, c, c) and normalize.
        void set_direction(float x, float y, float z);  // to (x, y, z) and normalize.
        void set_direction(const Vector3D& p);          // to p and normalize.

        // Destructor.
        virtual ~Spotlight() = default;
};
