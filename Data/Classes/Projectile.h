#pragma once
#include "Entity.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>

class Projectile : public Entity {
public:
	Projectile(sf::Sprite* sprite, sf::Vector2f* position, sf::Vector2f* velocity, Animation* onhit, float damage);

	virtual void update(sf::Time dt);
public:
	sf::Vector2f*	mVelocity;
	Animation*		onHitAnim;
	float			mDamage;
	
};