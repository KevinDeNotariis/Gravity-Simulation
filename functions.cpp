/*
 * functions.cpp
 *
 *  Created on: 11 gen 2017
 *      Author: kevin
 */

#include "functions.h"

void calculateForces(std::vector<Particle> &p)
{
	for(unsigned int i = 0; i < p.size(); i++)
	{
		p.at(i).gravitationalForce(p);
	}
}

void moveParticles(std::vector<Particle> &p,  double dt)
{
	for(unsigned int i = 0; i < p.size(); i++)
	{
		p.at(i).move(dt);
	}
}

void drawParticles(std::vector<Particle> p)
{
	for(unsigned int i = 0; i < p.size(); i++)
	{
		p.at(i).draw();
	}
}

void elasticCollision(double R, double m1, double m2, double r1, double r2,
        double& x1, double& y1,double& z1,
        double& x2, double& y2, double& z2,
        double& vx1, double& vy1, double& vz1,
        double& vx2, double& vy2, double& vz2)
{
	double  pi,r12,m21,d,v,theta2,phi2,st,ct,sp,cp,vx1r,vy1r,vz1r,fvz1r,
		           thetav,phiv,dr,alpha,beta,sbeta,cbeta,dc,sqs,t,a,dvz2,
				   vx2r,vy2r,vz2r,x21,y21,z21,vx21,vy21,vz21,vx_cm,vy_cm,vz_cm;

   pi=acos(-1.0E0);
   r12=r1+r2;
   m21=m2/m1;
   x21=x2-x1;
   y21=y2-y1;
   z21=z2-z1;
   vx21=vx2-vx1;
   vy21=vy2-vy1;
   vz21=vz2-vz1;

   vx_cm = (m1*vx1+m2*vx2)/(m1+m2) ;
   vy_cm = (m1*vy1+m2*vy2)/(m1+m2) ;
   vz_cm = (m1*vz1+m2*vz2)/(m1+m2) ;

   //     **** calculate relative distance and relative speed ***
          d=sqrt(x21*x21 +y21*y21 +z21*z21);
          v=sqrt(vx21*vx21 +vy21*vy21 +vz21*vz21);


   //     **** shift coordinate system so that ball 1 is at the origin ***
          x2=x21;
          y2=y21;
          z2=z21;

   //     **** boost coordinate system so that ball 2 is resting ***
          vx1=-vx21;
          vy1=-vy21;
          vz1=-vz21;

   //     **** find the polar coordinates of the location of ball 2 ***
          theta2=acos(z2/d);
          if (x2==0 && y2==0) {phi2=0;} else {phi2=atan2(y2,x2);}
          st=sin(theta2);
          ct=cos(theta2);
          sp=sin(phi2);
          cp=cos(phi2);

  //     **** express the velocity vector of ball 1 in a rotated coordinate
  //          system where ball 2 lies on the z-axis ******
		 vx1r=ct*cp*vx1+ct*sp*vy1-st*vz1;
		 vy1r=cp*vy1-sp*vx1;
		 vz1r=st*cp*vx1+st*sp*vy1+ct*vz1;
		 fvz1r = vz1r/v ;
		 if (fvz1r>1) {fvz1r=1;}   // fix for possible rounding errors
			else if (fvz1r<-1) {fvz1r=-1;}
		 thetav=acos(fvz1r);
		 if (vx1r==0 && vy1r==0) {phiv=0;} else {phiv=atan2(vy1r,vx1r);}


  //     **** calculate the normalized impact parameter ***
		 dr=d*sin(thetav)/r12;

   //     **** calculate impact angles if balls do collide ***
          alpha=asin(-dr);
          beta=phiv;
          sbeta=sin(beta);
          cbeta=cos(beta);


   //     **** calculate time to collision ***
          t=(d*cos(thetav) -r12*sqrt(1-dr*dr))/v;


   //     **** update positions and reverse the coordinate shift ***
          x2=x2+vx2*t +x1;
          y2=y2+vy2*t +y1;
          z2=z2+vz2*t +z1;
          x1=(vx1+vx2)*t +x1;
          y1=(vy1+vy2)*t +y1;
          z1=(vz1+vz2)*t +z1;

          //  ***  update velocities ***

                 a=tan(thetav+alpha);

                 dvz2=2*(vz1r+a*(cbeta*vx1r+sbeta*vy1r))/((1+a*a)*(1+m21));

                 vz2r=dvz2;
                 vx2r=a*cbeta*dvz2;
                 vy2r=a*sbeta*dvz2;
                 vz1r=vz1r-m21*vz2r;
                 vx1r=vx1r-m21*vx2r;
                 vy1r=vy1r-m21*vy2r;


          //     **** rotate the velocity vectors back and add the initial velocity
          //           vector of ball 2 to retrieve the original coordinate system ****

                 vx1=ct*cp*vx1r-sp*vy1r+st*cp*vz1r +vx2;
                 vy1=ct*sp*vx1r+cp*vy1r+st*sp*vz1r +vy2;
                 vz1=ct*vz1r-st*vx1r               +vz2;
                 vx2=ct*cp*vx2r-sp*vy2r+st*cp*vz2r +vx2;
                 vy2=ct*sp*vx2r+cp*vy2r+st*sp*vz2r +vy2;
                 vz2=ct*vz2r-st*vx2r               +vz2;


          //     ***  velocity correction for inelastic collisions ***

                 vx1=(vx1-vx_cm)*R + vx_cm;
                 vy1=(vy1-vy_cm)*R + vy_cm;
                 vz1=(vz1-vz_cm)*R + vz_cm;
                 vx2=(vx2-vx_cm)*R + vx_cm;
                 vy2=(vy2-vy_cm)*R + vy_cm;
                 vz2=(vz2-vz_cm)*R + vz_cm;
}

void checkCollisions(std::vector<Particle> & p)
{
	for(unsigned int i = 0; i < p.size()-1; i++)
	{
		for(unsigned int j = i+1; j < p.size(); j++)
		{
			if((p.at(i).pos - p.at(j).pos).r <= (p.at(i).size + p.at(j).size)/400)
			{
				elasticCollision(1, p.at(i).mass, p.at(j).mass,
									p.at(i).size, p.at(j).size,
									p.at(i).pos.x, p.at(i).pos.y, p.at(i).pos.z,
									p.at(j).pos.x, p.at(j).pos.y, p.at(j).pos.z,
									p.at(i).vel.x, p.at(i).vel.y, p.at(i).vel.z,
									p.at(j).vel.x, p.at(j).vel.y, p.at(j).vel.z);
				p.at(i).pos.cartesianToSpherical();
				p.at(j).pos.cartesianToSpherical();
				p.at(i).vel.cartesianToSpherical();
				p.at(j).vel.cartesianToSpherical();
			}
		}
	}
}

int randomSign()
{
	if(((double)(rand() % 100) / 100) <= 0.5)
		return -1;
	return 1;
}

void createParticles(std::vector<Particle>& p, int number, double mass, double size, std::vector<double> color, bool centerOfGravity,
					double massCOG, double sizeCOG, std::vector<double> colorCOG,
					double posRangeX, double posRangeY, double posRangeZ,
					double velRange1, double velRange2)
{

	if(centerOfGravity)
	{
		Vector3 pos(0,0,0);
		Vector3 vel(0,0,0);
		Particle COG(massCOG, pos, vel, sizeCOG, colorCOG);
		p.push_back(COG);
	}

	for(int i = 0; i < number; i++)
	{
		int roundingNumber = 100;

		double x = (double)(rand() % (int)round(posRangeX*roundingNumber)) * randomSign() / roundingNumber;
		double y = (double)(rand() % (int)round(posRangeY*roundingNumber)) * randomSign() / roundingNumber;

		//double z = (double)(rand() % (int)round(posRangeZ*roundingNumber)) * randomSign() / roundingNumber;

		double z = 0;
		double v = (velRange2 - velRange1) + (double)(rand() % (int)round((velRange1 * roundingNumber))) / roundingNumber;

		//double v = velRange1 + (double)(rand() % (int)round((velRange2 - velRange1)*roundingNumber)) / roundingNumber;
		double theta = (double)(rand() % (int)round(M_PI * roundingNumber)) / roundingNumber;
		double phi = (double)(rand() % (int)round(2 * M_PI * roundingNumber)) / roundingNumber;
		//double phi = 0;
		Vector3 dummyPos(x,y,z,0);
		Vector3 dummyVel(v,theta,phi,1);

		Particle dummy(mass, dummyPos, dummyVel, size, color);

		p.push_back(dummy);
	}
}


