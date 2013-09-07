#ifndef _FACE_H
#define _FACE_H

#include "vertex.h"

class Object;

class Face {
public:
	// Face();
	inline void addVertex(Vertex* v) { vertices.push_back(v); };
	inline std::vector<Vertex*> getVertices() const { return vertices; };
	inline void setObject(Object* o) { obj = o; };
	inline Object* getObject() const { return obj; };
private:
	std::vector<Vertex*> vertices;
	Object* obj;
};

#endif