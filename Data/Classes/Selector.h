#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include "Button.h"
#include "Game.h"

class Selector
{
public:
	enum Movement
	{
		up,
		down,
	};

	Button*											mSelectedButton;
	std::vector<Button>&							mButtonVector;
	size_t											mNumberOfButtons;

public:
													Selector(sf::Texture &texture, sf::Vector2f startLocation, float moveDistance, std::vector<Button> &vector);
													~Selector();
	void											draw();
	void											move(enum Movement direction);

private:
	sf::Sprite										mSprite;
	size_t											mIndex;
	float											mMoveDistance;
	Game*											game;

private:



};