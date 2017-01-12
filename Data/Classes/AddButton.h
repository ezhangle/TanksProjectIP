#pragma once

#include "TextButton.h"
#include "Tank.h"
#include "Player.h"
#include "Map.h"
#include "AI_Easy.h"
#include "AI_Medium.h"
#include "AI_Hard.h"
#include <vector>
//#include "Team.h"

class team;

class AddButton
	: public TextButton
{
public:
	enum class Action
	{
		addPlayer1,
		addPlayer2,
		addAI_easy,
		addAI_medium,
		addAI_hard,
	};

	

public:
	AddButton(sf::Vector2f initialPosition, std::string text, size_t characterSize, Action action);
	AddButton(sf::Vector2f initialPosition, Action action);

	void											triggerAction(team& team);
	void											insertPlayerOne(const std::string& tankType, sf::Vector2f position, sf::Vector2f velocity, float health, float damage, team& team, sf::Vector2f buttonPosition);
	void											insertPlayerTwo(const std::string& tankType, sf::Vector2f position, sf::Vector2f velocity, float health, float damage, team& team, sf::Vector2f buttonPosition);
	void											insertAI(const std::string& difficulty, const std::string& tankType, sf::Vector2f position, sf::Vector2f velocity, float health, float damage, team& team, sf::Vector2f buttonPosition);
	void											getTextureIDs(const std::string& textureString, Texture& baseTexture, Texture& topTexture);

private:
	Action											mAction;

private:


};