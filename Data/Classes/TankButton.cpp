#include "TankButton.h"

TankButton::TankButton(sf::Vector2f position, std::string text, size_t charSize, float hp, float damage, float speed, std::string textureIdentifier)
	: TextButton(position, text, 20, TextButton::Action::none)
	, tankData(hp, damage, speed, textureIdentifier)
{

}
