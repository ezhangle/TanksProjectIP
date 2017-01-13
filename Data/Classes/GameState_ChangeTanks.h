#pragma once

#include "GameState.h"
#include "GameState_GameBuild.h"
#include "Game.h"
#include "PlayerTank.h"


class GameState_ChangeTanks
	: public GameState
{
public:


public:

	GameState_ChangeTanks();

	void											buildGUI();
	void											update(sf::Time deltaTime);
	void											draw();
	void											handleInput();
	void											handleEvents();
	void											handleRealTimeInput();
	void											rePositionButtons(sf::Vector2u &currentPosition, sf::Vector2u &newPosition);

private:
	Game*											gamePointer;
	GameState_GameBuild*							gameBuildPointer;
	std::vector<TextButton>							mButtons;
	Selector<TextButton>							mButtons_Selector;
	PlayerTank										player1;
	PlayerTank										player2;

private:



};