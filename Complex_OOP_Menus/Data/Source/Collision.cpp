#include "Collision.h"
#include <cmath>

void Collision::normalize(sf::Vector2f& vec) {
	const float length = sqrt(vec.x * vec.x + vec.y * vec.y);
	if (length == 0)
		return;
	vec.x = vec.x / length;
	vec.y = vec.y / length;
}

float Collision::dotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	return v1.x*v2.x + v1.y*v2.y;
}

float Collision::distance(float firstMin, float firstMax, float secondMin, float secondMax) {
	if (secondMin > firstMax) return secondMin - firstMax;
	else return firstMin - secondMax;
}

void Collision::project(const sf::Vector2f& axis,Rect* rect, float &min, float &max) {
	float dot = dotProduct(axis, rect->vertex[0]);

	min = dot;
	max = dot;

	for (short i = 1; i<4; i++)
	{
		dot = dotProduct(rect->vertex[i], axis);

		if (dot < min)
			min = dot;
		else if (dot > max)
			max = dot;
	}
}

bool Collision::collision(sf::Sprite *s1, sf::Sprite *s2) {
	Rect one;
	Rect two;

	sf::Transform transform = s1->getTransform();
	sf::FloatRect rect = s1->getLocalBounds();

	one.vertex[0] = transform.transformPoint(sf::Vector2f(rect.left, rect.top));
	one.vertex[1] = transform.transformPoint(sf::Vector2f(rect.left + rect.width, rect.top));
	one.vertex[2] = transform.transformPoint(sf::Vector2f(rect.left + rect.width, rect.top + rect.height));
	one.vertex[3] = transform.transformPoint(sf::Vector2f(rect.left, rect.top + rect.height));

	transform = s2->getTransform();
	rect = s2->getLocalBounds();

	two.vertex[0] = transform.transformPoint(sf::Vector2f(rect.left, rect.top));
	two.vertex[1] = transform.transformPoint(sf::Vector2f(rect.left + rect.width, rect.top));
	two.vertex[2] = transform.transformPoint(sf::Vector2f(rect.left + rect.width, rect.top + rect.height));
	two.vertex[3] = transform.transformPoint(sf::Vector2f(rect.left, rect.top + rect.height));

	sf::Vector2f axis;
	float minA;
	float minB;
	float maxA;
	float maxB;


	// Test one
	axis.x = one.vertex[1].x - one.vertex[0].x;
	axis.y = one.vertex[1].y - one.vertex[0].y;
	normalize(axis);

	project(axis, &one, minA, maxA);
	project(axis, &two, minB, maxB);

	if (distance(minA, maxA, minB, maxB)>0.f)
		return false;


	// Test two
	axis.x = one.vertex[3].x - one.vertex[0].x;
	axis.y = one.vertex[3].y - one.vertex[0].y;
	normalize(axis);

	project(axis, &one, minA, maxA);
	project(axis, &two, minB, maxB);

	if (distance(minA, maxA, minB, maxB)>0.f)
		return false;


	// Test three
	axis.x = two.vertex[1].x - two.vertex[0].x;
	axis.y = two.vertex[1].y - two.vertex[0].y;
	normalize(axis);

	project(axis, &one, minA, maxA);
	project(axis, &two, minB, maxB);

	if (distance(minA, maxA, minB, maxB)>0.f)
		return false;


	// Test four
	axis.x = two.vertex[3].x - two.vertex[0].x;
	axis.y = two.vertex[3].y - two.vertex[0].y;
	normalize(axis);

	project(axis, &one, minA, maxA);
	project(axis, &two, minB, maxB);

	if (distance(minA, maxA, minB, maxB)>0.f)
		return false;

	return true;
}