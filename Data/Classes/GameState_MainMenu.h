#ifndef GAMESTATE_MAINMENU_H

#define GAMESTATE_MAINMENU_H


//CUSTOM CLASSES AND OTHER HELPERS
#include "GameState.h"
#include "TextButton.h"
#include "Selector.h"


//SFML LIBRARIES
#include "SFML\Graphics\View.hpp"

//STL LIBRARIES


class GameState_MainMenu
	: public GameState
{
public:



public:
													GameState_MainMenu();
													

	void											draw();
	void											buildGUI();
	void											update(const sf::Time deltaTime);
	void											handleInput();
	void											handleEvents();
	void											handleRealTimeInput();
	void											rePositionButtons(sf::Vector2u &currentPosition, sf::Vector2u &newPosition);
			

private:
	Game*											game;
	std::vector<TextButton>							mButtons;
	Selector<TextButton>							mSelector;


private:
	
};


#endif