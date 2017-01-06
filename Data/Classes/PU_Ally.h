#pragma once
#include <SFML/Graphics.hpp>
#include "PowerUp.h"
#include "Tank.h"

class PU_Ally : public PowerUp {
public:
	PU_Ally(sf::Vector2f* position);

	virtual void onTrigger(Tank* target);
	virtual void checkForDuplicate() {};
};