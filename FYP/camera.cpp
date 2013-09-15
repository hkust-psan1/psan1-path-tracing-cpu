#include "camera.h"

Camera::Camera(const Vec3& e, const Vec3& c, const Vec3& u)
: eye(e), ctr(c), up(u) {
    view = c - e;
    cameraLeft = cross(up, view);
    cameraUp = cross(view, cameraLeft);
    
    view.normalize();
    cameraLeft.normalize();
    cameraUp.normalize();
}

Ray Camera::getCameraRay(int x, int y) const
{
    return Ray(eye, view + cameraLeft * ((float)x / width - 0.5) + cameraUp * ((float)y / height - 0.5));
}
