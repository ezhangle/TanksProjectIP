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
	TextButton backButton(sf::Vector2f(game->mWindow.getSize().x - 75.0f, game->mWindow.getSize().y - 75.0f), "Back", 20, TextButton::Action::back);
	TextButton addTeamOneButton(sf::Vector2f(mBorderTeamOne.getGlobalBounds().left + 225.0f, mBorderTeamOne.getGlobalBounds().top + 10.0f), "Add", 20, TextButton::Action::none);
	TextButton addTeamTwoButton(sf::Vector2f(mBorderTeamTwo.getGlobalBounds().left + 225.0f, mBorderTeamTwo.getGlobalBounds().top + 10.0f), "Add", 20, TextButton::Action::none);

	mButtons.push_back(addTeamTwoButton);
	mButtons.push_back(addTeamOneButton);
	mButtons.push_back(backButton);
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

	for each (TextButton button in mButtons)
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
	for each (TextButton button in mButtons)
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

void GameState_GameBuild::rePositionButtons(sf::Vector2u & currentPosition, sf::Vector2u & newPosition)
{
}
