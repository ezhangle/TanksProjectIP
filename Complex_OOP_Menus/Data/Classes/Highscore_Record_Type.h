#pragma once
#include <SFML/Graphics/Text.hpp>
#include "Game.h"

class highscore_Record
{
public:
	sf::Text										name;
	sf::Text										score;
	unsigned int									identifier;

public:
													highscore_Record(sf::Font &font);
	
};