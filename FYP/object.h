#ifndef _OBJECT_H
#define _OBJECT_H

#include "face.h"
#include "intersection.h"
#include "material.h"
#include "boundingbox.h"

class Face;
class Intersection;
class BoundingBox;

class Object {
public:
	Object();
	void addFace(Face* f);
    inline std::string getName() const { return name; };
	inline std::vector<Face*> getFaces() const { return faces; };
	/*
    inline Material* getMaterial() const { return mat; };
    inline void setMaterial(Material* mtl) { mat = mtl; };
    */

	Material* mat;
    std::string materialName;
	BoundingBox* root;
	void buildBox(Vec3 min, Vec3 max);
    
private:
    std::string name;
	std::vector<Face*> faces;
    

};

#endif