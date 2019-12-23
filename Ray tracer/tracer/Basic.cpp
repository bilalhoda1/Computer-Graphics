#include "Basic.h"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../world/World.hpp"
#include "../materials/Material.hpp"

Basic::Basic() {
    this->world_ptr = nullptr;
}

Basic::Basic(World* w_ptr) {
    this->world_ptr = w_ptr;
}

RGBColor Basic::trace_ray(const Ray ray, const int depth) const {
    ShadeInfo sinfo = world_ptr->hit_objects(ray);
    if (sinfo.hit){
          return ray.w * sinfo.material_ptr->shade(sinfo);
    }
	else{
          return ray.w * world_ptr->bg_color;
    }
}
