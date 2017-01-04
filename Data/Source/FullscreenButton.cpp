#include "FullscreenButton.h"

FullscreenButton::FullscreenButton(sf::Vector2f initialPosition, Action action, size_t fullscreenData)
	: game(Game::get())
	, mFullscreenData(fullscreenData)
	, mAction(action)
	, TextButton(initialPosition, TextButton::Action::none)
{
}

FullscreenButton::FullscreenButton(sf::Vector2f initialPosition, std::string text, Action action, size_t fullscreenData)
	: game(Game::get())
	, mFullscreenData(fullscreenData)
	, mAction(action)
	, TextButton(initialPosition, text, TextButton::Action::none)
{
}

FullscreenButton::FullscreenButton(sf::Vector2f initialPosition, sf::Font & font, Action action, size_t fullscreenData)
	: game(Game::get())
	, mFullscreenData(fullscreenData)
	, mAction(action)
	, TextButton(initialPosition, font, TextButton::Action::none)
{
}

FullscreenButton::FullscreenButton(sf::Vector2f initialPosition, std::string text, size_t characterSize, Action action, size_t fullscreenData)
	: game(Game::get())
	, mFullscreenData(fullscreenData)
	, mAction(action)
	, TextButton(initialPosition, text, characterSize, TextButton::Action::none)
{
}

FullscreenButton::FullscreenButton(sf::Vector2f initialPosition, std::string text, sf::Font & font, Action action, size_t fullscreenData)
	: game(Game::get())
	, mFullscreenData(fullscreenData)
	, mAction(action)
	, TextButton(initialPosition, text, font, TextButton::Action::none)
{
}

FullscreenButton::FullscreenButton(sf::Vector2f initialPosition, std::string text, sf::Font & font, size_t characterSize, Action action, size_t fullscreenData)
	: game(Game::get())
	, mFullscreenData(fullscreenData)
	, mAction(action)
	, TextButton(initialPosition, text, font, characterSize, TextButton::Action::none)
{
}

void FullscreenButton::triggerAction()
{
	switch (mAction)
	{
	case Action::back:
	{
		game->popState();
		break;
	}

	case Action::changeFullscreen:
	{
		std::ofstream fullscreenCFG("Assets/Config/fullscreenCFG.txt");
		fullscreenCFG.clear();
		fullscreenCFG << mFullscreenData;
		fullscreenCFG.close();

		break;
	}


	default:break;
	}
}