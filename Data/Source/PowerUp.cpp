#include "PowerUp.h"

PowerUp::PowerUp(sf::Vector2f* position, sf::Sprite* sprite) :
	Entity(position, sprite), 
	mDuration(5.f),
	mDurationClock(nullptr),
	mTarget(nullptr),
	mIsActive(false){

	mFloatMinimum = position->y;
	mFloatMaximum = position->y + 10.f;
	mFloatSpeed = 20.f;
	mFloatUpwards = true;
}

void PowerUp::update(sf::Time dt) {
	float axisOffset = mFloatSpeed*dt.asSeconds();
	if (mFloatUpwards) {
		if (axisOffset + mSprite->getPosition().y > mFloatMaximum)
			mFloatUpwards = false;
	}
	else {
		if (-axisOffset + mSprite->getPosition().y < mFloatMinimum)
			mFloatUpwards = true;
	}

	sf::Vector2f offset(0.f, axisOffset);
	if (!mFloatUpwards)
		offset.y *= -1.f;
	mSprite->move(offset);


	if (mDurationClock != nullptr) {
		if (mDurationClock->getElapsedTime().asSeconds() > mDuration) {
			onDurationEnd();
			mDelete = true;
		}
	}
}

void PowerUp::onTrigger(Tank* target) {
	mSprite->setPosition(-50.f, -50.f);
	mTarget = target;
	mIsActive = true;

	mDurationClock = new sf::Clock;
	mDurationClock->restart();
}
