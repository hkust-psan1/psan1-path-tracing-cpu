#include "camera.h"

Camera::Camera(const Vec3& e, const Vec3& c, const Vec3& u)
: eye(e), ctr(c), up(u) {
    update();
    useDof = false;
    focalLength = 10;
}

void Camera::update() {
    view = ctr - eye;
    cameraLeft = cross(up, view);
    cameraUp = cross(view, cameraLeft);
    
    view.normalize();
    cameraLeft.normalize();
    cameraUp.normalize();
}

vector<Ray*> Camera::getCameraRays(float x, float y) const {
    vector<Ray*> rays;
    if (useDof) {
        for (int i = 0; i < 10; i++) {
            float rand1 = (float)rand() / (float)RAND_MAX;
            float rand2 = (float)rand() / (float)RAND_MAX;
            
            float randX = sqrt(- 2 * log(rand1)) * cos(2 * M_PI * rand2) / 30;
            float randY = sqrt(- 2 * log(rand1)) * sin(2 * M_PI * rand2) / 30;
            
            Ray* r = new Ray(eye + cameraLeft * randX + cameraUp * randY, view * focalLength + cameraLeft * focalLength * (x / width - 0.5f) - cameraUp * focalLength * (y / height - 0.5f));
            rays.push_back(r);
        }
    } else {
        Ray* singleRay = new Ray(eye, view + cameraLeft * (x / width - 0.5f) - cameraUp * (y / height - 0.5f));
        rays.push_back(singleRay);
    }
    return rays;
}
