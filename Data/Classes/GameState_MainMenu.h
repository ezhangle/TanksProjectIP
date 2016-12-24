#ifndef GAMESTATE_MAINMENU_H

#define GAMESTATE_MAINMENU_H


//CUSTOM CLASSES AND OTHER HELPERS
#include "GameState.h"
#include "Button.h"


//SFML LIBRARIES
#include "SFML\Graphics\View.hpp"

//STL LIBRARIES


class GameState_MainMenu
	: public GameState
{
public:


public:
													GameState_MainMenu(Game *game);

	void											draw(const sf::Time deltaTime);
	void											update(const sf::Time deltaTime);
	void											handleInput();
	void											handleEvents();
	void											handleRealTimeInput();
			

private:
	sf::View										mView;
	Button											ExitGame;


private:
	
};


#endif