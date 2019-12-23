#include "Parallel.hpp"

Parallel::Parallel() {
	dir.x = 0;
	dir.y = 0;
	dir.z = -1;
}

Parallel::Parallel(float c) {
	dir.x = c;
	dir.y = c;
	dir.z = c;
	dir.normalize();
}

Parallel::Parallel(float x, float y, float z) {
	dir.x = x;
	dir.y = y;
	dir.z = z;
	dir.normalize();
}

Parallel::Parallel(const Vector3D &d) {
	dir = d;
	dir.normalize();
}

Parallel::Parallel(const Parallel &camera) {
	this->dir = camera.dir;
}

Vector3D Parallel::get_direction(const Point3D &p) const {
	return this->dir;
}
