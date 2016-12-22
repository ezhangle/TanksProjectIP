#include "Game.h"
#include "GameState_Start.h"
#include <exception>
#include <iostream>

int main()
{
	try {
		Game::get()->run();
	}
	catch (std::runtime_error& err) {
		std::cout << err.what();
	}
	
}