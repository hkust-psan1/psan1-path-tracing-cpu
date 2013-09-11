#ifndef _OBJECT_H
#define _OBJECT_H

#include "face.h"
#include "material.h"

class Face;

class Object {
public:
	Object();
	void addFace(Face* f);
	inline std::vector<Face*> getFaces() const { return faces; };

private:
	std::vector<Face*> faces;
	Material* material;
};

#endif