#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "vec3.h"

class Material {
public:
	Material(std::string n);
    Vec3 ke;  // emissive
    Vec3 ka;  // ambient
    Vec3 ks;  // specular
    Vec3 kd;  // diffuse
    Vec3 kr;  // reflective
    Vec3 kt;  // transmissive
	Vec3 rate;
	bool isTransmissive;
    std::string name;
	float index;
	float index_inverse;
};

#endif