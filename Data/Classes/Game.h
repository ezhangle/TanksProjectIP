#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include "ResourceHolder.h"
#include "Enums.h"
#include "Map.h"



#include <SFML\System\NonCopyable.hpp>
#include <SFML\System\Time.hpp>
#include <SFML\System\Clock.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Event.hpp>


#include <stack>
#include <string>
#include <fstream>


class GameState;


class Game
	: private sf::NonCopyable

{
	static Game										*instance;
public:

	std::stack<GameState*>							stateStack;
	sf::RenderWindow								mWindow;
	static const sf::Time							timePerFrame;

public:
													Game(unsigned int w, unsigned int h, bool vSync = 0, bool fullscreen = 1);
													~Game();
	void											run();

	void											pushState(GameState *state);
	void											popState();
	void											changeState(GameState *state);
	GameState*										getActiveState();
	void											deleteTopState();

public:
	ResourceHolder<sf::Texture, Texture>			mTextures;
	ResourceHolder<sf::Font, Font>					mFonts;
	unsigned int									mWidth;
	unsigned int									mHeight;
	Map*											mMap;
	sf::Clock										mClock;

	sf::View										mView;
	sf::Sprite										mBackground;

	static Game* get() {
		if (instance == nullptr)
		{
			instance = new Game(1600, 832);
		}

		return instance;
	}

private:
	void											loadTextures();
	void											processEvents();
	void											update(sf::Time deltaTime);
	void											handleInput();
	void											render();
	Map*											getMap();
										
};


#endif // !GAME_H
