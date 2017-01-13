#include "GameState_Play.h"
#include "GameState_MainMenu.h"

GameState_Play *GameState_Play::instance = nullptr;

GameState_Play::GameState_Play(std::string& mapObjectsPath, std::vector<Entity*>& entities)
	: game(Game::get())
	, gameOver("Game Over!", Game::get()->mFonts.get(Font::VanillaExtractRegular), 90)
	, mMapObjectsPath(mapObjectsPath)
	, drawGameOver(false)
{
	gameOver.setPosition(400.0f, 300.0f);
	gameOver.setFillColor(sf::Color::Black);
	//gameOver.setScale(3.0f, 3.0f);

	for each (Entity* entity in entities)
	{
		mEntities.push_back(entity);
	}

	buildGUI();

	instance = this;
}

void GameState_Play::buildGUI()
{
	mMap = new Map(mMapObjectsPath, mEntities);
}

void GameState_Play::update(sf::Time deltaTime)
{


	if (GameState_GameBuild::get()->teamOne.numberOfMembers == 0 || GameState_GameBuild::get()->teamTwo.numberOfMembers == 0)
	{
		drawGameOver = true;
		if (timeUntilRestart.getElapsedTime() >= sf::seconds(8.0f))
		{
			while (game->getActiveState() != nullptr)
				game->popState();

			game->pushState(new GameState_MainMenu());
		}
	}

	mMap->update(deltaTime);
	handleInput();
}

void GameState_Play::draw()
{
	mMap->draw(&(game->mWindow));
	if(drawGameOver)
		Game::get()->mWindow.draw(gameOver);
}

void GameState_Play::handleInput()
{
	handleEvents();
	handleRealTimeInput();
}

void GameState_Play::handleEvents()
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
					case sf::Keyboard::Escape:
					{
						while (game->getActiveState() != nullptr)
							game->popState();

						game->pushState(new GameState_MainMenu());
						break;
					}
					

					default:break;
				}

			}
			
			default:break;
		}
	}
}


void GameState_Play::handleRealTimeInput()
{

}

void GameState_Play::rePositionButtons(sf::Vector2u &currentPosition, sf::Vector2u &newPosition)
{
	//THIS IS USELESS SHIT, BUT I CAN'T REMOVE IT BCUZ I WOULD HAVE TO REMOVE A **LOT** OF LEFTOVER CODE...
}