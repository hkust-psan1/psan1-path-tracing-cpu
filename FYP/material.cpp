#include "material.h"

Material::Material(std::string n) : name(n) {
	ke = Vec3(0, 0, 0);
    ka = Vec3(0, 0, 0);
	kd = Vec3(0, 0, 0);
    ks = Vec3(0, 0, 0);
	kt = Vec3(0.3f, 0.3f, 0.3f);
    kr = Vec3(0.5f, 0.5f, 0.5f);
	rate = Vec3(1, 1, 1) - kt;
	isTransmissive = true;
	index = 1.1f;
	index_inverse = 1.0f / index;
}