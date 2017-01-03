#pragma once
#include "GameState.h"
#include "Game.h"
#include "VSyncButton.h"
#include "Selector.h"




class GameState_Options_Vsync
	: public GameState
{
public:


public:
													GameState_Options_Vsync();
													~GameState_Options_Vsync();
	
	void											buildGUI();
	void											update(sf::Time deltaTime);
	void											draw();
	void											handleInput();
	void											handleEvents();
	void											handleRealTimeInput();
	void											rePositionButtons(sf::Vector2u &currentPosition, sf::Vector2u &newPosition);

private:
	Game*											game;
	std::vector<VSyncButton>						mButtons;
	Selector<VSyncButton>							mSelector;

	
private:



};