#include "GameState_GameBuild.h"

GameState_GameBuild::GameState_GameBuild()
	: game(Game::get())
	, mBorderTeamOne(game->mTextures.get(Texture::border_Full))
	, mBorderTeamTwo(game->mTextures.get(Texture::border_Full))
	, mTextTeamOne("Team 1", game->mFonts.get(Font::VanillaExtractRegular), 20)
	, mTextTeamTwo("Team 2", game->mFonts.get(Font::VanillaExtractRegular), 20)
	, mTextMap("Map", game->mFonts.get(Font::VanillaExtractRegular), 20)
	, mBorderMapSelector(game->mTextures.get(Texture::border_Half))
	, mTip1("Tip: Use the mouse to navigate this menu, it's a lot faster.", game->mFonts.get(Font::VanillaExtractRegular), 20)
{
	mTextMap.setPosition(920.0f, 70.0f);
	mTextTeamOne.setPosition(200.0f, 70.0f);
	mTextTeamTwo.setPosition(550.0f, 70.0f);
	mBorderTeamOne.setPosition(100.0f, 100.0f);
	mBorderTeamTwo.setPosition(450.0f, 100.0f);
	mBorderMapSelector.setPosition(800.0f, 100.0f);
	mTip1.setPosition(sf::Vector2f(30.0f, 30.0f));
	buildGUI();
}

void GameState_GameBuild::buildGUI()
{
	AddButton addTeamOne(sf::Vector2f(mBorderTeamOne.getGlobalBounds().left + 10.0f, mBorderTeamOne.getGlobalBounds().top + 5.0f), "+", 40, AddButton::Action::addEntity, mTeamOne);
	AddButton addTeamTwo(sf::Vector2f(mBorderTeamTwo.getGlobalBounds().left + 10.0f, mBorderTeamTwo.getGlobalBounds().top + 5.0f), "+", 40, AddButton::Action::addEntity, mTeamOne);
	AddButton back(sf::Vector2f(game->mWindow.getSize().x - 75.0f, game->mWindow.getSize().y - 75.0f), "Back", 20, AddButton::Action::back, mTeamOne);

	mButtons.push_back(addTeamOne);
	mButtons.push_back(addTeamTwo);
	mButtons.push_back(back);
}

void GameState_GameBuild::update(sf::Time deltaTime)
{
	handleInput();
}

void GameState_GameBuild::draw()
{
	game->mWindow.draw(game->mBackground);
	game->mWindow.draw(mBorderTeamOne);
	game->mWindow.draw(mBorderTeamTwo);
	game->mWindow.draw(mBorderMapSelector);
	game->mWindow.draw(mTextTeamOne);
	game->mWindow.draw(mTextTeamTwo);
	game->mWindow.draw(mTextMap);
	game->mWindow.draw(mTip1);

	for each (AddButton button in mButtons)
	{
		game->mWindow.draw(button.getText());
	}

}

void GameState_GameBuild::handleInput()
{
	handleRealTimeInput();
	handleEvents();
}

void GameState_GameBuild::handleEvents()
{
	sf::Event eventToBeHandled;
	while (game->mWindow.pollEvent(eventToBeHandled))
	{
		switch (eventToBeHandled.type)
		{
			default:break;
		}
	}
}

void GameState_GameBuild::handleRealTimeInput()
{
	for each (AddButton button in mButtons)
	{
		if (button.isSpriteClicked())
		{
			button.triggerAction();
			addEntity(1);
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

void GameState_GameBuild::rePositionButtons(sf::Vector2u & currentPosition, sf::Vector2u & newPosition)
{
}

void GameState_GameBuild::addEntity(size_t team)
{
	switch (team)
	{
		case 1:
		{
			AddButton addPlayer1(mButtons[1].getText().getPosition(), "Player 1", 20, AddButton::Action::addPlayer1, mTeamOne);
			AddButton addPlayer2(mButtons[1].getText().getPosition() + sf::Vector2f(0.0f, 30.0f), "Player 2", 20, AddButton::Action::addPlayer2, mTeamOne);
			AddButton addAI_Easy(mButtons[1].getText().getPosition() + sf::Vector2f(0.0f, 60.0f), "AI(easy)", 20, AddButton::Action::addAI_easy, mTeamOne);
			AddButton addAI_Medium(mButtons[1].getText().getPosition() + sf::Vector2f(0.0f, 90.0f), "AI(medium)", 20, AddButton::Action::addAI_medium, mTeamOne);
			AddButton addAI_Hard(mButtons[1].getText().getPosition() + sf::Vector2f(0.0f, 120.0f), "AI(hard)", 20, AddButton::Action::addAI_hard, mTeamOne);
			mButtons.push_back(addPlayer1);
			mButtons.push_back(addPlayer2);
			mButtons.push_back(addAI_Easy);
			mButtons.push_back(addAI_Medium);
			mButtons.push_back(addAI_Hard);
		}

		case 2:
		{
			AddButton addPlayer1(mButtons.back().getText().getPosition(), "Player 1", 20, AddButton::Action::addPlayer1, mTeamTwo);
			AddButton addPlayer2(mButtons.back().getText().getPosition() + sf::Vector2f(0.0f, 30.0f), "Player 2", 20, AddButton::Action::addPlayer2, mTeamTwo);
			AddButton addAI_Easy(mButtons.back().getText().getPosition() + sf::Vector2f(0.0f, 60.0f), "AI(easy)", 20, AddButton::Action::addAI_easy, mTeamTwo);
			AddButton addAI_Medium(mButtons.back().getText().getPosition() + sf::Vector2f(0.0f, 90.0f), "AI(medium)", 20, AddButton::Action::addAI_medium, mTeamTwo);
			AddButton addAI_Hard(mButtons.back().getText().getPosition() + sf::Vector2f(0.0f, 120.0f), "AI(hard)", 20, AddButton::Action::addAI_hard, mTeamTwo);
			mButtons.push_back(addPlayer1);
			mButtons.push_back(addPlayer2);
			mButtons.push_back(addAI_Easy);
			mButtons.push_back(addAI_Medium);
			mButtons.push_back(addAI_Hard);
		}
	}

	
}