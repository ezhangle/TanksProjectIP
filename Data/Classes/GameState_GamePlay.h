#pragma once

//CUSTOM CLASSES AND OTHER HELPERS
#include "GameState.h"


//SFML LIBRARIES


//STL LIBRARIES

class GameState_GamePlay
	: public GameState
{
public:


public:
													GameState_GamePlay(Game *game);

	void											update(const sf::Time deltaTime);
	void											draw(const sf::Time deltaTime);
	void											handleInput();
	void											handleEvents();
	void											handleRealTimeInput();
													
private:
	sf::View										mGameView;
	sf::View										mGUIView;

private:



};