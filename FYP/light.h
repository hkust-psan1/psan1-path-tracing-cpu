#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "scene.h"

class Light
{
public:
	virtual Vec3 shadowAttenuation(const Vec3& P) const = 0;
	virtual double distanceAttenuation( const Vec3& P ) const = 0;
	virtual Vec3 getColor( const Vec3& P ) const = 0;
	virtual Vec3 getDirection( const Vec3& P ) const = 0;

protected:
	Light(const Vec3& col ): color( col ) {}
	Vec3 color;
};

class DirectionalLight
	: public Light
{
public:
	DirectionalLight(const Vec3& orien, const Vec3& color )
		: Light(color ), orientation( orien ) {}
	virtual Vec3 shadowAttenuation(const Vec3& P) const {return NULL;};
	virtual double distanceAttenuation( const Vec3& P ) const {return 1.0;};
	virtual Vec3 getColor( const Vec3& P ) const {return color;};
	virtual Vec3 getDirection( const Vec3& P ) const {return orientation;};

protected:
	Vec3 orientation;
};

class PointLight
	: public Light
{
public:
	PointLight( Scene *scene, const Vec3& pos, const Vec3& color )
		: Light(color ), position( pos ) {}
	virtual Vec3 shadowAttenuation(const Vec3& P) const;
	virtual double distanceAttenuation( const Vec3& P ) const;
	virtual Vec3 getColor( const Vec3& P ) const;
	virtual Vec3 getDirection( const Vec3& P ) const;

protected:
	Vec3 position;
};

#endif // __LIGHT_H__
