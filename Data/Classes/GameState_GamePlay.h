#pragma once

//CUSTOM CLASSES AND OTHER HELPERS
#include "GameState.h"
#include <SFML\Graphics\View.hpp>
#include "Game.h"

//SFML LIBRARIES


//STL LIBRARIES

class GameState_GamePlay
	: public GameState
{
public:


public:
													GameState_GamePlay();
													~GameState_GamePlay();

	void											update(const sf::Time deltaTime);
	void											draw();
	void											handleInput();
	void											handleEvents();
	void											handleRealTimeInput();
													
private:
	sf::View										mGameView;
	sf::View										mGUIView;
	Game*											game;

private:



};