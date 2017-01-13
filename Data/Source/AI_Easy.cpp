#include "AI_Easy.h"
#include "VectorUtility.h"

AI_Easy::AI_Easy(sf::Sprite* base, sf::Sprite* top, sf::Vector2f* pos, sf::Vector2f* vel, float health, float damage, size_t team):
AI(base, top, pos, vel, health, damage, team){

}

void AI_Easy::update(sf::Time dt) {

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

		sf::Vector2f playerPosition(mTarget->mBase->getPosition());
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