#include "PU_Missile.h"
#include "PU_Laser.h"
#include "Game.h"
#include "Enums.h"


PU_Missile::PU_Missile(sf::Vector2f* position)
	:PowerUp(position, new sf::Sprite(Game::get()->mTextures.get(Texture::pu_missile))) {
	mDuration = 30.f;
}

void PU_Missile::onTrigger(Tank * target)
{
	PowerUp::onTrigger(target);

	checkForDuplicate();

	target->changeProjectile(Tank::ProjectileType::Missile);

	
}

void PU_Missile::onDurationEnd()
{
	if (mTarget != nullptr)
		mTarget->changeProjectile(Tank::ProjectileType::Basic);

	PowerUp::onDurationEnd();
}


void PU_Missile::checkForDuplicate() {
	bool found = false;
	auto it = mTarget->mPowerUpList.begin();

	for (; it != mTarget->mPowerUpList.end(); ++it) {
		if (PU_Missile* obj = dynamic_cast<PU_Missile*>((*it))) {
			obj->mDurationClock->restart();
			found = true;

			onDurationEnd();
		}

		if (PU_Laser* obj = dynamic_cast<PU_Laser*>((*it))) {
			obj->onDurationEnd();
		}
		
	}

	if (!found)
		mTarget->mPowerUpList.insert(mTarget->mPowerUpList.begin(), this);
}