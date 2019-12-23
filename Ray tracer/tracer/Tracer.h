#pragma once

/**
    This file declares tracer class which is an abstract class from which
    different types of ray tracers inherit.
**/

class RGBColor;
class World;
class Ray;

class Tracer {
    protected:
        World* world_ptr;

    public:
        Tracer();
        Tracer(World* w_ptr);
        virtual RGBColor trace_ray(const Ray ray, const int depth) const;
        virtual ~Tracer() = default;
};
