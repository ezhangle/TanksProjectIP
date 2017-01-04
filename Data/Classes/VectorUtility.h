#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

namespace Vector2f {
	float dot(const sf::Vector2f& v1, const sf::Vector2f& v2);
	float length(const sf::Vector2f& vector);
	float distance(const sf::Vector2f& v1, const sf::Vector2f& v2);
	float angle(const sf::Vector2f& v1, const sf::Vector2f& v2);

	sf::Vector2f normalize(const sf::Vector2f& vector);
}