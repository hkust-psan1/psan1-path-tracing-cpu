#include "face.h"
#define EPSILON 0.00001 

void Face::calculateFaceNormal() {
    e1 = vertices[1]->getPos() - vertices[0]->getPos();
    e2 = vertices[2]->getPos() - vertices[0]->getPos();
    normal = cross(e2, e1);
    normal.normalize();
}

Intersection* Face::intersect(const Ray* r, float t_min)
{
    float det, inv_det, u, v;
    float t;

    Vec3 P = cross(r->dir, e2);
    det = dot(e1, P);

	//no intersection with the plane
    if (det > -EPSILON && det < EPSILON) 
	{
        return NULL;
    }
    
    inv_det = 1.f / det;
    
    Vec3 T = r->pos - vertices[0]->getPos();
    
    u = dot(T, P) * inv_det;
    if (u < 0.f || u > 1.f) {
        return NULL;
    }
    
    Vec3 Q = cross(T, e1);
    
    //Calculate V parameter and test bound
    v = dot(r->dir, Q) * inv_det;
    
    //The intersection lies outside of the triangle
    if (v < 0.f || u + v  > 1.f) {
        return NULL;
    }
    
    t = dot(e2, Q) * inv_det;
    
    Vec3 N;
    if (obj->smoothShading) {
        N = vertices[1]->getNormal() * u + vertices[2]->getNormal() * v + vertices[0]->getNormal() * (1 - u - v);
    } else {
        N = normal;
    }
    N.normalize();

    Vec3 texCoord = vertices[1]->getTexCoords() * u + vertices[2]->getTexCoords() * v + vertices[0]->getTexCoords() * (1 - u - v);

    if(t > EPSILON && t < t_min) { // ray intersection
		Intersection* i = new Intersection(obj, obj->mat, N, texCoord, t);
        return i;
    }
    
    // No hit, no win
    return NULL;
}
