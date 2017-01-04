#pragma once
#include "Tank.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <stack>



class AI : public Tank{
	struct LeePoint {
		int x;
		int y;
		int step = 1;
	};
	
	int dx[4] = { 0, -1, 0, 1 };
	int dy[4] = { 1, 0, -1, 0 };
public:
								AI(sf::Sprite* base, sf::Sprite* top, sf::Vector2f* pos, sf::Vector2f* vel, float health, float damage, size_t team);
								~AI();

	virtual void				update(sf::Time dt);
	virtual void				assignNewPoint();

	void						initMap();
	void						calculatePath(sf::Vector2f& toInsert);
	void						calculateRandomPath();
	void						calculatePathMap();
	void						calculateRotation();
	void						findNewTarget();
	bool						isProjectilePathClear();

public:
	float						mRotationAngle;

	std::stack<sf::Vector2f>	mCurrentPath;
	sf::Vector2f				mNextPoint;
	sf::Vector2f				mLastPoint;
	float						mDistToNextPoint;

	Tank*						mTarget;

	int							**mPathFindMap;
	float						mTileLength;
	int							mWidth;
	int							mHeight;
};