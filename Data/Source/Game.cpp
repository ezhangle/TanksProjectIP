#include "Game.h"

const sf::Time Game::timePerFrame = sf::seconds(1.f / 60.f);


Game::Game(unsigned int w, unsigned int h)
	: mWidth(w),
	mHeight(h),
	mWindow(sf::VideoMode(w, h), "Tanks")
{
	loadTextures();
	loadWorld();
}

Game::~Game()
{

}

void Game::loadTextures() {
	mTextures.load(Texture::TEST, "Assets/Textures/test.jpg");
}

void Game::loadWorld() {
	mWorld.loadWorld("Assets/Maps/graph.txt", &mTextures);
}

//GAME FRAMEWORK LOGIC

void Game::update(sf::Time deltaTime)
{
	//HANDLE STATES

	GameState *currentState = getActiveState();
	if (currentState != nullptr)
	{
		currentState->handleInput();
		currentState->update(deltaTime);
		mWindow.clear(sf::Color::Blue);
		currentState->draw(deltaTime);
		mWindow.display();
	}
}

void Game::render()
{
	mWorld.mMaps[0]->drawTiles(&mWindow);
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

//GAMESTATE LOGIC

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
	//IF THE STACK IS NOT EMPTY, REMOVE THE CURRENT STATE
	if (!this->stateStack.empty())
		popState();
	pushState(state);
}

GameState* Game::getActiveState()
{
	//IF THE STATESTACK IS EMPTY, RETURN NULLPTR - THIS MEANS THERE ARE NO GAMESTATES
	if (this->stateStack.empty())
		return nullptr;

	//ELSE, GET THE TOP OF THE STACK AND RETURN
	return this->stateStack.top();
}
