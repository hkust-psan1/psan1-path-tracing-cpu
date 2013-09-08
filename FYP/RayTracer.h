#ifndef __RAYTRACER_H__
#define __RAYTRACER_H__

// The main ray tracer.

#include "ray.h"
#include "vec3.h"
#include "qimage.h"

class RayTracer
{
public:
	RayTracer(){};
	RayTracer(int width, int height);
	~RayTracer(){};

	void render();

    Vec3 trace(double x, double y );
	Vec3 traceRay(const Vec3& thresh, int depth);


	void getBuffer( unsigned char *&buf, int &w, int &h );
	double aspectRatio();
	void traceSetup( int w, int h );
	void traceLines( int start = 0, int stop = 10000000 );
	void tracePixel( int i, int j );
	void antiAliasing(int part);

	bool loadScene( char* fn );

	void setMaxDepth(int m){maxDepth = m;}

	bool sceneLoaded();
	
	
	QImage image;
private:
	int maxDepth;
	int width;
	int height;
};
#endif // __RAYTRACER_H__
