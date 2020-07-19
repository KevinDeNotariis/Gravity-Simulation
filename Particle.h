/*
 * Particle.h
 *
 *  Created on: 10 gen 2017
 *      Author: kevin
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_
#include <iostream>
#include <vector>
#include "Vector3.h"
#include <GL\glew.h>
#include <GL\glut.h>

#define G 1

class Particle {
public:

	static int counter;
	double mass;
	int tag;

	Vector3 pos;
	Vector3 vel;
	Vector3 force;

	double size;
	double* color;

	std::vector<Vector3> trajectory;
	double* trajectoryColor;

	//Particle();
	Particle(double, Vector3, Vector3, double, std::vector<double>); //(mass, pos, vel, size, color)
	virtual ~Particle();

	void move(double);  // simply v = v_0 + a*dt && x = x_0 + v*dt

	void draw();
	void drawTrajectory();

	void gravitationalForce(std::vector<Particle>);

	void print();

};

#endif /* PARTICLE_H_ */
