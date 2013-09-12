#include "light.h"

Scene* Light::scene = NULL;

Vec3 DirectionalLight::shadowAttenuation(const Vec3& P ) const
{
	Ray r = Ray(P, direction);
	float t = FLT_MAX; //large
    //return scene->shadowAttenuation(r, t);
	return Vec3(1, 1, 1);
}