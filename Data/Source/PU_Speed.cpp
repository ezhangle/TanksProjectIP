#include "PU_Speed.h"
#include "Enums.h"
#include "Game.h"
#include <cstdlib>

PU_Speed::PU_Speed(sf::Vector2f * position)
	:PowerUp(position, new sf::Sprite(Game::get()->mTextures.get(Texture::pu_speed))),
	mMovementSpeedMultiplier(3.f)
{
	mDuration = 10.f;
	mAnimationSpawnClock.restart();
}

void PU_Speed::update(sf::Time dt)
{
	PowerUp::update(dt);
	
	if (mIsActive) {
		if (mTarget->mMovingState == 1 && mAnimationSpawnClock.getElapsedTime().asMilliseconds() > 15.f) {

			sf::Vector2f* position = new sf::Vector2f(-sin(mTarget->mBase->getRotation()*3.14f / 180.f)*mTarget->mBase->getLocalBounds().width / 3.f + mTarget->mBase->getPosition().x,
				+cos(mTarget->mBase->getRotation()*3.14f / 180.f)*mTarget->mBase->getLocalBounds().height / 3.f + mTarget->mBase->getPosition().y);

			Animation* anim = new Animation(position, Texture::expl_01_0000, Texture::expl_01_0023, 20, false);

			Game::get()->mMap->mEffects.insert(Game::get()->mMap->mEffects.begin(), anim);

			mAnimationSpawnClock.restart();
		}
	}
	
	
}

void PU_Speed::onTrigger(Tank * target)
{
	PowerUp::onTrigger(target);

	target->mVelocity->x *= mMovementSpeedMultiplier;
	target->mVelocity->y *= mMovementSpeedMultiplier;

	checkForDuplicate();
}

void PU_Speed::onDurationEnd()
{
	PowerUp::onDurationEnd();
	mTarget->mVelocity->x /= mMovementSpeedMultiplier;
	mTarget->mVelocity->y /= mMovementSpeedMultiplier;
}

void PU_Speed::checkForDuplicate() {
	bool found = false;
	auto it = mTarget->mPowerUpList.begin();

	for (; it != mTarget->mPowerUpList.end(); ++it) {
		if (PU_Speed* obj = dynamic_cast<PU_Speed*>((*it))) {
			obj->mDurationClock->restart();
			found = true;

			onDurationEnd();
		}
	}

	if (!found)
		mTarget->mPowerUpList.insert(mTarget->mPowerUpList.begin(), this);
}