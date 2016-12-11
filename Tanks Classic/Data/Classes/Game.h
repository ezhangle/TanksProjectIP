#ifndef GAME_H

#define GAME_H

#include <SFML\System\NonCopyable.hpp>
#include <SFML\System\Time.hpp>
#include <SFML\System\Clock.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Event.hpp>


class Game
	: private sf::NonCopyable
{
private:

private:
	void										processEvents();
	void										update(sf::Time deltaTime);
	void										render();


public:
	
	
	
	sf::RenderWindow							mWindow;



	static const sf::Time						timePerFrame;

public:
												Game();
												~Game();
	void										run();
};


#endif // !GAME_H
