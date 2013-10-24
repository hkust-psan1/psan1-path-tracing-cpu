#ifndef _FACE_H
#define _FACE_H

#include "vertex.h"
#include "ray.h"
#include "intersection.h"

class Intersection;
class Object;

class Face {
public:
	// Face();
	// inline std::vector<Vertex*> getVertices() const { return vertices; };
	inline void setObject(Object* o) { obj = o; };
	inline Object* getObject() const { return obj; };
	Intersection* intersect(const Ray* r, float T_min);
    void calculateFaceNormal();
    void calculateTangentSpace();

	friend std::ostream& operator<<(std::ostream& os, const Face& f) {
		os << "Face: " << std::endl;
		for (Vertex* v : f.vertices) {
			os << *v;
		}
        return os;
    };
        
    Vertex* vertices[3];

private:
    // std::vector<Vertex*> vertices;
    Vec3 e1;
    Vec3 e2;
    Vec3 normal;
        
    /* a pointer to the obj the face belongs to */
    Object* obj;
};
        
#endif