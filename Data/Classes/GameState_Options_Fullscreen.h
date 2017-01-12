#pragma once
#include "GameState.h"
#include "FullscreenButton.h"
#include "Selector.h"
#include "Game.h"



class GameState_Options_Fullscreen
	: public GameState
{
public:


public:
													GameState_Options_Fullscreen();
													~GameState_Options_Fullscreen();

	void											buildGUI();
	void											update(sf::Time deltaTime);
	void											draw();
	void											handleInput();
	void											handleEvents();
	void											handleRealTimeInput();
	void											rePositionButtons(sf::Vector2u &currentPosition, sf::Vector2u &newPosition);


private:
	Game*											game;
	std::vector<FullscreenButton>					mButtons;
	Selector<FullscreenButton>						mSelector;


private:



};