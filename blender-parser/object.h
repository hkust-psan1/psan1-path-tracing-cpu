#ifndef _OBJECT_H
#define _OBJECT_H

#include "face.h"

class Object {
public:
	Object();
	void addFace(Face* f);
private:
	std::vector<Face*> faces;
};

#endif