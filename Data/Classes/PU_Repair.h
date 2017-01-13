#pragma once
#include <SFML\Graphics.hpp>
#include "PowerUp.h"

class PU_Repair : public PowerUp {
public:
	PU_Repair(sf::Vector2f* position);
	virtual void update(sf::Time dt);
	virtual void onTrigger(Tank* target);
	virtual void checkForDuplicate();

public:
	float		mHpPerSecond;
};