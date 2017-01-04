#include "Missile.h"
#include "Game.h"
#include "Enums.h"
#include "VectorUtility.h"
#include <cmath>
#include <iostream>

Missile::Missile(Tank * parent)
	:Projectile(new sf::Sprite(Game::get()->mTextures.get(Texture::missile)), parent),
	mTarget(nullptr),
	mAcceleration(0.f)
{
	mSprite->setRotation(parent->mTop->getRotation());
	mSprite->setOrigin(mSprite->getLocalBounds().width / 2.f, mSprite->getLocalBounds().height / 2.f);

	sf::Vector2f pos(sin(parent->mTop->getRotation()*3.14f / 180.f)*parent->mTop->getLocalBounds().width / 2.f + parent->mTop->getPosition().x,
		-cos(parent->mTop->getRotation()*3.14f / 180.f)*parent->mTop->getLocalBounds().height / 2.f + parent->mTop->getPosition().y);

	mSprite->setPosition(pos);

	setTarget();
}

void Missile::update(sf::Time dt)
{
	Projectile::update(dt);
	
	if (mTarget != nullptr) {
		mAcceleration += 50.f * dt.asSeconds();

		sf::Vector2f targetPos(mTarget->mBase->getPosition());
		sf::Vector2f missilePos(mSprite->getPosition());

		float angle = 180.f - atan2(targetPos.x - missilePos.x, targetPos.y - missilePos.y) * 180.f / 3.14f;

		float currentRotation = mSprite->getRotation();

		if (abs(currentRotation - angle) < 180.f) {
			if (currentRotation < angle)
				rotateMissile(dt.asSeconds());
			else
				rotateMissile(-dt.asSeconds());
		}
		else {
			if (currentRotation < angle)
				rotateMissile(-dt.asSeconds());
			else
				rotateMissile(dt.asSeconds());
		}
	}
	
}

void Missile::setTarget()
{
	auto it = Game::get()->mMap->mEntities[2].begin();
	for (; it != Game::get()->mMap->mEntities[2].end(); ++it) {
		if (Tank* enemy = dynamic_cast<Tank*>(*it)) {
			if (enemy->mTeam != mParent->mTeam && enemy->mHealth > 0.f)
				mTarget = enemy;
		}
	}
}

void Missile::rotateMissile(float deltaAsSeconds)
{
	mSprite->rotate(deltaAsSeconds * (200.f + mAcceleration));
}

