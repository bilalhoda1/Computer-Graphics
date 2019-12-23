#include <iostream>
#include <string>
#include "../utilities/BBox.hpp"
#include "../geometry/Geometry.hpp"
#include "../geometry/Triangle.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../acceleration/Acceleration.h"
#include "../tracer/Tracer.h"
#include "../lights/Ambient.hpp"
#include "../samplers/Sampler.hpp"
#include "../cameras/Camera.hpp"
#include "../happly/happly.h"
#include "World.hpp"

using namespace std;

World::World(): bg_color(0), ambient_ptr(new Ambient), camera_ptr(NULL), sampler_ptr(NULL),
                acceleration_ptr(NULL), tracer_ptr(NULL) {}

World::~World()
{
    geometry.clear();
    std::vector<Geometry*>().swap(geometry);
    lights.clear();
    std::vector<Light*>().swap(lights);

    delete camera_ptr;
    delete sampler_ptr;
    delete acceleration_ptr;
    delete tracer_ptr;
    delete ambient_ptr;

}

void World::add_geometry(Geometry* geom_ptr)
{
    geometry.push_back(geom_ptr);
}

void World::add_light(Light* light_ptr)
{
    lights.push_back(light_ptr);
}

void World::set_camera(Camera* c_ptr)
{
    camera_ptr = c_ptr;
}

void World::set_acceleration(Acceleration* a_ptr)
{
    acceleration_ptr = a_ptr;
}

void World::set_tracer(Tracer* t_ptr)
{
    tracer_ptr = t_ptr;
}

void World::set_ambient_light(Ambient* amb_ptr)
{
    if (ambient_ptr){
        delete ambient_ptr;
    }
    ambient_ptr = amb_ptr->clone();
}

ShadeInfo World::hit_objects(const Ray& ray)
{
    if (acceleration_ptr != NULL){
        return acceleration_ptr->hit(ray);
    }

    ShadeInfo s(*this);
    float t;
    float tmin = kHugeValue;
    Vector3D normal;
    Point3D local_hit;
    for (unsigned int i = 0; i < geometry.size(); i++){
        if (geometry[i]->hit(ray, t, s) && (t < tmin)){
            s.hit = true;
            tmin = t;
            s.material_ptr = geometry[i]->get_material();
            normal = s.normal;
            local_hit = s.hit_point;
        }
    }
    if (s.hit){
        s.t = tmin;
        s.normal = normal;
        s.hit_point = local_hit;
    }
    return s;
}

void World::add_mesh(std::string filename, Material* material_ptr, Point3D bottom, Point3D top) {

    happly::PLYData plyIn(filename);
    std::vector<array<double, 3>> vertices = plyIn.getVertexPositions();
    std::vector<vector<size_t>> faces = plyIn.getFaceIndices<size_t>();
    std::vector<Point3D> points;

    Point3D modelMin(vertices[0][0], vertices[0][1], vertices[0][2]);
    Point3D modelMax(vertices[0][0], vertices[0][1], vertices[0][2]);
    /*std::cout << "vertices stores " << int(vertices.size()) << " numbers.\n";
    std::cout << "vertices " << vPos[1][0] << " numbers.\n";
    std::cout << "fInd stores " << int(fInd.size()) << " numbers.\n";
    std::cout << "vertices " << int(fInd[0].size()) << " numbers.\n";
    std::cout << modelMin.to_string()<<endl;*/

    for (const auto& i : vertices) {
        //std::cout << "vertices " << int(point[0])<<int(point[1])<<int(point[2]) << " numbers.\n";
        Point3D obj(i[0], i[1], i[2]);
        points.push_back(obj);
        modelMin = min(modelMin, obj);
        modelMax = max(modelMax, obj);
    }

    for (auto& p: points) {
        p = Point3D::interpolate(modelMin, modelMax, p, bottom, top);
    }

    for (const auto& f : faces) {
      //std::cout << points[f[0]].to_string() << std::endl;

      Triangle* mesh_triangle = new Triangle(points[f[0]], points[f[1]], points[f[2]]);
      mesh_triangle->set_material(material_ptr);
      add_geometry(mesh_triangle);
    }
    //delete material_ptr;

}

