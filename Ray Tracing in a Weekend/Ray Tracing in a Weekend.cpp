// Ray Tracing in a Weekend.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>


using namespace std;

int main()
{
	fstream OutputPPM;
	OutputPPM.open("OutputPPM.ppm");
	int nx = 200;
	int ny = 100;
	OutputPPM << "P3\n" << nx << " " << ny <<"\n 255\n";
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = 0.2;
			int ir = int(255.99*r);
			int ig = int(255.99*g);
			int ib = int(255.99*b);
			OutputPPM << ir << " " << ig << " " << ib << "\n";
		}
	}
	OutputPPM.close();
	
	return 0;
}
