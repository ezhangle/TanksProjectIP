#pragma once
#include "GameState.h"
#include "Game.h"
#include "Tank.h"
#include "Map.h"
#include "Button.h"

class GameState_GameBuild
	: public GameState
{
public:


public:
													GameState_GameBuild();
	void											buildGUI();
	void											update(sf::Time deltaTime);
	void											draw();
	void											handleInput();
	void											handleEvents();
	void											handleRealTimeInput();


private:
	Game*											game;
	sf::Sprite										mBackground;

	sf::Sprite										mBorderTeamOne;
	sf::Sprite										mBorderTeamTwo;

	sf::Sprite										mBorderMapSelector;
	sf::Sprite										mBorderMapPreview;

	sf::Text										mTextTeamOne;
	sf::Text										mTextTeamTwo;

	sf::Text										mTip1;
	sf::Text										mTextMap;

	sf::View										mView;

	std::vector<Tank>								mTeamOne;
	std::vector<Tank>								mTeamTwo;
	std::vector<Button>								mButtons;
	std::vector<Map>								mMap;


private:



};