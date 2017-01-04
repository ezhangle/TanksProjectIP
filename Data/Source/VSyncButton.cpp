#include "VSyncButton.h"

VSyncButton::VSyncButton(sf::Vector2f initialPosition, Action action, bool vsyncData)
	: game(Game::get())
	, mVSync(vsyncData)
	, mAction(action)
	, TextButton(initialPosition, TextButton::Action::none)
{
}

VSyncButton::VSyncButton(sf::Vector2f initialPosition, std::string text, Action action, bool vsyncData)
	: game(Game::get())
	, mVSync(vsyncData)
	, mAction(action)
	, TextButton(initialPosition, text, TextButton::Action::none)
{
}

VSyncButton::VSyncButton(sf::Vector2f initialPosition, sf::Font & font, Action action, bool vsyncData)
	: game(Game::get())
	, mVSync(vsyncData)
	, mAction(action)
	, TextButton(initialPosition, font, TextButton::Action::none)
{
}

VSyncButton::VSyncButton(sf::Vector2f initialPosition, std::string text, size_t characterSize, Action action, bool vsyncData)
	: game(Game::get())
	, mVSync(vsyncData)
	, mAction(action)
	, TextButton(initialPosition, text, characterSize, TextButton::Action::none)
{
}

VSyncButton::VSyncButton(sf::Vector2f initialPosition, std::string text, sf::Font & font, Action action, bool vsyncData)
	: game(Game::get())
	, mVSync(vsyncData)
	, mAction(action)
	, TextButton(initialPosition, text, font, TextButton::Action::none)
{
}

VSyncButton::VSyncButton(sf::Vector2f initialPosition, std::string text, sf::Font & font, size_t characterSize, Action action, bool vsyncData)
	: game(Game::get())
	, mVSync(vsyncData)
	, mAction(action)
	, TextButton(initialPosition, text, font, characterSize, TextButton::Action::none)
{
}

void VSyncButton::triggerAction()
{
	switch (mAction)
	{
		case Action::back:
		{
			game->popState();
			break;
		}

		case Action::changeVSync:
		{
			std::ofstream vsyncCFG("Assets/Config/vsyncCFG.txt");
			vsyncCFG.clear();
			vsyncCFG << mVSync;
			vsyncCFG.close();
			game->mWindow.setVerticalSyncEnabled(mVSync);
			break;
		}


		default:break;
	}
}