#pragma once
#include "SFML\Graphics.hpp"

class Entity {
public:
	Entity(sf::Vector2f* pos, sf::Sprite* sprite);
	Entity() {};
	
	virtual void									draw(sf::RenderWindow* window);
	virtual sf::Sprite*								getSprite();
	virtual void									update(sf::Time dt) = 0;
	
	sf::Vector2f									getPos() const;
	void											setPos(sf::Vector2f* pos);
public:
	sf::Sprite*										mSprite;
};