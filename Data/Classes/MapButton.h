#pragma once
#include "TextButton.h"

class MapButton
	: public TextButton
{
public:
	MapButton(sf::Vector2f position, std::string text, size_t charSize, std::string path_characters, std::string path_objects);

	std::string										loadPath_characters;
	std::string										loadPath_objects;
};