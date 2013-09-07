#ifndef _VEC3_H
#define _VEC3_H

#include "includes.h"

class Vec3 {
public:
	Vec3(float x, float y, float z);
	Vec3(float c[3]);
	Vec3(const Vec3& v);
	inline float length() const;
	void normalize();
	float x;
	float y;
	float z;
};

#endif