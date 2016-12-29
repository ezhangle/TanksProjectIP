#include "GameState_Options.h"

GameState_Options::GameState_Options()
	: game(Game::get())
	, mBackground(game->mTextures.get(Texture::background_Options))
	, mTitle(game->mTextures.get(Texture::title_Options))
	, mSelector(game->mTextures.get(Texture::button_Selector), sf::Vector2f(45.0f, game->mWindow.getSize().y - 250.0f), 50.0f, mButtonVector)
{
	mView.setSize(game->mWindow.getSize().x, game->mWindow.getSize().y);
	mBackground.setScale(game->mWindow.getSize().x / 1920.0f, game->mWindow.getSize().y / 1080.0f);
	sf::Vector2f mWindowPosition = sf::Vector2f(game->mWindow.getSize());
	mView.setSize(mWindowPosition);
	mView.setCenter(mWindowPosition * 0.5f);
	game->mWindow.setView(mView);
	buildGUI();
	mSelector.mNumberOfButtons = mButtonVector.size();
	mSelector.mButtonVector = mButtonVector;
	mSelector.mSelectedButton = &mButtonVector[0];
}

GameState_Options::~GameState_Options()
{
	//delete game;
}

void GameState_Options::buildGUI()
{
	Button resolution(sf::Vector2f(100.0f, game->mWindow.getSize().y - 250.0f), button::Action::options_resolution, game->mTextures.get(Texture::button_Options_Resolution));
	Button fullscreen(sf::Vector2f(100.0f, game->mWindow.getSize().y - 200.0f), button::Action::options_fullscreen, game->mTextures.get(Texture::button_Options_Fullscreen));
	Button vsync(sf::Vector2f(100.0f, game->mWindow.getSize().y - 150.0f), button::Action::options_vsync, game->mTextures.get(Texture::button_Options_Vsync));
	Button back(sf::Vector2f(100.0f, game->mWindow.getSize().y - 100.0f), button::Action::back, game->mTextures.get(Texture::button_Back));
	mButtonVector.push_back(resolution);
	mButtonVector.push_back(fullscreen);
	mButtonVector.push_back(vsync);
	mButtonVector.push_back(back);
}

void GameState_Options::draw()
{
	game->mWindow.draw(mBackground);
	mSelector.draw();
	for each (Button button in mButtonVector)
	{
		game->mWindow.draw(button.mButtonSprite);
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
						if (mSelector.mSelectedButton == &mButtonVector[0])
						{
							game->mWindow.setVerticalSyncEnabled(true);
						}
						
						if (mSelector.mSelectedButton == &mButtonVector[1])
						{
							game->mWindow.setVerticalSyncEnabled(false);
						}

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
		}
	}
}

void GameState_Options::handleRealTimeInput()
{

}