#include "Player.h"
#include "Game.h"
#include "Animation.h"
#include "Projectile.h"
#include "PU_AttackSpeed.h"
#include <cmath>
#include <iostream>

Player::Player(sf::Sprite* base, sf::Sprite* top, sf::Vector2f* pos, sf::Vector2f* vel, float health, float damage, std::vector<sf::Keyboard::Key> keys, size_t team):
Tank(base, top, pos, vel, health, damage, team),
mKeys(keys){
	
}

void Player::handleInput(sf::Time dt) {

	//cheats
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde))
		changeProjectile(ProjectileType::Basic);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde))
		changeProjectile(ProjectileType::Missile);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde))
		changeProjectile(ProjectileType::LaserBall);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde))
		mHitCooldown = 0.1f;


	//handle input
	if (sf::Keyboard::isKeyPressed(mKeys[(int)Command::SHOOT]))
		shoot();

	if (sf::Keyboard::isKeyPressed(mKeys[(int)Command::UP])) {
		MoveX(dt.asSeconds());
	}
	else if (sf::Keyboard::isKeyPressed(mKeys[(int)Command::DOWN])) {
		MoveX(-dt.asSeconds());
	}
	else {
		mAcceleration -= 8.f;
		if (mAcceleration < 0.f)
			mAcceleration = 0.f;
	}

	if (sf::Keyboard::isKeyPressed(mKeys[(int)Command::LEFT])) {
		rotateBase(-dt.asSeconds());
	}	
	else if (sf::Keyboard::isKeyPressed(mKeys[(int)Command::RIGHT])) {
		rotateBase(dt.asSeconds());
	}	
	
	if (sf::Keyboard::isKeyPressed(mKeys[(int)Command::ROT_LEFT]))
		rotateTurret(-dt.asSeconds());
	if (sf::Keyboard::isKeyPressed(mKeys[(int)Command::ROT_RIGHT]))
		rotateTurret(dt.asSeconds());

}

void Player::update(sf::Time dt) {

	handleInput(dt);
	Tank::update(dt);
}