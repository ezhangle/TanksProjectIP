#include "Game.h"
#include <fstream>
#include "GameState_MainMenu.h"
const sf::Time Game::timePerFrame = sf::seconds(1.f / 60.f);
Game *Game::instance = nullptr;

Game::Game(unsigned int w, unsigned int h, bool bFullScreen)
	: mWidth(w),
	mHeight(h),
	mWindow(sf::VideoMode(w, h), "Thunder Tanks", sf::Style::None)
{
	if (bFullScreen)
		mWindow.create(sf::VideoMode(w, h), "Thunder Tanks", sf::Style::Fullscreen);

	instance = this;
	loadTextures();

	changeState(new GameState_MainMenu());
	std::string path("Assets/Maps/map1.tmap");
	mMap = new Map(path);
	
	mClock.restart();
}

Game::~Game()
{

}

void Game::loadTextures() {
	std::ifstream in("Assets/Textures/asset_path.txt");
	std::string path;
	int i = 0;

	while (!in.eof()) {
		in >> path;
		mTextures.load(static_cast<Texture>(i++), path);
	}
	in.close();
}

Map* Game::getMap() {
	return mMap;
}

void Game::update(sf::Time deltaTime)
{
	GameState *currentState = getActiveState();
	if (currentState != nullptr)
	{
		currentState->update(deltaTime);
	}

	//mMap->update(deltaTime);
}

void Game::render()
{
	//mMap->draw(&mWindow);
	GameState *currentState = getActiveState();
	if (currentState != nullptr)
	{
		mWindow.clear(sf::Color::Blue);
		currentState->draw();
	}
	mWindow.display();
}

void Game::processEvents()
{
	sf::Event eventToBeHandled;

	while (mWindow.pollEvent(eventToBeHandled))
	{
		switch (eventToBeHandled.type)
		{
			case sf::Event::Closed:
				mWindow.close();
		}
	}
}

void Game::handleInput()
{
	processEvents();
}

void Game::run()
{
	
	sf::Clock gameClock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = gameClock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			update(timePerFrame);
		}
		render();
	}
}

void Game::pushState(GameState *state)
{
	this->stateStack.push(state);
}

void Game::popState()
{
	delete stateStack.top();
	stateStack.pop();
}

void Game::changeState(GameState *state)
{
	if (!stateStack.empty())
		popState();
	pushState(state);
}

GameState* Game::getActiveState()
{
	if (stateStack.empty())
		return nullptr;

	return stateStack.top();
}