#include "Player.h"

Player::Player() : Entity()
{

}

Player::Player(std::string textureSource, float x, float y) : Entity(textureSource, x, y)
{
	init();
}

Player::Player(std::string textureSource, float x, float y, sf::Vector2f origin) : Entity(textureSource, x, y, origin)
{
	init();
}

Player::~Player()
{
}

void Player::damage(float value)
{
	currentHealth -= value;
	if (currentHealth < 0) {
		currentHealth = 0;
	}
}

void Player::slow(float value)
{
	speed -= value;
	if (speed < 0.2f) {
		speed = 0.2f;
	}
}

void Player::resetSpeed()
{
	speed = 1.f;
}

void Player::setHealth(float value)
{
	if (value > 100.f) {
		value = 100.f;
	}
	currentHealth = value;
}

void Player::init() {
	sf::Texture texture;
	if (!texture.loadFromFile("img/HealthBar.png")) {
		print("Failed to load texture: HealthBar.png!");
	}
}

float Player::getCurrentHealth()
{
	return currentHealth;
}
