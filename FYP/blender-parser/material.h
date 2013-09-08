#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "vec3.h"

class Material {
public:
	Material();
private:
	Vec3 kAmbient;
	Vec3 kDiffuse;
	Vec3 kSpecular;
};

#endif