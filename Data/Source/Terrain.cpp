#pragma once
#include "Terrain.h"

Terrain::Terrain(sf::Vector2f* pos, sf::Sprite* sprite, bool solid, Map* map)
	:Entity(pos, sprite, map),
	bSolid(solid) {

}

void Terrain::update(sf::Time dt) {

}