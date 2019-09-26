// Ray Tracing in a Weekend.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include <random>
#include <math.h>
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"

using namespace std;
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
		p = 2.0*vec3(RandF()*2-1, RandF() * 2 - 1, RandF() * 2 - 1)-vec3(1.0,1.0,1.0);
	} while (p.squared_length()>=1.0);
	return p;
}


vec3 color(const ray& r, hitable *world)
{
	hit_record rec;
	if (world->hit(r,0.001f,FLT_MAX,rec))
	{
		vec3 target = rec.p + rec.normal + random_int_unit_sphere();
		return 0.5*color(ray(rec.p,target-rec.p),world);
	}
	else
	{
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5f*(unit_direction.y() + 1.0);
		return (1.0 - t)*vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5, 0.7, 1.0);
	}
}

int main()
{
	fstream OutputPPM;
	OutputPPM.open("OutputPPM.ppm");
	int nx = 200;	
	int ny = 100;
	int ns = 100;
	OutputPPM << "P3\n" << nx << " " << ny <<"\n255\n";
	hitable *list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
	hitable *world = new hitable_list(list, 2);
	camera cam;
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++)
			{
				float u = float(i+ RandF()) / float(nx);
				float v = float(j+ RandF())/ float(ny);
				ray r = cam.get_ray(u, v);
				vec3 p = r.point_at_parameter(2.0);
				col += color(r, world);
			}
			col /= float(ns);

			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			OutputPPM << ir << " " << ig << " " << ib << "\n";
		}
	}
	OutputPPM.close();
	
	return 0;
}
