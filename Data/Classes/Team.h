#pragma once

#include <vector>
#include <list>

#include "Selector.h"
#include "Team_Record.h"
#include "TankBuildData.h"

class team
{
public:
	size_t										teamNumber;
	size_t										numberOfMembers;
	std::vector<AddButton>						mAddButtons;
	std::vector<teamRecord>						mTeamMembers;

	sf::Sprite									mBorder;
	sf::Text									mText;
	Selector<AddButton>							mAddButtons_Selector;
	sf::Vector2f								mAddPosition;
	Selector<teamRecord>						mTeamMembers_Selector;
	sf::Vector2f*								spawnPosition;
	TankBuildData								player1TankData;
	TankBuildData								player2TankData;


	team(sf::Vector2f borderPosition, sf::Vector2f removeButtonsPosition, sf::Vector2f textPosition, size_t teamNumb, std::string text, TankBuildData player1Tank, TankBuildData player2Tank);
};

inline team::team(sf::Vector2f borderPosition, sf::Vector2f removeButtonsPosition, sf::Vector2f textPosition, size_t teamNumb, std::string text, TankBuildData player1Tank, TankBuildData player2Tank)
	: mAddButtons_Selector(Game::get()->mTextures.get(Texture::button_Selector), sf::Vector2f(20.0f, Game::get()->mWindow.getSize().y - 270.0f), 50.0f, mAddButtons)
	, teamNumber(teamNumb)
	, mText(text, Game::get()->mFonts.get(Font::VanillaExtractRegular), 20)
	, mBorder(Game::get()->mTextures.get(Texture::border_Full))
	, mTeamMembers_Selector(Game::get()->mTextures.get(Texture::button_Selector), sf::Vector2f(20.0f, Game::get()->mWindow.getSize().y - 270.0f), 50.0f, mTeamMembers)
	, player1TankData(player1Tank)
	, player2TankData(player2Tank)
{
	player1TankData.mTextureIdentifier = "tank1";
	player1TankData.mDamage = 15.0f;
	player1TankData.mHealth = 100.0f;
	player1TankData.mSpeed = 100.0f;
	player2TankData.mTextureIdentifier = "tank1";
	player2TankData.mDamage = 15.0f;
	player2TankData.mHealth = 100.0f;
	player2TankData.mSpeed = 100.0f;

	mText.setPosition(textPosition);
	mBorder.setPosition(borderPosition);
	numberOfMembers = 0;
	if (teamNumb == 1)
		spawnPosition = new sf::Vector2f(200.0f, 200.0f);
	else
		spawnPosition = new sf::Vector2f(1200.0f, 600.0f);

	mTeamMembers.reserve(18);

	//buildGUI
	AddButton addPlayer1(mBorder.getPosition() + sf::Vector2f(-130.0f, 0.0f), "Player 1", 20, AddButton::Action::addPlayer1);
	AddButton addPlayer2(mBorder.getPosition() + sf::Vector2f(-130.0f, 30.0f), "Player 2", 20, AddButton::Action::addPlayer2);
	AddButton addAI_Easy(mBorder.getPosition() + sf::Vector2f(-130.0f, 60.0f), "AI(easy)", 20, AddButton::Action::addAI_easy);
	AddButton addAI_Medium(mBorder.getPosition() + sf::Vector2f(-130.0f, 90.0f), "AI(medium)", 20, AddButton::Action::addAI_medium);
	AddButton addAI_Hard(mBorder.getPosition() + sf::Vector2f(-130.0f, 120.0f), "AI(hard)", 20, AddButton::Action::addAI_hard);
	mAddButtons.push_back(addPlayer1);
	mAddButtons.push_back(addPlayer2);
	mAddButtons.push_back(addAI_Easy);
	mAddButtons.push_back(addAI_Medium);
	mAddButtons.push_back(addAI_Hard);

	mAddButtons_Selector.mNumberOfButtons = mAddButtons.size();
	mAddButtons_Selector.mButtons = mAddButtons;
	mAddButtons_Selector.mSelectedButton = &mAddButtons[0];

	mAddPosition = mBorder.getPosition() + sf::Vector2f(20.0f, 5.0f);
}