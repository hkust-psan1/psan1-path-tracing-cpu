#ifndef _INTERSECTION_H
#define _INTERSECTION_H

#include "Ray.h"
#include "Material.h"
#include "object.h"


class Intersection {
public:
	Intersection(Object* obj, Material* mat, const Vec3& normal, const Vec3& position, float t)
		: obj(obj), mat(mat), normal(normal), position(position), t(t){};

	Object* obj;
	Material* mat;
	Vec3 normal;
	Vec3 position;
	float t;
private:

};

#endif