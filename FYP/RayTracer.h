#ifndef __RAYTRACER_H__
#define __RAYTRACER_H__

// The main ray tracer.

#include "ray.h"
#include "vec3.h"
#include "camera.h"
#include "qimage.h"
#include "parser.h"
#include "scene.h"
#include "light.h"

class RayTracer
{
public:
	RayTracer(){};
	RayTracer(int width, int height);
	~RayTracer(){};

	void render();

    Vec3 trace(double x, double y );
	Vec3 traceRay(const Ray& ray, int depth = 0);
	void setScene(Scene* scene){this->scene = scene;};
	bool sceneLoaded(){return scene != NULL;};

	void addLight(Light* l) {lights.push_back(l);};

	void getBuffer( unsigned char *&buf, int &w, int &h );
	double aspectRatio();
	void traceSetup( int w, int h );
	void traceLines( int start = 0, int stop = 10000000 );
	void tracePixel( int i, int j );
	void antiAliasing(int part);

	bool loadScene( char* fn );

	//void setMaxDepth(int m){maxDepth = m;}
	
	
	QImage image;
private:
	static const int maxDepth = 10;
	int width;
	int height;

	Camera* camera;
	Scene* scene;
	std::vector<Light*> lights;
};
#endif // __RAYTRACER_H__
