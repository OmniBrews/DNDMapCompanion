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
int display_x;				//Number of columns drawn
int display_y;				//Number of rows drawn
int bottom_left_x;			//X-Coordinate on the map that is drawn in the bottom left corner
int bottom_left_y;			//Y-Coordinate on the map that is drawn in the bottom left corner
bool left_mouse_down;		//Left mouse button is down
bool right_mouse_down;		//Right mouse button is down
int right_x;				//X-Coordinate where right mouse button was down
int right_y;				//Y-Coordinate where right mouse button was down
int entityID;				//Default entity ID assigned the new entities then increamented
int draw_mode;				//If 0 draw entity. If 1 draw terrain.

int old_x;
int old_y;

TerrainType terrain_type;	//Type of terrain being drawn
EntityType entity_type;		//Type of Entity selected

//GLUI Stuff
GLUI_RadioGroup *terrain_radio;
GLUI_RadioGroup *entity_radio;
GLUI_RadioGroup *mode_radio;
int tt = 0;
int et = 0;


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
	glutSetWindow(main_window);

	float xMax = findxMax(xin - bottom_left_x);
	float xMin = findxMin(xin - bottom_left_x);
	float yMax = findyMax(yin - bottom_left_y);
	float yMin = findyMin(yin - bottom_left_y);

	//enum TerrainType { Basic, Woods, River, Brush, Desert, Custom };
	switch (T.getType()){
	case TerrainType::Basic:
		glColor3f(.5, .5, .5);
		break;
	case TerrainType::Woods:
		glColor3f(.2, .7, .2);
		break;
	case TerrainType::River:
		glColor3f(.2, .2, .7);
		break;
	case TerrainType::Brush:
		glColor3f(.2, .5, .5);
		break;
	case TerrainType::Desert:
		glColor3f(.5, .2, .5);
		break;
	case TerrainType::Custom:
		glColor3f(.4, .4, .4);
		break;
	}

	glBegin(GL_POLYGON);
	glVertex2f(xMin, yMin);
	glVertex2f(xMax, yMin);
	glVertex2f(xMax, yMax);
	glVertex2f(xMin, yMax);
	glEnd();
	//glFlush();
}

void drawEntity(Entity *E){
	glutSetWindow(main_window);

	int xin = E->getX() - bottom_left_x;
	int yin = E->getY() - bottom_left_y;

	float xMax = findxMax(xin);
	float xMin = findxMin(xin);
	float yMax = findyMax(yin);
	float yMin = findyMin(yin);
	glColor3f(.1, .1, .1);
	switch (E->getType()){
	case EntityType::Tank:
		
		glBegin(GL_POLYGON);
		glVertex2f(xMin + .01, yMin + .08);
		glVertex2f(xMin + .035, yMin + .02);
		glVertex2f(xMax - .035, yMin + .02);
		glVertex2f(xMax - .01, yMin + .08);
		glVertex2f(xMax - .01, yMax - .02);
		glVertex2f(xMin + .01, yMax - .02);
		glEnd();

		break;
	case EntityType::Melee:
	
		glBegin(GL_POLYGON);
		glVertex2f(xMin + .05, yMin + .02);
		glVertex2f(xMax - .05, yMin + .02);
		glVertex2f(xMax - .05, yMax - .02);
		glVertex2f(xMin + .05, yMax - .07);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(xMin + .035, yMin + .055);
		glVertex2f(xMax - .035, yMin + .055);
		glVertex2f(xMax - .035, yMin + .045);
		glVertex2f(xMin + .035, yMin + .045);
		glEnd();

		break;
	case EntityType::Ranged:
		
		glBegin(GL_POLYGON);
		glVertex2f(xMin + .015, yMin + .02);
		glVertex2f(xMin + .02, yMin + .02);
		glVertex2f(xMin + .02, yMax - .02);
		glVertex2f(xMin + .015, yMax - .02);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(xMax - .015, yMin + .02);
		glVertex2f(xMax - .02, yMin + .02);
		glVertex2f(xMax - .02, yMax - .02);
		glVertex2f(xMax - .015, yMax - .02);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(xMin + .044, yMin + .02);
		glVertex2f(xMax - .044, yMin + .02);
		glVertex2f(xMax - .044, yMax - .02);
		glVertex2f(xMin + .044, yMax - .02);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(xMin + .04, yMax - .05);
		glVertex2f(xMax - .04, yMax - .05);
		glVertex2f(xMax - .045, yMax - .02);
		glVertex2f(xMin + .045, yMax - .02);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(xMin + .01, yMax - .05);
		glVertex2f(xMin + .025, yMax - .05);
		glVertex2f(xMin + .0175, yMax - .02);
		glVertex2f(xMin + .0125, yMax - .02);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(xMax - .01, yMax - .05);
		glVertex2f(xMax - .025, yMax - .05);
		glVertex2f(xMax - .0175, yMax - .02);
		glVertex2f(xMax - .0125, yMax - .02);
		glEnd();


		break;
	case EntityType::Magic:
		
		glBegin(GL_POLYGON);
		glVertex2f(xMin + .05, yMin + .02);
		glVertex2f(xMax - .05, yMin + .02);
		glVertex2f(xMax - .05, yMax - .02);
		glVertex2f(xMin + .05, yMax - .02);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(xMin + .04, yMax - .05);
		glVertex2f(xMax - .04, yMax - .05);
		glVertex2f(xMax - .04, yMax - .02);
		glVertex2f(xMin + .04, yMax - .02);
		glEnd();

		break;
	case EntityType::Healer:
		
		glBegin(GL_POLYGON);
		glVertex2f(xMin + .035, yMin + .02);
		glVertex2f(xMax - .035, yMin + .02);
		glVertex2f(xMax - .035, yMax - .02);
		glVertex2f(xMin + .035, yMax - .02);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(xMin + .01, yMin + .06);
		glVertex2f(xMax - .01, yMin + .06);
		glVertex2f(xMax - .01, yMax - .06);
		glVertex2f(xMin + .01, yMax - .06);
		glEnd();

		break;
	case EntityType::Mob:
		
		glBegin(GL_POLYGON);
		glVertex2f(xMin + .015, yMin + .02);
		glVertex2f(xMin + .02, yMin + .02);
		glVertex2f(xMin + .02, yMax - .02);
		glVertex2f(xMin + .015, yMax - .02);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(xMax - .015, yMin + .02);
		glVertex2f(xMax - .02, yMin + .02);
		glVertex2f(xMax - .02, yMax - .02);
		glVertex2f(xMax - .015, yMax - .02);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(xMin + .044, yMin + .02);
		glVertex2f(xMax - .044, yMin + .02);
		glVertex2f(xMax - .044, yMax - .02);
		glVertex2f(xMin + .044, yMax - .02);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(xMin + .015, yMax - .05);
		glVertex2f(xMin + .045, yMax - .05);
		glVertex2f(xMin + .045, yMax - .02);
		glVertex2f(xMin + .015, yMax - .02);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(xMax - .015, yMax - .05);
		glVertex2f(xMax - .045, yMax - .05);
		glVertex2f(xMax - .045, yMax - .02);
		glVertex2f(xMax - .015, yMax - .02);
		glEnd();

		break;
	case EntityType::Boss:
		
		glBegin(GL_POLYGON);
		glVertex2f(xMin + .01, yMin + .02);
		glVertex2f(xMin + .03, yMin + .02);
		glVertex2f(xMax - .03, yMax - .02);
		glVertex2f(xMax - .01, yMax - .02);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(xMax - .01, yMin + .02);
		glVertex2f(xMax - .03, yMin + .02);
		glVertex2f(xMin + .03, yMax - .02);
		glVertex2f(xMin + .01, yMax - .02);
		glEnd();

		break;
	case EntityType::Neutral:
		
		glBegin(GL_POLYGON);
		glVertex2f(xMin + .02, yMin + .03);
		glVertex2f(xMax - .02, yMin + .03);
		glVertex2f(xMax - .02, yMax - .03);
		glVertex2f(xMin + .02, yMax - .03);
		glEnd();

		break;
	}
	//glColor3f(.2, .5, .2);

	//glFlush();
}

void myDisplay(void){
	glutSetWindow(main_window);

	glClearColor(.2f, .2f, .2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);

	//Draw Terrain
	for (int i = bottom_left_x; i < bottom_left_x + display_x; i++){
		for (int j = bottom_left_y; j < bottom_left_y + display_y; j++){
			drawTerrain(map->terrainAtSquare(i, j), i, j);
		}
	}

	//Draw Entities
	for (int i = bottom_left_x; i < bottom_left_x + display_x; i++){
		for (int j = bottom_left_x; j < bottom_left_y + display_y; j++){
			for (int k = 0; k < map->entitiesAtSquare(i, j).size(); k++){
				drawEntity(map->entitiesAtSquare(i, j)[k]);
			}
		}
	}

	//Draw Grided Lines
	if (draw_grid){
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
		for (int i = 0; i <= display_x; i++){
			glVertex2f((9.0f / 16.0) * (2 * i * (1.0f / display_x)) - 1, -1.0f);
			glVertex2f((9.0f / 16.0) * (2 * i * (1.0f / display_x)) - 1, 1.0f);
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
	switch (Key){
	case 97:	//a
		if (bottom_left_x > 0)
			bottom_left_x--;
		break;
	case 119:	//w
		if (bottom_left_y < map->getMapHeight() - (1 + display_y))
			bottom_left_y++;
		break;
	case 100:	//d
		if (bottom_left_x < map->getMapWidth() - (1 + display_x))
			bottom_left_x++;
		break;
	case 115:	//s
		if (bottom_left_y > 0)
			bottom_left_y--;
		break;
		/*case 9:		//tab
		if (terrain_type == TerrainType::Basic)
		terrain_type = TerrainType::River;
		else
		terrain_type = TerrainType::Basic;
		break;
		case 32:	//space
		if (draw_mode == 0)
		draw_mode = 1;
		else
		draw_mode = 0;
		break;*/
	default:
		break;
	}
	myDisplay();
}

void myMouse(int button, int button_state, int x, int y){
	int x_pos;
	int y_pos;

	if (button_state == GLUT_DOWN){
		switch (button){
		case GLUT_LEFT_BUTTON:
			left_mouse_down = true;
			if (x < 720){
				switch (draw_mode){
				case 0:
					x_pos = display_x * x / 720;
					y_pos = display_y * (720 - y) / 720;
					map->createEntity(entityID, (EntityType)et, x_pos + bottom_left_x, y_pos + bottom_left_y, "Player", "", 10, 30);
					entityID++;
					break;
					case 1:
						break;
					case 2:
						x_pos = display_x * x / 720;
						y_pos = display_y * (720 - y) / 720;

						old_x = x_pos + bottom_left_x;
						old_y = y_pos + bottom_left_y;
						std::cout << "case 2" << std::endl;
						std::cout << "old x " << old_x << std::endl;
						std::cout << "old y " << old_y << std::endl;
						/*get entity at square
							get x get y
							store in temp x temp y in MyMouse
						*/

						break;
						/*
					x_pos = display_x * x / 720;
					y_pos = display_y * (720 - y) / 720;
					map->updateTerrainAtSquare(terrain_type, x_pos + bottom_left_x, y_pos + bottom_left_y);
					break;*/
				}
			}
			break;
		case GLUT_RIGHT_BUTTON:
			if (x < 720){
				right_mouse_down = true;
				right_x = display_x * x / 720 + bottom_left_x;
				right_y = display_y * (720 - y) / 720 + bottom_left_y;
			}
			if (x < 720 && (draw_mode == 0)){
				x_pos = display_x * x / 720;
				y_pos = display_y * (720 - y) / 720;
				if (map->entitiesAtSquare(x_pos, y_pos).size() > 0){
					map->removeEntity(map->entitiesAtSquare(x_pos, y_pos)[0]);
				}
			}
			if (x < 720 && (draw_mode == 2)){
				x_pos = display_x * x / 720;
				y_pos = display_y * (720 - y) / 720;
				//std::cout << "new x " << x_pos << std::endl;
				//std::cout << "new y " << y_pos << std::endl;
				//std::cout << "old x " << old_x << std::endl;
				//std::cout << "old y " << old_y << std::endl;
				if (map->entitiesAtSquare(old_x, old_y).size() > 0){
					//std::cout << "if statement" << std::endl;
					map->removeEntity(map->entitiesAtSquare(old_x-bottom_left_x, old_y-bottom_left_y)[0]);
					map->createEntity(entityID, (EntityType)et, x_pos + bottom_left_x, y_pos + bottom_left_y, "Player", "", 10, 30);
				}
			}
			break;
		}
	}
	if (button_state == GLUT_UP){
		if (button == GLUT_LEFT_BUTTON){
			left_mouse_down = false;
		}
		if (button == GLUT_RIGHT_BUTTON){
			right_mouse_down = false;
			if (x < 720 && (draw_mode == 1)){
				x_pos = display_x * x / 720 + bottom_left_x;
				y_pos = display_y * (720 - y) / 720 + bottom_left_y;
				for (int i = std::min(x_pos, right_x); i <= std::max(x_pos, right_x); i++){
					for (int j = std::min(y_pos, right_y); j <= std::max(y_pos, right_y); j++){
						map->updateTerrainAtSquare((TerrainType)tt, i, j);
					}
				}
			}
		}
	}
	myDisplay();
}

void myMotion(int x, int y){
	int x_pos, y_pos;
	if (left_mouse_down && (draw_mode == 1) && (x < 720)){
		x_pos = display_x * x / 720;
		y_pos = display_y * (720 - y) / 720;
		map->updateTerrainAtSquare((TerrainType)tt, x_pos + bottom_left_x, y_pos + bottom_left_y);
	}
	myDisplay();
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	map = new Map(30, 30);
	draw_grid = true;
	display_x = 12;
	display_y = 12;
	bottom_left_x = 0;
	bottom_left_y = 0;
	left_mouse_down = false;
	entityID = 0;
	draw_mode = 0;
	terrain_type = TerrainType::River;

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(100, 100);
	main_window = glutCreateWindow("DND Map Companion");

	glutDisplayFunc(myDisplay);
	//glutIdleFunc(NULL);
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(myKeyboard);
	glutMouseFunc(myMouse);
	glutMotionFunc(myMotion);

	GLUI_Master.set_glutIdleFunc(NULL);

	GLUI *glui = GLUI_Master.create_glui_subwindow(main_window, GLUI_SUBWINDOW_RIGHT);

	GLUI_Panel *mode_panel = new GLUI_Panel(glui, "Draw Mode");
	mode_radio = glui->add_radiogroup_to_panel(mode_panel, &draw_mode);
	glui->add_radiobutton_to_group(mode_radio, "Draw Entity");
	glui->add_radiobutton_to_group(mode_radio, "Draw Terrain");
	glui->add_radiobutton_to_group(mode_radio, "Move Entities");

	GLUI_Panel *terrain_panel = new GLUI_Panel(glui, "Terrain Type");
	terrain_radio = glui->add_radiogroup_to_panel(terrain_panel, &tt);
	glui->add_radiobutton_to_group(terrain_radio, "Basic");
	glui->add_radiobutton_to_group(terrain_radio, "Woods");
	glui->add_radiobutton_to_group(terrain_radio, "River");
	glui->add_radiobutton_to_group(terrain_radio, "Brush");
	glui->add_radiobutton_to_group(terrain_radio, "Desert");
	glui->add_radiobutton_to_group(terrain_radio, "Custom");

	GLUI_Panel *entity_panel = new GLUI_Panel(glui, "Entity Type");
	entity_radio = glui->add_radiogroup_to_panel(entity_panel, &et);
	glui->add_radiobutton_to_group(entity_radio, "Tank");
	glui->add_radiobutton_to_group(entity_radio, "Melee");
	glui->add_radiobutton_to_group(entity_radio, "Ranged");
	glui->add_radiobutton_to_group(entity_radio, "Magic");
	glui->add_radiobutton_to_group(entity_radio, "Healer");
	glui->add_radiobutton_to_group(entity_radio, "Mob");
	glui->add_radiobutton_to_group(entity_radio, "Boss");
	glui->add_radiobutton_to_group(entity_radio, "Neutral");

	glutSetWindow(main_window);
	glui->set_main_gfx_window(main_window);

	glutMainLoop();

	return 0;
}
