#pragma once
#include "SFML\Graphics.hpp"

class Entity {
public:
	Entity(const sf::Vector2f& pos, sf::Sprite* sprite);
	
	virtual void									draw() = 0;
	virtual void									update() = 0;

	sf::Vector2f									getPos() const;
	void											setPos(const sf::Vector2f &pos);
private:
	sf::Sprite*										mSprite;
};