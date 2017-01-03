#pragma once

#include "TextButton.h"
#include "Tank.h"

#include <vector>

class AddButton
	: public TextButton
{
public:
	enum class Action
	{
		addPlayer1,
		addPlayer2,
		addAI,
	};

public:
	AddButton(sf::Vector2f initialPosition, std::string text, size_t characterSize, Action action, std::vector<Tank> &tanks);

private:
	Action											mAction;
	std::vector<Tank>&								mTanks;

private:


};