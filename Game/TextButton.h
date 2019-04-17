#pragma once
#include "TextObject.h"
class TextButton : public TextObject
{
public:
	TextButton();
	TextButton(std::string text, float x, float y, int size, sf::Color originalColor, sf::Color hoverColor);
	~TextButton();

	bool isClicked(sf::Event& evt, sf::RenderWindow& window);

private:
	sf::Color originalColor;
	sf::Color hoverColor;
};