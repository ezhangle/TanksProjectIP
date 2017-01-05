#pragma once
#include "Entity.h"
#include "Animation.h"
#include "Collision.h"
#include "Tank.h"
#include <SFML/Graphics.hpp>

class Projectile : public Entity {
public:
	Projectile(sf::Sprite* sprite, Tank* parent);
	~Projectile();

	virtual void update(sf::Time dt);
	bool		 outOfBounds();
	bool		 checkCollision();
	virtual void spawnOnHitAnimation() = 0;
	void		 setHollow();
public:
	Tank*			mParent;
	sf::Vector2f*	mVelocity;
	float			mDamage;
	Collision		SAT;
	
	bool			mHollow;
};