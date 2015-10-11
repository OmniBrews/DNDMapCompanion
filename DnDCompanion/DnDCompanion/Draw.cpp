#include <stdio.h> 
#include <GL/glut.h>
#include "Entity.h"
#include "Map.h"
#include "Terrain.h"

float findxMax(int x){

	float xMax = -1 + x*(60 * (2 / 720));
	return xMax;
}
float findxMin(int x){

	float xMin = -1 + (x - 1)*(60 * (2 / 720));
	return xMin;
}
float findyMax(int y){

	float yMax = -1 + y*(60 * (2 / 1280));
	return yMax;
}
float findyMin(int y){

	float yMin = -1 + (y - 1)*(60 * (2 / 1280));
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
