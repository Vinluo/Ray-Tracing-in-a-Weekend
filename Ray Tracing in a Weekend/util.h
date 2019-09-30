#pragma once
#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <random>
#include "Vec3.h"
#include "sphere.h"
#include "hitable.h"
#include "Ray.h"
#include "material.h"

class material;

constexpr float LARGE_FLT = 98e8f; // 大浮点数
constexpr float DELTA_FLT = 98e-8f; // 小浮点数

//[0,1)
float RandF() {
	static std::default_random_engine engine;
	static std::uniform_real_distribution<float> fMap(0.0f, 1.f - DELTA_FLT);
	return fMap(engine);
}

vec3 random_int_unit_sphere()
{
	vec3 p;
	do
	{
		p = 2.0*vec3(RandF() * 2 - 1, RandF() * 2 - 1, RandF() * 2 - 1) - vec3(1.0, 1.0, 1.0);
	} while (p.squared_length() >= 1.0);
	return p;
}


vec3 color(const ray& r, hitable *world,int depth)
{
	hit_record rec;
	if (world->hit(r,0.0001,FLT_MAX,rec))
	{
		ray scattered;
		vec3 attenuation;
		if ((depth <50) && rec.mat_ptt->scatter(r,rec,attenuation,scattered))
		{
			return attenuation * color(scattered, world, depth + 1);
		}
		else
		{
			return vec3(0, 0, 0);
		}
	}
	else
	{
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5f*(unit_direction.y() + 1.0);
		return (1.0 - t)*vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5, 0.7, 1.0);
	}
}


vec3 reflect(const vec3 &v, const vec3 &n)
{
	return v - 2 * dot(v, n)*n;
}

#endif // UTIL_H