#pragma once
#include "Map.h"
#include "Terrain.h"
#include "Tank.h"
#include "Player.h"
#include <vector>
#include <fstream>

Map::Map(ResourceHolder<sf::Texture, Texture>* res)
:mRows(0),
mColumns(0),
mTextures(res)
{
	mTiles.resize((int)Priority::NUMBER);
}

Map::Map(std::string& path, ResourceHolder<sf::Texture, Texture>* res)
	:mRows(0),
	mColumns(0),
	mTextures(res)
{
	mTiles.resize((int)Priority::NUMBER);
	loadFromFile(path);
}

void Map::loadFromFile(std::string& path) {
	std::ifstream in(path);

	in >> mRows;
	in >> mColumns;

	std::vector<Tile**>::iterator it = mTiles.begin();
	for (; it != mTiles.end(); ++it) {
		(*it) = new Tile*[mRows];
		for (int i = 0; i < mRows; ++i) {
			(*it)[i] = new Tile[mColumns];
		}
	}
	

	generateTerrain();

	int objects;
	in >> objects;

	int ki, kj;
	std::string id;
	for (int i = 0; i < objects; ++i) {
		in >> ki >> kj >> id;
		insertObject(ki, kj, id);
	}

	in.close();
}

void Map::generateTerrain() {
	std::string terrain_01("TERRAIN_GR_01");
	for (int i = 0; i < mRows; ++i) {
		for (int j = 0; j < mColumns; ++j) {
			insertObject(i, j, terrain_01);
		}
	}
}

void Map::insertObject(int x, int y, std::string& id) {
	if (id == "ROCK_01")
		mTiles[(int)Priority::OBSTACLE][x][y].insertEntity(new Terrain(new sf::Vector2f(x*TILE_WIDTH, y*TILE_HEIGHT), 
			new sf::Sprite(mTextures->get(Texture::ROCK_01)), 
			true,
			this));

	if (id == "TERRAIN_GR_01") 
		mTiles[(int)Priority::DECO][x][y].insertEntity(new Terrain(new sf::Vector2f(x*TILE_WIDTH, y*TILE_HEIGHT), 
			new sf::Sprite(mTextures->get(Texture::TERRAIN_GR_01)), 
			false,
			this));

	if (id == "TANK1") {
		std::vector<sf::Keyboard::Key> playerKeys;
		playerKeys.resize((int)Tank::Command::NUMBER);

		playerKeys[(int)Tank::Command::LEFT] = sf::Keyboard::A;
		playerKeys[(int)Tank::Command::UP] = sf::Keyboard::W;
		playerKeys[(int)Tank::Command::RIGHT] = sf::Keyboard::D;
		playerKeys[(int)Tank::Command::DOWN] = sf::Keyboard::S;

		mTiles[(int)Priority::PLAYER][x][y].insertEntity(new Player(new sf::Sprite(mTextures->get(Texture::TANK1_BODY)),
			new sf::Sprite(mTextures->get(Texture::TANK1_GUN)),
			new sf::Vector2f(x*TILE_WIDTH, y*TILE_HEIGHT),
			new sf::Vector2f(200.f, 200.f),
			10.f,
			10.f,
			this,
			playerKeys));
	}
}

void Map::updateTiles(sf::Time dt) {
	std::vector<Tile**>::iterator it = mTiles.begin();

	for (; it != mTiles.end(); ++it) {
		for (int i = 0; i < mRows; ++i) {
			for (int j = 0; j < mColumns; ++j) {
				(*it)[i][j].update(dt);
			}
		}
	}
}

void Map::drawTiles(sf::RenderWindow* window) {
	std::vector<Tile**>::iterator it = mTiles.begin();

	for (; it != mTiles.end(); ++it) {
		for (int i = 0; i < mRows; ++i) {
			for (int j = 0; j < mColumns; ++j) {
				(*it)[i][j].draw(window);
			}
		}
	}
}

int Map::getPriority(Entity* entity) {
	if (typeid(*entity) == typeid(Tank))
		return (int)Priority::PLAYER;
	else
		return (int)Priority::DECO;
}