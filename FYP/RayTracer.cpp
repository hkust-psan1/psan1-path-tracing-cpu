#include "RayTracer.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <ctime>
#define EPSILON 0.00001 
#define SPECULAR_N 64
#define A_THRESHOLD 0.1

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
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Ray* r = camera->getCameraRay(i, j);
            node n = {r, i, j, 0, Vec3(1)};
            queue.push(n);
        }
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
	
    /*
	AA();
    std::cout << "Anti-Aliasing" << std::endl;
    */
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
    /*
    pixelRendered = new bool*[height];
    for (int i = 0; i < height; i++) {
        pixelRendered[i] = new bool[width];
        for (int j = 0; j < width; j++) {
            pixelRendered[i][j] = false;
        }
    }
    */
    
    const clock_t begin_time = clock();
	renderWithGridSize(1);
    /*
    for (int gridSize = 8; gridSize != 0; gridSize /= 2) {
        renderWithGridSize(gridSize);
    }
    */
    
    std::cout << "time elapsed: " << float(clock() - begin_time) / CLOCKS_PER_SEC << std::endl;

    
    rendering = false;
}

bool RayTracer::isAliasing(int i, int j)
{
	if (i > 0 && (colorBuffer[i - 1][j] - colorBuffer[i][j]).length() > A_THRESHOLD)
		return true;
	if (j > 0 && (colorBuffer[i][j - i] - colorBuffer[i][j]).length() > A_THRESHOLD)
		return true;
	if (i < width - 1 && (colorBuffer[i + 1][j] - colorBuffer[i][j]).length() > A_THRESHOLD)
		return true;
	if (j < height - 1 && (colorBuffer[i][j + 1] - colorBuffer[i][j]).length() > A_THRESHOLD)
		return true;
	return false;
}

void RayTracer::AA()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (isAliasing(j, i))
			{
				colorBuffer[i][j] = Vec3(0.0);
				Ray* r1 = camera->getCameraRay(i + 0.5, j);
				node n1 = {r1, i, j, 0, Vec3(0.25f)};
				queue.push(n1);				
				Ray* r2 = camera->getCameraRay(i - 0.5, j);
				node n2 = {r2, i, j, 0, Vec3(0.25f)};
				queue.push(n2);
				Ray* r3 = camera->getCameraRay(i, j + 0.5);
				node n3 = {r3, i, j, 0, Vec3(0.25f)};
				queue.push(n3);				
				Ray* r4 = camera->getCameraRay(i, j - 0.5);
				node n4 = {r4, i, j, 0, Vec3(0.25f)};
				queue.push(n4);
			}
		}
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
}

void RayTracer::traceRay(node n) 
{
    /*
    if (n.depth > 0) {
        // return;
        cout << n.p << endl;
    }
     */
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
    
	for (Light* l : scene->lights)
	{
		Vec3 atten = l->getColor(point) * l->shadowAttenuation(point) * l->distanceAttenuation(point);
		Vec3 L = l->getDirection(point);
		
        Vec3 normal;
        
        if (mat->displacementMap) {
            /*
            int x = mat->displacementMap->width() * intc->texCoord.x;
            int y = mat->displacementMap->height() * intc->texCoord.y;
            
            QColor normalColor = mat->displacementMap->pixel(x, y);
            normal = Vec3(normalColor.red() / 255.0, normalColor.green() / 255.0,
                normalColor.blue() / 255.0);
            */
            normal = intc->normal;
        } else {
            normal = intc->normal;
        }
        
        float NL = dot(normal, L);

        Vec3 diffuse;
        if (mat->diffuseMap != NULL) // has diffuse map
		{
            int x = mat->diffuseMap->width() * intc->texCoord.x;
            int y = mat->diffuseMap->height() * intc->texCoord.y;

            QColor diffuseColor = mat->diffuseMap->pixel(x, y);
            diffuse = l->energy * atten * Vec3(diffuseColor.red() / 255.0, diffuseColor.green() / 255.0, diffuseColor.blue() / 255.0) * NL;
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
        
        Vec3 ks;
        
        if (mat->specularMap != NULL) { // has specular map
            int x = mat->specularMap->width() * intc->texCoord.x;
            int y = mat->specularMap->height() * intc->texCoord.y;
            
            QColor specularity = mat->specularMap->pixel(x, y);
            ks = Vec3(specularity.red() / 255.0);
        } else {
            ks = mat->ks;
        }
        
        I += (atten * pow(RV, SPECULAR_N)) * ks;
	}

    I *= (1 - mat->reflectFactor * n.p);
	I.clamp();
    
	colorBuffer[n.x][n.y] += I * n.p;
    colorBuffer[n.x][n.y].clamp();
    
	// max depth
	if (n.depth >= maxDepth || n.p < threshold) 
	{
		return;
	}

	// reflection
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

void RayTracer::traceRay(int x, int y)
{
    Vec3 v(0, 0, 0);
    node n = { camera->getCameraRay(x, y), x, y, 1, v };
    return traceRay(n);
}