#pragma once
#include <list>
#include <SFML\System\Time.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include "Entity.h"

class Entity;

class Tile {
public:
	Tile();
	void					update(sf::Time dt);
	void					draw(sf::RenderWindow* window);
	void					insertEntity(Entity* entity);
	void					eraseEntity(Entity* entity);
	void					eraseEntity(std::list<Entity*>::iterator it);
public:
	std::list<Entity*>		mEntities;
};