#include "RayTracer.h"
#include "mainwindow.h"
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

RayTracer::~RayTracer() {

}

void RayTracer::renderWithGridSize(int gridSize) {
    int offset = gridSize / 2;
    
    for (int i = 0; i < height; i += gridSize) {
        for (int j = 0; j < width; j += gridSize) {
            int x = j + offset;
            int y = i + offset;
            
            Vec3 color = traceRay(camera->getCameraRay(x, y), maxDepth);
            pixelRendered[i][j] = true; // mark as rendered
            
            for (int k = 0; k < gridSize && i + k < height; k++) {
                for (int l = 0; l < gridSize && j + l < width; l++) {
                    image.setPixel(j + l, i + k, qRgb(color.x * 255, color.y * 255, color.z * 255));
                }
            }
        }
    }
    
    emit rowCompleted();
}

void RayTracer::render()
{
	Light::setScene(scene);
	
    /* initialize the 2d array */
    pixelRendered = new bool*[height];
    for (int i = 0; i < height; i++) {
        pixelRendered[i] = new bool[width];
    }
	
    for (int gridSize = 64; gridSize != 0; gridSize /= 2) {
        renderWithGridSize(gridSize);
    }
}

Vec3 RayTracer::traceRay(const Ray& ray, int depth) 
{
	Intersection* intc = scene->intersect(ray);
	// no hit
	if (intc == NULL) {
		return Vec3();
    }   
	
	Vec3 point = ray.at(intc->t);
	
	Material* mat = intc->mat;
	Vec3 I = Vec3(intc->mat->ke);

	//ambient
	if (mat->isTransmissive) I += Vec3();
	else I += scene->ambient * mat->ka;

	for (Light* l : lights)
	{
		Vec3 atten = l->getColor(point) * l->shadowAttenuation(point) * l->distanceAttenuation(point);
		Vec3 L = l->getDirection(point);
		float NL = abs(dot(intc->normal, L));

		//diffuse
		Vec3 diffuse = (atten * mat->kd * NL);
		diffuse.clamp();
		I += diffuse;
	}

	// max depth
	if (depth <= 0)
		return I;
	
	//reflection
	const float NL = -dot(intc->normal, ray.dir);
	Vec3 ref = intc->normal * (2 * NL) + ray.dir;
	Ray R = Ray(point, ref);
	Vec3 reflection = mat->kr * (traceRay(R, depth - 1));
	
	reflection.clamp();
	I += reflection;
	
	I.clamp();
	return I;
}