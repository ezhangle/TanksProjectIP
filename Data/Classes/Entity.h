#pragma once
#include "SFML\Graphics.hpp"

class Entity {
public:
	Entity(sf::Vector2f* pos, sf::Sprite* sprite);
	Entity(sf::Sprite* sprite);
	Entity() {};
	~Entity();
	
	virtual void									draw(sf::RenderWindow* window);
	virtual sf::Sprite*								getCollisionSprite();
	virtual void									update(sf::Time dt) = 0;
	
public:
	sf::Sprite*										mSprite;
	bool											mDelete;
};