#include "GameState_GameBuild.h"

GameState_GameBuild::GameState_GameBuild()
	: game(Game::get())
	, mBackground(game->mTextures.get(Texture::background_MainMenu))
	, mBorderTeamOne(game->mTextures.get(Texture::border_Full))
	, mBorderTeamTwo(game->mTextures.get(Texture::border_Full))
	, mTextTeamOne("Team 1", game->mFonts.get(Font::VanillaExtractRegular), 20)
	, mTextTeamTwo("Team 2", game->mFonts.get(Font::VanillaExtractRegular), 20)
	, mTextMap("Map", game->mFonts.get(Font::VanillaExtractRegular), 20)
	, mBorderMapSelector(game->mTextures.get(Texture::border_Half))
	, mTip1("Tip: Use the mouse to navigate this menu, it's a lot faster.", game->mFonts.get(Font::VanillaExtractRegular), 20)
{
	mBackground.setScale(game->mWindow.getSize().x / 1920.0f, game->mWindow.getSize().y / 1080.0f);
	sf::Vector2f mWindowPosition = sf::Vector2f(game->mWindow.getSize());
	mView.setSize(mWindowPosition);
	mView.setCenter(mWindowPosition * 0.5f);
	game->mWindow.setView(mView);

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
	Button back(sf::Vector2f(game->mWindow.getSize().x - game->mTextures.get(Texture::button_Back).getSize().x + 150.0f, game->mWindow.getSize().y - 100.0f), button::Action::back, game->mTextures.get(Texture::button_Back));
	Button addTeamOne(sf::Vector2f(mBorderTeamOne.getGlobalBounds().left + 225.0f, mBorderTeamOne.getGlobalBounds().top + 10.0f), button::Action::none, game->mTextures.get(Texture::button_Add));
	Button addTeamTwo(sf::Vector2f(mBorderTeamTwo.getGlobalBounds().left + 225.0f, mBorderTeamTwo.getGlobalBounds().top + 10.0f), button::Action::none, game->mTextures.get(Texture::button_Add));
	
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
	game->mWindow.draw(mBackground);
	game->mWindow.draw(mBorderTeamOne);
	game->mWindow.draw(mBorderTeamTwo);
	game->mWindow.draw(mBorderMapSelector);
	game->mWindow.draw(mTextTeamOne);
	game->mWindow.draw(mTextTeamTwo);
	game->mWindow.draw(mTextMap);
	game->mWindow.draw(mTip1);

	for each (Button button in mButtons)
	{
		game->mWindow.draw(button.mButtonSprite);
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
	for each (Button button in mButtons)
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