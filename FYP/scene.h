#ifndef _SCENE_H
#define _SCENE_H

#include "object.h"
#include "intersection.h"
#include "ray.h"

class Light;

class Scene 
{
public:
    Scene();
	Intersection* intersect(const Ray* r);
    
	inline vector<Object*> getObjects() const { return objects; };
    inline void addObject(Object* o) { objects.push_back(o); };
    
    inline vector<_Light*> getLights() const { return lights; };
    inline void addLight(_Light* l) { lights.push_back(l); };
	
	static Vec3 ambient;
	static void setAmbient(Vec3 a) { ambient = a; }
	void buildBox();
	BoundingBox* root;

	std::vector<Object*> objects;
    std::vector<_Light*> lights;
};

#endif