#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>

class Terrain : public Entity {
public:
							Terrain(sf::Vector2f* pos, sf::Sprite* sprite, bool solid);
	virtual void			update(sf::Time dt);
private:
	bool					bSolid;
};