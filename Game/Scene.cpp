#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::addEntity(Entity* icon)
{
	entitys.push_back(icon);
}

void Scene::addTextObject(TextObject* textObject)
{
	textObjects.push_back(textObject);
}

void Scene::addNavigationButton(NavigationButton* navButton)
{
	navigationButtons.push_back(navButton);
}

void Scene::renderAll(sf::RenderWindow& window)
{
	for (Entity* entity : entitys) {
		entity->draw(window);
	}
	for (TextObject* textObject : textObjects) {
		textObject->draw(window);
	}
	for (NavigationButton* navButton : navigationButtons) {
		navButton->draw(window);
	}
}
