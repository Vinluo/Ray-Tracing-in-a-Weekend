#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"

class material;

class sphere : public hitable
{
public:

	sphere() {};

	sphere(vec3 cen, float r,material* mater_) :center(cen), radius(r),mater(mater_) {};

	inline vec3 getCenter()	const {return center;}

	inline float getRadius() const{ return radius;}

	inline void setCenter(const vec3 &cen){center = cen;}

	inline void setRadius(float r){radius = r;}

	virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const ;

private:	
	vec3 center;
	float radius;
	material *mater;
};


#endif // !SPHERE_H
 