#pragma once

#include "GameState.h"


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


private:



};