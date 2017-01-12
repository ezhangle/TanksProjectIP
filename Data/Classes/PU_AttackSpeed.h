#pragma once
#include "PowerUp.h"
#include "Tank.h"
#include "Game.h"

class PU_AttackSpeed : public PowerUp {
public:
	PU_AttackSpeed(sf::Vector2f* position);

	virtual void update(sf::Time dt);
	virtual void onTrigger(Tank* target);
	virtual void onDurationEnd();
	virtual void checkForDuplicate();

public:
	float	mAttackSpeedMultiplier;
};

