#include "AI.h"
#include "Game.h"
#include "Map.h"
#include "Obstacle.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <queue>

AI::AI(sf::Sprite* base, sf::Sprite* top, sf::Vector2f* pos, sf::Vector2f* vel, float health, float damage):
Tank(base, top, pos, vel, health, damage),
mTileLength(64.f),
mPathFindMap(nullptr),
mPlayer(nullptr){

	std::srand(std::time(NULL));
	mWidth = Game::get()->mWidth / mTileLength;
	mHeight = Game::get()->mHeight / mTileLength;

	mNextPoint.x = -1.f;
	mNextPoint.y = -1.f;

	nextPoint.setFillColor(sf::Color::Red);
	sf::Vector2f size;
	size.x = 5.f;
	size.y = 5.f;
	nextPoint.setSize(size);

}

void AI::initMap() {
	mPathFindMap = new int*[mHeight];
	for (int i = 0; i < mHeight; ++i) {
		mPathFindMap[i] = new int[mWidth]();
	}

	auto it1 = Game::get()->mMap->mEntities[0].begin();
	auto it2 = Game::get()->mMap->mEntities[0].end();
	for (; it1 != it2; ++it1) {

		sf::FloatRect bounds = (*it1)->mSprite->getGlobalBounds();

		int left = (int)(bounds.left / mTileLength);
		int top = (int)(bounds.top / mTileLength);
		int leftPlus = (int)((bounds.left + bounds.width) / mTileLength);
		int topPlus = (int)((bounds.top + bounds.height) / mTileLength);

		for (int i = left; i <= leftPlus; ++i) {
			mPathFindMap[top][i] = -1;
			mPathFindMap[topPlus][i] = -1;
		}		
		for (int i = top; i <= topPlus; ++i) {
			mPathFindMap[i][left] = -1;
			mPathFindMap[i][leftPlus] = -1;
		}

	}

	auto it = Game::get()->mMap->mEntities[2].begin();
	for (; it != Game::get()->mMap->mEntities[2].end(); ++it) {
		if (Player* player = dynamic_cast<Player*>(*it)) {
			mPlayer = player;
		}
	}

	float edgeX, edgeY;
	for (int i = 0; i < mHeight; ++i) {
		for (int j = 0; j < mWidth; ++j) {
			edgeY = i * mTileLength;
			edgeX = j * mTileLength;
			if (edgeX < 64.f || edgeY < 64.f || edgeX >= Game::get()->mWidth - 64.f || edgeY >= Game::get()->mHeight - 64.f)
				mPathFindMap[i][j] = -1;
		}
	}

}

void AI::calculateRotation() {

	if (mNextPoint.x > mBase->getPosition().x)
		mRotationAngle = 90.f;
	else if(mNextPoint.x < mBase->getPosition().x)
		mRotationAngle = 270.f;
	else if (mNextPoint.y > mBase->getPosition().y)
		mRotationAngle = 180.f;
	else if (mNextPoint.y < mBase->getPosition().y)
		mRotationAngle = 0.f;
}

void AI::assignNewPoint() {
	if (!mCurrentPath.empty()) {
		mNextPoint = mCurrentPath.top();
		mCurrentPath.pop();

		calculateRotation();
	}
	else {
		calculatePathMap();
		calculateRandomPath();

		mBase->setPosition(mCurrentPath.top());
		mTop->setPosition(mCurrentPath.top());
		mCurrentPath.pop();

		assignNewPoint();
	}
}

void AI::update(sf::Time dt) {

	nextPoint.setPosition(mNextPoint);

	if (mPathFindMap == nullptr) {
		assignNewPoint();
	}

	float distToNext = sqrt((mBase->getPosition().x - mNextPoint.x)*(mBase->getPosition().x - mNextPoint.x) + (mBase->getPosition().y - mNextPoint.y)*(mBase->getPosition().y - mNextPoint.y));
	if (distToNext < 5.f) {
		mBase->setPosition(mNextPoint);
		mTop->setPosition(mNextPoint);
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
				if(currentRotation >= 270.f)
					mBase->setRotation(currentRotation + 6.f);
				else
					mBase->setRotation(currentRotation - 6.f);
			}
			else {
				if(currentRotation > mRotationAngle)
					mBase->setRotation(currentRotation - 6.f);
				else
					mBase->setRotation(currentRotation + 6.f);
			}
		}


		sf::Vector2f turretProjection(mBase->getPosition());
		sf::Vector2f playerPosition(mPlayer->mBase->getPosition());

		float d = sqrt((turretProjection.x - playerPosition.x)*(turretProjection.x - playerPosition.x) + (turretProjection.y - playerPosition.y)*(turretProjection.y - playerPosition.y));
		if (mPlayer->mMoveState > 0) {
			float d = sqrt((turretProjection.x - playerPosition.x)*(turretProjection.x - playerPosition.x) + (turretProjection.y - playerPosition.y)*(turretProjection.y - playerPosition.y));

			if (mPlayer->mMoveState == 1) {
				playerPosition.x += sin(mPlayer->mBase->getRotation()*3.14f / 180.f)* (mPlayer->mVelocity->y + mPlayer->mAcceleration)* d / 500.f;
				playerPosition.y -= cos(mPlayer->mBase->getRotation()*3.14f / 180.f)* (mPlayer->mVelocity->y + mPlayer->mAcceleration)* d / 500.f;
			}
			else {
				playerPosition.x += sin((mPlayer->mBase->getRotation() + 180.f)*3.14f / 180.f)* (mPlayer->mVelocity->y + mPlayer->mAcceleration)* d / 500.f;
				playerPosition.y -= cos((mPlayer->mBase->getRotation() + 180.f)*3.14f / 180.f)* (mPlayer->mVelocity->y + mPlayer->mAcceleration)* d / 500.f;
			}
		}
		
		float distanceToPlayer = sqrt((turretProjection.x - playerPosition.x)*(turretProjection.x - playerPosition.x) + (turretProjection.y - playerPosition.y)*(turretProjection.y - playerPosition.y));

		turretProjection.x += sin(mTop->getRotation()*3.14f / 180.f)* distanceToPlayer;
		turretProjection.y -= cos(mTop->getRotation()*3.14f / 180.f)* distanceToPlayer;

		if (abs(turretProjection.y - playerPosition.y) > 5.f && abs(turretProjection.x - playerPosition.x) > 5.f) {

			float distProjPlayer = sqrt((turretProjection.x - playerPosition.x)*(turretProjection.x - playerPosition.x) + (turretProjection.y - playerPosition.y)*(turretProjection.y - playerPosition.y));
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
	
		
	
	Tank::update(dt);
}

void AI::draw(sf::RenderWindow* window) {
	window->draw(nextPoint);

	Tank::draw(window);
}

void AI::calculatePathMap() {
	if (mPathFindMap == nullptr)
		initMap();
	else {
		for (int i = 0; i < mHeight; ++i) {
			for (int j = 0; j < mWidth; ++j) {
				if (mPathFindMap[i][j] > 0)
					mPathFindMap[i][j] = 0;
			}
		}
	}

	std::queue<LeePoint> que;
	LeePoint startPoint;
	LeePoint currentPoint;
	startPoint.x = mBase->getPosition().y / mTileLength;
	startPoint.y = mBase->getPosition().x / mTileLength;
	if(mPathFindMap[startPoint.x][startPoint.y] != -1)
		mPathFindMap[startPoint.x][startPoint.y] = 1;

	que.push(startPoint);
	while (!que.empty()) {
		currentPoint = que.front();
		que.pop();

		for (int i = 0; i < 4; ++i) {
			currentPoint.x += dx[i];
			currentPoint.y += dy[i];

			if (mPathFindMap[currentPoint.x][currentPoint.y] == 0) {
				currentPoint.step++;
				que.push(currentPoint);

				mPathFindMap[currentPoint.x][currentPoint.y] = currentPoint.step;
				currentPoint.step--;
			}

			currentPoint.x -= dx[i];
			currentPoint.y -= dy[i];
		}
	}
 
}

void AI::calculateRandomPath() {
	sf::Vector2f startPoint;
	sf::Vector2f toInsert;

	do {
		startPoint.x = rand() % mHeight;
		startPoint.y = rand() % mWidth;
	} while (mPathFindMap[(int)(startPoint.x)][(int)(startPoint.y)] <= 0);

	int cost = mPathFindMap[(int)(startPoint.x)][(int)(startPoint.y)];
	toInsert.y = (startPoint.x * mTileLength) + mTileLength / 2.f;
	toInsert.x = (startPoint.y * mTileLength) + mTileLength / 2.f;

	mCurrentPath.push(toInsert);

	while (cost > 0) {
		cost--;

		for (int i = 0; i < 4; ++i) {
			startPoint.x += dx[i];
			startPoint.y += dy[i];

			if (mPathFindMap[(int)(startPoint.x)][(int)(startPoint.y)] == cost) {
				toInsert.y = (startPoint.x * mTileLength) + mTileLength / 2.f;
				toInsert.x = (startPoint.y * mTileLength) + mTileLength / 2.f;
				mCurrentPath.push(toInsert);

				break;
			}

			startPoint.x -= dx[i];
			startPoint.y -= dy[i];
		}
	}
}

void AI::calculatePath() {

}


AI::~AI(){
	for (int i = 0; i < mHeight; ++i)
		delete[] mPathFindMap[i];
	mPathFindMap = nullptr;
}