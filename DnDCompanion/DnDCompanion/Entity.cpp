#include "Entity.h"

Entity::Entity()
{
	type = Null;
}

Entity::Entity(int id, EntityType typ, std::string nm, std::string img, double hp, double sght_rng)
{
	entity_ID = id;
	type = typ;
	name = nm;
	image = img;
	health = hp;
	sight_range = sght_rng;
}

bool Entity::isNull()
{
	return type == Null;
}

int Entity::getID()
{
	return entity_ID;
}

int Entity::getX()
{
	return x_pos;
}

int Entity::getY()
{
	return y_pos;
}

EntityType Entity::getType()
{
	return type;
}

std::string Entity::getName()
{
	return name;
}

std::string Entity::getImage()
{
	return image;
}

double Entity::getHealth()
{
	return health;
}

double Entity::getSightRange()
{
	return sight_range;
}

void Entity::setPostion(int x, int y)
{
	x_pos = x;
	y_pos = y;
}