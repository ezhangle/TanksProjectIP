#pragma once

#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include "Game.h"

namespace button
{
	enum Action
	{
		exit,
		play,
		tankType,
		highscore,
		options
	};
}

class Button
{

public:
	sf::Sprite										mButtonSprite;

public:
													Button(sf::Vector2f buttonPosition, enum button::Action action, sf::Texture &texture);
													~Button();
	sf::Vector2f									getPosition();
	void											setPosition(sf::Vector2f desiredPosition);
	void											triggerAction();
	bool											isSpriteClicked();

private:
	sf::Vector2f									mPositionVector;
	enum button::Action								mButtonAction;
	Game*											game;

private:
	


};