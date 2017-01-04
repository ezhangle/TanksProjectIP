#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include "Enums.h"
#include <vector>

template <typename buttonType>
class Selector
{
public:
	buttonType*										mSelectedButton;
	std::vector<buttonType>&						mButtons;
	size_t											mNumberOfButtons;
	sf::Sprite										mSprite;

public:
													Selector(sf::Texture &texture, sf::Vector2f startLocation, float moveDistance, std::vector<buttonType> &vector);
	void											move(Movement direction);

private:
	size_t											mIndex;
	float											mMoveDistance;

private:



};