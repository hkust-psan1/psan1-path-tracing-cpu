#include "RayTracer.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#define EPSILON 0.00001 
#define SPECULAR_N 64
#define A_THRESHOLD 0.01

RayTracer::RayTracer(RenderManager* m, int tid) : manager(m), tracerId(tid) {
}

void RayTracer::run() {
    while (manager->isRendering() && (task = manager->getTask()) != NULL) {
        Vec3 color = traceRay(task);
        manager->setPixelData(task->x, task->y, color * task->p);
    }
    emit completed();
}

/*
void RayTracer::renderWithGridSize(int gridSize) 
{
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
    }

	AA();
    std::cout << "Anti-Aliasing" << std::endl;
}
*/

/*
void RayTracer::render()
{
	if (colorBuffer != NULL)
	{
		for (int i = 0; i < manager->height; i++)
		{
			if(colorBuffer[i] != NULL)
				delete[] colorBuffer[i];
		}
		delete[] colorBuffer;
	}

	colorBuffer = new Vec3*[manager->height];
	for (int i = 0; i < manager->height; i++)
	{
		colorBuffer[i] = new Vec3[width];
		for (int j = 0; j < manager->width; j++)
		{
			colorBuffer[i][j] = Vec3(.0f);
		}
	}

	queue = std::queue<RenderNode>();
    
    const clock_t begin_time = clock();
    
    for (int i = 0; i < manager->height; i++)
    {
        for (int j = 0; j < manager->width; j++)
        {
            Ray* r = manager->getCamera()->getCameraRay(i, j);
            RenderNode n = {r, i, j, 0, Vec3(1)};
            queue.push(n);
        }
    }
    
	while(!queue.empty())
	{
		RenderNode n = queue.front();
		traceRay(n);
		//std::cout << queue.size() << std::endl;
		delete n.ray;
		queue.pop();
	}
	
	for (int i = 0; i < manager->height; i++)
	{.
		for (int j = 0; j < manager->width; j++)
		{
			backBuffer->setPixel(j, i, qRgb(colorBuffer[j][i].x * 255, colorBuffer[j][i].y * 255, colorBuffer[j][i].z * 255));
		}
	}
    
    std::cout << "time elapsed: " << float(clock() - begin_time) / CLOCKS_PER_SEC << std::endl;

    QImage* tmp = backBuffer;
    backBuffer = frontBuffer;
    frontBuffer = tmp;
    
    emit updateScreen();

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
				RenderNode n1 = {r1, i, j, 0, Vec3(0.25f)};
				queue.push(n1);				
				Ray* r2 = camera->getCameraRay(i - 0.5, j);
				RenderNode n2 = {r2, i, j, 0, Vec3(0.25f)};
				queue.push(n2);
				Ray* r3 = camera->getCameraRay(i, j + 0.5);
				RenderNode n3 = {r3, i, j, 0, Vec3(0.25f)};
				queue.push(n3);				
				Ray* r4 = camera->getCameraRay(i, j - 0.5);
				RenderNode n4 = {r4, i, j, 0, Vec3(0.25f)};
				queue.push(n4);
			}
		}
	}
	
	while(!queue.empty())
	{
		RenderNode n = queue.front();
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
*/

Vec3 RayTracer::traceRay(RenderNode* n)
{
	// max depth
	if (n->depth >= manager->maxDepth || n->p < manager->threshold)
	{
		return Vec3(0.f);
	}
    Scene* scene = manager->getScene();

	Intersection* intc = scene->intersect(n->ray);
	// no hit
	if (intc == NULL) {
		return Vec3(0.25f);
    }

	Vec3 point = n->ray->at(intc->t);
	
	Material* mat = intc->mat;
	Vec3 I = Vec3(0.f);
	Vec3 AE = Vec3(mat->ke);

	//ambient
	if (mat->isTransmissive)
	{
        AE += scene->ambient * mat->ka * (1.0f - mat->ior);
    } 
	else 
	{
        AE += scene->ambient * mat->ka;
    }

	I += AE;
    
	for (Light* l : scene->lights)
	{
		Vec3 atten = l->getColor(point) * l->shadowAttenuation(point) * l->distanceAttenuation(point);
		Vec3 L = l->getDirection(point);
		
        Vec3 normal;
        
        if (mat->displacementMap) {
            if (intc->texCoord.x >= 1 || intc->texCoord.x <= 0
                || intc->texCoord.y >= 1 || intc->texCoord.y <= 0) {
                normal = intc->normal;
            } else {
            int x = mat->displacementMap->width() * intc->texCoord.x;
            int y = mat->displacementMap->height() * intc->texCoord.y;
            
            QColor normalColor = mat->displacementMap->pixel(x, y);
            Vec3 perturb = Vec3(normalColor.red() / 255.0 - 0.5, normalColor.green() / 255.0 - 0.5,
                normalColor.blue() / 255.0 - 0.5);

            // printf("%.3f\t\t%.3f\t\t%.3f\n%.3f\t\t%.3f\t\t%.3f\n%.3f\t\t%.3f\t\t%.3f\t\t\n\n", intc->normal.x, intc->normal.y, intc->normal.z, intc->tangent.x, intc->tangent.y, intc->tangent.z, intc->bitangent.x, intc->bitangent.y, intc->bitangent.z);
            // printf("%.3f\t\t%.3f\t\t%.3f\n", perturb.x, perturb.y, perturb.z);
            
            normal = intc->normal * perturb.z + intc->tangent * perturb.x + intc->tangent * perturb.y;
            normal.normalize();
            }
        } else {
            normal = intc->normal;
        }
        
        float NL = dot(normal, L);

        Vec3 diffuse;
        if (mat->diffuseMap != NULL) // has diffuse map
		{
			Vec3 at = atten + AE * Vec3(1 / scene->lights.size());
            if (intc->texCoord.x >= 1 || intc->texCoord.x <= 0
                || intc->texCoord.y >= 1 || intc->texCoord.y <= 0) {
                diffuse = (at * mat->kd * NL);
            } else {
                int x = mat->diffuseMap->width() * intc->texCoord.x;
                int y = mat->diffuseMap->height() * intc->texCoord.y;
                
                QColor diffuseColor = mat->diffuseMap->pixel(x, y);
                diffuse = l->energy * at * Vec3(diffuseColor.red() / 255.0, diffuseColor.green() / 255.0, diffuseColor.blue() / 255.0) * NL;
            }
        }
		else
		{
            diffuse = (atten * mat->kd * NL);
        }
        
        diffuse.clamp();
        I += diffuse;
        
		//specular
		Vec3 R = intc->normal * (2 * NL) - L;
		double RV = -dot(R, n->ray->dir);
        
        Vec3 ks;
        
        if (mat->specularMap != NULL) { // has specular map
            if (intc->texCoord.x >= 1 || intc->texCoord.x <= 0
                || intc->texCoord.y >= 1 || intc->texCoord.y <= 0) {
                ks = mat->ks;
            } else {
            int x = mat->specularMap->width() * intc->texCoord.x;
            int y = mat->specularMap->height() * intc->texCoord.y;
            
            QColor specularity = mat->specularMap->pixel(x, y);
            ks = Vec3(specularity.red() / 255.0);
            }
        } else {
            ks = mat->ks;
        }
        
        I += (atten * pow(RV, SPECULAR_N)) * ks;
	}

    I *= 1 - (mat->reflectFactor + (1 - mat->alpha)) * n->p;
     
    // reflection
    const float NL = -dot(intc->normal, n->ray->dir);
    float reflGloss = 1 - mat->reflectGloss;
	
    if (abs(mat->reflectFactor > EPSILON)) { // reflective
        Vec3 refl = intc->normal * (2 * NL) + n->ray->dir;
        
        if (abs(reflGloss) < EPSILON) { // no glossy reflection
            Ray* R = new Ray(point, refl);
            RenderNode* r = new RenderNode(R, n->x, n->y, n->depth + 1, mat->reflectFactor * n->p);
            manager->addTask(r);
        } else { // glossy
            for (int i = 0; i < 10; i++) {
                Ray* R = new Ray(point, refl.randomize(reflGloss));
                RenderNode* r = new RenderNode(R, n->x, n->y, n->depth + 1, mat->reflectFactor * n->p * 0.1f);
                manager->addTask(r);
            }
        }
    }

    //refraction
    float refrGloss = 1 - mat->refractGloss;
	if (abs(mat->alpha - 1) > EPSILON) // alpha is not 1, refractive
	{
        // Vec3 refraction;
        float pn;
        
        if (NL > 0)
        {
            pn = mat->ior_inverse;
            float LONG_TERM = pn * NL - sqrt(1 - pn * pn * (1 - NL * NL));
            Vec3 refr = intc->normal * LONG_TERM + n->ray->dir * pn;
            if (abs(refrGloss) < EPSILON) { // no glossy refraction
                Ray* T = new Ray(point, refr);
                RenderNode* t = new RenderNode(T, n->x, n->y, n->depth + 1, (1 - mat->alpha) * n->p);
                manager->addTask(t);
            } else { // glossy
                for (int i = 0; i < 10; i++) {
                    Ray* T = new Ray(point, refr.randomize(refrGloss));
                    RenderNode* t = new RenderNode(T, n->x, n->y, n->depth + 1, (1 - mat->alpha) * n->p * 0.1f);
                    manager->addTask(t);
                }
            }
        }
        else
        {
            pn = mat->ior;
            if (1 - pn * pn * (1 - NL * NL) < EPSILON)
            {
                return I;
            }
            
            float LONG_TERM = -(pn * (-NL) - sqrt(1 - pn * pn * (1 - NL * NL)));
            Vec3 refr = intc->normal * LONG_TERM + n->ray->dir * pn;
            if (abs(refrGloss) < EPSILON) { // no glossy refraction
                Ray* T = new Ray(point, refr);
                RenderNode* t = new RenderNode(T, n->x, n->y, n->depth + 1, (1 - mat->alpha) * n->p);
                manager->addTask(t);
            } else { // glossy
                for (int i = 0; i < 10; i++) {
                    Ray* T = new Ray(point, refr.randomize(refrGloss));
                    RenderNode* t = new RenderNode(T, n->x, n->y, n->depth + 1, (1 - mat->alpha) * n->p * 0.1f);
                    manager->addTask(t);
                }
            }
        }
    }

    return I;
}
