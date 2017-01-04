#pragma once
#include "TextButton.h"

class FullscreenButton
	: public TextButton
{
public:
	size_t											mFullscreenData;
	enum class Action
	{
		changeFullscreen,
		back,
	};

public:
													FullscreenButton(sf::Vector2f initialPosition, Action action, size_t fullscreenData);
													FullscreenButton(sf::Vector2f initialPosition, std::string text, Action action, size_t fullscreenData);
													FullscreenButton(sf::Vector2f initialPosition, sf::Font &font, Action action, size_t fullscreenData);
													FullscreenButton(sf::Vector2f initialPosition, std::string text, size_t characterSize, Action action, size_t fullscreenData);
													FullscreenButton(sf::Vector2f initialPosition, std::string text, sf::Font &font, Action action, size_t fullscreenData);
													FullscreenButton(sf::Vector2f initialPosition, std::string text, sf::Font &font, size_t characterSize, Action action, size_t fullscreenData);
	
	void											triggerAction();
	
private:
	Action											mAction;
	Game*											game;


private:

};