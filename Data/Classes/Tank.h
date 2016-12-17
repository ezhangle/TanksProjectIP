#pragma once
#include "Entity.h"
#include "Map.h"
#include <SFML\Graphics.hpp>
#include <SFML\System\Time.hpp>

class Tank: public Entity {
public:
	enum class Command {
		LEFT, RIGHT, UP, DOWN,

		NUMBER,

		H_UP_LEFT, H_UP_RIGHT, H_DOWN_LEFT, H_DOWN_RIGHT
	};
public:
						Tank(sf::Sprite* base, sf::Sprite* top, sf::Vector2f* pos, sf::Vector2f* vel, float health, float damage, Map* map);
	void				update(sf::Time dt);
	void				draw(sf::RenderWindow* window);
	void				rotateTurret(float modifier);
	void				move(Command dir, sf::Time dt);

public:
	sf::Sprite*			mTop;
	sf::Sprite*			mBase;
	sf::Vector2f*		mVelocity;
	float				mHealth;
	float				mDamage;
};