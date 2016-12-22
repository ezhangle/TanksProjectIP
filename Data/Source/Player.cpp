#include "Player.h"
#include "Game.h"
#include "Animation.h"
#include "Projectile.h"
#include <cmath>

Player::Player(sf::Sprite* base, sf::Sprite* top, sf::Vector2f* pos, sf::Vector2f* vel, float health, float damage, std::vector<sf::Keyboard::Key> keys):
Tank(base, top, pos, vel, health, damage),
mKeys(keys){

}

void Player::handleInput(sf::Time dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		mHealth = 0.f;

	if (sf::Keyboard::isKeyPressed(mKeys[(int)Command::SHOOT]))
		shoot();

	if (sf::Keyboard::isKeyPressed(mKeys[(int)Command::UP])) {
		MoveX(dt.asSeconds());
	}
	else if (sf::Keyboard::isKeyPressed(mKeys[(int)Command::DOWN])) {
		MoveX(-dt.asSeconds());
	}
	if (sf::Keyboard::isKeyPressed(mKeys[(int)Command::LEFT])) {
		rotateBase(dt.asSeconds() * -200);
	}	
	else if (sf::Keyboard::isKeyPressed(mKeys[(int)Command::RIGHT])) {
		rotateBase(dt.asSeconds() * 200.f);
	}	
	
	if (sf::Keyboard::isKeyPressed(mKeys[(int)Command::ROT_LEFT]))
		rotateTurret(-dt.asSeconds() * 200.f);
	if (sf::Keyboard::isKeyPressed(mKeys[(int)Command::ROT_RIGHT]))
		rotateTurret(dt.asSeconds() * 200.f);

	
}

void Player::update(sf::Time dt) {

	handleInput(dt);
	Tank::update(dt);
	
}