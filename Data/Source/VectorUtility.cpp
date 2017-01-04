#include "VectorUtility.h"

float Vector2f::dot(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	return (v1.x*v2.x + v1.y*v2.y);
}
float Vector2f::length(const sf::Vector2f& vector) {
	return (sqrt(vector.x*vector.x + vector.y*vector.y));
}

sf::Vector2f Vector2f::normalize(const sf::Vector2f& vector) {
	sf::Vector2f newVec;
	float magn = length(vector);

	newVec.x = vector.x / magn;
	newVec.y = vector.y / magn;

	return newVec;
}

float Vector2f::distance(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	return (sqrt((v1.x - v2.x)*(v1.x - v2.x) + (v1.y - v2.y)*(v1.y - v2.y)));
}

float Vector2f::angle(const sf::Vector2f& v1, const sf::Vector2f& v2) {
	return acos(dot(v1, v2) / (length(v1) * length(v2))) * 180.f / 3.14f;
}