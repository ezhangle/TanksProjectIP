#pragma once
#include "Entity.h"
#include "Map.h"
#include <SFML/Graphics.hpp>

class Terrain : public Entity {
public:
							Terrain(sf::Vector2f* pos, sf::Sprite* sprite, bool solid, Map* map);
	virtual void			update(sf::Time dt);
public:
	bool					bSolid;
};