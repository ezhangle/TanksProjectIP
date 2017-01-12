#include "PU_Repair.h"
#include "Game.h"
#include "Enums.h"

PU_Repair::PU_Repair(sf::Vector2f * position):
	PowerUp(position, new sf::Sprite(Game::get()->mTextures.get(Texture::pu_repair))),
	mHpPerSecond(0.f)
{
	mDuration = 3.f;
}

void PU_Repair::update(sf::Time dt)
{
	PowerUp::update(dt);

	if (mTarget != nullptr) {
		mTarget->mHealth += mHpPerSecond * dt.asSeconds();

		if (mTarget->mHealth > mTarget->mMaxHealth) {
			mTarget->mHealth = mTarget->mMaxHealth;

			onDurationEnd();
		}
	}
	
}

void PU_Repair::onTrigger(Tank * target)
{
	PowerUp::onTrigger(target);

	mHpPerSecond = target->mMaxHealth / 10.f;

	checkForDuplicate();
}

void PU_Repair::checkForDuplicate()
{
	bool found = false;
	auto it = mTarget->mPowerUpList.begin();

	for (; it != mTarget->mPowerUpList.end(); ++it) {
		if (PU_Repair* obj = dynamic_cast<PU_Repair*>((*it))) {
			obj->mDurationClock->restart();
			found = true;

			onDurationEnd();
		}
	}

	if (!found)
		mTarget->mPowerUpList.insert(mTarget->mPowerUpList.begin(), this);
}
