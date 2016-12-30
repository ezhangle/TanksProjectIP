#include "AI_Hard.h"
#include "VectorUtility.h"
#include <iostream>

AI_Hard::AI_Hard(sf::Sprite* base, sf::Sprite* top, sf::Vector2f* pos, sf::Vector2f* vel, float health, float damage, size_t team) :
	AI(base, top, pos, vel, health, damage, team) {
}

void AI_Hard::update(sf::Time dt) {
	

	if (mPathFindMap == nullptr) {
		assignNewPoint();
	}
		

	float distToNext = Vector2f::distance(mNextPoint, mBase->getPosition());
	if (distToNext < 5.f) {
		setPosition(mNextPoint);
		assignNewPoint();
	}
	else {

		float currentRotation = mBase->getRotation();

		if (currentRotation == mRotationAngle) {

			if (!MoveX(dt.asSeconds())) {
				std::stack<sf::Vector2f> clear;
				mCurrentPath = clear;

				assignNewPoint();
			}
		}
		else {

			if (mRotationAngle == 0.f) {
				if (currentRotation >= 270.f)
					mBase->setRotation(currentRotation + 6.f);
				else
					mBase->setRotation(currentRotation - 6.f);
			}
			else {
				if (currentRotation > mRotationAngle)
					mBase->setRotation(currentRotation - 6.f);
				else
					mBase->setRotation(currentRotation + 6.f);
			}
		}

		if (mTarget == nullptr) {
			findNewTarget();
			return;
		}

		sf::Vector2f turretProjection(mBase->getPosition());
		sf::Vector2f playerPosition(mTarget->mBase->getPosition());

		if (mTarget->mMovingState > 0) {
			sf::Vector2f closingVelocity;
			if (mTarget->mMovingState == 1) {
				closingVelocity.x = (mTarget->mVelocity->x + mTarget->mAcceleration) - 500.f;
				closingVelocity.y = (mTarget->mVelocity->y + mTarget->mAcceleration) - 500.f;
			}
			else {
				closingVelocity.x = (mTarget->mVelocity->x)*0.5f - 500.f;
				closingVelocity.y = (mTarget->mVelocity->y)*0.5f - 500.f;
			}

			sf::Vector2f closingRange(mTarget->mBase->getPosition());
			closingRange.x -= sin(mTop->getRotation()*3.14f / 180.f)*mTop->getLocalBounds().width + mTop->getPosition().x;
			closingRange.y -= -cos(mTop->getRotation()*3.14f / 180.f)*mTop->getLocalBounds().height + mTop->getPosition().y;

			float clVelMagn = Vector2f::length(closingVelocity);
			float clRanMagn = Vector2f::length(closingRange);
			float clTime = clRanMagn / clVelMagn;

			playerPosition.x += mTarget->mVelocity->x * clTime;
			playerPosition.y += mTarget->mVelocity->y * clTime;

			float extraAngle = 90.f + atan2(Vector2f::dot(playerPosition, mBase->getPosition()), playerPosition.x*mBase->getPosition().y + playerPosition.y*mBase->getPosition().x) * 180.f / 3.14f;

			float angleOfRotation = (360.f - extraAngle + mTarget->mBase->getRotation()) * 3.14f / 180.f;
			if (mTarget->mMovingState == 2)
				angleOfRotation += 180.f * 3.14 / 180.f;

			sf::Vector2f newPos;
			newPos.x = (playerPosition.x - mTarget->mBase->getPosition().x) * cos(angleOfRotation) - (playerPosition.y - mTarget->mBase->getPosition().y) * sin(angleOfRotation);
			newPos.y = (playerPosition.x - mTarget->mBase->getPosition().x) * sin(angleOfRotation) + (playerPosition.y - mTarget->mBase->getPosition().y) * cos(angleOfRotation);

			newPos.x += mTarget->mBase->getPosition().x;
			newPos.y += mTarget->mBase->getPosition().y;

			playerPosition = newPos;
		}
		

		float distanceToPlayer = Vector2f::distance(turretProjection, playerPosition);

		turretProjection.x += sin(mTop->getRotation()*3.14f / 180.f)* distanceToPlayer;
		turretProjection.y -= cos(mTop->getRotation()*3.14f / 180.f)* distanceToPlayer;

		if (abs(turretProjection.y - playerPosition.y) > 5.f && abs(turretProjection.x - playerPosition.x) > 5.f) {

			float distProjPlayer = Vector2f::distance(turretProjection, playerPosition);
			float angle = acos(1.f - distProjPlayer / (2 * distanceToPlayer));

			if (playerPosition.x < mBase->getPosition().x) {
				if (360.f - angle > 180.f)
					if (turretProjection.y > playerPosition.y)
						rotateTurret(dt.asSeconds());
					else
						rotateTurret(-dt.asSeconds());
				else {
					if (turretProjection.y > playerPosition.y)
						rotateTurret(-dt.asSeconds());
					else
						rotateTurret(dt.asSeconds());
				}
			}
			else {
				if (360.f - angle > 180.f)
					if (turretProjection.y > playerPosition.y)
						rotateTurret(-dt.asSeconds());
					else
						rotateTurret(dt.asSeconds());
				else {
					if (turretProjection.y > playerPosition.y)
						rotateTurret(dt.asSeconds());
					else
						rotateTurret(-dt.asSeconds());
				}
			}


		}
		else
			shoot();
	}

	AI::update(dt);
}
