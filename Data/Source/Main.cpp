#include "Game.h"
#include <exception>
#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
	std::srand(std::time(NULL));
	try {
		Game::get()->run();
	}
	catch (std::runtime_error& err) {
		std::cout << err.what();
	}
	
}