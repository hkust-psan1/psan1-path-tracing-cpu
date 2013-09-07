#ifndef _OBJECT_H
#define _OBJECT_H

#include "face.h"

class Object {
public:
	Object();
	inline void addFace(Face* f) { faces.push_back(f); };
	inline std::vector<Face*> getFaces() const { return faces; };
private:
	std::vector<Face*> faces;
};

#endif