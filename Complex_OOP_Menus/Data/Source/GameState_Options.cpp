#include "GameState_Options.h"

GameState_Options::GameState_Options()
	: game(Game::get())
	, mSelector(game->mTextures.get(Texture::button_Selector), sf::Vector2f(20.0f, game->mWindow.getSize().y - 220.0f), 50.0f, mButtons)
	, mRestartRequired("Important: In order to apply any changed settings, a game restart is required", game->mFonts.get(Font::VanillaExtractRegular), 20)
{
	buildGUI();
	mRestartRequired.setPosition(75.0f, 50.0f);
	mSelector.mNumberOfButtons = mButtons.size();
	mSelector.mButtons = mButtons;
	mSelector.mSelectedButton = &mButtons[0];
}

GameState_Options::~GameState_Options()
{
	//delete game;
}

void GameState_Options::buildGUI()
{
	TextButton fullscrenButton(sf::Vector2f(75.0f, game->mWindow.getSize().y - 200.0f), "Fullscreen", 20, TextButton::Action::buildOptions_Fullscreen);
	TextButton vsyncButton(sf::Vector2f(75.0f, game->mWindow.getSize().y - 150.0f), "V-Sync", 20, TextButton::Action::buildOptions_VSync);
	TextButton backButton(sf::Vector2f(75.0f, game->mWindow.getSize().y - 100.0f), "Back", 20, TextButton::Action::back);
	
	mButtons.push_back(fullscrenButton);
	mButtons.push_back(vsyncButton);
	mButtons.push_back(backButton);
}

void GameState_Options::draw()
{
	game->mWindow.draw(game->mBackground);
	game->mWindow.draw(mSelector.mSprite);
	game->mWindow.draw(mRestartRequired);
	for each (TextButton button in mButtons)
	{
		game->mWindow.draw(button.getText());
	}
}

void GameState_Options::handleInput()
{
	handleEvents();
	handleRealTimeInput();
}

void GameState_Options::update(sf::Time deltaTime)
{
	handleInput();
}

void GameState_Options::handleEvents()
{
	sf::Event eventToBeHandled;

	while (game->mWindow.pollEvent(eventToBeHandled))
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
						mSelector.move(Movement::down);
						break;
					}

					case sf::Keyboard::Up:
					{
						mSelector.move(Movement::up);
						break;
					}
				}
			}
		}
	}
}

void GameState_Options::handleRealTimeInput()
{
	for each (TextButton button in mButtons)
	{
		if (button.isSpriteClicked())
			button.triggerAction();
	}
}

void GameState_Options::rePositionButtons(sf::Vector2u & currentPosition, sf::Vector2u & newPosition)
{
}
