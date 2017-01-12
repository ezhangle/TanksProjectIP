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
													Game(unsigned int w, unsigned int h, bool VSync);
													Game(unsigned int w, unsigned int h, bool vSync, bool fullscreen);
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
			std::ifstream resolutionCFG("Assets/Config/resolutionCFG.txt");
			std::ifstream vsyncCFG("Assets/Config/vsyncCFG.txt");
			std::ifstream fullscreenCFG("Assets/Config/fullscreenCFG.txt");
			int w, h;
			bool bVsync, fullscreen;
			resolutionCFG >> w >> h;
			vsyncCFG >> bVsync;
			fullscreenCFG >> fullscreen;
			resolutionCFG.close();
			vsyncCFG.close();
			fullscreenCFG.close();

			if (!fullscreen)
			{
				instance = new Game(w, h, bVsync);
			}

			else
			{
				instance = new Game(w, h, bVsync, 1);
			}
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
