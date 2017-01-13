#include "GameState_ChangeTanks.h"


GameState_ChangeTanks::GameState_ChangeTanks()
	: gamePointer(Game::get())
	, gameBuildPointer(GameState_GameBuild::get())
	, mButtons_Selector(gamePointer->mTextures.get(Texture::button_Selector), sf::Vector2f(20.0f, gamePointer->mWindow.getSize().y - 270.0f), 50.0f, mButtons)
	, player1(sf::Vector2f(100.0f, 60.0f), "Player 1 Tank")
	, player2(sf::Vector2f(gamePointer->mWindow.getSize().x - 600.0f, 60.0f), "Player 2 Tank")
{


	buildGUI();

	mButtons_Selector.mNumberOfButtons = mButtons.size();
	mButtons_Selector.mButtons = mButtons;
	mButtons_Selector.mSelectedButton = &mButtons[0];
}

void GameState_ChangeTanks::buildGUI()
{
	TextButton back(sf::Vector2f(50.0f, gamePointer->mWindow.getSize().y - 50.0f), "Back to team builder", 20, TextButton::Action::back);
	mButtons.push_back(back);
}

void GameState_ChangeTanks::update(sf::Time deltaTime)
{
	handleInput();
}

void GameState_ChangeTanks::draw()
{
	gamePointer->mWindow.draw(gamePointer->mBackground);
	gamePointer->mWindow.draw(player1.mBorder);
	gamePointer->mWindow.draw(player1.mMainText);
	gamePointer->mWindow.draw(player2.mBorder);
	gamePointer->mWindow.draw(player2.mMainText);

	for each (TextButton button in mButtons)
		gamePointer->mWindow.draw(button.getText());
	for each (sf::Text text in player1.mDisplayStats)
		gamePointer->mWindow.draw(text);
	for each (sf::Text text in player2.mDisplayStats)
		gamePointer->mWindow.draw(text);
	for each (TankButton tankButton in player1.mTanks)
		gamePointer->mWindow.draw(tankButton.getText());
	for each (TankButton tankButton in player2.mTanks)
		gamePointer->mWindow.draw(tankButton.getText());
	for each (sf::Text plusStats in player1.mTanks_Selector.mSelectedButton->mTextData)
		gamePointer->mWindow.draw(plusStats);
	for each (sf::Text plusStats in player2.mTanks_Selector.mSelectedButton->mTextData)
		gamePointer->mWindow.draw(plusStats);

}

void GameState_ChangeTanks::handleInput()
{
	handleEvents();
	handleRealTimeInput();
}

void GameState_ChangeTanks::handleEvents()
{
	sf::Event eventToBeHandled;

	while (gamePointer->mWindow.pollEvent(eventToBeHandled))
	{
		switch (eventToBeHandled.type)
		{
			case sf::Event::KeyPressed:
			{
				switch (eventToBeHandled.key.code)
				{
					default:break;
				}
				break;
			}

			case sf::Event::MouseButtonPressed:
			{
				switch (eventToBeHandled.mouseButton.button)
				{
					case sf::Mouse::Left:
					{
						if (mButtons_Selector.mSelectedButton != nullptr)
						{
							sf::Text mText = mButtons_Selector.mSelectedButton->getText();
							sf::FloatRect buttonSpriteRect(mText.getGlobalBounds());

							if (buttonSpriteRect.contains(eventToBeHandled.mouseButton.x, eventToBeHandled.mouseButton.y))
								mButtons_Selector.mSelectedButton->triggerAction();
						}

						break;
					}

					default:break;
				}

				break;
			}

			default:break;
		}
	}
}

void GameState_ChangeTanks::handleRealTimeInput()
{
	for (unsigned int i = 0; i < mButtons.size(); i++)
	{
		if (mButtons[i].isSpriteSelected())
		{
			if (mButtons[i].getText().getFillColor() == sf::Color::White)
			{
				//mButtonSelector.mSelectedButton->getText().setFillColor(sf::Color::White);
				mButtons[i].getText().setFillColor(sf::Color::Red);
				mButtons_Selector.mSelectedButton = &mButtons[i];
			}
		}
		else
			mButtons[i].getText().setFillColor(sf::Color::White);
	}

	for (unsigned int i = 0; i < player1.mTanks.size(); i++)
	{
		if (player1.mTanks[i].isSpriteClicked())
		{
			player1.mTanks_Selector.mSelectedButton->getText().setFillColor(sf::Color::White);
			player1.mTanks_Selector.mSelectedButton = &player1.mTanks[i];
			player1.mTanks_Selector.mSelectedButton->getText().setFillColor(sf::Color::Red);

			gameBuildPointer->teamOne.player1TankData.mDamage = player1.mTanks_Selector.mSelectedButton->tankData.mDamage;
			gameBuildPointer->teamOne.player1TankData.mSpeed = player1.mTanks_Selector.mSelectedButton->tankData.mSpeed;
			gameBuildPointer->teamOne.player1TankData.mHealth = player1.mTanks_Selector.mSelectedButton->tankData.mHealth;
			gameBuildPointer->teamOne.player1TankData.mTextureIdentifier = player1.mTanks_Selector.mSelectedButton->tankData.mTextureIdentifier;


			gameBuildPointer->teamTwo.player1TankData.mDamage = player1.mTanks_Selector.mSelectedButton->tankData.mDamage;
			gameBuildPointer->teamTwo.player1TankData.mSpeed = player1.mTanks_Selector.mSelectedButton->tankData.mSpeed;
			gameBuildPointer->teamTwo.player1TankData.mHealth = player1.mTanks_Selector.mSelectedButton->tankData.mHealth;
			gameBuildPointer->teamTwo.player1TankData.mTextureIdentifier = player1.mTanks_Selector.mSelectedButton->tankData.mTextureIdentifier;

		}
	}

	for (unsigned int i = 0; i < player2.mTanks.size(); i++)
	{
		if (player2.mTanks[i].isSpriteClicked())
		{
			player2.mTanks_Selector.mSelectedButton->getText().setFillColor(sf::Color::White);
			player2.mTanks_Selector.mSelectedButton = &player2.mTanks[i];
			player2.mTanks_Selector.mSelectedButton->getText().setFillColor(sf::Color::Red);


			gameBuildPointer->teamOne.player2TankData.mDamage = player2.mTanks_Selector.mSelectedButton->tankData.mDamage;
			gameBuildPointer->teamOne.player2TankData.mSpeed = player2.mTanks_Selector.mSelectedButton->tankData.mSpeed;
			gameBuildPointer->teamOne.player2TankData.mHealth = player2.mTanks_Selector.mSelectedButton->tankData.mHealth;
			gameBuildPointer->teamOne.player2TankData.mTextureIdentifier = player2.mTanks_Selector.mSelectedButton->tankData.mTextureIdentifier;


			gameBuildPointer->teamTwo.player2TankData.mDamage = player2.mTanks_Selector.mSelectedButton->tankData.mDamage;
			gameBuildPointer->teamTwo.player2TankData.mSpeed = player2.mTanks_Selector.mSelectedButton->tankData.mSpeed;
			gameBuildPointer->teamTwo.player2TankData.mHealth = player2.mTanks_Selector.mSelectedButton->tankData.mHealth;
			gameBuildPointer->teamTwo.player2TankData.mTextureIdentifier = player2.mTanks_Selector.mSelectedButton->tankData.mTextureIdentifier;
		}
	}
}

void GameState_ChangeTanks::rePositionButtons(sf::Vector2u& currentPosition, sf::Vector2u& newPosition)
{

}