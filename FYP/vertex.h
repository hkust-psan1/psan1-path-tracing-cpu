#ifndef _VERTEX_H
#define _VERTEX_H

#include "vec3.h"

class Vec3;

class Vertex {
public:
	Vertex(const Vec3& p, const Vec3& n);
    // Vertex(const Vec3& p, const Vec3& n, const Vec3& t);
    
	inline const Vec3& getPos() const { return pos; };
    inline const Vec3& getNormal() const { return normal; };
    inline const Vec3& getTexCoords() const { return texCoords; };
    
    inline const void setTexCoords(const Vec3& t) { texCoords = t; hasTexture = true; };
    
	friend std::ostream& operator<<(std::ostream& os, const Vertex& v) {
		os << "Vertex: " << std::endl << "Position: " << v.pos << std::endl
            << "Normal: " << v.normal << std::endl
            << "Texture: " << v.texCoords << std::endl;
		return os;
	}
private:
	Vec3 pos;
	Vec3 normal;
	Vec3 texCoords;
    bool hasTexture;
};


#endif