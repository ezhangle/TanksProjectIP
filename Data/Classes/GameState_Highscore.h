#pragma once
#include "GameState.h"
#include "Highscore_Record.h"
#include <string>
#include <vector>
#include <fstream>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/View.hpp>

class GameState_Highscore
	: public GameState
{
public:
	

public:
													GameState_Highscore();
													~GameState_Highscore();

	void											draw();
	void											buildGUI();
	void											update(sf::Time deltaTime);
	void											handleInput();
	void											handleEvents();
	void											handleRealTimeInput();


private:
	Game*											game;


	std::vector<highscore_Record>					mHighscoreVector;

	sf::Sprite										mBackground;
	sf::Text										mTitle;
	sf::Text										mHelperText;

	unsigned int									mNumberOfScores;
	sf::View										mView;

private:



};
