#include "scene.h"

#ifdef __APPLE__
	#include <float.h>
#endif

#include "setting.h"

Vec3 Scene::ambient = Vec3(.4f);

Scene::Scene(std::vector<Object*> obj): objects(obj)
{

}

void Scene::buildBox()
{
	Vec3 min = Vec3(FLT_MAX);
	Vec3 max = Vec3(-FLT_MAX);
	root = new BoundingBox(min, max);
	std::vector<BoundingBox*> boxes;
	for (Object* obj : objects)
	{
		root->mergeBox(obj->root);
		boxes.push_back(obj->root);
	}
	root->partition(boxes);
}

Intersection* Scene::intersect(const Ray* r)
{
	if (Setting::HBV)
		return root->intersect(r, FLT_MAX);	

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
				{
					delete intc;
				}
				intc = temp;
				min  = intc->t;
			}
		}
	}
	return intc;
}