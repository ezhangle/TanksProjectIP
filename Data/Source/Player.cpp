#include "Player.h"

Player::Player(sf::Sprite* base, sf::Sprite* top, sf::Vector2f* pos, sf::Vector2f* vel, float health, float damage, Map* map, std::vector<sf::Keyboard::Key> keys):
Tank(base, top, pos, vel, health, damage, map),
mKeys(keys){

}

void Player::handleInput(sf::Time dt) {
	if (sf::Keyboard::isKeyPressed(mKeys[(int)Command::UP])) {
		if (sf::Keyboard::isKeyPressed(mKeys[(int)Command::LEFT]))
			move(Command::H_UP_LEFT, dt);
		else if (sf::Keyboard::isKeyPressed(mKeys[(int)Command::RIGHT]))
			move(Command::H_UP_RIGHT, dt);
		else
			move(Command::UP, dt);
	}
	else if (sf::Keyboard::isKeyPressed(mKeys[(int)Command::DOWN])) {
		if (sf::Keyboard::isKeyPressed(mKeys[(int)Command::LEFT]))
			move(Command::H_DOWN_LEFT, dt);
		else if (sf::Keyboard::isKeyPressed(mKeys[(int)Command::RIGHT]))
			move(Command::H_DOWN_RIGHT, dt);
		else
			move(Command::DOWN, dt);
	}
	else if (sf::Keyboard::isKeyPressed(mKeys[(int)Command::LEFT])) {
		move(Command::LEFT, dt);
	}	
	else if (sf::Keyboard::isKeyPressed(mKeys[(int)Command::RIGHT])) {
		move(Command::RIGHT, dt);
	}	
	
		


}

void Player::update(sf::Time dt) {
	handleInput(dt);
}