#pragma once

/**
   This file declares the Geometry class which is an abstract class from which
   other concrete geometric objects will inherit.

   Courtesy Kevin Suffern.
*/

#include <string>

class BBox;
class Material;
class Ray;
class ShadeInfo;
class Point3D;

class Geometry {
    protected:
        Material *material_ptr;     // this object's material.

    public:
        // constructors.
        Geometry();                 // sets material_ptr to NULL.

        // copy constructor and assignment operator.
        Geometry(const Geometry &object) = default;
        Geometry &operator=(const Geometry &rhs) = default;

        // destructor.
        virtual ~Geometry() = default;

        // string representation.
        virtual std::string to_string() const = 0;

        // get/set material.
        Material *get_material() const;
        void set_material(Material *mPtr);

        // ray intersection. Set t and sinfo as per intersection with this object.
        virtual bool hit(const Ray &ray, float &t, ShadeInfo &sinfo) const = 0;

        // shadow ray intersection
        virtual bool shadow_hit(const Ray& ray, float& t) const = 0;

        // get bounding box.
        virtual BBox getBBox() const = 0;
        virtual Point3D getCenter() const = 0;
};
