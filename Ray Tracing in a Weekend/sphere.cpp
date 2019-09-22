#include "sphere.h"



sphere::sphere()
{
}


sphere::~sphere()
{
}


bool sphere::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b =  dot(r.direction(), oc);
	float c = dot(oc, oc) - radius * radius;

	float discriment = b * b - a * c;
	if (discriment > 0)
	{
		float temp = (-b - sqrt(b*b - a * c)) / a;

	}
	else
	{
	}

}
