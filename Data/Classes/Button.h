#pragma once

#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include "Game.h"


namespace button
{
	enum Action
	{
		none,
		exit,
		play,
		tankType,
		highscore,
		options,
		options_resolution,
		options_fullscreen,
		options_vsync,
		back,
	};
}

class Button
{

public:
	sf::Sprite										mButtonSprite;
	sf::Vector2u									resolutionData;
	size_t											fullscreenData;

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
	std::vector<Button*>							mNextButtons;

private:
	


};