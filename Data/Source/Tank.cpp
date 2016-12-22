#include "Tank.h"
#include "Game.h"
#include "Collision.h"
#include "Terrain.h"
#include "Map.h"
#include <iostream>
#include <cmath>
Tank::Tank(sf::Sprite* base, sf::Sprite* top, sf::Vector2f* pos, sf::Vector2f* vel, float health, float damage):
Entity(),
mBase(base),
mTop(top),
mVelocity(vel),
mHealth(health),
mDamage(damage)
{
	sf::Vector2f topPos = top->getPosition();
	top->setOrigin((float)top->getTexture()->getSize().x / 2, (float)top->getTexture()->getSize().y / 2);
	base->setOrigin((float)base->getTexture()->getSize().x / 2, (float)base->getTexture()->getSize().y / 2);
	base->setPosition(pos->x, pos->y);
	top->setPosition(base->getPosition());

	
}

void Tank::draw(sf::RenderWindow* window) {
	window->draw(*mBase);
	window->draw(*mTop);
}

void Tank::update(sf::Time dt) {
	
}

void Tank::rotateTurret(float modifier) {
	mTop->setRotation(mTop->getRotation() + modifier);
}

void Tank::rotateBase(float modifier) {
	mBase->rotate(modifier);

	if (checkCollision())
		mBase->rotate(-modifier);
}
void Tank::MoveX(float inc) {
	sf::Vector2f newPos(mBase->getPosition());
	sf::Vector2f oldPos(newPos);

	newPos.x += sin(mBase->getRotation()*3.14f / 180.f)* inc * mVelocity->x;
	newPos.y -= cos(mBase->getRotation()*3.14f / 180.f)* inc * mVelocity->y;

	mBase->setPosition(newPos);
	mTop->setPosition(newPos);

	if (checkCollision() || checkOutOfBounds()) {
		mBase->setPosition(oldPos);
		mTop->setPosition(oldPos);
	}
}

bool Tank::checkCollision() {
	bool collideSolid = false;
	Collision col;

	Map* map = Game::get()->mMap;

	for (auto it1 = map->mEntities.begin(); it1 != map->mEntities.end(); ++it1) {
		for (auto it2 = (*it1).begin(); it2 != (*it1).end(); ++it2) {
			if ((*it2) != this)
			{
				if (col.collision(mBase, (*it2)->getSprite())) {
					collideSolid = true;
				}
			}
		}
	}

	return collideSolid;
}

bool Tank::checkOutOfBounds() {
	sf::Vector2f pos = mBase->getPosition();

	if (pos.x < 64.f || pos.x > (float)Game::get()->mWidth - 64.f ||
		pos.y < 64.f || pos.y > (float)Game::get()->mHeight - 64.f)
		return true;

	return false;
}

sf::Sprite* Tank::getSprite() {
	return mBase;
}