#include "Map.h"



Map::Map(int x, int y)
{
	x_size = x;
	y_size = y;
	for (int i = 0; i < x_size; x++) 
	{
		std::vector<Terrain> tempVector;
		for (int j = 0; j < y_size; j++)
		{
			tempVector.push_back(Terrain());
		}
		terrain_map.push_back(tempVector);
	}
}

Map::Map(std::string loadFileName)
{
	Map(10, 10);
}

int Map::getMapWidth()
{
	return x_size;
}

int Map::getMapHeight()
{
	return y_size;
}

std::vector<Entity*> Map::entitiesAtSquare(int x, int y)
{
	return terrain_map[x][y].getEntities();
}

TerrainType Map::terrainAtSquare(int x, int y)
{
	return terrain_map[x][y].getType();
}

void Map::addEntity(Entity e)
{
	entity_list.push_back(e);
}

void Map::createEntity(int entity_ID, EntityType type, int x, int y, std::string name, std::string image, double health, double sight_range)
{
	Entity temp = Entity(entity_ID, type, name, image, health, sight_range);
	temp.setPostiion(x, y);
	entity_list.push_back(temp);
}

void Map::moveEntity(int entity_ID, int x, int y)
{
	findEntity(entity_ID)->setPostiion(x, y);
}

void Map::removeEntity(Entity* entity)
{
	if (entity->isNull())
	{
		return;
	}

	terrain_map[entity->getX()][entity->getY()].removeEntitiy(entity);
	
	std::vector<Entity>::iterator position = entity_list.begin();
	while (position != entity_list.end() && position->getID() != entity->getID())
		position++;
	if (position != entity_list.end())
		entity_list.erase(position);
}

void Map::removeEntity(int entity_ID)
{
	removeEntity(findEntity(entity_ID));
}

Entity* Map::findEntity(int entity_ID)
{
	for (unsigned int i = 0; i < entity_list.size(); i++)
	{
		if (entity_list[i].getID() == entity_ID)
		{
			return &entity_list[i];
		}
	}
	return new Entity();
}

int main() {
	return 0;
}