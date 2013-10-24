#include <cmath>
#include "vec3.h"

#define PI 3.1415926536f
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

bool operator<(const Vec3& v1, const Vec3& v2) {
	return v1.x < v2.x && v1.y < v2.y && v1.z < v2.z;
}

bool operator>(const Vec3& v1, const Vec3& v2) {
    return v1.x > v2.x && v1.y > v2.y && v1.z > v2.z;
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

std::ostream& operator<<(std::ostream& os, const Vec3& v) {
    os << v.x << '\t' << v.y << '\t' << v.z << std::endl;
    return os;
};

Vec3 Vec3::randomize(float r) {
    float rand1 = (float)rand() / (float)RAND_MAX;
    float rand2 = (float)rand() / (float)RAND_MAX;
    
    float X = sqrt(- 2 * log(rand1)) * cos(2 * M_PI * rand2) * r / 10;
    float Y = sqrt(- 2 * log(rand1)) * sin(2 * M_PI * rand2) * r / 10;
    // printf("%.3f\t%.3f\n", X, Y);
    
    Vec3 u = *this;
    u.x += 1; // create a vector not parallel to v
    
    Vec3 e1 = cross(u, *this);
    Vec3 e2 = cross(*this, e1);
    
    e1.normalize();
    e2.normalize();

    Vec3 randVec = *this + e1 * X + e2 * Y;
    randVec.normalize();
    
    return randVec;
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

float Vec3::get(int n) const
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

int Vec3::maxElement()
{
	if (x > y)
	{
		return x > z ? 0 : 2;
	}
	else
	{
		return y > z ? 1 : 2;
	}
}

