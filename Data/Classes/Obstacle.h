#pragma once
#include "Entity.h"
#include "Map.h"
#include <SFML/Graphics.hpp>

class Obstacle : public Entity {
public:
							Obstacle(sf::Vector2f* pos, sf::Sprite* sprite);
	virtual void			update(sf::Time dt);
};