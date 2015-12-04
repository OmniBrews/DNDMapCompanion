#include "Map.h"



Map::Map(int x, int y)
{
	x_size = x;
	y_size = y;
	for (int i = 0; i < x_size; i++) 
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

Terrain Map::terrainAtSquare(int x, int y)
{
	return terrain_map[x][y];
}

TerrainType Map::terrainTypeAtSquare(int x, int y)
{
	return terrain_map[x][y].getType();
}

void Map::updateTerrainAtSquare(TerrainType t, int x, int y){
	terrain_map[x][y].updateTerrainType(t);
}

void Map::addEntity(Entity e)
{
	entity_list.push_back(e);
	terrain_map[e.getX()][e.getY()].addEntity(findEntity(e.getID()));
}

void Map::createEntity(int entity_ID, EntityType type, int x, int y, std::string name, std::string image, double health, double sight_range)
{
	Entity *temp = new Entity(entity_ID, type, name, image, health, sight_range);
	temp->setPostion(x, y);
	entity_list.push_back(*temp);
	terrain_map[x][y].addEntity(temp);
}

void Map::moveEntity(int entity_ID, int x, int y)
{
	Entity *temp = findEntity(entity_ID);
	terrain_map[temp->getX()][temp->getY()].removeEntity(temp);
	temp->setPostion(x, y);
	terrain_map[x][y].addEntity(temp);
}

void Map::removeEntity(Entity* entity)
{
	if (entity->isNull())
	{
		return;
	}

	terrain_map[entity->getX()][entity->getY()].removeEntity(entity);
	
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


void Map::saveToFile(std::string fileName)
{
	std::ofstream saveFile;
	saveFile.open(fileName);
	saveFile << getMapWidth() << " " << getMapHeight() << "\n";
	saveFile << "Entities\n";
	for (int i = 0; i < entity_list.size(); i++)
	{
		saveFile << entity_list[i].getID() << " ";
		saveFile << entity_list[i].getType() << " ";
		saveFile << entity_list[i].getX() << " ";
		saveFile << entity_list[i].getY() << " ";
		saveFile << entity_list[i].getHealth() << " ";
		saveFile << entity_list[i].getSightRange() << " ";
		saveFile << entity_list[i].getName() << "\n";
	}
	saveFile << "Terrain\n";
	for (int x = 0; x < getMapWidth(); x++)
	{
		for (int y = 0; y < getMapHeight(); y++)
		{
			saveFile << terrainAtSquare(x, y).getType();
			if (!terrainAtSquare(x, y).getEntities().empty())
			{
				std::vector<Entity *> temp = terrainAtSquare(x, y).getEntities();
				saveFile << " " << terrainAtSquare(x, y).getEntities()[0]->getID();
				for (int i = 1; i < terrainAtSquare(x, y).getEntities().size(); i++)
				{
					saveFile << " " << terrainAtSquare(x, y).getEntities()[i]->getID();
				}
			}
			saveFile << "\n";
		}
	}
	saveFile.close();
}

void Map::loadFromFile(std::string fileName)
{
	std::ifstream loadFile;
	loadFile.open(fileName.c_str());
	entity_list.clear();
	terrain_map.clear();
	try
	{
		std::string line;
		std::getline(loadFile, line);
		std::stringstream sss(line);
		sss >> x_size >> y_size;

		for (int i = 0; i < x_size; i++)
		{
			std::vector<Terrain> tempVector;
			for (int j = 0; j < y_size; j++)
			{
				tempVector.push_back(Terrain());
			}
			terrain_map.push_back(tempVector);
		}

		std::getline(loadFile, line);
		std::getline(loadFile, line);
		while (line.compare("Terrain"))
		{
			int entity_ID, type, x_pos, y_pos;
			double health;
			double sight_range;
			std::string name = "Player";
			std::stringstream ss(line);
			ss >> entity_ID;
			ss >> type;
			ss >> x_pos;
			ss >> y_pos;
			ss >> health;
			ss >> sight_range;
			//std::getline(ss, name);
			Entity *temp = new Entity(entity_ID, (EntityType)type, name, "", health, sight_range);
			temp->setPostion(x_pos, y_pos);
			entity_list.push_back(*temp);
			terrain_map[x_pos][y_pos].addEntity(temp);
			std::getline(loadFile, line);
		}

		for (int i = 0; i < x_size; i++)
		{
			for (int j = 0; j < y_size; j++)
			{
				std::getline(loadFile, line);
				std::stringstream ss(line);
				int type;
				ss >> type;
				terrain_map[i][j].updateTerrainType((TerrainType)type);
				/*while (!ss.eof())
				{
					int id;
					ss >> id;
					terrain_map[i][j].addEntity(findEntity(id));
				}*/
			}
		}
	}
	catch (int e)
	{

	}
}