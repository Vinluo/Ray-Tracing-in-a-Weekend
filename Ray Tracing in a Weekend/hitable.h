#pragma once
#ifndef HITABLE_H
#define HITABLE_H

#include "Ray.h"
#include "material.h"

class material;

struct hit_record
{
	float t;
	vec3 p;
	vec3 normal;
	material *mat_ptt;
};


class hitable
{
public:
	virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec)const = 0;
};

#endif // !HITABLE_H


