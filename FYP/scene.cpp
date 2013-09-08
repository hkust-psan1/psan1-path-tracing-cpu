#include "scene.h"

Intersection* Scene::intersect(const Ray& r)
{
	float min = FLT_MAX;
	Intersection* intc = NULL;
	for (Object* obj : objects)
	{
		for (Face* f : obj->getFaces())
		{
			Intersection* temp = f->intersect(r, min);
			if (temp != NULL)
			{
				if (intc != NULL)
					delete intc;
				intc = temp;
			}
		}
	}
	return intc;
}