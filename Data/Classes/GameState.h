#ifndef GAMESTATE_H

#define GAMESTATE_H


//CUSTOM LIBRARIES AND OTHER HELPERS
#include "Game.h"


//SFML LIBRARIES
#include <SFML\System\Time.hpp>


class GameState
{

public:


public:
	virtual void									draw(sf::Time deltaTime) = 0;
	virtual void									update(sf::Time deltaTime) = 0;
	virtual void									handleInput() = 0;


private:


private:


};


#endif // !GAMESTATE_H
