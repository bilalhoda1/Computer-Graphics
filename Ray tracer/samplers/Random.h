#pragma once
/**
    Courtesy Kevin Suffern
*/
#include "Sampler.hpp"

class Random : public Sampler {
    public:
        Random() = default;
        Random(Camera *c_ptr, ViewPlane *v_ptr, int n); // set members.

        // Copy constuctor and assignment operator.
        Random(const Random &camera);
        Random &operator=(const Random &other);

        // Desctructor.
        virtual ~Random() = default;

        // Shoot a ray of weight 1 through the center of the pixel.
        std::vector<Ray> get_rays(int px, int py) const override;
};
