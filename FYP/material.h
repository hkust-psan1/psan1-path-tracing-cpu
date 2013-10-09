#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "vec3.h"
#include <QPixmap>

class Material {
public:
	Material(std::string n);
    Vec3 ke;  // emissive
    Vec3 ka;  // ambient
    Vec3 ks;  // specular
    Vec3 kd;  // diffuse
    std::string name;
	float index;
	float index_inverse;
    
    float alpha;
    float ior;
    float reflectFactor;
    float reflectGloss;
    
    QPixmap* diffuseMap;
    QPixmap* specularMap;
    QPixmap* displacementMap;
};

#endif