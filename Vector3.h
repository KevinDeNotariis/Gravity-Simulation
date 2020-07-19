/*
 * Vector3.h
 *
 *  Created on: 10 gen 2017
 *      Author: kevin
 */

#ifndef VECTOR3_H_
#define VECTOR3_H_

class Vector3 {
public:

	double x;
	double y;
	double z;

	double r;
	double theta;
	double phi;

	Vector3();
	Vector3(double, double, double, bool = false); //(x,y,z,0) for Cartesian coordinates, (r,theta,phi) for Spherical coordinates;
	virtual ~Vector3();

	void sphericalToCartesian();
	void cartesianToSpherical();
	void print();
	Vector3 direction();

	Vector3 operator+(Vector3);
	Vector3 operator-(Vector3);
	double operator*(Vector3);
	Vector3 operator*(double);
	Vector3 operator/(double);
	void operator=(Vector3);

};

#endif /* VECTOR3_H_ */
