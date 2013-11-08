#ifndef __RAYTRACER_H__
#define __RAYTRACER_H__

#include "ray.h"
#include "vec3.h"
#include "camera.h"
#include "qimage.h"
#include "parser.h"
#include "scene.h"
#include "light.h"

struct RenderNode;
struct PixelData;
class RenderManager;

class RayTracer : public QObject {
    Q_OBJECT
public:
    RayTracer(QObject* parent = 0) : QObject(parent) { };
    RayTracer(RenderManager* m, int tid);

    Vec3 tracePath(RenderNode* n);
	Vec3 traceRay(RenderNode* n);
    inline void setTask(RenderNode* t) { task = t; };
public slots:
	void run();
    
signals:
    void rayTraced(int x, int y, Vec3 color);
    void completed();
    
private:
    RenderManager* manager;
    RenderNode* task;
    int tracerId; // to identify the tracer
};

#endif // __RAYTRACER_H__
