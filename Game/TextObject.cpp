#include "TextObject.h"

TextObject::TextObject()
{
}

TextObject::TextObject(std::string text, float x, float y, int size, sf::Color color)
{
	if (!font.loadFromFile("fonts/arial.ttf")) {
		print("Failed to load font: arial.ttf!");
		pause();
	}
	this->text.setFont(font);
	this->text.setString(text);
	this->text.setCharacterSize(size);
	this->text.setPosition((int)x, (int)y);
	this->text.setFillColor(color);
}

TextObject::TextObject(std::string textureSource, float x, float y)
{
	if (!texture.loadFromFile(textureSource)) {
		print("Failed to load texture: " + textureSource + "!");
	}
	sprite_text.setTexture(texture);
	sprite_text.setPosition(x, y);
	isUsingSprite = true;
}

void TextObject::setStyles(bool bold, bool italic)
{
	if (bold) {
		text.setStyle(sf::Text::Bold);
	}
	if (italic) {
		text.setStyle(sf::Text::Italic);
	}
	if (!(bold && italic)) {
		text.setStyle(sf::Text::Regular);
	}
}

void TextObject::setFont(std::string font)
{
	if (!this->font.loadFromFile(font)) {
		print("Failed to load font: " + font + "!");
		return;
	}
	text.setFont(this->font);
}

void TextObject::draw(sf::RenderWindow& window)
{
	if (isUsingSprite) {
		window.draw(sprite_text);
	}else{
		window.draw(text); 
	}
}

void TextObject::setPos(float x, float y) {
	text.setPosition(x, y);
}

void TextObject::setText(std::string text)
{
	this->text.setString(text);
}

void TextObject::setFillColor(sf::Color color)
{
	this->text.setFillColor(color);
}

void TextObject::setOutlineColor(sf::Color color, int borderThickness)
{
	this->text.setOutlineThickness(borderThickness);
	this->text.setOutlineColor(color);
}

void TextObject::setSize(int size)
{
	this->text.setCharacterSize(size);
}

void TextObject::printDistanceToCenter()
{
	sf::FloatRect bounds = getGlobalBounds();
	float left = bounds.left;
	float right = W_WIDTH - (bounds.left + bounds.width);
	print(right - left);
}

sf::FloatRect TextObject::getGlobalBounds()
{
	return text.getGlobalBounds();
}

TextObject::~TextObject()
{
}
