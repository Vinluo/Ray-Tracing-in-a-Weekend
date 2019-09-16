#include "Vec3.h"

using namespace std;

void vec3::make_unit_vectot()
{

}

vec3& vec3::operator+=(const vec3 &v2)
{

}

vec3& vec3::operator-=(const vec3 &v2)
{

}

vec3& vec3::operator*=(const vec3 &v2)
{

}

vec3& vec3::operator/=(const vec3 &v2)
{

}


vec3& vec3::operator/=(const float t)
{

}

vec3& vec3::operator*=(const float t)
{

}

inline ifstream&operator>>(istream &is, vec3& t)
{
	is >> t.e[0] >> t.e[1] >> t.e[2];
	return is;
}

inline ofstream& operator<<(ofstream &os, const vec3 &t)
{
	os << t.e[0] << " " << t.e[1] << " " << t.e[2];
	return os;
}