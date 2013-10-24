#include "face.h"
#define EPSILON 0.00001 

void Face::calculateFaceNormal() {
    e1 = vertices[1]->pos - vertices[0]->pos;
    e2 = vertices[2]->pos - vertices[0]->pos;
    normal = cross(e2, e1);
    normal.normalize();
}

void Face::calculateTangentSpace() {
    Vertex* v1 = vertices[0];
    Vertex* v2 = vertices[1];
    Vertex* v3 = vertices[2];
    
    float x1 = v2->pos.x - v1->pos.x;
    float y1 = v2->pos.y - v1->pos.y;
    float z1 = v2->pos.z - v1->pos.z;
    float x2 = v3->pos.x - v1->pos.x;
    float y2 = v3->pos.y - v1->pos.y;
    float z2 = v3->pos.z - v1->pos.z;
    
    float s1 = v2->texCoords.x - v1->texCoords.x;
    float t1 = v2->texCoords.y - v1->texCoords.y;
    float s2 = v3->texCoords.x - v1->texCoords.x;
    float t2 = v3->texCoords.y - v1->texCoords.y;
    
    float r = 1.f / (s1 * t2 - s2 * t1);

    Vec3 sdir((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r, (t2 * z1 - t1 * z2) * r);
    Vec3 tdir((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r, (s1 * z2 - s2 * z1) * r);

    sdir.normalize();
    tdir.normalize();
    
    v1->tangent = sdir;
    v2->tangent = sdir;
    v3->tangent = sdir;
    
    v1->bitangent = tdir;
    v2->bitangent = tdir;
    v3->bitangent = tdir;
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
    
    Vec3 T = r->pos - vertices[0]->pos;
    
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
        N = vertices[1]->normal * (-u) + vertices[2]->normal * (-v) + vertices[0]->normal * (u+v-1);
    } else {
        N = normal;
    }
    N.normalize();
    
    Vec3 tangent = vertices[1]->tangent * u + vertices[2]->tangent * v + vertices[0]->tangent * (1 - u - v);
    Vec3 bitangent = vertices[1]->bitangent * u + vertices[2]->bitangent * v + vertices[0]->bitangent * (1 - u - v);

    Vec3 texCoord = vertices[1]->texCoords * u + vertices[2]->texCoords * v + vertices[0]->texCoords * (1 - u - v);

    if(t > EPSILON && t < t_min) { // ray intersection
		Intersection* i = new Intersection(obj, obj->mat, N, tangent, bitangent, texCoord, t);
        return i;
    }
    
    // No hit, no win
    return NULL;
}
