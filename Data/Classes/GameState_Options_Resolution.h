#pragma once
#include "GameState.h"
#include "ResolutionButton.h"
#include "Selector.h"
#include "Game.h"





class GameState_Options_Resolution
	: public GameState
{
public:


public:
													GameState_Options_Resolution();
													~GameState_Options_Resolution();

	void											buildGUI();
	void											update(sf::Time deltaTime);
	void											draw();
	void											handleInput();
	void											handleEvents();
	void											handleRealTimeInput();
	void											rePositionButtons(sf::Vector2u &currentPosition, sf::Vector2u &newPosition);

private:
	Game*											game;
	std::vector<ResolutionButton>					mButtons;
	Selector<ResolutionButton>						mSelector;


private:



};