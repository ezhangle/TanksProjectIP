#include "Game.h"
#include "GameState_MainMenu.h"
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