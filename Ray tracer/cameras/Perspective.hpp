#pragma once

/**
   This file declares the Perspective class which represents a perspective
   viewing camera.

   Courtesy Kevin Suffern.
*/

#include "Camera.hpp"
#include "../utilities/Point3D.hpp"

class Vector3D;

class Perspective : public Camera {
    protected:
        Point3D pos;        // center of projection.

    public:
        // constructors.
        Perspective();                          // set pos to origin.
        Perspective(float c);                   // set pos to (c, c, c).
        Perspective(float x, float y, float z); // set pos to (x, y, z)
        Perspective(const Point3D &pt);         // set pos parallel to pt.

        // copy constuctor and assignment operator.
        Perspective(const Perspective &camera);
        Perspective &operator=(const Perspective &other);

        // desctructor.
        virtual ~Perspective() = default;

        // Get direction of projection for a point.
        virtual Vector3D get_direction(const Point3D &p) const;
};
