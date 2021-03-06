#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "scene.h"

class Light
{
public:
	virtual Vec3 shadowAttenuation(const Vec3& P) const = 0;
    virtual double distanceAttenuation( const Vec3& P ) const = 0;
    virtual Vec3 getColor( const Vec3& P ) const {return color;}
    virtual Vec3 getDirection( const Vec3& P ) const = 0;
	static void setScene(Scene* c) {scene = c;}
    Light() {}
	Light(const Vec3& col ): color( col ) {}
	Vec3 color;
	static Scene* scene;
    float energy;
};

class DirectionalLight
	: public Light
{
public:
    DirectionalLight() {};
	DirectionalLight(const Vec3& d, const Vec3& color )
		: Light(color ), direction( d ) {direction.normalize();}
	virtual Vec3 shadowAttenuation(const Vec3& P) const;
    virtual double distanceAttenuation( const Vec3& P ) const {return 1.0;}
    virtual Vec3 getDirection( const Vec3& P ) const {return direction;}
protected:
	Vec3 direction;
};

class PointLight
	: public Light
{
public:
    PointLight() {};
	PointLight(const Vec3& pos, const Vec3& color )
		: Light(color ), position( pos ) {}
	virtual Vec3 shadowAttenuation(const Vec3& P) const;
	virtual double distanceAttenuation( const Vec3& P ) const;
	virtual Vec3 getDirection( const Vec3& P ) const {Vec3 d = P - position; d.normalize(); return d;}
	Vec3 position;
};

#endif // __LIGHT_H__
