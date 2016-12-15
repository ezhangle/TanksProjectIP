#pragma once
#include "SFML\Graphics.hpp"
#include "Map.h"

class Map;

class Entity {
public:
	Entity(sf::Vector2f* pos, sf::Sprite* sprite, Map* map);
	Entity(Map* map);
	
	virtual void									draw(sf::RenderWindow* window);
	virtual void									update(sf::Time dt) = 0;

	sf::Vector2f									getPos() const;
	void											setPos(sf::Vector2f* pos);
public:
	sf::Sprite*										mSprite;
	Map*											mCurrentMap;
};