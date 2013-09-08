#ifndef _SCENE_H
#define _SCENE_H

#include "object.h"
#include "intersection.h"
#include "ray.h"

class Scene {
public:
	Scene(std::vector<Object*> obj): objects(obj){};
	Intersection* intersect(const Ray& r);
private:
	std::vector<Object*> objects;
};

#endif