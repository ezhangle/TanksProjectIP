#ifndef GAMESTATE_MAINMENU_H

#define GAMESTATE_MAINMENU_H


//CUSTOM CLASSES AND OTHER HELPERS
#include "GameState.h"

//SFML LIBRARIES


//STL LIBRARIES


class GameState_MainMenu
	: private GameState
{
public:


public:
													GameState_MainMenu();
													~GameState_MainMenu();

private:
	

private:
	virtual void									draw(sf::Time deltaTime);
	virtual void									update(sf::Time deltaTime);
	virtual void									handleInput();
};


#endif