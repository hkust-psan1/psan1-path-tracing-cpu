#include "material.h"

Material::Material() {
    /* temporary testing data */
	ke = Vec3(0, 0, 0);
    ka = Vec3(0.8, 0.2, 0.2);
    kd = Vec3(0.4, 0.4, 0.4);
    ks = Vec3(1.0, 1.0, 0.5);
	kt = Vec3(0, 0, 0);
	isTransmissive = false;
}