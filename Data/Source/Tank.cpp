#include "Tank.h"

Tank::Tank(sf::Sprite* base, sf::Sprite* top, sf::Vector2f* pos, sf::Vector2f* vel, float health, float damage, Map* map):
Entity(map),
mBase(base),
mTop(top),
mVelocity(vel),
mHealth(health),
mDamage(damage)
{
	sf::Vector2f topPos = top->getPosition();
	top->setOrigin((float)top->getTexture()->getSize().x / 2, (float)top->getTexture()->getSize().y / 2);
	top->setPosition(pos->x + (float)base->getTexture()->getSize().x / 2, pos->y + (float)base->getTexture()->getSize().y / 2);

	base->setPosition(pos->x, pos->y);
}

void Tank::draw(sf::RenderWindow* window) {
	window->draw(*mBase);
	window->draw(*mTop);
}

void Tank::update(sf::Time dt) {
	rotateTurret(dt.asSeconds() * 50.f);
}

void Tank::rotateTurret(float modifier) {
	mTop->setRotation(mTop->getRotation() + modifier);
}