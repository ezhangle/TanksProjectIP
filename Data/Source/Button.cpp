#include "Button.h"

Button::Button(sf::Vector2f buttonPosition, enum button::Action action)
	: mPositionVector(buttonPosition)
	, mButtonRect(buttonPosition, sf::Vector2f(130.0f, 40.0f))
	, mButtonAction(action)
	, game(Game::get())
{
	mButtonSprite.setTexture(game->mTextures.get(Texture::button_ExitGame));
};


Button::~Button()
{

};


sf::Vector2f Button::getPosition()
{
	return mPositionVector;
}


void Button::setPosition(sf::Vector2f desiredPosition)
{
	
}

void Button::triggerAction()
{
	switch (mButtonAction)
	{
		case button::Action::exitGame:
		{
			game->mWindow.close();
			break;
		}

		case button::Action::startGame:
		{
			//ADD CODE HERE
			break;
		}

		case button::Action::changeTank:
		{
			//ADD CODE HERE
			break;
		}


		default:
			break;
	}
}