#include "RayTracer.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <ctime>
#define EPSILON 0.00001 
#define SPECULAR_N 64

const Vec3 RayTracer::threshold = Vec3(.1f);

RayTracer::RayTracer(int width, int height)
{
	this->height = height;
	this->width = width;
	this->camera = new Camera(Vec3(15, 10, 16), Vec3(0, 0, 0), Vec3(0, 1, 0));
    this->camera->setSize(width, height);
	scene = NULL;
	colorBuffer = NULL;
    
    frontBuffer = new QImage(width, height, QImage::Format_RGB32);
    backBuffer = new QImage(width, height, QImage::Format_RGB32);
    
    rendering = false;
}

RayTracer::~RayTracer() {

}

void RayTracer::renderWithGridSize(int gridSize) 
{
	
	if (gridSize == 1)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				Ray* r = camera->getCameraRay(i, j);
				node n = {r, i, j, 0, Vec3(1)};
				queue.push(n);
			}
		}
	}
	else
	{
		return;
	}

	while(!queue.empty())
	{
		node n = queue.front();
		traceRay(n);
		//std::cout << queue.size() << std::endl;
		delete n.ray;
		queue.pop();
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			backBuffer->setPixel(j, i, qRgb(colorBuffer[j][i].x * 255, colorBuffer[j][i].y * 255, colorBuffer[j][i].z * 255));
		}
	}

	/*
    int offset = gridSize / 2;
    
    for (int i = 0; i < height && rendering; i += gridSize) {
        for (int j = 0; j < width && rendering; j += gridSize) {
            int x = j + offset;
            int y = i + offset;
            
            QRgb color;
            // if (!pixelRendered[i][j]) {
                Vec3 colorVec = traceRay(camera->getCameraRay(x, y), maxDepth);
                color = qRgb(colorVec.x * 255, colorVec.y * 255, colorVec.z * 255);
            // } else {
                // color = backBuffer->pixel(j, i);
            // }
            pixelRendered[i][j] = true; // mark as rendered
            
            for (int k = 0; k < gridSize && i + k < height; k++) {
                for (int l = 0; l < gridSize && j + l < width; l++) {
                    backBuffer->setPixel(j + l, i + k, color);
                }
            }
        }
    }*/
    
    QImage* tmp = backBuffer;
    backBuffer = frontBuffer;
    frontBuffer = tmp;
    
    emit rowCompleted();
}

void RayTracer::render()
{
	Light::setScene(scene);

	if (colorBuffer != NULL)
	{
		for (int i = 0; i < height; i++)
		{
			if(colorBuffer[i] != NULL)
				delete[] colorBuffer[i];
		}
		delete[] colorBuffer;
	}

	colorBuffer = new Vec3*[height];
	for (int i = 0; i < height; i++)
	{
		colorBuffer[i] = new Vec3[width];
		for (int j = 0; j < width; j++)
		{
			colorBuffer[i][j] = Vec3(.0f);
		}
	}

	queue = std::queue<node>();
    rendering = true;
	
    /* initialize the 2d array */
    pixelRendered = new bool*[height];
    for (int i = 0; i < height; i++) {
        pixelRendered[i] = new bool[width];
        for (int j = 0; j < width; j++) {
            pixelRendered[i][j] = false;
        }
    }
    
    const clock_t begin_time = clock();
	
    for (int gridSize = 8; gridSize != 0; gridSize /= 2) {
        renderWithGridSize(gridSize);
    }
    
    std::cout << "time elapsed: " << float(clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
    
    rendering = false;
}

void RayTracer::traceRay(node n) 
{
	Intersection* intc = scene->intersect(n.ray);
	// no hit
	if (intc == NULL) {
		return;
    }   
	
	Vec3 point = n.ray->at(intc->t);
	
	Material* mat = intc->mat;
	Vec3 I = Vec3(mat->ke);

	//ambient
	if (mat->isTransmissive) 
	{
        I += scene->ambient * mat->ka * (1.0f - mat->ior);
    } 
	else 
	{
        I += scene->ambient * mat->ka;
    }
	
	for (Light* l : lights) 
	{
		Vec3 atten = l->getColor(point) * l->shadowAttenuation(point) * l->distanceAttenuation(point);
		Vec3 L = l->getDirection(point);
		float NL = dot(intc->normal, L);
                
        Vec3 diffuse;
        if (mat->diffuseMap != NULL)
		{
			// has diffuse map
            int x = mat->diffuseMap->width() * intc->texCoord.x;
            int y = mat->diffuseMap->height() * intc->texCoord.y;

            QColor diffuseColor = mat->diffuseMap->toImage().pixel(x, y);
            diffuse = atten * Vec3(diffuseColor.red() / 255.0, diffuseColor.green() / 255.0, diffuseColor.blue() / 255.0) * NL;
        }
		else
		{
            diffuse = (atten * mat->kd * NL);
        }
        
        diffuse.clamp();
        I += diffuse;
        
		//specular
		Vec3 R = intc->normal * (2 * NL) - L;
		double RV = -dot(R, n.ray->dir);

		I += (atten * pow(RV, SPECULAR_N)) * mat->ks;
	}

	I.clamp();
	colorBuffer[n.x][n.y] += I * n.p;
	// max depth
	if (n.depth >= maxDepth || n.p < threshold) 
	{
		return;
	}
	
	//reflection
	const float NL = -dot(intc->normal, n.ray->dir);
	Vec3 ref = intc->normal * (2 * NL) + n.ray->dir;
	Ray* R = new Ray(point, ref);
	node r = {R, n.x, n.y, n.depth + 1, mat->reflectFactor * n.p};
	queue.push(r);
	

	//refraction		
	if (abs(mat->alpha - 1) < EPSILON) // alpha is 1
	{
		return;
	}
	
	Vec3 refraction;
	float pn;
	
	if (NL > 0)
	{
		pn = mat->ior_inverse;
		float LONG_TERM = pn * NL - sqrt(1 - pn * pn * (1 - NL * NL));
		Ray* T = new Ray(point, (intc->normal * LONG_TERM + n.ray->dir * pn));
		node t = {T, n.x, n.y, n.depth + 1, mat->alpha * n.p};
		queue.push(t);
	}
	else
	{
		pn = mat->ior;
		if (1 - pn * pn * (1 - NL * NL) < EPSILON)
		{
			return;
		}			
		
		float LONG_TERM = -(pn * (-NL) - sqrt(1 - pn * pn * (1 - NL * NL)));
		Ray* T = new Ray(point, (intc->normal * LONG_TERM + n.ray->dir * pn));
		node t = {T, n.x, n.y, n.depth + 1, mat->alpha * n.p};
		queue.push(t);
	} 

}

Vec3 RayTracer::traceRay(int x, int y) 
{
//	return traceRay(camera->getCameraRay(x, y), maxDepth);
	return Vec3(1);
}