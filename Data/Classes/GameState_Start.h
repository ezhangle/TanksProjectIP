#pragma once

#include "GameState.h"

class GameState_Start
	: public GameState
{
private:
	sf::View										mView;

private:
	void											draw(sf::Time deltaTime);
	void											update(sf::Time deltaTime);
	void											handleInput();

public:
													GameState_Start();
													~GameState_Start();

public:


};