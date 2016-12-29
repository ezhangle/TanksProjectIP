#pragma once
#include "GameState.h"
#include "Button.h"
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


private:
	Game*											game;
	std::vector<Button>								mButtonVector;
	Selector										mSelector;
	sf::Sprite										mTitle;
	sf::Sprite										mBackground;
	sf::View										mView;

private:



};