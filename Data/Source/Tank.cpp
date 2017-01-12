#include "Tank.h"
#include "Game.h"
#include "Obstacle.h"
#include "Map.h"
#include "basic_bullet.h"
#include "Missile.h"
#include "LaserBall.h"
#include "AI.h"

#include "Animation.h"
#include "GameState_Play.h"
#include <cmath>
Tank::Tank(sf::Sprite* base, sf::Sprite* top, sf::Vector2f* pos, sf::Vector2f* vel, float health, float damage, size_t team):
Entity(),
mBase(base),
mTop(top),
mVelocity(vel),
mHealth(health),
mMaxHealth(health),
mDamage(damage),
mTeam(team),
mIsProjectileHollow(false),
mProjectileType(ProjectileType::Basic),
mProjectileSpeed(new sf::Vector2f(500.f, 500.f))
{
	sf::Vector2f topPos = top->getPosition();
	top->setOrigin((float)top->getTexture()->getSize().x / 2, (float)top->getTexture()->getSize().y / 2);
	base->setOrigin((float)base->getTexture()->getSize().x / 2, (float)base->getTexture()->getSize().y / 2);
	base->setPosition(pos->x, pos->y);
	top->setPosition(base->getPosition());

	mHitCooldown = 0.6f;
	mHitCooldownClock.restart();

	mAcceleration = 0.f;
	mMaxAcceleration = 60.f;

	mHpBarBase.setTexture(Game::get()->mTextures.get(Texture::hp_base));
	mHpBarTop.setTexture(Game::get()->mTextures.get(Texture::hp_top));

	mHpBarTop.setPosition(mBase->getPosition().x - mHpBarTop.getLocalBounds().width / 2.f, mBase->getPosition().y - 50.f);
	mHpBarBase.setPosition(mBase->getPosition().x - mHpBarBase.getLocalBounds().width / 2.f, mBase->getPosition().y - 50.f);


	mMovingState = 0;
	mLastPoint = mBase->getPosition();
	mMovingStateClock.restart();
}

Tank::~Tank()
{
	delete mTop, mBase, mVelocity, mProjectileSpeed;
}

void Tank::draw(sf::RenderWindow* window) {
	window->draw(*mBase);
	window->draw(*mTop);

	window->draw(mHpBarBase);
	window->draw(mHpBarTop);
}

void Tank::update(sf::Time dt) {
	if (mBase->getPosition().x != mLastPoint.x && mBase->getPosition().y != mLastPoint.y) {
		mMovingStateClock.restart();
	}
	else {
		if (mMovingStateClock.getElapsedTime().asSeconds() > 0.1f) {
			mMovingState = 0;
			mMovingStateClock.restart();
		}
			
	}

	if (mHealth <= 0) {
		auto it1 = GameState_Play::getStatePointer()->mMap->mEntities[2].begin();
		auto it2 = GameState_Play::getStatePointer()->mMap->mEntities[2].end();

		//disable all kind of targeting on this entity
		for (; it1 != it2; ++it1) {
			if (AI* target = dynamic_cast<AI*>((*it1))) {
				target->mTarget = nullptr;
			}
			if (Missile* target = dynamic_cast<Missile*>((*it1))) {
				target->mTarget = nullptr;
			}
		}

		//end all power up objects
		for (auto it = mPowerUpList.begin(); it != mPowerUpList.end(); ++it) {
			(*it)->onDurationEnd();
		}

		GameState_Play::getStatePointer()->mMap->mEffects.insert(GameState_Play::getStatePointer()->mMap->mEffects.begin(), new Animation(new sf::Vector2f(mBase->getPosition()), Texture::expl_10_0000, Texture::expl_10_0031, 50, false));
		mDelete = true;
	}
	else {
		//handle hp bar
		sf::Vector2f newScale;
		newScale.x = mHealth / mMaxHealth;
		newScale.y = 1.f;
		mHpBarTop.setScale(newScale);
	}
}

void Tank::rotateTurret(float modifier) {
	mTop->setRotation(mTop->getRotation() + 350.f * modifier);
}

void Tank::rotateBase(float modifier) {
	mLastPoint = mBase->getPosition();
	mBase->rotate(300.f * modifier);
}

bool Tank::MoveX(float inc) {

		
	mAcceleration += 1.f;
	if (mAcceleration > mMaxAcceleration) {
		mAcceleration = mMaxAcceleration;
	}

	sf::Vector2f oldPosPlayer(mBase->getPosition());
	sf::Vector2f oldPosHpBar(mHpBarBase.getPosition());
	sf::Vector2f newPos;

	if (inc > 0.f) {
		mMovingState = 1;
		newPos.x = sin(mBase->getRotation()*3.14f / 180.f)* inc * (mVelocity->x + mAcceleration);
		newPos.y = -cos(mBase->getRotation()*3.14f / 180.f)* inc * (mVelocity->y + mAcceleration);
	}
	else {
		mMovingState = 2;
		newPos.x = sin(mBase->getRotation()*3.14f / 180.f)* inc * 0.5f*(mVelocity->x + mAcceleration);
		newPos.y = -cos(mBase->getRotation()*3.14f / 180.f)* inc * 0.5f*(mVelocity->y + mAcceleration);
	}
	
	mBase->move(newPos);
	mTop->move(newPos);

	mLastPoint = mBase->getPosition();

	mHpBarBase.move(newPos);
	mHpBarTop.move(newPos);

	if (checkCollision() || checkOutOfBounds()) {
		mBase->setPosition(oldPosPlayer);
		mTop->setPosition(oldPosPlayer);

		mHpBarBase.setPosition(oldPosHpBar);
		mHpBarTop.setPosition(oldPosHpBar);

		mLastPoint = oldPosPlayer;

		return false;
	}
	return true;
}

void Tank::shoot() {
	if (mHitCooldownClock.getElapsedTime().asSeconds() > mHitCooldown) {
		Projectile* projectile = nullptr;
		Map* map = GameState_Play::getStatePointer()->mMap;
		
		if (mProjectileType == ProjectileType::Basic) {
			mProjectileSpeed->x = 500.f;
			mProjectileSpeed->y = 500.f;
			projectile = new BasicBullet(this);
		}
		if (mProjectileType == ProjectileType::Missile) {
			mProjectileSpeed->x = 300.f;
			mProjectileSpeed->y = 300.f;
			projectile = new Missile(this);
		}	
		if (mProjectileType == ProjectileType::LaserBall) {
			mProjectileSpeed->x = 200.f;
			mProjectileSpeed->y = 200.f;
			projectile = new LaserBall(this);
		}
			
		if(mIsProjectileHollow)
			projectile->setHollow();
		map->mEntities[2].insert(map->mEntities[2].end(), projectile);

		mHitCooldownClock.restart();
	}
}

bool Tank::checkCollision() {
	bool collideSolid;

	Map* map = GameState_Play::getStatePointer()->mMap;

	sf::Vector2f tempScale;
	tempScale.x = tempScale.y = 0.5f;
	mBase->setScale(tempScale);

	collideSolid = false;
	for (auto it1 = map->mEntities.begin(); it1 != map->mEntities.end(); ++it1) {
		for (auto it2 = (*it1).begin(); it2 != (*it1).end(); ++it2) {
			if ((*it2) != this)
			{
				if (SAT.collision(mBase, (*it2)->getCollisionSprite())) {

					if (PowerUp* pu = dynamic_cast<PowerUp*>(*it2)) {
						pu->onTrigger(this);
					}
					if (Obstacle* obs = dynamic_cast<Obstacle*>(*it2)) {
						collideSolid = true;
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

void Tank::setPosition(sf::Vector2f& newPos) {

	mBase->setPosition(newPos);
	mTop->setPosition(newPos);

	mHpBarTop.setPosition(mBase->getPosition().x - mHpBarTop.getLocalBounds().width / 2.f, mBase->getPosition().y - 50.f);
	mHpBarBase.setPosition(mBase->getPosition().x - mHpBarBase.getLocalBounds().width / 2.f, mBase->getPosition().y - 50.f);
}

sf::Sprite* Tank::getCollisionSprite() {
	return mBase;
}