#include "light.h"
#include "setting.h"

Scene* Light::scene = NULL;
#define  ATTENU_CONSTANT 0.25
#define  ATTENU_LINEAR 0.25
#define  ATTENU_QUAD 0.5


Vec3 DirectionalLight::shadowAttenuation(const Vec3& P ) const
{
	Ray r = Ray(P, direction);
	float t = FLT_MAX; //large
    //return scene->shadowAttenuation(r, t);
	return Vec3(1, 1, 1);
}

Vec3 PointLight::shadowAttenuation(const Vec3& P ) const
{
	Ray r = Ray(position, getDirection(P));
	float t = (position - P).length() - Setting::EPSILON;
	return scene->root->shadowAttenuation(r, t);
}

double PointLight::distanceAttenuation(const Vec3& P ) const
{
	
	double t = (position - P).length();
	double d = 1.0 / (ATTENU_CONSTANT + ATTENU_LINEAR * t + ATTENU_QUAD * t * t);
	if (d < 1) d = 1.0;

	return d;
}