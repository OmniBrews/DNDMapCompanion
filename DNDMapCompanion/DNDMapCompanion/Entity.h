#pragma once
#include <string>
#include <tuple>

enum EntityType { Player, NPC, Object, NullEntity };

class Entity
{
	int entity_ID;
	EntityType type;
	int x_pos, y_pos;
	std::string name;
	std::string image;
	double health;
	double sight_range;

public:
	Entity();
	Entity(int id, EntityType typ, std::string nm, std::string img, double health, double sight_range);
	bool isNull();
	int getID();
	int getX();
	int getY();
	EntityType getType();
	std::string getName();
	std::string getImage();
	double getHealth();
	double getSightRange();
	void setPostiion(int x, int y);
};