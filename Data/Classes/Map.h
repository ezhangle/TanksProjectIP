#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <vector>
#include <string>
#include "Entity.h"
#include "ResourceHolder.h"
#include "Enums.h"
#include "Animation.h"

class Map {
	enum {
		OBSTACLE,
		POWERUP,
		TANK,

		NUMBER
	};
public:
												Map(std::string& objectsPath, std::string& charactersPath);
	void										loadFromFile(std::string& objectsPath, std::string& charactersPath);
	void										update(sf::Time dt);
	void										draw(sf::RenderWindow* window);
	void										insertObject(std::string& obj, std::ifstream& stream);
public:
	int											**mObstacleMap;
	float										mTileLength;
	int											mWidth;
	int											mHeight;

	std::vector<std::list<Entity*>>				mEntities;
	std::list<Animation*>						mEffects;
	sf::Sprite									mBackground;
	sf::Clock									mPowerUpRespawnClock;

public:
	void										initObstacleMap();
	void										insertPlayerOne(const std::string& tankType, sf::Vector2f* position, sf::Vector2f* velocity, float health, float damage, size_t team);
	void										insertPlayerTwo(const std::string& tankType, sf::Vector2f* position, sf::Vector2f* velocity, float health, float damage, size_t team);
	void										insertStaticObject(const std::string& textureString, sf::Vector2f* pos);
	void										insertAI(const std::string& difficulty, const std::string& tankType, sf::Vector2f* position, sf::Vector2f* velocity, float health, float damage, size_t team);
	void										insertRandomPowerUp(sf::Vector2f* position);

	void										getTankTextureIds(const std::string& textureString, Texture& baseTexture, Texture& topTexture);
	void										getStaticObjectTextureId(const std::string& textureString, Texture& texture);
};