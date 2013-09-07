#ifndef _FACE_H
#define _FACE_H

#include "vertex.h"

class Face {
public:
	// Face();
	inline void addVertex(Vertex* v) { vertices.push_back(v); };
	inline std::vector<Vertex*> getVertices() const { return vertices; };
private:
	std::vector<Vertex*> vertices;
};

#endif