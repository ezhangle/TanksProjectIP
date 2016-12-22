#pragma once
#include "Entity.h"
#include "Map.h"
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
						Tank(sf::Sprite* base, sf::Sprite* top, sf::Vector2f* pos, sf::Vector2f* vel, float health, float damage);
	void				update(sf::Time dt);
	void				draw(sf::RenderWindow* window);
	void				rotateTurret(float modifier);
	void				rotateBase(float modifier);
	void				MoveX(float inc);
	bool				checkCollision();
	bool				checkOutOfBounds();
	virtual sf::Sprite* getSprite();

public:
	sf::Sprite*			mTop;
	sf::Sprite*			mBase;
	sf::Vector2f*		mVelocity;
	float				mHealth;
	float				mDamage;
};