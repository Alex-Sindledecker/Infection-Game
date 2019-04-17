#pragma once

#include "Globals.h"

class NavigationButton
{
public:
	NavigationButton();
	NavigationButton(std::string textureSource, std::string hoverTextureSource, float x, float y, sf::Vector2f scale);
	~NavigationButton();

	void draw(sf::RenderWindow& window);
	bool isClicked(sf::Event& evt, sf::RenderWindow& window);

private:
	sf::Texture hoverTexture;
	sf::Texture idleTexture;
	sf::Sprite button;
};