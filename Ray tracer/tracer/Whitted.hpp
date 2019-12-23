#pragma once

/** Whitted Tracer - Updates depth in ShadeInfo
    Courtesy Kevin Suffern
**/

#include "Tracer.h"

class Whitted : public Tracer {
    public:
        Whitted();
        Whitted(World* w_ptr);

        virtual ~Whitted() = default;

        virtual RGBColor trace_ray(const Ray ray, const int depth) const;
};
