#include <stdio.h> 
#include <GL/glut.h>
#include "Entity.h"
#include "Map.h"
#include "Terrain.h"

float findxMax(int x){

	float xMax = -1.0 + (x+1.0)*(60.0 * (2.0 / 1280.0));
	return xMax;
}
float findxMin(int x){

	float xMin = -1.0 + (x)*(60.0 * (2.0 / 1280.0));
	return xMin;
}
float findyMax(int y){

	float yMax = -1.0 + (y+1.0)*(60.0 * (2.0 / 720.0));
	return yMax;
}
float findyMin(int y){

	float yMin = -1.0 + (y)*(60.0 * (2.0 / 720.0));
	return yMin;
}

void drawTerrain(Terrain T, int xin, int yin)
{
	float xMax = findxMax(xin);
	float xMin = findxMin(xin);
	float yMax = findyMax(yin);
	float yMin = findyMin(yin);

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(xMin, yMin);
	glVertex2f(xMax, yMin);
	glVertex2f(xMax, yMax);
	glVertex2f(xMin, yMax);
	glEnd();
	glFlush();
}

void drawEntity(Entity E)
{
	int xin = E.getX();
	int yin = E.getY();

	float xMax = findxMax(xin);
	float xMin = findxMin(xin);
	float yMax = findyMax(yin);
	float yMin = findyMin(yin);

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(xMin, yMin);
	glVertex2f(xMax, yMin);
	glVertex2f(xMax, yMax);
	glVertex2f(xMin, yMax);
	glEnd();
	glFlush();
}
