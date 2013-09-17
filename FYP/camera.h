#ifndef _CAMERA_H
#define _CAMERA_H

#include "ray.h"

class Camera {
public:
    Camera(const Vec3& e, const Vec3& c, const Vec3& u);
	Ray getCameraRay(int x, int y) const;
    
    void update();
	
    inline void setEyePos(const Vec3& e) { eye = e; };
    inline const Vec3& getEyePos() const { return eye; };
    
    inline void setCenterPos(const Vec3& c) { ctr = c; };
    inline const Vec3& getCenterPos() const { return ctr; };
    inline void setSize(int w, int h) { width = w; height = h; };
    
private:
	Vec3 eye, ctr, up;
    Vec3 view, cameraUp, cameraLeft;
	int width, height;
};

#endif