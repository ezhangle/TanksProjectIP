#pragma once
#include "GameState.h"
#include "Button.h"
#include "Selector.h"
#include "Game.h"

class GameState_Options
	: public GameState
{
public:


public:
													GameState_Options();
													~GameState_Options();

	void											buildGUI();
	void											update(const sf::Time deltaTime);
	void											draw();
	void											handleInput();
	void											handleEvents();
	void											handleRealTimeInput();

private:
	Game*											game;
	std::vector<Button>								mButtonVector;
	Selector										mSelector;
	sf::Sprite										mTitle;
	sf::Sprite										mBackground;
	sf::View										mView;

private:


};