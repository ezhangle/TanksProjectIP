#include "Game.h"
#include <exception>
#include <iostream>

int main()
{
	try {
		Game game;
		game.run();
	}
	catch (std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
}