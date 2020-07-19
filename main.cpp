/*
 * main.cpp
 *
 *  Created on: 05 gen 2017
 *      Author: kevin
 */
/*
 * OGL02Animation.cpp: 3D Shapes with animation
 */
#include <Windows.h>  // for MS Windows
#include "functions.h"
#include "prototypes.h"

#define Cos(th) cos(M_PI/180*(th))
#define Sin(th) sin(M_PI/180*(th))

double dim = 3;
const char* windowName = "Hello OpenGL";
int keyPressed = 0;
const char* modifiers = "";
const char* special  = "";

int toggleAxes = 0;
int toggleValues = 1;
int toggleMode = 0;

int th = 0;
int ph = 0;
int fov = 55;
int asp = 1;
double xTr = 0;
double yTr = 0;
double zTr = 0;

GLfloat vertA[3] = {0.5, 0.5, 0.5};
GLfloat vertB[3] = {-0.5, 0.5, 0.5};
GLfloat vertC[3] = {-0.5, -0.5, 0.5};
GLfloat vertD[3] = {0.5, -0.5, 0.5};
GLfloat vertE[3] = {0.5, 0.5, -0.5};
GLfloat vertF[3] = {-0.5, 0.5, -0.5};
GLfloat vertG[3] = {-0.5, -0.5, -0.5};
GLfloat vertH[3] = {0.5, -0.5, -0.5};

int objId = 0;
int objSlices = 16;
int objStacks = 16;

/////////// PARTICLES' VARIABLES //////////////
std::vector<Particle> particles;

double massOfParticles;
double sizeOfParticles;
int numberOfParticles;
std::vector<double> colorOfParticles;
std::vector<double> velRange;
std::vector<double> posRange;

bool centerOfGravity;
double massCOG;
double sizeCOG;
std::vector<double> colorCOG;

bool drawTrajectories;

double dt;
//////////////////////////////////////////////

void initializeVariables(int number, double massOfParticle, double sizeOfParticle, std::vector<double> _color,
						bool COG, double _massCOG, double _sizeCOG, std::vector<double> _colorCOG,
						double velRange1, double velRange2,
						double posRangeX, double posRangeY, double posRangeZ,
						double _dt, bool _drawTrajectories)
{
	numberOfParticles = number;
	massOfParticles = massOfParticle;
	sizeOfParticles = sizeOfParticle;
	colorOfParticles.resize(0);
	colorOfParticles.push_back(_color.at(0));
	colorOfParticles.push_back(_color.at(1));
	colorOfParticles.push_back(_color.at(2));

	centerOfGravity = COG;
	massCOG = _massCOG;
	sizeCOG = _sizeCOG;
	colorCOG.resize(0);
	colorCOG.push_back(_colorCOG.at(0));
	colorCOG.push_back(_colorCOG.at(1));
	colorCOG.push_back(_colorCOG.at(2));

	velRange.resize(0);
	velRange.push_back(velRange1);
	velRange.push_back(velRange2);
	posRange.resize(0);
	posRange.push_back(posRangeX);
	posRange.push_back(posRangeY);
	posRange.push_back(posRangeZ);

	dt = _dt;
	drawTrajectories = _drawTrajectories;
}

void project()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(toggleMode)
		gluPerspective(fov, asp, dim/4, 4*dim);
	else
		glOrtho(-dim*asp, +dim*asp, -dim, +dim, -dim, +dim);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void drawAxes()
{
	if(toggleAxes)
	{
		double len = 2.0;
		glColor3f(1,1,1);
		glBegin(GL_LINES);
			glVertex3d(0, 0, 0);
			glVertex3d(len, 0, 0);
			glVertex3d(0, 0, 0);
			glVertex3d(0, len, 0);
			glVertex3d(0, 0, 0);
			glVertex3d(0, 0, len);
		glEnd();

		glRasterPos3d(len, 0, 0);
		print("X");
		glRasterPos3d(0, len, 0);
		print("Y");
		glRasterPos3d(0, 0, len);
		print("Z");
	}

}

void drawShape()
{
	/*glBegin(GL_QUADS);
		glColor3f(1, 1, 0);
		glVertex3fv(vertA);
		glVertex3fv(vertB);
		glVertex3fv(vertC);
		glVertex3fv(vertD);

		glColor3f(1, 0, 0);
		glVertex3fv(vertF);
		glVertex3fv(vertE);
		glVertex3fv(vertH);
		glVertex3fv(vertG);

		glColor3f(0, 1, 0);
		glVertex3fv(vertE);
		glVertex3fv(vertA);
		glVertex3fv(vertD);
		glVertex3fv(vertH);

		glColor3f(0, 0, 1);
		glVertex3fv(vertB);
		glVertex3fv(vertF);
		glVertex3fv(vertG);
		glVertex3fv(vertC);

		glColor3f(0, 1, 1);
		glVertex3fv(vertE);
		glVertex3fv(vertF);
		glVertex3fv(vertB);
		glVertex3fv(vertA);

		glColor3f(1, 0, 1);
		glVertex3fv(vertD);
		glVertex3fv(vertC);
		glVertex3fv(vertG);
		glVertex3fv(vertH);
	glEnd();*/
/*
	glPointSize(10/dim);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
		glColor3f(1, 1, 1);
		glVertex3f(0, 0, 0);
	glEnd();
*/
}

void drawValues()
{
	if(toggleValues)
	{
		glColor3f(0.8, 0.8, 0.8);
		printAt(-1, -1, "View angle (th, ph) = (%d, %d)", th, ph);
		printAt(-1, -2, "Projection mode = %s", toggleMode? "Perspective" : "Orthogonal");
		glRasterPos3fv(vertA);
		print("A");
		glRasterPos3fv(vertB);
		print("B");
		glRasterPos3fv(vertC);
		print("C");
		glRasterPos3fv(vertD);
		print("D");
		glRasterPos3fv(vertE);
		print("E");
		glRasterPos3fv(vertF);
		print("F");
		glRasterPos3fv(vertG);
		print("G");
		glRasterPos3fv(vertH);
		print("H");
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);

	glLoadIdentity();

	glTranslatef(xTr, yTr, zTr);

	if(toggleMode)
	{
		double Ex = -2*dim * Sin(th) * Cos(ph);
		double Ey = +2*dim*Sin(ph);
		double Ez = +2*dim*Cos(th)*Cos(ph);

		gluLookAt(Ex, Ey, Ez, xTr, yTr, zTr, 0, Cos(ph), 0);
	}
	else
	{
		glRotated(ph, 1, 0, 0);
		glRotated(th, 0, 1, 0);
	}

	drawParticles(particles);
	drawAxes();
	if(drawTrajectories)
	{
		for(unsigned int i = 0; i < particles.size(); i++)
		{
			particles.at(i).drawTrajectory();
		}
	}

	glFlush();
	glutSwapBuffers();

}

void reshape(int width, int height)
{

	asp = (height>0) ? (double)width/height : 1;
	glViewport(0, 0, width, height);
	project();

}

void windowKey(unsigned char key, int x, int y)
{
	if(key == 27)
		exit(0);
	else if(key == 'a' || key == 'A')
		toggleAxes = 1-toggleAxes;
	else if(key == 'v' || key == 'V')
		toggleValues = 1-toggleValues;
	else if(key == 'n' || key == 'N')
		toggleMode = 1-toggleMode;
	else if(key == '-' && key > 1)
		fov --;
	else if(key == '+' && key < 179)
		fov ++;
	else if(key == 'D')
		dim += 0.1;
	else if(key == 'd' && dim > 1)
		dim -= 0.1;
	else if(key == 32)
	{
		if(objId == 18)
			objId = 0;
		else
			objId++;
	}
	else if(key == 'x')
		xTr += 0.15;
	else if(key == 'y')
		yTr += 0.15;
	else if(key == 'z')
		zTr += 0.15;
	else if(key == 'X')
		xTr -= 0.15;
	else if(key == 'Y')
		yTr -= 0.15;
	else if(key == 'Z')
		zTr -= 0.15;

	project();
	glutPostRedisplay();
}

void windowSpecial(int key, int x, int y)
{
	if(key == GLUT_KEY_RIGHT)
		th += 5;
	else if (key == GLUT_KEY_LEFT)
		th -= 5;
	else if(key == GLUT_KEY_UP)
		ph += 5;
	else if(key == GLUT_KEY_DOWN)
		ph -= 5;

	th %= 360;
	ph %= 360;

	glutPostRedisplay();
}

void windowMenu(int value)
{
	windowKey((unsigned char)value, 0, 0);
}

void idleGL()
{
	//checkCollisions(particles);
	moveParticles(particles, dt);
	calculateForces(particles);
	glutPostRedisplay();
}

int main(int argc, char* argv)
{

	srand(time(NULL));

	std::vector<double> _color;
	_color.resize(0);
	_color.push_back(1);
	_color.push_back(1);
	_color.push_back(1);

	std::vector<double> _colorCOG;
	_colorCOG.resize(0);
	_colorCOG.push_back(1);
	_colorCOG.push_back(0);
	_colorCOG.push_back(0);

	//initializVariabes(number,massOfParticle,sizeOfParticle,color,massCOG,sizeCOG,colorCOG,velRange1, double velRange2,
	//					posRangeX,posRangeY,posRangeZ,dt)

	initializeVariables(30, 200, 5, _color, true, 10000, 10, _colorCOG, 120, 130, 2, 2, 2, 0.00005, false);

	createParticles(particles, numberOfParticles, massOfParticles, sizeOfParticles, colorOfParticles,
					centerOfGravity, massCOG, sizeCOG, colorCOG,
					posRange.at(0), posRange.at(1), posRange.at(2),
					velRange.at(0), velRange.at(1));

	glutInit(&argc, &argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);

	glutCreateWindow(windowName);

	glutDisplayFunc(display);
	glutIdleFunc(idleGL);
	glutReshapeFunc(reshape);

	glutKeyboardFunc(windowKey);
	glutSpecialFunc(windowSpecial);

	glutCreateMenu(windowMenu);
	glutAddMenuEntry("Toggle Axis [a]", 'a');
	glutAddMenuEntry("Toggle Values [v]", 'v');
	glutAddMenuEntry("Toggle Mode [m]", 'm');
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();

}
























