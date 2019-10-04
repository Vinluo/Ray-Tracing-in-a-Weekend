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
using namespace util;


hitable* random_scene() {
	int n = 500;
	hitable** list = new hitable * [n + 1];
	list[0] = new sphere(vec3(0, -700, 0), 700, new lambertian(vec3(0.5, 0.5, 0.5)));
	int i = 1;
	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			float choose_mat = RandF();
			vec3 center(a + 0.9 *RandF(), 0.2, b + 0.9 * RandF());
			if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
				if (choose_mat < 0.8) {  // diffuse
					list[i++] = new sphere(center, 0.2, new lambertian(vec3(RandF() * RandF(), RandF() * RandF(), RandF() * RandF())));
				}
				else if (choose_mat < 0.95) { // metal
					list[i++] = new sphere(center, 0.2,
						new metal(vec3(0.5 * (1 + RandF()), 0.5 * (1 + RandF()), 0.5 * (1 + RandF())), 0.5 * RandF()));
				}
				else {  // glass
					list[i++] = new sphere(center, 0.2, new dielectric(1.5));
				}
			}
		}
	}

	list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(2.5));
	list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
	list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(1, 1, 1), 0.0));

	return new hitable_list(list, i);
}

int main()
{
	fstream OutputPPM;
	OutputPPM.open("OutputPPM.ppm");
	int nx = 200;	
	int ny = 100;
	int ns = 100;
	OutputPPM << "P3\n" << nx << " " << ny <<"\n255\n";

	hitable* world = random_scene();

	vec3 lookfrom(3, 3, 2);
	vec3 lookat(0, 0, -1);
	float dist_to_focus = (lookfrom - lookat).length();
	float aperture = 2.0f;

	camera cam(lookfrom, lookat,vec3(0,1,0),20,float(nx)/float(ny),aperture,dist_to_focus);
	int rate = 0;
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

				//
				int Currentrate = ((float)(s*(ny - j)*i)/ (float)(ny * nx * ns))*100.0f;
				if (Currentrate > rate)
				{
					rate = Currentrate;
					cout << "rate of progress::" << rate << endl;
				}
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
