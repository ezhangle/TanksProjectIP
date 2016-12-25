#include "GameState_MainMenu.h"

#include <iostream>


GameState_MainMenu::GameState_MainMenu()
	: game(Game::get())
	, mBackground(game->mTextures.get(Texture::background_MainMenu))
	, mSelector(game->mTextures.get(Texture::button_Selector), sf::Vector2f(45.0f, game->mWindow.getSize().y - 300.0f), 50.0f, mButtonVector)
{
	sf::Vector2f mWindowPosition = sf::Vector2f(game->mWindow.getSize());
	mView.setSize(mWindowPosition);
	mView.setCenter(mWindowPosition * 0.5f);
	buildGUI();
	mSelector.mNumberOfButtons = mButtonVector.size();
	mSelector.mButtonVector = mButtonVector;
	mSelector.mSelectedButton = &mButtonVector[0];
};

void GameState_MainMenu::buildGUI()
{
	Button buttonPlay(sf::Vector2f(100.0f, game->mWindow.getSize().y - 300.0f), button::Action::play, game->mTextures.get(Texture::button_Play));
	Button buttonTankType(sf::Vector2f(100.0f, game->mWindow.getSize().y - 250.0f), button::Action::tankType, game->mTextures.get(Texture::button_TankType));
	Button buttonOptions(sf::Vector2f(100.0f, game->mWindow.getSize().y - 150.0f), button::Action::options, game->mTextures.get(Texture::button_Options));
	Button buttonHighscore(sf::Vector2f(100.0f, game->mWindow.getSize().y - 200.0f), button::Action::highscore, game->mTextures.get(Texture::button_Highscore));
	Button buttonExit(sf::Vector2f(100.0f, game->mWindow.getSize().y - 100.0f), button::Action::exit, game->mTextures.get(Texture::button_Exit));
	mButtonVector.push_back(buttonPlay);
	mButtonVector.push_back(buttonTankType);
	mButtonVector.push_back(buttonOptions);
	mButtonVector.push_back(buttonHighscore);
	mButtonVector.push_back(buttonExit);
}

void GameState_MainMenu::update(const sf::Time deltaTime)
{	
	handleInput();
}

void GameState_MainMenu::draw()
{
	game->mWindow.draw(mBackground);
	mSelector.draw();
	for each (Button btn in mButtonVector)
	{
		game->mWindow.draw(btn.mButtonSprite);
	}
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
				game->mWindow.close();
				break;
			}


			case sf::Event::KeyPressed:
			{
				switch (eventToBeHandled.key.code)
				{
					case sf::Keyboard::Return:
					{
						mSelector.mSelectedButton->triggerAction();
						break;
					}

					case sf::Keyboard::Down:
					{
						mSelector.move(Selector::Movement::down);
						break;
					}

					case sf::Keyboard::Up:
					{
						mSelector.move(Selector::Movement::up);
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
	for each (Button button in mButtonVector)
	{
		if (button.isSpriteClicked())
			button.triggerAction();
	}
}
