#include "Map.h"
#include "Tank.h"
#include "Player.h"
#include "Game.h"
#include <fstream>
#include <vector>

Map::Map(std::string& path){
	mEntities.resize(NUMBER);
	loadFromFile(path);
}

void Map::loadFromFile(std::string& path) {
	std::ifstream in(path);

	int bground;
	in >> bground;

	mBackground.setTexture(Game::get()->mTextures.get((Texture)bground));

	std::string obj;
	float x, y;
	while (!in.eof()) {
		in >> obj >> x >> y;
		insertObject(obj, new sf::Vector2f(x, y));
	}
	in.close();
}

void Map::insertObject(std::string& obj, sf::Vector2f* pos) {
	if (obj == "player1") {
		std::vector<sf::Keyboard::Key> keys;
		keys.resize(20);

		keys[(int)Tank::Command::DOWN] = sf::Keyboard::S;
		keys[(int)Tank::Command::UP] = sf::Keyboard::W;
		keys[(int)Tank::Command::LEFT] = sf::Keyboard::A;
		keys[(int)Tank::Command::RIGHT] = sf::Keyboard::D;

		keys[(int)Tank::Command::ROT_LEFT] = sf::Keyboard::Q;
		keys[(int)Tank::Command::ROT_RIGHT] = sf::Keyboard::E;

		keys[(int)Tank::Command::SHOOT] = sf::Keyboard::Space;
	
		mEntities[TANK].insert(mEntities[TANK].begin(), new Player(
			new sf::Sprite(Game::get()->mTextures.get(Texture::tank1b_body)),
			new sf::Sprite(Game::get()->mTextures.get(Texture::tank1b_gun)),
			pos,
			new sf::Vector2f(150.f, 150.f),
			10.f,
			10.f,
			keys));
	}

	if (obj == "player2") {
		std::vector<sf::Keyboard::Key> keys;
		keys.resize(20);

		keys[(int)Tank::Command::DOWN] = sf::Keyboard::Numpad5;
		keys[(int)Tank::Command::UP] = sf::Keyboard::Numpad8;
		keys[(int)Tank::Command::LEFT] = sf::Keyboard::Numpad4;
		keys[(int)Tank::Command::RIGHT] = sf::Keyboard::Numpad6;

		keys[(int)Tank::Command::ROT_LEFT] = sf::Keyboard::Numpad7;
		keys[(int)Tank::Command::ROT_RIGHT] = sf::Keyboard::Numpad9;

		keys[(int)Tank::Command::SHOOT] = sf::Keyboard::P;

		mEntities[TANK].insert(mEntities[TANK].begin(), new Player(
			new sf::Sprite(Game::get()->mTextures.get(Texture::tank1_body)),
			new sf::Sprite(Game::get()->mTextures.get(Texture::tank1_gun)),
			pos,
			new sf::Vector2f(150.f, 150.f),
			10.f,
			10.f,
			keys));
	}
}

void Map::update(sf::Time dt) {
	for (auto it1 = mEntities.begin(); it1 != mEntities.end(); ++it1) {
		for (auto it2 = (*it1).begin(); it2 != (*it1).end(); ++it2) {
			(*it2)->update(dt);
		}
	}

	for (auto it = mEffects.begin(); it != mEffects.end(); ++it) {
		if ((*it)->bFinished == true)
			mEffects.erase(it);
		else
			(*it)->update(dt);
	}
}

void Map::draw(sf::RenderWindow* window) {
	
	window->draw(mBackground);
	for (auto it1 = mEntities.begin(); it1 != mEntities.end(); ++it1) {
		for (auto it2 = (*it1).begin(); it2 != (*it1).end(); ++it2) {
			(*it2)->draw(window);
		}
	}

	for (auto it = mEffects.begin(); it != mEffects.end(); ++it) {
		(*it)->draw(window);
	}
}