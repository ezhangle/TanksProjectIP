#ifndef GAME_H
#define GAME_H

//CUSTOM CLASSES AND OTHER HELPERS
#include "GameState.h"
#include "ResourceHolder.h"
#include "Enums.h"
#include "World.h"


//SFML LIBRARIES
#include <SFML\System\NonCopyable.hpp>
#include <SFML\System\Time.hpp>
#include <SFML\System\Clock.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Event.hpp>


//STL LIBRARIES
#include <stack>
#include <string>


//DECLARE GAMESTATE TO LET THE GAME CLASS KNOW ABOUT GAMESTATE
class GameState;


class Game
	: private sf::NonCopyable

{

public:

	std::stack<GameState*>							stateStack;
	sf::RenderWindow								mWindow;
	static const sf::Time							timePerFrame;
	sf::Sprite										mBackground;

public:
													Game(unsigned int w, unsigned int h);
													~Game();
	void											run();

	void											pushState(GameState *state);
	void											popState();
	void											changeState(GameState *state);
	GameState*										getActiveState();

private:
	ResourceHolder<sf::Texture, Texture>			mTextures;
	unsigned int									mWidth;
	unsigned int									mHeight;
	World											mWorld;

private:
	void											loadTextures();
	void											loadWorld();
	void											processEvents();
	void											handleRealTimeInput();
	void											update(sf::Time deltaTime);
	void											handleInput();
	void											render();
										
};


#endif // !GAME_H
