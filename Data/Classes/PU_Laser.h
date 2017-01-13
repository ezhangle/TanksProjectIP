#pragma once
#include "PowerUp.h"

#include <SFML/Graphics.hpp>

class PU_Laser: public PowerUp {

public:
	PU_Laser(sf::Vector2f* position);
	
	virtual void onTrigger(Tank* target);
	virtual void onDurationEnd();
	virtual void checkForDuplicate();
};