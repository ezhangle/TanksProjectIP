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
												Map(std::string& path);
	void										loadFromFile(std::string& path);
	void										update(sf::Time dt);
	void										draw(sf::RenderWindow* window);
	void										insertObject(std::string& obj, std::ifstream& stream);
public:
	std::vector<std::list<Entity*>>				mEntities;
	std::list<Animation*>						mEffects;
	sf::Sprite									mBackground;

private:
	void										insertPlayerOne(const std::string& tankType, sf::Vector2f* position, sf::Vector2f* velocity, float health, float damage);
	void										insertPlayerTwo(const std::string& tankType, sf::Vector2f* position, sf::Vector2f* velocity, float health, float damage);
	void										insertStaticObject(const std::string& textureString, sf::Vector2f* pos);

	void										getTankTextureIds(const std::string& textureString, Texture& baseTexture, Texture& topTexture);
	void										getStaticObjectTextureId(const std::string& textureString, Texture& texture);
};