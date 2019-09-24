#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include "Ray.h"

class camera
{
public:
	camera(){
		vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
		vec3 horizontal(4.0f, 0.0f, 0.0f);
		vec3 vertical(0.0f, 2.0f, 0.0f);
		vec3 origin(0.0f, 0.0f, 0.0f);
		}
	ray get_ray(float u, float v)
	{
		ray R(origin, lower_left_corner + u * horizontal + v * vertical);
		return R;
	}

private:
	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
};


#endif
