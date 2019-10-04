#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include "util.h"
#include "sphere.h"
#include "hitable_list.h"

using namespace util;

class material 
{
public:
	virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray& scattered) const = 0;
};


class lambertian :public material
{
public:
	lambertian(const vec3 &a) :albedo(a) {}

	virtual bool scatter(const ray& r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const override
	{
		vec3 target = rec.p + rec.normal + util::random_int_unit_sphere();
		scattered = ray(rec.p, target - rec.p);
		attenuation = albedo;
		return true;
	}

	vec3 albedo;
};

class metal :public material
{
public:
	metal(const vec3& a, float f = 1.0f) :albedo(a), fuzz(f)
	{
		if (fuzz<1)
		{
			fuzz = f;
		}
		else
		{
			fuzz = 1;
		}
	}

	virtual bool scatter(const ray& r_in, const hit_record &rec, vec3 & attenuation, ray& scattered) const override
	{
		vec3 reflected = util::reflect(unit_vector(r_in.direction()), rec.normal);
		scattered = ray(rec.p, reflected+fuzz* util::random_int_unit_sphere());
		attenuation = albedo;
		return (dot(scattered.direction(),rec.normal))> 0 ;
	}
	vec3 albedo;
	float fuzz;
};


class dielectric :public material
{
public:
	dielectric(float ri) :ref_index(ri) { }
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
	{
		vec3 outward_normal;
		vec3 reflected = util::reflect(r_in.direction(), rec.normal);
		float ni_over_nt;
		vec3 refracted;
		attenuation = vec3(1.0, 1.0, 1.0);
		float reflect_porb;
		float cosine;

		if (dot(r_in.direction(), rec.normal) > 0)
		{
			outward_normal = -rec.normal;
			ni_over_nt = ref_index;
			cosine = ref_index * dot(r_in.direction(), rec.normal) / rec.normal.length();
		}
		else
		{
			outward_normal = rec.normal;
			ni_over_nt = 1.0f / ref_index;
			cosine = -dot(r_in.direction(), rec.normal) / rec.normal.length();
		}
		if (util::refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
		{
			reflect_porb = util::schlick(cosine, ref_index);
		}
		else
		{
			reflect_porb = 1.0f;
		}

		if (util::RandF() < reflect_porb)
			scattered = ray(rec.p, reflected);
		else
			scattered = ray(rec.p, refracted);

		return true;
	}

	float ref_index;
};

vec3 color(const ray& r, hitable* world, int depth)
{
	hit_record rec;
	if (world->hit(r, 0.0001, FLT_MAX, rec))
	{
		ray scattered;
		vec3 attenuation;
		if ((depth < 50) && rec.mat_ptt->scatter(r, rec, attenuation, scattered))
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
		float t = 0.5f * (unit_direction.y() + 1.0);
		return (1.0 - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5, 0.7, 1.0);
	}
}

#endif