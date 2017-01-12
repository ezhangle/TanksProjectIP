#pragma once
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include "Animation.h"
#include "Tank.h"

class LaserBall : public Projectile {
public:
	LaserBall(Tank* parent);
	virtual void update(sf::Time dt);
	virtual void draw(sf::RenderWindow* window);
	virtual void spawnOnHitAnimation();

public:
	float							mLaserRange;
	std::list<sf::VertexArray>		mLasers;
};