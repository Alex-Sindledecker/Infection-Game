#include "Entity.h"

Entity::Entity()
{
}

Entity::Entity(std::string textureSource, float x, float y)
{
	if (!texture.loadFromFile(textureSource)) {
		print("Failed to load texture: " + textureSource + "!");
	}
	entity.setTexture(texture);
	entity.setPosition(x, y);
	border.setSize(sf::Vector2f(entity.getGlobalBounds().width, entity.getGlobalBounds().height));
	border.setPosition(x, y);
	border.setFillColor(sf::Color(0, 0, 0, 0));
}

Entity::Entity(std::string textureSource, float x, float y, sf::Vector2f origin)
{
	if (!texture.loadFromFile(textureSource)) {
		print("Failed to load texture: " + textureSource + "!");
	}
	entity.setTexture(texture);
	if (origin == CENTER) {
		entity.setOrigin(sf::Vector2f(entity.getGlobalBounds().width / 2, entity.getGlobalBounds().height / 2));
		border.setOrigin(sf::Vector2f(entity.getGlobalBounds().width / 2, entity.getGlobalBounds().height / 2));
	}
	else {
		entity.setOrigin(origin);
		border.setOrigin(origin);
	}
	entity.setPosition(x, y);
	border.setSize(sf::Vector2f(entity.getGlobalBounds().width, entity.getGlobalBounds().height));
	border.setPosition(x, y);
	border.setFillColor(sf::Color(0, 0, 0, 0));
	
}

Entity::~Entity()
{
}

void Entity::draw(sf::RenderWindow& window)
{
	window.draw(entity);
	if (usingBorder) {
		window.draw(border);
	}
}

void Entity::setPosition(sf::Vector2f pos)
{
	entity.setPosition(pos);
	border.setPosition(pos);
}

void Entity::setBorder(sf::Color color, int thickness)
{
	border.setOutlineColor(color);
	border.setOutlineThickness(thickness);
}

void Entity::setOrigin(sf::Vector2f pos)
{
	entity.setOrigin(pos);
	border.setOrigin(pos);
}

void Entity::setTextureRect(float x, float y, float width, float height)
{
	entity.setTextureRect(sf::IntRect(x, y, width, height));
}

void Entity::setRotation(float theta)
{
	entity.setRotation(theta);
	border.setRotation(theta);
}

void Entity::translate(sf::Vector2f translation)
{
	entity.move(translation);
}

void Entity::rotate(float theta)
{
	entity.rotate(theta);
	border.rotate(theta);
}

void Entity::scale(sf::Vector2f scale)
{
	entity.scale(scale);
	border.scale(scale);
}

void Entity::useBorder(bool usage)
{
	usingBorder = usage;
}

sf::Vector2f Entity::getPosition()
{
	return entity.getPosition();
}

sf::FloatRect Entity::getGlobalBounds()
{
	return entity.getGlobalBounds();
}

float Entity::getRotation()
{
	return entity.getRotation();
}

sf::Sprite Entity::getSprite()
{
	return entity;
}

bool Entity::isCollidingWith(Entity& entity)
{
	return entity.getGlobalBounds().intersects(getGlobalBounds());
}
