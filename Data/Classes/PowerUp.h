#pragma once
#include <SFML\Graphics.hpp>
#include "Entity.h"
#include "Tank.h"

class PowerUp : public Entity {
public:
	PowerUp(sf::Vector2f* position, sf::Sprite* sprite);

	virtual void update(sf::Time dt);
	virtual void onTrigger(Tank* target);
	virtual void onDurationEnd() = 0;

public:
	float	   mFloatMinimum;
	float	   mFloatMaximum;
	float	   mFloatSpeed;
	float	   mFloatUpwards;

	float	   mDuration;
	sf::Clock* mDurationClock;
	Tank*	   mTarget;
	bool       mIsActive;
};