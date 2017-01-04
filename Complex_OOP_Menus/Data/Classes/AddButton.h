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
		addEntity,
		addPlayer1,
		addPlayer2,
		addAI_easy,
		addAI_medium,
		addAI_hard,
		back,
	};

public:
	AddButton(sf::Vector2f initialPosition, std::string text, size_t characterSize, Action action, std::vector<Tank> &tanks);
	AddButton(sf::Vector2f initialPosition, Action action, std::vector<Tank> &tanks);

	void											triggerAction();

private:
	Action											mAction;
	std::vector<Tank>&								mTanks;

private:


};