#include "Game.h"
#include <exception>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>

int main()
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	std::srand(std::time(NULL));
	try {
		Game::get()->run();
	}
	catch (std::runtime_error& err) {
		std::cout << err.what();
	}
	
}