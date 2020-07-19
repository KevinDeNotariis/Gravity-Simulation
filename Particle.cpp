/*
 * Particle.cpp
 *
 *  Created on: 10 gen 2017
 *      Author: kevin
 */

#include "Particle.h"
#include <cmath>
#include <time.h>
#include <stdlib.h>

/*Particle::Particle() {
	mass = 0;
	size = 0;

	for(int i = 0; i < 3; i++)
	{
		color[i] = 0;
	}
}*/

int Particle::counter = 0;

Particle::Particle(double m, Vector3 p, Vector3 v, double s, std::vector<double> _color)
{
	mass = m;
	pos = p;
	vel = v;
	size = s;

	//std::cout<<v.r<<std::endl;

	tag = counter;
	counter++;

	color = new double[3];
	color[0] = _color.at(0);
	color[1] = _color.at(1);
	color[2] = _color.at(2);

	int roundingNumber = 10;

	trajectoryColor = new double[3];
	trajectoryColor[0] = (double)(rand() % roundingNumber) / (double)roundingNumber;
	trajectoryColor[1] = (double)(rand() % roundingNumber) / (double)roundingNumber;
	trajectoryColor[2] = (double)(rand() % roundingNumber) / (double)roundingNumber;

}

Particle::~Particle() {
}

void Particle::move(double dt)
{
	//trajectory.push_back(pos);

	vel = vel + (force/mass)*dt;
	pos = pos + vel*dt;
}

void Particle::draw()
{
	glPointSize(size);
	glBegin(GL_POINTS);
		glColor3f(color[0], color[1], color[2]);
		glVertex3f(pos.x, pos.y, pos.z);
	glEnd();
}

void Particle::drawTrajectory()
{
	glPointSize(2);
	glColor3f(trajectoryColor[0], trajectoryColor[1], trajectoryColor[2]);
	glBegin(GL_POINTS);
	{
		for(unsigned int i = 0; i < trajectory.size(); i++)
		{
			glVertex3f(trajectory.at(i).x, trajectory.at(i).y, trajectory.at(i).z);
		}
	}
	glEnd();
}

void Particle::gravitationalForce(std::vector<Particle> p)
{
	Vector3 ret;

	for(unsigned int i = 0; i < p.size(); i++)
	{
		if(tag != p.at(i).tag)
		{
			Vector3 force((p.at(i).pos - this->pos).direction());
					force = force*mass*p.at(i).mass*G;
					force = force/(pow((p.at(i).pos - pos).r,2));
					ret = ret+force;
		}
	}
	force = ret;
}

void Particle::print()
{
	std::cout<<"Particle: "<<tag<<std::endl;
	std::cout<<"Mass = "<<mass<<std::endl;
	std::cout<<"Position (x, y, z) = "<<"("<<pos.x<<", "<<pos.y<<", "<<pos.z<<")"<<std::endl;
	std::cout<<"Position (r, theta, phi) = "<<"("<<pos.r<<", "<<pos.theta<<", "<<pos.phi<<")"<<std::endl;
	std::cout<<"Color: "<<"("<<color[0]<<", "<<color[1]<<", "<<color[2]<<")"<<std::endl;
	std::cout<<"Velocity (x, y, z) = "<<"("<<vel.x<<", "<<vel.y<<", "<<vel.z<<")"<<std::endl;
	std::cout<<"Velocity (r, theta, phi) = "<<"("<<vel.r<<", "<<vel.theta<<", "<<vel.phi<<")"<<std::endl;
}
