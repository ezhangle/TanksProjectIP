#pragma once
#include "Tank.h"
#include <vector>

class Player : public Tank {
public:
	Player(sf::Sprite* base, sf::Sprite* top, sf::Vector2f* pos, sf::Vector2f* vel, float health, float damage, std::vector<sf::Keyboard::Key> keys);

	void	handleInput(sf::Time dt);
	void	update(sf::Time dt);
public:
	std::vector<sf::Keyboard::Key> mKeys;
};