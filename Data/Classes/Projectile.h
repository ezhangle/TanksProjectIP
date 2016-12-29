#pragma once
#include "Entity.h"
#include "Animation.h"
#include "Collision.h"
#include "Tank.h"
#include <SFML/Graphics.hpp>

class Projectile : public Entity {
public:
	Projectile(sf::Sprite* sprite, sf::Vector2f* position, sf::Vector2f* velocity, float damage, Tank* parent);
	~Projectile();

	virtual void update(sf::Time dt);
	bool		 outOfBounds();
	bool		 checkCollision();
public:
	Tank*			mParent;
	sf::Vector2f*	mVelocity;
	float			mDamage;
	Collision		SAT;
	
};