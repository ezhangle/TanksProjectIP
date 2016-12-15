#ifndef GAMESTATE_H

#define GAMESTATE_H


//CUSTOM LIBRARIES AND OTHER HELPERS
#include "Game.h"


//SFML LIBRARIES
#include <SFML\System\Time.hpp>

class Game;

class GameState
{

public:
	Game*											game;

public:
	virtual void									draw(const sf::Time deltaTime) = 0;
	virtual void									update(const sf::Time deltaTime) = 0;
	virtual void									handleInput() = 0;
	virtual void									handleEvents() = 0;
	virtual void									handleRealTimeInput() = 0;

private:


private:


};


#endif // !GAMESTATE_H
