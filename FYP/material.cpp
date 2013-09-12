#include "material.h"

Material::Material() {
    /* temporary testing data */
    kAmbient = Vec3(0.4, 0.2, 0.2);
    kDiffuse = Vec3(0.8, 0.4, 0.4);
    kSpecular = Vec3(1.0, 1.0, 0.5);
}