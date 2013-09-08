#ifndef _RAY_H
#define _RAY_H

#include "vec3.h"

class Ray {
public:
	Ray(const Vec3& p, const Vec3& d);
	Vec3 pos;
	Vec3 dir;
};

#endif