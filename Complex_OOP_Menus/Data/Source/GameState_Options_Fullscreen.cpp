#include "GameState_Options_Fullscreen.h"

GameState_Options_Fullscreen::GameState_Options_Fullscreen()
	: game(Game::get())
	, mSelector(game->mTextures.get(Texture::button_Selector), sf::Vector2f(20.0f, game->mWindow.getSize().y - 220.0f), 50.0f, mButtons)
{;
	buildGUI();
	mSelector.mNumberOfButtons = mButtons.size();
	mSelector.mButtons = mButtons;
	mSelector.mSelectedButton = &mButtons[0];
};

GameState_Options_Fullscreen::~GameState_Options_Fullscreen()
{
	
};

void GameState_Options_Fullscreen::buildGUI()
{
	FullscreenButton fullscreenButton(sf::Vector2f(75.0f, game->mWindow.getSize().y - 200.0f), "Fullscreen", 20, FullscreenButton::Action::changeFullscreen, 1);
	FullscreenButton windowedButton(sf::Vector2f(75.0f, game->mWindow.getSize().y - 150.0f), "Windowed", 20, FullscreenButton::Action::changeFullscreen, 0);
	FullscreenButton backButton(sf::Vector2f(75.0f, game->mWindow.getSize().y - 100.0f), "Back", 20, FullscreenButton::Action::back, 9);

	mButtons.push_back(fullscreenButton);
	mButtons.push_back(windowedButton);
	mButtons.push_back(backButton);

}

void GameState_Options_Fullscreen::update(sf::Time deltaTime)
{
	handleInput();
}

void GameState_Options_Fullscreen::draw()
{
	game->mWindow.draw(game->mBackground);
	game->mWindow.draw(mSelector.mSprite);
	for each (TextButton button in mButtons)
	{
		game->mWindow.draw(button.getText());
	}
}

void GameState_Options_Fullscreen::handleInput()
{
	handleEvents();
	handleRealTimeInput();
}

void GameState_Options_Fullscreen::handleEvents()
{
	sf::Event eventToBeHandled;
	while (game->mWindow.pollEvent(eventToBeHandled))
	{
		switch (eventToBeHandled.type)
		{
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
						mSelector.move(Movement::down);
						break;
					}

					case sf::Keyboard::Up:
					{
						mSelector.move(Movement::up);
						break;
					}

					default:
						break;
				}
			}


			default:
				break;
		}
	}
}

void GameState_Options_Fullscreen::handleRealTimeInput()
{

}

void GameState_Options_Fullscreen::rePositionButtons(sf::Vector2u & currentPosition, sf::Vector2u & newPosition)
{
}
