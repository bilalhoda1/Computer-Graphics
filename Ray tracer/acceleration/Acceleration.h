#pragma once

/**
   This file declares the Acceleration class which is an abstract class for all the
   acceleration structures used.
*/

#include <vector>

class Ray;
class ShadeInfo;
class World;

class Acceleration {
    protected:
        World* world_ptr;

    public:
        Acceleration() = default;
        virtual ShadeInfo hit(const Ray &ray) = 0;
        virtual ~Acceleration() = default;
};
