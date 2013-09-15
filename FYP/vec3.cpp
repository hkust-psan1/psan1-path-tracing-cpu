#include <cmath>
#include "vec3.h"

#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)

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

Vec3& Vec3::operator=(const Vec3& v) {
    x = v.x;
   	y = v.y;
	z = v.z;
    return *this;
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

void Vec3::clamp() {
	x = min(x, 1.0f);
	y = min(y, 1.0f);
	z = min(z, 1.0f);
	x = max(x, .0f);
	y = max(y, .0f);
	z = max(z, .0f);
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

Vec3 operator*(const Vec3& v1, float n) {
	return Vec3(v1.x * n, v1.y * n, v1.z * n);
}

float dot(const Vec3& v1, const Vec3& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vec3 cross(const Vec3& v1, const Vec3& v2) {
	return Vec3(v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}

float& Vec3::operator[](int n)
{
	switch(n)
	{
	default:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	}
}
