#pragma once
#include "Map.h"
#include "Terrain.h"
#include <fstream>

Map::Map(ResourceHolder<sf::Texture, Texture>* res)
:mTiles(nullptr),
mRows(0),
mColumns(0),
mTextures(res)
{
}

Map::Map(std::string& path, ResourceHolder<sf::Texture, Texture>* res)
	:mTiles(nullptr),
	mRows(0),
	mColumns(0),
	mTextures(res)
{
	loadFromFile(path);
}

void Map::loadFromFile(std::string& path) {
	std::ifstream in(path);

	in >> mRows;
	in >> mColumns;

	mTiles = new Tile*[mRows];
	for (int i = 0; i < mRows; ++i) {
		mTiles[i] = new Tile[mColumns];
	}

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

void Map::insertObject(int x, int y, std::string& id) {
	if (id == "pet") {
		mTiles[x][y].insertEntity(new Terrain(new sf::Vector2f(x*TILE_WIDTH, y*TILE_HEIGHT), new sf::Sprite(mTextures->get(Texture::TEST)), false));
	}
}

void Map::updateTiles(sf::Time dt) {
	for (int i = 0; i < mRows; ++i) {
		for (int j = 0; j < mColumns; ++j) {
			mTiles[i][j].update(dt);
		}
	}
}

void Map::drawTiles(sf::RenderWindow* window) {
	for (int i = 0; i < mRows; ++i) {
		for (int j = 0; j < mColumns; ++j) {
			mTiles[i][j].draw(window);
		}
	}
}