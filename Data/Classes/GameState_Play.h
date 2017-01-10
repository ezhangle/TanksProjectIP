#pragma once

#include "GameState.h"
#include "Game.h"
#include "Map.h"
#include "TextButton.h"
#include "GameState_GameBuild.h"

class GameState_Play
	: public GameState
{
public:
	static 	GameState_Play*							instance;

public:
	GameState_Play(std::string& mapObjectsPath, std::vector<Entity*>& entities);

	void											buildGUI();
	void											update(sf::Time deltaTime);
	void											draw();
	void											handleInput();
	void											handleEvents();
	void											handleRealTimeInput();
	void											rePositionButtons(sf::Vector2u &currentPosition, sf::Vector2u &newPosition);


	Map*											mMap;

private:
	Game*											game;
	GameState_GameBuild*							buildStatePointer;



private:
	std::string										mMapObjectsPath;
	std::vector<Entity*>							mEntities;


public:
	static GameState_Play* getStatePointer()
	{
		if (instance == nullptr)
		{
			instance = new GameState_Play(GameState_GameBuild::get()->getSelectedMapPath(), *(GameState_GameBuild::get()->getEntities()));
		}

		return instance;
	}
};
