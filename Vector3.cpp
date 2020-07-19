/*
 * Vector3.cpp
 *
 *  Created on: 10 gen 2017
 *      Author: kevin
 */

#include "Vector3.h"
#include <iostream>
#include <cmath>

Vector3::Vector3(double x1, double x2, double x3, bool spherical) {

	if(!spherical)
	{
		x = x1;
		y = x2;
		z = x3;
		cartesianToSpherical();
	}
	else
	{
		r = x1;
		theta = x2;
		phi = x3;
		sphericalToCartesian();
	}

}

Vector3::Vector3(){
	x = 0;
	y = 0;
	z = 0;
	r = 0;
	theta = 0;
	phi = 0;
}

void Vector3::sphericalToCartesian()
{
	x = r*sin(theta)*cos(phi);
	y = r*sin(theta)*sin(phi);
	z = r*cos(theta);
}
void Vector3::cartesianToSpherical()
{
	r = sqrt(x*x + y*y + z*z);
	theta = acos(z/r);
	phi = atan2(hypot(x,z),y);
}
void Vector3::print()
{
	std::cout<<"(x, y, z) = "<<"( "<<x<<", "<<y<<", "<<z<<")"<<std::endl;
	std::cout<<"(r, theta, phi) = "<<"( "<<r<<", "<<theta<<", "<<phi<<")"<<std::endl;
}
Vector3 Vector3::direction()
{
	Vector3 vec(x,y,z,0);
	vec = vec/vec.r;
	vec.cartesianToSpherical();
	return vec;
}

Vector3 Vector3::operator+(Vector3 v)
{
	Vector3 ret(x,y,z,0);
	ret.x += v.x;
	ret.y += v.y;
	ret.z += v.z;
	ret.cartesianToSpherical();
	return ret;
}

Vector3 Vector3::operator-(Vector3 v)
{
	Vector3 ret(x,y,z,0);
	ret.x -= v.x;
	ret.y -= v.y;
	ret.z -= v.z;
	ret.cartesianToSpherical();
	return ret;
}

Vector3 Vector3::operator*(double c)
{
	Vector3 ret(x,y,z,0);
	ret.x *= c;
	ret.y *= c;
	ret.z *= c;
	ret.cartesianToSpherical();
	return ret;
}

Vector3 Vector3::operator/(double c)
{
	Vector3 ret(x,y,z,0);
		ret.x /= c;
		ret.y /= c;
		ret.z /= c;
		ret.cartesianToSpherical();
		return ret;
}

double Vector3::operator*(Vector3 v)
{
	return (x*v.x + y*v.y + z*v.z);
}

void Vector3::operator=(Vector3 v)
{
	x = v.x;
	y = v.y;
	z = v.z;

	r = v.r;
	theta = v.theta;
	phi = v.phi;
}

Vector3::~Vector3() {
}

