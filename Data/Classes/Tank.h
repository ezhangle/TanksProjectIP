#pragma once
#include "Entity.h"
#include "Map.h"
#include "Collision.h"
#include <SFML\Graphics.hpp>
#include <SFML\System\Time.hpp>

class Tank: public Entity {
public:
	enum class Command {
		LEFT, RIGHT, UP, DOWN,
		ROT_LEFT, ROT_RIGHT,
		SHOOT,

		NUMBER,
	};
public:
							Tank(sf::Sprite* base, sf::Sprite* top, sf::Vector2f* pos, sf::Vector2f* vel, float health, float damage, size_t team);
	void					update(sf::Time dt);
	void					draw(sf::RenderWindow* window);

	void					rotateTurret(float modifier);
	void					rotateBase(float modifier);
	bool					MoveX(float inc);
	void					shoot();
	void					setPosition(sf::Vector2f& newPos);

	bool					checkCollision();
	bool					checkOutOfBounds();
	virtual sf::Sprite*		getCollisionSprite();

public:
	size_t					mTeam;
	sf::Sprite*				mTop;
	sf::Sprite*				mBase;
	sf::Sprite				mHpBarBase;
	sf::Sprite				mHpBarTop;

	sf::Vector2f*			mVelocity;
	float					mAcceleration;
	float					mMaxAcceleration;
	sf::Clock				mMovingStateClock;
	size_t					mMovingState;
	sf::Vector2f			mLastPoint;

	sf::Clock				mHitCooldownClock;
	float					mHitCooldown;
	Collision				SAT;
	
	const float				mMaxHealth;
	float					mHealth;
	float					mDamage;

};