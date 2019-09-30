// Ray Tracing in a Weekend.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include <random>
#include <math.h>
#include "hitable_list.h"
#include "camera.h"
#include "util.h"
#include "material.h"
#include "sphere.h"

using namespace std;

int main()
{
	fstream OutputPPM;
	OutputPPM.open("OutputPPM.ppm");
	int nx = 200;	
	int ny = 100;
	int ns = 100;
	OutputPPM << "P3\n" << nx << " " << ny <<"\n255\n";
	hitable *list[4];

	list[0] = new sphere(vec3(0, 0, -1), 0.5,new lambertian(vec3(0.8f,0.3f,0.3f)));
	list[1] = new sphere(vec3(0, -100.5, -1), 100,new lambertian(vec3(0.8f, 0.8f, 0.f)));
	list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8f,0.6f,0.2f)));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5, new metal(vec3(0.8f, 0.8f, 0.8f)));
	hitable *world = new hitable_list(list, 4);
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
				col += color(r, world, 0);
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
