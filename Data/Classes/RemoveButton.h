#pragma once
#include "TextButton.h"



class team;


class RemoveButton
	: public TextButton
{
public:
	enum Action
	{
		remove,
		clear,
		none,
	};

	sf::Text										mTextRemove;


public:
	RemoveButton(sf::Vector2f position, std::string text, size_t charSize, RemoveButton::Action action);

	void											triggerAction(team &team, unsigned int index, size_t& player1_team, size_t& player2_team);

private:
	Action											mAction;

private:


};