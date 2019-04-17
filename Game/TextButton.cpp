#include "TextButton.h"

TextButton::TextButton()
{
	
}

TextButton::TextButton(std::string text, float x, float y, int size, sf::Color originalColor, sf::Color hoverColor) :
	TextObject(text, x, y, size, originalColor)
{
	this->originalColor = originalColor;
	this->hoverColor = hoverColor;
}

TextButton::~TextButton()
{
}

bool TextButton::isClicked(sf::Event& evt, sf::RenderWindow& window) {
	sf::FloatRect border = getGlobalBounds();
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	bool onText = false;
	if (mousePos.x > border.left && mousePos.x < (border.left + border.width)) {
		if (mousePos.y > border.top && mousePos.y < (border.top + border.height)) {
			onText = true;
		}
		else {
			onText = false;
		}
	}
	else {
		onText = false;
	}

	if (onText) {
		setFillColor(hoverColor);
		if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Left) {
			return true;
		}
	}
	else {
		setFillColor(originalColor);
	}
	return false;
}
