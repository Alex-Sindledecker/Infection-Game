#pragma once

#include "Globals.h"

class TextObject
{
public:
	TextObject();
	TextObject(std::string text, float x, float y, int size, sf::Color color);
	TextObject(std::string textureSource, float x, float y);
	void setStyles(bool bold, bool italic);
	void setFont(std::string font);
	void draw(sf::RenderWindow& window);
	void setPos(float x, float y);
	void setText(std::string text);
	void setFillColor(sf::Color color);
	void setOutlineColor(sf::Color color, int borderThickness);
	void setSize(int size);
	void printDistanceToCenter();
	sf::FloatRect getGlobalBounds();
	~TextObject();

protected:
	sf::Font font;
	sf::Text text;

private:
	sf::Texture texture;
	sf::Sprite sprite_text;
	bool isUsingSprite = false;
};

