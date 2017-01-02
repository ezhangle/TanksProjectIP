#include "AI_Medium.h"
#include "VectorUtility.h"
#include "Game.h"
#include "PowerUp.h"

AI_Medium::AI_Medium(sf::Sprite* base, sf::Sprite* top, sf::Vector2f* pos, sf::Vector2f* vel, float health, float damage, size_t team) :
	AI(base, top, pos, vel, health, damage, team) {

}

void AI_Medium::assignNewPoint() {
	if (!mCurrentPath.empty()) {
		mNextPoint = mCurrentPath.top();
		mCurrentPath.pop();

		calculateRotation();
	}
	else {
		calculatePathMap();
		
		auto it1 = Game::get()->mMap->mEntities[1].begin();
		auto it2 = Game::get()->mMap->mEntities[1].end();
		bool foundPU = false;

		for (; it1 != it2; ++it1) {
			PowerUp* pu = dynamic_cast<PowerUp*>((*it1));

			if (pu->mIsActive == false) {
				sf::Vector2f targetPoint;
				targetPoint.x = (int)((pu->mSprite->getPosition().y + pu->mSprite->getLocalBounds().height / 2.f) / mTileLength);
				targetPoint.y = (int)((pu->mSprite->getPosition().x + pu->mSprite->getLocalBounds().width / 2.f )/ mTileLength);


				calculatePath(targetPoint);
				foundPU = true;

				break;	
			}
		}
		
		if(foundPU == false)
			calculateRandomPath();

		setPosition(mCurrentPath.top());
		mCurrentPath.pop();

		assignNewPoint();
	}
}

void AI_Medium::update(sf::Time dt) {
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