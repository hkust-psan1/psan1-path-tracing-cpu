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
    inline string getName() const { return name; };
	inline vector<Face*> getFaces() const { return faces; };
    
    // check if object is light by its emmisive coefficient
    inline bool isLight() const { return mat->ke > 0.000001; };
	/*
    inline Material* getMaterial() const { return mat; };
    inline void setMaterial(Material* mtl) { mat = mtl; };
    */

    bool smoothShading;
	Material* mat;
    std::string materialName;
	BoundingBox* root;
	void buildBox(Vec3 min, Vec3 max);
    
private:
    std::string name;
	std::vector<Face*> faces;
};

class _Light : public Object {
public:
    _Light();
    inline const Vec3& getColor() const { return mat->kd; };
private:
};

#endif