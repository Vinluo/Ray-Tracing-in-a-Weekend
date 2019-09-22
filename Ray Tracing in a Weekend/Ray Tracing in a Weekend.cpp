// Ray Tracing in a Weekend.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include "Ray.h"

using namespace std;

float hit_sphere(const vec3& center, float radius, const ray& r)
{

}


vec3 color(const ray &r)
{
	float t = hit_sphere(vec3(0, 0, -1), 0.5f, r);
	if (t > 0.0f)
	{
		vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0, 0, -1));
		return 0.5*vec3(N.x() + 1, N.y() + 1, N.z() + 1);
	}
	vec3 unit_direction = unit_vector(r.direction());
	t = 0.5f*(unit_direction.y() + 1.0f);
	return (1.0f - t)*vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}


int main()
{
	fstream OutputPPM;
	OutputPPM.open("OutputPPM.ppm");
	int nx = 200;
	int ny = 100;
	OutputPPM << "P3\n" << nx << " " << ny <<"\n255\n";
	vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
	vec3 horizontal(4.0f, 0.0f, 0.0f);
	vec3 vertical(0.0f, 2.0f, 0.0f);
	vec3 origin(0.0f, 0.0f, 0.0f);

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			vec3 col = color(r);
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			OutputPPM << ir << " " << ig << " " << ib << "\n";
		}
	}
	OutputPPM.close();
	
	return 0;
}
