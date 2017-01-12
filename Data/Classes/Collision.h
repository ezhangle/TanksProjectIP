#pragma once
#include <SFML/Graphics.hpp>

class Collision {
	struct Rect {
		sf::Vector2f vertex[4];
	};
public:
	bool collision(sf::Sprite *s1, sf::Sprite *s2);

private:
	void normalize(sf::Vector2f& vec);
	float dotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2);
	float distance(float firstMin, float firstMax, float secondMin, float secondMax);
	void project(const sf::Vector2f& axis,Rect* rect, float &min, float &max);

};