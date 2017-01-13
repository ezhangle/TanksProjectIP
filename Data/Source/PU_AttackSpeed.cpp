#include "PU_AttackSpeed.h"
#include "Game.h"
#include "Enums.h"

PU_AttackSpeed::PU_AttackSpeed(sf::Vector2f* position) :
	PowerUp(position, new sf::Sprite(Game::get()->mTextures.get(Texture::pu_fast_attacks))),
	mAttackSpeedMultiplier(5.f){

}

void PU_AttackSpeed::update(sf::Time dt) {
	PowerUp::update(dt);
}

void PU_AttackSpeed::onTrigger(Tank* target) {

	PowerUp::onTrigger(target);

	target->mHitCooldown /= mAttackSpeedMultiplier;
	target->mHitCooldownClock.restart();

	checkForDuplicate();
}

void PU_AttackSpeed::onDurationEnd() {

	if (mTarget != nullptr) {
		mTarget->mHitCooldown *= mAttackSpeedMultiplier;
		mTarget->mHitCooldownClock.restart();
	}
	
	PowerUp::onDurationEnd();
}

void PU_AttackSpeed::checkForDuplicate() {
	bool found = false;
	auto it = mTarget->mPowerUpList.begin();

	for (; it != mTarget->mPowerUpList.end(); ++it) {
		if (PU_AttackSpeed* obj = dynamic_cast<PU_AttackSpeed*>((*it))) {
			obj->mDurationClock->restart();
			found = true;

			onDurationEnd();
		}
	}

	if (!found)
		mTarget->mPowerUpList.insert(mTarget->mPowerUpList.begin(), this);
}