#include "object.h"
#define EPSILON 0.0001 

Object::Object() {
    // mat = new Material();
}

void Object::addFace(Face* f) {
	faces.push_back(f);
	f->setObject(this);
}

int max_of(const float* d)
{
	if (d[0] > d[1])
	{
		if (d[0] > d[2]) return 0;
		return 2;
	}
	else
	{
		if (d[1] > d[2]) return 1;
		return 2;
	}
}

int min_of(const float* d)
{
	if (d[0] < d[1])
	{
		if (d[0] < d[2]) return 0;
		return 2;
	}
	else
	{
		if (d[1] < d[2]) return 1;
		return 2;
	}
}

Intersection* Object::intersect(const Ray& r, float T_min)
{
	Vec3 d = Vec3(r.dir);
	Vec3 p = r.pos;

	for (int i = 0; i < 3; i++)
		if (d[i] == 0.0)
			d[i] = FLT_MIN; 

	float min[3] = {};
	float max[3] = {};

	for (int j = 0; j < 3; j++)
	{
		if (d[j] > 0)
		{
			min[j] = (boundingBoxMin[j] - p[j]) / d[j];
			max[j] = (boundingBoxMax[j] - p[j]) / d[j];
		}
		else
		{
			min[j] = (boundingBoxMax[j] - p[j]) / d[j];
			max[j] = (boundingBoxMin[j] - p[j]) / d[j];
		}
	}

	int max_of_min = max_of(min);
	int min_of_max = min_of(max);

	//no intersection point
	if (max[min_of_max] < min[max_of_min]) return NULL;

	//t < 0
	if (max[min_of_max] < EPSILON) return NULL;
	
	float min_t = FLT_MAX;
	Intersection* intc = NULL;

	for (Face* f : faces)
	{
		Intersection* temp = f->intersect(r, min_t);
		if (temp != NULL)
		{
			if (intc != NULL) 
			{
				delete intc;
			}
			intc = temp;
			min_t  = intc->t;
		}
	}

	return intc;
}