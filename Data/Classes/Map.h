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
	void										insertObject(std::string& obj, sf::Vector2f* pos);
public:
	std::vector<std::list<Entity*>>				mEntities;
	std::list<Animation*>						mEffects;
	sf::Sprite									mBackground;
};