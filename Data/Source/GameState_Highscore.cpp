#include "GameState_Highscore.h"

GameState_Highscore::GameState_Highscore()
	: game(Game::get())
	, mHelperText("Press Escape to go back", game->mFonts.get(Font::VanillaExtractRegular), 30)
	, mTitle("Top Scores : ", game->mFonts.get(Font::VanillaExtractRegular))
	, mHighscoreVector()

{
	std::ifstream highscoreCFG("Assets/Config/highscoreCFG.txt");
	highscoreCFG >> mNumberOfScores;
	mHelperText.setPosition(100.0f, game->mWindow.getSize().y - 100.0f);
	float deltaY = 100.0f;
	
	for (int i = 0; i < mNumberOfScores; i++)
	{
		highscore_Record newHS(game->mFonts.get(Font::VanillaExtractRegular));
		std::string helper;
		game = Game::get();
		highscoreCFG >> helper;
		newHS.name.setString(helper);
		highscoreCFG >> helper;
		newHS.score.setString(helper);
		newHS.identifier = i + 1;
		newHS.name.setFont(game->mFonts.get(Font::VanillaExtractRegular));
		newHS.score.setFont(game->mFonts.get(Font::VanillaExtractRegular));
		newHS.name.setPosition(150.0f, game->mWindow.getSize().y - deltaY);
		newHS.score.setPosition(800.0f, game->mWindow.getSize().y - deltaY);
		mHighscoreVector.push_back(newHS);
		deltaY += 30.0f;
	}


	highscoreCFG.close();
}

GameState_Highscore::~GameState_Highscore()
{

}

void GameState_Highscore::buildGUI()
{

}

void GameState_Highscore::draw()
{
	game->mWindow.draw(mHelperText);
	game->mWindow.draw(game->mBackground);
	for (int i = 0; i < mNumberOfScores; i++)
	{
		game->mWindow.draw(mHighscoreVector[i].name);
		game->mWindow.draw(mHighscoreVector[i].score);
	}
}

void GameState_Highscore::update(sf::Time deltaTime)
{
	handleInput();
}

void GameState_Highscore::handleInput()
{
	handleEvents();
	handleRealTimeInput();
}

void GameState_Highscore::handleEvents()
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
					case sf::Keyboard::Escape:
					{
						game->popState();
						break;
					}

					default:break;
				}
			}
			default:break;
		}
	}
}

void GameState_Highscore::handleRealTimeInput()
{

}

void GameState_Highscore::rePositionButtons(sf::Vector2u & currentPosition, sf::Vector2u & newPosition)
{
}
