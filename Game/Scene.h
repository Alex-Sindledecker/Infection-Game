#pragma once

#include "Globals.h"
#include "TextObject.h"
#include "TextButton.h"
#include "NavigationButton.h"
#include "Entity.h"

class Scene
{
public:
	Scene();
	~Scene();

	void addEntity(Entity* icon);
	void addTextObject(TextObject* textObject);
	void addNavigationButton(NavigationButton* navButton);
	void renderAll(sf::RenderWindow& window);

private:
	std::vector<Entity*> entitys;
	std::vector<TextObject*> textObjects;
	std::vector<NavigationButton*> navigationButtons;
};

