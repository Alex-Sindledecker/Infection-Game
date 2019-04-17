#pragma once

#include "Entity.h"
#include "Player.h"
#include "Globals.h"
#include <math.h>

class Mob : public Entity
{
public:
	Mob();
	Mob(std::string textureSource, float x, float y);
	Mob(std::string textureSource, float x, float y, sf::Vector2f origin);
	~Mob();

	void setEffects(float damage, float speedLoss);
	void applyEffects(Player& player);
	void follow(Player& player, float deltaTime, float speed, bool followCenter);

private:
	float damage;
	float speedLoss;
};

