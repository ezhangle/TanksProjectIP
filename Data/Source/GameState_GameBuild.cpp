#include "GameState_GameBuild.h"

#include <algorithm>


GameState_GameBuild *GameState_GameBuild::instance = nullptr;

GameState_GameBuild::GameState_GameBuild()
	: game(Game::get())
	, player1TankData(100.0, 15.0, 100.0, "tank1")
	, player2TankData(100.0, 15.0, 100.0, "tank1")
	, teamOne(sf::Vector2f(150.0f, 100.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(260.0f, 70.0f), 1, "Team 1", player1TankData, player2TankData)
	, teamTwo(sf::Vector2f(650.0f, 100.0f), sf::Vector2f(0.0f, 0.0f), sf::Vector2f(750.0f, 70.0f), 2, "Team 2", player1TankData, player2TankData)
	, mTextMap("Map", game->mFonts.get(Font::VanillaExtractRegular), 20)
	, mBorderMapSelector(game->mTextures.get(Texture::border_Half))
	, mTip1("Tip: Use the mouse to navigate this menu, it's a lot faster.", game->mFonts.get(Font::VanillaExtractRegular), 15)
	, mTip2("To change the map, hold left mouse button and drag the red button.", game->mFonts.get(Font::VanillaExtractRegular), 15)
	, mMapSelector(mMaps)
	, mButtonSelector(game->mTextures.get(Texture::button_Selector), sf::Vector2f(20.0f, game->mWindow.getSize().y - 270.0f), 50.0f, mButtons)

{

	//teamOne.mTeamMembers.resize(100);
	//teamTwo.mTeamMembers.resize(100);
	mTextMap.setPosition(1120.0f, 70.0f);
	mBorderMapSelector.setPosition(1000.0f, 100.0f);
	mTip1.setPosition(sf::Vector2f(30.0f, game->mWindow.getSize().y - 50.0f));
	mTip2.setPosition((sf::Vector2f(30.0f, game->mWindow.getSize().y - 25.0f)));
	buildGUI();
	mMapSelector.mNumberOfButtons = mMaps.size();
	mMapSelector.setSelected(mMaps[0]);

	mButtonSelector.mNumberOfButtons = mButtons.size();
	mButtonSelector.mButtons = mButtons;
	mButtonSelector.mSelectedButton = &mButtons[0];

	player1_team = 0;
	player2_team = 0;

	

	teamOne.mTeamMembers_Selector.mSelectedButton = nullptr;
	teamOne.mTeamMembers_Selector.mNumberOfButtons = teamOne.mTeamMembers.size();
	teamOne.mTeamMembers_Selector.mButtons = teamOne.mTeamMembers;
	

	teamTwo.mTeamMembers_Selector.mSelectedButton = nullptr;
	teamTwo.mTeamMembers_Selector.mButtons = teamTwo.mTeamMembers;
	teamTwo.mTeamMembers_Selector.mNumberOfButtons = teamTwo.mTeamMembers.size();

	instance = this;
}

void GameState_GameBuild::buildGUI()
{
	TextButton play(sf::Vector2f(game->mWindow.getSize().x - 200.0f, game->mWindow.getSize().y - 110.0f), "Play", 20, TextButton::Action::playGame);
	TextButton changeTanks(sf::Vector2f(game->mWindow.getSize().x - 200.0f, game->mWindow.getSize().y - 80.0f), "Change Tanks", 20, TextButton::Action::buildGamePlay_ChangeTanks);
	TextButton back(sf::Vector2f(game->mWindow.getSize().x - 200.0f, game->mWindow.getSize().y - 50.0f), "Back", 20, TextButton::Action::back);

	mButtons.push_back(play);
	mButtons.push_back(changeTanks);
	mButtons.push_back(back);

	teamOne.teamNumber = 1;
	teamTwo.teamNumber = 2;


	MapButton map_Plains(mBorderMapSelector.getPosition() + sf::Vector2f(15.0f, 15.0f), "Island", 20, "Assets/Maps/map1_Characters.tmap", "Assets/Maps/map1_Objects.tmap");
	MapButton map_Beach(mBorderMapSelector.getPosition() + sf::Vector2f(15.0f, 45.0f), "Beach", 20, "Assets/Maps/maptest_Characters.tmap", "Assets/Maps/map2_Objects.tmap");
	mMaps.push_back(map_Plains);
	mMaps.push_back(map_Beach);

	for each  (MapButton map in mMaps)
	{
		std::ofstream map_Characters(map.loadPath_characters);
		map_Characters.clear();
		map_Characters.close();
	}

}

void GameState_GameBuild::update(sf::Time deltaTime)
{
	teamOne_NumberOfMembers = teamOne.numberOfMembers;
	teamTwo_NumberOfMembers = teamTwo.numberOfMembers;

	if (Game::get()->getActiveState() == this) {
		handleInput();
		//mButtons[0].getText().setPosition(Game::get()->mWidth - game->mWindow.getSize().x/10.f, Game::get()->mHeight - game->mWindow.getSize().y/5.f);
	}
		
}

void GameState_GameBuild::draw()
{
	game->mWindow.draw(game->mBackground);
	game->mWindow.draw(mBorderMapSelector);
	game->mWindow.draw(mTextMap);
	game->mWindow.draw(mTip1);
	game->mWindow.draw(mTip2);
	game->mWindow.draw(teamOne.mBorder);
	game->mWindow.draw(teamOne.mText);
	game->mWindow.draw(teamTwo.mBorder);
	game->mWindow.draw(teamTwo.mText);

	for each (TextButton button in mButtons)
		game->mWindow.draw(button.getText());

	for each(AddButton button in teamOne.mAddButtons)
		game->mWindow.draw(button.getText());

	for each(AddButton button in teamTwo.mAddButtons)
		game->mWindow.draw(button.getText());

	for each(teamRecord teamMember in teamOne.mTeamMembers)
	{
		game->mWindow.draw(teamMember.mRemoveButton->getText());
		game->mWindow.draw(teamMember.mText);
	}

	for each(teamRecord teamMember in teamTwo.mTeamMembers)
	{
		game->mWindow.draw(teamMember.mRemoveButton->getText());
		game->mWindow.draw(teamMember.mText);
	}

	for each(MapButton button in mMaps)
		game->mWindow.draw(button.getText());
}

void GameState_GameBuild::handleInput()
{
	handleEvents();
	handleRealTimeInput();
}

void GameState_GameBuild::handleEvents()
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

				break;
			}

			case sf::Event::MouseButtonPressed:
			{
				switch (eventToBeHandled.mouseButton.button)
				{
					case sf::Mouse::Left:
					{
						if (teamOne.mAddButtons_Selector.mSelectedButton != nullptr)
						{
							sf::Text mText = teamOne.mAddButtons_Selector.mSelectedButton->getText();
							sf::FloatRect buttonSpriteRect(mText.getGlobalBounds());

							if (buttonSpriteRect.contains(eventToBeHandled.mouseButton.x, eventToBeHandled.mouseButton.y))
							{
								if (teamOne.mAddButtons_Selector.mSelectedButton->getText().getString() == "Player 1")
								{
									if (player1_team == 0)
									{
										teamOne.mAddButtons_Selector.mSelectedButton->triggerAction(teamOne);
										player1_team = 1;
									}
								}
								else if (teamOne.mAddButtons_Selector.mSelectedButton->getText().getString() == "Player 2")
								{
									if (player2_team == 0)
									{
										teamOne.mAddButtons_Selector.mSelectedButton->triggerAction(teamOne);
										player2_team = 1;
									}
								}
								else
									teamOne.mAddButtons_Selector.mSelectedButton->triggerAction(teamOne);
							}
						}

						if (teamTwo.mAddButtons_Selector.mSelectedButton != nullptr)
						{
							sf::Text mText = teamTwo.mAddButtons_Selector.mSelectedButton->getText();
							sf::FloatRect buttonSpriteRect(mText.getGlobalBounds());

							if (buttonSpriteRect.contains(eventToBeHandled.mouseButton.x, eventToBeHandled.mouseButton.y))
							{
								if (teamTwo.mAddButtons_Selector.mSelectedButton->getText().getString() == "Player 1")
								{
									if (player1_team == 0)
									{
										teamTwo.mAddButtons_Selector.mSelectedButton->triggerAction(teamTwo);
										player1_team = 2;
									}
								}
								else if (teamTwo.mAddButtons_Selector.mSelectedButton->getText().getString() == "Player 2")
								{
									if (player2_team == 0)
									{
										teamTwo.mAddButtons_Selector.mSelectedButton->triggerAction(teamTwo);
										player2_team = 2;
									}
								}
								else
									teamTwo.mAddButtons_Selector.mSelectedButton->triggerAction(teamTwo);
							}
						}

						if (teamOne.mTeamMembers_Selector.mSelectedButton != nullptr)
						{
							if(teamOne.mTeamMembers_Selector.mSelectedButton->mRemoveButton->isSpriteSelected())
								teamOne.mTeamMembers_Selector.mSelectedButton->mRemoveButton->triggerAction(teamOne, teamOne.mTeamMembers_Selector.mSelectedButton->index, player1_team, player2_team);
						}

						if (teamTwo.mTeamMembers_Selector.mSelectedButton != nullptr)
						{
							if (teamTwo.mTeamMembers_Selector.mSelectedButton->mRemoveButton->isSpriteSelected())
								teamTwo.mTeamMembers_Selector.mSelectedButton->mRemoveButton->triggerAction(teamTwo, teamTwo.mTeamMembers_Selector.mSelectedButton->index, player1_team, player2_team);
						}


						if (mButtonSelector.mSelectedButton != nullptr)
						{
							sf::Text mText = mButtonSelector.mSelectedButton->getText();
							sf::FloatRect buttonSpriteRect(mText.getGlobalBounds());

							if (buttonSpriteRect.contains(eventToBeHandled.mouseButton.x, eventToBeHandled.mouseButton.y))
								mButtonSelector.mSelectedButton->triggerAction();
						}	
							
					
								


						
					}


					default:break;
				}
			}

			default:break;
		}
	}
}

void GameState_GameBuild::handleRealTimeInput()
{
	for (unsigned int i = 0; i < mButtons.size(); i++)
	{
		if (mButtons[i].isSpriteSelected())
		{
			if (mButtons[i].getText().getFillColor() == sf::Color::White)
			{
				//mButtonSelector.mSelectedButton->getText().setFillColor(sf::Color::White);
				mButtons[i].getText().setFillColor(sf::Color::Red);
				mButtonSelector.mSelectedButton = &mButtons[i];
			}
		}
		else
			mButtons[i].getText().setFillColor(sf::Color::White);
	}

	for (unsigned int i = 0; i < teamOne.mAddButtons.size(); i++)
	{
		if (teamOne.mAddButtons[i].isSpriteSelected())
		{
			if (teamOne.mAddButtons[i].getText().getFillColor() == sf::Color::White)
			{
				teamOne.mAddButtons[i].getText().setFillColor(sf::Color::Red);
				teamOne.mAddButtons_Selector.mSelectedButton = &teamOne.mAddButtons[i];
			}
		}
		else
			teamOne.mAddButtons[i].getText().setFillColor(sf::Color::White);
	}

	for (unsigned int i = 0; i < teamTwo.mAddButtons.size(); i++)
	{
		if (teamTwo.mAddButtons[i].isSpriteSelected())
		{
			if (teamTwo.mAddButtons[i].getText().getFillColor() == sf::Color::White)
			{
				teamTwo.mAddButtons[i].getText().setFillColor(sf::Color::Red);
				teamTwo.mAddButtons_Selector.mSelectedButton = &teamTwo.mAddButtons[i];
			}
		}
		else
			teamTwo.mAddButtons[i].getText().setFillColor(sf::Color::White);
	}

	for (unsigned int i = 0; i < teamOne.mTeamMembers.size(); i++)
	{
		if (teamOne.mTeamMembers[i].mRemoveButton->isSpriteSelected())
		{
			if (teamOne.mTeamMembers[i].mRemoveButton->getText().getFillColor() == sf::Color(0, 0, 153))
			{
				teamOne.mTeamMembers[i].mRemoveButton->getText().setFillColor(sf::Color::Red);
				teamOne.mTeamMembers[i].mText.setFillColor(sf::Color::Red);
				teamOne.mTeamMembers_Selector.mSelectedButton = &teamOne.mTeamMembers[i];
			}
		}
		else
		{
			teamOne.mTeamMembers[i].mRemoveButton->getText().setFillColor(sf::Color(0, 0, 153));
			teamOne.mTeamMembers[i].mText.setFillColor(sf::Color(0, 0, 153));
		}
	}

	for (unsigned int i = 0; i < teamTwo.mTeamMembers.size(); i++)
	{
		if (teamTwo.mTeamMembers[i].mRemoveButton->isSpriteSelected())
		{
			if (teamTwo.mTeamMembers[i].mRemoveButton->getText().getFillColor() == sf::Color(0, 102, 51))
			{
				teamTwo.mTeamMembers[i].mText.setFillColor(sf::Color::Red);
				teamTwo.mTeamMembers[i].mRemoveButton->getText().setFillColor(sf::Color::Red);
				teamTwo.mTeamMembers_Selector.mSelectedButton = &teamTwo.mTeamMembers[i];
			}
		}
		else
		{
			teamTwo.mTeamMembers[i].mText.setFillColor(sf::Color(0, 102, 51));
			teamTwo.mTeamMembers[i].mRemoveButton->getText().setFillColor(sf::Color(0, 102, 51));
		}
	}


	for (unsigned int i = 0; i < mMaps.size(); i++)
	{
		if (mMaps[i].isSpriteClicked())
		{
			mMapSelector.mSelectedButton->getText().setFillColor(sf::Color::White);
			mMapSelector.mSelectedButton = &mMaps[i];
			mMapSelector.mSelectedButton->getText().setFillColor(sf::Color::Red);
		}
	}
}

void GameState_GameBuild::rePositionButtons(sf::Vector2u & currentPosition, sf::Vector2u & newPosition)
{
}


std::string& GameState_GameBuild::getSelectedMapPath()
{
	return mMapSelector.mSelectedButton->loadPath_objects;
}

std::vector<Entity*>* GameState_GameBuild::getEntities()
{
	std::vector<Entity*> *vector = new std::vector<Entity*>;
	for each (teamRecord member in teamOne.mTeamMembers)
		vector->push_back(member.mEntity);

	for each (teamRecord member in teamTwo.mTeamMembers)
		vector->push_back(member.mEntity);

	return vector;
}