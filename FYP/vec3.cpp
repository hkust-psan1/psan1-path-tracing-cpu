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

Vec3& Vec3::operator+=(const Vec3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vec3& Vec3::operator-=(const Vec3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vec3& Vec3::operator*=(const Vec3& v) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

Vec3 operator+(const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

Vec3 operator-(const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

Vec3 operator*(const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

Vec3 operator*(const Vec3& v1, const float& f) {
	return Vec3(v1.x *f, v1.y * f, v1.z * f);
}

float dot(const Vec3& v1, const Vec3& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vec3 cross(const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}