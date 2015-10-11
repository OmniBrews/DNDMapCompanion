#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include "Entity.h"

enum TerrainType { Basic, Woods, River, Brush, Desert, Custom };

class Terrain
{
	std::vector<Entity*> entities_in_square;
	TerrainType type;
	std::string custom_image;
	int elevation;

public:
	Terrain();
	Terrain(TerrainType typ, std::string image, int elevation);
	TerrainType getType();
	std::string getImage();
	std::vector<Entity*> getEntities();
	void addEntity(Entity* e);
	void removeEntitiy(Entity* e);
};