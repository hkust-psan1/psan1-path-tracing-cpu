#include <cmath>
#include "vec3.h"

Vec3::Vec3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3::Vec3(float c[3]) {
	x = c[0];
	y = c[1];
	z = c[2];
}

Vec3::Vec3(const Vec3& v) {
	x = v.x;
	y = v.y;
	z = v.z;
}

inline float Vec3::length() const {
	return sqrt(x * x + y * y + z * z);
}

void Vec3::normalize() {
	float l = length();
	x /= l;
	y /= l;
	z /= l;
}