#pragma once

/**
   This file declares BBox class which represents an axis-aligned bounding box
   defined by 2 points containing the min and max values respectively of x, y,
   and z.
*/

#include "Point3D.hpp"
#include "Vector3D.hpp"

class Geometry;
class Ray;

class BBox {
    public:
        // Diagonally opposite points.
        Point3D pmin; // min coordinates.
        Point3D pmax; // max coordinates.
        Vector3D center;
        Vector3D delta;

    public:
        // Constructors.
        BBox() = default; // both points at origin.
        BBox(const Point3D& min, const Point3D& max); // set points.

        // Copy constructor and assignment operator.
        BBox(const BBox &b) = default;
        BBox &operator=(const BBox &rhs) = default;

        // Destructor.
        ~BBox() = default;

        // String representation.
        std::string to_string() const;

        // Does ray hit bbox? If so, set entering and leaving t values for ray.
        bool hit(const Ray &ray, float &t_enter, float &t_exit) const;

        // Extend this bbox, if necessary, to include g or b.
        void extend(Geometry* g);
        void extend(const BBox& b);
        void extend(const Point3D& p);

        // Does this BBox contain p? True even when p lies on a boundary.
        bool contains(const Point3D& p);

        // Does this BBox overlap with g or b?
        bool overlaps(Geometry* g);
        bool overlaps(const BBox& b);

        int maxDimension() const;
        Vector3D getExtent() const;
};
