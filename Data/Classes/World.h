#pragma once
#include "Map.h"
#include "ResourceHolder.h"
#include "Enums.h"
#include <list>
#include <string>
#include <vector>

class World {
public:
									World();
	void							loadWorld(std::string path, ResourceHolder<sf::Texture, Texture>* res);
public:
	int								mNodes;
	std::vector<Map*>				mMaps;
	std::vector<std::list<Map*>>	mAdj;

};