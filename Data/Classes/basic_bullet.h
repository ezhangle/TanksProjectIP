#pragma once

#include "Projectile.h"
#include "Tank.h"

class BasicBullet : public Projectile {

public:
	BasicBullet(Tank* parent);
	virtual void spawnOnHitAnimation();
};