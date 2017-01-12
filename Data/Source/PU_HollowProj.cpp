#include "PU_HollowProj.h"
#include "Game.h"
#include "Enums.h"

PU_HollowProj::PU_HollowProj(sf::Vector2f * position)
	:PowerUp(position, new sf::Sprite(Game::get()->mTextures.get(Texture::pu_damage)))
{
	mSprite->setColor(sf::Color(255, 255, 255, 128));
	mDuration = 10.f;
}

void PU_HollowProj::onTrigger(Tank* target)
{
	PowerUp::onTrigger(target);

	mTarget->mIsProjectileHollow = true;
}

void PU_HollowProj::onDurationEnd()
{
	PowerUp::onDurationEnd();

	mTarget->mIsProjectileHollow = false;
}

void PU_HollowProj::checkForDuplicate()
{
	bool found = false;
	auto it = mTarget->mPowerUpList.begin();

	for (; it != mTarget->mPowerUpList.end(); ++it) {
		if (PU_HollowProj* obj = dynamic_cast<PU_HollowProj*>((*it))) {
			obj->mDurationClock->restart();
			found = true;

			onDurationEnd();
		}
	}

	if (!found)
		mTarget->mPowerUpList.insert(mTarget->mPowerUpList.begin(), this);
}
