#pragma once

#include "Entity.h"

#define ROTATE 360
#define TRANSLATE 4
#define SCALE 2

class Player : public Entity
{
public:
	Player();
	Player(std::string textureSource, float x, float y);
	Player(std::string textureSource, float x, float y, sf::Vector2f origin);
	~Player();

	void damage(float value);
	void slow(float value);
	void resetSpeed();
	void setHealth(float value);

	float getCurrentHealth();

	inline void addEventListener(sf::Keyboard::Key key, int action, float parameter);
	template<class N>
	inline void addEventListener(sf::Keyboard::Key key, int action, N parameter);

private:
	void init();

private:
	float currentHealth = 100.f;
	float speed = 1.f;
};

inline void Player::addEventListener(sf::Keyboard::Key key, int action, float parameter)
{
	if (sf::Keyboard::isKeyPressed(key)) {
		if (action == ROTATE) {
			rotate(parameter);
		}
	}
}

template<class N>
inline void Player::addEventListener(sf::Keyboard::Key key, int action, N parameter)
{
	if (sf::Keyboard::isKeyPressed(key)) {
		if (action == TRANSLATE) {
			translate(parameter * speed);
		}
		if (action == SCALE) {
			scale(parameter);
		}
	}
}
