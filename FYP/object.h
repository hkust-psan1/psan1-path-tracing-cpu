#ifndef _OBJECT_H
#define _OBJECT_H

#include "face.h"
#include "material.h"

class Face;

class Object {
public:
	Object();
	void addFace(Face* f);
    inline std::string getName() const { return name; };
	inline std::vector<Face*> getFaces() const { return faces; };
    inline Material* getMaterial() const { return mat; };

private:
    std::string name;
	std::vector<Face*> faces;
	Material* mat;
};

#endif