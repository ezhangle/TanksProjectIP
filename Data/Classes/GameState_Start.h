#pragma once

#include "GameState.h"

class GameState_Start
	: public GameState
{
public:
													

public:
													GameState_Start(Game *game);

	void											draw(const sf::Time deltaTime);
	void											update(const sf::Time deltaTime);
	void											handleInput();
	void											handleEvents();
	void											handleRealTimeInput();

private:
	sf::View										mView;

private:


};