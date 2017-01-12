#include "ResolutionButton.h"

ResolutionButton::ResolutionButton(sf::Vector2f initialPosition, Action action, sf::Vector2f resolutionData)
	: game(Game::get())
	, mResolutionData(resolutionData.x, resolutionData.y)
	, mAction(action)
	, TextButton(initialPosition, TextButton::Action::none)
{
}

ResolutionButton::ResolutionButton(sf::Vector2f initialPosition, std::string text, Action action, sf::Vector2f resolutionData)
	: game(Game::get())
	, mResolutionData(resolutionData.x, resolutionData.y)
	, mAction(action)
	, TextButton(initialPosition, text, TextButton::Action::none)
{
}

ResolutionButton::ResolutionButton(sf::Vector2f initialPosition, sf::Font & font, Action action, sf::Vector2f resolutionData)
	: game(Game::get())
	, mResolutionData(resolutionData.x, resolutionData.y)
	, mAction(action)
	, TextButton(initialPosition, font, TextButton::Action::none)
{
}

ResolutionButton::ResolutionButton(sf::Vector2f initialPosition, std::string text, size_t characterSize, Action action, sf::Vector2f resolutionData)
	: game(Game::get())
	, mResolutionData(resolutionData.x, resolutionData.y)
	, mAction(action)
	, TextButton(initialPosition, text, characterSize, TextButton::Action::none)
{
}

ResolutionButton::ResolutionButton(sf::Vector2f initialPosition, std::string text, sf::Font & font, Action action, sf::Vector2f resolutionData)
	: game(Game::get())
	, mResolutionData(resolutionData.x, resolutionData.y)
	, mAction(action)
	, TextButton(initialPosition, text, font, TextButton::Action::none)
{
}

ResolutionButton::ResolutionButton(sf::Vector2f initialPosition, std::string text, sf::Font & font, size_t characterSize, Action action, sf::Vector2f resolutionData)
	: game(Game::get())
	, mResolutionData(resolutionData.x, resolutionData.y)
	, mAction(action)
	, TextButton(initialPosition, text, font, characterSize, TextButton::Action::none)
{
}

void ResolutionButton::triggerAction()
{
	switch (mAction)
	{
		case Action::back:
		{
			game->popState();
			break;
		}

		case Action::changeResolution:
		{
			game->mWindow.setSize(mResolutionData);
			break;
		}


		default:break;
	}
}