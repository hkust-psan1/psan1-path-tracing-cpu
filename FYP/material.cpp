#include "material.h"

Material::Material(const std::string& n) : name(n) {
	ke = 0.f;
    ka = Vec3(0, 0, 0);
	kd = Vec3(0, 0, 0);
    ks = Vec3(0, 0, 0);
	// kt = Vec3(0.0, 0.0, 0.0);
    // kr = Vec3(0, 0, 0);
	// rate = Vec3(1.0f, 1.0f, 1.0f) - kt;
    
    diffuseMap = NULL;
    specularMap = NULL;
    displacementMap = NULL;
}