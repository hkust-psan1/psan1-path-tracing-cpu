#include "face.h"
#define EPSILON 0.0000001 

void Face::addVertex(Vertex* v)
{
	vertices.push_back(v);
	if (vertices.size() == 3)
	{
		e1 = vertices[2]->getPos() - vertices[0]->getPos();
		e2 = vertices[1]->getPos() - vertices[0]->getPos();
	}
}

Intersection* Face::intersect(const Ray& r, float t_min)
{
  float det, inv_det, u, v;
  float t;
 
  Vec3 P = cross(r.dir, e2);
  det = dot(e1, P);
  if(det > -EPSILON && det < EPSILON) return 0;
  inv_det = 1.f / det;
 
  Vec3 T = r.pos - vertices[0]->getPos();
 
  u = dot(T, P) * inv_det;
  if(u < 0.f || u > 1.f) return 0;
 
  Vec3 Q = cross(T, e1);
 
  //Calculate V parameter and test bound
  v = dot(r.dir, Q) * inv_det;
  //The intersection lies outside of the triangle
  if(v < 0.f || u + v  > 1.f) return NULL;
 
  t = dot(e2, Q) * inv_det;
 
  if(t > EPSILON && t < t_min) { //ray intersection
    return NULL;
  }
 
  // No hit, no win
  return NULL;
}
