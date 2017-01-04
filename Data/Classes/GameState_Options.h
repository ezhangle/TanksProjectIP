#pragma once
#include "GameState.h"
#include "TextButton.h"
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
	void											rePositionButtons(sf::Vector2u &currentPosition, sf::Vector2u &newPosition);

private:
	Game*											game;
	std::vector<TextButton>							mButtons;
	sf::Text										mRestartRequired;
	Selector<TextButton>							mSelector;

private:


};