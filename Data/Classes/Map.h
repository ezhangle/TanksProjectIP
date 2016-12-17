#pragma once
#define TILE_WIDTH 64
#define TILE_HEIGHT 64
#include "Tile.h"
#include "ResourceHolder.h"
#include "Enums.h"
#include "Entity.h"
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include <vector>

class Tile;
class Entity;


class Map {
public:
	enum class Priority {
		DECO,
		OBSTACLE,
		POWER_UP,
		PLAYER,
		NUMBER
	};
public:
											Map(ResourceHolder<sf::Texture, Texture>* res);
											Map(std::string& path, ResourceHolder<sf::Texture, Texture>* res);
	void									loadFromFile(std::string& path);

	void									generateTerrain();
	void									insertObject(int x, int y, std::string& id);
	void									updateTiles(sf::Time dt);
	void									drawTiles(sf::RenderWindow* window);
	int										getPriority(Entity* entity);

public:
	int										mRows;
	int										mColumns;
	std::vector<Tile**>						mTiles;
	ResourceHolder<sf::Texture, Texture>*	mTextures;
};