#pragma once
#include "AI.h"

class AI_Medium : public AI {
public:
					AI_Medium(sf::Sprite* base, sf::Sprite* top, sf::Vector2f* pos, sf::Vector2f* vel, float health, float damage, size_t team);
	virtual void	update(sf::Time dt);
};