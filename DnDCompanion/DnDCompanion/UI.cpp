// Installing Freeglut
/*
	Open your solution, click TOOLS->NuGet Package Manager->Package Manager Console to open a NuGet console, type Install-Package freeglut.
	--
	For VS 2013, use nupengl.core package instead.
*/

// Installing glui
/*
	https://masdel.wordpress.com/2010/06/13/installing-glui-using-vc-on-windows/
	If you have problems, read the note at the end of the post
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <GL/glut.h>
#include <GL/glui.h>
#include "Map.h"
#include "Entity.h"
#include "Terrain.h"

int main_window;
Map *map;
bool draw_grid;
int display_x;
int display_y;

float findxMax(int x){

	float xMax = -1.0 + (x + 1.0)*(60.0 * (2.0 / 1280.0));
	return xMax;
}
float findxMin(int x){

	float xMin = -1.0 + (x)*(60.0 * (2.0 / 1280.0));
	return xMin;
}
float findyMax(int y){

	float yMax = -1.0 + (y + 1.0)*(60.0 * (2.0 / 720.0));
	return yMax;
}
float findyMin(int y){

	float yMin = -1.0 + (y)*(60.0 * (2.0 / 720.0));
	return yMin;
}

void myGlui(){

}

void myInit(){

}

void drawTerrain(Terrain T, int xin, int yin){
	float xMax = findxMax(xin);
	float xMin = findxMin(xin);
	float yMax = findyMax(yin);
	float yMin = findyMin(yin);

	glColor3f(.5, .2, .2);
	glBegin(GL_POLYGON);
	glVertex2f(xMin, yMin);
	glVertex2f(xMax, yMin);
	glVertex2f(xMax, yMax);
	glVertex2f(xMin, yMax);
	glEnd();
	//glFlush();
}

void drawEntity(Entity E){
	int xin = E.getX();
	int yin = E.getY();

	float xMax = findxMax(xin);
	float xMin = findxMin(xin);
	float yMax = findyMax(yin);
	float yMin = findyMin(yin);

	glColor3f(0.2, .5, .5);
	glBegin(GL_POLYGON);
	glVertex2f(xMin, yMin);
	glVertex2f(xMax, yMin);
	glVertex2f(xMax, yMax);
	glVertex2f(xMin, yMax);
	glEnd();
	//glFlush();
}

void myDisplay(void){
	glClearColor(.2f, .2f, .2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);

	//Draw Terrain
	for (int i = 0; i < display_x; i++){
		for (int j = 0; j < display_y; j++){
			drawTerrain(map->terrainAtSquare(i, j), i , j);
		}
	}

	//Draw Entities
	for (int i = 0; i < display_x; i++){
		for (int j = 0; j < display_y; j++){
			std::vector<Entity*> entity_list = map->entitiesAtSquare(i, j);
			for (int k = 0; k < entity_list.size(); k++){
				Entity e = Entity(0, Player, "Player0", "", 10, 0);
				e.setPostion(i, j);
				drawEntity(e);
			}
		}
	}

	//Draw Grided Map
	if (draw_grid){
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
		for (int i = 0; i <= display_x; i++){
			glVertex2f((9.0f / 16.0) * (2 * i * (1.0f / display_x)) - 1, -1.0f);
			glVertex2f((9.0f / 16.0) * (2 * i * (1.0f / display_x)) - 1,  1.0f);
		}
		for (int i = 0; i <= display_y; i++){
			glVertex2f(-1.0f, (2 * i * (1.0f / display_y)) - 1);
			glVertex2f((9.0f / 16.0 * 2) - 1, (2 * i * (1.0f / display_y)) - 1);
		}
		glEnd();
	}

	glFlush();
	glutSwapBuffers();
}

void myReshape(int x, int y){

}

void myKeyboard(unsigned char Key, int x, int y){

}

void myMouse(int button, int button_state, int x, int y){

}

void myMotion(int x, int y){

}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	map = new Map(30, 30);
	draw_grid = true;
	display_x = 12;
	display_y = 12;

	//Hardcoded example map
	map->createEntity(0, Player, 0, 0, "Player 0", "", 10, 30);
	map->createEntity(1, Player, 1, 1, "Player 1", "", 10, 30);
	map->createEntity(2, Player, 2, 2, "Player 2", "", 10, 30);
	map->createEntity(3, Player, 3, 3, "Player 3", "", 10, 30);
	map->createEntity(4, Player, 4, 4, "Player 4", "", 10, 30);
	map->createEntity(5, Player, 5, 5, "Player 5", "", 10, 30);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(100, 100);
	main_window = glutCreateWindow("DND Map Companion");

	glutDisplayFunc(myDisplay);
	glutIdleFunc(NULL);
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(myKeyboard);
	glutMouseFunc(myMouse);
	glutMotionFunc(myMotion);

	myGlui();
	myInit();

	glutMainLoop();

	return 0;
}
