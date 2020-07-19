/*
 * functions.h
 *
 *  Created on: 11 gen 2017
 *      Author: kevin
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "Vector3.h"
#include "Particle.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>

# define M_PI           3.14159265358979323846  /* pi */

void calculateForces(std::vector<Particle> &);
void moveParticles(std::vector<Particle> &, double);
void drawParticles(std::vector<Particle>);
void elasticCollision(double R, double m1, double m2, double r1, double r2,
        double& x1, double& y1,double& z1,
        double& x2, double& y2, double& z2,
        double& vx1, double& vy1, double& vz1,
        double& vx2, double& vy2, double& vz2);
void checkCollisions(std::vector<Particle>&);
int randomSign();
void createParticles(std::vector<Particle>&, int, double, double, std::vector<double>, bool, double, double, std::vector<double>,
					double, double, double, double, double);

#endif /* FUNCTIONS_H_ */
