#include "Terrain.h"

Terrain::Terrain()
{
	type = Basic;
	elevation = 0;
	custom_image = "";
}

Terrain::Terrain(TerrainType typ, std::string image, int elev)
{
	type = typ;
	custom_image = image;
	elevation = elev;
}

TerrainType Terrain::getType()
{
	return type;
}

std::string Terrain::getImage()
{
	return type != Custom ? "" : custom_image;
}

std::vector<Entity*> Terrain::getEntities()
{
	return entities_in_square;
}

void Terrain::addEntity(Entity * e)
{
	entities_in_square.push_back(e);
}

void Terrain::removeEntitiy(Entity * e)
{
	std::vector<Entity*>::iterator position = entities_in_square.begin();
	while (position != entities_in_square.end() && (*position)->getID() != e->getID())
		position++;
	if (position != entities_in_square.end())
		entities_in_square.erase(position);
}
