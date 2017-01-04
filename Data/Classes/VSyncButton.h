#pragma once
#include "TextButton.h"


class VSyncButton
	: public TextButton
{
public:
	bool											mVSync;
	enum class Action
	{
		changeVSync,
		back,
	};

public:
													VSyncButton(sf::Vector2f initialPosition, Action action, bool vsyncData);
													VSyncButton(sf::Vector2f initialPosition, std::string text, Action action, bool vsyncData);
													VSyncButton(sf::Vector2f initialPosition, sf::Font &font, Action action, bool vsyncData);
													VSyncButton(sf::Vector2f initialPosition, std::string text, size_t characterSize, Action action, bool vsyncData);
													VSyncButton(sf::Vector2f initialPosition, std::string text, sf::Font &font, Action action, bool vsyncData);
													VSyncButton(sf::Vector2f initialPosition, std::string text, sf::Font &font, size_t characterSize, Action action, bool vsyncData);
	
	void											triggerAction();

private:
	Action											mAction;
	Game*											game;

private:


};