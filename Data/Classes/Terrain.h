#pragma once
#include "Entity.h"
#include "Map.h"
#include <SFML/Graphics.hpp>

class Terrain : public Entity {
public:
							Terrain(sf::Vector2f* pos, sf::Sprite* sprite);
	virtual void			update(sf::Time dt);
};