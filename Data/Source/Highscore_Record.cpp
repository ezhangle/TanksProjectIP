#include "Highscore_Record.h"

highscore_Record::highscore_Record(sf::Font &font)
	: name("\0", font, 30)
	, score("\0", font, 30)
	, identifier(0)
{

};