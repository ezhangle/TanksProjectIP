#pragma once
#define TILE_WIDTH 64
#define TILE_HEIGHT 64
#include "Tile.h"
#include "ResourceHolder.h"
#include "Enums.h"
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

class Map {
public:
											Map(ResourceHolder<sf::Texture, Texture>* res);
											Map(std::string& path, ResourceHolder<sf::Texture, Texture>* res);
	void									loadFromFile(std::string& path);
	void									insertObject(int x, int y, std::string& id);
	void									updateTiles(sf::Time dt);
	void									drawTiles(sf::RenderWindow* window);

public:
	int										mRows;
	int										mColumns;
	Tile**									mTiles;
	ResourceHolder<sf::Texture, Texture>*	mTextures;
};