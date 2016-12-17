#include "Tank.h"
#include "Game.h"
#include <iostream>
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

void Tank::move(Command dir, sf::Time dt) {
	sf::Vector2f newPos(mBase->getPosition());
	int tileX = (int)newPos.x / 64;
	int tileY = (int)newPos.y / 64;
	int tileX2 = tileX;
	int tileY2 = tileY;

	if (dir == Command::RIGHT) {
		newPos.x += dt.asSeconds() * mVelocity->x;
		tileX2 = (int)newPos.x / 64;

		mBase->setRotation(90.f);
	}

	if (dir == Command::UP) {
		newPos.y -= dt.asSeconds() * mVelocity->y;
		tileY2 = (int)newPos.y / 64;

		mBase->setRotation(0.f);
	}

	if (dir == Command::DOWN) {
		newPos.y += dt.asSeconds() * mVelocity->y;
		tileY2 = (int)newPos.y / 64;

		mBase->setRotation(180.f);
	}

	if (dir == Command::LEFT) {
		newPos.x -= dt.asSeconds() * mVelocity->x;
		tileX2 = (int)newPos.x / 64;
		
		mBase->setRotation(-90.f);
	}

	if (dir == Command::H_DOWN_LEFT) {
		newPos.x -= dt.asSeconds() * mVelocity->x;
		newPos.y += dt.asSeconds() * mVelocity->y;
		tileX2 = tileX2 = (int)newPos.x / 64;
		tileY2 = tileY2 = (int)newPos.y / 64;

		mBase->setRotation(-135.f);
	}

	if (dir == Command::H_DOWN_RIGHT) {
		newPos.x += dt.asSeconds() * mVelocity->x;
		newPos.y += dt.asSeconds() * mVelocity->y;
		tileX2 = tileX2 = (int)newPos.x / 64;
		tileY2 = tileY2 = (int)newPos.y / 64;

		mBase->setRotation(135.f);
	}

	if (dir == Command::H_UP_LEFT) {
		newPos.x -= dt.asSeconds() * mVelocity->x;
		newPos.y -= dt.asSeconds() * mVelocity->y;
		tileX2 = tileX2 = (int)newPos.x / 64;
		tileY2 = tileY2 = (int)newPos.y / 64;

		mBase->setRotation(-45.f);
	}

	if (dir == Command::H_UP_RIGHT) {
		newPos.x += dt.asSeconds() * mVelocity->x;
		newPos.y -= dt.asSeconds() * mVelocity->y;
		tileX2 = tileX2 = (int)newPos.x / 64;
		tileY2 = tileY2 = (int)newPos.y / 64;

		mBase->setRotation(45.f);
	}

	if (tileX != tileX2 || tileY2 != tileY) {
		mCurrentMap->mTiles[(int)Map::Priority::PLAYER][tileX2][tileY2].insertEntity(this);
		mCurrentMap->mTiles[(int)Map::Priority::PLAYER][tileX][tileY].eraseEntity(this);
	}
	
	mBase->setPosition(newPos);
	mTop->setPosition(newPos);

}