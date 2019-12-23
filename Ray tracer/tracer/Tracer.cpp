#include "Tracer.h"
#include "../utilities/Constants.hpp"
#include "../utilities/Ray.hpp"

Tracer::Tracer(): world_ptr(NULL)
{}

Tracer::Tracer(World* w_ptr):world_ptr(w_ptr)
{}

RGBColor Tracer::trace_ray(const Ray ray, const int depth) const {
    return black;
}
