#include "GameState_Options_Resolution.h"

GameState_Options_Resolution::GameState_Options_Resolution()
	: game(Game::get())
	, mBackground(game->mTextures.get(Texture::background_Options))
	, mSelector(game->mTextures.get(Texture::button_Selector), sf::Vector2f(45.0f, game->mWindow.getSize().y - 300.0f), 50.0f, mButtonVector)
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


GameState_Options_Resolution::~GameState_Options_Resolution()
{
	
}

void GameState_Options_Resolution::buildGUI()
{
	Button button_1920x1080(sf::Vector2f(100.0f, game->mWindow.getSize().y - 300.0f), button::Action::none, game->mTextures.get(Texture::button_Resolution_1920x1080));
	Button button_1600x900(sf::Vector2f(100.0f, game->mWindow.getSize().y - 250.0f), button::Action::none, game->mTextures.get(Texture::button_Resolution_1600x900));
	Button button_1366x768(sf::Vector2f(100.0f, game->mWindow.getSize().y - 200.0f), button::Action::none, game->mTextures.get(Texture::button_Resolution_1366x768));
	Button button_1280x720(sf::Vector2f(100.0f, game->mWindow.getSize().y - 150.0f), button::Action::none, game->mTextures.get(Texture::button_resolution_1280x720));
	Button button_back(sf::Vector2f(100.0f, game->mWindow.getSize().y - 100.0f), button::Action::back, game->mTextures.get(Texture::button_Back));
	button_1920x1080.resolutionData = sf::Vector2u(1920, 1080);
	button_1600x900.resolutionData = sf::Vector2u(1600, 900);
	button_1366x768.resolutionData = sf::Vector2u(1366, 768);
	button_1280x720.resolutionData = sf::Vector2u(1280, 720);

	mButtonVector.push_back(button_1920x1080);
	mButtonVector.push_back(button_1600x900);
	mButtonVector.push_back(button_1366x768);
	mButtonVector.push_back(button_1280x720);
	mButtonVector.push_back(button_back);
}

void GameState_Options_Resolution::update(sf::Time deltaTime)
{
	handleInput();
}

void GameState_Options_Resolution::draw()
{
	game->mWindow.draw(mBackground);
	mSelector.draw();
	for each (Button button in mButtonVector)
	{
		game->mWindow.draw(button.mButtonSprite);
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
						sf::Vector2u newResolution(mSelector.mSelectedButton->resolutionData);
						if (newResolution.x != 0)
						{
							std::ofstream resolutionCFG("Assets/Config/resolutionCFG.txt");
							resolutionCFG.clear();
							resolutionCFG << newResolution.x << " " << newResolution.y;
							resolutionCFG.close();
						}
						else
						{
							mSelector.mSelectedButton->triggerAction();
						}
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

void GameState_Options_Resolution::handleRealTimeInput()
{

}
