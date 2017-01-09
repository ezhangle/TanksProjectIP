#pragma once

#include "GameState.h"
#include "Game.h"
#include "Map.h"
#include "TextButton.h"

class GameState_Play
	: public GameState
{
public:


public:
	GameState_Play(std::string& mapObjectsPath, std::vector<Entity*>& entities);

	void											buildGUI();
	void											update(sf::Time deltaTime);
	void											draw();
	void											handleInput();
	void											handleEvents();
	void											handleRealTimeInput();
	void											rePositionButtons(sf::Vector2u &currentPosition, sf::Vector2u &newPosition);

private:
	Game*											game;
	Map*											mMap;

private:
	std::string										mMapObjectsPath;
	std::vector<Entity*>							mEntities;

};
