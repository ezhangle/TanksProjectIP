#include "TextButton.h"
#include "GameState_GameBuild.h"
#include "GameState_Highscore.h"
#include "GameState_MainMenu.h"
#include "GameState_Options.h"
#include "GameState_Options_Fullscreen.h"
#include "GameState_Options_Resolution.h"
#include "GameState_Options_Vsync.h"

TextButton::TextButton(sf::Vector2f initialPosition, Action action)
	: game(Game::get())
	, mText("", game->mFonts.get(Font::VanillaExtractRegular), 30)
	, mAction(action)
{
	mText.setPosition(initialPosition);
};

TextButton::TextButton(sf::Vector2f initialPosition, std::string text, Action action)
	: game(Game::get())
	, mText(text, game->mFonts.get(Font::VanillaExtractRegular), 30)
	, mAction(action)
{
	mText.setPosition(initialPosition);
};

TextButton::TextButton(sf::Vector2f initialPosition, sf::Font & font, Action action)
	: game(Game::get())
	, mText("", font, 30)
	, mAction(action)
{
	mText.setPosition(initialPosition);
};

TextButton::TextButton(sf::Vector2f initialPosition, std::string text, size_t characterSize, Action action)
	
	: mAction(action)
{
	game = Game::get();
	mText.setString(text);
	mText.setFont(game->mFonts.get(Font::VanillaExtractRegular));
	mText.setCharacterSize(characterSize);

	mText.setPosition(initialPosition);
};

TextButton::TextButton(sf::Vector2f initialPosition, std::string text, sf::Font & font, Action action)
	: game(Game::get())
	, mText(text, font, 30)
	, mAction(action)
{
	mText.setPosition(initialPosition);
};

TextButton::TextButton(sf::Vector2f initialPosition, std::string text, sf::Font &font, size_t characterSize, Action action)
	: game(Game::get())
	, mText(text, font, characterSize)
	, mAction(action)
{
	mText.setPosition(initialPosition);
}

void TextButton::update(sf::Time deltaTime)
{
}

void TextButton::triggerAction()
{
	switch (mAction)
	{
		case Action::none:
		{
			break;
		}

		case Action::buildGamePlay:
		{
			game->pushState(new GameState_GameBuild());
			break;
		}

		case Action::buildOptions:
		{
			game->pushState(new GameState_Options());
			break;
		}

		case Action::buildOptions_Fullscreen:
		{
			game->pushState(new GameState_Options_Fullscreen());
			break;
		}

		case Action::buildOptions_Resolution:
		{
			game->pushState(new GameState_Options_Resolution());
			break;
		}

		case Action::buildOptions_VSync:
		{
			game->pushState(new GameState_Options_Vsync());
			break;
		}

		case Action::back:
		{
			game->popState();
			break;
		}

		case Action::exit:
		{
			game->mWindow.close();
			break;
		}

		case Action::buildScoreboard:
		{
			game->pushState(new GameState_Highscore());
			break;
		}


		default:break;
	}
}


sf::Text& TextButton::getText()
{
	return mText;
};

bool TextButton::isSpriteClicked()
{
	sf::FloatRect buttonSpriteRect(mText.getGlobalBounds());

	if (buttonSpriteRect.contains(sf::Mouse::getPosition(game->mWindow).x, sf::Mouse::getPosition(game->mWindow).y))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return 1;
		}
	}

	return 0;
}

bool TextButton::isSpriteSelected()
{
	sf::FloatRect buttonSpriteRect(mText.getGlobalBounds());

	if (buttonSpriteRect.contains(sf::Mouse::getPosition(game->mWindow).x, sf::Mouse::getPosition(game->mWindow).y))
		return 1;

	return 0;
}

sf::Text& TextButton::getTextAdress()
{
	return *&mText;
}
