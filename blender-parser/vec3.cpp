#include <cmath>
#include "vec3.h"

Vec3::Vec3(float x, float y, float z) {
	coords[0] = x;
	coords[1] = y;
	coords[2] = z;
}

Vec3::Vec3(float c[3]) {
	coords[0] = c[0];
	coords[1] = c[1];
	coords[2] = c[2];
}

Vec3::Vec3(const Vec3& v) {
	coords[0] = v.coords[0];
	coords[1] = v.coords[1];
	coords[2] = v.coords[2];
}

inline float Vec3::getX() const {
	return coords[0];
}

inline float Vec3::getY() const {
	return coords[1];
}

inline float Vec3::getZ() const {
	return coords[2];
}

inline float Vec3::length() const {
	return sqrt(coords[0] * coords[0] + coords[1] * coords[1] + coords[2] * coords[2]);
}

void Vec3::normalize() {
	float l = length();
	coords[0] /= l;
	coords[1] /= l;
	coords[2] /= l;
}