#pragma once

#include "Globals.h"
#include <limits.h>

#define CENTER sf::Vector2f(INT_MAX, INT_MAX)

class Entity
{
public:
	Entity();
	Entity(std::string textureSource, float x, float y);
	Entity(std::string textureSource, float x, float y, sf::Vector2f origin);
	~Entity();

	void draw(sf::RenderWindow& window);
	void setPosition(sf::Vector2f pos);
	void setBorder(sf::Color color, int thickness);
	void setOrigin(sf::Vector2f pos);
	void setTextureRect(float x, float y, float width, float height);
	void setRotation(float theta);
	void translate(sf::Vector2f translation);
	void rotate(float theta);
	void scale(sf::Vector2f scale);
	void useBorder(bool usage);

	sf::Vector2f getPosition();
	sf::FloatRect getGlobalBounds();
	float getRotation();
	sf::Sprite getSprite();
	bool isCollidingWith(Entity& entity);

protected:
	sf::Texture texture;
	sf::Sprite entity;
	sf::RectangleShape border;
	bool usingBorder = false;
};

