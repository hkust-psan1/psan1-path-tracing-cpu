#include "RayTracer.h"
#include "ui_mainwindow.h"

RayTracer::RayTracer(int width, int height)
{
	this->height = height;
	this->width = width;
	image = QImage(width, height, QImage::Format_RGB32);

}

void RayTracer::render()
{
	for (int i = 0; i < 200; i++) {
		image.setPixel(i, i, qRgb(189, 149, 39));
	}
}