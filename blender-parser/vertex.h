#ifndef _VERTEX_H
#define _VERTEX_H

#include "vec3.h"

class Vertex {
public:
	Vertex();
private:
	Vec3 pos;
	Vec3 normal;
	Vec3 texCoords;
};

#endif