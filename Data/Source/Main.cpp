#include "Game.h"
#include "GameState_Start.h"

int main()
{
	Game game(1280, 768);
	game.pushState(new GameState_Start(&game));
	game.run();
}