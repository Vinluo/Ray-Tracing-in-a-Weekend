#pragma once
#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <random>
#include "Vec3.h"

class material;

constexpr float LARGE_FLT = 98e8f; // 大浮点数
constexpr float DELTA_FLT = 98e-8f; // 小浮点数

namespace util {
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
			p = 2.0 * vec3(RandF() * 2 - 1, RandF() * 2 - 1, RandF() * 2 - 1) - vec3(1.0, 1.0, 1.0);
		} while (p.squared_length() >= 1.0);
		return p;
	}

	vec3 reflect(const vec3& v, const vec3& n)
	{
		return v - 2 * dot(v, n) * n;
	}



	//折射光线计算 SNell.s law
	//n*sin(theia)=n'*sin(theia')
	// ni_over_nt=n/n'

	bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted)
	{

		//cos(theia)
		vec3 uv = unit_vector(v);
		float dt = dot(uv, n);
		float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1 - dt * dt);
		//如果折射率低介质射入折射率更高会被吸收。
		if (discriminant > 0)
		{
			refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
			return true;
		}
		else
		{
			return false;
		}
	}


	//real glass refectivity that varies with angle
	//Approximation by Christophe Schlick
	float schlick(float cosine, float ref_indx)
	{
		float r0 = (1 - ref_indx) / (1 + ref_indx);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}

	vec3 radon_in_unit_desk()
	{
		vec3 p;
		do
		{
			p = 2.0 * vec3(RandF(), RandF(), 0) - vec3(1, 1, 0);
		} while (dot(p, p) >= 1.0);

		return p;
	}
}

#endif // UTIL_H