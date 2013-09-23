#ifndef _VEC3_H
#define _VEC3_H

#include "includes.h"

class Vec3 {
public:
	Vec3(){x = 0; y = 0; z = 0;};
	Vec3(float x, float y, float z);
	Vec3(float f) {x = f; y = f; z = f;}
	Vec3(float c[3]);
	Vec3(const Vec3& v);

	inline float length() const { return sqrt(x * x + y * y + z * z); };
	void normalize();
	void clamp();

	Vec3& operator+=(const Vec3& v);
	Vec3& operator-=(const Vec3& v);
	Vec3& operator*=(const Vec3& v);
    
    Vec3& operator=(const Vec3& v);
    float& operator[](int n);
	float get(int n) const;
	int maxElement();

	friend Vec3 operator+(const Vec3& v1, const Vec3& v2);
	friend Vec3 operator-(const Vec3& v1, const Vec3& v2);
	friend Vec3 operator*(const Vec3& v1, const Vec3& v2);
	friend Vec3 operator*(const Vec3& v1, float n);

	friend float dot(const Vec3& v1, const Vec3& v2);
	friend Vec3 cross(const Vec3& v1, const Vec3& v2);

	friend std::ostream& operator<<(std::ostream& os, const Vec3& v) {
		os << v.x << '\t' << v.y << '\t' << v.z << std::endl;
		return os;
	}

	float x;
	float y;
	float z;
};

#endif