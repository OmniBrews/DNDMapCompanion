#pragma once
#include <string>
#include <tuple>

enum EntityType { Tank, Melee, Ranged, Magic, Healer, Mob, Boss, Neutral, Null };

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
	void setPostion(int x, int y);
};
