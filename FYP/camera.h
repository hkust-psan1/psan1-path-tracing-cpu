#ifndef _CAMERA_H
#define _CAMERA_H

#include "ray.h"

class Camera {
public:
	Camera(const Vec3& e, const Vec3& d);
	Ray getCameraRay(int width, int height);
private:
	Vec3 eye;
	Vec3 dir;
};

#endif