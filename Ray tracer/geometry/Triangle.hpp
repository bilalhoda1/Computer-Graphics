#pragma once

/**
   This file declares the Triangle class which represents a triangle defined by
   its 3 vertices.

   Courtesy Kevin Suffern.
*/

#include "Geometry.hpp"
#include "../utilities/Point3D.hpp"

class Triangle : public Geometry {
    protected:
        Point3D v0, v1, v2;     // the vertices (must not be colinear)

    public:
        // constructors. Passed vertices are assumed to be ordered for orientation
        Triangle();                                                     // triangle with vertices at origin.
        Triangle(const Point3D &, const Point3D &, const Point3D &);    // set vertices.

        // copy constructor and assignment operator.
        Triangle(const Triangle &object);
        Triangle &operator=(const Triangle &rhs);

        // destructor.
        virtual ~Triangle() = default;

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
