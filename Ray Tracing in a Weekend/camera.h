#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include "Ray.h"
#include "util.h"
#include <corecrt_math_defines.h>


class camera
{
public:
	camera(vec3 lookfrom,vec3 lookat,vec3 vup,float vfov,float aspect,float apertrue,float foucs_dist)//vfov is top to bottom in degrees
	{
		lens_radius = apertrue / 2;
		float theta = vfov * M_PI / 180;
		float half_height = tan(theta / 2);
		float half_width = aspect * half_height;
		origin = lookfrom;
		w = unit_vector(lookfrom - lookat);
		u = unit_vector(cross(vup, w));
		v = cross(w, u);
		lower_left_corner = origin - u * foucs_dist*half_width - half_height* foucs_dist * v - foucs_dist*w;
		horizontal = 2 * half_width * foucs_dist*u;
		vertical = 2 * half_height * foucs_dist* v;
	}
	ray get_ray(float s, float t)
	{
		vec3 rd = lens_radius * util::radon_in_unit_desk();
		vec3 offset = u * rd.x() + v * rd.y();
		return ray(origin+offset, lower_left_corner + s * horizontal + t * vertical - origin-offset);
	}

private:
	vec3 u, v, w;
	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	float lens_radius;
};


#endif
