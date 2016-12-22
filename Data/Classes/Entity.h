#pragma once
#include "SFML\Graphics.hpp"

class Entity {
public:
	Entity(sf::Vector2f* pos, sf::Sprite* sprite);
	Entity() {};
	~Entity();
	
	virtual void									draw(sf::RenderWindow* window);
	virtual sf::Sprite*								getSprite();
	virtual void									update(sf::Time dt) = 0;
	

	void											selfDestruct();
	sf::Vector2f									getPos() const;
	void											setPos(sf::Vector2f* pos);
public:
	sf::Sprite*										mSprite;
};