#include "GameState_Options_Resolution.h"

GameState_Options_Resolution::GameState_Options_Resolution()
	: game(Game::get())
	, mSelector(game->mTextures.get(Texture::button_Selector), sf::Vector2f(20.0f, game->mWindow.getSize().y - 320.0f), 50.0f, mButtons)
{
	buildGUI();
	mSelector.mNumberOfButtons = mButtons.size();
	mSelector.mButtons = mButtons;
	mSelector.mSelectedButton = &mButtons[0];
};


GameState_Options_Resolution::~GameState_Options_Resolution()
{
	
}

void GameState_Options_Resolution::buildGUI()
{
	ResolutionButton button_1920x1080(sf::Vector2f(75.0f, game->mWindow.getSize().y - 300.0f), "1920x1080", 20, ResolutionButton::Action::changeResolution, sf::Vector2f(1920, 1080));
	ResolutionButton button_1600x900(sf::Vector2f(75.0f, game->mWindow.getSize().y - 250.0f), "1600x900", 20, ResolutionButton::Action::changeResolution, sf::Vector2f(1600, 900));
	ResolutionButton button_1366x768(sf::Vector2f(75.0f, game->mWindow.getSize().y - 200.0f), "1366x768", 20, ResolutionButton::Action::changeResolution, sf::Vector2f(1366, 768));
	ResolutionButton button_1280x720(sf::Vector2f(75.0f, game->mWindow.getSize().y - 150.0f), "1280x720", 20, ResolutionButton::Action::changeResolution, sf::Vector2f(1280, 720));
	ResolutionButton backButton(sf::Vector2f(75.0f, game->mWindow.getSize().y - 100.0f), "Back", 20, ResolutionButton::Action::back, sf::Vector2f(0, 0));

	mButtons.push_back(button_1920x1080);
	mButtons.push_back(button_1600x900);
	mButtons.push_back(button_1366x768);
	mButtons.push_back(button_1280x720);
	mButtons.push_back(backButton);
}

void GameState_Options_Resolution::update(sf::Time deltaTime)
{
	handleInput();
}

void GameState_Options_Resolution::draw()
{
	game->mWindow.draw(game->mBackground);
	game->mWindow.draw(mSelector.mSprite);
	for each (ResolutionButton button in mButtons)
	{
		game->mWindow.draw(button.getText());
	}
}

void GameState_Options_Resolution::handleInput()
{
	handleEvents();
	handleRealTimeInput();
}

void GameState_Options_Resolution::handleEvents()
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

					default:break;
				}
			}

			default:break;
		}
	}
}

void GameState_Options_Resolution::handleRealTimeInput()
{
	for each (ResolutionButton button in mButtons)
	{
		if (button.isSpriteClicked())
		{
			button.triggerAction();
			sf::Clock wait;
			sf::Time timer = sf::Time::Zero;
			timer = sf::seconds(0.15f);
			while (wait.getElapsedTime() < timer)
			{

			}
			wait.restart();
		}
	}
}

void GameState_Options_Resolution::rePositionButtons(sf::Vector2u & currentPosition, sf::Vector2u & newPosition)
{
}
