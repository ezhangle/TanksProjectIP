#include "MapButton.h"

MapButton::MapButton(sf::Vector2f position, std::string text, size_t charSize, std::string path_characters, std::string path_objects)
	: loadPath_characters(path_characters)
	, loadPath_objects(path_objects)
	, TextButton(position, text, charSize, TextButton::Action::none)
{

}