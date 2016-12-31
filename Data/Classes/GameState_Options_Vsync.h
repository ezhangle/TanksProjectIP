#pragma once
#include "GameState.h"
#include "Game.h"
#include "Button.h"
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

private:
	Game*											game;
	std::vector<Button>								mButtonVector;
	Selector										mSelector;
	sf::Sprite										mBackground;
	sf::View										mView;
	
private:



};