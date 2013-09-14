#ifndef _VERTEX_H
#define _VERTEX_H

#include "vec3.h"

class Vertex {
public:
	Vertex(const Vec3& p, const Vec3& n);
	inline const Vec3& getPos() const { return pos; };
    inline const Vec3& getNormal() const { return normal; };
	friend std::ostream& operator<<(std::ostream& os, const Vertex& v) {
		os << "Vertex: " << std::endl << "Position: " << v.pos << std::endl;
		return os;
	}
private:
	Vec3 pos;
	Vec3 normal;
	// Vec3 texCoords;
};


#endif