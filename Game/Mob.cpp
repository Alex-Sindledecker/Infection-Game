#include "Mob.h"

Mob::Mob()
{

}

Mob::Mob(std::string textureSource, float x, float y) : Entity(textureSource, x, y)
{

}

Mob::Mob(std::string textureSource, float x, float y, sf::Vector2f origin) : Entity(textureSource, x, y, origin)
{

}

Mob::~Mob()
{
}

void Mob::setEffects(float damage, float speedLoss)
{
	this->damage = damage;
	this->speedLoss = speedLoss;
}

void Mob::applyEffects(Player& player)
{
	player.damage(damage);
	player.slow(speedLoss);
}

void Mob::follow(Player& player, float deltaTime, float speed, bool followCenter)
{
	if (!followCenter) {
		float p_x = player.getPosition().x;
		float p_y = player.getPosition().y;
		float m_x = getPosition().x;
		float m_y = getPosition().y;

		float d_x = m_x - p_x;
		float d_y = m_y - p_y;
		float angleToPlayer = atan2(d_y, d_x);

		translate(sf::Vector2f(-cos(angleToPlayer) * speed * deltaTime, -sin(angleToPlayer) * speed * deltaTime));
	}
	else {
		float p_x = player.getPosition().x - player.getGlobalBounds().width / 2;
		float p_y = player.getPosition().y - player.getGlobalBounds().height / 2;
		float m_x = getPosition().x;
		float m_y = getPosition().y;

		float d_x = m_x - p_x;
		float d_y = m_y - p_y;
		float angleToPlayer = atan2(d_y, d_x);

		translate(sf::Vector2f(-cos(angleToPlayer) * speed * deltaTime, -sin(angleToPlayer) * speed * deltaTime));
	}
}
