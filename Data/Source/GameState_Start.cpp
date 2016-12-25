//CUSTOM CLASSES AND OTHER HELPERS
#include "GameState_Start.h"
#include "GameState_MainMenu.h"

//SFML LIBRARIES


//STL LIBRARIES

GameState_Start::GameState_Start()
	: game(Game::get())
{
	sf::Vector2f mWindowPosition = sf::Vector2f(this->game->mWindow.getSize());
	this->mView.setSize(mWindowPosition);
	mWindowPosition *= 0.5f;
	this->mView.setCenter(mWindowPosition);
}


void GameState_Start::draw()
{
	this->game->mWindow.setView(this->mView);
	this->game->mWindow.clear(sf::Color::Black);
	//this->game->mWindow.draw(this->game->mBackground);
}


void GameState_Start::update(sf::Time deltaTime)
{

}


void GameState_Start::handleInput()
{
	handleEvents();
	handleRealTimeInput();
}

void GameState_Start::handleEvents()
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

			/*case sf::Event::Resized:
			{
				this->mView.setSize(eventToBeHandled.size.width, eventToBeHandled.size.height);
				this->game->mBackground.setPosition(this->game->mWindow.mapPixelToCoords(sf::Vector2i(0, 0)));
				this->game->mBackground.setScale(
					float(eventToBeHandled.size.width) / float(this->game->mBackground.getTexture()->getSize().x),
					float(eventToBeHandled.size.height) / float(this->game->mBackground.getTexture()->getSize().y)
				);
				break;
			}*/

			case sf::Event::LostFocus:
			{
				this->game->changeState(new GameState_MainMenu());
				break;
			}

			case sf::Event::KeyPressed:
			{
				switch (eventToBeHandled.key.code)
				{
					case sf::Keyboard::Escape:
					{
						this->game->changeState(new GameState_MainMenu());
						break;
					}
				}
			}

			default:
				break;
		}
	}
}

void GameState_Start::handleRealTimeInput()
{
	
}