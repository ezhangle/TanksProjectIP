#pragma once

#include "GameState.h"
#include "Game.h"
#include <SFML/Graphics/View.hpp>

class GameState_Start
	: public GameState
{
public:
													

public:
													GameState_Start();

	void											draw();
	void											update(const sf::Time deltaTime);
	void											handleInput();
	void											handleEvents();
	void											handleRealTimeInput();

private:
	sf::View										mView;
	Game*											game;
private:


};