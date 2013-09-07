#ifndef _FACE_H
#define _FACE_H

#include <vector>
#include "vertex.h"

class Face {
public:
	Face();
	void addVertex(const Vertex* v);
private:
	std::vector<Vertex*> vertices;
};

#endif