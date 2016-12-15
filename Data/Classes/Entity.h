#pragma once
#include "SFML\Graphics.hpp"

class Entity {
public:
	Entity(sf::Vector2f* pos, sf::Sprite* sprite);
	
	virtual void									draw(sf::RenderWindow* window);
	virtual void									update(sf::Time dt) = 0;

	sf::Vector2f									getPos() const;
	void											setPos(sf::Vector2f* pos);
private:
	sf::Sprite*										mSprite;
};