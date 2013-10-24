#ifndef _INTERSECTION_H
#define _INTERSECTION_H

#include "Ray.h"
#include "Material.h"
#include "object.h"

class Object;

class Intersection {
public:
	Intersection(Object* obj, Material* mat, const Vec3& normal, const Vec3& tangent, const Vec3& bitangent, const Vec3& tc, float t)
		: obj(obj), mat(mat), normal(normal), tangent(tangent), bitangent(bitangent), texCoord(tc), position(position), t(t){};
	Object* obj;
	Material* mat;
	Vec3 normal;
    Vec3 tangent;
    Vec3 bitangent;
    Vec3 texCoord;
	Vec3 position;
	float t;
private:

};

#endif