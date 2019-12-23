#pragma once

/**
   This file declares the Sphere class which represents a sphere defined by its
   center and radius.

   Courtesy Kevin Suffern.
*/

#include "Geometry.hpp"
#include "../utilities/Point3D.hpp"

class Sphere : public Geometry {
    protected:
        Point3D c;      // center.
        float r;        // radius.

    public:
        // constructors.
        Sphere();                                       // sphere at origin with radius 0.
        Sphere(const Point3D &center, float radius);    // set center and radius,

        // copy constructor and assignment operator.
        Sphere(const Sphere &object);
        Sphere &operator=(const Sphere &rhs);

        // destructor.
        virtual ~Sphere() = default;

        // string representation.
        std::string to_string() const override;

        // ray intersection. Set t and sinfo as per intersection with this object.
        virtual bool hit(const Ray &ray, float &t, ShadeInfo &s) const override;

        // shadow ray intersection
        virtual bool shadow_hit(const Ray& ray, float& tmin) const override;

        // get bounding box.
        virtual BBox getBBox() const override;
        virtual Point3D getCenter() const override;
};
