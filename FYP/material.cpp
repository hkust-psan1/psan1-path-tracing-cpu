#include "material.h"

Material::Material() {
	ke = Vec3(0, 0, 0);
    ka = Vec3(0, 0, 0);
	kd = Vec3(0, 0, 0);
    ks = Vec3(0, 0, 0);
	kt = Vec3(0, 0, 0);
    kr = Vec3(0, 0, 0);
	isTransmissive = false;
}