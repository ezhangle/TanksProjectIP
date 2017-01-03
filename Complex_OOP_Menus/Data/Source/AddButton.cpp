#include "AddButton.h"

AddButton::AddButton(sf::Vector2f initialPosition, std::string text, size_t characterSize, Action action, std::vector<Tank> &tanks)
	: TextButton(initialPosition, "text", 20, TextButton::Action::none)
	, mAction(action)
	, mTanks(tanks)
{

}