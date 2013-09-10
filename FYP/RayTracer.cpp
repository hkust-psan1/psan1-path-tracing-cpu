#include "RayTracer.h"
#include "ui_mainwindow.h"

RayTracer::RayTracer(int width, int height)
{
	this->height = height;
	this->width = width;
	this->camera = new Camera(Vec3(0, 0, -1), Vec3(0, 0, 1));
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
	if (intc != NULL)
		return Vec3(1, 1, 1);
	return Vec3(0, 0, 0);
}