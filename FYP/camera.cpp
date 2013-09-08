#include "camera.h"

Camera::Camera(const Vec3& e, const Vec3& d)
	: eye(e), dir(d) {
}

Ray Camera::getCameraRay(int width, int height) 
{
	return Ray(Vec3(0, 0, 6), Vec3(width / 500.0, height/ 500.0, -3));
}