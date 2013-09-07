#ifndef _VEC3_H
#define _VEC3_H

class Vec3 {
public:
	Vec3(float x, float y, float z);
	inline float getX();
	inline float getY();
	inline float getZ();
private:
	float coords[3];
};

#endif