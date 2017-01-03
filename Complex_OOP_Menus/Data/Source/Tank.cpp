#include "Tank.h"
#include "Game.h"
#include "Obstacle.h"
#include "Map.h"
#include "Projectile.h"
#include "Animation.h"

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

	mHitCooldown = 0.2f;
	mHitCooldownClock.restart();

	mAcceleration = 0.f;
	mMaxAcceleration = 60.f;

	
}

void Tank::draw(sf::RenderWindow* window) {
	window->draw(*mBase);
	window->draw(*mTop);
}

void Tank::update(sf::Time dt) {
	if (mHealth <= 0) {
		Game::get()->mMap->mEffects.insert(Game::get()->mMap->mEffects.begin(), new Animation(new sf::Vector2f(mBase->getPosition()), Texture::expl_10_0000, Texture::expl_10_0031, 50, false));
		mDelete = true;
	}

}

void Tank::rotateTurret(float modifier) {
	mTop->setRotation(mTop->getRotation() + 250.f * modifier);
}

void Tank::rotateBase(float modifier) {
	mBase->rotate(250.f * modifier);
}

bool Tank::MoveX(float inc) {
	if (inc < 0.f)
		inc /= 1.2f;

	mAcceleration += 1.f;
	if (mAcceleration > mMaxAcceleration) {
		mAcceleration = mMaxAcceleration;
	}
	sf::Vector2f newPos(mBase->getPosition());
	sf::Vector2f oldPos(newPos);

	newPos.x += sin(mBase->getRotation()*3.14f / 180.f)* inc * (mVelocity->x + mAcceleration);
	newPos.y -= cos(mBase->getRotation()*3.14f / 180.f)* inc * (mVelocity->y + mAcceleration);

	mBase->setPosition(newPos);
	mTop->setPosition(newPos);

	if (checkCollision() || checkOutOfBounds()) {
		mBase->setPosition(oldPos);
		mTop->setPosition(oldPos);

		return false;
	}
	return true;
}

void Tank::shoot() {
	if (mHitCooldownClock.getElapsedTime().asSeconds() > mHitCooldown) {
		sf::Sprite* news = new sf::Sprite(Game::get()->mTextures.get(Texture::bullet_orange));

		news->setRotation(mTop->getRotation());
		news->setOrigin(news->getLocalBounds().width / 2.f, news->getLocalBounds().height / 2.f);
		news->setPosition(mTop->getPosition());

		sf::Vector2f* pos = new sf::Vector2f(sin(mTop->getRotation()*3.14f / 180.f)*mTop->getLocalBounds().width + mTop->getPosition().x,
			-cos(mTop->getRotation()*3.14f / 180.f)*mTop->getLocalBounds().height + mTop->getPosition().y);

		Map* m = Game::get()->mMap;
		m->mEntities[2].insert(m->mEntities[2].end(), new Projectile(news, pos, new sf::Vector2f(500.f, 500.f), mDamage));
		//m->mEntities[2].insert(m->mEntities[2].end(), new Projectile(news, pos, new sf::Vector2f(550.f, 550.f), mDamage));
		//m->mEntities[2].insert(m->mEntities[2].end(), new Projectile(news, pos, new sf::Vector2f(600.f, 600.f), mDamage));


		mHitCooldownClock.restart();
	}
}

bool Tank::checkCollision() {
	bool collideSolid = false;

	Map* map = Game::get()->mMap;

	sf::Vector2f tempScale;
	tempScale.x = tempScale.y = 0.5f;

	mBase->setScale(tempScale);
	for (auto it1 = map->mEntities.begin(); it1 != map->mEntities.end(); ++it1) {
		for (auto it2 = (*it1).begin(); it2 != (*it1).end(); ++it2) {
			if ((*it2) != this)
			{
				if (SAT.collision(mBase, (*it2)->getSprite())) {
					collideSolid = true;
					if (Tank* tank = dynamic_cast<Tank*>(*it2)) {
						collideSolid = false;
					}
				}
			}
		}
	}

	tempScale.x = tempScale.y = 1.f;

	mBase->setScale(tempScale);

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