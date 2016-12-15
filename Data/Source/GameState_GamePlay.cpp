#include "GameState_GamePlay.h"
#include "GameState_MainMenu.h"

GameState_GamePlay::GameState_GamePlay(Game *game)
{
	this->game = game;
	sf::Vector2f mWindowPosition = sf::Vector2f(this->game->mWindow.getSize());
	this->mGUIView.setSize(mWindowPosition);
	this->mGameView.setSize(mWindowPosition);
	mWindowPosition *= 0.5f;
	this->mGUIView.setCenter(mWindowPosition);
	this->mGameView.setCenter(mWindowPosition);
}

void GameState_GamePlay::update(sf::Time deltaTime)
{

}

void GameState_GamePlay::draw(sf::Time deltaTime)
{
	this->game->mWindow.setView(this->mGameView);
	this->game->mWindow.clear(sf::Color::Black);
	this->game->mWindow.draw(this->game->mBackground);
}

void GameState_GamePlay::handleInput()
{
	handleEvents();
	handleRealTimeInput();
}

void GameState_GamePlay::handleEvents()
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
				this->mGameView.setSize(eventToBeHandled.size.width, eventToBeHandled.size.height);
				this->game->mBackground.setPosition(this->game->mWindow.mapPixelToCoords(sf::Vector2i(0, 0)));
				this->game->mBackground.setScale(
					float(eventToBeHandled.size.width) / float(this->game->mBackground.getTexture()->getSize().x),
					float(eventToBeHandled.size.height) / float(this->game->mBackground.getTexture()->getSize().y)
				);
				break;
			}

			case sf::Event::LostFocus:
			{
				this->game->changeState(new GameState_MainMenu(game));
				break;
			}

			case sf::Event::KeyPressed:
			{
				switch (eventToBeHandled.key.code)
				{
					case sf::Keyboard::Escape:
					{
						this->game->changeState(new GameState_MainMenu(game));
						break;
					}
				}
			}

			default:
				break;
		}
	}
}

void GameState_GamePlay::handleRealTimeInput()
{

}