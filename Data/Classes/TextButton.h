#pragma once





#include <SFML/Graphics/Text.hpp>
#include "Game.h"

class TextButton
{
public:
	enum class Action
	{
		//building
		buildGamePlay,
		buildOptions,
		buildScoreboard,
		buildOptions_Resolution,
		buildOptions_Fullscreen,
		buildOptions_VSync,
		buildGamePlay_ChangeTanks,

		//FINA-FUCKING-LLY
		playGame,

		//simple commands
		back,
		yes,
		no,
		none,
		exit,

	};

public:
													TextButton(sf::Vector2f initialPosition, Action action);
													TextButton(sf::Vector2f initialPosition, std::string text, Action action);
													TextButton(sf::Vector2f initialPosition, sf::Font &font, Action action);
													TextButton(sf::Vector2f initialPosition, std::string text, size_t characterSize, Action action);
													TextButton(sf::Vector2f initialPosition, std::string text, sf::Font &font, Action action);
													TextButton(sf::Vector2f initialPosition, std::string text, sf::Font &font, size_t characterSize, Action action);


	sf::Text&										getText();
	void											update(sf::Time deltaTime);
	void											triggerAction();
	bool											isSpriteClicked();
	bool											isSpriteSelected();
	sf::Text&										getTextAdress();

private:
	sf::Text										mText;
	Action											mAction;
	Game*											game;


private:
	
};