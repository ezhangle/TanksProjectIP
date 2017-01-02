#include "PU_AttackSpeed.h"

PU_AttackSpeed::PU_AttackSpeed(sf::Vector2f* position, sf::Sprite* sprite) :
	PowerUp(position, sprite),
	mAttackSpeedMultiplier(5.f){

}

void PU_AttackSpeed::update(sf::Time dt) {
	PowerUp::update(dt);
}

void PU_AttackSpeed::onTrigger(Tank* target) {

	PowerUp::onTrigger(target);

	target->mHitCooldown /= mAttackSpeedMultiplier;
	target->mHitCooldownClock.restart();
}

void PU_AttackSpeed::onDurationEnd() {
	mTarget->mHitCooldown *= mAttackSpeedMultiplier;
	mTarget->mHitCooldownClock.restart();
}