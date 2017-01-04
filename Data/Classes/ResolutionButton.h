#pragma once
#include "TextButton.h"


class ResolutionButton
	: public TextButton
{
public:
	sf::Vector2u									mResolutionData;
	enum class Action
	{
		changeResolution,
		back
	};
	

public:
													ResolutionButton(sf::Vector2f initialPosition, Action action, sf::Vector2f resolutionData);
													ResolutionButton(sf::Vector2f initialPosition, std::string text, Action action, sf::Vector2f resolutionData);
													ResolutionButton(sf::Vector2f initialPosition, sf::Font &font, Action action, sf::Vector2f resolutionData);
													ResolutionButton(sf::Vector2f initialPosition, std::string text, size_t characterSize, Action action, sf::Vector2f resolutionData);
													ResolutionButton(sf::Vector2f initialPosition, std::string text, sf::Font &font, Action action, sf::Vector2f resolutionData);
													ResolutionButton(sf::Vector2f initialPosition, std::string text, sf::Font &font, size_t characterSize, Action action, sf::Vector2f resolutionData);
	void											triggerAction();

private:
	Action											mAction;
	Game*											game;


private:


};