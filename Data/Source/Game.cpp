#include "Game.h"
#include <fstream>
const sf::Time Game::timePerFrame = sf::seconds(1.f / 60.f);
Game *Game::instance = nullptr;

Game::Game(unsigned int w, unsigned int h)
	: mWidth(w),
	mHeight(h),
	mWindow(sf::VideoMode(w,h), "Tanks")
{
	instance = this;
	loadTextures();

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
	sf::Vector2u newSize(mWindow.getSize());
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp)) {
		newSize.x += (int)mWidth / 100;
		newSize.y += (int)mHeight / 100;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown)){	
		newSize.x -= (int)mWidth / 100;
		newSize.y -= (int)mHeight / 100;
	}

	if(newSize.x > 100 && newSize.y > 100)
		mWindow.setSize(newSize);

	mMap->update(deltaTime);
}

void Game::render()
{
	mMap->draw(&mWindow);
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
			handleInput();
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
	delete this->stateStack.top();
	this->stateStack.pop();
}

void Game::changeState(GameState *state)
{
	if (!this->stateStack.empty())
		popState();
	pushState(state);
}

GameState* Game::getActiveState()
{
	if (this->stateStack.empty())
		return nullptr;

	return this->stateStack.top();
}