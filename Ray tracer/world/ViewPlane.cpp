#include "ViewPlane.hpp"

ViewPlane::ViewPlane() :
    top_left(320, 240, 100), bottom_right(-320, -240, 100),
    hres(640), vres(480), max_depth(0) {}

int ViewPlane::get_hres() const
{
    return hres;
}

void ViewPlane::set_hres(int h)
{
    hres = h;
}

int ViewPlane::get_vres() const
{
    return vres;
}

void ViewPlane::set_vres(int v)
{
    vres = v;
}

void ViewPlane::set_maxdepth(int d)
{
    max_depth = d;
}

