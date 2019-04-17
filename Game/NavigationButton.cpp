#include "NavigationButton.h"

NavigationButton::NavigationButton()
{
	
}

NavigationButton::NavigationButton(std::string textureSource, std::string hoverTextureSource, float x, float y, sf::Vector2f scale)
{
	if (!idleTexture.loadFromFile(textureSource)) {
		print("Failed to load texture: " + textureSource + "!");
	}
	if (!hoverTexture.loadFromFile(hoverTextureSource)) {
		print("Failed to load texture: " + hoverTextureSource + "!");
	}
	button.setTexture(idleTexture);
	button.setPosition(x, y);
	button.scale(scale);
}

NavigationButton::~NavigationButton()
{
}

void NavigationButton::draw(sf::RenderWindow & window)
{
	window.draw(button);
}

bool NavigationButton::isClicked(sf::Event & evt, sf::RenderWindow & window)
{
	sf::FloatRect bounds = button.getGlobalBounds();
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	bool hovering = false;
	if (mousePos.x > bounds.left && mousePos.x < bounds.left + bounds.width) {
		if (mousePos.y > bounds.top && mousePos.y < bounds.top + bounds.height) {
			hovering = true; 
		}
		else {
			hovering = false;
		}
	}
	else {
		hovering = false;
	}
	if (hovering) {
		button.setTexture(hoverTexture);
		if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Left) {
			return true;
		}
	}
	else {
		button.setTexture(idleTexture);
	}
	return false;
}
