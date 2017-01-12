#pragma once
#include <SFML/Graphics.hpp>
#include "PowerUp.h"
#include "Animation.h"

class PU_Speed : public PowerUp {
public:
	PU_Speed(sf::Vector2f* position);
	
	virtual void update(sf::Time dt);
	virtual void onTrigger(Tank* target);
	virtual void onDurationEnd();
	virtual void checkForDuplicate();

public:
	float	   mMovementSpeedMultiplier;
	sf::Clock  mAnimationSpawnClock;
};

