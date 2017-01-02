#pragma once
#include "PowerUp.h"
#include "Tank.h"

class PU_AttackSpeed : public PowerUp {
public:
	PU_AttackSpeed(sf::Vector2f* position, sf::Sprite* sprite);

	virtual void update(sf::Time dt);
	virtual void onTrigger(Tank* target);
	virtual void onDurationEnd();

public:
	float	mAttackSpeedMultiplier;
};