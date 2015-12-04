#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Terrain.h"
#include "Entity.h"

class Map {
	int x_size;
	int y_size;
	std::vector<Entity> entity_list;
	std::vector<std::vector<Terrain>> terrain_map;

public:
	Map(int x, int y);
	Map(std::string loadFileName);
	int getMapWidth();
	int getMapHeight();
	std::vector<Entity*> entitiesAtSquare(int x, int y);
	Terrain terrainAtSquare(int x, int y);
	TerrainType terrainTypeAtSquare(int x, int y);
	void updateTerrainAtSquare(TerrainType t, int x, int y);
	void addEntity(Entity e);
	void createEntity(int entity_ID, EntityType type, int x, int y, std::string name, std::string image, double health, double sight_range);
	void moveEntity(int entity_ID, int x, int y);
	void removeEntity(Entity* entity);
	void removeEntity(int entity_ID);
	Entity* findEntity(int entity_ID);
	void saveToFile(std::string fileName);
	void loadFromFile(std::string fileName);
};