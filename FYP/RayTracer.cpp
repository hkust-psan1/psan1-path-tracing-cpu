#include "RayTracer.h"
#include "ui_mainwindow.h"

RayTracer::RayTracer(int width, int height)
{
	this->height = height;
	this->width = width;
	this->camera = new Camera(Vec3(3, 3, 3), Vec3(0, 0, 0), Vec3(0, 0, 1));
    this->camera->setSize(width, height);
	scene = NULL;
	image = QImage(width, height, QImage::Format_RGB32);
}

void RayTracer::render() {
	for (int i = 0; i < width; i++)
	{
		for( int j = 0; j < height; j++)
		{
			Vec3 color = traceRay(camera->getCameraRay(i, j), 0); 
			image.setPixel(i, j, qRgb(color.x * 255, color.y * 255, color.z * 255));
		}
	}
}

Vec3 RayTracer::traceRay(const Ray& ray, int depth) 
{
	Intersection* intc = scene->intersect(ray);
	// no hit
	if (intc == NULL) 
		return Vec3(0, 0, 0);

	
	Vec3 I = Vec3(0, 0, 0);
	for (Light* l : lights)
	{
		I += l->getColor(ray.pos);
	}

	// max depth
	if (depth <= 0)
		return I;
	
	//reflection
	const float NL = -dot(intc->normal, ray.dir);
	Vec3 ref = intc->normal * (2 * NL) + ray.dir;
	Vec3 intp = ray.at(intc->t);
	Ray R = Ray(intp, ref);
	//I += (m.kr.time(traceRay(scene, R, thresh, depth - 1))).clamp(); 
	

	return I;
}