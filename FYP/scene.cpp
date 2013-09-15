#include "scene.h"

#ifdef __APPLE__
	#include <float.h>
#endif

Vec3 Scene::ambient = Vec3(0.2, 0.2, 0.2);

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
				if (intc != NULL) {
					delete intc;
				}
				intc = temp;
				min  = intc->t;
			}
		}
	}
	return intc;
}