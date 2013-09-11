#ifndef _CAMERA_H
#define _CAMERA_H

#include "ray.h"

class Camera {
public:
	Camera(const Vec3& e, const Vec3& d, int w, int h);
	Ray getCameraRay(int x, int y) const;
private:
	Vec3 eye;
	Vec3 dir;
	int width, height;
};

#endif