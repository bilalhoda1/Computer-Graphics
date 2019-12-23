#include <fstream>
#include <iostream>
#include "../world/ViewPlane.hpp"
#include "RGBColor.hpp"
#include "Image.hpp"

Image::Image(int hres, int vres)
{
    this->hres = hres;
    this->vres = vres;
    colors = new RGBColor*[vres];
    for (int i=0; i<(hres); i++)
        colors[i] = new RGBColor[hres];
}

Image::Image(const ViewPlane& vp)
{
    hres = vp.hres;
    vres = vp.vres;
    colors = new RGBColor*[vres];
    for (int i=0; i<(hres); i++)
        colors[i] = new RGBColor[hres];
}

Image::~Image()
{
    for (int i = 0; i < hres; i++)
        delete[] colors[i];
    delete[] colors;
}

void Image::set_pixel(int x, int y, const RGBColor& color)
{
    colors[y][x] = color;
}

void Image::write_ppm(std::string path) const
{
    float mmax = 0;
    for (int r = 0; r < vres; ++r) {
        for (int c = 0; c < hres; ++c) {
            mmax = std::max(colors[r][c].r,std::max(colors[r][c].g, std::max(colors[r][c].b, mmax)));
        }
    }
    std::ofstream file(path);
    file << "P3" << '\n';
    file << hres << " " << vres << '\n';
    file << 255 << '\n';

    double scale = 255/mmax;
    for(int i = 0; i < vres; i++) //loop through the viewplane
    {
        for(int j = 0; j < hres; j++)
        {
            file << static_cast<int>(colors[i][j].r*scale) << " " <<
            static_cast<int>(colors[i][j].g*scale) << " " <<
            static_cast<int>(colors[i][j].b*scale) << " "; //draw pixels
        }
        file << '\n';
    }
    file.close();
}
