#pragma once
#include "PowerUp.h"

class PU_HollowProj : public PowerUp {
public:
	PU_HollowProj(sf::Vector2f* position);

	virtual void onTrigger(Tank* target);
	virtual void onDurationEnd();
	virtual void checkForDuplicate();
};