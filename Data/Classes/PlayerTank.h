#pragma once
#include <vector>
#include "TankButton.h"
#include "Selector.h"


class PlayerTank
{
public:
	std::vector<TankButton>							mTanks;
	std::vector<sf::Text>							mDisplayStats;
	Selector<TankButton>							mTanks_Selector;
	sf::Sprite										mBorder;
	sf::Text										mMainText;

public:
	PlayerTank(sf::Vector2f borderPosition, std::string title);

private:


private:

	void											buildGUI();

};

inline PlayerTank::PlayerTank(sf::Vector2f borderPosition, std::string title)
	: mBorder(Game::get()->mTextures.get(Texture::border_Half))
	, mMainText(title, Game::get()->mFonts.get(Font::VanillaExtractRegular), 30)
	, mTanks_Selector(Game::get()->mTextures.get(Texture::button_Selector), sf::Vector2f(20.0f, Game::get()->mWindow.getSize().y - 270.0f), 50.0f, mTanks)
{
	mBorder.setPosition(borderPosition);
	mMainText.setPosition(mBorder.getPosition().x + 30.0f, mBorder.getPosition().y - 40.0f);
	buildGUI();


	mTanks_Selector.mButtons = mTanks;
	mTanks_Selector.mNumberOfButtons = mTanks.size();
	mTanks_Selector.mSelectedButton = &mTanks[0];
	mTanks_Selector.mSelectedButton->getText().setFillColor(sf::Color::Red);
}

inline void PlayerTank::buildGUI()
{
	mDisplayStats.push_back(sf::Text("Health:", Game::get()->mFonts.get(Font::VanillaExtractRegular), 20));
	mDisplayStats.push_back(sf::Text("Speed: ", Game::get()->mFonts.get(Font::VanillaExtractRegular), 20));
	mDisplayStats.push_back(sf::Text("Damage:", Game::get()->mFonts.get(Font::VanillaExtractRegular), 20));

	mDisplayStats[0].setPosition(mBorder.getPosition().x + 5.0f, mBorder.getPosition().y + mBorder.getTexture()->getSize().y + 5.0f);
	mDisplayStats[1].setPosition(mBorder.getPosition().x + 5.0f, mBorder.getPosition().y + mBorder.getTexture()->getSize().y + 35.0f);
	mDisplayStats[2].setPosition(mBorder.getPosition().x + 5.0f, mBorder.getPosition().y + mBorder.getTexture()->getSize().y + 65.0f);
	mDisplayStats[0].setFillColor(sf::Color::Red);
	mDisplayStats[1].setFillColor(sf::Color::Green);
	mDisplayStats[2].setFillColor(sf::Color::Blue);

	sf::Vector2f deltaPosition(5.0f, 5.0f);

	mTanks.push_back(TankButton(mBorder.getPosition() + deltaPosition, "M1-Abrams", 20, 200.0, 15.0, 100.0f, "tank1"));
	mTanks[0].mTextData.push_back(sf::Text("+++", Game::get()->mFonts.get(Font::VanillaExtractRegular), 20));
	mTanks[0].mTextData.push_back(sf::Text("+", Game::get()->mFonts.get(Font::VanillaExtractRegular), 20));
	mTanks[0].mTextData.push_back(sf::Text("++", Game::get()->mFonts.get(Font::VanillaExtractRegular), 20));
	mTanks[0].mTextData[0].setPosition(mDisplayStats[0].getPosition() + sf::Vector2f(150.0f, 0.0f));
	mTanks[0].mTextData[0].setFillColor(sf::Color::Red);
	mTanks[0].mTextData[1].setPosition(mDisplayStats[1].getPosition() + sf::Vector2f(150.0f, 0.0f));
	mTanks[0].mTextData[1].setFillColor(sf::Color::Green);
	mTanks[0].mTextData[2].setPosition(mDisplayStats[2].getPosition() + sf::Vector2f(150.0f, 0.0f));
	mTanks[0].mTextData[2].setFillColor(sf::Color::Blue);

	deltaPosition.y += 30.0f;

	mTanks.push_back(TankButton(mBorder.getPosition() + deltaPosition, "T-34", 20, 250.0, 15.0, 80.0f, "tank3b"));
	mTanks[1].mTextData.push_back(sf::Text("++++", Game::get()->mFonts.get(Font::VanillaExtractRegular), 20));
	mTanks[1].mTextData.push_back(sf::Text("+", Game::get()->mFonts.get(Font::VanillaExtractRegular), 20));
	mTanks[1].mTextData.push_back(sf::Text("+", Game::get()->mFonts.get(Font::VanillaExtractRegular), 20));
	mTanks[1].mTextData[0].setPosition(mDisplayStats[0].getPosition() + sf::Vector2f(150.0f, 0.0f));
	mTanks[1].mTextData[0].setFillColor(sf::Color::Red);
	mTanks[1].mTextData[1].setPosition(mDisplayStats[1].getPosition() + sf::Vector2f(150.0f, 0.0f));
	mTanks[1].mTextData[1].setFillColor(sf::Color::Green);
	mTanks[1].mTextData[2].setPosition(mDisplayStats[2].getPosition() + sf::Vector2f(150.0f, 0.0f));
	mTanks[1].mTextData[2].setFillColor(sf::Color::Blue);
	deltaPosition.y += 30.0f;

	mTanks.push_back(TankButton(mBorder.getPosition() + deltaPosition, "Tiger Panzer", 20, 320.0, 20.0, 60.0f, "tank2b"));
	mTanks[2].mTextData.push_back(sf::Text("+++++", Game::get()->mFonts.get(Font::VanillaExtractRegular), 20));
	mTanks[2].mTextData.push_back(sf::Text("++", Game::get()->mFonts.get(Font::VanillaExtractRegular), 20));
	mTanks[2].mTextData.push_back(sf::Text("-", Game::get()->mFonts.get(Font::VanillaExtractRegular), 20));
	mTanks[2].mTextData[0].setPosition(mDisplayStats[0].getPosition() + sf::Vector2f(150.0f, 0.0f));
	mTanks[2].mTextData[0].setFillColor(sf::Color::Red);
	mTanks[2].mTextData[1].setPosition(mDisplayStats[1].getPosition() + sf::Vector2f(150.0f, 0.0f));
	mTanks[2].mTextData[1].setFillColor(sf::Color::Green);
	mTanks[2].mTextData[2].setPosition(mDisplayStats[2].getPosition() + sf::Vector2f(150.0f, 0.0f));
	mTanks[2].mTextData[2].setFillColor(sf::Color::Blue);
	deltaPosition.y += 30.0f;

	mTanks.push_back(TankButton(mBorder.getPosition() + deltaPosition, "T-55", 20, 150.0, 30.0, 180.0f, "tank3c"));
	mTanks[3].mTextData.push_back(sf::Text("-", Game::get()->mFonts.get(Font::VanillaExtractRegular), 20));
	mTanks[3].mTextData.push_back(sf::Text("++", Game::get()->mFonts.get(Font::VanillaExtractRegular), 20));
	mTanks[3].mTextData.push_back(sf::Text("+++++", Game::get()->mFonts.get(Font::VanillaExtractRegular), 20));
	mTanks[3].mTextData[0].setPosition(mDisplayStats[0].getPosition() + sf::Vector2f(150.0f, 0.0f));
	mTanks[3].mTextData[0].setFillColor(sf::Color::Red);
	mTanks[3].mTextData[1].setPosition(mDisplayStats[1].getPosition() + sf::Vector2f(150.0f, 0.0f));
	mTanks[3].mTextData[1].setFillColor(sf::Color::Green);
	mTanks[3].mTextData[2].setPosition(mDisplayStats[2].getPosition() + sf::Vector2f(150.0f, 0.0f));
	mTanks[3].mTextData[2].setFillColor(sf::Color::Blue);

}