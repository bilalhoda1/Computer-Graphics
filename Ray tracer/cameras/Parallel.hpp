#pragma once

/**
   This file declares the Parallel class which represents a parallel viewing
   camera.

   Courtesy Kevin Suffern.
*/

#include "Camera.hpp"
#include "../utilities/Vector3D.hpp"

class Parallel : public Camera {
    protected:
        Vector3D dir;       // direction of projection, stored as a unit vector.

    public:
        // constructors.
        Parallel();                             // set dir parallel to -z (negative z) axis.
        Parallel(float c);                      // set dir parallel to (c, c, c).
        Parallel(float x, float y, float z);    // set dir parallel to (x, y, z)
        Parallel(const Vector3D &d);            // set dir parallel to d.

        // copy constuctor and assignment operator.
        Parallel(const Parallel &camera);
        Parallel &operator=(const Parallel &other);

        // desctructor.
        virtual ~Parallel() = default;

        // get direction of projection for a point.
        virtual Vector3D get_direction(const Point3D &p) const;
};
