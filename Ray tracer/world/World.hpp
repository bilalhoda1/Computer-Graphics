#pragma once

/**
   This file declares the World class which contains all the information about
   the scene - geometry and materials, lights, viewplane, camera, samplers, and
   acceleration structures.

   It also traces rays through the scene.

   Courtesy Kevin Suffern.
*/

#include <vector>

#include "../utilities/RGBColor.hpp"

#include "ViewPlane.hpp"

class Camera;
class Geometry;
class Ray;
class Sampler;
class ShadeInfo;
class Acceleration;
class Tracer;
class Light;
class Ambient;
class Material;

class World {
public:
  ViewPlane vplane;
  RGBColor bg_color;
  std::vector<Geometry *> geometry;
  std::vector<Light*> lights;
  Light* ambient_ptr;
  Camera *camera_ptr;
  Sampler *sampler_ptr;
  Acceleration *acceleration_ptr;
  Tracer *tracer_ptr;

public:
  // Constructors.
  World(); // initialize members.

  // Destructor.
  ~World(); // free memory.

  // Add to the scene.
  void add_geometry(Geometry *geom_ptr);
  void add_light(Light* light_ptr);
  void set_camera(Camera *c_ptr);
  void set_acceleration(Acceleration* a_ptr);
  void set_tracer(Tracer* t_ptr);
  void set_ambient_light(Ambient* amb_ptr);

  // Build scene - add all geometry, materials, lights, viewplane, camera,
  // samplers, and acceleration structures
  void build();

  // Returns appropriate shading information corresponding to intersection of
  // the ray with the scene geometry.
  ShadeInfo hit_objects(const Ray &ray);
  void add_mesh(std::string filename, Material* material_ptr, Point3D bottom, Point3D top);
};
