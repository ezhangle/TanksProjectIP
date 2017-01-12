#include "AI_Hard.h"
#include "VectorUtility.h"
#include "Game.h"
#include "GameState_Play.h"

AI_Hard::AI_Hard(sf::Sprite* base, sf::Sprite* top, sf::Vector2f* pos, sf::Vector2f* vel, float health, float damage, size_t team) :
	AI(base, top, pos, vel, health, damage, team) {
}

void AI_Hard::assignNewPoint() {
	if (!mCurrentPath.empty()) {
		mNextPoint = mCurrentPath.top();
		mCurrentPath.pop();

		calculateRotation();
		mDistToNextPoint = Vector2f::distance(mNextPoint, mBase->getPosition());
	}
	else {
		calculatePathMap();

		int noPowerUps = GameState_Play::getStatePointer()->mMap->mEntities[1].size();
		bool foundPU = false;

		if (noPowerUps > 0) {
			int puTarget = rand() % noPowerUps;

			auto it = GameState_Play::getStatePointer()->mMap->mEntities[1].begin();

			for (int i = 0; i < puTarget; ++i) {
				++it;
			}

			PowerUp* pu = dynamic_cast<PowerUp*>((*it));
			if (pu->mIsActive == false) {
				sf::Vector2f targetPoint;
				targetPoint.x = (int)((pu->mSprite->getPosition().y + pu->mSprite->getLocalBounds().height / 2.f) / mTileLength);
				targetPoint.y = (int)((pu->mSprite->getPosition().x + pu->mSprite->getLocalBounds().width / 2.f) / mTileLength);


				calculatePath(targetPoint);
				foundPU = true;
			}

		}


		if (foundPU == false)
			calculateRandomPath();

		setPosition(mCurrentPath.top());
		mCurrentPath.pop();

		assignNewPoint();
	}
}

void AI_Hard::update(sf::Time dt) {
	

	if (mPathFindMap == nullptr) {
		assignNewPoint();
	}
		
	if (mDistToNextPoint < 5.f) {
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
			else
				mDistToNextPoint -= (mVelocity->x + mAcceleration)*dt.asSeconds();
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
				closingVelocity.x = (mTarget->mVelocity->x + mTarget->mAcceleration) - mTarget->mProjectileSpeed->x;
				closingVelocity.y = (mTarget->mVelocity->y + mTarget->mAcceleration) - mTarget->mProjectileSpeed->y;
			}
			else {
				closingVelocity.x = (mTarget->mVelocity->x)*0.5f - mTarget->mProjectileSpeed->x;
				closingVelocity.y = (mTarget->mVelocity->y)*0.5f - mTarget->mProjectileSpeed->y;
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

		sf::Vector2f tankPos(mBase->getPosition());

		float angle = 180.f - atan2(playerPosition.x - tankPos.x, playerPosition.y - tankPos.y) * 180.f / 3.14f;
		float currentTurretRotation = mTop->getRotation();
		float angleDiff = abs(currentTurretRotation - angle);

		if (angleDiff > 3.f) {
			if (abs(currentTurretRotation - angle) < 180.f) {
				if (currentTurretRotation < angle)
					rotateTurret(dt.asSeconds());
				else
					rotateTurret(-dt.asSeconds());
			}
			else {
				if (currentTurretRotation < angle)
					rotateTurret(-dt.asSeconds());
				else
					rotateTurret(dt.asSeconds());
			}
		}
		else
			if (isProjectilePathClear())
				shoot();
		
	}

	AI::update(dt);
}
