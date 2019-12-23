#include <sstream>
#include <iostream>
#include "../geometry/Geometry.hpp"
#include "Constants.hpp"
#include "Point3D.hpp"
#include "Ray.hpp"
#include "BBox.hpp"
#include "Vector3D.hpp"

BBox::BBox(const Point3D& min, const Point3D& max):pmin(min), pmax(max), delta(pmax - pmin)
{}

std::string BBox::to_string() const {
    std::stringstream stream;
    stream << "pmin: " << pmin.to_string() << '\n';
    stream << "pmax: " << pmax.to_string();
    return stream.str();
}

bool BBox::hit(const Ray& ray, float& t_enter, float& t_exit) const {
    float txmin, txmax, tymin, tymax, tzmin, tzmax;

    float x = 1.0/ray.d.x;
    if (x >= 0){
        txmin = (pmin.x - ray.o.x)*x;
        txmax = (pmax.x - ray.o.x)*x;
    }
    else{
        txmin = (pmax.x - ray.o.x)*x;
        txmax = (pmin.x - ray.o.x)*x;
    }

    float y = 1.0/ray.d.y;
    if (y >= 0){
        tymin = (pmin.y - ray.o.y)*y;
        tymax = (pmax.y - ray.o.y)*y;
    }
    else{
        tymin = (pmax.y - ray.o.y)*y;
        tymax = (pmin.y - ray.o.y)*y;
    }

    float z = 1.0/ray.d.z;
    if (z >= 0){
        tzmin = (pmin.z - ray.o.z)*z;
        tzmax = (pmax.z - ray.o.z)*z;
    }
    else{
        tzmin = (pmax.z - ray.o.z)*z;
        tzmax = (pmin.z - ray.o.z)*z;
    }

    t_enter = std::max(std::max(txmin, tymin), tzmin); //largest entering value
    t_exit = std::min(std::min(txmax, tymax), tzmax); //smallest exiting value

    return ((t_enter < t_exit) && (t_exit > kEpsilon));
}

void BBox::extend(Geometry* g) {
    this->pmin = min(g->getBBox().pmin, pmin);
    this->pmax = max(g->getBBox().pmax, pmax);
}

void BBox::extend(const BBox& b) {
    this->pmin = min(b.pmin, pmin);
    this->pmax = max(b.pmax, pmax);
    delta = pmax - pmin;
}

void BBox::extend(const Point3D& p) {
    this->pmin = min(pmin, p);
    this->pmax = max(pmax, p);
    delta = pmax - pmin;
}

bool BBox::contains(const Point3D& p) {
    return ((p.x > pmin.x && p.x < pmax.x) && (p.y > pmin.y && p.y < pmax.y) && (p.z > pmin.z && p.z < pmax.z));
}

bool BBox::overlaps(Geometry* g) {
    BBox temp = g->getBBox();
    return ((pmax.x > temp.pmin.x) && (pmax.y > temp.pmin.y) && (pmax.z > temp.pmin.z));
}

bool BBox::overlaps(const BBox& b) {
    return ((pmax.x > b.pmin.x) && (pmax.y > b.pmin.y) && (pmax.z > b.pmin.z));
}
int BBox::maxDimension() const {
    if (delta.x > delta.y) {
        if (delta.x > delta.z) return 0;
        return 2;
    }
    if (delta.y > delta.z) return 1;
    return 2;
}

Vector3D BBox::getExtent() const {
    return delta;
}
