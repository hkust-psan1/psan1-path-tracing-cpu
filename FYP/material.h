#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "vec3.h"
#include <QPixmap>

class Material {
public:
	Material(const std::string& n);
    float ke;  // emissive
    Vec3 ka;  // ambient
    Vec3 ks;  // specular
    Vec3 kd;  // diffuse
	bool isTransmissive;

    std::string name;
    
    float ior;
	float ior_inverse;
    float refractFactor;
    float refractGloss;
    float reflectFactor;
    float reflectGloss;
    
    QImage* diffuseMap;
    QImage* specularMap;
    QImage* displacementMap;
};

#endif