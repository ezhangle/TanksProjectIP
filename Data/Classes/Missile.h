#pragma once

#include "Projectile.h"
#include <SFML\Graphics.hpp>
#include "Tank.h"

class Missile: public Projectile {

public:
					Missile(Tank* parent);
	virtual void	update(sf::Time dt);
	void			setTarget();
	void			rotateMissile(float deltaAsSeconds);
	virtual void    spawnOnHitAnimation();
public:
	Tank*			mTarget;
	float			mAcceleration;
};