#pragma once

#include "GameState.h"
#include "Tank.h"
#include "Map.h"
#include "Player.h"
#include "MapButton.h"
#include "MapSelector.h"
#include "Selector.h"
#include "Team.h"


class GameState_GameBuild
	: public GameState
	, private sf::NonCopyable
{
	static GameState_GameBuild						*instance;

public:


public:
	GameState_GameBuild();
	void											buildGUI();
	void											update(sf::Time deltaTime);
	void											draw();
	void											handleInput();
	void											handleEvents();
	void											handleRealTimeInput();
	void											rePositionButtons(sf::Vector2u &currentPosition, sf::Vector2u &newPosition);
	std::string&									getSelectedMapPath();
	std::vector<Entity*>*							getEntities();

private:
	Game*											game;

	sf::Sprite										mBorderMapSelector;
	sf::Sprite										mBorderMapPreview;

	sf::Text										mTip1;
	sf::Text										mTip2;
	sf::Text										mTextMap;

	Map*											map;

	MapSelector										mMapSelector;
	Selector<TextButton>							mButtonSelector;

	std::vector<TextButton>							mButtons;
	std::vector<MapButton>							mMaps;

	size_t											player1_team;
	size_t											player2_team;


	team											teamOne;
	team											teamTwo;


private:


public:
	static GameState_GameBuild* get()
	{
		if (instance == nullptr)
		{
			instance = new GameState_GameBuild();
		}

		return instance;
	}
};