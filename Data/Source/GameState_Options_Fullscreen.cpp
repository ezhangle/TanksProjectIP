#include "GameState_Options_Fullscreen.h"

GameState_Options_Fullscreen::GameState_Options_Fullscreen()
	: game(Game::get())
	, mBackground(game->mTextures.get(Texture::background_Options))
	, mSelector(game->mTextures.get(Texture::button_Selector), sf::Vector2f(45.0f, game->mWindow.getSize().y - 200.0f), 50.0f, mButtonVector)
	, mTitle(game->mTextures.get(Texture::title_Options))
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
};

GameState_Options_Fullscreen::~GameState_Options_Fullscreen()
{
	
};

void GameState_Options_Fullscreen::buildGUI()
{

	Button fullscreen(sf::Vector2f(100.0f, game->mWindow.getSize().y - 200.0f), button::Action::none, game->mTextures.get(Texture::button_Yes));
	Button windowed(sf::Vector2f(100.0f, game->mWindow.getSize().y - 150.0f), button::Action::none, game->mTextures.get(Texture::button_No));
	Button back(sf::Vector2f(100.0f, game->mWindow.getSize().y - 100.0f), button::Action::back, game->mTextures.get(Texture::button_Back));
	
	fullscreen.fullscreenData = 1;
	windowed.fullscreenData = 0;
	
	mButtonVector.push_back(fullscreen);
	mButtonVector.push_back(windowed);
	mButtonVector.push_back(back);
}

void GameState_Options_Fullscreen::update(sf::Time deltaTime)
{
	handleInput();
}

void GameState_Options_Fullscreen::draw()
{
	game->mWindow.draw(mBackground);
	mSelector.draw();
	for each (Button button in mButtonVector)
	{
		game->mWindow.draw(button.mButtonSprite);
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
						if (mSelector.mSelectedButton->fullscreenData != 2)
						{
							std::ofstream fullscreenCFG("Assets/Config/fullscreenCFG.txt");
							fullscreenCFG.clear();
							fullscreenCFG << mSelector.mSelectedButton->fullscreenData;
							fullscreenCFG.close();
						}

						else
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