#include "Sampler.hpp"

Sampler::Sampler() : camera_ptr(nullptr), viewplane_ptr(nullptr)
{}

Sampler::Sampler(Camera* c_ptr, ViewPlane* v_ptr) : camera_ptr(c_ptr), viewplane_ptr(v_ptr)
{}

int Sampler::get_num_rays() {
    return num_rays;
}
