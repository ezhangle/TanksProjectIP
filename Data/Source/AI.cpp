#include "AI.h"
#include "Game.h"
#include "Map.h"
#include "Obstacle.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <queue>
#include <iomanip>

void printMatrix(int **m, int w, int h) {
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j)
			std::cout << std::setw(3) << m[i][j];
		std::cout << '\n';
	}
	std::cout << '\n';
}

AI::AI(sf::Sprite* base, sf::Sprite* top, sf::Vector2f* pos, sf::Vector2f* vel, float health, float damage):
Tank(base, top, pos, vel, health, damage),
mTileLength(64.f),
mPathFindMap(nullptr){

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
	float distToNext = sqrt((mBase->getPosition().x - mNextPoint.x)*(mBase->getPosition().x - mNextPoint.x) + (mBase->getPosition().y - mNextPoint.y)*(mBase->getPosition().y - mNextPoint.y));

	sf::Vector2f projection(mBase->getPosition());
	projection.x += sin(mBase->getRotation()*3.14f / 180.f)* distToNext;
	projection.y -= cos(mBase->getRotation()*3.14f / 180.f)* distToNext;
	std::cout << projection.x << ' ' << projection.y << std::endl;

	float distProjToNext = sqrt((projection.x - mNextPoint.x)*(projection.x - mNextPoint.x) + (projection.y - mNextPoint.y)*(projection.y - mNextPoint.y));

	mRotationAngle = acos(1.f - (distProjToNext*distProjToNext)/(2*distToNext*distToNext)) * 180.f / 3.14f;

	std::cout << mRotationAngle;


	if (mNextPoint.x < mBase->getPosition().x) {
		mBase->setRotation(mBase->getRotation()  -mRotationAngle);
	}
	else
		mBase->setRotation(mBase->getRotation() + mRotationAngle);
}

void AI::update(sf::Time dt) {

	nextPoint.setPosition(mNextPoint);

	if (mPathFindMap == nullptr) {
		calculatePathMap();
		calculateRandomPath();
		if (!mCurrentPath.empty()) {
			mNextPoint = mCurrentPath.top();
			mCurrentPath.pop();
		}	
		calculateRotation();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		calculateRotation();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
		float distToNext = sqrt((mBase->getPosition().x - mNextPoint.x)*(mBase->getPosition().x - mNextPoint.x) + (mBase->getPosition().y - mNextPoint.y)*(mBase->getPosition().y - mNextPoint.y));
		if (distToNext < 10.f) {
			if (!mCurrentPath.empty()) {
				mNextPoint = mCurrentPath.top();
				mCurrentPath.pop();
			}
			calculateRotation();
		}
		else {
			//calculateRotation();
			if (!MoveX(dt.asSeconds())) {
				calculatePathMap();
				calculateRandomPath();
				if (!mCurrentPath.empty()) {
					mNextPoint = mCurrentPath.top();
					mCurrentPath.pop();
				}
				calculateRotation();
			}
		}
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
 
	printMatrix(mPathFindMap, mWidth, mHeight);
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
	//std::cout << toInsert.x << ' ' << toInsert.y << '\n';
	while (cost > 0) {
		cost--;

		for (int i = 0; i < 4; ++i) {
			startPoint.x += dx[i];
			startPoint.y += dy[i];

			if (mPathFindMap[(int)(startPoint.x)][(int)(startPoint.y)] == cost) {
				toInsert.y = (startPoint.x * mTileLength) + mTileLength / 2.f;
				toInsert.x = (startPoint.y * mTileLength) + mTileLength / 2.f;
				mCurrentPath.push(toInsert);
				//std::cout << toInsert.x << ' ' << toInsert.y << '\n';
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