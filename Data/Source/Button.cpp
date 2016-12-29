#include "Button.h"
#include "GameState_Options.h"
#include "GameState_Options_Resolution.h"
#include "GameState_Options_Fullscreen.h"
#include "GameState_Options_Vsync.h"
#include "GameState_Highscore.h"
#include <iostream>


Button::Button(sf::Vector2f buttonPosition, enum button::Action action, sf::Texture &texture)
	: mPositionVector(buttonPosition)
	, mButtonAction(action)
	, game(Game::get())
	, mButtonSprite(texture)
	, resolutionData(0, 0)
	, fullscreenData(2)
{
	setPosition(mPositionVector);
};




Button::~Button()
{

};


sf::Vector2f Button::getPosition()
{
	return mButtonSprite.getPosition();
}


void Button::setPosition(sf::Vector2f desiredPosition)
{
	mButtonSprite.setPosition(desiredPosition);
}

void Button::triggerAction()
{
	switch (mButtonAction)
	{
		case button::Action::exit:
		{
			game->mWindow.close();
			break;
		}

		case button::Action::play:
		{
			//ADD CODE HERE
			break;
		}

		case button::Action::tankType:
		{
			//ADD CODE HERE
			break;
		}

		case button::Action::options:
		{
			game->pushState(new GameState_Options());
			break;
		}

		case button::Action::options_resolution:
		{
			game->pushState(new GameState_Options_Resolution());
			break;
		}

		case button::Action::options_fullscreen:
		{
			game->pushState(new GameState_Options_Fullscreen());
			break;
		}

		case button::Action::options_vsync:
		{
			game->pushState(new GameState_Options_Vsync());
			break;
		}

		case button::Action::highscore:
		{
			game->pushState(new GameState_Highscore());
			break;
		}

		case button::Action::back:
		{
			//game->deleteTopState();
			game->popState();
			break;
		}

		case::button::none:
		{
			break;
		}

		default:
			break;
	}
}

bool Button::isSpriteClicked()
{
	sf::FloatRect buttonSpriteRect(mButtonSprite.getPosition().x, mButtonSprite.getPosition().y, mButtonSprite.getGlobalBounds().width, mButtonSprite.getGlobalBounds().height);

	if (buttonSpriteRect.contains(sf::Mouse::getPosition(game->mWindow).x, sf::Mouse::getPosition(game->mWindow).y))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return 1;
		}
	}

	return 0;
}