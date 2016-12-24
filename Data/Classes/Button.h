#pragma once

#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include "Game.h"

namespace button
{
	enum Action
	{
		exitGame,
		startGame,
		changeTank
	};
}

class Button
{

public:


public:
													Button(sf::Vector2f buttonPosition, enum button::Action action);
													~Button();
	sf::Vector2f									getPosition();
	void											setPosition(sf::Vector2f desiredPosition);
	void											triggerAction();

private:
	sf::Vector2f									mPositionVector;
	sf::FloatRect									mButtonRect;
	enum button::Action								mButtonAction;
	sf::Sprite										mButtonSprite;
	Game*											game;

private:
	


};