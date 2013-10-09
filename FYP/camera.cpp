#include "camera.h"

Camera::Camera(const Vec3& e, const Vec3& c, const Vec3& u)
: eye(e), ctr(c), up(u) {
    update();
}

void Camera::update() {
    view = ctr - eye;
    cameraLeft = cross(up, view);
    cameraUp = cross(view, cameraLeft);
    
    view.normalize();
    cameraLeft.normalize();
    cameraUp.normalize();
}

Ray* Camera::getCameraRay(float x, float y) const {
    return (new Ray(eye, view + cameraLeft * (x / width - 0.5f) - cameraUp * (y / height - 0.5f)));
}
