#include "../materials/Material.hpp"
#include "Geometry.hpp"

Geometry::Geometry() : material_ptr(nullptr)
{}

Material* Geometry::get_material() const {
    return material_ptr;
}

void Geometry::set_material(Material* mPtr) {
    if (material_ptr != nullptr) {
        material_ptr = nullptr;
    }
    material_ptr = mPtr;
}
