#pragma once
#include "AI.h"
#include <SFML/Graphics.hpp>

class AI_Easy: public AI {
public:
					AI_Easy(sf::Sprite* base, sf::Sprite* top, sf::Vector2f* pos, sf::Vector2f* vel, float health, float damage, size_t team);
	virtual void	update(sf::Time dt);
};