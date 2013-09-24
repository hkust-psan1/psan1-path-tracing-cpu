#ifndef _BOUNDINGBOX_H
#define _BOUNDINGBOX_H

#include "vec3.h"
#include <vector>
#include "face.h"

class Face;
class Intersection;

class BoundingBox
{
public:	
	BoundingBox* left;
	BoundingBox* right;
	Face* face;
	void partition(std::vector<BoundingBox*>);

	BoundingBox(Vec3 m, Vec3 M) : isLeaf(false), left(0), right(0), face(0), boxMin(m), boxMax(M) {}
	BoundingBox(Face* f);
	Intersection* intersect(const Ray& r, float T_min);
	Vec3 shadowAttenuation(const Ray& r, float T_min);
	void mergeBox(BoundingBox* b);
	void mergePoint(Vec3 p);

private:
	bool intersectBox(const Ray& r, float T_min);
	Vec3 boxMin;
	Vec3 boxMax;
	int pivot;
	float midLine;
	bool isLeaf;
};
#endif