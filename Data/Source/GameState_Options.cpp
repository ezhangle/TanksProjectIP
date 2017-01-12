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
	mSelector.mSelectedButton->getText().setFillColor(sf::Color::Red);
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
	//game->mWindow.draw(mSelector.mSprite);
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

			case sf::Event::MouseButtonPressed:
			{
				switch (eventToBeHandled.mouseButton.button)
				{
					case sf::Mouse::Left:
					{
						if (mSelector.mSelectedButton->isSpriteSelected())
						{
							mSelector.mSelectedButton->triggerAction();
							sf::Clock timer;
							while (timer.getElapsedTime() < sf::seconds(0.15f))
							{

							}
						}

						break;
					}

					default:break;
				}

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
						mSelector.mSelectedButton->getText().setFillColor(sf::Color::White);
						mSelector.move(Movement::down);
						mSelector.mSelectedButton->getText().setFillColor(sf::Color::Red);
						break;
					}

					case sf::Keyboard::Up:
					{
						mSelector.mSelectedButton->getText().setFillColor(sf::Color::White);
						mSelector.move(Movement::up);
						mSelector.mSelectedButton->getText().setFillColor(sf::Color::Red);
						break;
					}
				}
			}
		}
	}
}

void GameState_Options::handleRealTimeInput()
{
	for (unsigned int i = 0; i < mButtons.size(); i++)
	{
		if (mButtons[i].getText().getFillColor() == sf::Color::White)
			if (mButtons[i].isSpriteSelected())
			{
				mSelector.mSelectedButton->getText().setFillColor(sf::Color::White);
				mButtons[i].getText().setFillColor(sf::Color::Red);
				mSelector.mSelectedButton = &mButtons[i];
			}
	}
}

void GameState_Options::rePositionButtons(sf::Vector2u & currentPosition, sf::Vector2u & newPosition)
{
}
