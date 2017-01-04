#include "AddButton.h"

AddButton::AddButton(sf::Vector2f initialPosition, std::string text, size_t characterSize, Action action, std::vector<Tank> &tanks)
	: TextButton(initialPosition, text, characterSize, TextButton::Action::none)
	, mAction(action)
	, mTanks(tanks)
{

}

AddButton::AddButton(sf::Vector2f initialPosition, Action action, std::vector<Tank> &tanks)
	: TextButton(initialPosition, "+", 20, TextButton::Action::none)
	, mAction(action)
	, mTanks(tanks)
{

}

void AddButton::triggerAction()
{
	switch (mAction)
	{
		case Action::back:
		{
			Game::get()->popState();
			break;
		}



		default:break;
	}
}

