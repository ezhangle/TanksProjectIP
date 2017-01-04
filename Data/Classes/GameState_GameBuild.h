#pragma once

#include "GameState.h"
#include "Tank.h"
#include "Map.h"
#include "AddButton.h"


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
	void											rePositionButtons(sf::Vector2u &currentPosition, sf::Vector2u &newPosition);
	void											addEntity(size_t team);


private:
	Game*											game;

	sf::Sprite										mBorderTeamOne;
	sf::Sprite										mBorderTeamTwo;

	sf::Sprite										mBorderMapSelector;
	sf::Sprite										mBorderMapPreview;

	sf::Text										mTextTeamOne;
	sf::Text										mTextTeamTwo;

	sf::Text										mTip1;
	sf::Text										mTextMap;




	std::vector<Tank>								mTeamOne;
	std::vector<Tank>								mTeamTwo;
	std::vector<AddButton>							mButtons;
	std::vector<Map>								mMap;


private:



};