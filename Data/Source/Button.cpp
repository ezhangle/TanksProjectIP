#include "Button.h"


Button::Button(sf::Vector2f buttonPosition, enum button::Action action, sf::Texture &texture)
	: mPositionVector(buttonPosition)
	, mButtonAction(action)
	, game(Game::get())
	, mButtonSprite(texture)
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