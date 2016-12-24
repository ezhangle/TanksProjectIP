#include "GameState_MainMenu.h"

GameState_MainMenu::GameState_MainMenu(Game *game)
	: ExitGame(sf::Vector2f(0.0f, 0.0f), button::Action::exitGame)
{
	this->game = game;
	sf::Vector2f mWindowPosition = sf::Vector2f(this->game->mWindow.getSize());
	this->mView.setSize(mWindowPosition);
	mWindowPosition *= 0.5f;
	this->mView.setCenter(mWindowPosition);
};

void GameState_MainMenu::update(const sf::Time deltaTime)
{

}

void GameState_MainMenu::draw(const sf::Time deltaTime)
{
	this->game->mWindow.clear(sf::Color::Black);
	this->game->mWindow.draw(this->game->mBackground);
}

void GameState_MainMenu::handleInput()
{
	handleEvents();
	handleRealTimeInput();
}

void GameState_MainMenu::handleEvents()
{
	sf::Event eventToBeHandled;
	while (this->game->mWindow.pollEvent(eventToBeHandled))
	{
		switch (eventToBeHandled.type)
		{
			case sf::Event::Closed:
			{
				this->game->mWindow.close();
				break;
			}

			case sf::Event::Resized:
			{
				this->mView.setSize(eventToBeHandled.size.width, eventToBeHandled.size.height);
				this->game->mBackground.setPosition(this->game->mWindow.mapPixelToCoords(sf::Vector2i(0, 0)));
				this->game->mBackground.setScale(
					float(eventToBeHandled.size.width) / float(this->game->mBackground.getTexture()->getSize().x),
					float(eventToBeHandled.size.height) / float(this->game->mBackground.getTexture()->getSize().y)
				);
				break;
			}

			case sf::Event::KeyPressed:
			{
				switch (eventToBeHandled.key.code)
				{
					case sf::Keyboard::Escape:
					{
						this->game->popState();
						break;
					}
				}
			}

			default:
				break;
		}
	}
}

void GameState_MainMenu::handleRealTimeInput()
{
	
}
