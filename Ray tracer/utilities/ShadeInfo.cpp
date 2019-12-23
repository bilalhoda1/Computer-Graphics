#include "ShadeInfo.hpp"
#include "../utilities/Constants.hpp"

ShadeInfo::ShadeInfo(const World& wr):
    hit(false), material_ptr(NULL), hit_point(),
    local_hit_point(), normal(), ray(),
    depth(0), dir(), t(kEpsilon), w(&wr) {}
